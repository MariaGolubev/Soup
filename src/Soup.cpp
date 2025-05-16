/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Soup.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgolubev <mgolubev@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/16 20:05:26 by mgolubev      #+#    #+#                 */
/*   Updated: 2025/05/16 21:12:58 by mgolubev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Soup.hpp"
#include "Task.hpp"

#include "iostream"

Soup::Soup(size_t count)
    : _running(true)
    , _index(0)
{
    setCurrent(this);
    if (count == 0)
        throw std::invalid_argument("Executer must have at least one worker");
    for (size_t i = 0; i < count; ++i)
    {
        _workers.emplace_back(std::make_unique<Worker>(_running));
    }
}

Soup::~Soup() { setCurrent(nullptr); }

void Soup::addTask(ITask::Ptr task)
{
    if (!_running)
        throw std::runtime_error("Executer is not running");
    if (!task)
        throw std::invalid_argument("Task cannot be null");

    _workers[_index]->addTask(std::move(task));
    _index = (_index + 1) % _workers.size();
}

void Soup::stop()
{
    for (auto &worker : _workers)
    {
        worker->stop();
    }
}

void Soup::run(std::function<Task<void>()> func)
{
    Soup::spawn(std::move(func));
}

void Soup::spawn(std::function<Task<void>()> func)
{

    if (!IWorker::getCurrent())
        throw std::runtime_error("Executer is not running");

    IWorker::getCurrent()->addTask(
        std::make_unique<Task<void>>(std::move(func())));
}
