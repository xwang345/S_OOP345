#include "process.h"
#include "CString.h"
#include <string>
#include <iostream>
using namespace std;

using namespace w1;
   int main(int argc, char* argv[]) {
      int i = 0;

      cout << "Command Line : ";
      for (i = 0; i < argc; i++) {
         cout << " " << argv[i];
      }
      cout << "\n";

      if (argc == 1) {
         cout << "Insufficient number of arguments (min 1)" << "\n";
         return 1;   //false
      }
      else {
         cout << "Maximum number of characters stored : 3" << "\n";
         for (i = 0; i < argc; i++) {
            process(argv[i]);
         }
         return 0;   //true
      }
   }
