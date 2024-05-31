// RUN: %cladclang %s -I%S/../../include -fsyntax-only -Xclang -verify 2>&1

#define non_differentiable __attribute__((annotate("non_differentiable")))

#include "clad/Differentiator/Differentiator.h"

class non_differentiable SimpleFunctions {
public:
  SimpleFunctions() noexcept : x(0), y(0) {}
  SimpleFunctions(double p_x, double p_y) noexcept : x(p_x), y(p_y) {}
  double x;
  double y;
  double mem_fn(double i, double j) { return (x + y) * i + i * j * j; }
};

non_differentiable double mem_fn(double i, double j) {
  SimpleFunctions obj(2, 3);
  return obj.mem_fn(i, j) + i * j;
}

int main() {
    auto mem_fn_class_grad = clad::gradient(&SimpleFunctions::mem_fn); // expected-error {{attempted differentiation of method 'mem_fn' in class 'SimpleFunctions', which is marked as non-differentiable}}

    auto mem_fn_grad = clad::gradient(&mem_fn); // expected-error {{attempted differentiation of function 'mem_fn', which is marked as non-differentiable}}
}
