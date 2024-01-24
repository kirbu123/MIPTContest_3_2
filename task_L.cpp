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
  void AhoCorasik(std::string text) {
    int64_t v = 0;
    for (int64_t i = 0; i < static_cast<int64_t>(text.length()); ++i) {
      v = Step(v, text[i]);
      AllIns(i, v);
    }
    for (int64_t i = 0; i < static_cast<int64_t>(ins_.size()); ++i) {
      std::cout << ins_[i].size() << ' ';
      for (int64_t j = 0; j < static_cast<int64_t>(ins_[i].size()); ++j) {
        std::cout << ins_[i][j] << ' ';
      }
      std::cout << '\n';
    }
  }
  void Print() const {
    for (int64_t i = 0; i < static_cast<int64_t>(bor_.size()); ++i) {
      std::cout << "Vertex: " << i << "\n";
      std::cout << "Parent: " << bor_[i].parent_ << '\n';
      std::cout << "Is Terminal: " << bor_[i].terminal << '\n';
      for (auto& pair : bor_[i].neighs) {
        std::cout << "Edge: " << pair.first << ' ' << pair.second << '\n';
      }
      std::cout << "Suff Link: " << bor_[i].link_ << '\n';
      std::cout << "Exit Link: " << bor_[i].exit_link_ << '\n';
      std::cout << "Lenght: " << bor_[i].lenght << '\n';
      std::cout << '\n';
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string string;
  std::cin >> string;
  int64_t n = 0;
  std::cin >> n;
  std::vector<std::string> patterns(n);
  for (int64_t i = 0; i < n; ++i) {
    std::cin >> patterns[i];
  }
  Bor bor(patterns);
  bor.AhoCorasik(string);
  return 0;
}
