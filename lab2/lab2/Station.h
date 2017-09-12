#pragma once
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

namespace w2 {

   enum PassType {
      STUDENT_PASS, 
      ADULT_PASS, 
      PASS_COUNT
   };

   class Station {
      std::string stationName;
      int passes[PASS_COUNT];

   public:
      Station();
      Station(istream& is);
      void update();
      void restock();
      void report();
      void write(ostream& os);
   };

}
