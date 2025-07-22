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
  
  Item( std::string name = "Default Name",
        Type::E itemType = Type::DEFAULT,
        int damage = 50, 
        bool isEnchanted = false)
        : m_name(name) ,
          m_itemType(itemType),
          m_damage(damage),
          m_isEnchanted(isEnchanted){}
  
  ~Item() = default;

  std::string m_name {"Default_Name"};
  
  Type::E m_itemType {Type::DEFAULT};
  
  int m_damage{50};
  
  bool m_isEnchanted {false};

};


int main(){

  std::mt19937 mt;
  mt.seed((unsigned)std::time(NULL));
  std::uniform_int_distribution<int> dist(0, 100);

  MKVector<Item> vItems;
  
  
  
  for (int i = 0; i < 8; ++i)
  {
    vItems.PushBack({"IITEEEM!"});
  }
  
  vItems.PushBack({"Drorthy"});

  std::cout << vItems.Size() <<" elements on the vector: " << std::endl;
  for (int i = 0; i < vItems.Size(); ++i)
  {
    std::cout << "\t- Element " <<i<<": " << vItems[i].m_name << std::endl;
  }
  
  
  
  int fasd = 0;
  
  return 0;
}
