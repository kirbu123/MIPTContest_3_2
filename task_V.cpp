#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

struct Node {
 public:
  int len;
  int link;
  int end_pos;
  std::map<char, int> next;
  Node() = default;
};

class SuffixAutomation {
 public:
  std::vector<Node> st_;
  int size_;
  int last_ = 0;
  void AddChar(char c) {
    Node new_node;
    ++size_;
    st_.emplace_back(new_node);
    int cur = static_cast<int>(st_.size() - 1);
    st_[cur].len = st_[last_].len + 1;
    st_[cur].end_pos = st_[last_].end_pos + 1;
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
        ++size_;
        st_[clone].len = st_[p].len + 1;
        st_[clone].link = st_[q].link;
        st_[clone].next = st_[q].next;
        st_[clone].end_pos = st_[q].end_pos;
        for (; p != -1 && st_[p].next[c] == q; p = st_[p].link) {
          st_[p].next[c] = clone;
        }
        st_[q].link = clone;
        st_[cur].link = clone;
      }
    }
    last_ = cur;
  }
  SuffixAutomation() {
    Node new_node;
    st_.emplace_back(new_node);
    st_[st_.size() - 1].len = 0;
    st_[st_.size() - 1].link = -1;
    st_[st_.size() - 1].end_pos = 0;
    size_ = 0;
  }
  explicit SuffixAutomation(std::string string) {
    Node new_node;
    size_ = 0;
    st_.emplace_back(new_node);
    st_[st_.size() - 1].len = 0;
    st_[st_.size() - 1].link = -1;
    st_[st_.size() - 1].end_pos = -1;
    for (size_t i = 0; i < string.length(); ++i) {
      AddChar(string[i]);
    }
  }
};

struct State {
 public:
  int begin;
  int len;
  std::map<char, int> next;
  State() = default;
};

class SuffixTree : public SuffixAutomation {
 public:
  std::vector<State> states_;
  std::string str_;
  int size_;
  void ExtractTransitions(SuffixAutomation& sa, int idx) {
    int suff_idx = sa.st_[idx].link;
    states_[idx].begin = static_cast<int>(str_.size()) - 1 - (sa.st_[idx].end_pos - sa.st_[suff_idx].len);
    states_[idx].len = sa.st_[idx].len - sa.st_[suff_idx].len;
    states_[suff_idx].next[str_[states_[idx].begin]] = idx;
  }
  explicit SuffixTree(std::string str) : str_(str) {
    std::string reversed_string(str);
    std::reverse(reversed_string.begin(), reversed_string.end());
    SuffixAutomation sa(reversed_string);
    size_ = sa.size_;
    states_.resize(size_ + 1);
    states_[0].begin = -1;
    states_[0].len = 0;
    for (int i = 1; i <= size_; ++i) {
      ExtractTransitions(sa, i);
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string string;
  std::cin >> string;
  string += '#';
  SuffixTree tree(string);
  std::cout << tree.size_ + 1 << '\n';
  for (int i = 0; i <= tree.size_; ++i) {
    for (auto elem = tree.states_[i].next.begin(); elem != tree.states_[i].next.end(); ++elem) {
      std::cout << i << ' ' << elem->first << ' ' << tree.states_[elem->second].len << ' ' << elem->second << '\n';
    }
  }
}
