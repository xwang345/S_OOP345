#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "util.h"
#include "i.h"

class Order {
	std::string orderCustomer, orderProduct;
	std::vector <std::string> itemList;
public:
	Order(std::vector<std::string> &row);
	void print();
	void graph(std::fstream& os);

	std::string& getCustomer()		{ return orderCustomer; }
	std::string& getProduct()		{ return orderProduct; }
	size_t       getSize()			{ return itemList.size(); }
	std::string& getItem(size_t i)	{ return itemList[i]; }
}; // end Order

class OrderManager {
	std::vector< Order > orderList;
public:
	OrderManager(std::vector< std::vector<std::string> > &csvData);
	void print();
	void graph(std::string& fileName);
	bool validate(ItemManager& im)
	{
		int errors = 0;
		for (auto order : orderList) {
			for (size_t i = 0; i < order.getSize(); i++) {
				if (im.find(order.getItem(i)) == nullptr) {
					errors++;
					std::cerr << "Customer " << order.getCustomer() << " ordered product " << order.getProduct()
						<< " references unknown item " << order.getItem(i) << "\n";
				}
			}
		}
		return errors == 0;
	}
}; // end OrderManager