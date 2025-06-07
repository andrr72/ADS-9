// Copyright 2022 NNTU-CS

#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

class PMTreeNode {
 public:
  char value;
  std::vector<PMTreeNode*> children;

  explicit PMTreeNode(char val) : value(val) {}
  ~PMTreeNode() {
    for (PMTreeNode* child : children) {
      delete child;
    }
  }
};

class PMTree {
 public:
  PMTreeNode* root;

  explicit PMTree(const std::vector<char>& elements);
  ~PMTree();
};

std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(const PMTree& tree, int num);
std::vector<char> getPerm2(const PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
