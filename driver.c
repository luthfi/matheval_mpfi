#include "ivalarith.h"
#include <stdio.h>

int main() {
  //void ivalarith_evaluate(char* expr, int a, int b, double* min, double* max);
  double min, max;
  ivalarith_evaluate("2^x+x*x+3", -2, 3, &min, &max);
  printf("min:%f, max:%f\n",min,max);
  return 0;
}
