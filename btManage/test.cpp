#include "json.hpp"
#include <assert.h>
#include <iostream>
#include <string>

#define DEBUG

using nlohmann::json;
using std::cout;
using std::endl;
using std::string;

namespace ns {
struct person {
  std::string name;
  std::string address;
  int age;
};

void to_json(json &j, const person &p) {
  j = json{{"name", p.name}, {"address", p.address}, {"age", p.age}};
}

void from_json(const json &j, person &p) {
  #define aaa 5
  j.at("name").get_to(p.name);
  j.at("address").get_to(p.address);
  j.at("age").get_to(p.age);
}
} // namespace ns

int main() {

  string str = "新建文本文档新建文本文档新建文本文档新建文本文档新建文本文档新建文本文档新建文本文档新建文本文档新建文本文档新建文本文档新建文本文档新建文本文档新建文本文档新建文本文";
  cout << str.size();
  return 0;
}