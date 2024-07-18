#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>

using namespace std;

class FlightGraph {
public:
    // Initialize the graph with given number of cities
    FlightGraph() {
        n = 5;
        cityMap = {{"Mumbai", 0}, {"Delhi", 1}, {"Kolkata", 2}, {"Chennai", 3}, {"Bangalore", 4}};
        cities = {"Mumbai", "Delhi", "Kolkata", "Chennai", "Bangalore"};

        adjList.resize(n);
        addFlight(0, 1, 5000); // Mumbai to Delhi
        addFlight(1, 2, 4000); // Delhi to Kolkata
        addFlight(2, 3, 3000); // Kolkata to Chennai
        addFlight(3, 4, 2000); // Chennai to Bangalore
        addFlight(4, 0, 4500); // Bangalore to Mumbai
        addFlight(0, 3, 6000); // Mumbai to Chennai
    }

    // Find the cheapest price with at most k stops
    int findCheapestPrice(int src, int dst, int k) {
        vector<vector<int>> prices(n, vector<int>(k + 2, INT_MAX));
        prices[src][0] = 0;

        priority_queue<vector<int>, vector<vector<int>>, greater<>> pq;
        pq.push({0, src, 0}); // {cost, city, stops}

        while (!pq.empty()) {
            auto top = pq.top();
            pq.pop();

            int cost = top[0];
            int city = top[1];
            int stops = top[2];

            if (city == dst) return cost;
            if (stops > k) continue;

            for (auto& next : adjList[city]) {
                int nextCity = next.first;
                int nextCost = next.second;

                if (cost + nextCost < prices[nextCity][stops + 1]) {
                    prices[nextCity][stops + 1] = cost + nextCost;
                    pq.push({cost + nextCost, nextCity, stops + 1});
                }
            }
        }

        return -1;
    }

    // Function to get the city index from the city name
    int getCityIndex(const string& cityName) {
        if (cityMap.find(cityName) != cityMap.end()) {
            return cityMap[cityName];
        }
        return -1;
    }

private:
    int n;
    vector<vector<pair<int, int>>> adjList; // {destination, price}
    unordered_map<string, int> cityMap;
    vector<string> cities;

    // Add an edge (flight) to the graph
    void addFlight(int from, int to, int price) {
        adjList[from].push_back({to, price});
    }
};

int main() {
    FlightGraph graph;

    string srcCity, dstCity;
    int k;
    cout << "Enter the source city: ";
    cin >> srcCity;
    cout << "Enter the destination city: ";
    cin >> dstCity;
    cout << "Enter the maximum number of stops: ";
    cin >> k;

    int src = graph.getCityIndex(srcCity);
    int dst = graph.getCityIndex(dstCity);

    if (src == -1 || dst == -1) {
        cout << "Invalid city names entered.\n";
        return 1;
    }

    int result = graph.findCheapestPrice(src, dst, k);

    if (result != -1) {
        cout << "The cheapest price from " << srcCity << " to " << dstCity << " with at most " << k << " stops is: " << result << "\n";
    } else {
        cout << "No route found from " << srcCity << " to " << dstCity << " within " << k << " stops.\n";
    }

    return 0;
}
