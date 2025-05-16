/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.cpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgolubev <mgolubev@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/14 20:27:06 by mgolubev      #+#    #+#                 */
/*   Updated: 2025/05/16 22:49:42 by mgolubev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "Soup.hpp"
#include <iostream>

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
            co_await std::suspend_always{};
            std::cout << "Another task started" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "Another task resumed" << std::endl;
            co_return;
        });

    executer.run(
        []() -> Task<void>
        {
            std::cout << "Task started" << std::endl;
            co_await std::suspend_always{};

            Soup::spawn(
                []() -> Task<void>
                {
                    std::cout << " Nested task started" << std::endl;
                    co_await std::suspend_always{};
                    int result = co_await sum(3, 4);
                    std::cout << " Result of sum(3, 4): " << result
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
                    std::cout << " Nested task resumed" << std::endl;
                    co_return;
                });
            std::cout << "Task resumed" << std::endl;
            co_return;
        });

    return 0;
}
