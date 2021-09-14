#ifndef _HOBGOBLIN_EMU_CHANNEL_H
#define _HOBGOBLIN_EMU_CHANNEL_H

#include <cassert>
#include <condition_variable>
#include <mutex>
#include <optional>
#include <queue>
#include <thread>

namespace emu {

template <typename T>
class Channel {
public:
    explicit Channel(std::size_t size)
        : size_(size)
    {
        assert(size_ > 0);
    }

    bool Empty() const {
        std::unique_lock lock(mutex_);
        return buffer_.empty();
    }

    void Send(T value) {
        std::unique_lock lock(mutex_);
        while (buffer_.size() >= size_) {
            buffer_not_full_.wait(lock);
        }
        buffer_.push(value);
        lock.unlock();
        buffer_not_empty_.notify_all();
    }

    bool TrySend(T value) {
        std::unique_lock lock(mutex_);
        if (buffer_.size() >= size_) {
            return false;
        }
        buffer_.push(value);
        lock.unlock();
        buffer_not_empty_.notify_all();
        return true;
    }

    T Receive() {
        std::unique_lock lock(mutex_);
        while (buffer_.empty()) {
            buffer_not_empty_.wait(lock);
        }
        T value = buffer_.front();
        buffer_.pop();
        lock.unlock();
        buffer_not_full_.notify_all();
        return value;
    }

    std::optional<T> TryReceive() {
        std::unique_lock lock(mutex_);
        if (buffer_.empty()) {
            return std::nullopt;
        }
        T value = buffer_.front();
        buffer_.pop();
        lock.unlock();
        buffer_not_full_.notify_all();
        return value;
    }

private:
    mutable std::mutex mutex_;
    std::size_t size_;
    std::queue<T> buffer_;
    std::condition_variable buffer_not_empty_;
    std::condition_variable buffer_not_full_;
};

} // namespace emu

#endif // _HOBGOBLIN_EMU_CHANNEL_H 
