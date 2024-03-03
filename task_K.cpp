#include <iostream>
#include <string>
#include <vector>
#include <map>

class Bor {
 private:
  struct Vertex {
   public:
    std::map<char, size_t> neighs;
    bool terminal = false;
    Vertex() = default;
  };
  std::vector<Vertex> bor_;

 public:
  Bor() {
    Vertex root;
    bor_.emplace_back(root);
  }
  void Insert(std::string string) {
    size_t v = 0;
    for (size_t i = 0; i < string.size(); ++i) {
      if (bor_[v].neighs.count(string[i]) == 0) {
        Vertex new_vert;
        bor_.emplace_back(new_vert);
        bor_[v].neighs[string[i]] = bor_.size() - 1;
        v = bor_.size() - 1;
      } else {
        v = bor_[v].neighs[string[i]];
      }
    }
    bor_[v].terminal = true;
  }
  bool Exists(std::string string) {
    size_t v = 0;
    for (size_t i = 0; i < string.size(); ++i) {
      if (bor_[v].neighs.count(string[i]) == 0) {
        return false;
      }
      v = bor_[v].neighs[string[i]];
    }
    return bor_[v].terminal;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string string;
  std::string command;
  Bor bor;
  while (std::cin >> command && command != "#") {
    std::cin >> string;
    if (command == "+") {
      bor.Insert(string);
    } else if (command == "?") {
      if (bor.Exists(string)) {
        std::cout << "YES\n";
      } else {
        std::cout << "NO\n";
      }
    }
  }
  return 0;
}
