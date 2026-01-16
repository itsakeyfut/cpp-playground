// constexpr if の演習
// TODOコメントを埋めて、プログラムを完成させてください。

#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

// ============================================================================
// 演習 1.4.1: シリアライゼーション関数
// ============================================================================

// TODO: serialize関数テンプレートを実装してください
// 要件:
// - 整数型（std::is_integral_v<T>）: そのままバイト列に変換
// - 文字列型（std::is_same_v<T, std::string>）: 長さ(4バイト) + データ
// - その他の型: static_assertでコンパイルエラー

template <typename T>
std::vector<uint8_t> serialize(const T& value) {
  std::vector<uint8_t> result;

  // TODO: constexpr ifを使って型に応じた処理を実装

  // ヒント1: 整数型の場合
  // if constexpr (std::is_integral_v<T>) {
  //   // valueを1バイトずつresultに追加
  // }

  // ヒント2: 文字列型の場合
  // else if constexpr (std::is_same_v<T, std::string>) {
  //   // 長さを4バイトで保存
  //   // データをresultに追加
  // }

  // ヒント3: その他の型
  // else {
  //   static_assert(!std::is_same_v<T, T>, "この型はシリアライズできません");
  // }

  return result;
}

void exercise_1_4_1() {
  std::cout << "=== 演習 1.4.1: シリアライゼーション ===" << std::endl;

  // TODO: 整数をシリアライズして結果を出力
  // auto int_bytes = serialize(42);

  // TODO: 文字列をシリアライズして結果を出力
  // auto str_bytes = serialize(std::string("test"));

  // TODO: それぞれのバイト列を表示
  // 形式: "整数42: [バイト1] [バイト2] ..."

  std::cout << std::endl;
}

// ============================================================================
// 演習 1.4.2: 型に応じた演算
// ============================================================================

// TODO: calculate関数テンプレートを実装してください
// 要件:
// - 整数型: value * 2
// - 浮動小数点型: value * 2.5
// - その他: static_assertでエラー

template <typename T>
auto calculate(T value) {
  // TODO: constexpr ifを使って型に応じた計算を実装

  // ヒント: if constexpr (std::is_integral_v<T>) { return value * 2; }
}

void exercise_1_4_2() {
  std::cout << "=== 演習 1.4.2: 型に応じた演算 ===" << std::endl;

  // TODO: calculate関数を整数と浮動小数点で呼び出し、結果を出力
  // auto int_result = calculate(10);
  // auto float_result = calculate(3.14);

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習: 型の情報を表示
// ============================================================================

// TODO: describe_type関数テンプレートを実装してください
// 要件:
// - 整数型かどうか
// - 符号付きかどうか
// - サイズ（バイト数）
// を表示する

template <typename T>
void describe_type(T value) {
  std::cout << "値: " << value << " の型情報:" << std::endl;

  // TODO: constexpr ifを使って型の情報を表示

  // ヒント1: 整数型かチェック
  // if constexpr (std::is_integral_v<T>) {
  //   std::cout << "  - 整数型" << std::endl;
  //   // さらに符号付きかチェック
  //   if constexpr (std::is_signed_v<T>) {
  //     std::cout << "  - 符号付き" << std::endl;
  //   }
  // }

  // ヒント2: サイズを表示
  // std::cout << "  - サイズ: " << sizeof(T) << "バイト" << std::endl;
}

void bonus_exercise() {
  std::cout << "=== ボーナス演習: 型の情報表示 ===" << std::endl;

  // TODO: describe_typeを様々な型で呼び出し
  // describe_type(42);
  // describe_type(3.14);
  // describe_type(std::string("hello"));

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "constexpr if の演習\n" << std::endl;

  exercise_1_4_1();
  exercise_1_4_2();
  bonus_exercise();

  std::cout << "演習が完了しました！" << std::endl;
  std::cout << "solution.cppと比較して、答え合わせをしましょう。" << std::endl;
  return 0;
}
