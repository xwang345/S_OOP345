#include <iostream>
#include <iomanip>
#include <utility>
#include "Text.h"

using namespace w3;

size_t Text::size() { return count; }

void Text::dump() {
   size_t number = count;
   if (number > 10) number = 10;
   for (size_t i = 0; i < number; i++) {
      std::cout << "   line " << i + 1 << "--->" << lineTable[i] << "<--\n";
   }
}

Text::~Text() {
   delete[] lineTable;
}

Text::Text()
   : count(0), lineTable(nullptr) {}

Text::Text(char* f)
   : count(0) {
   std::fstream in(f, std::ios::in);
   if (in.is_open()) {
      std::string line;
      while (getline(in, line)) {
         count++;
      }
      std::cout << "file '" << f << "' contains " << count << " lines\n";

      lineTable = new std::string[count];

      std::cout << in.good() << "<-- good: true if none of the flags is set\n";
      std::cout << in.fail() << "<-- fail: true if ios::failbit or ios::badbit is true\n";
      std::cout << in.eof() << "<-- eof: true if ios::eofbit is true\n";
      std::cout << in.bad() << "<-- bad: true if ios::badit is true\n";

      std::cout << "clearing all status flags\n";
      in.clear();

      std::cout << in.good() << "<-- good: true if none of the flags is set\n";
      std::cout << in.fail() << "<-- fail: true if ios::failbit or ios::badbit is true\n";
      std::cout << in.eof() << "<-- eof: true if ios::eofbit is true\n";
      std::cout << in.bad() << "<-- bad: true if ios::badit is true\n";

      in.seekp(0);

      for (size_t i = 0; i < count; i++) {
         getline(in, lineTable[i]);
         auto cr = lineTable[i].find('\r');
         if (cr != std::string::npos)
            lineTable[i].erase(cr);
      }

      in.close();

      dump();
   }
   else {
      std::cerr << "Cannot open file '" << f << "'\n";
      exit(3);
   }
}

Text::Text(const Text& rhs)
   :count(0), lineTable(nullptr) {
   *this = rhs;
}

Text::Text(Text&& rhs)
   : count(0), lineTable(nullptr) {
   *this = std::move(rhs);
}

Text& Text::operator= (const Text& rhs) {
   if (this != &rhs) {
      delete[] lineTable;
      lineTable = nullptr;
      count = 0;

      count = rhs.count;

      lineTable = new std::string[count];
      for (size_t i = 0; i < count; i++)
         lineTable[i] = rhs.lineTable[i];
   }
   return *this;
}

Text&& Text::operator= (Text&& rhs) {
   if (this != &rhs) {
      delete[] lineTable;

      lineTable = rhs.lineTable;
      count = rhs.count;

      rhs.lineTable = nullptr;
      rhs.count = 0;
   }
   return std::move(*this);
}


