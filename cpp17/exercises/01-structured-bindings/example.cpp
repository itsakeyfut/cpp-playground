// 構造化束縛（Structured Bindings）のサンプルコード
// このファイルは写経用です。コードを理解しながら写経してください。

#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <utility>

// ============================================================================
// 1. 基本的な構造化束縛
// ============================================================================

void basic_examples() {
  std::cout << "=== 基本的な構造化束縛 ===" << std::endl;

  // pair の分解
  auto [x, y] = std::make_pair(1, 2);
  std::cout << "x = " << x << ", y = " << y << std::endl;

  // tuple の分解
  auto [a, b, c] = std::make_tuple(10, 3.14, "hello");
  std::cout << "a = " << a << ", b = " << b << ", c = " << c << std::endl;

  // 配列の分解
  int arr[] = {100, 200, 300};
  auto [first, second, third] = arr;
  std::cout << "first = " << first << ", second = " << second
            << ", third = " << third << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 2. 構造体の分解
// ============================================================================

struct Point {
  int x;
  int y;
  int z;
};

void struct_example() {
  std::cout << "=== 構造体の分解 ===" << std::endl;

  Point p{1, 2, 3};
  auto [px, py, pz] = p;
  std::cout << "Point: (" << px << ", " << py << ", " << pz << ")"
            << std::endl;

  // const参照で受け取る
  const auto& [rx, ry, rz] = p;
  std::cout << "Point (const ref): (" << rx << ", " << ry << ", " << rz << ")"
            << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 3. mapのイテレーション（最も実用的な使い方）
// ============================================================================

void map_iteration_example() {
  std::cout << "=== mapのイテレーション ===" << std::endl;

  std::map<std::string, int> scores = {
      {"Alice", 100}, {"Bob", 85}, {"Carol", 92}};

  // 従来の方法（C++14以前）
  std::cout << "従来の方法:" << std::endl;
  for (const auto& pair : scores) {
    std::cout << pair.first << ": " << pair.second << std::endl;
  }

  std::cout << "\n構造化束縛を使った方法:" << std::endl;
  // C++17の構造化束縛
  for (const auto& [name, score] : scores) {
    std::cout << name << ": " << score << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// 4. 複雑な例：ネストしたデータ構造
// ============================================================================

void complex_example() {
  std::cout << "=== 複雑な例：RGB値を格納したmap ===" << std::endl;

  std::map<std::string, std::tuple<int, int, int>> colors = {
      {"Red", {255, 0, 0}},
      {"Green", {0, 255, 0}},
      {"Blue", {0, 0, 255}},
      {"Yellow", {255, 255, 0}}};

  for (const auto& [color_name, rgb] : colors) {
    // tupleをさらに分解
    auto [r, g, b] = rgb;
    std::cout << color_name << ": RGB(" << r << ", " << g << ", " << b << ")"
              << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// 5. 関数の戻り値を分解
// ============================================================================

std::pair<int, int> divide_with_remainder(int dividend, int divisor) {
  return {dividend / divisor, dividend % divisor};
}

void return_value_example() {
  std::cout << "=== 関数の戻り値を分解 ===" << std::endl;

  auto [quotient, remainder] = divide_with_remainder(17, 5);
  std::cout << "17 ÷ 5 = " << quotient << " 余り " << remainder << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "C++17 構造化束縛のサンプル\n" << std::endl;

  basic_examples();
  struct_example();
  map_iteration_example();
  complex_example();
  return_value_example();

  std::cout << "全てのサンプルが完了しました！" << std::endl;
  return 0;
}
