#pragma once
#include "Station.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>	
using namespace std;

namespace w2
{
   class Stations
   {
      int stationAmount;
      Station* stationTable;
      char* file;
   public:
      Stations(char* fileName);
      ~Stations();
      void update();
      void restock();
      void report();
   };
}