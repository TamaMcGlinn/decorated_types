#include "dimensioned.h"
#include <iostream>
using std::cout;
using std::endl;

int main(){
  // adding lengths of differing dimensions
  dimensioned<float,Metre,1> a(100);
  dimensioned<float,Centimetre,1> b(10);
  dimensioned<float,Metre,1> c = a + b;
  cout << a << " + " << b << " = " << c << endl;

  // multiplying lengths yields a surface
  dimensioned<float,Metre,1> side1(3);
  dimensioned<float,Metre,1> side2(5);
  dimensioned<float,Metre,2> surface = side1 * side2;
  cout << side1 << " x " << side2 << " = " << surface << endl;

  // multiplying lengths of different unit type
  dimensioned<float,Centimetre,1> shortside(90);
  dimensioned<float,Metre,1> longside(5);
  dimensioned<float,Centimetre,2> surface2 = shortside * longside;
  cout << shortside << " x " << longside << " = " << surface2 << endl;

  // converting the unit type works also for higher dimensions
  dimensioned<float,Metre,2> squareMetre(1000000);
  dimensioned<float,Kilometre,2> squareKms = squareMetre;
  cout << squareMetre << " = " << squareKms << endl;
}
