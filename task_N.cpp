#include <iostream>
#include <vector>
#include <map>

struct Node {
  int len;
  int link;
  std::map<char, int> next;
  Node() = default;
};

class SuffixAutomation {
 private:
  std::vector<Node> st_;
  int last_ = 0;
  void AddChar(char c) {
    Node new_node;
    st_.emplace_back(new_node);
    int cur = static_cast<int>(st_.size() - 1);
    st_[cur].len = st_[last_].len + 1;
    int p = 0;
    for (p = last_; p != -1 && st_[p].next.count(c) == 0; p = st_[p].link) {
      st_[p].next[c] = cur;
    }
    if (p == -1) {
      st_[cur].link = 0;
    } else {
      int q = st_[p].next[c];
      if (st_[q].len == st_[p].len + 1) {
        st_[cur].link = q;
      } else {
        Node new_node;
        st_.emplace_back(new_node);
        int clone = static_cast<int>(st_.size() - 1);
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
  automato.Show();
}