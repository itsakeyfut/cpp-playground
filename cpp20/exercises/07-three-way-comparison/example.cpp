// 三方比較演算子（Spaceship Operator <=>）のサンプルコード
// このファイルは写経用です。コードを理解しながら写経してください。

#include <compare>
#include <iostream>
#include <string>
#include <vector>

// ============================================================================
// 1. 基本的な三方比較演算子
// ============================================================================

struct Point {
  int x, y;

  // デフォルトの三方比較演算子
  // これだけで <, >, <=, >=, ==, != が全て使えるようになる
  auto operator<=>(const Point&) const = default;
};

void basic_comparison() {
  std::cout << "=== 基本的な三方比較演算子 ===" << std::endl;

  Point p1{1, 2};
  Point p2{3, 4};
  Point p3{1, 2};

  // 自動生成された比較演算子を使用
  std::cout << "p1 < p2: " << (p1 < p2) << std::endl;
  std::cout << "p1 > p2: " << (p1 > p2) << std::endl;
  std::cout << "p1 <= p2: " << (p1 <= p2) << std::endl;
  std::cout << "p1 >= p2: " << (p1 >= p2) << std::endl;
  std::cout << "p1 == p3: " << (p1 == p3) << std::endl;
  std::cout << "p1 != p2: " << (p1 != p2) << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 2. 比較カテゴリの理解
// ============================================================================

void comparison_categories() {
  std::cout << "=== 比較カテゴリ ===" << std::endl;

  // std::strong_ordering: 全順序
  // a < b, a == b, a > b のいずれか1つだけが真
  int a = 10, b = 20;
  auto result1 = a <=> b;
  std::cout << "10 <=> 20: ";
  if (result1 < 0) std::cout << "less" << std::endl;
  if (result1 == 0) std::cout << "equal" << std::endl;
  if (result1 > 0) std::cout << "greater" << std::endl;

  // std::strong_orderingの値
  std::cout << "\nstrong_ordering値:" << std::endl;
  std::cout << "less: " << (std::strong_ordering::less < 0) << std::endl;
  std::cout << "equal: " << (std::strong_ordering::equal == 0) << std::endl;
  std::cout << "greater: " << (std::strong_ordering::greater > 0) << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 3. カスタム実装：バージョン比較
// ============================================================================

struct Version {
  int major, minor, patch;

  // カスタムの三方比較演算子
  std::strong_ordering operator<=>(const Version& other) const {
    // major -> minor -> patch の順に比較
    if (auto cmp = major <=> other.major; cmp != 0) return cmp;
    if (auto cmp = minor <=> other.minor; cmp != 0) return cmp;
    return patch <=> other.patch;
  }

  // == 演算子も定義が必要（<=>とは独立）
  bool operator==(const Version&) const = default;
};

void version_comparison() {
  std::cout << "=== バージョン比較 ===" << std::endl;

  Version v1{1, 2, 3};
  Version v2{1, 2, 4};
  Version v3{2, 0, 0};
  Version v4{1, 2, 3};

  std::cout << "v1 (1.2.3) < v2 (1.2.4): " << (v1 < v2) << std::endl;
  std::cout << "v1 (1.2.3) < v3 (2.0.0): " << (v1 < v3) << std::endl;
  std::cout << "v1 (1.2.3) == v4 (1.2.3): " << (v1 == v4) << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 4. 複合型の比較
// ============================================================================

struct Player {
  std::string name;
  int score;
  int level;

  // スコアで比較、スコアが同じならレベルで比較
  std::strong_ordering operator<=>(const Player& other) const {
    if (auto cmp = score <=> other.score; cmp != 0) return cmp;
    return level <=> other.level;
  }

  bool operator==(const Player&) const = default;
};

void player_comparison() {
  std::cout << "=== プレイヤー比較（スコア優先） ===" << std::endl;

  std::vector<Player> players = {
      {"Alice", 1000, 10}, {"Bob", 1500, 8}, {"Carol", 1000, 12},
      {"Dave", 1500, 10},  {"Eve", 800, 15},
  };

  // ソート（スコア降順、レベル降順）
  std::sort(players.begin(), players.end(),
            [](const Player& a, const Player& b) { return a > b; });

  std::cout << "ランキング:" << std::endl;
  for (const auto& p : players) {
    std::cout << p.name << " - Score: " << p.score << ", Level: " << p.level
              << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// 5. 部分順序：浮動小数点数
// ============================================================================

struct Position {
  double x, y;

  // 浮動小数点数はNaNがあるため、partial_orderingを使用
  std::partial_ordering operator<=>(const Position& other) const {
    if (auto cmp = x <=> other.x; cmp != 0) return cmp;
    return y <=> other.y;
  }

  bool operator==(const Position&) const = default;
};

void partial_ordering_example() {
  std::cout << "=== 部分順序（浮動小数点数） ===" << std::endl;

  Position p1{1.0, 2.0};
  Position p2{3.0, 4.0};
  Position p3{1.0, 2.0};

  std::cout << "p1 < p2: " << (p1 < p2) << std::endl;
  std::cout << "p1 == p3: " << (p1 == p3) << std::endl;

  // NaNの場合
  double nan = std::numeric_limits<double>::quiet_NaN();
  Position p4{nan, 0.0};
  Position p5{0.0, 0.0};

  // NaNを含む比較は全てfalseになる
  std::cout << "\nNaNを含む比較:" << std::endl;
  std::cout << "p4 < p5: " << (p4 < p5) << std::endl;
  std::cout << "p4 > p5: " << (p4 > p5) << std::endl;
  std::cout << "p4 == p5: " << (p4 == p5) << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 6. 実用例：優先度付きタスク
// ============================================================================

enum class Priority { Low, Medium, High, Critical };

struct Task {
  std::string name;
  Priority priority;
  int deadline;  // 締切（小さいほど緊急）

  // 優先度が高い順、同じなら締切が早い順
  std::strong_ordering operator<=>(const Task& other) const {
    // 優先度を比較（Criticalが最も大きい）
    if (auto cmp = priority <=> other.priority; cmp != 0) return cmp;
    // 締切を比較（小さい方が優先）
    return other.deadline <=> deadline;  // 逆順にする
  }

  bool operator==(const Task&) const = default;
};

void task_priority_example() {
  std::cout << "=== タスク優先度ソート ===" << std::endl;

  std::vector<Task> tasks = {
      {"Fix bug", Priority::High, 3},
      {"Write docs", Priority::Low, 7},
      {"Review PR", Priority::Medium, 2},
      {"Critical fix", Priority::Critical, 5},
      {"Refactor", Priority::Low, 1},
  };

  // 優先度順にソート
  std::sort(tasks.begin(), tasks.end(),
            [](const Task& a, const Task& b) { return a > b; });

  std::cout << "タスク一覧（優先度順）:" << std::endl;
  for (const auto& t : tasks) {
    std::string priority_str;
    switch (t.priority) {
      case Priority::Low:
        priority_str = "Low";
        break;
      case Priority::Medium:
        priority_str = "Medium";
        break;
      case Priority::High:
        priority_str = "High";
        break;
      case Priority::Critical:
        priority_str = "Critical";
        break;
    }
    std::cout << "[" << priority_str << "] " << t.name
              << " (deadline: " << t.deadline << " days)" << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "C++20 三方比較演算子のサンプル\n" << std::endl;

  basic_comparison();
  comparison_categories();
  version_comparison();
  player_comparison();
  partial_ordering_example();
  task_priority_example();

  std::cout << "全てのサンプルが完了しました！" << std::endl;
  return 0;
}
