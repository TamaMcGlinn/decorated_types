#include "si.h"

#include<iostream>

int main(){
  //lengths and surfaces
  SI::length<int> width(5);
  SI::length<int> height(10);
  SI::area<int> surface = width * height;
  //SI::length<int> error = width * height;
  std::cout << "A " << width << " by " << height << " metre square has a surface area of " << surface.value << " m2." << std::endl;

  std::cout << "---------------------------------------------------------------------------------" << std::endl;

  
  //acceleration
  SI::length<double> between_trains = 2300;
  std::cout << "Two trains are facing each other, " << between_trains << " metres apart." << std::endl;
  SI::speed<double> v1 = 5, v2 = 50;
  SI::time<double> start_time = 80;
  std::cout << "At t=" << start_time << " seconds, they instantly accelerate to " << v1 << " and " << v2 << " m/s, respectively." << std::endl;
  SI::time<double> crash_time = start_time + between_trains/(v1+v2);
  std::cout << "They collide at t=" << crash_time << " seconds." << std::endl;
 
  SI::unit<float, 1, 0, 0> length(3); // 3 metres
  SI::unit<float, 3, 0, 0> volume(3); // 3 cubic metres
  SI::unit<float, 0, 0, -1> frequency(3); // 3 times per second
  SI::unit<float, 1, 0, -1> speed(3); // 3 metres per second

  //length = length * length; // illegal
  volume = length * length * length; // 3m * 3m * 3m = 27 cubic metres

  std::cout << "---------------------------------------------------------------------------------" << std::endl;
 
//   //fire
//   SI::temperature<double> treeTemperature = 292.15;
//   SI::unit<double, 0, 0, -1, 0, 1, 0, 0> warmupSpeed = 4;
//   SI::unit<double, 0, 0, -2, 0, 1, 0, 0> warmupAcceleration = 2.3;
//   std::cout << "A nearby tree, starting from an initial temperature of " << treeTemperature << " K, is warmed by the resulting fire " << std::endl
//   << "at a rate starting at " << warmupSpeed << " K/s and increasing at a rate of " << warmupAcceleration << " K/s2." << std::endl;
// 
//   SI::time<double> delta = 0.05; SI::time<double> burnTime = 10.0;
//   for(SI::time<double> t = 0.0; t < burnTime; t += delta){
// 	  warmupSpeed += warmupAcceleration * delta;
// 	  treeTemperature += warmupSpeed * delta;
//   }
// 
//   std::cout << "After " << burnTime << " seconds, the tree has reached a temperature of " << toCelsius(treeTemperature) << " C." << std::endl;
  return 0;
}
