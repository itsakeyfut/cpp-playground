// std::filesystemのサンプルコード
// このファイルは写経用です。コードを理解しながら写経してください。

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

// ============================================================================
// 1. 基本的なパス操作
// ============================================================================

void basic_path_operations() {
  std::cout << "=== 基本的なパス操作 ===" << std::endl;

  // パスの作成
  fs::path p1 = "/home/user/document.txt";
  fs::path p2 = "C:\\Windows\\System32\\kernel32.dll";
  fs::path p3 = "relative/path/file.cpp";

  std::cout << "Path 1: " << p1 << std::endl;
  std::cout << "Path 2: " << p2 << std::endl;
  std::cout << "Path 3: " << p3 << std::endl;

  // パスの各部分を取得
  fs::path sample = "/home/user/game/assets/texture.png";
  std::cout << "\nPath analysis of: " << sample << std::endl;
  std::cout << "  filename: " << sample.filename() << std::endl;
  std::cout << "  stem: " << sample.stem() << std::endl;
  std::cout << "  extension: " << sample.extension() << std::endl;
  std::cout << "  parent_path: " << sample.parent_path() << std::endl;
  std::cout << "  root_name: " << sample.root_name() << std::endl;
  std::cout << "  root_path: " << sample.root_path() << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 2. パスの結合と操作
// ============================================================================

void path_manipulation() {
  std::cout << "=== パスの結合と操作 ===" << std::endl;

  fs::path base = "project";
  fs::path sub = "src";
  fs::path file = "main.cpp";

  // operator/ でパスを結合
  fs::path full = base / sub / file;
  std::cout << "Combined path: " << full << std::endl;

  // 拡張子の変更
  fs::path original = "document.txt";
  fs::path changed = original;
  changed.replace_extension(".pdf");
  std::cout << "Original: " << original << " -> Changed: " << changed
            << std::endl;

  // ファイル名の置き換え
  fs::path p = "dir/old.txt";
  p.replace_filename("new.txt");
  std::cout << "After replace_filename: " << p << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 3. ファイル・ディレクトリの存在確認
// ============================================================================

void existence_check() {
  std::cout << "=== ファイル・ディレクトリの存在確認 ===" << std::endl;

  // 現在のディレクトリ
  fs::path current = fs::current_path();
  std::cout << "Current directory: " << current << std::endl;

  // 存在確認
  std::cout << "Current directory exists: " << fs::exists(current) << std::endl;
  std::cout << "Is directory: " << fs::is_directory(current) << std::endl;

  // 一時ディレクトリ
  fs::path temp = fs::temp_directory_path();
  std::cout << "Temp directory: " << temp << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 4. ディレクトリ走査（非再帰）
// ============================================================================

void directory_iteration() {
  std::cout << "=== ディレクトリ走査（非再帰） ===" << std::endl;

  fs::path current = fs::current_path();
  std::cout << "Listing files in: " << current << std::endl;

  int count = 0;
  for (const auto& entry : fs::directory_iterator(current)) {
    std::cout << "  ";
    if (entry.is_directory()) {
      std::cout << "[DIR]  ";
    } else if (entry.is_regular_file()) {
      std::cout << "[FILE] ";
    } else {
      std::cout << "[?]    ";
    }

    std::cout << entry.path().filename();

    if (entry.is_regular_file()) {
      std::cout << " (" << entry.file_size() << " bytes)";
    }

    std::cout << std::endl;

    if (++count >= 10) {
      std::cout << "  ... (showing first 10 entries)" << std::endl;
      break;
    }
  }

  std::cout << std::endl;
}

// ============================================================================
// 5. 再帰的なディレクトリ走査
// ============================================================================

void recursive_directory_iteration() {
  std::cout << "=== 再帰的なディレクトリ走査 ===" << std::endl;

  fs::path current = fs::current_path();
  std::cout << "Recursively listing files in: " << current << std::endl;

  int count = 0;
  for (const auto& entry : fs::recursive_directory_iterator(current)) {
    if (entry.is_regular_file()) {
      // 相対パスを表示
      auto relative = fs::relative(entry.path(), current);
      std::cout << "  " << relative << std::endl;

      if (++count >= 10) {
        std::cout << "  ... (showing first 10 files)" << std::endl;
        break;
      }
    }
  }

  std::cout << std::endl;
}

// ============================================================================
// 6. ファイルのサイズ計算
// ============================================================================

void file_size_example() {
  std::cout << "=== ファイルのサイズ計算 ===" << std::endl;

  // このソースファイル自体のサイズを取得
  fs::path this_file = __FILE__;

  if (fs::exists(this_file)) {
    auto size = fs::file_size(this_file);
    std::cout << "This file (" << this_file.filename() << "): " << size
              << " bytes" << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// 7. ディレクトリとファイルの作成・削除
// ============================================================================

void create_and_delete_example() {
  std::cout << "=== ディレクトリとファイルの作成・削除 ===" << std::endl;

  // テスト用のディレクトリを作成
  fs::path test_dir = "test_directory";

  // ディレクトリを作成（既に存在する場合は何もしない）
  if (fs::create_directory(test_dir)) {
    std::cout << "Created directory: " << test_dir << std::endl;
  } else {
    std::cout << "Directory already exists: " << test_dir << std::endl;
  }

  // ネストしたディレクトリを作成
  fs::path nested = test_dir / "sub1" / "sub2";
  fs::create_directories(nested);
  std::cout << "Created nested directories: " << nested << std::endl;

  // ファイルを作成
  fs::path test_file = test_dir / "test.txt";
  {
    std::ofstream ofs(test_file);
    ofs << "Hello, filesystem!" << std::endl;
  }
  std::cout << "Created file: " << test_file << std::endl;

  // ファイルサイズを確認
  std::cout << "File size: " << fs::file_size(test_file) << " bytes"
            << std::endl;

  // ファイルをコピー
  fs::path copied = test_dir / "test_copy.txt";
  fs::copy(test_file, copied);
  std::cout << "Copied to: " << copied << std::endl;

  // クリーンアップ
  std::cout << "\nCleaning up..." << std::endl;
  fs::remove_all(test_dir);
  std::cout << "Removed directory: " << test_dir << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 8. 拡張子でファイルをフィルタリング
// ============================================================================

std::vector<fs::path> find_files_by_extension(const fs::path& dir,
                                               const std::string& ext) {
  std::vector<fs::path> result;

  for (const auto& entry : fs::recursive_directory_iterator(dir)) {
    if (entry.is_regular_file() && entry.path().extension() == ext) {
      result.push_back(entry.path());
    }
  }

  return result;
}

void filter_by_extension_example() {
  std::cout << "=== 拡張子でファイルをフィルタリング ===" << std::endl;

  fs::path current = fs::current_path();

  // .cppファイルを検索
  auto cpp_files = find_files_by_extension(current, ".cpp");
  std::cout << "Found " << cpp_files.size() << " .cpp files:" << std::endl;

  int count = 0;
  for (const auto& file : cpp_files) {
    std::cout << "  " << fs::relative(file, current) << std::endl;
    if (++count >= 5) {
      std::cout << "  ... (showing first 5 files)" << std::endl;
      break;
    }
  }

  std::cout << std::endl;
}

// ============================================================================
// 9. ディレクトリの合計サイズを計算
// ============================================================================

std::uintmax_t calculate_directory_size(const fs::path& dir) {
  std::uintmax_t total_size = 0;

  for (const auto& entry : fs::recursive_directory_iterator(dir)) {
    if (entry.is_regular_file()) {
      total_size += entry.file_size();
    }
  }

  return total_size;
}

void directory_size_example() {
  std::cout << "=== ディレクトリの合計サイズ ===" << std::endl;

  fs::path current = fs::current_path();
  auto size = calculate_directory_size(current);

  std::cout << "Total size of " << current.filename() << ": " << size
            << " bytes" << std::endl;
  std::cout << "  = " << size / 1024 << " KB" << std::endl;
  std::cout << "  = " << size / 1024 / 1024 << " MB" << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "C++17 std::filesystemのサンプル\n" << std::endl;

  try {
    basic_path_operations();
    path_manipulation();
    existence_check();
    directory_iteration();
    recursive_directory_iteration();
    file_size_example();
    create_and_delete_example();
    filter_by_extension_example();
    directory_size_example();

    std::cout << "全てのサンプルが完了しました！" << std::endl;
  } catch (const fs::filesystem_error& e) {
    std::cerr << "Filesystem error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
