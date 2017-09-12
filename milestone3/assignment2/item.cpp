#include <iostream>
#include <fstream>
#include <vector> 
#include <string>
#include "util.h"

using namespace std;


class Item {
  string itemName, itemInstaller, itemRemover, itemSequence, itemDescription;
public:
  Item( vector<string> row)
  {
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
  void print()
  {
     std::cout << "/Name/Installer/Remover/Sequence/Description/ = "
        << "/" << itemName
        << "/" << itemInstaller
        << "/" << itemRemover
        << "/" << itemSequence
        << "/" << itemDescription
        << "\n";
  }
  void graph( fstream& os )
  {
     std::string q = "\"";
     os << q << "Item: " + itemName << q << " -> " << q << "Installer: " << itemInstaller << q << " [color=green];\n";
     os << q << "Item: " + itemName << q << " -> " << q << "Remover: " << itemInstaller << q << " [color=red];\n";
  }
};

class ItemManager {
  vector< Item > itemList;
public:
  ItemManager( vector < vector< string > > & csvData)
  {
     for (auto& row : csvData) {
        try {
           itemList.push_back(std::move(Item(row)));
        }
        catch (const std::string& e) {
           std::cerr << e << "\n";
        }
     }
  }
  void print()
  {
     for (auto e : itemList)
        e.print();
  }
  void graph(string& filename)
  {
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

};

int main(int argc, char*argv[])
{
  try {
    if(argc != 3) {
      throw string("Usage ") + argv[0] + string(": filename delimiter-char");
    }

    string filename  = string(argv[1]);     // 1st arg is filename
    char   delimiter = argv[2][0];          // 2nd arg, 1st char is delimiter

    vector < vector< string > > csvItemData;
    csvReader(filename, delimiter, csvItemData);

    // csvPrint(csvItemData);

    ItemManager im(csvItemData);
    im.print();
    im.graph(filename);

  } catch (const string& e) {
    cerr << e << "\n";
  }

  //try {
  //   if (argc != 5)
  //      throw string("Usage : ") + argv[0] + " item-csv order-csv task-csv csv-seperator";
  //   string fileItemName = argv[1];
  //   string fileOrderName = argv[2];
  //   string fileTaskName = argv[3];
  //   char seperator = argv[4][0];
  //   vector<vector<string>> csvItemData;
  //   //vector<vector<string>> csvOrderData;
  //   //vector<vector<string>> csvTaskData;
  //   csvReader(fileItemName, seperator, csvItemData);
  //   //csvReader(fileOrderName, seperator, csvOrderData);
  //   //csvReader(fileTaskName, seperator, csvTaskData);
  //   ItemManager im(csvItemData);
  //   im.Print();
  //   im.Graph(fileItemName);
  //}
  //catch (const std::string& e) {
  //   std::cerr << e << "\n";
  //}

}
