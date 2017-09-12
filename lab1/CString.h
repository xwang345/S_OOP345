#pragma once
#include <iostream>

namespace w1 {                  
   const int MAX = 3;

   class CString {
      char str[MAX + 1];
   public:
      CString(char* c);
      void display(std::ostream& os) const;
   };

   std::ostream& operator<< (std::ostream& os, const CString& c);
}