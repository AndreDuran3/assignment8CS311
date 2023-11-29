#include "city.h"
#include <iomanip>
#include <iostream> 
using namespace std;

int main(){
  cout << "Author: Andre Duran, Max Gulart, Jonathan Pak" << endl; 
  cout << "Date: 11/28/2023" << endl; 
  cout << "Course: CS311 (Data structures and Algorithms)" << endl; 
  cout << "Description : Program to find the shortest route between cities" << endl;
  cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
  City cities[];
  Road roads[];
  City a; 
  int counter = 0;
  collect_all_cities(cities, counter);
  counter = 0; 
  collect_all_roads(roads, counter);
  cout << "program is finished" << endl;
}