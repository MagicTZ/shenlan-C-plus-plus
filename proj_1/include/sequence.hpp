#ifndef _INCLUDE_SEQUENCE_HPP_
#define _INCLUDE_SEQUENCE_HPP_

#pragma once

#include <iostream>
#include <vector>

namespace magictz {

class Sequence {
  // 存储10进制结构整数
 public:
  Sequence() {}
  ~Sequence() {}

 public:
  void setCharVec(std::vector<char>& temp) { 
    for(size_t i = 0; i < temp.size();i++){
      char_vec.push_back(temp[i]);
    }
  }

  void vectorCharToInt() {
    if (char_vec.size() == 0) {
      std::cerr << "字符序列长度为0, 请检查!";
      return;
    }

    size_t start_pos = 0;  // 起始位置

    // 处理第一位可能出现符号的场景
    if (char_vec[0] == '-') {
      isPositive = false;
      start_pos = 1;
    } else if (char_vec[0] == '+') {
      start_pos = 1;
    }

    // 找到第一个非0整数的位置
    size_t pos = start_pos;
    while (char_vec[pos] == '0') {
      pos++;
    }
    start_pos = pos;

    for (size_t i = start_pos; i < char_vec.size(); i++) {
      char tmp = char_vec[i];
      uint64_t res = tmp - '0';  // 字符转数字
      int_vec.push_back(res);
    }
  }

  void PrintInteger() const {
    std::cout << "打印整数: ";
    if(isPositive==false) std::cout<<'-';
    for (size_t i = 0; i < int_vec.size(); i++) {
      std::cout << int_vec[i];
    }
    std::cout << std::endl;
  }

  void PrintString() const {
    std::cout << "打印字符: ";
    for (size_t i = 0; i < char_vec.size(); i++) {
      std::cout << char_vec[i];
    }
    std::cout << std::endl;
  }

 public:
  std::vector<char> char_vec;     // 存储长字符序列
  std::vector<uint64_t> int_vec;  // 存储长整型序列

  bool isPositive = true;  // 默认是正数
};

}  // namespace magictz

#endif  //_INCLUDE_SEQUENCE_HPP_
