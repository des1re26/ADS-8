// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
#include <algorithm>
#include <utility>
#include <string>

#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "File error!" << std::endl;
    return;
  }

  std::string word;
  int ch;
  while ((ch = file.get()) != EOF) {
    if (std::isalpha(static_cast<unsigned char>(ch))) {
      word += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    } else {
      if (!word.empty()) {
        tree.insert(word);
        word.clear();
      }
    }
  }
  if (!word.empty()) {
    tree.insert(word);
  }

  file.close();
}

void printFreq(BST<std::string>& tree) {
  auto pairs = tree.getAll();
  if (pairs.empty()) {
    std::cout << "Tree is empty." << std::endl;
    return;
  }

  std::sort(pairs.begin(), pairs.end(),
            [](const std::pair<std::string, int>& a,
               const std::pair<std::string, int>& b) {
              if (a.second != b.second)
                return a.second > b.second;
              return a.first < b.first;
            });

  std::ofstream out("result/freq.txt");
  if (!out) {
    std::cerr << "Cannot create result/freq.txt" << std::endl;
    return;
  }

  for (const auto& p : pairs) {
    std::cout << p.first << " " << p.second << std::endl;
    out << p.first << " " << p.second << std::endl;
  }

  out.close();
}
