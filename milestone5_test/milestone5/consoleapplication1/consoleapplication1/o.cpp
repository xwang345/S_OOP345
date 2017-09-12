#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "util.h"
#include "o.h"

  Order::Order( std::vector<std::string> &row )
  {
    // for(auto e : row) 
      // std::cout << "~" << e << "~ ";
    // std::cout << "\n";

    if( row.size()  < 3)
      throw std::string("Expected at least three fields for an order: customer, product, and at least one item -  found ") + std::to_string( row.size() );

    orderCustomer = row[0];
    orderProduct  = row[1];

    for(size_t field = 2; field < row.size(); field++)
      if(validItemName( row[field] ) )
        orderItems.push_back( row[field] );
      else
        throw std::string("Expected valid item name - found '") + row[field] + "'";
  }

 void Order::print()
 {
   std::cout << "order: /customer/product/ items ... /"
        << orderCustomer << "/"
        << orderProduct << "/";
   for(auto i : orderItems)
        std::cout << i << "/";
   std::cout << "\n";
 }

 void Order::graph(std::fstream &os)
 {
   std::string q("\"");

   for(auto item : orderItems) {
     os << q + orderCustomer + "/" + orderProduct + q + " -> " + q + item + q + "[color=blue];\n";
   }
 }

 OrderManager::OrderManager() {}
 OrderManager::OrderManager( std::vector< std::vector<std::string> > &csvData )
 {
   for(auto row : csvData) {
     try {
       orders.push_back( std::move(Order(row)) );
     } catch (const std::string& e) {
       std::cerr << "OrderManager: problem " << e << "\n";
     }
   }
 }

 void OrderManager::print()
 {
   for(auto t : orders)
     t.print();
 }

 void OrderManager::graph(std::string& orderFilename)
 {
   std::string dotFile = orderFilename + ".gv";
   std::fstream os(dotFile, std::ios::out | std::ios::trunc); // NOTE single | not ||

   os << "digraph orderGraph {\n";
   for(auto t : orders)
     t.graph( os );
   os << "}\n";
   os.close();

  #ifdef __unix
    std::string dot = "dot";
  #else  // Microsoft
    // assumes GraphViz 2.38 is installed in the default location
    std::string dot = "C:/\"Program Files (x86)\"/Graphviz2.38/bin/dot.exe";
  #endif
    std::string cmd = dot + " -Tpng " + orderFilename + ".gv > " + orderFilename + ".gv.png";
    std::cout << cmd << " returned " << system(cmd.c_str()) << "\n";;
 }

 bool OrderManager::validate(ItemManager& im)
 {
   int errors = 0;
   for(auto o : orders) {
     for(size_t i = 0; i < o.getItemSize(); i++) {
         if(im.find(o.getItemNumber(i)) == nullptr) {
           std::cerr << o.getCustomer() << ":" << o.getProduct() 
                     << " CANNOT FIND ITEM '" << o.getItemNumber(i) << "'\n";
           errors++;
         }
     }
   }

   return errors == 0;
 }
