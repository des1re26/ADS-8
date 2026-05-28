// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

template <typename T>
class BST {
 private:
  struct Node {
    T key;
    int count;
    Node *left;
    Node *right;

    explicit Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
  };

  Node *root;

  void insertNode(Node*& node, const T& value) {
    if (!node) {
      node = new Node(value);
    } else if (value < node->key) {
      insertNode(node->left, value);
    } else if (node->key < value) {
      insertNode(node->right, value);
    } else {
      ++(node->count);
    }
  }

  // Поиск частоты слова (int)
  int searchNode(const Node* node, const T& value) const {
    if (!node) return 0;
    if (value < node->key) return searchNode(node->left, value);
    if (node->key < value) return searchNode(node->right, value);
    return node->count;   // нашли
  }

  int depthNode(const Node* node) const {
    if (!node) return -1;
    return 1 + std::max(depthNode(node->left), depthNode(node->right));
  }

  void clearNode(Node* node) {
    if (node) {
      clearNode(node->left);
      clearNode(node->right);
      delete node;
    }
  }

  void inorderCollect(const Node* node,
                      std::vector<std::pair<T, int>>& vec) const {
    if (!node) return;
    inorderCollect(node->left, vec);
    vec.push_back({node->key, node->count});
    inorderCollect(node->right, vec);
  }

 public:
  BST() : root(nullptr) {}
  ~BST() { clearNode(root); }

  void insert(const T& value) {
    insertNode(root, value);
  }

  // Возвращает частоту слова (0, если отсутствует)
  int search(const T& value) const {
    return searchNode(root, value);
  }

  int depth() const {
    return depthNode(root);
  }

  std::vector<std::pair<T, int>> getAll() const {
    std::vector<std::pair<T, int>> result;
    inorderCollect(root, result);
    return result;
  }
};

#endif  // INCLUDE_BST_H_
