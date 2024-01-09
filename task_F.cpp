#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int MaxPiFunction(std::string string) {
  std::vector<int> pi(string.length(), 0);
  int result = 0;
  for (size_t i = 1; i < string.length(); ++i) {
    int k = pi[i - 1];
    while (k > 0 && string[k] != string[i]) {
      k = pi[k - 1];
    }
    if (string[k] == string[i]) {
      ++k;
    }
    pi[i] = k;
    result = std::max(result, pi[i]);
  }
  return result;
}

int main() {
  std::string string;
  std::cin >> string;
  int result = 1;
  for (size_t i = 1; i < string.size(); ++i) {
    std::string reversed(std::make_reverse_iterator(string.begin() + static_cast<int>(i) + 1), string.rend());
    result += static_cast<int>(i) + 1 - MaxPiFunction(reversed);
  }
  std::cout << result;
  return 0;
}
