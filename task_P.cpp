#include <iostream>
#include <vector>
#include <map>

struct Node {
  int64_t len;
  int64_t link;
  int64_t pref_res = 0;
  std::map<char, int64_t> next;
  Node() = default;
};

class SuffixAutomation {
 private:
  std::vector<Node> st_;
  int64_t last_ = 0;
  void AddChar(char c) {
    Node new_node;
    st_.emplace_back(new_node);
    auto cur = static_cast<int64_t>(st_.size() - 1);
    st_[cur].len = st_[last_].len + 1;
    int64_t p = 0;
    for (p = last_; p != -1 && st_[p].next.count(c) == 0; p = st_[p].link) {
      st_[p].next[c] = cur;
    }
    if (p == -1) {
      st_[cur].link = 0;
    } else {
      int64_t q = st_[p].next[c];
      if (st_[q].len == st_[p].len + 1) {
        st_[cur].link = q;
      } else {
        Node new_node;
        st_.emplace_back(new_node);
        auto clone = static_cast<int64_t>(st_.size() - 1);
        st_[clone].len = st_[p].len + 1;
        st_[clone].link = st_[q].link;
        st_[clone].next = st_[q].next;
        for (; p != -1 && st_[p].next[c] == q; p = st_[p].link) {
          st_[p].next[c] = clone;
        }
        st_[q].link = clone;
        st_[cur].link = clone;
      }
    }
    st_[cur].pref_res = st_[cur].len + st_[last_].pref_res - st_[st_[cur].link].len;
    std::cout << st_[cur].pref_res << '\n';
    last_ = cur;
  }

 public:
  SuffixAutomation() {
    Node new_node;
    st_.emplace_back(new_node);
    st_[st_.size() - 1].len = 0;
    st_[st_.size() - 1].link = -1;
  }
  explicit SuffixAutomation(std::string string) {
    Node new_node;
    st_.emplace_back(new_node);
    st_[st_.size() - 1].len = 0;
    st_[st_.size() - 1].link = -1;
    for (size_t i = 0; i < string.length(); ++i) {
      AddChar(string[i]);
    }
  }
  void Show() {
    std::cout << st_.size() << '\n';
    for (size_t i = 0; i < st_.size(); ++i) {
      for (auto j = st_[i].next.begin(); j != st_[i].next.end(); ++j) {
        std::cout << i << ' ' << j->first << ' ' << j->second << '\n';
      }
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string string;
  std::cin >> string;
  SuffixAutomation automato(string);
}
