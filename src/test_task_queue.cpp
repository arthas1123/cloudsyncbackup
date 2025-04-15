#include "threading/task_queue.hpp"
#include <iostream>
#include <thread>
#include <chrono>

void producer(TaskQueue<std::string> &queue)
{
    for (int i = 1; i <= 5; ++i)
    {
        std::string task = "任務_" + std::to_string(i);
        std::cout << "📤 加入任務：" << task << std::endl;
        queue.push(task);
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 模擬延遲
    }
}

void consumer(TaskQueue<std::string> &queue)
{
    for (int i = 1; i <= 5; ++i)
    {
        std::string task = queue.pop(); // 這會阻塞直到有東西
        std::cout << "✅ 處理任務：" << task << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(150)); // 模擬工作時間
    }
}

int main()
{
    TaskQueue<std::string> queue;

    std::thread t1(producer, std::ref(queue));
    std::thread t2(consumer, std::ref(queue));

    t1.join();
    t2.join();

    std::cout << "🎉 所有任務已完成！" << std::endl;
    return 0;
}
