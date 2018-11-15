#include "dimensioned.h"
using namespace dimensional;

#include <iostream>
using std::cout;
using std::endl;

int main(){
  cout << "------------Examples using distances---------------------" << endl;
  {
    // adding lengths of differing dimensions
    distance<float> a(100);
    distance<float,Centimetre> b(10);
    distance<float> c = a + b;
    cout << a << " + " << b << " = " << c << endl;
  }

  {
    // multiplying lengths yields a surface
    distance<float> side1(3);
    distance<float> side2(5);
    surface<float> surf = side1 * side2;
    cout << side1 << " x " << side2 << " = " << surf << endl;
  }

  {
    // multiplying lengths of different unit type
    dimensioned<float,Centimetre> shortside(90);
    distance<float> longside(5);
    surface<float,Centimetre> surface2 = shortside * longside;
    cout << shortside << " x " << longside << " = " << surface2 << " = " << surface<float,Metre>(surface2) << endl;
  }

  {
    // adding surfaces of different unittype
    surface<float,Centimetre> surface1(100);
    surface<float,Metre> surface2(1);
    cout << surface1 << " + " << surface2 << " = " << surface1 + surface2 << endl;
    cout << surface2 << " + " << surface1 << " = " << surface2 + surface1 
         << " = " << surface<float,Centimetre>( surface2 + surface1 ) << endl;
  }

  {
    // converting the unit type works also for higher dimensions
    surface<float> squareMetre(1000000);
    surface<float,Kilometre> squareKms = squareMetre;
    cout << squareMetre << " = " << squareKms << endl;
  }

  {
    // converting the unit type works also for higher dimensions
    surface<float,Kilometre> squareKilometre(25);
    distance<float,Metre> height(1);
    cout << squareKilometre << " * " << height << " = " << squareKilometre * height << endl;
    cout << height << " * " << squareKilometre << " = " << height * squareKilometre 
      << " = " << volume<float,Kilometre>(height * squareKilometre) << endl;
  }

  {
    volume<float> sqM(1); 
    volume<float,Centimetre> sqCms( sqM );
    cout << sqM << " = " << sqCms << endl;
  }

  cout << endl;
  cout << "------------Examples using distances and times-----------" << endl;

  {
    time<float> t1(5);
    time<float,Minute> t2(0.25);
    cout << t1 << " + " << t2 << " = " << t1 + t2 << endl;
    cout << t2 << " + " << t1 << " = " << t2 + t1 << endl;
    cout << t2 << " - " << t1 << " = " << time<float>(t2 - t1) << endl;
    cout << t1 << " * " << t2 << " = " << t1 * t2 << endl;
  }

  {
    surface<float> choppedArea(10);
    time<float,Second> chopTime(10);
    auto chopSpeed = choppedArea / chopTime;
    cout << choppedArea << " / " << chopTime << " = " << chopSpeed 
         << " = " << dimensioned<float,Metre,2,Minute,-1>(chopSpeed) << endl;
  }

  {
    // note that Minute here is nonsense since the time-dimension is 0, and this does not affect the result
    dimensioned<float,Metre,1,Minute,0> d1(50);
    time<float> t1(36);
    cout << "A timespace surface of " << d1 << " by " << t1 << " is " << d1 * t1 
         << " = " << dimensioned<float,Metre,1,Second,1>( d1 * t1 ) << endl;
    auto speed = d1 / t1;
    cout << "A distance of " << d1 << " is covered in " << t1 << " at a speed of " << speed 
         << " = " << dimensioned<float,Kilometre,1,Hour,-1>(speed) << endl;
  }
  
  dimensioned<float,Metre> d(5);
  dimensioned<float,Metre,0,Second,1> t(1);
  auto speed = d / t; // in metres per second
  dimensioned<float,Kilometre,1,Hour,-1> speed2(speed); // converted to kilometres per hour
  cout << "A distance of " << d << " is covered in " << t << " at a speed of " << speed 
       << " = " << speed2 << endl;
}
