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
  size_t n = 0;
  std::cin >> n;
  std::string first;
  std::cin >> first;
  std::string second;
  std::cin >> second;
  bool relevant_0 = false;
  bool relevant_1 = false;
  for (char i = '0'; i != '2'; ++i) {
    std::string new_string = first + '#' + second + i + second;
    std::vector<int> z = ZFunction(new_string);
    for (size_t j = first.size() + 1; j < new_string.size(); ++j) {
      if (z[j] == static_cast<int>(first.size())) {
        if (i == '0') {
          relevant_0 = true;
        } else if (i == '1') {
          relevant_1 = true;
        }
      }
    }
  }
  if (relevant_0 && relevant_1) {
    std::cout << "Random";
  } else if (relevant_0) {
    std::cout << "No";
  } else {
    std::cout << "Yes";
  }
}
