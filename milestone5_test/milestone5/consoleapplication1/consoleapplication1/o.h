#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "util.h"
#include "i.h"

class Order {
  std::string orderCustomer, orderProduct;
  std::vector<std::string> orderItems;
public:
   Order() {}
  Order( std::vector<std::string> &row );
 void print();
 void graph(std::fstream &os);
 std::string& getCustomer()            { return orderCustomer; }
 std::string& getProduct()             { return orderProduct; }
 size_t       getItemSize()            { return orderItems.size(); }
 std::string& getItemNumber(int index) { return orderItems[index]; }

};

class OrderManager {
  std::vector<Order> orders;
public:
 OrderManager();
 OrderManager( std::vector< std::vector<std::string> > &csvData );
 void print();
 void graph(std::string& orderFilename);
 bool validate(ItemManager& im);
 size_t getSize() { return orders.size(); }
 Order* getOrder(size_t o) { return &orders[o]; }
};
