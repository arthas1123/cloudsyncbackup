#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class TaskQueue
{
public:
    TaskQueue() = default;

    void push(const T &task)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        queue_.push(task);
        cv_.notify_one(); // 通知一個等待的執行緒
    }

    T pop()
    {
        std::unique_lock<std::mutex> lock(mtx_);
        cv_.wait(lock, [this]
                 { return !queue_.empty(); }); // 等待直到有任務
        T task = queue_.front();
        queue_.pop();
        return task;
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(mtx_);
        return queue_.empty();
    }

private:
    std::queue<T> queue_;
    mutable std::mutex mtx_;
    std::condition_variable cv_;
};
