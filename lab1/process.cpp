#include "process.h"
#include "CString.h"
#include <iostream>
using namespace std;
namespace w1 {
   void process(char * c)
   {
      CString CStr(c);
      cout << CStr;
      cout << "\n";
   }
}

