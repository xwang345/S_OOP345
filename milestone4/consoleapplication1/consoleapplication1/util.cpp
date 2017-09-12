#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "util.h"
std::string& trim(std::string& s, char trimChar)
{
  while (!s.empty() && s[0] == trimChar)
    s.erase(0, 1);

  while (!s.empty() && s[s.size() - 1] == trimChar)
    s.erase(s.size() - 1, 1);

  return s;
}

#define PROCESS_DOUBLE_QUOTES
void csvReader(std::string& filename, char delim, std::vector< std::vector<std::string> > &csv)
{
  std::ifstream is(filename);
  if (is) {
    std::string line;
    std::vector<std::string> fields;

    while (getline(is, line)) {
      auto cr = line.find('\r');
      if (cr != std::string::npos)
        line.erase(cr, 1);

      std::string field;
      for (size_t i = 0; i < line.size(); i++) {
#ifdef PROCESS_DOUBLE_QUOTES
        if (line[i] == '"') {
          field += line[i];        // copy 1st "
          for (i++; i < line.size(); i++) {
            field += line[i];
            if (line[i] == '"')     // found 2nd "
              break;
          }
        }
        else
#endif
          if (line[i] != delim) {
            field += line[i];
          }
          else {
            trim(field);
            if (!field.empty())
              fields.push_back(move(field));
            // field.clear(); // not needed if we do a move
          }
      }
      trim(field);
      if (!field.empty())
        fields.push_back(field);
      if (!fields.empty())
        csv.push_back(move(fields));
      // field.clear(); // not needed if we do a move
    }
    is.close();
  }
  else {
    std::cerr << "cannot open file " << filename << "\n";
  }
}

void csvPrint(std::vector< std::vector<std::string> > &csv)
{
  // Method 1 - range-based for loop: 
  for (auto row : csv) {
    for (auto column : row) {
      std::cout << column << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";

  // Method 2 - conventional for loop
  for (size_t row = 0; row < csv.size(); row++) {
    for (size_t column = 0; column < csv[row].size(); column++) {
      std::cout << csv[row][column] << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";

  // Method 3 - iterator for loop
  for (auto row = csv.begin(); row < csv.end(); row++) {
    for (auto column = row->begin(); column < row->end(); column++) {
      std::cout << *column << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}
bool validTaskName(std::string &s) {
	for (auto c : s)
		if (!(isalnum(c) || c == ' '))
			return false;
	return true;
}

bool validSlots(std::string &s) {
	for (auto c : s)
		if (!(isdigit(c)))
			return false;
	return true;
}
bool validCustomerName(std::string &s) {
	for (auto c : s)
		if (!(isalnum(c) || c == ' '))
			return false;
	return true;
}
bool validProductName(std::string &s) {
	for (auto c : s)
		if (!(isalnum(c) || c == ' '))
			return false;
	return true;
}
bool validItemName(std::string &s) {
	for (auto c : s)
		if (!(isalnum(c) || c == ' '))
			return false;
	return true;
}
bool validItemSequence(std::string &s) {
	for (auto c : s)
		if (!(isalnum(c) || c == ' '))
			return false;
	return true;
}