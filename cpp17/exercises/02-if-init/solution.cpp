// if/switch初期化式の演習 - 解答例

#include <iostream>
#include <string>
#include <unordered_map>

// ============================================================================
// 演習 1.2.1: キャッシュシステムの実装
// ============================================================================

std::unordered_map<int, int> calculation_cache;

int expensive_calculation(int x) {
  std::cout << "  [計算中...] " << x << " の2乗を計算" << std::endl;
  return x * x;
}

void exercise_1_2_1() {
  std::cout << "=== 演習 1.2.1: キャッシュシステム ===" << std::endl;

  int input = 5;

  // if初期化式を使ったキャッシュ検索
  if (auto it = calculation_cache.find(input); it != calculation_cache.end()) {
    std::cout << "キャッシュヒット！" << std::endl;
    std::cout << input << " の2乗 = " << it->second << std::endl;
  } else {
    std::cout << "キャッシュミス！" << std::endl;
    int result = expensive_calculation(input);
    calculation_cache[input] = result;
    std::cout << input << " の2乗 = " << result << " (キャッシュに保存)"
              << std::endl;
  }

  std::cout << "\n2回目の呼び出し（キャッシュヒットするはず）:" << std::endl;

  // 2回目の呼び出し
  if (auto it = calculation_cache.find(input); it != calculation_cache.end()) {
    std::cout << "キャッシュヒット！" << std::endl;
    std::cout << input << " の2乗 = " << it->second << std::endl;
  } else {
    std::cout << "キャッシュミス！" << std::endl;
    int result = expensive_calculation(input);
    calculation_cache[input] = result;
    std::cout << input << " の2乗 = " << result << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習: switch初期化式を使った文字列分類
// ============================================================================

enum class StringType { Empty, Short, Medium, Long };

StringType classify_string(const std::string& str) {
  size_t len = str.length();
  if (len == 0)
    return StringType::Empty;
  if (len <= 5)
    return StringType::Short;
  if (len <= 20)
    return StringType::Medium;
  return StringType::Long;
}

void bonus_exercise() {
  std::cout << "=== ボーナス演習: 文字列分類 ===" << std::endl;

  std::string test = "Hello, World!";

  // switch初期化式を使った分類
  switch (StringType type = classify_string(test); type) {
    case StringType::Empty:
      std::cout << "空の文字列です" << std::endl;
      break;
    case StringType::Short:
      std::cout << "短い文字列です (1-5文字): " << test << std::endl;
      break;
    case StringType::Medium:
      std::cout << "中程度の文字列です (6-20文字): " << test << std::endl;
      break;
    case StringType::Long:
      std::cout << "長い文字列です (21文字以上): " << test << std::endl;
      break;
  }

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "if/switch初期化式の演習 - 解答例\n" << std::endl;

  exercise_1_2_1();
  bonus_exercise();

  std::cout << "お疲れ様でした！" << std::endl;
  return 0;
}
