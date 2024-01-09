#include <iostream>
#include <string>
#include <vector>

std::vector<int> ZToPi(std::vector<int> z) {
  std::vector<int> pi(z.size(), 0);
  for (int i = 1; i < static_cast<int>(pi.size()); ++i) {
    for (int j = z[i] - 1; j >= 0; --j) {
      if (pi[i + j] == 0) {
        pi[i + j] = j + 1;
      } else {
        break;
      }
    }
  }
  return pi;
}

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
  std::vector<int> z(n);
  for (size_t i = 0; i < n; ++i) {
    std::cin >> z[i];
  }
  std::cout << PiString(ZToPi(z));
}
