#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "util.h"
class Task
{
   std::string taskName, taskSlots, taskPass, taskFail;
public:
   //Task();
   Task(std::vector<std::string>& row);
   std::string& getName() { return taskName; }
   std::string& getSlots() { return taskSlots; }
   std::string& getPass() { return taskPass; }
   std::string& getFail() { return taskFail; }
   void print();
   void graph(std::fstream& os);
};
class TaskManager
{
   std::vector<Task> taskList;
public:
   TaskManager(std::vector<std::vector<std::string>> &csvData);
   Task* find(std::string name)
   {
      for (size_t i = 0; i < taskList.size(); i++)
      {
         if (name == taskList[i].getName())
         {
            return &taskList[i];
         }
      }
      return nullptr;
   }
   void print();
   void graph(std::string& filename);
   bool validate()
   {
      int errors = 0;
      for (auto task : taskList)
      {
         if (!task.getPass().empty() && find(task.getPass()) == nullptr)
         {
            errors++;
            std::cerr << "Task " << task.getName() << " references unknown pass task " << task.getPass() << std::endl;
         }
         if (!task.getFail().empty() && find(task.getFail()) == nullptr)
         {
            errors++;
            std::cerr << "Task " << task.getName() << " references unknow fail task " << task.getFail() << std::endl;
         }
      }
      return errors == 0;
   }
};