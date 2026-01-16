// constexpr if の演習 - 解答例

#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

// ============================================================================
// 演習 1.4.1: シリアライゼーション関数
// ============================================================================

template <typename T>
std::vector<uint8_t> serialize(const T& value) {
  std::vector<uint8_t> result;

  if constexpr (std::is_integral_v<T>) {
    // 整数型: バイト列として保存
    for (size_t i = 0; i < sizeof(T); ++i) {
      result.push_back(static_cast<uint8_t>((value >> (i * 8)) & 0xFF));
    }
  } else if constexpr (std::is_same_v<T, std::string>) {
    // 文字列型: 長さ + データ
    size_t len = value.size();
    // 長さを4バイトで保存
    for (size_t i = 0; i < 4; ++i) {
      result.push_back(static_cast<uint8_t>((len >> (i * 8)) & 0xFF));
    }
    // データを保存
    for (char c : value) {
      result.push_back(static_cast<uint8_t>(c));
    }
  } else {
    // その他の型はサポートしない
    static_assert(!std::is_same_v<T, T>, "この型はシリアライズできません");
  }

  return result;
}

void exercise_1_4_1() {
  std::cout << "=== 演習 1.4.1: シリアライゼーション ===" << std::endl;

  // 整数をシリアライズ
  auto int_bytes = serialize(42);
  std::cout << "整数42をシリアライズ: ";
  for (auto byte : int_bytes) {
    std::cout << static_cast<int>(byte) << " ";
  }
  std::cout << std::endl;

  // 文字列をシリアライズ
  auto str_bytes = serialize(std::string("test"));
  std::cout << "文字列\"test\"をシリアライズ: ";
  for (auto byte : str_bytes) {
    std::cout << static_cast<int>(byte) << " ";
  }
  std::cout << "(最初の4バイトが長さ、残りがデータ)" << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 演習 1.4.2: 型に応じた演算
// ============================================================================

template <typename T>
auto calculate(T value) {
  if constexpr (std::is_integral_v<T>) {
    return value * 2;
  } else if constexpr (std::is_floating_point_v<T>) {
    return value * 2.5;
  } else {
    static_assert(!std::is_same_v<T, T>, "この型は計算できません");
  }
}

void exercise_1_4_2() {
  std::cout << "=== 演習 1.4.2: 型に応じた演算 ===" << std::endl;

  auto int_result = calculate(10);
  std::cout << "整数10の計算結果（×2）: " << int_result << std::endl;

  auto float_result = calculate(3.14);
  std::cout << "浮動小数点3.14の計算結果（×2.5）: " << float_result << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習: 型の情報を表示
// ============================================================================

template <typename T>
void describe_type(T value) {
  std::cout << "値: " << value << " の型情報:" << std::endl;

  // 整数型かどうか
  if constexpr (std::is_integral_v<T>) {
    std::cout << "  - 整数型" << std::endl;

    // 符号付きかどうか
    if constexpr (std::is_signed_v<T>) {
      std::cout << "  - 符号付き" << std::endl;
    } else {
      std::cout << "  - 符号なし" << std::endl;
    }
  } else if constexpr (std::is_floating_point_v<T>) {
    std::cout << "  - 浮動小数点型" << std::endl;
  } else if constexpr (std::is_same_v<T, std::string>) {
    std::cout << "  - std::string型" << std::endl;
  } else {
    std::cout << "  - その他の型" << std::endl;
  }

  // サイズ
  std::cout << "  - サイズ: " << sizeof(T) << "バイト" << std::endl;

  std::cout << std::endl;
}

void bonus_exercise() {
  std::cout << "=== ボーナス演習: 型の情報表示 ===" << std::endl;

  describe_type(42);
  describe_type(-10);
  describe_type(3.14);
  describe_type(std::string("hello"));

  // 符号なし整数
  unsigned int u = 100;
  describe_type(u);
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "constexpr if の演習 - 解答例\n" << std::endl;

  exercise_1_4_1();
  exercise_1_4_2();
  bonus_exercise();

  std::cout << "お疲れ様でした！" << std::endl;
  return 0;
}
