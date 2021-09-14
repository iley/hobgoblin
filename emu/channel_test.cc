#define CATCH_CONFIG_MAIN
#include "third_party/catch.hpp"

#include <vector>
#include <thread>

#include "channel.h"

namespace emu {

TEST_CASE("producer-consumer") {
    Channel<int> channel(1);

    std::thread producer([&channel]() {
        for (int i = 0; i < 10; i++) {
            channel.Send(i);
        }
    });

    std::vector<int> received;
    std::thread consumer([&channel, &received]() {
        for (int i = 0; i < 10; i++) {
            int value = channel.Receive();
            received.push_back(value);
        }
    });

    producer.join();
    consumer.join();

    REQUIRE(received == std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
}

TEST_CASE("TrySend") {
    Channel<int> channel(2);

    REQUIRE(channel.TrySend(1));
    REQUIRE(channel.TrySend(2));
    REQUIRE(!channel.TrySend(3));

    REQUIRE(channel.Receive() == 1);
    REQUIRE(channel.Receive() == 2);
}

TEST_CASE("TryReceive") {
    Channel<int> channel(2);

    channel.Send(1);
    channel.Send(2);

    auto value = channel.TryReceive();
    REQUIRE(value);
    REQUIRE(*value == 1);
    value = channel.TryReceive();
    REQUIRE(value);
    REQUIRE(*value == 2);
}

} // namespace emu
