// if/switch初期化式の演習

#include <iostream>
#include <string>
#include <unordered_map>

// ============================================================================
// 演習 1.2.1: キャッシュシステムの実装
// ============================================================================

// グローバルキャッシュ（計算結果を保存）
std::unordered_map<int, int> calculation_cache;

// 重い計算をシミュレート（単純に2乗を返す）
int expensive_calculation(int x) {
  std::cout << "  [計算中...] " << x << " の2乗を計算" << std::endl;
  return x * x;
}

void exercise_1_2_1() {
  std::cout << "=== 演習 1.2.1: キャッシュシステム ===" << std::endl;

  int input = 5;

  // TODO: if初期化式を使って、以下の処理を実装してください
  // 1. calculation_cacheからinputをキーにして検索
  // 2. キャッシュに存在する場合：
  //    - "キャッシュヒット！" と表示
  //    - キャッシュされた値を表示
  // 3. キャッシュに存在しない場合：
  //    - "キャッシュミス！" と表示
  //    - expensive_calculation(input)を呼び出して計算
  //    - 結果をキャッシュに保存
  //    - 計算結果を表示

  // ヒント: if (auto it = calculation_cache.find(input); ...) { ... }

  std::cout << "\n2回目の呼び出し（キャッシュヒットするはず）:" << std::endl;

  // TODO: もう一度同じコードを実行してください
  // 今度はキャッシュヒットするはずです

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習: switch初期化式を使った文字列分類
// ============================================================================

enum class StringType { Empty, Short, Medium, Long };

StringType classify_string(const std::string& str) {
  // TODO: 文字列の長さに応じてStringTypeを返してください
  // - 0文字: Empty
  // - 1-5文字: Short
  // - 6-20文字: Medium
  // - 21文字以上: Long
  return StringType::Empty;  // TODO: 実装してください
}

void bonus_exercise() {
  std::cout << "=== ボーナス演習: 文字列分類 ===" << std::endl;

  std::string test = "Hello, World!";

  // TODO: switch初期化式を使って、文字列を分類してください
  // ヒント: switch (StringType type = classify_string(test); type) { ... }

  // TODO: それぞれのケースで適切なメッセージを表示してください

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "if/switch初期化式の演習\n" << std::endl;

  exercise_1_2_1();
  bonus_exercise();

  std::cout << "演習が完了しました！" << std::endl;
  return 0;
}
