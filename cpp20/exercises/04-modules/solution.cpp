// モジュール（Modules）の演習問題 - 解答例
// 注意: これは概念理解のための演習です

#include <iostream>
#include <stdexcept>
#include <string>

// ============================================================================
// 演習 2.4.1: モジュール風の数学ライブラリ（解答）
// ============================================================================

namespace math_lib {
// 公開関数
int add(int a, int b) { return a + b; }

int subtract(int a, int b) { return a - b; }

int multiply(int a, int b) { return a * b; }

int divide(int a, int b) {
  if (!validate_division(b)) {
    throw std::invalid_argument("Division by zero");
  }
  return a / b;
}

// 非公開関数（匿名名前空間）
namespace {
bool validate_division(int divisor) { return divisor != 0; }
}  // namespace

}  // namespace math_lib

void test_math_module() {
  std::cout << "=== 演習 2.4.1: 数学ライブラリモジュール（解答） ==="
            << std::endl;

  std::cout << "5 + 3 = " << math_lib::add(5, 3) << std::endl;
  std::cout << "10 - 4 = " << math_lib::subtract(10, 4) << std::endl;
  std::cout << "6 * 7 = " << math_lib::multiply(6, 7) << std::endl;
  std::cout << "15 / 3 = " << math_lib::divide(15, 3) << std::endl;

  // 0除算のテスト
  try {
    math_lib::divide(10, 0);
  } catch (const std::invalid_argument& e) {
    std::cout << "エラーハンドリング成功: " << e.what() << std::endl;
  }

  std::cout << "✓ 数学ライブラリが正しく動作しています" << std::endl;
  std::cout << std::endl;
}

// ============================================================================
// 演習 2.4.2: インターフェースと実装の分離（解答）
// ============================================================================

namespace logger {
// 公開インターフェース
void log(const std::string& message) {
  std::cout << format_message(message) << std::endl;
}

void log_error(const std::string& message) {
  std::cout << format_error(message) << std::endl;
}

// 非公開実装（匿名名前空間）
namespace {
std::string format_message(const std::string& msg) { return "[LOG] " + msg; }

std::string format_error(const std::string& msg) { return "[ERROR] " + msg; }
}  // namespace

}  // namespace logger

void test_logger_module() {
  std::cout << "=== 演習 2.4.2: ロガーモジュール（解答） ===" << std::endl;

  logger::log("Application started");
  logger::log("Processing data");
  logger::log_error("Something went wrong");
  logger::log("Application finished");

  std::cout << "\n✓ ロガーが正しく動作しています" << std::endl;
  std::cout << std::endl;
}

// ============================================================================
// おまけ: より実践的な例
// ============================================================================

namespace config {
// 設定管理モジュール
class Config {
  std::string app_name_;
  int version_major_;
  int version_minor_;

 public:
  Config(std::string name, int major, int minor)
      : app_name_(name), version_major_(major), version_minor_(minor) {}

  std::string get_version_string() const {
    return format_version(version_major_, version_minor_);
  }

  std::string get_app_name() const { return app_name_; }
};

// 非公開ヘルパー
namespace {
std::string format_version(int major, int minor) {
  return std::to_string(major) + "." + std::to_string(minor);
}
}  // namespace

// ファクトリー関数
Config create_default_config() { return Config("MyApp", 1, 0); }

}  // namespace config

void advanced_example() {
  std::cout << "=== おまけ: 設定管理モジュール ===" << std::endl;

  auto cfg = config::create_default_config();
  std::cout << "アプリケーション: " << cfg.get_app_name() << std::endl;
  std::cout << "バージョン: " << cfg.get_version_string() << std::endl;

  std::cout << "\n✓ 設定管理が正しく動作しています" << std::endl;
  std::cout << std::endl;
}

// ============================================================================
// モジュールの実際の構文（参考）
// ============================================================================

void show_real_module_syntax() {
  std::cout << "=== 参考: 実際のモジュール構文 ===" << std::endl;
  std::cout << R"(
実際のC++20モジュール構文:

// math.ixx
export module math;

export namespace math {
    int add(int a, int b) {
        return a + b;
    }

    int multiply(int a, int b) {
        return a * b;
    }
}

// 非公開（exportなし）
namespace {
    bool validate(int x) {
        return x >= 0;
    }
}

---

// main.cpp
import math;

int main() {
    int result = math::add(1, 2);
    // validate(5); // エラー: アクセスできない
}
)" << std::endl;

  std::cout << "注意: 実際に動かすにはコンパイラの追加設定が必要です"
            << std::endl;
  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "C++20 モジュール（Modules）の演習問題 - 解答例\n"
            << std::endl;

  test_math_module();
  test_logger_module();
  advanced_example();
  show_real_module_syntax();

  std::cout << "全ての演習が完了しました！" << std::endl;
  std::cout << "\nモジュールの重要ポイント:" << std::endl;
  std::cout << "  ✓ export で公開するものを明示" << std::endl;
  std::cout << "  ✓ カプセル化の向上" << std::endl;
  std::cout << "  ✓ コンパイル時間の短縮" << std::endl;
  std::cout << "  ✓ マクロ汚染の防止" << std::endl;
  std::cout << "\n現状: 実験的機能（将来に期待）" << std::endl;

  return 0;
}
