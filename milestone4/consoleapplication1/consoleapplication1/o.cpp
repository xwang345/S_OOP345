#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

#include "util.h"
#include "o.h"

Order::Order(std::vector<std::string> &row) {
	if (row.size() < 3) {
		throw std::string("Expected 3 or more fields, found ") + std::to_string(row.size());
	}
	if (validCustomerName(row[0])) {
		orderCustomer = row[0];
	}
	else {
		throw std::string("Expected a customer name --- found '") + row[0] + "'";
	}

	if (validProductName(row[1])) {
		orderProduct = row[1];
	}
	else {
		throw std::string("Expected a customer name --- found '") + row[1] + "'";
	}

	for (auto i = 2; i < row.size(); i++) {
		if (validItemName(row[i]))
			itemList.push_back(row[i]);
		else
			throw std::string("Expected a customer name --- found '") + row[i] + "'";
	}
}

void Order::print() {
	std::cout << " /Customer/Product/Items .../ = "
		<< "/" << orderCustomer
		<< "/" << orderProduct
		;

	for (auto item : itemList)
		std::cout << "/" << item;
	std::cout << "\n";
}

void Order::graph(std::fstream& os) {
	std::string q = "\"";
	for (auto item : itemList)
		os << q << orderCustomer + ":" + orderProduct << q << " -> " << q << item << q << "[color=blue];\n";
}

OrderManager::OrderManager( std::vector< std::vector<std::string> > &csvData) {
	for (auto& row : csvData) {
		try {
      if (row.size() > 2)
			orderList.push_back( std::move(Order(row)) );
		}
		catch (const std::string& e) {
			std::cerr << e << "\n";
		}
	}
}

void OrderManager::print() {
	for (auto e : orderList)
		e.print();
}

void OrderManager::graph(std::string& filename) {
	std::string f = filename + ".gv";
	std::fstream os(f, std::ios::out | std::ios::trunc);
	os << "digraph orderGraph {\n";
	
	for (auto t : orderList) {
		t.graph(os);
	}

	os << "}\n";

	os.close();

	std::string cmd = std::string("dot -Tpng ") + filename + ".gv > " + filename + ".gv.png";

	std::cout << cmd << " returned " << system(cmd.c_str()) << "\n";
}
