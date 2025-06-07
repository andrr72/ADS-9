// Copyright 2022 NNTU-CS

#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

class PMTree {
private:
  struct Node {
    char value;
    std::vector<Node*> children;
    Node(char v) : value(v), children() {}
  };

  Node* root;
  std::vector<char> symbols;

  void buildTree(Node* node, std::vector<char> available);
  void getPermutations(Node* node, std::vector<char>& current, std::vector<std::vector<char>>& result);
  void getPermByIndex(Node* node, std::vector<char>& current, int& index, int target, std::vector<char>& result);
  void navigateTree(Node* node, std::vector<char>& current, int& index, int target, std::vector<char>& result);

public:
  PMTree(const std::vector<char>& input);
  ~PMTree();
  std::vector<std::vector<char>> getAllPerms();
  std::vector<char> getPerm1(int num);
  std::vector<char> getPerm2(int num);
};

#endif  // INCLUDE_TREE_H_
