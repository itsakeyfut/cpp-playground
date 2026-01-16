// constexpr拡張とconstevalの演習
// TODOコメントを埋めて、プログラムを完成させてください。

#include <array>
#include <iostream>
#include <string>
#include <vector>

// ============================================================================
// 演習 2.5.4.1: constexpr仮想関数
// ============================================================================

// TODO: Shape基底クラスを定義してください
// - constexpr仮想デストラクタ
// - constexpr仮想関数 area() を持つ

// TODO: Circle派生クラスを定義してください
// - メンバ変数: radius
// - constexpr コンストラクタ
// - area() をオーバーライド（円の面積 = π * r^2、π ≈ 3.14159）

// TODO: Square派生クラスを定義してください
// - メンバ変数: side
// - constexpr コンストラクタ
// - area() をオーバーライド（正方形の面積 = side * side）

// TODO: コンパイル時に複数の図形の面積合計を計算する関数
// constexpr double calculate_total_area() {
//   // Circle、Squareのインスタンスを作成して合計を返す
// }

void exercise_2_5_4_1() {
  std::cout << "=== 演習 2.5.4.1: constexpr仮想関数 ===" << std::endl;

  // TODO: コンパイル時に面積を計算
  // constexpr double total = calculate_total_area();
  // std::cout << "Total area: " << total << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 演習 2.5.4.2: constevalでフィボナッチ数
// ============================================================================

// TODO: constevalを使ってフィボナッチ数を計算する関数を実装
// consteval int fibonacci(int n) {
//   // 基底ケース: n <= 1 のとき n を返す
//   // 再帰ケース: fibonacci(n-1) + fibonacci(n-2)
// }

void exercise_2_5_4_2() {
  std::cout << "=== 演習 2.5.4.2: constevalでフィボナッチ数 ===" << std::endl;

  // TODO: コンパイル時にフィボナッチ数を計算
  // constexpr int fib5 = fibonacci(5);
  // constexpr int fib10 = fibonacci(10);
  // constexpr int fib15 = fibonacci(15);

  // std::cout << "fibonacci(5): " << fib5 << std::endl;
  // std::cout << "fibonacci(10): " << fib10 << std::endl;
  // std::cout << "fibonacci(15): " << fib15 << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 演習 2.5.4.3: ゲーム用ダメージ計算テーブル
// ============================================================================

// TODO: ダメージ計算テーブルを生成する関数を実装
// 仕様:
// - レベル0〜99の100レベル分
// - ダメージ = 基礎値(20) + レベル * 成長率(3) + レベル^2 / 10
// constexpr auto generate_damage_table() {
//   std::array<int, 100> table{};
//   for (int level = 0; level < 100; ++level) {
//     table[level] = ...;  // 上記の式で計算
//   }
//   return table;
// }

// TODO: コンパイル時にテーブルを生成
// constexpr auto damage_table = generate_damage_table();

// TODO: レベルからダメージを取得する関数
// int get_damage(int level) {
//   if (level < 0 || level >= 100) return 0;
//   return damage_table[level];
// }

void exercise_2_5_4_3() {
  std::cout << "=== 演習 2.5.4.3: ゲーム用ダメージテーブル ===" << std::endl;

  // TODO: いくつかのレベルでダメージを表示
  // for (int level : {1, 10, 25, 50, 99}) {
  //   std::cout << "Level " << level << ": " << get_damage(level) << " damage"
  //             << std::endl;
  // }

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習: コンパイル時のハッシュ計算
// ============================================================================

// TODO: 簡易的なハッシュ関数を実装（FNV-1a）
// consteval unsigned int hash_string(const char* str) {
//   unsigned int hash = 2166136261u;  // FNV offset basis
//   while (*str) {
//     hash ^= static_cast<unsigned int>(*str++);
//     hash *= 16777619u;  // FNV prime
//   }
//   return hash;
// }

void bonus_exercise() {
  std::cout << "=== ボーナス演習: コンパイル時ハッシュ ===" << std::endl;

  // TODO: 文字列のハッシュ値をコンパイル時に計算
  // constexpr unsigned int hash1 = hash_string("Player");
  // constexpr unsigned int hash2 = hash_string("Enemy");
  // constexpr unsigned int hash3 = hash_string("Item");

  // std::cout << "Hash(\"Player\"): 0x" << std::hex << hash1 << std::endl;
  // std::cout << "Hash(\"Enemy\"): 0x" << std::hex << hash2 << std::endl;
  // std::cout << "Hash(\"Item\"): 0x" << std::hex << hash3 << std::endl;
  // std::cout << std::dec;  // 10進数に戻す

  // 用途: コンパイル時に文字列をハッシュ値に変換して、
  // ランタイムでは整数比較のみで高速化

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "constexpr拡張とconstevalの演習\n" << std::endl;

  exercise_2_5_4_1();
  exercise_2_5_4_2();
  exercise_2_5_4_3();
  bonus_exercise();

  std::cout << "演習が完了しました！" << std::endl;
  std::cout << "solution.cppと比較して、答え合わせをしましょう。" << std::endl;
  return 0;
}
