// Copyright 2022 NNTU-CS

#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include "tree.h"

PMTreeNode::~PMTreeNode() {
  for (auto child : children) {
    delete child;
  }
}

PMTree::~PMTree() {
  delete root;
}

PMTree::PMTree(const std::vector<char>& elements) {
  root = new PMTreeNode('\0');
  buildTree(root, elements);
}

void PMTree::buildTree(PMTreeNode* node, const std::vector<char>& remaining) {
  if (remaining.empty()) return;

  for (char c : remaining) {
    PMTreeNode* child = new PMTreeNode(c);
    node->children.push_back(child);

    std::vector<char> nextRemaining;
    for (char elem : remaining) {
      if (elem != c) nextRemaining.push_back(elem);
    }
    buildTree(child, nextRemaining);
  }
}

void collectPermutations(const PMTreeNode* node,
                        std::vector<char>& current,
                        std::vector<std::vector<char>>& result) {
  if (node->value != '\0') {
    current.push_back(node->value);
  }
  if (node->children.empty()) {
    result.push_back(current);
  } else {
    for (const auto& child : node->children) {
      collectPermutations(child, current, result);
    }
  }
  if (!current.empty()) {
    current.pop_back();
  }
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
  std::vector<std::vector<char>> result;
  std::vector<char> current;
  collectPermutations(tree.root, current, result);
  return result;
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
  std::vector<std::vector<char>> allPerms = getAllPerms(tree);
  if (num < 1 || num > static_cast<int>(allPerms.size())) return {};
  return allPerms[num - 1];
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
  std::vector<char> result;
  const PMTreeNode* node = tree.root;

  while (!node->children.empty()) {
    int factorial = 1;
    for (int i = 1; i <= static_cast<int>(node->children.size()) - 1; ++i) {
      factorial *= i;
    }

    int index = (num - 1) / factorial;
    if (index >= static_cast<int>(node->children.size())) return {};

    node = node->children[index];
    result.push_back(node->value);
    num = num - (index * factorial);
  }
  return result;
}
