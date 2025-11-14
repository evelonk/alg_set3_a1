#include <iostream>
#include <cmath>
#include <random>

struct Circle {
  double x, y, r2;
};

double area(int N, double xmin, double xmax, double ymin, double ymax, Circle c[3], std::mt19937_64 &rng) {
  int M = 0;
  double w = xmax - xmin;
  double h = ymax - ymin;
  for (int i = 0; i < N; i++) {
    double rx = (double)rng() / rng.max();
    double ry = (double)rng() / rng.max();
    double x = xmin + rx * w;
    double y = ymin + ry * h;
    bool fl = true;
    for (int k = 0; k < 3; k++) {
      double dx = x - c[k].x;
      double dy = y - c[k].y;
      if (dx * dx + dy * dy > c[k].r2) {
        fl = false;
        break;
      }
    }
    if (fl)
      M++;
  }
  return (double)M / N * (w * h);
}

int main() {
  Circle c[3] = {{1.0, 1.0, 1.0},
                 {1.5, 2.0, (sqrt(5.0) / 2.0) * (sqrt(5.0) / 2.0)},
                 {2.0, 1.5, (sqrt(5.0) / 2.0) * (sqrt(5.0) / 2.0)}};
  double S_exact = 0.25 * M_PI + 1.25 * asin(0.8) - 1.0;
  double xn1 = 0.7, xn2 = 2.2;
  double yn1 = 0.7, yn2 = 2.2;
  double xw1 = 0.0, xw2 = 3.2;
  double yw1 = 0.0, yw2 = 3.2;
  std::mt19937_64 rng(123456789);
  std::cout << "N,S_wide,Err_wide,S_narrow,Err_narrow\n";
  for (int N = 100; N <= 100000; N += 500) {
    double S_wide = area(N, xw1, xw2, yw1, yw2, c, rng);
    double S_narrow = area(N, xn1, xn2, yn1, yn2, c, rng);
    double err_wide = std::abs(S_wide - S_exact) / S_exact;
    double err_narrow = std::abs(S_narrow - S_exact) / S_exact;
    std::cout << N << "," << S_wide << "," << err_wide << "," << S_narrow << "," << err_narrow << "\n";
  }
  return 0;
}
