#include <iostream>
#include <string>
#include <vector>

std::string PiString(std::vector<int> pi) {
  std::string string(pi.size(), 'a');
  for (size_t i = 1; i < string.size(); ++i) {
    if (pi[i] == 0) {
      size_t k = pi[i - 1];
      std::vector<bool> alphabet(26, false);
      alphabet[0] = true;
      while (k > 0) {
        alphabet[static_cast<int>(string[k] - 'a')] = true;
        k = pi[k - 1];
      }
      alphabet[static_cast<int>(string[k] - 'a')] = true;
      for (size_t j = 0; j < alphabet.size(); ++j) {
        if (!alphabet[j]) {
          string[i] = static_cast<char>('a' + j);
          break;
        }
      }
    } else {
      string[i] = string[pi[i] - 1];
    }
  }
  return string;
}

int main() {
  size_t n = 0;
  std::cin >> n;
  std::vector<int> pi(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> pi[i];
  }
  std::cout << PiString(pi);
}
