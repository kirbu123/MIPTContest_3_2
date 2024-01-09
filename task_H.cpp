#include <iostream>
#include <string>
#include <vector>

int PiFunction(std::string string) {
  std::vector<int> pi(string.length(), 0);
  for (size_t i = 1; i < string.length(); ++i) {
    int k = pi[i - 1];
    while (k > 0 && string[k] != string[i]) {
      k = pi[k - 1];
    }
    if (string[k] == string[i]) {
      ++k;
    }
    pi[i] = k;
  }
  return pi[pi.size() - 1];
}

std::string MatchByRule(std::vector<std::string> strings) {
  std::string first = strings[0];
  for (size_t i = 1; i < strings.size(); ++i) {
    std::string second = strings[i];
    if (first.size() > second.size()) {
      std::string first_string(first.begin() + static_cast<int>(first.size() - second.size()), first.end());
      int suff = PiFunction(second + '#' + first_string);
      first += second.substr(suff);
    } else {
      int suff = PiFunction(second + '#' + first);
      first += second.substr(suff);
    }
  }
  return first;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  size_t n = 0;
  std::cin >> n;
  std::vector<std::string> strings(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> strings[i];
  }
  std::cout << MatchByRule(strings);
}
