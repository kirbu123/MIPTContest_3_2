#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
std::vector<int> Maneker(std::vector<int> data) {
  std::vector<int> p(data.size(), 0);
  int left = 0;
  int right = 0;
  for (size_t i = 1; i < data.size(); ++i) {
    if (static_cast<int>(i) <= right) {
      p[i] = std::max(0, std::min(right - static_cast<int>(i) + 1, p[right - static_cast<int>(i) + 1 + left]));
    }
    while ((static_cast<int>(data.size() - i) > p[i]) && (static_cast<int>(i) > p[i]) &&
           (data[i - p[i] - 1] == data[i + p[i]])) {
      ++p[i];
    }
    if (p[i] > right + 1 - static_cast<int>(i)) {
      left = static_cast<int>(i) - p[i];
      right = static_cast<int>(i) + p[i] - 1;
    }
  }
  return p;
}

template <class T>
void Solvation(std::vector<T> p, int n) {
  for (T i = n - 1; i >= 0; --i) {
    if (i == p[i]) {
      std::cout << n - p[i] << ' ';
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  std::vector<int> cubes(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> cubes[i];
  }
  std::vector<int> p = Maneker(cubes);
  Solvation<int>(p, n);
  return 0;
}
