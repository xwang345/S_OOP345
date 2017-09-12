#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "t.h"
#include "util.h"

Task::Task(std::vector<std::string>& row) :taskSlots("1") {
	switch (row.size()) {
	case 4:
		if (validTaskName(row[3]))
			taskFail = row[3];
		else
         throw std::string("Expected a fail task name --- found '") + row[3] + "'";
	case 3:
		if (validTaskName(row[2]))
			taskPass = row[2];
		else
         throw std::string("Expected a pass task name --- found '") + row[2] + "'";
	case 2:
		if (validSlots(row[1]))
			taskSlots = row[1];
		else
         throw std::string("Expected a slots --- found '") + row[1] + "'";
	case 1:
		if (validTaskName(row[0]))
			taskName = row[0];
		else
         throw std::string("Expected a pass task name --- found '") + row[0] + "'";
		break;
	default:
			throw std::string("Ecxpected 1,2,3, or 4 feilds, found ") + std::to_string(row.size());
	}
}
void Task::print()
{
	std::cout << " /Name/Slots/Pass/Fail/ = "
		<< "/" << taskName
		<< "/" << taskSlots
		<< "/" << taskPass
		<< "/" << taskFail
		<< "/" << std::endl;
}
void Task::graph(std::fstream& os)
{
	std::string q = "\"";
	if(!(taskPass.empty()))
		os << q << taskName << q << " -> " << q << taskPass << q << " [color=green];\n";
	if(!(taskFail.empty()))
		os << q << taskName << q << " -> " << q << taskFail << q << " [color=red];\n";
   if (taskPass.empty() && taskFail.empty())
      os << q << taskName << q << ";\n";
}
TaskManager::TaskManager(std::vector<std::vector<std::string>>& csvData)
{
	for (auto& row : csvData) {
		try {
			taskList.push_back(std::move(Task(row)));
		}
		catch (const std::string& e) {
			std::cerr << e << std::endl;
		}
	}
}
void TaskManager::print() {
	for (auto t : taskList)
		t.print();
}
void TaskManager::graph(std::string& filename)
{
	std::string f = filename + ".gv";
	std::fstream os(f, std::ios::out | std::ios::trunc);
	os << "digraph taskGraph {\n";
	for (auto t : taskList)
	{
		t.graph(os);
	}
	os << "}" << std::endl;
	os.close();
	
	std::string cmd = std::string("dot -Tpng ") + filename + ".gv > " + filename + ".gv.png";

	std::cout << cmd << " returned " << system(cmd.c_str()) << "\n";
}
