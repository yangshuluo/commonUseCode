#include "nlohmann/json.hpp"
#include <iostream>
#include <string>

// Animal.h文件
//定义Animal类，其包含两个成员变量kind与height
using namespace std;
using nlohmann::json;
class Animal {
public:
  Animal(std::string kind, double height) {
    this->kind = kind;
    this->height = height;
  }
  std::string kind;
  double height;
};
//定义from_json(const json& j,T& value)函数，用于序列化
void from_json(const json &j, Animal &animal) {
  animal.kind = j["kind"].get<std::string>();
  animal.height = j["height"].get<double>();
}

//定义to_json(json& j,const T& value)函数，用于反序列化
void to_json(json &j, const Animal &animal) {
  j["kind"] = animal.kind;
  j["height"] = animal.height;
}

// main.cpp文件
int main() {
  Animal animal{"dog", 50};
  nlohmnn::json j = animal; //像basic value一样将自定义对象赋值给json value
  j["height"] = 60;         //修改数据
  Animal animalNew =
      j.get<Animal>(); //像basic
                       //value一样通过get函数获取值，将其值直接赋值给自定义对象
  std::cout << animal.height; //输出60
  return 0;
}
