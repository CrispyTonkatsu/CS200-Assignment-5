#include <cmath>
#include <iostream>
#include <ostream>

float textureWrap(float x) {
  float fraction = std::modf(x, &x);
  fraction = std::modf(1.f + fraction, &x);

  return fraction;
}

int main(int, char *[]) {
  std::cout << textureWrap(0.2) << std::endl;
  std::cout << textureWrap(1.2) << std::endl;
  std::cout << textureWrap(-0.8) << std::endl;
}
