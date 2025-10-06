#include <unordered_map>
#include <deque>
#include <set>
#include <ctime>

class RobotStatistics {
private:
    static constexpr time_t WINDOW_SIZE = 300; // 5 minutes in seconds
    static constexpr int EVENT_THRESHOLD = 1000;
    
    // For each user, store their events in a deque with timestamps
    std::unordered_map<int, std::deque<time_t>> user_events;
    // Keep track of users who are currently considered robots
    std::set<int> current_robots;
    
    // Clean up old events for a specific user
    void cleanupUserEvents(int userId, time_t now) {
        auto& events = user_events[userId];
        while (!events.empty() && events.front() < now - WINDOW_SIZE) {
            events.pop_front();
        }
    }
    
    // Update robot status for a user
    void updateRobotStatus(int userId, time_t now) {
        cleanupUserEvents(userId, now);
        auto& events = user_events[userId];
        
        if (events.size() >= EVENT_THRESHOLD) {
            current_robots.insert(userId);
        } else {
            current_robots.erase(userId);
        }
    }

public:
    void OnEvent(time_t now, int userId) {
        user_events[userId].push_back(now);
        updateRobotStatus(userId, now);
    }
    
    int GetRobotCount(time_t now) {
        // Clean up old events for all users
        for (auto& [userId, events] : user_events) {
            cleanupUserEvents(userId, now);
            updateRobotStatus(userId, now);
        }
        return current_robots.size();
    }
};

// Example usage:

int main() {
    RobotStatistics stats;
    
    // Simulate some events
    stats.OnEvent(1000, 1);  // User 1 generates an event
    stats.OnEvent(1001, 1);
    stats.OnEvent(1002, 2);  // User 2 generates an event
    
    // Get current robot count
    int robotCount = stats.GetRobotCount(1003);
    
    return 0;
}

