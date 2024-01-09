#include <iostream>
#include <string>
#include <vector>

std::vector<int> PiFunction(std::string string) {
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
  return pi;
}

int main() {
  std::string string;
  std::cin >> string;
  std::vector<int> pi = PiFunction(string);
  for (size_t i = 0; i < pi.size(); ++i) {
    std::cout << pi[i] << ' ';
  }
}
