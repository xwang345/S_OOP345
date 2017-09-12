#pragma once

#include <fstream>
#include <iostream>
#include <string>

namespace w3 {

   class Text{
      size_t count;
      std::string* lineTable;

   public:
      size_t size();

      void dump();

      ~Text();

      Text();

      Text(char* f);

      Text(const Text& rhs);

      Text(Text&& rhs);

      Text& operator= (const Text& rhs);

      Text&& operator= (Text&& rhs);
   };
};