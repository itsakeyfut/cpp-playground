// モジュール（Modules）の演習問題
// 注意: これは概念理解のための演習です

#include <iostream>
#include <string>

// ============================================================================
// 演習 2.4.1: モジュール風の数学ライブラリ
// ============================================================================
// 名前空間と匿名名前空間を使って、モジュール風の実装を作成せよ。
//
// 要件:
// - 公開関数: add(), subtract(), multiply(), divide()
// - 非公開関数: validate_division() （0除算チェック用）

// TODO: math_lib 名前空間を実装してください
namespace math_lib {
// TODO: 公開関数を実装

// TODO: 匿名名前空間で非公開関数を実装
// namespace {
//     bool validate_division(int divisor) {
//         return divisor != 0;
//     }
// }

}  // namespace math_lib

void test_math_module() {
  std::cout << "=== 演習 2.4.1: 数学ライブラリモジュール ===" << std::endl;

  // TODO: 以下のコメントを外して動作確認してください
  // std::cout << "5 + 3 = " << math_lib::add(5, 3) << std::endl;
  // std::cout << "10 - 4 = " << math_lib::subtract(10, 4) << std::endl;
  // std::cout << "6 * 7 = " << math_lib::multiply(6, 7) << std::endl;
  // std::cout << "15 / 3 = " << math_lib::divide(15, 3) << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 演習 2.4.2: インターフェースと実装の分離
// ============================================================================
// 公開インターフェースと非公開実装を分離する設計を理解せよ。

// TODO: logger 名前空間を実装してください
namespace logger {
// TODO: 公開インターフェース
// void log(const std::string& message);

// TODO: 非公開実装（匿名名前空間）
// namespace {
//     std::string format_message(const std::string& msg) {
//         return "[LOG] " + msg;
//     }
// }

}  // namespace logger

void test_logger_module() {
  std::cout << "=== 演習 2.4.2: ロガーモジュール ===" << std::endl;

  // TODO: 以下のコメントを外して動作確認してください
  // logger::log("Application started");
  // logger::log("Processing data");
  // logger::log("Application finished");

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "C++20 モジュール（Modules）の演習問題\n" << std::endl;

  test_math_module();
  test_logger_module();

  std::cout << "演習が完了しました！" << std::endl;
  std::cout << "モジュールの概念（公開/非公開の分離）を理解できましたか？"
            << std::endl;
  return 0;
}
