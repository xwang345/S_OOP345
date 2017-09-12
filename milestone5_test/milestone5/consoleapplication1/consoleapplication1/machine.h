#pragma once

#include <queue>

#include "t.h"
#include "job.h"

class Machine : public Task {
  int inComing;
  std::queue< Job > inputQ;

  bool bInstaller;
  bool bRemover;

public:
  Machine()
    : inComing(0)
  {
  }
  Machine (Task* t) 
    : Task(*t) 
    , inComing(0)
  {
  }
  void IncInComing()
  {
    inComing++;
  }
  bool isSource()    const { return inComing == 0; }
  bool isSink()            { return getPass().empty();  }  // compiler error if const
  bool isSingleton()       { return isSource() && isSink(); }  // compiler error if const

  void AddJob( Job job ) { inputQ.push( move ( job ) ); }

  size_t inputQSize() const { return inputQ.size(); }

  Job getJob() {
    //  cout << "getJob: " << inputQSize() << "\n";
    Job job = move( inputQ.front() );
    inputQ.pop();
    //  cout << "getJob after pop: " << inputQSize() << "\n";
    return job;
  }

  void Classify(ItemManager& im) {
    bInstaller = false;
    bRemover   = false;

    for(size_t i = 0; i < im.getSize(); i++ ) {
      if(getName() == im.getItem(i) -> getInstaller() )
        bInstaller = true;
      if(getName() == im.getItem(i)-> getRemover() )
        bRemover = true;
    }

    if(bInstaller) cout << getName() << " is an installer\n";
    if(bRemover)   cout << getName() << " is a remover\n";
    if(bInstaller && bRemover)
      throw getName() + " is BOTH an and a remover";
    
  }
  bool getInstaller() const { return bInstaller; }
  bool getRemover  () const { return bRemover; }
};
