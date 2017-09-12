#include <iostream>
#include <fstream>
#include <vector> 
#include <string>
#include "util.h"

using namespace std;


class Order {
  string orderCustomer, orderProduct;
  vector<string> itemList;
public:
  Order( vector<string> row)
  {
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
  void print()
  {
     std::cout << " /Customer/Product/Items .../ = "
        << "/" << orderCustomer
        << "/" << orderProduct
        ;

     for (auto item : itemList)
        std::cout << "/" << item;
     std::cout << "\n";
  }
  void graph( fstream& os )
  {
     std::string q = "\"";
     for (auto item : itemList)
        os << q << orderCustomer + ":" + orderProduct << q << " -> " << q << item << q << "[color=blue];\n";
  }
};

class OrderManager {
  vector< Order > orderList;
public:
  OrderManager( vector < vector< string > > & csvData)
  {
     for (auto& row : csvData) {
        try {
           if (row.size() > 2)
              orderList.push_back(std::move(Order(row)));
        }
        catch (const std::string& e) {
           std::cerr << e << "\n";
        }
     }
  }
  void print()
  {
     for (auto e : orderList)
        e.print();
  }
  void graph(string& filename)
  {
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

};

int main(int argc, char*argv[])
{
  try {
    if(argc != 3) {
      throw string("Usage ") + argv[0] + string(": filename delimiter-char");
    }

    string filename  = string(argv[1]);     // 1st arg is filename
    char   delimiter = argv[2][0];  // 2nd arg, 1st char is delimiter

    vector < vector< string > > csvOrderData;
    csvReader(filename, delimiter, csvOrderData);

    // csvPrint(csvOrderData);

    OrderManager om(csvOrderData);
    om.print();
    om.graph(filename);

  } catch (const string& e) {
    cerr << e << "\n";
  }
}
