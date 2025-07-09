#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// Complete the following function.
int find_nth_term(int n, int a, int b, int c) {
  // Write your code here.
  if (n == 3) {
      return c;
  }
  else if (n == 2) {
      return b;
  }
  else if (n == 1) {
      return a;
  }
  else if (n == 0) {
      return 0;
  }
  return find_nth_term(n-1, a, b, c) + find_nth_term(n-2, a, b, c) + find_nth_term(n-3, a, b, c);
}

int main() {
    int n, a, b, c;
    printf("Enter the values of n, a, b, c: ");
    scanf("%d %d %d %d", &n, &a, &b, &c);
    int result = find_nth_term(n, a, b, c);
    printf("The %dth term is %d\n", n, result);
    return 0;
}