/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Worker.hpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgolubev <mgolubev@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/16 16:49:10 by mgolubev      #+#    #+#                 */
/*   Updated: 2025/05/16 21:32:31 by mgolubev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ITask.hpp"
#include "IWorker.hpp"

#include <atomic>
#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

template <typename T> struct Task;

class Worker : public IWorker
{
  public:
    /// @brief Smart pointer type for Worker
    using Ptr = std::unique_ptr<Worker>;

    /// @brief Worker constructor
    /// @param running Reference to the running flag
    Worker(std::atomic<bool> &running) noexcept;

    /// @brief Worker destructor
    ~Worker();

    Worker(const Worker &) = delete;
    Worker &operator=(const Worker &) = delete;
    Worker(Worker &&) noexcept = delete;
    Worker &operator=(Worker &&) noexcept = delete;

    /// @brief Add a task to the worker's queue
    /// @param task Pointer to the task
    void addTask(ITask::Ptr task);

    /// @brief Add a lambda as a task
    /// @param lambda Lambda function
    template <typename Lambda> void addLambda(Lambda &&lambda);

    /// @brief Stop the worker
    void stop();

    // static void spawn(std::function<Task<void>()> func);

  private:
    std::atomic<bool>      &_running;
    std::thread             _thread;
    std::mutex              _mutex;
    std::condition_variable _condition;
    std::queue<ITask::Ptr>  _tasks;

    /// @brief Main worker loop
    void _workerLoop();
};

#include "Worker.tpp"