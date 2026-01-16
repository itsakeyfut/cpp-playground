// 構造化束縛（Structured Bindings）の演習
// TODOコメントを埋めて、プログラムを完成させてください。

#include <iostream>
#include <map>
#include <string>
#include <tuple>

// ============================================================================
// 演習 1.1.1: 3D空間の点を表す構造体
// ============================================================================

struct Point3D {
  // TODO: x, y, z のメンバ変数を定義してください
};

void exercise_1_1_1() {
  std::cout << "=== 演習 1.1.1: Point3Dの分解 ===" << std::endl;

  // TODO: Point3D型の変数を作成し、適当な値で初期化してください
  // 例: Point3D p{...};

  // TODO: 構造化束縛を使って、x, y, z を分解してください
  // ヒント: auto [変数1, 変数2, 変数3] = p;

  // TODO: 分解した値を出力してください
  // 例: std::cout << "Point: (" << x << ", " << y << ", " << z << ")" << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 演習 1.1.2: RGB値を格納したmapのイテレーション
// ============================================================================

void exercise_1_1_2() {
  std::cout << "=== 演習 1.1.2: RGB値のmapをイテレート ===" << std::endl;

  // RGB値を格納したmapを作成（すでに完成しています）
  std::map<std::string, std::tuple<int, int, int>> colors = {
      {"Red", {255, 0, 0}},
      {"Green", {0, 255, 0}},
      {"Blue", {0, 0, 255}},
      {"Purple", {128, 0, 128}},
      {"Orange", {255, 165, 0}}};

  // TODO: 構造化束縛を使って、mapをイテレートしてください
  // ヒント1: for (const auto& [...] : colors) { ... }
  // ヒント2: mapの要素はpair<const Key, Value>なので、[key, value]で分解できます
  // ヒント3: valueはtupleなので、さらに[r, g, b]で分解できます

  // TODO: 各色の名前とRGB値を以下の形式で出力してください
  // 形式: "Red: RGB(255, 0, 0)"

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習: 複数の戻り値を持つ関数
// ============================================================================

// TODO: この関数を実装してください
// 機能: 最小値、最大値、平均値をtupleで返す
// ヒント: std::make_tuple()を使います
std::tuple<int, int, double> calculate_stats(int a, int b, int c) {
  // TODO: 最小値を計算
  // TODO: 最大値を計算
  // TODO: 平均値を計算
  // TODO: tupleで返す
  return {};  // TODO: この行を置き換えてください
}

void bonus_exercise() {
  std::cout << "=== ボーナス演習: 統計関数 ===" << std::endl;

  // TODO: calculate_stats関数を呼び出し、構造化束縛で結果を受け取ってください
  // 例: auto [min, max, avg] = calculate_stats(10, 20, 15);

  // TODO: 結果を出力してください
  // 形式: "Min: X, Max: Y, Average: Z"

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "構造化束縛の演習\n" << std::endl;

  exercise_1_1_1();
  exercise_1_1_2();
  bonus_exercise();

  std::cout << "演習が完了しました！" << std::endl;
  std::cout << "solution.cppと比較して、答え合わせをしましょう。" << std::endl;
  return 0;
}
