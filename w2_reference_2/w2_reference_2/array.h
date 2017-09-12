// Move-Constructor, Move-Assignment 
// array.h

class Array {
   int* a;
   int n;
   int dummy;
   void init(const Array&);
public:
   Array(int = 0);
   ~Array();
   Array(const Array&);
   Array(Array&&);
   Array& operator=(const Array&);
   Array&& operator=(Array&&);
   int& operator[](int);
   int  operator[](int i) const;
   int length() const;
};