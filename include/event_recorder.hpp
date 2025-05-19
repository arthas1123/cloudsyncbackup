#ifndef EVENT_RECORDER_HPP
#define EVENT_RECORDER_HPP

#include <fstream>
#include <mutex>
#include <string>
#include <memory> // For std::enable_shared_from_this

// Forward declarations
class EventBus;
class EventBase;

class EventRecorder : public std::enable_shared_from_this<EventRecorder>
{
public:
    explicit EventRecorder(const std::string &filename);
    ~EventRecorder();

    void subscribeToEvents(EventBus &bus);
    void recordEvent(const std::shared_ptr<EventBase> &event);

private:
    std::ofstream logFile_;
    std::mutex mutex_;
};

#endif // EVENT_RECORDER_HPP
