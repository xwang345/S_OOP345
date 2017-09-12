#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::string& trim(std::string& s, char trimChar = ' ');

void csvReader(std::string& filename, char delim, std::vector< std::vector<std::string> > &csv);

void csvPrint(std::vector< std::vector< std::string >> &csvData);

bool validTaskName(std::string &s);

bool validSlots(std::string &s);
