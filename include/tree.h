// Copyright 2022 NNTU-CS

#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

class PMTree {
 public:
  explicit PMTree(const std::vector<char>& input);
  ~PMTree();
  std::vector<std::vector<char>> getAllPerms();
  std::vector<char> getPerm1(int num);
  std::vector<char> getPerm2(int num);

 private:
  struct Node {
    char value;
    std::vector<Node*> children;
    explicit Node(char v) : value(v), children() {}
    ~Node() {
      for (Node* child : children) delete child;
    }
  };

  Node* root;
  std::vector<char> symbols;

  void buildTree(Node* node, std::vector<char> available);
  void getPermutations(Node* node, std::vector<char>& current,
                      std::vector<std::vector<char>>& result);
  void getPermByIndex(Node* node, std::vector<char>& current, int& index,
                      int target, std::vector<char>& result, int depth = 0);
  void navigateTree(Node* node, std::vector<char>& current, int& index,
                   int target, std::vector<char>& result, int depth = 0);
};

std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
