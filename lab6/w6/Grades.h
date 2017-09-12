// Grades.h
#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Grades
{
   string* students_;
   double* grades_;
   int count_;

public:
   Grades()
      : students_(nullptr), grades_(nullptr), count_(0) {}

   Grades(char* file) {
      try {
         ifstream fs(file);
         if (fs.is_open()) {
            int line = 0;
            string s;
            while (getline(fs, s))
               line++;
            fs.clear();
            fs.seekg(0);
            count_ = line;
            students_ = new string[count_];
            grades_ = new double[count_];
            for (int i = 0; i < count_; i++) {
               fs >> students_[i];
               fs >> grades_[i];
            }
            fs.close();
         }
         else throw "Failed to open file.";
      }
      catch (const char* msg) {
         cerr << msg << endl;
         exit(0);
      }
   }

   template<typename T>
   void displayGrades(std::ostream& os, T t) const {
      for (int i = 0; i < count_; i++)
         os << students_[i] << " " << grades_[i] << " " << t(grades_[i]) << endl;
   }

   Grades(const Grades& g) = delete;
   Grades(Grades&& g) = delete;
   Grades& operator=(const Grades& g) = delete;
   Grades&& operator=(Grades&& g) = delete;
};
