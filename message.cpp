#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>

namespace std {

    struct City {
        std::string code;
        std::string acronym;
        std::string name;
        int population;
        int area;
    };

    struct Road {
        std::string sourceCode;
        std::string destinationCode;
        int distance;
    };

    class CityMap {
    public:
        void loadCities(const std::string& filename);
        void loadRoads(const std::string& filename);
        void findShortestPath(const std::string& sourceCode, const std::string& destinationCode);
        const std::vector<City>& getCities() const;

    private:
        std::vector<City> cities;
        std::vector<Road> roads;
        std::unordered_map<std::string, int> cityCodeIndexMap;
    };

    void CityMap::loadCities(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            City city;
            iss >> city.code >> city.acronym >> city.name >> city.population >> city.area;
            cities.push_back(city);
            cityCodeIndexMap[city.code] = cities.size() - 1;
        }

        file.close();
    }

    void CityMap::loadRoads(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            Road road;
            std::string sourceCode, destinationCode;
            iss >> sourceCode >> destinationCode >> road.distance;

            if (cityCodeIndexMap.find(sourceCode) == cityCodeIndexMap.end() || cityCodeIndexMap.find(destinationCode) == cityCodeIndexMap.end()) {
                std::cerr << "Invalid city codes in road data: " << sourceCode << " or " << destinationCode << std::endl;
                continue;
            }

            road.sourceCode = sourceCode;
            road.destinationCode = destinationCode;

            roads.push_back(road);
        }

        file.close();
    }

    void CityMap::findShortestPath(const std::string& sourceCode, const std::string& destinationCode) {
        if (cityCodeIndexMap.find(sourceCode) == cityCodeIndexMap.end() || cityCodeIndexMap.find(destinationCode) == cityCodeIndexMap.end()) {
            std::cerr << "Invalid city codes." << std::endl;
            return;
        }

        int sourceIndex = cityCodeIndexMap[sourceCode];
        int destinationIndex = cityCodeIndexMap[destinationCode];

        std::vector<int> distance(cities.size(), std::numeric_limits<int>::max());
        distance[sourceIndex] = 0;

        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
        pq.push({0, sourceIndex});

        std::vector<int> parent(cities.size(), -1); // Parent array to reconstruct the path

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (const Road& road : roads) {
                if (road.sourceCode == cities[u].code) {
                    int v = cityCodeIndexMap[road.destinationCode];
                    int w = road.distance;

                    if (distance[u] + w < distance[v]) {
                        distance[v] = distance[u] + w;
                        parent[v] = u; // Track the parent to reconstruct the path
                        pq.push({distance[v], v});
                    }
                }
            }
        }

        if (distance[destinationIndex] == std::numeric_limits<int>::max()) {
            std::cout << "No path found from " << sourceCode << " to " << destinationCode << std::endl;
        } else {
            std::cout << "The shortest distance from " << cities[sourceIndex].name << " to " << cities[destinationIndex].name
                    << " is " << distance[destinationIndex] << std::endl;

            std::cout << "Through the route: ";
            std::vector<std::string> route;

            int current = destinationIndex;
            while (current != -1) {
                route.push_back(cities[current].name);
                current = parent[current];
            }

            for (auto it = route.rbegin(); it != route.rend(); ++it) {
                std::cout << *it;
                if (it + 1 != route.rend()) {
                    std::cout << "->";
                }
            }

            std::cout << std::endl;
        }
    }

    const std::vector<City>& CityMap::getCities() const {
        return cities;
    }

} // namespace std

int main() {
  cout << "Author: Jonathan Pak, Andre Duran, Max Gulart" << endl;\
  cout << "Date: 12/4/2023" << endl;
  cout << "CS 311 (Data Structures and Algorithms)" << endl;
  cout << "Description : Program to find the shortest route between cities" << endl;
  cout << endl; 
    std::CityMap cityMap;
    cityMap.loadCities("city.txt");
    cityMap.loadRoads("road.txt");

    int sourceIndex, destinationIndex;
    std::cout << "Enter source city index: ";
    std::cin >> sourceIndex;
    std::cout << "Enter destination city index: ";
    std::cin >> destinationIndex;

    cityMap.findShortestPath(cityMap.getCities()[sourceIndex].code, cityMap.getCities()[destinationIndex].code);

    return 0;
}