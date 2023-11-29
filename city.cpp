#include "city.h"
#include <iostream> 

using namespace std; 

void collect_one_city(ifstream &fin, City& a){
  char comma; // To store and discard the comma
  fin >> a.id;
  fin >> comma; // Discard the comma after id
  getline(fin, a.code, ',');
  getline(fin, a.name, ',');
  fin >> a.population;
  fin >> comma; // Discard the comma after population
  fin >> a.elevation;
}
void collect_one_road(ifstream &fin, Road& a){
  fin >> a.from;
  fin >> comma;
  fin >> a.to;
  fin >> comma;
  fin >> a.weight;
  fin >> comma;
}

void collect_all_cities(City arr[], unsigned & i){
  ifstream input("city.txt");
  while(!input.eof()){
    collect_one_city(input, arr[d]);
    d++;
  }
}
void collect_all_roads(Road arr[], unsigned&i){
    ifstream input("road.txt");
  while(!input.eof()){
    collect_one_city(input, arr[d]);
    d++;
  }
}
