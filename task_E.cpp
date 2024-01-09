#include <iostream>
#include <string>
#include <vector>

std::vector<int> ZFunction(std::string string) {
  std::vector<int> z(string.length(), 0);
  z[0] = static_cast<int>(string.length());
  size_t l = 0;
  size_t r = 0;
  for (size_t i = 1; i < string.length(); ++i) {
    if (i <= r) {
      z[i] = std::min(static_cast<int>(r - i + 1), z[i - l]);
    }
    while (i + static_cast<size_t>(z[i]) < string.length() && string[z[i]] == string[z[i] + i]) {
      ++z[i];
    }
    if (r < i + z[i] - 1) {
      r = i + z[i] - 1;
      l = i;
    }
  }
  return z;
}

std::vector<int> KMP(std::string string, std::string pattern) {
  std::string kmp = pattern + '#' + string;
  std::vector<int> z = ZFunction(kmp);
  std::vector<int> result;
  for (size_t i = pattern.size() + 1; i < kmp.size(); ++i) {
    if (z[i] == static_cast<int>(pattern.size())) {
      result.emplace_back(i - pattern.size() - 1);
    }
  }
  return result;
}

int main() {
  std::string string;
  std::string pattern;
  std::cin >> string;
  std::cin >> pattern;
  std::vector<int> kmp = KMP(string, pattern);
  for (size_t i = 0; i < kmp.size(); ++i) {
    std::cout << kmp[i] << '\n';
  }
}
