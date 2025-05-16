/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Worker.tpp                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgolubev <mgolubev@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/16 18:55:12 by mgolubev      #+#    #+#                 */
/*   Updated: 2025/05/16 19:16:01 by mgolubev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Worker.hpp"

template <typename Lambda> void Worker::addLambda(Lambda &&lambda)
{
    using TaskType = decltype(lambda());
    addTask(std::make_unique<TaskType>(lambda()));
}
