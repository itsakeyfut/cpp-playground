// std::filesystemの演習
// TODOコメントを埋めて、プログラムを完成させてください。

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

// ============================================================================
// 演習 1.10.1: 画像ファイルの検索と合計サイズ計算
// ============================================================================

struct ImageFileInfo {
  fs::path path;
  std::uintmax_t size;
  std::string extension;
};

// TODO: 指定ディレクトリ内の画像ファイルを再帰的に検索する関数を実装してください
// 対象拡張子: .png, .jpg, .jpeg, .bmp, .gif
// ヒント1: fs::recursive_directory_iteratorを使います
// ヒント2: entry.is_regular_file()でファイルかチェック
// ヒント3: entry.path().extension()で拡張子を取得
// ヒント4: 拡張子は大文字小文字を区別しないようにしましょう
std::vector<ImageFileInfo> find_image_files(const fs::path& directory) {
  std::vector<ImageFileInfo> images;

  // TODO: ここに実装してください

  return images;
}

// TODO: 画像ファイルのリストから合計サイズを計算する関数を実装してください
std::uintmax_t calculate_total_size(const std::vector<ImageFileInfo>& images) {
  std::uintmax_t total = 0;
  // TODO: ここに実装してください
  return total;
}

void exercise_1_10_1() {
  std::cout << "=== 演習 1.10.1: 画像ファイルの検索 ===" << std::endl;

  // カレントディレクトリを検索
  fs::path search_dir = fs::current_path();
  std::cout << "Searching in: " << search_dir << std::endl;

  // TODO: find_image_files関数を呼び出してください

  // TODO: 見つかった画像ファイルを表示してください
  // 出力形式: "  image.png (1234 bytes)"

  // TODO: 合計サイズを計算して表示してください
  // 出力形式:
  //   "Total: X bytes"
  //   "     = X KB"
  //   "     = X MB"

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習1: ファイルの拡張子別統計
// ============================================================================

struct ExtensionStats {
  int count;
  std::uintmax_t total_size;
};

// TODO: 指定ディレクトリ内のファイルを拡張子別に集計する関数を実装してください
// 戻り値: map<拡張子, ExtensionStats>
// ヒント: std::map<std::string, ExtensionStats> を使います
std::map<std::string, ExtensionStats> analyze_by_extension(
    const fs::path& directory) {
  std::map<std::string, ExtensionStats> stats;

  // TODO: ここに実装してください

  return stats;
}

void bonus_exercise_1() {
  std::cout << "=== ボーナス演習1: 拡張子別統計 ===" << std::endl;

  fs::path search_dir = fs::current_path();

  // TODO: analyze_by_extension関数を呼び出してください

  // TODO: 結果を表示してください
  // 出力形式:
  //   ".cpp: 5 files, 12345 bytes"
  //   ".h: 3 files, 6789 bytes"

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習2: 大きなファイルの検索
// ============================================================================

// TODO: 指定サイズ以上のファイルを検索する関数を実装してください
std::vector<ImageFileInfo> find_large_files(const fs::path& directory,
                                             std::uintmax_t min_size) {
  std::vector<ImageFileInfo> large_files;

  // TODO: ここに実装してください

  return large_files;
}

void bonus_exercise_2() {
  std::cout << "=== ボーナス演習2: 大きなファイルの検索 ===" << std::endl;

  fs::path search_dir = fs::current_path();
  std::uintmax_t threshold = 10 * 1024;  // 10KB以上

  // TODO: find_large_files関数を呼び出してください

  // TODO: 見つかったファイルを表示してください
  // サイズでソートして表示すると良いでしょう

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習3: ディレクトリツリーの表示
// ============================================================================

// TODO: ディレクトリツリーを表示する関数を実装してください
// インデントを使って階層構造を表現します
// 例:
//   dir1/
//     file1.txt
//     subdir/
//       file2.txt
void print_directory_tree(const fs::path& directory, int indent_level = 0) {
  // TODO: ここに実装してください
  // ヒント1: std::string(indent_level * 2, ' ')でインデントを作成
  // ヒント2: 再帰呼び出しで階層を下る
  // ヒント3: ディレクトリには末尾に'/'を付ける
}

void bonus_exercise_3() {
  std::cout << "=== ボーナス演習3: ディレクトリツリーの表示 ===" << std::endl;

  fs::path search_dir = fs::current_path();
  std::cout << "Directory tree of: " << search_dir.filename() << "/"
            << std::endl;

  // TODO: print_directory_tree関数を呼び出してください
  // 注意: 大きなディレクトリでは出力が多くなるので、
  //       深さ制限を追加すると良いでしょう

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "std::filesystemの演習\n" << std::endl;

  try {
    exercise_1_10_1();
    bonus_exercise_1();
    bonus_exercise_2();
    bonus_exercise_3();

    std::cout << "演習が完了しました！" << std::endl;
    std::cout << "solution.cppと比較して、答え合わせをしましょう。" << std::endl;
  } catch (const fs::filesystem_error& e) {
    std::cerr << "Filesystem error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
