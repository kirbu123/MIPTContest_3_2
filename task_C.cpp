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
  std::cin >> string;
  std::vector<int> z = ZFunction(string);
  for (size_t i = 0; i < z.size(); ++i) {
    std::cout << z[i] << ' ';
  }
}
