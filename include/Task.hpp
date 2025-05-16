/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Task.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgolubev <mgolubev@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/16 19:23:10 by mgolubev      #+#    #+#                 */
/*   Updated: 2025/05/16 21:32:31 by mgolubev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ITask.hpp"
#include <coroutine>
#include <exception>
#include <optional>
#include <utility>

template <typename T> struct Task;

template <typename T> struct Task : public ITask
{
    struct promise_type
    {
        std::optional<T>        value;
        std::exception_ptr      exception;
        std::coroutine_handle<> continuation;

        /// @brief Get the Task object from the promise
        Task<T> get_return_object() noexcept;
        /// @brief Initial suspend point (not used)
        std::suspend_never initial_suspend() noexcept;
        /// @brief Final suspend point (used for awaiting)
        std::suspend_always final_suspend() noexcept;
        /// @brief Return a value from the coroutine
        void return_value(T v);
        /// @brief Handle unhandled exceptions
        void unhandled_exception();
    };

    /// @brief Coroutine handle type
    using HandleType = std::coroutine_handle<promise_type>;

    HandleType coro;

    /// @brief Construct from coroutine handle
    explicit Task(HandleType h);
    /// @brief Destructor
    ~Task();
    /// @brief Copy constructor (deleted)
    Task(const Task &) = delete;
    /// @brief Move constructor
    Task(Task &&other) noexcept;
    /// @brief Copy assignment (deleted)
    Task &operator=(const Task &) = delete;
    /// @brief Move assignment
    Task &operator=(Task &&other) noexcept;

    /// @brief Check if the task is finished
    bool done() const override;
    /// @brief Resume the task
    void resume();
    /// @brief Execute the task (for ITask interface)
    void call() override;
    /// @brief Get the result of the task
    T get();

    /// @brief co_await operator for coroutine support
    auto operator co_await();
};

template <> struct Task<void> : public ITask
{
    struct promise_type
    {
        std::optional<std::exception_ptr> exception;
        std::coroutine_handle<>           continuation;

        /// @brief Get the Task<void> object from the promise
        Task<void> get_return_object() noexcept;
        /// @brief Initial suspend point (not used)
        std::suspend_never initial_suspend() noexcept;
        /// @brief Final suspend point (used for awaiting)
        std::suspend_always final_suspend() noexcept;
        /// @brief Complete the coroutine without a return value
        void return_void();
        /// @brief Handle unhandled exceptions
        void unhandled_exception();
    };

    /// @brief Coroutine handle type
    using HandleType = std::coroutine_handle<promise_type>;

    HandleType coro;

    /// @brief Construct from coroutine handle
    explicit Task(HandleType h);
    /// @brief Destructor
    ~Task();
    /// @brief Copy constructor (deleted)
    Task(const Task &) = delete;
    /// @brief Move constructor
    Task(Task &&other) noexcept;
    /// @brief Copy assignment (deleted)
    Task &operator=(const Task &) = delete;
    /// @brief Move assignment
    Task &operator=(Task &&other) noexcept;

    /// @brief Check if the task is finished
    bool done() const override;
    /// @brief Resume the task
    void resume();
    /// @brief Execute the task (for ITask interface)
    void call() override;
    /// @brief Get the result of the task (does not return anything)
    void get();

    /// @brief co_await operator for coroutine support
    auto operator co_await();
};

#include "Task.tpp"
