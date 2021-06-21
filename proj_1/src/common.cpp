#include "include/common.h"

namespace magictz {

void ReadTestFile(const std::string& filename, Sequence& seq1, Sequence& seq2) {
  std::ifstream in;
  in.open(filename);
  if (!in.is_open()) {
    std::cerr << "打开文件失败!" << std::endl;
    exit(-1);
  }

  std::cout << "================原始测试数据================" << std::endl;
  std::vector<std::string> data;
  std::string line;
  while (getline(in, line)) {
    data.push_back(line);
    std::cout << line << std::endl;
  }

  std::vector<char> temp1, temp2;
  for (size_t i = 0; i < data[0].length() - 1; i++) {
    temp1.push_back(data[0][i]);
  }
  for (size_t i = 0; i < data[1].length() - 1; i++) {
    temp2.push_back(data[1][i]);
  }

  seq1.setCharVec(temp1);
  seq2.setCharVec(temp2);
}

void SequenceAdd(const Sequence& seq1, const Sequence& seq2, Sequence& res) {
  std::vector<uint64_t> seq1_vec = seq1.int_vec;
  std::vector<uint64_t> seq2_vec = seq2.int_vec;

  size_t length_1 = seq1_vec.size();
  size_t length_2 = seq2_vec.size();

  // 分三种情况, 符号判断
  bool isPlus = false;  // 是否进位
  std::vector<uint64_t> tmp;

  if (length_1 == length_2) {  // 序列长度相同
    std::cout << "序列长度相同" << std::endl;

    while (!seq1_vec.empty()) {
      int num1 = seq1_vec.back();
      int num2 = seq2_vec.back();
      seq1_vec.pop_back();
      seq2_vec.pop_back();

      int sum = num1 + num2;
      if (isPlus) sum++;
      if (sum > 9) {
        isPlus = true;
        sum = sum % 10;
      } else {
        isPlus = false;
      }
      tmp.push_back(sum);
    }
    if (isPlus) tmp.push_back(1);  // 特殊情况: 超出范围仍进位,需要额外加1
  } else {                         // 序列长度不同
    std::cout << "序列长度不同" << std::endl;

    while ((!seq1_vec.empty()) || (!seq2_vec.empty())) {
      // 第一个序列更短
      if (seq1_vec.empty()) {
        int num = seq2_vec.back();  //取出最后元素
        if (isPlus) num++;
        if (num > 9) {
          num = 0;
          isPlus = true;
        } else {
          isPlus = false;
        }
        tmp.push_back(num);  // 存入vec
        seq2_vec.pop_back();
      } else if (seq2_vec.empty()) {  // 第二个序列更短
        int num = seq1_vec.back();    //取出最后元素
        if (isPlus) num++;
        if (num > 9) {
          num = 0;
          isPlus = true;
        } else {
          isPlus = false;
        }
        tmp.push_back(num);  // 存入vec
        seq1_vec.pop_back();
      } else {
        int num1 = seq1_vec.back();
        int num2 = seq2_vec.back();
        seq1_vec.pop_back();
        seq2_vec.pop_back();

        int sum = num1 + num2;
        if (isPlus) sum++;
        if (sum > 9) {
          isPlus = true;
          sum = sum % 10;
        } else {
          isPlus = false;
        }
        tmp.push_back(sum);
      }
    }
  }

  // 将tmp倒置传给res
  while (!tmp.empty()) {
    int num = tmp.back();
    tmp.pop_back();
    res.int_vec.push_back(num);
  }
}

void SequenceMinus(const Sequence& seq1, const Sequence& seq2, Sequence& res) {
  std::vector<uint64_t> seq1_vec = seq1.int_vec;
  std::vector<uint64_t> seq2_vec = seq2.int_vec;

  bool seq1_isPositive = seq1.isPositive;
  bool seq2_isPositive = seq2.isPositive;

  size_t length_1 = seq1_vec.size();
  size_t length_2 = seq2_vec.size();

  // 找到绝对值较大的数, 并强行放到数列1
  if (length_1 == length_2) {
    if (seq1_vec[0] < seq2_vec[0]) {  // 将大数序列放到前面
      std::vector<uint64_t> seq_tmp = seq1_vec;
      seq1_vec = seq2_vec;
      seq2_vec = seq_tmp;
      seq1_isPositive = seq2.isPositive;
      seq2_isPositive = seq1.isPositive;
    }
  } else {  // 如果长度不相等, 把长数列放到前面
    if (length_1 < length_2) {
      std::vector<uint64_t> seq_tmp = seq1_vec;
      seq1_vec = seq2_vec;
      seq2_vec = seq_tmp;
      seq1_isPositive = seq2.isPositive;
      seq2_isPositive = seq1.isPositive;
    }
  }

  std::vector<char> temp;

  bool isBorrow = false;

  while (!seq1_vec.empty() && !seq2_vec.empty()) {
    int num1 = seq1_vec.back();
    int num2 = seq2_vec.back();

    seq1_vec.pop_back();
    seq2_vec.pop_back();

    int count_borrow = 0;

    // 上个位置是否借位
    if (isBorrow) {
      if (num1 == 0) {
        num1 = 9;
        count_borrow += 1;  //借位数自加
      } else {
        num1 -= 1;
      }
    }

    int diff = 0;
    if (num1 >= num2) {
      diff = num1 - num2;
    } else {
      diff = num1 + 10 - num2;
      count_borrow += 1;
    }
    isBorrow = (count_borrow > 0) ? true : false;
    temp.push_back(diff);
  }

  while (!seq1_vec.empty()) {  //对较长数列进行判断
    int num = seq1_vec.back();
    seq1_vec.pop_back();

    // 上个位置是否借位
    if (isBorrow) {
      if (num == 0) {
        num = 9;
        isBorrow = true;
      } else {
        num -= 1;
        isBorrow = false;
      }
    }
    temp.push_back(num);
  }

  if (temp.back() == 0) {  // 如果首位是0的情况
    temp.pop_back();
  }

  while (!temp.empty()) {  // 将tmp倒置传给res
    int num = temp.back();
    temp.pop_back();
    res.int_vec.push_back(num);
  }

  if(seq1_isPositive == true && seq2_isPositive == false){
    res.isPositive = true;
  }else{
    res.isPositive = false;
  }
}

}  // namespace magictz
