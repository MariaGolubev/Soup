/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ITask.hpp                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgolubev <mgolubev@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/16 16:51:17 by mgolubev      #+#    #+#                 */
/*   Updated: 2025/05/16 21:32:31 by mgolubev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <memory>

struct ITask
{
    /// @brief Smart pointer type for tasks
    using Ptr = std::unique_ptr<ITask>;

    /// @brief Virtual destructor
    virtual ~ITask() = default;

    /// @brief Execute the task (or resume coroutine)
    virtual void call() = 0;

    /// @brief Check if the task is finished
    virtual bool done() const = 0;
};