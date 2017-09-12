#include "Message.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace w5;      

Message::Message() {
}

Message::Message(std::ifstream& in, char c) {
   // constructor retrieves a record from the in file object, 
   // parses the record ( asdescribed above) a? ts components in the Message object.
   // c is the character that delimits each record
   std::string line;
   getline(in, line, c);
   auto cr = line.find('\r');
   if (cr != std::string::npos)
      line.erase(cr);
   //std::cout << "line-->" << line << "<--\n";

   size_t index = 0;

   while (index < line.size()) {
      if (line[index] == ' ') break;
      name += line[index];
      index++;
   }
   //std::cout << "name = '" << name << "'\n";

   index++;

   if (index < line.size() && line[index] == '@') {
      index++;
      while (index < line.size()) {
         if (line[index] == ' ') break;
         reply += line[index];
         index++;
      }
      //std::cout << "reply = '" << reply << "'\n";
      index++;
   }
   while (index < line.size()) {
      tweet += line[index];
      index++;
   }
   //std::cout << "tweet = '" << tweet << "'\n";
}

bool Message::empty() const {
   return tweet.empty();
}

void Message::display(std::ostream& os) const {
   os << "Message\n";
   os << "User   :" << name << "\n";
   if (reply == "") {
      os << "Reply  :" << reply << "\n";
   }
   os << "Tweet  :" << tweet << "\n";
   os << "\n";
}