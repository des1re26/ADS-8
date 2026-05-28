#include <iostream>
#include "bst.h"

// Объявления функций из alg.cpp
void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
  BST<std::string> tree;
  makeTree(tree, "src/war_peace.txt");

  std::cout << "Tree depth: " << tree.depth() << std::endl;
  printFreq(tree);

  return 0;
}
