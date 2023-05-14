#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

const int N_MAX = 1e5;
const int M_MAX = 1e4;

int main(int, char* argv[]) {
  srand(static_cast<unsigned int>(std::time(nullptr)));

  int n = N_MAX;
  int m = M_MAX;
  printf("%d %d\n", n, m);
  for (int i = 0; i < m; i++) {
    int a = rand() % n;
    int b = rand() % (n - 1);
    if (a == b) b++;
    printf("%d %d\n", a, b);
  }
  return 0;
}