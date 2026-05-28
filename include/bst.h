#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <stdexcept>
#include <algorithm>
#include <utility>
#include <string>

template <typename T>
class BST {
 private:
  struct Node {
    T key;
    int count;      // счётчик повторений слова
    Node *left;
    Node *right;

    explicit Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
  };

  Node *root;

  // Рекурсивное добавление/обновление
  void insertNode(Node*& node, const T& value) {
    if (!node) {
      node = new Node(value);
    } else if (value < node->key) {
      insertNode(node->left, value);
    } else if (node->key < value) {
      insertNode(node->right, value);
    } else {
      ++(node->count);   // ключ уже существует
    }
  }

  // Рекурсивный поиск
  bool searchNode(const Node* node, const T& value) const {
    if (!node) return false;
    if (value < node->key) return searchNode(node->left, value);
    if (node->key < value) return searchNode(node->right, value);
    return true;  // равны
  }

  // Рекурсивное вычисление глубины
  int depthNode(const Node* node) const {
    if (!node) return 0;
    return 1 + std::max(depthNode(node->left), depthNode(node->right));
  }

  // Рекурсивное удаление дерева
  void clearNode(Node* node) {
    if (node) {
      clearNode(node->left);
      clearNode(node->right);
      delete node;
    }
  }

  // Обход для сбора всех пар (слово, частота)
  void inorderCollect(const Node* node, std::vector<std::pair<T, int>>& vec) const {
    if (!node) return;
    inorderCollect(node->left, vec);
    vec.push_back({node->key, node->count});
    inorderCollect(node->right, vec);
  }

 public:
  BST() : root(nullptr) {}
  ~BST() { clearNode(root); }

  // Добавить значение (или увеличить счётчик)
  void insert(const T& value) {
    insertNode(root, value);
  }

  // Поиск ключа
  bool search(const T& value) const {
    return searchNode(root, value);
  }

  // Глубина (высота) дерева
  int depth() const {
    return depthNode(root);
  }

  // Получить все пары (ключ, частота) для последующей сортировки
  std::vector<std::pair<T, int>> getAll() const {
    std::vector<std::pair<T, int>> result;
    inorderCollect(root, result);
    return result;
  }
};

#endif  // INCLUDE_BST_H_
