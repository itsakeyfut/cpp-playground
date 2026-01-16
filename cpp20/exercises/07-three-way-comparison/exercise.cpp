// 三方比較演算子（Spaceship Operator <=>）の演習
// TODOコメントを埋めて、プログラムを完成させてください。

#include <compare>
#include <iostream>
#include <string>
#include <vector>

// ============================================================================
// 演習 2.5.3.1: 基本的な三方比較演算子
// ============================================================================

struct Point2D {
  int x, y;

  // TODO: デフォルトの三方比較演算子を定義してください
  // ヒント: auto operator<=>(const Point2D&) const = default;
};

void exercise_2_5_3_1() {
  std::cout << "=== 演習 2.5.3.1: 基本的な三方比較演算子 ===" << std::endl;

  Point2D p1{10, 20};
  Point2D p2{30, 40};
  Point2D p3{10, 20};

  // TODO: 以下の比較演算子が動作することを確認してください
  // std::cout << "p1 < p2: " << (p1 < p2) << std::endl;
  // std::cout << "p1 == p3: " << (p1 == p3) << std::endl;
  // std::cout << "p1 != p2: " << (p1 != p2) << std::endl;
  // std::cout << "p2 > p1: " << (p2 > p1) << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 演習 2.5.3.2: バージョン比較
// ============================================================================

struct Version {
  int major;
  int minor;
  int patch;

  // TODO: カスタムの三方比較演算子を実装してください
  // major -> minor -> patch の順に比較
  // ヒント: if (auto cmp = major <=> other.major; cmp != 0) return cmp;

  // TODO: == 演算子も定義してください
  // ヒント: bool operator==(const Version&) const = default;
};

void exercise_2_5_3_2() {
  std::cout << "=== 演習 2.5.3.2: バージョン比較 ===" << std::endl;

  Version v1{1, 0, 0};
  Version v2{1, 0, 1};
  Version v3{1, 1, 0};
  Version v4{2, 0, 0};

  // TODO: 以下の比較が正しく動作することを確認してください
  // std::cout << "v1 (1.0.0) < v2 (1.0.1): " << (v1 < v2) << std::endl;
  // std::cout << "v2 (1.0.1) < v3 (1.1.0): " << (v2 < v3) << std::endl;
  // std::cout << "v3 (1.1.0) < v4 (2.0.0): " << (v3 < v4) << std::endl;
  // std::cout << "v1 (1.0.0) == v1: " << (v1 == v1) << std::endl;

  // TODO: バージョンのソート
  // std::vector<Version> versions = {v4, v2, v1, v3};
  // std::sort(versions.begin(), versions.end());
  // for (const auto& v : versions) {
  //   std::cout << v.major << "." << v.minor << "." << v.patch << std::endl;
  // }

  std::cout << std::endl;
}

// ============================================================================
// 演習 2.5.3.3: UEスタイルのFVersion型
// ============================================================================

// TODO: FVersion構造体を定義してください
// メンバ変数: Major, Minor, Patch (int32型、またはint)
// 三方比較演算子を実装してください

// struct FVersion {
//   // TODO: メンバ変数を定義
//
//   // TODO: 三方比較演算子を実装
//
//   // TODO: == 演算子を実装
// };

void exercise_2_5_3_3() {
  std::cout << "=== 演習 2.5.3.3: UEスタイルのFVersion型 ===" << std::endl;

  // TODO: FVersionのインスタンスを作成してください
  // FVersion UE5_5{5, 5, 0};
  // FVersion UE5_6{5, 6, 0};
  // FVersion UE5_7{5, 7, 0};

  // TODO: バージョン比較を実装してください
  // std::cout << "UE 5.5 < UE 5.6: " << (UE5_5 < UE5_6) << std::endl;
  // std::cout << "UE 5.6 < UE 5.7: " << (UE5_6 < UE5_7) << std::endl;

  // TODO: 最小バージョンチェック
  // FVersion MinVersion{5, 7, 0};
  // FVersion CurrentVersion{5, 6, 0};
  // if (CurrentVersion < MinVersion) {
  //   std::cout << "Warning: UE version too old!" << std::endl;
  // }

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

  // TODO: 三方比較演算子を実装してください
  // 比較順序:
  // 1. レベルが高い方が強い
  // 2. レベルが同じなら攻撃力が高い方が強い
  // 3. 攻撃力も同じなら防御力が高い方が強い
};

void bonus_exercise() {
  std::cout << "=== ボーナス演習: キャラクター強さ比較 ===" << std::endl;

  // TODO: キャラクターを作成してください
  // Character c1{"Knight", 10, 50, 40};
  // Character c2{"Wizard", 10, 60, 30};
  // Character c3{"Rogue", 12, 45, 35};

  // TODO: 強さを比較してください
  // std::cout << "Knight < Wizard: " << (c1 < c2) << std::endl;
  // std::cout << "Wizard < Rogue: " << (c2 < c3) << std::endl;

  // TODO: キャラクターを強い順にソートしてください
  // std::vector<Character> party = {c1, c2, c3};
  // std::sort(party.begin(), party.end(), [](const Character& a, const
  // Character& b) {
  //   return a > b;  // 降順
  // });

  // TODO: ソート結果を出力してください

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "三方比較演算子の演習\n" << std::endl;

  exercise_2_5_3_1();
  exercise_2_5_3_2();
  exercise_2_5_3_3();
  bonus_exercise();

  std::cout << "演習が完了しました！" << std::endl;
  std::cout << "solution.cppと比較して、答え合わせをしましょう。" << std::endl;
  return 0;
}
