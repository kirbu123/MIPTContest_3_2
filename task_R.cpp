#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cmath>

class Bor {
 public:
  explicit Bor(int64_t max_digit_new) {
    Node root;
    bor_.emplace_back(root);
    max_digit_ = max_digit_new;
  };

  void Insert(std::string str, std::string city_name) {
    int64_t state = 0;
    auto size = static_cast<int64_t>(str.length());
    for (int64_t i = 0; i < size; ++i) {
      if (!bor_[state].dict.count(str[i])) {
        bor_.emplace_back();
        bor_[state].dict[str[i]] = static_cast<int64_t>((bor_.size())) - 1;
        bor_[state].depth = i;
      }
      state = bor_[state].dict[str[i]];
    }
    bor_[state].is_terminal = true;
    bor_[state].depth = size;
    bor_[state].city = city_name;
  }
  int64_t Counter(const int64_t&);

 private:
  struct Node {
    std::map<char, int64_t> dict;
    bool is_terminal = false;
    Node() = default;
    int64_t depth = 0;
    int64_t sum_cakes = 0;
    std::string city;
  };
  int64_t max_digit_ = 0;
  std::vector<Node> bor_;
};

int64_t Bor::Counter(const int64_t& ind = 0) {
  if ((bor_[ind].is_terminal) && (bor_[ind].depth <= max_digit_)) {
    bor_[ind].sum_cakes = static_cast<int64_t>(pow(10, static_cast<double>(max_digit_ - bor_[ind].depth)));
    for (auto it : bor_[ind].dict) {
      if (bor_[it.second].depth > max_digit_) {
        Counter(it.second);
        continue;
      }
      if (!bor_[it.second].is_terminal) {
        bor_[ind].sum_cakes -= Counter(it.second);
      } else {
        Counter(it.second);
        bor_[ind].sum_cakes -= static_cast<int64_t>(pow(10, static_cast<double>(max_digit_ - bor_[ind].depth - 1)));
      }
    }
    std::cout << bor_[ind].city << ' ' << bor_[ind].sum_cakes << std::endl;
  } else if ((bor_[ind].is_terminal) && (bor_[ind].depth > max_digit_)) {
    bor_[ind].sum_cakes = 0;
    std::cout << bor_[ind].city << ' ' << bor_[ind].sum_cakes << std::endl;
    for (auto it : bor_[ind].dict) {
      Counter(it.second);
    }
  } else {
    for (auto it : bor_[ind].dict) {
      if (bor_[it.second].depth <= max_digit_) {
        if (bor_[it.second].is_terminal) {
          Counter(it.second);
          bor_[ind].sum_cakes += static_cast<int64_t>(pow(10, static_cast<double>(max_digit_ - bor_[ind].depth - 1)));
        } else {
          bor_[ind].sum_cakes += Counter(it.second);
        }
        continue;
      }
      Counter(it.second);
    }
  }
  return bor_[ind].sum_cakes;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int64_t n = 0;
  std::cin >> n;
  int64_t m = 0;
  std::cin >> m;
  Bor trie(m);
  std::string city_name;
  std::string city_index;
  for (auto i = 0; i < n; ++i) {
    std::cin >> city_index >> city_name;
    trie.Insert(city_index, city_name);
  }
  trie.Counter();
  return 0;
}
