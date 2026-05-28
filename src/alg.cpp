#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
#include <algorithm>
#include "bst.h"

// Функция загрузки слов из файла в дерево
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
      // Собираем буквы, преобразуя в нижний регистр
      word += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    } else {
      // Небуквенный символ – конец слова (если было накоплено)
      if (!word.empty()) {
        tree.insert(word);
        word.clear();
      }
    }
  }
  // Последнее слово (если файл не заканчивается небуквенным символом)
  if (!word.empty()) {
    tree.insert(word);
  }

  file.close();
}

// Вывод слов по убыванию частоты и сохранение в result/freq.txt
void printFreq(BST<std::string>& tree) {
  auto pairs = tree.getAll();
  if (pairs.empty()) {
    std::cout << "Tree is empty." << std::endl;
    return;
  }

  // Сортировка по убыванию частоты (при равной частоте – по алфавиту, для определённости)
  std::sort(pairs.begin(), pairs.end(),
            [](const std::pair<std::string, int>& a,
               const std::pair<std::string, int>& b) {
              if (a.second != b.second)
                return a.second > b.second;   // по убыванию частоты
              return a.first < b.first;       // при равной частоте – по алфавиту
            });

  // Открываем файл для записи
  std::ofstream out("result/freq.txt");
  if (!out) {
    std::cerr << "Cannot create result/freq.txt" << std::endl;
    return;
  }

  // Вывод на экран и в файл
  for (const auto& p : pairs) {
    std::cout << p.first << " " << p.second << std::endl;
    out << p.first << " " << p.second << std::endl;
  }

  out.close();
}
