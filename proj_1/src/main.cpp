
#include <iostream>
#include <string>

#include "include/common.h"
#include "include/sequence.hpp"

int main(int argc, char** argv) {
  // 载入目录
  std::string filename = argv[1];
  // std::string filename =
  // "/home/magictz/Projects/深蓝/C++课程/proj_1/data/test_case6.txt";
  if (filename.empty()) {
    std::cerr << "文件路径有问题, 请重新输入 ! \n格式为: [可执行文件] <路径>";
    exit(-1);
  }

  magictz::Sequence sequence1;
  magictz::Sequence sequence2;

  // 读取测试文件
  magictz::ReadTestFile(filename, sequence1, sequence2);

  // 格式转换: char -> uint64_t
  sequence1.vectorCharToInt();
  sequence2.vectorCharToInt();

  sequence1.PrintInteger();
  sequence2.PrintInteger();

  magictz::Sequence seq_res;
  // 加法
  if (sequence1.isPositive && sequence2.isPositive) {
    magictz::SequenceAdd(sequence1, sequence2, seq_res);
  }else if (sequence1.isPositive == false && sequence2.isPositive == false) {
      magictz::SequenceAdd(sequence1, sequence2, seq_res);
      seq_res.isPositive = false;
  } else{ // 减法
    magictz::SequenceMinus(sequence1, sequence2, seq_res);
  }

  std::cout << "==================结果输出==================" << std::endl;
  seq_res.PrintInteger();

  return 0;
}
