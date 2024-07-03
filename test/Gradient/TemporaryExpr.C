// RUN: %cladclang %s -fno-exceptions -I%S/../../include -oTemporaryExpr.out 2>&1 | %filecheck %s
// RUN: ./TemporaryExpr.out | %filecheck_exec %s

//CHECK-NOT: {{.*error|warning|note:.*}}
#include "clad/Differentiator/Differentiator.h"

class SimpleFunctions {
public:
  SimpleFunctions(double p_x = 0, double p_y = 0) : x(p_x), y(p_y) {}
  double x, y;
  double mem_fn(double i, double j) { return (x + y) * i + i * j; }

  SimpleFunctions operator*(SimpleFunctions& rhs) {
      return SimpleFunctions(this->x * rhs.x, this->y * rhs.y);
  }
};

double fn(int i, int j) {
    SimpleFunctions sf1 (3, 5);
    SimpleFunctions sf2 (i, j);

    return (sf1 * sf2).mem_fn(i, j);
}

int main() {
    auto fn_grad = clad::gradient(fn);

    double result[2] = {};
    fn_grad.execute(4, 5, &result[0], &result[1]);

    printf("%f %f\n", result[0], result[1]); // CHECK-EXEC: 0.000000 0.000000
}
