#pragma once
#include <iostream>

namespace w5 {
   class Message{
      std::string name, reply, tweet;
      
   public:
      Message();
      Message(std::ifstream& in, char c);
      bool empty() const;
      void display(std::ostream& os) const;
   };
}