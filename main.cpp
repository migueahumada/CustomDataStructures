#include <vector>
#include <iostream>
#include "MKVector.h"
#include <random>
#include <string>

namespace Type{
  enum E {
    DEFAULT = 0,
    ARMOR,
    POTION,
    WEAPON
  };
}

/*
* Test Class to see how MKVector Works
*/
class Item {

public:
  Item() = default;
  
  Item( Type::E itemType = Type::DEFAULT, 
        int damage = 50, 
        bool isEnchanted = false) {}
  
  ~Item() = default;

  Type::E 
  m_itemType {Type::DEFAULT};
  
  int 
  m_damage{50};
  
  bool 
  m_isEnchanted {false};

};


int main(){
  
  std::vector<int> vec(2);

  int asdf = vec.size();

  std::mt19937 mt;
  mt.seed(std::time(NULL));
  std::uniform_int_distribution<int> dist(0, 100);

  MKVector<int> numbers;
  
  for (int i = 0; i < 30; ++i)
  {
    numbers.PushBack(dist(mt));
  }

  std::cout << "The size of the vector is: " << numbers.Size() << std::endl;

  std::cout << "Elements on the vector with the [] operator: " << std::endl;
  for (int i = 0; i < numbers.Size(); ++i)
  {
    std::cout << "\t- Element " <<i<<": " << numbers[i] << std::endl;
  }

  std::cout << "Elements on the vector with the At function: " << std::endl;
  for (int i = 0; i < numbers.Size(); ++i)
  {
    std::cout << "\t- Element " << i << ": " << numbers.At(i) << std::endl;
  }

  return 0;
}