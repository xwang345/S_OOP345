//Sale.cpp
#include <iomanip>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;
#include "Sale.h"

namespace w7{
	Sale::Sale(const char* file){
		ifstream fs(file);
		if(fs.is_open()){			
			iProduct* iP;
			while((iP = readProduct(fs)))
				products.push_back(iP);
			fs.close();
		}
	}
	
	Sale::~Sale(){
      int i;
		for(i = 0;i < products.size();i++)
			delete [] products[i];
	}

	void Sale::display(std::ostream& os) const{
		double sumcost = 0.0;
      cout << "Product No      Cost Taxable" << endl;
		for(int i = 0;i < products.size();i++){
			os << *products[i] << endl;
			sumcost += products[i]->getCharge();
		}
		cout << setw(10) << "Total" << fixed;
		cout << setw(10) << setprecision(2) << sumcost << endl;
	}
}
