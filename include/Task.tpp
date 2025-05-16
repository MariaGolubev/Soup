#pragma once
#include "Task.hpp"
//
// Task<T>: реализация
//

template <typename T>
Task<T>::Task(HandleType h)
    : coro(h)
{
}

template <typename T> Task<T>::~Task()
{
    if (coro)
        coro.destroy();
}

template <typename T>
Task<T>::Task(Task &&other) noexcept
    : coro(other.coro)
{
    other.coro = nullptr;
}

template <typename T> Task<T> &Task<T>::operator=(Task &&other) noexcept
{
    if (this != &other)
    {
        if (coro)
            coro.destroy();
        coro = other.coro;
        other.coro = nullptr;
    }
    return *this;
}

template <typename T> bool Task<T>::done() const { return coro.done(); }

template <typename T> void Task<T>::resume()
{
    if (!done())
        coro.resume();
}

template <typename T> void Task<T>::call() { resume(); }

template <typename T> T Task<T>::get()
{
    if (!done())
        coro.resume();
    if (coro.promise().exception)
        std::rethrow_exception(coro.promise().exception);
    return std::move(coro.promise().value.value());
}

template <typename T> auto Task<T>::operator co_await()
{
    struct Awaiter
    {
        HandleType coro;
        bool       await_ready() const noexcept { return coro.done(); }

        bool await_suspend(std::coroutine_handle<> awaiting_coro) noexcept
        {
            coro.promise().continuation = awaiting_coro;
            coro.resume();
            return false;
        }

        T await_resume()
        {
            if (coro.promise().exception)
                std::rethrow_exception(coro.promise().exception);
            return std::move(coro.promise().value.value());
        }
    };
    return Awaiter{coro};
}

//
// Task<T>::promise_type
//

template <typename T>
Task<T> Task<T>::promise_type::get_return_object() noexcept
{
    return Task<T>{std::coroutine_handle<promise_type>::from_promise(*this)};
}

template <typename T>
std::suspend_never Task<T>::promise_type::initial_suspend() noexcept
{
    return {};
}

template <typename T>
std::suspend_always Task<T>::promise_type::final_suspend() noexcept
{
    return {};
}

template <typename T> void Task<T>::promise_type::return_value(T v)
{
    value = std::move(v);
}

template <typename T> void Task<T>::promise_type::unhandled_exception()
{
    exception = std::current_exception();
}

//
// Task<void>: реализация
//

inline Task<void>::Task(HandleType h)
    : coro(h)
{
}

inline Task<void>::~Task()
{
    if (coro)
        coro.destroy();
}

inline Task<void>::Task(Task &&other) noexcept
    : coro(other.coro)
{
    other.coro = nullptr;
}

inline Task<void> &Task<void>::operator=(Task<void> &&other) noexcept
{
    if (this != &other)
    {
        if (coro)
            coro.destroy();
        coro = other.coro;
        other.coro = nullptr;
    }
    return *this;
}

inline bool Task<void>::done() const { return coro.done(); }

inline void Task<void>::resume()
{
    if (!done())
        coro.resume();
}

inline void Task<void>::call() { resume(); }

inline void Task<void>::get()
{
    if (!done())
        coro.resume();
    if (coro.promise().exception)
        std::rethrow_exception(coro.promise().exception.value());
}

inline auto Task<void>::operator co_await()
{
    struct Awaiter
    {
        HandleType coro;
        bool       await_ready() const noexcept { return coro.done(); }

        bool await_suspend(std::coroutine_handle<> awaiting_coro) noexcept
        {
            coro.promise().continuation = awaiting_coro;
            coro.resume();
            return true;
        }

        void await_resume()
        {
            if (coro.promise().exception)
                std::rethrow_exception(coro.promise().exception.value());
        }
    };
    return Awaiter{coro};
}

//
// Task<void>::promise_type
//

inline Task<void> Task<void>::promise_type::get_return_object() noexcept
{
    return Task<void>{std::coroutine_handle<promise_type>::from_promise(*this)};
}

inline std::suspend_never Task<void>::promise_type::initial_suspend() noexcept
{
    return {};
}

inline std::suspend_always Task<void>::promise_type::final_suspend() noexcept
{
    return {};
}

inline void Task<void>::promise_type::return_void() {}

inline void Task<void>::promise_type::unhandled_exception()
{
    exception = std::current_exception();
}