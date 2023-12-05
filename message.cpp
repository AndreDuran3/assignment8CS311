#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
using namespace std; 
struct City {
    string code;
    string acronym;
    string name;
    int population;
    int area;
};

struct Road {
    string sourceCode;
    string destinationCode;
    int distance;
};

class CityMap {
public:
    void loadCities(const string& filename);
    void loadRoads(const string& filename);
    void findShortestPath(const string& sourceCode, const string& destinationCode);

private:
    vector<City> cities;
    vector<Road> roads;
    unordered_map<string, int> cityCodeIndexMap;
};

void CityMap::loadCities(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        City city;
        iss >> city.code >> city.acronym >> city.name >> city.population >> city.area;
        cities.push_back(city);
        cityCodeIndexMap[city.code] = cities.size() - 1;
    }

    file.close();
}

void CityMap::loadRoads(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        Road road;
        string sourceCode, destinationCode;

        // Read source and destination city codes
        iss >> sourceCode >> destinationCode >> road.distance;

        // Convert city codes to indices
        if (cityCodeIndexMap.find(sourceCode) == cityCodeIndexMap.end() || cityCodeIndexMap.find(destinationCode) == cityCodeIndexMap.end()) {
            cerr << "Invalid city codes in road data: " << sourceCode << " or " << destinationCode << endl;
            continue;
        }

        road.sourceCode = sourceCode;
        road.destinationCode = destinationCode;

        roads.push_back(road);
    }

    file.close();
}

void CityMap::findShortestPath(const string& sourceCode, const string& destinationCode) {
    if (cityCodeIndexMap.find(sourceCode) == cityCodeIndexMap.end() || cityCodeIndexMap.find(destinationCode) == cityCodeIndexMap.end()) {
        cerr << "Invalid city codes." << endl;
        return;
    }

    int sourceIndex = cityCodeIndexMap[sourceCode];
    int destinationIndex = cityCodeIndexMap[destinationCode];

    vector<int> distance(cities.size(), numeric_limits<int>::max());
    distance[sourceIndex] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, sourceIndex});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (const Road& road : roads) {
            if (road.sourceCode == cities[u].code) {
                int v = cityCodeIndexMap[road.destinationCode];
                int w = road.distance;

                if (distance[u] + w < distance[v]) {
                    distance[v] = distance[u] + w;
                    pq.push({distance[v], v});
                }
            }
        }
    }

    if (distance[destinationIndex] == numeric_limits<int>::max()) {
        cout << "No path found from " << sourceCode << " to " << destinationCode << endl;
    } else {
        cout << "The shortest distance from " << cities[sourceIndex].name << " to " << cities[destinationIndex].name
                  << " is " << distance[destinationIndex] << endl;

        cout << "Through the route: ";
        int current = destinationIndex;
        vector<string> route;
        while (current != sourceIndex) {
            route.push_back(cities[current].name);
            current = cityCodeIndexMap[roads[current].sourceCode];
        }
        route.push_back(cities[sourceIndex].name);

        for (auto it = route.rbegin(); it != route.rend(); ++it) {
            cout << *it;
            if (it + 1 != route.rend()) {
                cout << "->";
            }
        }

        cout << endl;
    }
}

int main() {
    CityMap cityMap;
    cityMap.loadCities("city.txt");
    cityMap.loadRoads("road.txt");

    string sourceCode, destinationCode;
    cout << "Enter source city code: ";
    cin >> sourceCode;
    cout << "Enter destination city code: ";
    cin >> destinationCode;

    cityMap.findShortestPath(sourceCode, destinationCode);

    return 0;
}