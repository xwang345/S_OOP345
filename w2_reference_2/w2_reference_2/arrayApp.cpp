// Move Constructor and Assignment Operator
// moveApp.cpp

#include <iostream>
#include "array.h"

int main() {
   const int size = 5;
   Array x(size), z;

   for (int i = 0; i < size; i++)
      x[i] = i;
   z = std::move(x);
   for (int i = size - 1; i >= 1; i--)
      std::cout << z[i] << ',';
   std::cout << z[0] << std::endl;
}