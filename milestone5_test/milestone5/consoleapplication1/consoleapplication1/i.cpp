#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>

#include "util.h"
#include "i.h"
#include "t.h"

Item::Item(std::vector<std::string> &row) {
	switch (row.size()) {
	case 5:
		itemDescription = row[4];
	case 4:
		if (validItemName(row[0]))
			itemName = row[0];
		else
			throw std::string("Expected a item name --- found '") + row[0] + "'";

		if (validTaskName(row[1]))
			itemInstaller = row[1];
		else
			throw std::string("Expected a installer task --- found '") + row[1] + "'";

		if (validTaskName(row[2]))
			itemRemover = row[2];
		else
			throw std::string("Expected a remover task --- found '") + row[2] + "'";

		if (validItemSequence(row[3]))
			itemSequence = row[3];
		else
			throw std::string("Expected a sequence number --- found '") + row[3] + "'";
		break;
	default:
		throw std::string("Expected 4 or 5 feilds, found '") + std::to_string(row.size());
	}
}
	
void Item::print() {
	std::cout << "/Name/Installer/Remover/Sequence/Description/ = "
		<< "/" << itemName
		<< "/" << itemInstaller
		<< "/" << itemRemover
		<< "/" << itemSequence
		<< "/" << itemDescription
		<< "\n";
}

void Item::graph(std::fstream& os) {
	std::string q = "\"";
	os << q << "Item: " + itemName << q << " -> " << q << "Installer: " << itemInstaller << q << " [color=green];\n";
	os << q << "Item: " + itemName << q << " -> " << q << "Remover: " << itemInstaller << q << " [color=red];\n";
}

ItemManager::ItemManager(std::vector<std::vector<std::string>> &csvData) {
	for (auto& row : csvData) {
		try {
			itemList.push_back(std::move(Item(row)));
		}
		catch (const std::string& e) {
			std::cerr << e << "\n";
		}
	}
}

void ItemManager::print() {
	for (auto e : itemList)
		e.print();
}

void ItemManager::graph(std::string& filename) {
	std::string f = filename + ".gv";
	std::fstream os(f, std::ios::out | std::ios::trunc);
	os << "digraph itemGraph {\n";

	for (auto t : itemList) {
		t.graph(os);
	}

	os << "}\n";

	os.close();

	std::string cmd = std::string("dot -Tpng ") + filename + ".gv > " + filename + ".gv.png";

	std::cout << cmd << " returned " << system(cmd.c_str()) << "\n";
}
