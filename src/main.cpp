// Copyright 2022 NNTU-CS
#include <chrono>
#include <random>
#include <iostream>
#include <vector>
#include "tree.h"

int main() {
  std::vector<char> in = {'1', '2', '3'};
  PMTree tree(in);

  auto perms = tree.getAllPerms();
  for (const auto& perm : perms) {
    for (char c : perm) std::cout << c;
    std::cout << '\n';
  }

  std::vector<int> sizes = {3, 4, 5, 6};
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 100);

  for (int n : sizes) {
    std::vector<char> testInput;
    for (int i = 1; i <= n; ++i) testInput.push_back('0' + i);
    PMTree testTree(testInput);

    auto start = std::chrono::high_resolution_clock::now();
    testTree.getAllPerms();
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "getAllPerms for n=" << n << ": "
              << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                                     start)
                     .count()
              << "us\n";

    int target = dis(gen) % (1 << n) + 1;
    start = std::chrono::high_resolution_clock::now();
    testTree.getPerm1(target);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "getPerm1 for n=" << n << ": "
              << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                                     start)
                     .count()
              << "us\n";

    start = std::chrono::high_resolution_clock::now();
    testTree.getPerm2(target);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "getPerm2 for n=" << n << ": "
              << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                                     start)
                     .count()
              << "us\n";
  }

  return 0;
}
