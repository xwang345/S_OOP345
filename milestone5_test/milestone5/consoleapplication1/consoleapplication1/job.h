#pragma once

#include "o.h"

class Job : public Order {
  vector<bool> installed;
public:
  Job() {}
  Job(Order *o) : Order(*o) {
    installed.resize( getItemSize() ); // allocate space

    for(size_t i = 0; i < getItemSize(); i++)
      installed[i] = false;        // initailize to false (not installed)
  }
  bool Installed(size_t i) { return installed[i]; } 
  void Installed(size_t i,bool value) { installed[i] = value; } 
};
