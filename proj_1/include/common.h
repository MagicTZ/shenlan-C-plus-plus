#ifndef _INCLUDE_COMMON_H_
#define _INCLUDE_COMMON_H_

#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "include/sequence.hpp"

namespace magictz {

void ReadTestFile(const std::string& filename, Sequence &seq1, Sequence& seq2);

void SequenceAdd(const Sequence & seq1, const Sequence & seq2, Sequence& res);

void SequenceMinus(const Sequence & seq1, const Sequence & seq2, Sequence& res);

}  // namespace magictz

#endif // _INCLUDE_COMMON_H_
