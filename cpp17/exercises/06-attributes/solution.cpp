// Attributes（属性）の演習 - 解答例

#include <iostream>
#include <string>

// ============================================================================
// 演習 1: [[nodiscard]] を使ったエラーハンドリング
// ============================================================================

enum class Result {
  Success,
  Error
};

[[nodiscard]]
Result process_data(int value) {
  std::cout << "データを処理: " << value << std::endl;

  if (value < 0) {
    return Result::Error;
  }

  return Result::Success;
}

void exercise_1() {
  std::cout << "=== 演習 1: [[nodiscard]] ===" << std::endl;

  // 正の値でテスト
  Result result1 = process_data(10);
  if (result1 == Result::Success) {
    std::cout << "処理成功" << std::endl;
  } else {
    std::cout << "処理失敗" << std::endl;
  }

  // 負の値でテスト
  Result result2 = process_data(-5);
  if (result2 == Result::Success) {
    std::cout << "処理成功" << std::endl;
  } else {
    std::cout << "処理失敗（負の値）" << std::endl;
  }

  // 戻り値を無視するとコンパイラ警告が出る
  // process_data(20);  // 警告: 戻り値が無視されています

  std::cout << std::endl;
}

// ============================================================================
// 演習 2: [[deprecated]] を使った移行警告
// ============================================================================

[[deprecated("use calculate_area_v2() instead")]]
double calculate_area_v1(double width, double height) {
  return width * height;
}

double calculate_area_v2(double width, double height) {
  if (width < 0 || height < 0) {
    return 0.0;
  }
  return width * height;
}

void exercise_2() {
  std::cout << "=== 演習 2: [[deprecated]] ===" << std::endl;

  double area = calculate_area_v2(5.0, 3.0);
  std::cout << "面積（v2）: " << area << std::endl;

  // 負の値のチェック
  double invalid_area = calculate_area_v2(-1.0, 3.0);
  std::cout << "面積（無効な入力）: " << invalid_area << std::endl;

  // 古いバージョンを使うと警告が出る
  // double old_area = calculate_area_v1(5.0, 3.0);  // 警告: deprecated

  std::cout << std::endl;
}

// ============================================================================
// 演習 3: [[maybe_unused]] を使ったデバッグコード
// ============================================================================

void exercise_3() {
  std::cout << "=== 演習 3: [[maybe_unused]] ===" << std::endl;

  [[maybe_unused]] bool debug_mode = false;

#ifndef NDEBUG
  debug_mode = true;
  std::cout << "[デバッグモード] デバッグ情報を表示します" << std::endl;
  std::cout << "[デバッグモード] debug_mode = " << debug_mode << std::endl;
#endif

  std::cout << "処理を実行中..." << std::endl;

#ifndef NDEBUG
  std::cout << "[デバッグモード] 処理完了" << std::endl;
#endif

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
      [[fallthrough]];
    case 'B':
      std::cout << "良好、";
      [[fallthrough]];
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

  process_grade('A');
  process_grade('B');
  process_grade('C');
  process_grade('D');
  process_grade('F');

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習: 複数の属性を組み合わせる
// ============================================================================

[[nodiscard, deprecated("use safe_divide() instead")]]
double unsafe_divide(double a, double b) {
  return a / b;  // ゼロ除算チェックなし
}

[[nodiscard]]
double safe_divide(double a, double b) {
  if (b == 0.0) {
    std::cerr << "エラー: ゼロ除算" << std::endl;
    return 0.0;
  }
  return a / b;
}

void bonus_exercise() {
  std::cout << "=== ボーナス演習: 複数の属性 ===" << std::endl;

  double result1 = safe_divide(10.0, 2.0);
  std::cout << "10.0 / 2.0 = " << result1 << std::endl;

  double result2 = safe_divide(5.0, 0.0);
  std::cout << "5.0 / 0.0 = " << result2 << " (ゼロ除算を検出)" << std::endl;

  // unsafe_divideを使うと警告が出る
  // double unsafe_result = unsafe_divide(10.0, 2.0);  // 警告: deprecated
  // unsafe_divide(10.0, 2.0);  // 警告: nodiscard + deprecated

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "Attributes の演習 - 解答例\n" << std::endl;

  exercise_1();
  exercise_2();
  exercise_3();
  exercise_4();
  bonus_exercise();

  std::cout << "お疲れ様でした！" << std::endl;
  std::cout << "\nヒント: コンパイラ警告を確認するには、" << std::endl;
  std::cout << "コメントアウトされているコードを有効にしてビルドしてください。" << std::endl;
  return 0;
}
