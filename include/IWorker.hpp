/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   IWorker.hpp                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgolubev <mgolubev@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/16 19:56:42 by mgolubev      #+#    #+#                 */
/*   Updated: 2025/05/16 21:32:31 by mgolubev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ITask.hpp"

class IWorker
{
  public:
    /// @brief Virtual destructor
    virtual ~IWorker() = default;

    /// @brief Add a task to the worker's queue
    /// @param task Pointer to the task
    virtual void addTask(ITask::Ptr task) = 0;

    /// @brief Stop the worker
    virtual void stop() = 0;

    /// @brief Get the current worker for this thread
    /// @return Pointer to the current worker or nullptr
    static IWorker *getCurrent() noexcept { return _tls_worker; }

  private:
    static thread_local IWorker *_tls_worker;

  protected:
    /// @brief Set the current worker for this thread
    /// @param worker Pointer to the worker
    static void setCurrent(IWorker *worker) noexcept { _tls_worker = worker; }
};