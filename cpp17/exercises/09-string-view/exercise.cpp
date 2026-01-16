// std::string_viewの演習
// TODOコメントを埋めて、プログラムを完成させてください。

#include <iostream>
#include <string>
#include <string_view>
#include <vector>

// ============================================================================
// 演習 1.9.1: CSVパーサー
// ============================================================================

// TODO: CSV行を解析して、各フィールドをstring_viewとして返す関数を実装してください
// 例: "apple,banana,cherry" -> ["apple", "banana", "cherry"]
// ヒント: findとsubstrを使います
// ヒント: カンマで区切られた各部分をstring_viewとして返します
std::vector<std::string_view> parse_csv_line(std::string_view line) {
  std::vector<std::string_view> fields;

  // TODO: ここに実装してください
  // ヒント1: size_t start = 0; で開始位置を記録
  // ヒント2: line.find(',', start) でカンマを探す
  // ヒント3: 見つかった位置までの部分文字列を追加
  // ヒント4: 最後のフィールドも忘れずに追加

  return fields;
}

void exercise_1_9_1() {
  std::cout << "=== 演習 1.9.1: CSVパーサー ===" << std::endl;

  std::vector<std::string> csv_lines = {
      "Alice,100,Tokyo",
      "Bob,85,New York",
      "Carol,92,London",
      "David,78,Paris"};

  // TODO: 各行をパースして、結果を出力してください
  // 出力形式: "Alice | 100 | Tokyo"

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習1: 空白文字のトリミング
// ============================================================================

// TODO: 文字列の前後の空白を削除する関数を実装してください
// 例: "  hello  " -> "hello"
// ヒント: remove_prefix と remove_suffix を使います
// ヒント: isspace()で空白文字を判定します
std::string_view trim(std::string_view sv) {
  // TODO: ここに実装してください
  return sv;
}

void bonus_exercise_1() {
  std::cout << "=== ボーナス演習1: トリミング ===" << std::endl;

  std::vector<std::string> strings = {
      "  hello  ", "\tworld\n", "  C++  ", "  no trim needed"};

  // TODO: 各文字列をトリミングして、結果を出力してください
  // 出力形式: "'  hello  ' -> 'hello'"

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習2: ファイルパスの解析
// ============================================================================

struct PathInfo {
  std::string_view directory;  // ディレクトリ部分
  std::string_view filename;   // ファイル名（拡張子含む）
  std::string_view stem;       // ファイル名（拡張子なし）
  std::string_view extension;  // 拡張子
};

// TODO: ファイルパスを解析する関数を実装してください
// 例: "/home/user/document.txt"
//   -> directory: "/home/user/"
//   -> filename: "document.txt"
//   -> stem: "document"
//   -> extension: ".txt"
// ヒント: rfind()で最後の'/'と'.'を探します
PathInfo parse_path(std::string_view path) {
  PathInfo info;

  // TODO: ここに実装してください
  // ヒント1: rfind('/') で最後のスラッシュを探す
  // ヒント2: rfind('.') で最後のドットを探す
  // ヒント3: substrで各部分を切り出す

  return info;
}

void bonus_exercise_2() {
  std::cout << "=== ボーナス演習2: パス解析 ===" << std::endl;

  std::vector<std::string_view> paths = {
      "/home/user/document.txt",
      "C:\\Windows\\System32\\kernel32.dll",
      "image.png",
      "archive.tar.gz"};

  // TODO: 各パスを解析して、結果を出力してください
  // 出力形式:
  //   Path: /home/user/document.txt
  //   - Directory: /home/user/
  //   - Filename: document.txt
  //   - Stem: document
  //   - Extension: .txt

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習3: 大文字小文字を無視した比較
// ============================================================================

// TODO: 大文字小文字を無視して文字列を比較する関数を実装してください
// 例: "Hello" と "hello" は等しい
// ヒント: std::tolowerを使います
bool equal_ignore_case(std::string_view sv1, std::string_view sv2) {
  // TODO: ここに実装してください
  return false;
}

void bonus_exercise_3() {
  std::cout << "=== ボーナス演習3: 大文字小文字を無視した比較 ===" << std::endl;

  // TODO: 以下のペアを比較して、結果を出力してください
  std::vector<std::pair<std::string_view, std::string_view>> pairs = {
      {"Hello", "hello"},
      {"World", "WORLD"},
      {"C++", "c++"},
      {"Test", "TEST"}};

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "std::string_viewの演習\n" << std::endl;

  exercise_1_9_1();
  bonus_exercise_1();
  bonus_exercise_2();
  bonus_exercise_3();

  std::cout << "演習が完了しました！" << std::endl;
  std::cout << "solution.cppと比較して、答え合わせをしましょう。" << std::endl;
  return 0;
}
