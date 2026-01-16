// Attributes（属性）のサンプルコード
// このファイルは写経用です。コードを理解しながら写経してください。

#include <iostream>
#include <string>

// ============================================================================
// 1. [[nodiscard]] - 戻り値を無視すると警告
// ============================================================================

// エラーコードを返す関数
[[nodiscard]] int compute_important() {
  return 42;
}

// エラー処理が必要な関数
[[nodiscard]] bool initialize_system() {
  std::cout << "システムを初期化しています..." << std::endl;
  return true;
}

// C++20以降: 理由を追加できる
[[nodiscard("メモリリークの原因になります")]]
int* allocate_memory(size_t size) {
  return new int[size];
}

void nodiscard_examples() {
  std::cout << "=== [[nodiscard]] の例 ===" << std::endl;

  // 正しい使い方: 戻り値を使用
  int result = compute_important();
  std::cout << "計算結果: " << result << std::endl;

  // エラーハンドリング
  if (initialize_system()) {
    std::cout << "システムの初期化に成功しました" << std::endl;
  }

  // 警告が出る例（コメントアウトしています）
  // compute_important();  // 警告: 戻り値が無視されています

  // メモリ確保
  int* ptr = allocate_memory(10);
  // ... 使用 ...
  delete[] ptr;

  std::cout << std::endl;
}

// ============================================================================
// 2. [[maybe_unused]] - 未使用警告を抑制
// ============================================================================

void maybe_unused_examples() {
  std::cout << "=== [[maybe_unused]] の例 ===" << std::endl;

  // デバッグ用の変数（リリースビルドでは使わない）
  [[maybe_unused]] int debug_counter = 0;

  // 条件付きコンパイルで使う変数
  [[maybe_unused]] const char* build_info = "Debug Build";

#ifdef NDEBUG
  std::cout << "リリースビルド" << std::endl;
#else
  std::cout << "デバッグビルド: " << build_info << std::endl;
  debug_counter++;
  std::cout << "デバッグカウンタ: " << debug_counter << std::endl;
#endif

  std::cout << std::endl;
}

// 未使用の関数パラメータ
void process_data([[maybe_unused]] int unused_param, int used_param) {
  std::cout << "使用するパラメータ: " << used_param << std::endl;
  // unused_paramは将来の拡張用に残している
}

// ============================================================================
// 3. [[fallthrough]] - 意図的なfall-through
// ============================================================================

void process_number(int value) {
  std::cout << "数値 " << value << " を処理: ";

  switch (value) {
    case 1:
      std::cout << "1は素数、";
      [[fallthrough]];  // 意図的にfall-through
    case 2:
      std::cout << "小さい数、";
      [[fallthrough]];
    case 3:
      std::cout << "3以下";
      break;
    case 4:
      std::cout << "4は偶数";
      [[fallthrough]];
    case 5:
      std::cout << "、5以下";
      break;
    default:
      std::cout << "その他";
      break;
  }

  std::cout << std::endl;
}

void fallthrough_examples() {
  std::cout << "=== [[fallthrough]] の例 ===" << std::endl;

  process_number(1);
  process_number(2);
  process_number(4);
  process_number(10);

  std::cout << std::endl;
}

// ============================================================================
// 4. [[deprecated]] - 非推奨マーク
// ============================================================================

// 非推奨の関数
[[deprecated]]
void old_function() {
  std::cout << "これは古い関数です" << std::endl;
}

// 理由を明記
[[deprecated("use new_function() instead")]]
void legacy_function() {
  std::cout << "これはレガシー関数です" << std::endl;
}

// 新しい関数
void new_function() {
  std::cout << "これは新しい関数です" << std::endl;
}

// 非推奨のクラス
[[deprecated("use ModernClass instead")]]
class LegacyClass {
 public:
  void do_something() {
    std::cout << "LegacyClass::do_something()" << std::endl;
  }
};

