// Fold Expressions（畳み込み式）のサンプルコード
// このファイルは写経用です。コードを理解しながら写経してください。

#include <iostream>
#include <string>
#include <vector>

// ============================================================================
// 1. 基本的なFold Expressions
// ============================================================================

// 右畳み込み: (args + ...)
// 展開: a + (b + (c + d))
template <typename... Args>
auto sum_right(Args... args) {
  return (args + ...);
}

// 左畳み込み: (... + args)
// 展開: ((a + b) + c) + d
template <typename... Args>
auto sum_left(Args... args) {
  return (... + args);
}

// 初期値付き右畳み込み: (init + ... + args)
// 展開: init + (a + (b + (c + d)))
template <typename... Args>
auto sum_with_init(Args... args) {
  return (0 + ... + args);
}

void basic_examples() {
  std::cout << "=== 基本的なFold Expressions ===" << std::endl;

  // 右畳み込み
  std::cout << "sum_right(1, 2, 3, 4, 5) = " << sum_right(1, 2, 3, 4, 5) << std::endl;

  // 左畳み込み
  std::cout << "sum_left(1, 2, 3, 4, 5) = " << sum_left(1, 2, 3, 4, 5) << std::endl;

  // 初期値付き
  std::cout << "sum_with_init(1, 2, 3, 4, 5) = " << sum_with_init(1, 2, 3, 4, 5) << std::endl;

  // 空の場合は初期値が必要
  std::cout << "sum_with_init() = " << sum_with_init() << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 2. 様々な演算子
// ============================================================================

// 積
template <typename... Args>
auto multiply(Args... args) {
  return (args * ...);
}

// すべてがtrueか判定（論理AND）
template <typename... Args>
bool all_true(Args... args) {
  return (args && ...);
}

// いずれかがtrueか判定（論理OR）
template <typename... Args>
bool any_true(Args... args) {
  return (args || ...);
}

void operator_examples() {
  std::cout << "=== 様々な演算子 ===" << std::endl;

  // 積
  std::cout << "multiply(2, 3, 4) = " << multiply(2, 3, 4) << std::endl;

  // 論理AND
  std::cout << "all_true(true, true, true) = " << all_true(true, true, true) << std::endl;
  std::cout << "all_true(true, false, true) = " << all_true(true, false, true) << std::endl;

  // 論理OR
  std::cout << "any_true(false, false, true) = " << any_true(false, false, true) << std::endl;
  std::cout << "any_true(false, false, false) = " << any_true(false, false, false) << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 3. カンマ演算子を使った副作用
// ============================================================================

// 可変長引数をすべて出力
template <typename... Args>
void print_all(Args... args) {
  (std::cout << ... << args) << std::endl;
}

// 各引数を改行付きで出力
template <typename... Args>
void print_each(Args... args) {
  ((std::cout << args << std::endl), ...);
}

void comma_operator_examples() {
  std::cout << "=== カンマ演算子 ===" << std::endl;

  std::cout << "print_all: ";
  print_all(1, " + ", 2, " = ", 3);

  std::cout << "print_each:" << std::endl;
  print_each("First", "Second", "Third");

  std::cout << std::endl;
}

// ============================================================================
// 4. 文字列連結
// ============================================================================

template <typename... Args>
std::string concatenate(Args... args) {
  std::string result;
  ((result += args), ...);
  return result;
}

// スペース区切りで連結
template <typename... Args>
std::string join_with_space(Args... args) {
  std::string result;
  auto add = [&result, first = true](const auto& arg) mutable {
    if (!first) result += " ";
    result += arg;
    first = false;
  };
  (add(args), ...);
  return result;
}

void string_concatenation_examples() {
  std::cout << "=== 文字列連結 ===" << std::endl;

  std::cout << "concatenate: "
            << concatenate("Hello", " ", "World", "!") << std::endl;

  std::cout << "join_with_space: "
            << join_with_space("C++17", "Fold", "Expressions") << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 5. コンテナへの挿入
// ============================================================================

template <typename Container, typename... Args>
void push_back_all(Container& container, Args... args) {
  (container.push_back(args), ...);
}

void container_examples() {
  std::cout << "=== コンテナへの挿入 ===" << std::endl;

  std::vector<int> vec;
  push_back_all(vec, 1, 2, 3, 4, 5);

  std::cout << "Vector: ";
  for (int x : vec) {
    std::cout << x << " ";
  }
  std::cout << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 6. 関数呼び出し
// ============================================================================

// 各引数に対して関数を適用
template <typename Func, typename... Args>
void apply_to_all(Func func, Args... args) {
  (func(args), ...);
}

void function_call_examples() {
  std::cout << "=== 関数呼び出し ===" << std::endl;

  auto print_doubled = [](int x) {
    std::cout << x * 2 << " ";
  };

  std::cout << "各要素を2倍にして出力: ";
  apply_to_all(print_doubled, 1, 2, 3, 4, 5);
  std::cout << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 7. 述語の結合
// ============================================================================

// すべての述語がtrueを返すか判定
template <typename T, typename... Predicates>
bool all_match(T value, Predicates... predicates) {
  return (predicates(value) && ...);
}

// いずれかの述語がtrueを返すか判定
template <typename T, typename... Predicates>
bool any_match(T value, Predicates... predicates) {
  return (predicates(value) || ...);
}

void predicate_examples() {
  std::cout << "=== 述語の結合 ===" << std::endl;

  auto is_positive = [](int x) { return x > 0; };
  auto is_even = [](int x) { return x % 2 == 0; };
  auto is_less_than_100 = [](int x) { return x < 100; };

  int value = 42;

  std::cout << "値42は正かつ偶数かつ100未満か: "
            << all_match(value, is_positive, is_even, is_less_than_100)
            << std::endl;

  std::cout << "値42は正または100以上か: "
            << any_match(value, is_positive, is_less_than_100)
            << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 8. 比較演算
// ============================================================================

// すべての引数が等しいか判定
template <typename T, typename... Args>
bool all_equal(T first, Args... args) {
  return ((first == args) && ...);
}

// すべての引数が昇順か判定
template <typename First, typename... Rest>
bool is_sorted(First first, Rest... rest) {
  return ((first < rest) && ...);
}

void comparison_examples() {
  std::cout << "=== 比較演算 ===" << std::endl;

  std::cout << "all_equal(5, 5, 5, 5): " << all_equal(5, 5, 5, 5) << std::endl;
  std::cout << "all_equal(5, 5, 6, 5): " << all_equal(5, 5, 6, 5) << std::endl;

  std::cout << "is_sorted(1, 2, 3, 4, 5): " << is_sorted(1, 2, 3, 4, 5) << std::endl;
  std::cout << "is_sorted(1, 3, 2, 4, 5): " << is_sorted(1, 3, 2, 4, 5) << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "C++17 Fold Expressions のサンプル\n" << std::endl;

  basic_examples();
  operator_examples();
  comma_operator_examples();
  string_concatenation_examples();
  container_examples();
  function_call_examples();
  predicate_examples();
  comparison_examples();

  std::cout << "全てのサンプルが完了しました！" << std::endl;
  return 0;
}
