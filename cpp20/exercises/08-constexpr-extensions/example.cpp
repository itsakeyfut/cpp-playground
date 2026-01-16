// constexpr拡張とconstevalのサンプルコード
// このファイルは写経用です。コードを理解しながら写経してください。

#include <array>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ============================================================================
// 1. constexpr仮想関数（C++20の新機能）
// ============================================================================

struct Shape {
  constexpr virtual ~Shape() = default;
  constexpr virtual double area() const = 0;
};

struct Circle : Shape {
  double radius;

  constexpr explicit Circle(double r) : radius(r) {}

  constexpr double area() const override { return 3.14159 * radius * radius; }
};

struct Rectangle : Shape {
  double width, height;

  constexpr Rectangle(double w, double h) : width(w), height(h) {}

  constexpr double area() const override { return width * height; }
};

constexpr double calculate_total_area() {
  // C++20: constexpr文脈で仮想関数を呼び出せる
  Circle c(5.0);
  Rectangle r(4.0, 6.0);

  return c.area() + r.area();
}

void constexpr_virtual_function() {
  std::cout << "=== constexpr仮想関数 ===" << std::endl;

  // コンパイル時に計算
  constexpr double total = calculate_total_area();
  std::cout << "Total area (compile-time): " << total << std::endl;

  // ランタイムでも使用可能
  Circle c(3.0);
  std::cout << "Circle area (runtime): " << c.area() << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 2. consteval（即時関数）
// ============================================================================

// constevalは必ずコンパイル時に評価される
consteval int square_consteval(int x) { return x * x; }

// constexprはコンパイル時でもランタイムでも使える
constexpr int square_constexpr(int x) { return x * x; }

void consteval_example() {
  std::cout << "=== consteval（即時関数） ===" << std::endl;

  // constevalはコンパイル時のみ
  constexpr int a = square_consteval(5);  // OK
  std::cout << "square_consteval(5): " << a << std::endl;

  // ランタイム値では使えない
  // int runtime_value = 5;
  // int b = square_consteval(runtime_value);  // エラー！

  // constexprはランタイムでも使える
  int runtime_value = 5;
  int c = square_constexpr(runtime_value);  // OK
  std::cout << "square_constexpr(runtime): " << c << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 3. constinit（静的初期化）
// ============================================================================

// constinitは静的変数の初期化を保証
constinit int global_value = 42;

// 通常の静的変数（初期化順序が不定）
static int normal_static = 100;

void constinit_example() {
  std::cout << "=== constinit（静的初期化） ===" << std::endl;

  std::cout << "global_value (constinit): " << global_value << std::endl;
  std::cout << "normal_static: " << normal_static << std::endl;

  // constinitは実行時に変更可能（constとは異なる）
  global_value = 100;
  std::cout << "global_value after modification: " << global_value
            << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 4. コンパイル時の動的メモリ確保（C++20）
// ============================================================================

constexpr int sum_vector() {
  // C++20: constexpr文脈でstd::vectorが使える
  std::vector<int> v = {1, 2, 3, 4, 5};
  int sum = 0;
  for (int x : v) {
    sum += x;
  }
  return sum;
}

void constexpr_dynamic_memory() {
  std::cout << "=== constexpr動的メモリ確保 ===" << std::endl;

  // コンパイル時に計算
  constexpr int total = sum_vector();
  std::cout << "Sum (compile-time): " << total << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 5. 実用例：ルックアップテーブルの生成
// ============================================================================

// コンパイル時に乗法テーブルを生成
constexpr auto generate_multiplication_table() {
  std::array<std::array<int, 10>, 10> table{};
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      table[i][j] = (i + 1) * (j + 1);
    }
  }
  return table;
}

// コンパイル時に計算済み
constexpr auto multiplication_table = generate_multiplication_table();

void lookup_table_example() {
  std::cout << "=== ルックアップテーブル ===" << std::endl;

  std::cout << "九九の一部:" << std::endl;
  for (int i = 0; i < 5; ++i) {
    for (int j = 0; j < 5; ++j) {
      std::cout << multiplication_table[i][j] << "\t";
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// 6. ゲーム開発例：ダメージ計算テーブル
// ============================================================================

constexpr auto generate_damage_table() {
  std::array<int, 100> table{};
  for (int level = 0; level < 100; ++level) {
    // 基礎ダメージ10 + レベル×5
    table[level] = 10 + level * 5;
  }
  return table;
}

constexpr auto damage_table = generate_damage_table();

int get_damage(int level) {
  if (level < 0 || level >= 100) return 0;
  return damage_table[level];
}

void game_damage_table() {
  std::cout << "=== ゲーム用ダメージテーブル ===" << std::endl;

  std::cout << "レベル別ダメージ:" << std::endl;
  for (int level : {1, 10, 25, 50, 99}) {
    std::cout << "Level " << level << ": " << get_damage(level) << " damage"
              << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// 7. constexpr文字列処理
// ============================================================================

constexpr bool is_palindrome(std::string_view str) {
  int left = 0;
  int right = str.size() - 1;

  while (left < right) {
    if (str[left] != str[right]) {
      return false;
    }
    ++left;
    --right;
  }
  return true;
}

void constexpr_string_processing() {
  std::cout << "=== constexpr文字列処理 ===" << std::endl;

  // コンパイル時にチェック
  constexpr bool result1 = is_palindrome("racecar");
  constexpr bool result2 = is_palindrome("hello");

  std::cout << "\"racecar\" is palindrome: " << result1 << std::endl;
  std::cout << "\"hello\" is palindrome: " << result2 << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 8. consteval vs constexpr の使い分け
// ============================================================================

// コンパイル時専用の計算（最適化重視）
consteval int fibonacci_consteval(int n) {
  if (n <= 1) return n;
  return fibonacci_consteval(n - 1) + fibonacci_consteval(n - 2);
}

// ランタイムでも使える計算
constexpr int fibonacci_constexpr(int n) {
  if (n <= 1) return n;
  return fibonacci_constexpr(n - 1) + fibonacci_constexpr(n - 2);
}

void consteval_vs_constexpr() {
  std::cout << "=== consteval vs constexpr ===" << std::endl;

  // constevalはコンパイル時のみ
  constexpr int fib10_eval = fibonacci_consteval(10);
  std::cout << "fibonacci_consteval(10): " << fib10_eval << std::endl;

  // constexprはランタイムでも使える
  int n = 10;
  int fib10_expr = fibonacci_constexpr(n);
  std::cout << "fibonacci_constexpr(10) at runtime: " << fib10_expr
            << std::endl;

  std::cout << "\n使い分けのポイント:" << std::endl;
  std::cout << "- consteval: コンパイル時専用、より厳格な最適化"
            << std::endl;
  std::cout << "- constexpr: 柔軟性が高い、ランタイムでも使用可能"
            << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "C++20 constexpr拡張とconsteval のサンプル\n" << std::endl;

  constexpr_virtual_function();
  consteval_example();
  constinit_example();
  constexpr_dynamic_memory();
  lookup_table_example();
  game_damage_table();
  constexpr_string_processing();
  consteval_vs_constexpr();

  std::cout << "全てのサンプルが完了しました！" << std::endl;
  return 0;
}
