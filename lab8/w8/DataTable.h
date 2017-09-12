//DataTable.h
#pragma once
#include <numeric>   
#include <algorithm> 
#include <vector>    
#include <cmath>   
using namespace std;

namespace w8 { 
   template<typename T>
   class DataTable {
      int FW;
      int ND;
      vector<T> x_;
      vector<T> y_;
   public:
      DataTable(ifstream& is, int field_width, int number_of_decimals) {
         FW = field_width;
         ND = number_of_decimals;
         T x, y;
         if (is.is_open()) {
            while (!is.eof()) {
               is >> x;
               x_.push_back(x);
               is >> y;
               y_.push_back(y);
            }
         }
      }
     
      T mean() const {
         T sum = accumulate(y_.begin(), y_.end(), (T)0);
         return sum / y_.size();
      }

      T sigma() const {
         T m = mean();
         T sum = 0;
         for (size_t i = 0; i < y_.size(); i++)
            sum = sum + (y_.at(i) - m) * (y_.at(i) - m);
         return sqrt(static_cast<double>(sum / (y_.size() - 1)));
      }

      T median() const {
         vector<T> v = y_;                           
         sort(v.begin(), v.end());
         T t = y_.size();
         return v[t / 2];
      }

      void regression(T& slope, T& y_intercept) const {
         T tatal_xy     = inner_product(x_.begin(), x_.end(), y_.begin(), (T)0);
         T tatal_x      = accumulate(x_.begin(), x_.end(), (T)0);
         T tatal_y      = accumulate(y_.begin(), y_.end(), (T)0);
         T tatal_xx   = inner_product(x_.begin(), x_.end(), x_.begin(), (T)0);
         T num = y_.size();
         slope = (num * tatal_xy - tatal_x * tatal_y) / (num * tatal_xx - tatal_x * tatal_x);
         y_intercept = (tatal_y - slope * tatal_x) / num;
      }

      void display(ostream& os) const {
         os << setw(FW) << setprecision(ND) << fixed<< 'X';
         os << setw(FW) << 'Y' << endl;
         for (int i = 0; i < x_.size(); i++) {
            os << setw(FW) << x_[i] << setw(FW) << y_[i] << endl;
         }
      }

      friend ostream& operator<<(ostream& os, const DataTable& datatable) {
         datatable.display(os);
         return os;
      }
   };
}
