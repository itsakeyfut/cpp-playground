// Attributes（属性）の演習
// TODOコメントを埋めて、プログラムを完成させてください。

#include <iostream>
#include <string>

// ============================================================================
// 演習 1: [[nodiscard]] を使ったエラーハンドリング
// ============================================================================

enum class Result {
  Success,
  Error
};

// TODO: この関数に[[nodiscard]]属性を追加してください
Result process_data(int value) {
  std::cout << "データを処理: " << value << std::endl;

  if (value < 0) {
    return Result::Error;
  }

  return Result::Success;
}

void exercise_1() {
  std::cout << "=== 演習 1: [[nodiscard]] ===" << std::endl;

  // TODO: process_data関数を呼び出し、戻り値をチェックしてください
  // 正の値でテスト
  // 負の値でテスト

  // ヒント:
  // Result result = process_data(10);
  // if (result == Result::Success) { ... }

  std::cout << std::endl;
}

// ============================================================================
// 演習 2: [[deprecated]] を使った移行警告
// ============================================================================

// TODO: この古い関数に[[deprecated]]属性を追加してください
// メッセージ: "use calculate_area_v2() instead"
double calculate_area_v1(double width, double height) {
  return width * height;
}

// 新しいバージョン
double calculate_area_v2(double width, double height) {
  // 負の値チェックを追加
  if (width < 0 || height < 0) {
    return 0.0;
  }
  return width * height;
}

void exercise_2() {
  std::cout << "=== 演習 2: [[deprecated]] ===" << std::endl;

  // TODO: calculate_area_v2を使って面積を計算
  // double area = calculate_area_v2(5.0, 3.0);

  // TODO: 結果を出力

  // 注意: calculate_area_v1を呼び出すとコンパイラ警告が出ます

  std::cout << std::endl;
}

// ============================================================================
// 演習 3: [[maybe_unused]] を使ったデバッグコード
// ============================================================================

void exercise_3() {
  std::cout << "=== 演習 3: [[maybe_unused]] ===" << std::endl;

  // TODO: debug_modeという変数を定義し、[[maybe_unused]]属性を付けてください
  // bool型で、デバッグビルドではtrueに設定

  // TODO: 条件付きコンパイルを使ってデバッグ情報を出力
  // ヒント: #ifndef NDEBUG でデバッグビルドかチェック

  std::cout << "処理を実行中..." << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 演習 4: [[fallthrough]] を使ったswitch文
// ============================================================================

void process_grade(char grade) {
  std::cout << "成績 " << grade << ": ";

  switch (grade) {
    case 'A':
      std::cout << "優秀、";
      // TODO: [[fallthrough]]を追加
    case 'B':
      std::cout << "良好、";
      // TODO: [[fallthrough]]を追加
    case 'C':
      std::cout << "合格";
      break;
    case 'D':
      std::cout << "不合格";
      break;
    default:
      std::cout << "不明な成績";
      break;
  }

  std::cout << std::endl;
}

void exercise_4() {
  std::cout << "=== 演習 4: [[fallthrough]] ===" << std::endl;

  // TODO: process_grade関数を様々な成績で呼び出し
  // 例: process_grade('A');
  //     process_grade('B');
  //     process_grade('D');

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習: 複数の属性を組み合わせる
// ============================================================================

// TODO: この関数に適切な属性を追加してください
// - [[nodiscard]]: 戻り値を無視してはいけない
// - [[deprecated]]: 非推奨（メッセージ: "use safe_divide() instead"）
double unsafe_divide(double a, double b) {
  return a / b;  // ゼロ除算チェックなし
}

// TODO: この関数に[[nodiscard]]属性を追加
double safe_divide(double a, double b) {
  if (b == 0.0) {
    std::cerr << "エラー: ゼロ除算" << std::endl;
    return 0.0;
  }
  return a / b;
}

void bonus_exercise() {
  std::cout << "=== ボーナス演習: 複数の属性 ===" << std::endl;

  // TODO: safe_divide関数を使って計算
  // 例: double result = safe_divide(10.0, 2.0);

  // TODO: 結果を出力

  // 注意: unsafe_divideを使うと警告が出ます

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "Attributes の演習\n" << std::endl;

  exercise_1();
  exercise_2();
  exercise_3();
  exercise_4();
  bonus_exercise();

  std::cout << "演習が完了しました！" << std::endl;
  std::cout << "solution.cppと比較して、答え合わせをしましょう。" << std::endl;
  return 0;
}
