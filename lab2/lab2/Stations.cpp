#include "Stations.h"
#include <cstring>
#include <cstdlib>
using namespace w2;
using namespace std;

Stations::Stations(char* fileName)
{
   file = fileName;
   cout << "Stations(" << fileName << ")" << endl;
   fstream is(file, ios::in);

   if (is.is_open())
   {
      is >> stationAmount;
      char c;
      is >> c;
      if (c != ';')
      {
         cerr << "File '" << file << "' expected a ';' but found a '" << c << "'. Can not continue." << endl;
         exit(2);
      }
      stationTable = new Station[stationAmount];
      for (int i = 0; i < stationAmount; i++){
         stationTable[i] = Station(is);
      }
      is.close();
   }
   else
   {
      cerr << "Cannot open file '" << file << "'\n" << endl;
      exit(1);
   }
}

Stations::~Stations()
{
   ofstream os(file);
   os.open(file, ios::trunc);
   if (os.is_open())
   {
      os << stationAmount << ';' << endl;
      for (int i = 0; i < stationAmount; i++) 
      {
         stationTable[i].write(os);
      }
      os.close();
   }
   else
   {
      cerr << "Cannot open file '" << file << "'\n" << endl;
      exit(3);
   }
   delete[] stationTable;
}

void Stations::update()
{
   cout << endl;
   cout << "Passes Sold  :" << endl;
   cout << "--------------";
   for (int i = 0; i < stationAmount; i++) {
      stationTable[i].update();
   }
   cout << endl;
}

void Stations::restock()
{
   cout << "Passes Added :" << endl;
   cout << "--------------";
   for (int i = 0; i < stationAmount; i++) {
      stationTable[i].restock();
   }
   cout << endl;
}

void Stations::report()
{
   cout << "Passes in Stock : Student Adult" << endl;
   cout << "-------------------------------" ;
   for (int i = 0; i < stationAmount; i++) {
      stationTable[i].report();
   }
}

