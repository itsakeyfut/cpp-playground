// std::variantのサンプルコード
// このファイルは写経用です。コードを理解しながら写経してください。

#include <iostream>
#include <string>
#include <variant>
#include <vector>

// ============================================================================
// 1. 基本的なstd::variantの使い方
// ============================================================================

void basic_examples() {
  std::cout << "=== 基本的なstd::variant ===" << std::endl;

  // Rustの enum Value { Int(i32), Float(f64), String(String) } に相当
  using Value = std::variant<int, double, std::string>;

  Value v = 42;  // int型で初期化
  std::cout << "v holds int: " << std::get<int>(v) << std::endl;

  v = 3.14;  // double型に変更
  std::cout << "v holds double: " << std::get<double>(v) << std::endl;

  v = "hello";  // string型に変更
  std::cout << "v holds string: " << std::get<std::string>(v) << std::endl;

  // 現在保持している型のインデックス
  std::cout << "v index: " << v.index() << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 2. 型の確認と取得
// ============================================================================

void type_checking() {
  std::cout << "=== 型の確認と取得 ===" << std::endl;

  using Value = std::variant<int, double, std::string>;
  Value v = 100;

  // holds_alternative: 指定した型を保持しているか確認
  if (std::holds_alternative<int>(v)) {
    std::cout << "v holds int: " << std::get<int>(v) << std::endl;
  }

  // get_if: ポインタで取得（型が違う場合はnullptr）
  if (auto* pval = std::get_if<int>(&v)) {
    std::cout << "v contains int value: " << *pval << std::endl;
  }

  if (auto* pval = std::get_if<double>(&v)) {
    std::cout << "v contains double value: " << *pval << std::endl;
  } else {
    std::cout << "v does not contain double" << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// 3. std::visit (Rustのmatchに相当)
// ============================================================================

void visit_example() {
  std::cout << "=== std::visit ===" << std::endl;

  using Value = std::variant<int, double, std::string>;

  std::vector<Value> values = {42, 3.14, "hello", 100, 2.718};

  for (const auto& v : values) {
    // visitは各型に対する処理を記述できる
    std::visit(
        [](const auto& arg) {
          using T = std::decay_t<decltype(arg)>;
          if constexpr (std::is_same_v<T, int>) {
            std::cout << "int: " << arg << std::endl;
          } else if constexpr (std::is_same_v<T, double>) {
            std::cout << "double: " << arg << std::endl;
          } else if constexpr (std::is_same_v<T, std::string>) {
            std::cout << "string: " << arg << std::endl;
          }
        },
        v);
  }

  std::cout << std::endl;
}

// ============================================================================
// 4. overloadedパターン (より洗練されたvisit)
// ============================================================================

// 複数のラムダを1つの関数オブジェクトにまとめるヘルパー
template <class... Ts>
struct overloaded : Ts... {
  using Ts::operator()...;
};
// C++17では推論ガイドが必要
template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

void overloaded_example() {
  std::cout << "=== overloadedパターン ===" << std::endl;

  using Value = std::variant<int, double, std::string>;

  std::vector<Value> values = {42, 3.14, "world", 99};

  for (const auto& v : values) {
    std::visit(
        overloaded{
            [](int i) { std::cout << "int: " << i << std::endl; },
            [](double d) { std::cout << "double: " << d << std::endl; },
            [](const std::string& s) {
              std::cout << "string: " << s << std::endl;
            }},
        v);
  }

  std::cout << std::endl;
}

// ============================================================================
// 5. ゲームの状態マシン
// ============================================================================

struct StateIdle {
  std::string message = "Idle";
};
struct StateMoving {
  float velocity;
};
struct StateAttacking {
  int damage;
  std::string target;
};

using GameState = std::variant<StateIdle, StateMoving, StateAttacking>;

void state_machine_example() {
  std::cout << "=== 状態マシンの例 ===" << std::endl;

  std::vector<GameState> states = {
      StateIdle{},
      StateMoving{5.5f},
      StateAttacking{10, "Enemy"},
      StateIdle{"Resting"}};

  for (const auto& state : states) {
    std::visit(
        overloaded{
            [](const StateIdle& s) {
              std::cout << "State: Idle (" << s.message << ")" << std::endl;
            },
            [](const StateMoving& s) {
              std::cout << "State: Moving (velocity=" << s.velocity << ")"
                        << std::endl;
            },
            [](const StateAttacking& s) {
              std::cout << "State: Attacking " << s.target
                        << " (damage=" << s.damage << ")" << std::endl;
            }},
        state);
  }

  std::cout << std::endl;
}

// ============================================================================
// 6. 戻り値を持つvisit
// ============================================================================

std::string describe_value(const std::variant<int, double, std::string>& v) {
  return std::visit(
      overloaded{
          [](int i) { return "Integer: " + std::to_string(i); },
          [](double d) { return "Double: " + std::to_string(d); },
          [](const std::string& s) { return "String: " + s; }},
      v);
}

void visit_with_return() {
  std::cout << "=== 戻り値を持つvisit ===" << std::endl;

  using Value = std::variant<int, double, std::string>;

  std::vector<Value> values = {123, 45.67, "test"};

  for (const auto& v : values) {
    std::cout << describe_value(v) << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// 7. エラーハンドリングの例
// ============================================================================

struct Success {
  int value;
};
struct Error {
  std::string message;
};

using Result = std::variant<Success, Error>;

Result divide(int a, int b) {
  if (b == 0) {
    return Error{"Division by zero"};
  }
  return Success{a / b};
}

void error_handling_example() {
  std::cout << "=== エラーハンドリング ===" << std::endl;

  auto result1 = divide(10, 2);
  auto result2 = divide(10, 0);

  // 結果を処理
  auto handle_result = [](const Result& r) {
    std::visit(
        overloaded{
            [](const Success& s) {
              std::cout << "Success: " << s.value << std::endl;
            },
            [](const Error& e) {
              std::cout << "Error: " << e.message << std::endl;
            }},
        r);
  };

  handle_result(result1);
  handle_result(result2);

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "C++17 std::variantのサンプル\n" << std::endl;

  basic_examples();
  type_checking();
  visit_example();
  overloaded_example();
  state_machine_example();
  visit_with_return();
  error_handling_example();

  std::cout << "全てのサンプルが完了しました！" << std::endl;
  return 0;
}
