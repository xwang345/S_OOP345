#include <string>
#include "util.h"
#include "i.h"
#include "o.h"
#include "t.h"
using namespace std;
int main(int argc, char* argv[]) {
	try {
		if (argc != 5)
			throw string("Usage : ") + argv[0] + "item-csv order-csv task-csv csv-seperator";
		string fileItemName = argv[1];
		string fileOrderName = argv[2];
		string fileTaskName = argv[3];
		char seperator = argv[4][0];
		vector<vector<string>> csvItemData;
		vector<vector<string>> csvOrderData;
		vector<vector<string>> csvTaskData;
		csvReader(fileItemName, seperator, csvItemData);
		csvReader(fileOrderName, seperator, csvOrderData);
		csvReader(fileTaskName, seperator, csvTaskData);
		//csvPrint(csvItemData);
		//csvPrint(csvOrderData);
		//csvPrint(csvTaskData);
		ItemManager im(csvItemData);
		OrderManager om(csvOrderData);
		TaskManager tm(csvTaskData);
		im.print();
		im.graph(fileItemName);
		om.print();
		om.graph(fileOrderName);
		tm.print();
		tm.graph(fileTaskName);
		if (im.validate(tm))
		{
			cout << "Item are consistent" << endl;
		}
		else
		{
			cerr << "Item are Not consistent" << endl;
		}
		if (om.validate(im))
		{
			cout << "All order item are consistent" << endl;
		}
		else
		{
			cerr << "NOT ALL items orderd are avilavle" << endl;
		}
		if (tm.validate())
		{
			cout << "Task are consistent" << endl;
		}
		else
		{
			cerr << "Task are Not consistent" << endl;
		}
	}
	catch (const string& msg)
	{
		cerr << msg << endl;
		exit(2);
	}
	return 0;
}