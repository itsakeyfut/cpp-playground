// std::format（フォーマット文字列）の演習 - 解答例

#include <cmath>
#include <format>
#include <iostream>
#include <string>
#include <vector>

// ============================================================================
// 演習 2.5.2.1: 基本的な数値フォーマット
// ============================================================================

void exercise_2_5_2_1() {
  std::cout << "=== 演習 2.5.2.1: 基本的な数値フォーマット ===" << std::endl;

  int number = 255;

  // 10進数
  std::cout << std::format("10進数: {}", number) << std::endl;

  // 16進数（小文字）
  std::cout << std::format("16進数: {:x}", number) << std::endl;

  // 2進数
  std::cout << std::format("2進数: {:b}", number) << std::endl;

  // 16進数（0xプレフィックス付き）
  std::cout << std::format("16進数(0x): {:#x}", number) << std::endl;

  double pi = 3.14159265358979;

  // 小数点以下2桁
  std::cout << std::format("円周率: {:.2f}", pi) << std::endl;

  // 小数点以下6桁
  std::cout << std::format("円周率: {:.6f}", pi) << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 演習 2.5.2.2: テーブル形式の出力
// ============================================================================

struct GameScore {
  std::string player_name;
  int score;
  int level;
  double win_rate;
};

void exercise_2_5_2_2() {
  std::cout << "=== 演習 2.5.2.2: テーブル形式の出力 ===" << std::endl;

  std::vector<GameScore> scores = {
      {"Alice", 1250, 15, 0.785},
      {"Bob", 890, 12, 0.642},
      {"Carol", 1450, 18, 0.823},
      {"Dave", 650, 8, 0.571},
  };

  // ヘッダー行
  std::cout << std::format("{:<10} {:>8} {:>6} {:>8}", "Name", "Score",
                           "Level", "Win Rate")
            << std::endl;

  // 区切り線
  std::cout << std::string(40, '-') << std::endl;

  // データ行
  for (const auto& player : scores) {
    std::cout << std::format("{:<10} {:>8} {:>6} {:>7.1f}%", player.player_name,
                             player.score, player.level, player.win_rate * 100)
              << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// 演習 2.5.2.3: カスタム型のフォーマッター（上級）
// ============================================================================

struct Point3D {
  int x, y, z;
};

// Point3D用のstd::formatter特殊化
template <>
struct std::formatter<Point3D> {
  // パース関数（フォーマット指定子の解析）
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

  // フォーマット関数
  auto format(const Point3D& p, std::format_context& ctx) const {
    return std::format_to(ctx.out(), "Point3D({}, {}, {})", p.x, p.y, p.z);
  }
};

void exercise_2_5_2_3() {
  std::cout << "=== 演習 2.5.2.3: カスタム型のフォーマッター ===" << std::endl;

  Point3D player_pos{100, 50, 25};
  Point3D enemy_pos{120, 60, 30};

  std::cout << std::format("Player position: {}", player_pos) << std::endl;
  std::cout << std::format("Enemy position: {}", enemy_pos) << std::endl;

  // マンハッタン距離を計算
  int distance = std::abs(player_pos.x - enemy_pos.x) +
                 std::abs(player_pos.y - enemy_pos.y) +
                 std::abs(player_pos.z - enemy_pos.z);
  std::cout << std::format("Distance: {} units", distance) << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習: ログフォーマッター
// ============================================================================

void bonus_exercise() {
  std::cout << "=== ボーナス演習: ログフォーマッター ===" << std::endl;

  // ログメッセージのフォーマット
  auto format_log = [](std::string_view level, std::string_view time,
                       std::string_view message) {
    return std::format("[{:<5}] {} - {}", level, time, message);
  };

  // ログ出力
  std::cout << format_log("INFO", "12:34:56", "Game started") << std::endl;
  std::cout << format_log("WARN", "12:35:23", "Low memory") << std::endl;
  std::cout << format_log("ERROR", "12:36:45", "Connection lost") << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "std::format の演習 - 解答例\n" << std::endl;

  exercise_2_5_2_1();
  exercise_2_5_2_2();
  exercise_2_5_2_3();
  bonus_exercise();

  std::cout << "お疲れ様でした！" << std::endl;
  return 0;
}
