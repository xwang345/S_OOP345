#include "Notifications.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace w5;

Notifications::Notifications()
   : messageTable(nullptr), messageCount(0) {
}

Notifications::Notifications(const Notifications& rhs)  // copy constructor
   : messageTable(nullptr), messageCount(0) {
   messageCount = rhs.messageCount;
   if (rhs.messageTable) {
      // deep copy
      for (int i = 0; i < messageCount; i++)
         messageTable[i] = rhs.messageTable[i];
   }
}

Notifications& Notifications::operator=(const Notifications& rhs) { // copy assignment
   if (this != &rhs)
      delete[] messageTable;

   if (rhs.messageTable) {
      //deep copy
      for (int i = 0; i < messageCount; i++)
         messageTable[i] = rhs.messageTable[i];
   }

   return *this;
}

Notifications::Notifications(Notifications&& rhs)
   : messageTable(nullptr), messageCount(0) { // move constructor
   rhs.messageTable = nullptr; // make rhs a 'zombie'
   rhs.messageTable = 0;
}

Notifications&& Notifications::operator=(Notifications&& rhs) { // move assignment
   if (this != &rhs) {
      delete[] messageTable; // delete our 'braisn' (if we have any)

                             // steal 'brains'
      messageTable = rhs.messageTable;
      messageCount = rhs.messageCount;

      //make rhs a 'zombie'
      rhs.messageTable = nullptr;
      rhs.messageCount = 0;
   }
   return std::move(*this);
}

Notifications::~Notifications() {
   delete[] messageTable;
}

void Notifications::operator+=(const Message& msg) { // adds msg to the set
   if (messageTable == nullptr)
      messageTable = new Message[MAX_SIZE];
   if (messageCount < MAX_SIZE) {
      messageTable[messageCount] = msg;
      messageCount++;
   }
}

void Notifications::display(std::ostream& os) const { // insert the Message objects to the os output stream
   for (int i = 0; i < messageCount; i++)
      messageTable[i].display(os);
}

