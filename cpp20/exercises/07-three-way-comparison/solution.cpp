// 三方比較演算子（Spaceship Operator <=>）の演習 - 解答例

#include <algorithm>
#include <compare>
#include <iostream>
#include <string>
#include <vector>

// ============================================================================
// 演習 2.5.3.1: 基本的な三方比較演算子
// ============================================================================

struct Point2D {
  int x, y;

  // デフォルトの三方比較演算子
  auto operator<=>(const Point2D&) const = default;
};

void exercise_2_5_3_1() {
  std::cout << "=== 演習 2.5.3.1: 基本的な三方比較演算子 ===" << std::endl;

  Point2D p1{10, 20};
  Point2D p2{30, 40};
  Point2D p3{10, 20};

  std::cout << "p1 < p2: " << (p1 < p2) << std::endl;
  std::cout << "p1 == p3: " << (p1 == p3) << std::endl;
  std::cout << "p1 != p2: " << (p1 != p2) << std::endl;
  std::cout << "p2 > p1: " << (p2 > p1) << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 演習 2.5.3.2: バージョン比較
// ============================================================================

struct Version {
  int major;
  int minor;
  int patch;

  // カスタムの三方比較演算子
  std::strong_ordering operator<=>(const Version& other) const {
    if (auto cmp = major <=> other.major; cmp != 0) return cmp;
    if (auto cmp = minor <=> other.minor; cmp != 0) return cmp;
    return patch <=> other.patch;
  }

  bool operator==(const Version&) const = default;
};

void exercise_2_5_3_2() {
  std::cout << "=== 演習 2.5.3.2: バージョン比較 ===" << std::endl;

  Version v1{1, 0, 0};
  Version v2{1, 0, 1};
  Version v3{1, 1, 0};
  Version v4{2, 0, 0};

  std::cout << "v1 (1.0.0) < v2 (1.0.1): " << (v1 < v2) << std::endl;
  std::cout << "v2 (1.0.1) < v3 (1.1.0): " << (v2 < v3) << std::endl;
  std::cout << "v3 (1.1.0) < v4 (2.0.0): " << (v3 < v4) << std::endl;
  std::cout << "v1 (1.0.0) == v1: " << (v1 == v1) << std::endl;

  // バージョンのソート
  std::vector<Version> versions = {v4, v2, v1, v3};
  std::sort(versions.begin(), versions.end());

  std::cout << "\nソート結果:" << std::endl;
  for (const auto& v : versions) {
    std::cout << v.major << "." << v.minor << "." << v.patch << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// 演習 2.5.3.3: UEスタイルのFVersion型
// ============================================================================

struct FVersion {
  int Major;
  int Minor;
  int Patch;

  std::strong_ordering operator<=>(const FVersion& other) const {
    if (auto cmp = Major <=> other.Major; cmp != 0) return cmp;
    if (auto cmp = Minor <=> other.Minor; cmp != 0) return cmp;
    return Patch <=> other.Patch;
  }

  bool operator==(const FVersion&) const = default;
};

void exercise_2_5_3_3() {
  std::cout << "=== 演習 2.5.3.3: UEスタイルのFVersion型 ===" << std::endl;

  FVersion UE5_5{5, 5, 0};
  FVersion UE5_6{5, 6, 0};
  FVersion UE5_7{5, 7, 0};

  std::cout << "UE 5.5 < UE 5.6: " << (UE5_5 < UE5_6) << std::endl;
  std::cout << "UE 5.6 < UE 5.7: " << (UE5_6 < UE5_7) << std::endl;

  // 最小バージョンチェック
  FVersion MinVersion{5, 7, 0};
  FVersion CurrentVersion{5, 6, 0};

  std::cout << "\nバージョンチェック:" << std::endl;
  if (CurrentVersion < MinVersion) {
    std::cout << "Warning: UE version " << CurrentVersion.Major << "."
              << CurrentVersion.Minor << "." << CurrentVersion.Patch
              << " is older than required " << MinVersion.Major << "."
              << MinVersion.Minor << "." << MinVersion.Patch << std::endl;
  } else {
    std::cout << "Version check passed!" << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習: ゲームキャラクターの強さ比較
// ============================================================================

struct Character {
  std::string name;
  int level;
  int attack;
  int defense;

  std::strong_ordering operator<=>(const Character& other) const {
    // レベル優先
    if (auto cmp = level <=> other.level; cmp != 0) return cmp;
    // 次に攻撃力
    if (auto cmp = attack <=> other.attack; cmp != 0) return cmp;
    // 最後に防御力
    return defense <=> other.defense;
  }

  bool operator==(const Character&) const = default;
};

void bonus_exercise() {
  std::cout << "=== ボーナス演習: キャラクター強さ比較 ===" << std::endl;

  Character c1{"Knight", 10, 50, 40};
  Character c2{"Wizard", 10, 60, 30};
  Character c3{"Rogue", 12, 45, 35};
  Character c4{"Paladin", 10, 50, 45};

  std::cout << "Knight < Wizard: " << (c1 < c2) << " (同レベル、攻撃力で判定)"
            << std::endl;
  std::cout << "Wizard < Rogue: " << (c2 < c3) << " (レベル差)" << std::endl;
  std::cout << "Knight < Paladin: " << (c1 < c4)
            << " (レベル・攻撃力同じ、防御力で判定)" << std::endl;

  // キャラクターを強い順にソート
  std::vector<Character> party = {c1, c2, c3, c4};
  std::sort(party.begin(), party.end(),
            [](const Character& a, const Character& b) { return a > b; });

  std::cout << "\n強さランキング:" << std::endl;
  int rank = 1;
  for (const auto& c : party) {
    std::cout << rank++ << ". " << c.name << " (Lv." << c.level
              << ", ATK:" << c.attack << ", DEF:" << c.defense << ")"
              << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "三方比較演算子の演習 - 解答例\n" << std::endl;

  exercise_2_5_3_1();
  exercise_2_5_3_2();
  exercise_2_5_3_3();
  bonus_exercise();

  std::cout << "お疲れ様でした！" << std::endl;
  return 0;
}
