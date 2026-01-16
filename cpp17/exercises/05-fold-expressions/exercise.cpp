// Fold Expressions（畳み込み式）の演習
// TODOコメントを埋めて、プログラムを完成させてください。

#include <iostream>
#include <string>
#include <vector>

// ============================================================================
// 演習 1.5.1: 文字列連結
// ============================================================================

// TODO: concatenate関数を実装してください
// 要件: 任意個の文字列を連結して返す
// ヒント: fold expressionとカンマ演算子を使用

template <typename... Args>
std::string concatenate(Args... args) {
  // TODO: fold expressionを使って実装

  // ヒント1: std::string result を用意
  // ヒント2: ((result += args), ...) でカンマ演算子による畳み込み
  // ヒント3: resultを返す

  return "";  // TODO: この行を置き換え
}

void exercise_1_5_1() {
  std::cout << "=== 演習 1.5.1: 文字列連結 ===" << std::endl;

  // TODO: concatenate関数を使って文字列を連結
  // 例: auto result = concatenate("Hello", " ", "C++", "17");

  // TODO: 結果を出力

  std::cout << std::endl;
}

// ============================================================================
// 演習 1.5.2: 述語の結合
// ============================================================================

// TODO: all_predicates関数を実装してください
// 要件: 任意個の述語をANDで結合し、値に対してすべての述語が真かチェック
// ヒント: (predicates(value) && ...)

template <typename T, typename... Predicates>
bool all_predicates(T value, Predicates... predicates) {
  // TODO: fold expressionを使って実装

  // ヒント: return (predicates(value) && ...);

  return false;  // TODO: この行を置き換え
}

void exercise_1_5_2() {
  std::cout << "=== 演習 1.5.2: 述語の結合 ===" << std::endl;

  // TODO: ラムダ式で述語を定義
  // 例: auto is_positive = [](int x) { return x > 0; };
  //     auto is_even = [](int x) { return x % 2 == 0; };
  //     auto is_small = [](int x) { return x < 100; };

  // TODO: all_predicates関数を使ってテスト
  // 例: bool result = all_predicates(42, is_positive, is_even, is_small);

  // TODO: 結果を出力

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習 1: 合計と平均
// ============================================================================

// TODO: sum関数を実装
template <typename... Args>
auto sum(Args... args) {
  // TODO: fold expressionで合計を計算
  // ヒント: return (args + ...);
}

// TODO: average関数を実装
template <typename... Args>
double average(Args... args) {
  // TODO: sum関数を使って平均を計算
  // ヒント: return static_cast<double>(sum(args...)) / sizeof...(args);
}

void bonus_exercise_1() {
  std::cout << "=== ボーナス演習 1: 合計と平均 ===" << std::endl;

  // TODO: sum関数とaverage関数をテスト
  // 例: auto s = sum(1, 2, 3, 4, 5);
  //     auto a = average(1, 2, 3, 4, 5);

  // TODO: 結果を出力

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習 2: すべてを出力
// ============================================================================

// TODO: print_all関数を実装
// 要件: 可変長引数をスペース区切りで出力
template <typename... Args>
void print_all(Args... args) {
  // TODO: fold expressionを使って実装

  // ヒント1: (std::cout << ... << args) では区切りがない
  // ヒント2: スペースを入れるには工夫が必要
  //          例: ((std::cout << args << " "), ...);
}

void bonus_exercise_2() {
  std::cout << "=== ボーナス演習 2: すべてを出力 ===" << std::endl;

  // TODO: print_all関数を使って様々な型を出力
  // 例: print_all(1, 2.5, "hello", 'A');

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習 3: コンテナに追加
// ============================================================================

// TODO: append_all関数を実装
// 要件: 可変長引数をすべてコンテナに追加
template <typename Container, typename... Args>
void append_all(Container& container, Args... args) {
  // TODO: fold expressionを使って実装

  // ヒント: (container.push_back(args), ...);
}

void bonus_exercise_3() {
  std::cout << "=== ボーナス演習 3: コンテナに追加 ===" << std::endl;

  // TODO: std::vector<int>を作成し、append_all関数で要素を追加
  // 例: std::vector<int> vec;
  //     append_all(vec, 1, 2, 3, 4, 5);

  // TODO: ベクトルの内容を出力

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "Fold Expressions の演習\n" << std::endl;

  exercise_1_5_1();
  exercise_1_5_2();
  bonus_exercise_1();
  bonus_exercise_2();
  bonus_exercise_3();

  std::cout << "演習が完了しました！" << std::endl;
  std::cout << "solution.cppと比較して、答え合わせをしましょう。" << std::endl;
  return 0;
}
