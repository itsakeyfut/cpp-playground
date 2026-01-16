// Fold Expressions（畳み込み式）の演習 - 解答例

#include <iostream>
#include <string>
#include <vector>

// ============================================================================
// 演習 1.5.1: 文字列連結
// ============================================================================

template <typename... Args>
std::string concatenate(Args... args) {
  std::string result;
  ((result += args), ...);
  return result;
}

void exercise_1_5_1() {
  std::cout << "=== 演習 1.5.1: 文字列連結 ===" << std::endl;

  auto result1 = concatenate("Hello", " ", "C++", "17");
  std::cout << "結果1: " << result1 << std::endl;

  auto result2 = concatenate("Fold", " ", "Expressions", " ", "are", " ", "powerful!");
  std::cout << "結果2: " << result2 << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 演習 1.5.2: 述語の結合
// ============================================================================

template <typename T, typename... Predicates>
bool all_predicates(T value, Predicates... predicates) {
  return (predicates(value) && ...);
}

void exercise_1_5_2() {
  std::cout << "=== 演習 1.5.2: 述語の結合 ===" << std::endl;

  auto is_positive = [](int x) { return x > 0; };
  auto is_even = [](int x) { return x % 2 == 0; };
  auto is_small = [](int x) { return x < 100; };

  int value1 = 42;
  bool result1 = all_predicates(value1, is_positive, is_even, is_small);
  std::cout << "42は正、偶数、100未満か: " << std::boolalpha << result1 << std::endl;

  int value2 = -10;
  bool result2 = all_predicates(value2, is_positive, is_even, is_small);
  std::cout << "-10は正、偶数、100未満か: " << std::boolalpha << result2 << std::endl;

  int value3 = 101;
  bool result3 = all_predicates(value3, is_positive, is_small);
  std::cout << "101は正かつ100未満か: " << std::boolalpha << result3 << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習 1: 合計と平均
// ============================================================================

template <typename... Args>
auto sum(Args... args) {
  return (args + ...);
}

template <typename... Args>
double average(Args... args) {
  return static_cast<double>(sum(args...)) / sizeof...(args);
}

void bonus_exercise_1() {
  std::cout << "=== ボーナス演習 1: 合計と平均 ===" << std::endl;

  auto s = sum(1, 2, 3, 4, 5);
  std::cout << "1+2+3+4+5の合計: " << s << std::endl;

  auto a = average(1, 2, 3, 4, 5);
  std::cout << "1,2,3,4,5の平均: " << a << std::endl;

  auto s2 = sum(10.5, 20.3, 30.7);
  std::cout << "10.5+20.3+30.7の合計: " << s2 << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習 2: すべてを出力
// ============================================================================

template <typename... Args>
void print_all(Args... args) {
  ((std::cout << args << " "), ...);
  std::cout << std::endl;
}

void bonus_exercise_2() {
  std::cout << "=== ボーナス演習 2: すべてを出力 ===" << std::endl;

  std::cout << "様々な型の出力: ";
  print_all(1, 2.5, "hello", 'A', true);

  std::cout << "整数のみ: ";
  print_all(10, 20, 30, 40, 50);

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習 3: コンテナに追加
// ============================================================================

template <typename Container, typename... Args>
void append_all(Container& container, Args... args) {
  (container.push_back(args), ...);
}

void bonus_exercise_3() {
  std::cout << "=== ボーナス演習 3: コンテナに追加 ===" << std::endl;

  std::vector<int> vec;
  append_all(vec, 1, 2, 3, 4, 5);

  std::cout << "ベクトルの内容: ";
  for (int x : vec) {
    std::cout << x << " ";
  }
  std::cout << std::endl;

  // 文字列のベクトル
  std::vector<std::string> words;
  append_all(words, std::string("Hello"), std::string("Fold"), std::string("Expressions"));

  std::cout << "文字列ベクトル: ";
  for (const auto& w : words) {
    std::cout << w << " ";
  }
  std::cout << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "Fold Expressions の演習 - 解答例\n" << std::endl;

  exercise_1_5_1();
  exercise_1_5_2();
  bonus_exercise_1();
  bonus_exercise_2();
  bonus_exercise_3();

  std::cout << "お疲れ様でした！" << std::endl;
  return 0;
}
