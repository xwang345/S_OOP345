// Move-Constructor, Move-Assignment
// array.cpp

#include <new>
#include "array.h"

void Array::init(const Array& s) {
   if (s.n > 0) {
      a = new (std::nothrow) int[s.n];
      if (a) {
         n = s.n;
         dummy = s.dummy;
         for (int i = 0; i < n; i++)
            a[i] = s.a[i];
      }
   }
   else {
      a = nullptr;
      n = 0;
      dummy = 0;
   }
}
Array::Array(int no) : n(no), dummy(0) {
   if (n > 0)
      a = new (std::nothrow) int[n];
   else
      a = nullptr;
}
Array::~Array() { delete[] a; }
Array::Array(const Array& s) { init(s); }
Array::Array(Array&& s) {
   a = s.a;
   n = s.n;
   dummy = s.dummy;
   s.a = nullptr;
   s.n = 0;
   s.dummy = 0;
}
Array& Array::operator=(const Array& s) {
   if (&s != this) {
      delete[] a;
      init(s);
   }
   return *this;
}
Array&& Array::operator=(Array&& s) {
   if (&s != this) {
      a = s.a;
      n = s.n;
      dummy = s.dummy;
      s.a = nullptr;
      s.n = 0;
      s.dummy = 0;
   }
   return std::move(*this);
}
int& Array::operator[](int i) {
   return i >= 0 && i < n ? a[i] : dummy;
}
int Array::operator[](int i) const {
   return i >= 0 && i < n ? a[i] : dummy;
}
int Array::length() const { return n; }