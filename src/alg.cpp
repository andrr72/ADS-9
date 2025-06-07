// Copyright 2022 NNTU-CS

#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include "tree.h"

PMTree::PMTree(const std::vector<char>& input) : symbols(input) {
  root = new Node('\0');
  buildTree(root, symbols);
}

PMTree::~PMTree() {
}

void PMTree::buildTree(Node* node, std::vector<char> available) {
  if (available.empty()) return;
  for (char val : available) {
    Node* child = new Node(val);
    node->children.push_back(child);
    std::vector<char> remaining;
    for (char c : available) if (c != val) remaining.push_back(c);
    buildTree(child, remaining);
  }
}

void PMTree::getPermutations(Node* node, std::vector<char>& current, std::vector<std::vector<char>>& result) {
  if (node->children.empty()) {
    if (node->value != '\0') current.push_back(node->value);
    result.push_back(current);
    if (node->value != '\0') current.pop_back();
    return;
  }
  if (node->value != '\0') current.push_back(node->value);
  for (Node* child : node->children) {
    getPermutations(child, current, result);
  }
  if (node->value != '\0') current.pop_back();
}

std::vector<std::vector<char>> PMTree::getAllPerms() {
  std::vector<std::vector<char>> result;
  std::vector<char> current;
  getPermutations(root, current, result);
  return result;
}

void PMTree::getPermByIndex(Node* node, std::vector<char>& current, int& index, int target, std::vector<char>& result) {
  if (index == target) {
    if (node->value != '\0') result = current;
    return;
  }
  if (node->value != '\0') current.push_back(node->value);
  for (Node* child : node->children) {
    index++;
    getPermByIndex(child, current, index, target, result);
    if (!result.empty()) return;
  }
  if (node->value != '\0') current.pop_back();
}

std::vector<char> PMTree::getPerm1(int num) {
  std::vector<char> current, result;
  int index = 0;
  getPermByIndex(root, current, index, num - 1, result);
  return result;
}

void PMTree::navigateTree(Node* node, std::vector<char>& current, int& index, int target, std::vector<char>& result) {
  if (node->children.empty()) {
    if (index == target - 1) result = current;
    return;
  }
  if (node->value != '\0') current.push_back(node->value);
  int childrenCount = node->children.size();
  int permsPerChild = 1;
  for (int i = 0; i < current.size() - 1; i++) permsPerChild *= (symbols.size() - i - 1);
  for (int i = 0; i < childrenCount; i++) {
    if (index + permsPerChild * (childrenCount - i) >= target) {
      index += permsPerChild * i;
      navigateTree(node->children[i], current, index, target, result);
      break;
    }
  }
  if (node->value != '\0') current.pop_back();
}

std::vector<char> PMTree::getPerm2(int num) {
  std::vector<char> current, result;
  int index = 0;
  navigateTree(root, current, index, num, result);
  return result;
}
