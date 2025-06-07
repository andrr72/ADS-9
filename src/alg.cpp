// Copyright 2022 NNTU-CS

#include <vector>
#include <algorithm>
#include "tree.h"

PMTree::PMTree(const std::vector<char>& elements) {
  if (elements.empty()) {
    root = nullptr;
    return;
  }
  root = new PMTreeNode('\0');
  buildTree(root, elements);
}

PMTree::~PMTree() {
  delete root;
}

void buildTree(PMTreeNode* node, const std::vector<char>& remaining) {
  if (!node || remaining.empty()) return;
  for (char c : remaining) {
    PMTreeNode* child = new PMTreeNode(c);
    node->children.push_back(child);
    std::vector<char> nextRemaining = remaining;
    nextRemaining.erase(std::remove(nextRemaining.begin(),
      nextRemaining.end(), c), nextRemaining.end());
    buildTree(child, nextRemaining);
  }
}

void collectPermutations(const PMTreeNode* node, std::vector<char>& current,
                        std::vector<std::vector<char>>& result) {
  if (!node) return;
  if (node->value != '\0') {
    current.push_back(node->value);
  }
  if (node->children.empty()) {
    result.push_back(current);
  } else {
    for (const PMTreeNode* child : node->children) {
      collectPermutations(child, current, result);
    }
  }
  if (node->value != '\0' && !current.empty()) {
    current.pop_back();
  }
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
  std::vector<std::vector<char>> result;
  std::vector<char> current;
  if (tree.root) {
    collectPermutations(tree.root, current, result);
  }
  return result;
}

std::vector<char> getPerm1(const PMTree& tree, int num) {
  if (!tree.root || num < 1) return {};
  std::vector<std::vector<char>> allPerms = getAllPerms(tree);
  if (num > static_cast<int>(allPerms.size())) return {};
  return allPerms[num - 1];
}

std::vector<char> getPerm2(const PMTree& tree, int num) {
  if (!tree.root || num < 1) return {};
  std::vector<char> result;
  const PMTreeNode* node = tree.root;
  int remaining = num;

  while (node && !node->children.empty()) {
    int childrenCount = node->children.size();
    int factorial = 1;
    for (int i = 1; i < childrenCount; ++i) {
      factorial *= i;
    }
    int index = (remaining - 1) / factorial;
    if (index >= childrenCount) return {};
    node = node->children[index];
    if (node->value != '\0') {
      result.push_back(node->value);
    }
    remaining = remaining - (index * factorial);
  }
  return result;
}