class ModernClass {
 public:
  void do_something() {
    std::cout << "ModernClass::do_something()" << std::endl;
  }
};

void deprecated_examples() {
  std::cout << "=== [[deprecated]] の例 ===" << std::endl;

  // 新しい関数を使用（推奨）
  new_function();

  // 非推奨の関数を使用（警告が出る - コメントアウト）
  // old_function();  // 警告: 'old_function' is deprecated
  // legacy_function();  // 警告: 'legacy_function' is deprecated: use new_function() instead

  // 新しいクラスを使用
  ModernClass modern;
  modern.do_something();

  // 非推奨のクラスを使用（警告が出る - コメントアウト）
  // LegacyClass legacy;  // 警告: 'LegacyClass' is deprecated: use ModernClass instead
  // legacy.do_something();

  std::cout << std::endl;
}

// ============================================================================
// 5. 実用例: エラーハンドリング
// ============================================================================

enum class ErrorCode {
  Success,
  FileNotFound,
  PermissionDenied,
  InvalidArgument
};

[[nodiscard]]
ErrorCode open_file(const std::string& filename) {
  std::cout << "ファイルを開く: " << filename << std::endl;

  if (filename.empty()) {
    return ErrorCode::InvalidArgument;
  }

  // ファイルが存在しないと仮定
  if (filename == "nonexistent.txt") {
    return ErrorCode::FileNotFound;
  }

  return ErrorCode::Success;
}

void error_handling_example() {
  std::cout << "=== 実用例: エラーハンドリング ===" << std::endl;

  // 正しい使い方: エラーコードをチェック
  ErrorCode result1 = open_file("test.txt");
  if (result1 == ErrorCode::Success) {
    std::cout << "ファイルを正常に開きました" << std::endl;
  }

  ErrorCode result2 = open_file("nonexistent.txt");
  if (result2 == ErrorCode::FileNotFound) {
    std::cout << "エラー: ファイルが見つかりません" << std::endl;
  }

  // 間違った使い方（警告が出る - コメントアウト）
  // open_file("ignored.txt");  // 警告: 戻り値が無視されています

  std::cout << std::endl;
}

// ============================================================================
// 6. 実用例: デバッグとリリースビルド
// ============================================================================

class Logger {
 public:
  void log([[maybe_unused]] const std::string& message) {
#ifndef NDEBUG
    std::cout << "[LOG] " << message << std::endl;
#endif
    // リリースビルドでは何もしない
  }
};

void debug_release_example() {
  std::cout << "=== 実用例: デバッグとリリース ===" << std::endl;

  Logger logger;
  logger.log("アプリケーション開始");
  logger.log("処理中...");
  logger.log("アプリケーション終了");

  std::cout << std::endl;
}

// ============================================================================
// 7. 複数の属性の組み合わせ
// ============================================================================

[[nodiscard, deprecated("use get_new_value() instead")]]
int get_old_value() {
  return 100;
}

[[nodiscard]]
int get_new_value() {
  return 200;
}

void combined_attributes_example() {
  std::cout << "=== 複数の属性の組み合わせ ===" << std::endl;

  // 新しい関数を使用
  int value = get_new_value();
  std::cout << "新しい値: " << value << std::endl;

  // 古い関数を使用（警告が出る - コメントアウト）
  // int old_value = get_old_value();  // 警告: deprecated

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "C++17 Attributes のサンプル\n" << std::endl;

  nodiscard_examples();
  maybe_unused_examples();
  process_data(0, 42);
  std::cout << std::endl;
  fallthrough_examples();
  deprecated_examples();
  error_handling_example();
  debug_release_example();
  combined_attributes_example();

  std::cout << "全てのサンプルが完了しました！" << std::endl;
  std::cout << "\n注意: いくつかの例はコメントアウトされています。" << std::endl;
  std::cout << "コメントを外すと、コンパイラ警告を確認できます。" << std::endl;
  return 0;
}
