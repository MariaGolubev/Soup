/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgolubev <mgolubev@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/14 20:27:06 by mgolubev      #+#    #+#                 */
/*   Updated: 2025/05/16 21:23:10 by mgolubev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Soup.hpp"

#include <coroutine>
#include <iostream>
#include <optional>

Task<int> sum(int a, int b)
{
    co_await std::suspend_always{};
    co_return a + b;
}

int main()
{
    std::cout << SOUP_ART << std::endl;

    Soup executer;

    executer.run(
        []() -> Task<void>
        {
            std::cout << "Task started" << std::endl;
            co_await std::suspend_always{};
            std::cout << "Task resumed" << std::endl;

            Soup::spawn(
                []() -> Task<void>
                {
                    std::cout << " Nested task started" << std::endl;
                    co_await std::suspend_always{};
                    std::cout << " Nested task resumed" << std::endl;

                    int result = co_await sum(3, 4);

                    std::cout << "  Result of sum(3, 4): " << result
                              << std::endl;

                    Soup::spawn(
                        []() -> Task<void>
                        {
                            std::cout << "  Deeply nested task started"
                                      << std::endl;
                            co_await std::suspend_always{};
                            std::cout << "  Deeply nested task resumed"
                                      << std::endl;
                            co_return;
                        });

                    co_return;
                });
            co_return;
        });

    return 0;
}
