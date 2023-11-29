#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct City{
    int id;
    string code;
    string name;
    int population;
    int elevation;
}

struct Road{
    int from;
    int to; 
    int weight;
}

void collect_one_city(ifstream &fin, City& a);
void collect_one_road(ifstream &fin, Road& a);
void collect_all_cities(City arr[], unsigned & i);
void collect_all_roads(Road arr[], unsigned&i);