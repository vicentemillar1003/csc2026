// CSC Latin America 2026 - Event Processor Tests
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "EventProcessor.hpp"

using namespace csc2026;
using Catch::Approx;

TEST_CASE("EventProcessor default state", "[processor]") {
    EventProcessor processor;
    REQUIRE(processor.totalTracksProcessed() == 0);
    REQUIRE(processor.totalEnergy() == 0.0);
}

TEST_CASE("EventProcessor single event", "[processor]") {
    EventProcessor processor;
    
    Event event;
    event.eventNumber = 1;
    event.particles.emplace_back(1.0, 0.0, 0.0, 0.0);  // E = 1
    event.particles.emplace_back(0.0, 2.0, 0.0, 0.0);  // E = 2
    
    processor.processEvent(event);
    
    REQUIRE(processor.totalTracksProcessed() == 2);
    REQUIRE(processor.totalEnergy() == Approx(3.0));
}

TEST_CASE("EventProcessor multiple events", "[processor]") {
    EventProcessor processor;
    
    std::vector<Event> events(3);
    for (auto& event : events) {
        event.particles.emplace_back(1.0, 0.0, 0.0, 0.0);
    }
    
    processor.processEvents(events);
    
    REQUIRE(processor.totalTracksProcessed() == 3);
}

TEST_CASE("EventProcessor reset", "[processor]") {
    EventProcessor processor;
    
    Event event;
    event.particles.emplace_back(1.0, 0.0, 0.0, 0.0);
    processor.processEvent(event);
    
    REQUIRE(processor.totalTracksProcessed() == 1);
    
    processor.reset();
    
    REQUIRE(processor.totalTracksProcessed() == 0);
    REQUIRE(processor.totalEnergy() == 0.0);
}

TEST_CASE("Generate sample events", "[processor]") {
    auto events = generateSampleEvents(10, 5);
    
    REQUIRE(events.size() == 10);
    for (const auto& event : events) {
        REQUIRE(event.particles.size() == 5);
    }
}

TEST_CASE("EventProcessor parallel consistency", "[processor][parallel]") {
    // Process same events and verify results are consistent
    auto events = generateSampleEvents(100, 10);
    
    EventProcessor processor1;
    EventProcessor processor2;
    
    // Sequential processing
    for (const auto& event : events) {
        processor1.processEvent(event);
    }
    
    // Parallel processing
    processor2.processEvents(events);
    
    REQUIRE(processor1.totalTracksProcessed() == processor2.totalTracksProcessed());
    REQUIRE(processor1.totalEnergy() == Approx(processor2.totalEnergy()));
}
