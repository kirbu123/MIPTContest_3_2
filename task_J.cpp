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

int main() {
  std::string string;
  std::string pattern;
  std::cin >> string >> pattern;
  std::vector<int> z = ZFunction(string + '#' + pattern);
  int counter = 0;
  bool result = true;
  std::vector<size_t> indexes;
  for (size_t i = string.size() + 1; i < z.size(); ++i) {
    if (z[i] > counter) {
      counter = z[i];
      indexes.emplace_back(i - string.size() - 1);
    }
    --counter;
    if (counter < 0) {
      break;
    }
  }
  result = (counter < 0);
  if (result) {
    std::cout << "Yes";
  } else {
    std::cout << "No\n";
    size_t idx = 1;
    std::cout << pattern[0];
    for (size_t i = 1; i < pattern.length(); ++i) {
      if (idx < indexes.size() && indexes[idx] == i) {
        std::cout << ' ';
        ++idx;
      }
      std::cout << pattern[i];
    }
  }
  std::cout << '\n';
}
