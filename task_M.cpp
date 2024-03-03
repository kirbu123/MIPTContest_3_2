#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>

class Bor {
 private:
  struct Vertex {
   public:
    std::map<char, int64_t> neighs;
    bool terminal = false;
    int64_t parent_;
    int64_t link_;
    int64_t exit_link_;
    int64_t lenght = 0;
    int64_t count;
    Vertex() = default;
  };
  struct Edge {
   public:
    char symbol;
    int64_t from;
    int64_t to;
    Edge() = default;
    Edge(char new_symbol, int64_t new_from, int64_t new_to) : symbol(new_symbol), from(new_from), to(new_to) {
    }
  };
  void MakeSuffLink() {
    bor_[0].link_ = -1;
    std::queue<Edge> que;
    Edge helper;
    for (auto& pair : bor_[0].neighs) {
      helper = Edge(pair.first, 0, pair.second);
      que.emplace(helper);
    }
    Edge edge;
    while (!que.empty()) {
      edge = que.front();
      que.pop();
      int64_t v = edge.from;
      int64_t link = bor_[v].link_;
      while ((link != -1) && (bor_[link].neighs.find(edge.symbol) == bor_[link].neighs.end())) {
        link = bor_[v].link_;
        v = link;
      }
      if (link == -1) {
        bor_[edge.to].link_ = 0;
      } else {
        bor_[edge.to].link_ = bor_[link].neighs[edge.symbol];
      }
      for (auto& pair : bor_[edge.to].neighs) {
        helper = Edge(pair.first, edge.to, pair.second);
        que.emplace(helper);
      }
    }
  }
  void MakeExitLink() {
    bor_[0].exit_link_ = -1;
    std::queue<int64_t> que;
    for (auto& pair : bor_[0].neighs) {
      que.emplace(pair.second);
    }
    int64_t tmp = 0;
    while (!que.empty()) {
      tmp = que.front();
      que.pop();
      int64_t link = bor_[tmp].link_;
      if (bor_[link].terminal) {
        bor_[tmp].exit_link_ = link;
      } else {
        bor_[tmp].exit_link_ = bor_[link].exit_link_;
      }
      for (auto& pair : bor_[tmp].neighs) {
        que.emplace(pair.second);
      }
    }
  }
  int64_t Step(int64_t v, char s) {
    while (v != -1 && bor_[v].neighs.find(s) == bor_[v].neighs.end()) {
      v = bor_[v].link_;
    }
    if (v == -1) {
      return 0;
    }
    return bor_[v].neighs[s];
  }
  void AllIns(int64_t index, int64_t v) {
    if (!bor_[v].terminal) {
      v = bor_[v].exit_link_;
    }
    while (v != -1 && v != 0) {
      ins_[bor_[v].count].emplace_back(index - bor_[v].lenght + 2);
      v = bor_[v].exit_link_;
    }
  }
  std::vector<Vertex> bor_;
  std::vector<std::vector<int64_t>> ins_;

 public:
  Bor() {
    Vertex root;
    root.parent_ = 0;
    bor_.emplace_back(root);
  }
  void Insert(std::string string, int64_t count = 0) {
    int64_t v = 0;
    for (int64_t i = 0; i < static_cast<int64_t>(string.size()); ++i) {
      if (bor_[v].neighs.count(string[i]) == 0) {
        Vertex new_vert;
        new_vert.parent_ = v;
        new_vert.lenght = bor_[v].lenght + 1;
        bor_.emplace_back(new_vert);
        bor_[v].neighs[string[i]] = static_cast<int>(bor_.size() - 1);
        v = static_cast<int64_t>(bor_.size() - 1);
      } else {
        v = bor_[v].neighs[string[i]];
      }
    }
    bor_[v].terminal = true;
    bor_[v].count = count;
  }
  explicit Bor(std::vector<std::string> patterns) {
    Vertex root;
    root.parent_ = 0;
    bor_.emplace_back(root);
    int64_t count = 0;
    for (auto& p : patterns) {
      Insert(p, count);
      ++count;
    }
    MakeSuffLink();
    MakeExitLink();
    ins_.resize(patterns.size());
  }
  bool Exists(std::string string) {
    int64_t v = 0;
    for (int64_t i = 0; i < static_cast<int64_t>(string.size()); ++i) {
      if (bor_[v].neighs.count(string[i]) == 0) {
        return false;
      }
      v = bor_[v].neighs[string[i]];
    }
    return bor_[v].terminal;
  }
  std::vector<std::vector<int64_t>> AhoCorasik(std::string text) {
    int64_t v = 0;
    for (int64_t i = 0; i < static_cast<int64_t>(text.length()); ++i) {
      v = Step(v, text[i]);
      AllIns(i, v);
    }
    return ins_;
  }
};

int main() {
  std::string parol;
  std::cin >> parol;
  int64_t n = 0;
  std::cin >> n;
  std::vector<std::string> patterns(n);
  std::vector<std::pair<int64_t, int64_t>> lr(n);
  for (int64_t i = 0; i < n; ++i) {
    std::cin >> lr[i].first >> lr[i].second >> patterns[i];
  }
  Bor bor(patterns);
  std::vector<std::vector<int64_t>> checker = bor.AhoCorasik(parol);
  std::map<std::string, int64_t> map;
  for (int64_t i = static_cast<int64_t>(checker.size()) - 1; i >= 0; --i) {
    if (map.find(patterns[i]) == map.end()) {
      map[patterns[i]] = i;
    } else {
      checker[i] = checker[map[patterns[i]]];
    }
  }
  for (size_t i = 0; i < patterns.size(); ++i) {
    bool check = false;
    for (size_t j = 0; j < checker[i].size(); ++j) {
      if (checker[i][j] >= lr[i].first &&
          checker[i][j] + static_cast<int64_t>(patterns[i].length()) - 1 <= lr[i].second) {
        check = true;
        break;
      }
    }
    if (check) {
      std::cout << '+';
    } else {
      std::cout << '-';
    }
  }
  return 0;
}
