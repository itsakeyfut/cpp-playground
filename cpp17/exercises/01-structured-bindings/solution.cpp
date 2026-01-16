// 構造化束縛（Structured Bindings）の演習 - 解答例

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <tuple>

// ============================================================================
// 演習 1.1.1: 3D空間の点を表す構造体
// ============================================================================

struct Point3D {
  int x;
  int y;
  int z;
};

void exercise_1_1_1() {
  std::cout << "=== 演習 1.1.1: Point3Dの分解 ===" << std::endl;

  Point3D p{10, 20, 30};

  // 構造化束縛で分解
  auto [x, y, z] = p;

  std::cout << "Point: (" << x << ", " << y << ", " << z << ")" << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 演習 1.1.2: RGB値を格納したmapのイテレーション
// ============================================================================

void exercise_1_1_2() {
  std::cout << "=== 演習 1.1.2: RGB値のmapをイテレート ===" << std::endl;

  std::map<std::string, std::tuple<int, int, int>> colors = {
      {"Red", {255, 0, 0}},
      {"Green", {0, 255, 0}},
      {"Blue", {0, 0, 255}},
      {"Purple", {128, 0, 128}},
      {"Orange", {255, 165, 0}}};

  // 方法1: 一度に全て分解
  for (const auto& [color_name, rgb_tuple] : colors) {
    auto [r, g, b] = rgb_tuple;
    std::cout << color_name << ": RGB(" << r << ", " << g << ", " << b << ")"
              << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習: 複数の戻り値を持つ関数
// ============================================================================

std::tuple<int, int, double> calculate_stats(int a, int b, int c) {
  int min_val = std::min({a, b, c});
  int max_val = std::max({a, b, c});
  double avg = (a + b + c) / 3.0;

  return std::make_tuple(min_val, max_val, avg);
}

void bonus_exercise() {
  std::cout << "=== ボーナス演習: 統計関数 ===" << std::endl;

  auto [min, max, avg] = calculate_stats(10, 20, 15);

  std::cout << "Min: " << min << ", Max: " << max << ", Average: " << avg
            << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "構造化束縛の演習 - 解答例\n" << std::endl;

  exercise_1_1_1();
  exercise_1_1_2();
  bonus_exercise();

  std::cout << "お疲れ様でした！" << std::endl;
  return 0;
}
