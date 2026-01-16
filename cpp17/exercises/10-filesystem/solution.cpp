// std::filesystemの演習 - 解答例

#include <algorithm>
#include <cctype>
#include <filesystem>
#include <iostream>
#include <map>
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

// 拡張子を小文字に変換
std::string to_lower(const std::string& str) {
  std::string result = str;
  std::transform(result.begin(), result.end(), result.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  return result;
}

std::vector<ImageFileInfo> find_image_files(const fs::path& directory) {
  std::vector<ImageFileInfo> images;

  const std::vector<std::string> image_extensions = {".png", ".jpg", ".jpeg",
                                                      ".bmp", ".gif"};

  for (const auto& entry : fs::recursive_directory_iterator(directory)) {
    if (entry.is_regular_file()) {
      std::string ext = to_lower(entry.path().extension().string());

      // 画像ファイルの拡張子かチェック
      if (std::find(image_extensions.begin(), image_extensions.end(), ext) !=
          image_extensions.end()) {
        images.push_back(
            {entry.path(), entry.file_size(), entry.path().extension()});
      }
    }
  }

  return images;
}

std::uintmax_t calculate_total_size(const std::vector<ImageFileInfo>& images) {
  std::uintmax_t total = 0;
  for (const auto& img : images) {
    total += img.size;
  }
  return total;
}

void exercise_1_10_1() {
  std::cout << "=== 演習 1.10.1: 画像ファイルの検索 ===" << std::endl;

  fs::path search_dir = fs::current_path();
  std::cout << "Searching in: " << search_dir << std::endl;

  auto images = find_image_files(search_dir);

  std::cout << "\nFound " << images.size() << " image files:" << std::endl;
  int count = 0;
  for (const auto& img : images) {
    std::cout << "  " << fs::relative(img.path, search_dir) << " ("
              << img.size << " bytes)" << std::endl;
    if (++count >= 10) {
      std::cout << "  ... (showing first 10 files)" << std::endl;
      break;
    }
  }

  auto total = calculate_total_size(images);
  std::cout << "\nTotal: " << total << " bytes" << std::endl;
  std::cout << "     = " << total / 1024 << " KB" << std::endl;
  std::cout << "     = " << total / 1024 / 1024 << " MB" << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習1: ファイルの拡張子別統計
// ============================================================================

struct ExtensionStats {
  int count;
  std::uintmax_t total_size;
};

std::map<std::string, ExtensionStats> analyze_by_extension(
    const fs::path& directory) {
  std::map<std::string, ExtensionStats> stats;

  for (const auto& entry : fs::recursive_directory_iterator(directory)) {
    if (entry.is_regular_file()) {
      std::string ext = to_lower(entry.path().extension().string());
      if (ext.empty()) {
        ext = "(no extension)";
      }

      auto& stat = stats[ext];
      stat.count++;
      stat.total_size += entry.file_size();
    }
  }

  return stats;
}

void bonus_exercise_1() {
  std::cout << "=== ボーナス演習1: 拡張子別統計 ===" << std::endl;

  fs::path search_dir = fs::current_path();
  auto stats = analyze_by_extension(search_dir);

  std::cout << "File statistics by extension:" << std::endl;
  for (const auto& [ext, stat] : stats) {
    std::cout << "  " << ext << ": " << stat.count << " files, "
              << stat.total_size << " bytes" << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習2: 大きなファイルの検索
// ============================================================================

std::vector<ImageFileInfo> find_large_files(const fs::path& directory,
                                             std::uintmax_t min_size) {
  std::vector<ImageFileInfo> large_files;

  for (const auto& entry : fs::recursive_directory_iterator(directory)) {
    if (entry.is_regular_file() && entry.file_size() >= min_size) {
      large_files.push_back(
          {entry.path(), entry.file_size(), entry.path().extension()});
    }
  }

  // サイズでソート（降順）
  std::sort(large_files.begin(), large_files.end(),
            [](const ImageFileInfo& a, const ImageFileInfo& b) {
              return a.size > b.size;
            });

  return large_files;
}

void bonus_exercise_2() {
  std::cout << "=== ボーナス演習2: 大きなファイルの検索 ===" << std::endl;

  fs::path search_dir = fs::current_path();
  std::uintmax_t threshold = 10 * 1024;  // 10KB以上

  auto large_files = find_large_files(search_dir, threshold);

  std::cout << "Files larger than " << threshold << " bytes:" << std::endl;
  int count = 0;
  for (const auto& file : large_files) {
    std::cout << "  " << fs::relative(file.path, search_dir) << " ("
              << file.size << " bytes)" << std::endl;
    if (++count >= 10) {
      std::cout << "  ... (showing first 10 files)" << std::endl;
      break;
    }
  }

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習3: ディレクトリツリーの表示
// ============================================================================

void print_directory_tree(const fs::path& directory, int indent_level = 0,
                          int max_depth = 3) {
  if (indent_level > max_depth) {
    return;
  }

  std::string indent(indent_level * 2, ' ');

  try {
    std::vector<fs::directory_entry> entries;
    for (const auto& entry : fs::directory_iterator(directory)) {
      entries.push_back(entry);
    }

    // ディレクトリを先に表示
    std::sort(entries.begin(), entries.end(),
              [](const fs::directory_entry& a, const fs::directory_entry& b) {
                if (a.is_directory() != b.is_directory()) {
                  return a.is_directory();
                }
                return a.path().filename() < b.path().filename();
              });

    int count = 0;
    for (const auto& entry : entries) {
      std::cout << indent << entry.path().filename().string();

      if (entry.is_directory()) {
        std::cout << "/" << std::endl;
        print_directory_tree(entry.path(), indent_level + 1, max_depth);
      } else if (entry.is_regular_file()) {
        std::cout << " (" << entry.file_size() << " bytes)" << std::endl;
      } else {
        std::cout << std::endl;
      }

      if (++count >= 20 && indent_level == 0) {
        std::cout << indent << "... (truncated)" << std::endl;
        break;
      }
    }
  } catch (const fs::filesystem_error&) {
    std::cout << indent << "(permission denied)" << std::endl;
  }
}

void bonus_exercise_3() {
  std::cout << "=== ボーナス演習3: ディレクトリツリーの表示 ===" << std::endl;

  fs::path search_dir = fs::current_path();
  std::cout << "Directory tree of: " << search_dir.filename() << "/"
            << std::endl;

  print_directory_tree(search_dir);

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "std::filesystemの演習 - 解答例\n" << std::endl;

  try {
    exercise_1_10_1();
    bonus_exercise_1();
    bonus_exercise_2();
    bonus_exercise_3();

    std::cout << "お疲れ様でした！" << std::endl;
  } catch (const fs::filesystem_error& e) {
    std::cerr << "Filesystem error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
