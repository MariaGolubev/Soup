/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   Soup.hpp                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgolubev <mgolubev@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/05/16 20:01:25 by mgolubev      #+#    #+#                 */
/*   Updated: 2025/05/16 21:32:31 by mgolubev      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Task.hpp"
#include "Worker.hpp"
#include <memory>

constexpr const char *SOUP_ART =
    R"(                                             
  █████████                                        
 ███░░░░░███                                       
░███    ░░░   ██████  █████ ████ ████████ 
░░█████████  ███░░███░░███ ░███ ░░███░░███
 ░░░░░░░░███░███ ░███ ░███ ░███  ░███ ░███
 ███    ░███░███ ░███ ░███ ░███  ░███ ░███
░░█████████ ░░██████  ░░████████ ░███████ 
 ░░░░░░░░░   ░░░░░░    ░░░░░░░░  ░███░░░  
                               ░███      
                               █████     
                              ░░░░░       
)";

class Soup : public IWorker
{
  public:
    /// @brief Constructor for the worker pool
    /// @param coutn Number of workers (default: hardware concurrency)
    Soup(size_t coutn = std::thread::hardware_concurrency());
    /// @brief Destructor for the worker pool
    ~Soup();
    Soup(const Soup &) = delete;
    Soup(Soup &&) = delete;
    Soup &operator=(const Soup &) = delete;
    Soup &operator=(Soup &&) = delete;

    /// @brief Add a task to the worker pool
    /// @param task Pointer to the task
    void addTask(ITask::Ptr task) override;

    /// @brief Stop all workers
    void stop() override;

    /// @brief Run a function in the worker pool
    /// @param func Function returning Task<void>
    void run(std::function<Task<void>()> func);

    /// @brief Statically spawn a function in a new worker pool
    /// @param func Function returning Task<void>
    static void spawn(std::function<Task<void>()> func);

  private:
    std::atomic<bool>        _running;
    size_t                   _index;
    std::vector<Worker::Ptr> _workers;
};