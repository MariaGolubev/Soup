# Soup

<p align="center">
	<img src="soup_image.png" alt="Soup Library" />
</p>

## Описание / Description

**Soup** — это минималистичная библиотека для асинхронного исполнения задач на основе корутин C++20 с поддержкой пула потоков. Она позволяет запускать и координировать задачи, которые могут приостанавливаться и возобновляться, а также создавать вложенные задачи.

**Soup** is a minimalist library for asynchronous task execution based on C++20 coroutines with thread pool support. It allows you to launch and coordinate tasks that can be suspended and resumed, as well as create nested tasks.

## Основные компоненты / Main Components

### 1. `Task<T>`

Шаблонная корутина-обёртка, реализующая асинхронную задачу с возвращаемым значением типа `T`.  
- Управляет жизненным циклом корутины.
- Позволяет приостанавливать и возобновлять выполнение.
- Для `Task<void>` реализована специализация для задач без возвращаемого значения.

A coroutine wrapper template implementing an asynchronous task returning a value of type `T`.
- Manages the coroutine lifecycle.
- Allows suspending and resuming execution.
- Specialization for `Task<void>` for tasks without a return value.

### 2. `ITask`

Базовый абстрактный интерфейс для всех задач.  
- Определяет методы `call()` (выполнить задачу) и `done()` (проверить завершение).

Base abstract interface for all tasks.
- Defines `call()` (execute the task) and `done()` (check if finished) methods.

### 3. `IWorker`

Абстрактный интерфейс для воркеров (рабочих потоков).  
- Позволяет добавлять задачи в очередь и останавливать воркер.
- Реализует механизм thread-local текущего воркера.

Abstract interface for workers (worker threads).
- Allows adding tasks to the queue and stopping the worker.
- Implements thread-local current worker mechanism.

### 4. `Worker`

Реализация воркера, который исполняет задачи из своей очереди в отдельном потоке.  
- Поддерживает добавление задач и корректное завершение работы.

Worker implementation that executes tasks from its queue in a separate thread.
- Supports adding tasks and proper shutdown.

### 5. `Soup`

Пул воркеров (thread pool), реализующий интерфейс `IWorker`.  
- Автоматически распределяет задачи между воркерами.
- Предоставляет статический метод `spawn` для запуска задач из любой корутины.

Thread pool implementing the `IWorker` interface.
- Automatically distributes tasks among workers.
- Provides a static `spawn` method to launch tasks from any coroutine.

## Что происходит в `main.cpp` / What happens in `main.cpp`

В функции `main` демонстрируется запуск задач с помощью пула воркеров:

1. Выводится ASCII-арт.
2. Создаётся объект `Soup` — пул воркеров.
3. Через метод `run` запускается корутина, которая:
    - Выводит сообщение о старте.
    - Приостанавливается и возобновляется.
    - Внутри себя спаунит вложенную задачу через `Soup::spawn`, которая:
        - Также приостанавливается и возобновляется.
        - Асинхронно вызывает функцию `sum(3, 4)` и выводит результат.
        - Вложенно спаунит ещё одну задачу, которая выводит сообщения о старте и возобновлении.
4. Все задачи исполняются асинхронно в пуле потоков.

The `main` function demonstrates launching tasks using the thread pool:

1. Prints ASCII art.
2. Creates a `Soup` object (thread pool).
3. Launches a coroutine via `run` method, which:
    - Prints a start message.
    - Suspends and resumes.
    - Spawns a nested task via `Soup::spawn`, which:
        - Also suspends and resumes.
        - Asynchronously calls `sum(3, 4)` and prints the result.
        - Spawns another nested task that prints start and resume messages.
4. All tasks are executed asynchronously in the thread pool.

## Пример запуска / Example Build & Run

```sh
g++ -std=c++20 -pthread *.cpp -o Soup
./Soup
```

## Зависимости / Dependencies

- C++20 (coroutines)
- pthread (for multithreading)

## Назначение классов / Class Responsibilities

- **Task<T>** — асинхронная задача-корутина.  
  Asynchronous coroutine task.
- **ITask** — базовый интерфейс для задач.  
  Base interface for tasks.
- **IWorker** — базовый интерфейс для воркеров.  
  Base interface for workers.
- **Worker** — поток-воркер, исполняющий задачи.  
  Worker thread executing tasks.
- **Soup** — пул воркеров, распределяющий задачи между потоками.  
  Thread pool distributing tasks among threads.

## Лицензия / License

MIT
