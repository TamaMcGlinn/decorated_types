#include <iostream>

#include "basic_unittype.h"

int main(){
  using std::cout; using std::endl;

  typedef basic_unit<int,Apples> IntApples;
  typedef basic_unit<int,Oranges> IntOranges;

  IntApples apples(5);
  IntOranges oranges(5);

  //bool same = apples == oranges; // error, cannot compares apples to oranges
  IntApples otherApples(4);
  if( apples == otherApples ){ }
  
  //apples = apples + 5; // error, + is not defined for Apples and integers
  
  oranges = oranges + oranges;

  apples *= 5;
  cout << apples.value() << endl;
}
