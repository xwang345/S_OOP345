#pragma once
#include "Message.h"

namespace w5 {
   const int MAX_SIZE = 10;
   class Notifications {
      Message* messageTable;
      int      messageCount;
   public:
      Notifications();
      Notifications(const Notifications& rhs);
      Notifications& operator=(const Notifications& rhs);
      Notifications(Notifications&& rhs);
      Notifications&& operator=(Notifications&& rhs);
      ~Notifications();
      void operator+=(const Message& msg);
      void display(std::ostream& os) const;
   };
}