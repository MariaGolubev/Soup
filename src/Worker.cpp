/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Worker.cpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgolubev <mgolubev@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/16 18:56:02 by mgolubev      #+#    #+#                 */
/*   Updated: 2025/05/16 21:07:05 by mgolubev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Worker.hpp"
#include "Task.hpp"
#include <iostream>

thread_local IWorker *IWorker::_tls_worker = nullptr;

Worker::Worker(std::atomic<bool> &running) noexcept
    : _running(running)
    , _thread(&Worker::_workerLoop, this)
{
}

Worker::~Worker()
{
    stop();
    if (_thread.joinable())
        _thread.join();
}

void Worker::addTask(ITask::Ptr task)
{
    {
        std::lock_guard lock(_mutex);
        _tasks.push(std::move(task));
    }
    _condition.notify_one();
}

void Worker::stop()
{
    _running = false;
    _condition.notify_all();
}

void Worker::_workerLoop()
{
    setCurrent(this);

    while (true)
    {
        ITask::Ptr task;
        {
            std::unique_lock lock(_mutex);
            _condition.wait(lock,
                            [this] { return !_tasks.empty() || !_running; });

            if (!_running && _tasks.empty())
                return;

            task = std::move(_tasks.front());
            _tasks.pop();
        }

        try
        {
            task->call();
        }
        catch (const std::exception &e)
        {
            std::cerr << "Exception in worker: " << e.what() << std::endl;
        }
        catch (...)
        {
            std::cerr << "Unknown exception in worker" << std::endl;
        }
    }
    setCurrent(nullptr);
}