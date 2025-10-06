#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Taxi {
    long long lastTimestamp;
    int position;
};

int main() {
    int N, L, S;
    cin >> N >> L >> S;

    map<int, Taxi> taxis;
    vector<vector<int>> orderResults;

    for (int i = 0; i < N; ++i) {
        string type;
        long long timestamp;
        cin >> type >> timestamp;

        if (type == "TAXI") {
            int taxiId, position;
            cin >> taxiId >> position;
            taxis[taxiId] = {timestamp, position};
        } else if (type == "ORDER") {
            int orderId, orderPosition, orderTime;
            cin >> orderId >> orderPosition >> orderTime;

            vector<int> availableTaxis;
            for (auto& [taxiId, taxi] : taxis) {
                long long timeDiff = timestamp - taxi.lastTimestamp;
                int maxDistance = timeDiff * S;
                int minPos = taxi.position;
                int maxPos = (taxi.position + maxDistance) % L;

                bool isIn;
                // проверка: заказ внутри или снаружи области таксиста
                // 1. не пересекает начало круга
                if (minPos <= maxPos)
                    isIn = minPos <= orderPosition && orderPosition < maxPos;
                // 2. пересекает начало круга
                else
                    isIn = orderPosition >= minPos || orderPosition < maxPos;

                int worstPosition;
                if (maxDistance >= L) {
                    worstPosition = (orderPosition + 1) % L;
                }
                else {
                    if (isIn)
                        worstPosition = (orderPosition + 1) % L;
                    else
                        worstPosition = minPos;
                }

                // TAXI <timestamp> <taxi_id> <taxi_position>
                // ORDER <timestamp> <order_id> <order_position> <order_time>
                int distance = (orderPosition - worstPosition + L) % L;

                if (distance <= orderTime * S) {
                    availableTaxis.push_back(taxiId);
                }
            }

            if (availableTaxis.empty()) {
                orderResults.push_back({-1});
            } else {
                sort(availableTaxis.begin(), availableTaxis.end());
                if (availableTaxis.size() > 5) {
                    availableTaxis.resize(5);
                }
                orderResults.push_back(availableTaxis);
            }
        }
    }

    for (const auto& result : orderResults) {
        for (size_t i = 0; i < result.size(); ++i) {
            cout << result[i];
            if (i + 1 < result.size()) {
                cout << " ";
            }
        }
        cout << endl;
    }

    return 0;
}