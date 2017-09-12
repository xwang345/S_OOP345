#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include "util.h"
#include "t.h"
class Item {
  std::string itemName, itemInstaller, itemRemover, itemSequence, itemDescription;
public:
  Item(std::vector<std::string> &row);
  void print();
  void graph(std::fstream& os);

  std::string& getName() { return itemName; }
  std::string& getInstaller() { return itemInstaller; }
  std::string& getRemover() { return itemRemover; }
  std::string& getSequence() { return itemSequence; }
};

class ItemManager {
  std::vector<Item> itemList;
public:
  ItemManager(std::vector<std::vector<std::string>> &csvData);
  void print();
  void graph(std::string& filename);

  Item* find(std::string& name)
  {
    for (size_t i = 0; i < itemList.size(); i++)
    {
      if (name == itemList[i].getName())
        return &itemList[i];
    }
    return nullptr;
  }

  bool validate(TaskManager& tm)
  {
    int errors = 0;
    for (auto item : itemList) {
      if (tm.find(item.getInstaller()) == nullptr) {
        errors++;
        std::cerr << "Item: " << item.getName() << " references unknown installer task " << item.getInstaller() << "\n";
      }
      if (tm.find(item.getRemover()) == nullptr) {
        errors++;
        std::cerr << "Item " << item.getName() << " references unknown remover task " << item.getRemover() << "\n";
      }
    }
    return errors == 0;
  }

  size_t getSize() { return itemList.size(); }

  Item*  getItem(size_t i) { return &itemList[i]; }
};
