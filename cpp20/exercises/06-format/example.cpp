// std::format（フォーマット文字列）のサンプルコード
// このファイルは写経用です。コードを理解しながら写経してください。

#include <format>
#include <iostream>
#include <string>
#include <vector>

// ============================================================================
// 1. 基本的なフォーマット
// ============================================================================

void basic_format() {
  std::cout << "=== 基本的なフォーマット ===" << std::endl;

  // 基本的な置き換え
  std::string s1 = std::format("Hello, {}!", "World");
  std::cout << s1 << std::endl;

  // 複数の引数
  std::string s2 = std::format("{} + {} = {}", 1, 2, 3);
  std::cout << s2 << std::endl;

  // 位置指定
  std::string s3 = std::format("{1} before {0}", "World", "Hello");
  std::cout << s3 << std::endl;

  // 同じ引数を複数回使用
  std::string s4 = std::format("{0} {0} {0}", "Buffalo");
  std::cout << s4 << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 2. 数値フォーマット
// ============================================================================

void numeric_format() {
  std::cout << "=== 数値フォーマット ===" << std::endl;

  int value = 42;

  // 10進数（デフォルト）
  std::cout << std::format("10進数: {}", value) << std::endl;

  // 16進数（小文字）
  std::cout << std::format("16進数: {:x}", value) << std::endl;

  // 16進数（大文字）
  std::cout << std::format("16進数: {:X}", value) << std::endl;

  // 2進数
  std::cout << std::format("2進数: {:b}", value) << std::endl;

  // 8進数
  std::cout << std::format("8進数: {:o}", value) << std::endl;

  // プレフィックス付き
  std::cout << std::format("16進数(0x): {:#x}", value) << std::endl;
  std::cout << std::format("2進数(0b): {:#b}", value) << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 3. 浮動小数点フォーマット
// ============================================================================

void floating_point_format() {
  std::cout << "=== 浮動小数点フォーマット ===" << std::endl;

  double pi = 3.14159265358979;

  // デフォルト
  std::cout << std::format("デフォルト: {}", pi) << std::endl;

  // 精度指定（小数点以下の桁数）
  std::cout << std::format("精度2: {:.2f}", pi) << std::endl;
  std::cout << std::format("精度5: {:.5f}", pi) << std::endl;

  // 指数表記
  std::cout << std::format("指数表記: {:e}", pi) << std::endl;
  std::cout << std::format("指数表記(大文字): {:E}", pi) << std::endl;

  // 一般形式（自動選択）
  std::cout << std::format("一般形式: {:g}", pi) << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 4. 幅とアライメント
// ============================================================================

void width_alignment() {
  std::cout << "=== 幅とアライメント ===" << std::endl;

  // 右寄せ（デフォルト）
  std::cout << std::format("[{:>10}]", "test") << std::endl;

  // 左寄せ
  std::cout << std::format("[{:<10}]", "test") << std::endl;

  // 中央揃え
  std::cout << std::format("[{:^10}]", "test") << std::endl;

  // パディング文字を指定
  std::cout << std::format("[{:*>10}]", "test") << std::endl;
  std::cout << std::format("[{:*<10}]", "test") << std::endl;
  std::cout << std::format("[{:*^10}]", "test") << std::endl;

  // 数値のパディング（0埋め）
  std::cout << std::format("数値: {:05d}", 42) << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 5. 実用例：テーブル表示
// ============================================================================

struct PlayerScore {
  std::string name;
  int score;
  std::string rank;
};

void table_example() {
  std::cout << "=== 実用例：テーブル表示 ===" << std::endl;

  std::vector<PlayerScore> players = {
      {"Alice", 1250, "Gold"},
      {"Bob", 890, "Silver"},
      {"Carol", 1450, "Platinum"},
      {"Dave", 650, "Bronze"},
  };

  // ヘッダー
  std::cout << std::format("{:<10} {:>8} {:>10}", "Name", "Score", "Rank")
            << std::endl;
  std::cout << std::string(30, '-') << std::endl;

  // データ行
  for (const auto& player : players) {
    std::cout << std::format("{:<10} {:>8} {:>10}", player.name, player.score,
                             player.rank)
              << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// 6. カスタム型のフォーマット（上級）
// ============================================================================

struct Point3D {
  int x, y, z;
};

// std::formatter特殊化
template <>
struct std::formatter<Point3D> {
  // パース関数（フォーマット指定子の解析）
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

  // フォーマット関数
  auto format(const Point3D& p, std::format_context& ctx) const {
    return std::format_to(ctx.out(), "Point3D({}, {}, {})", p.x, p.y, p.z);
  }
};

void custom_type_format() {
  std::cout << "=== カスタム型のフォーマット ===" << std::endl;

  Point3D p{10, 20, 30};
  std::cout << std::format("Position: {}", p) << std::endl;

  // 他の値と組み合わせて使用
  std::cout << std::format("Player at {}, health: {}", p, 100) << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 7. std::format vs printf の比較
// ============================================================================

void comparison_with_printf() {
  std::cout << "=== std::format vs printf ===" << std::endl;

  int age = 25;
  std::string name = "Alice";

  // printf（型安全でない）
  std::cout << "printf: ";
  std::printf("Name: %s, Age: %d\n", name.c_str(), age);

  // std::format（型安全）
  std::cout << "format: "
            << std::format("Name: {}, Age: {}", name, age) << std::endl;

  // printfの問題：型が間違っていてもコンパイルエラーにならない
  // std::printf("Age: %s\n", age);  // 警告は出るがコンパイルは通る

  // std::formatの利点：型が間違っているとコンパイルエラー
  // std::format("Age: {:x}", name);  // コンパイルエラー！

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "C++20 std::format のサンプル\n" << std::endl;

  basic_format();
  numeric_format();
  floating_point_format();
  width_alignment();
  table_example();
  custom_type_format();
  comparison_with_printf();

  std::cout << "全てのサンプルが完了しました！" << std::endl;
  return 0;
}
