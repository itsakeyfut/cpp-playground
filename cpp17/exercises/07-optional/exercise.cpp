// std::optionalの演習
// TODOコメントを埋めて、プログラムを完成させてください。

#include <iostream>
#include <optional>
#include <string>
#include <unordered_map>

// ============================================================================
// 演習 1.7.1: 設定ファイルのパーサー
// ============================================================================

// 設定ファイルを表すクラス
class ConfigParser {
 private:
  std::unordered_map<std::string, std::string> data_;

 public:
  // 設定値を追加
  void set(const std::string& key, const std::string& value) {
    data_[key] = value;
  }

  // TODO: get関数を実装してください
  // キーが存在する場合は値を、存在しない場合はstd::nulloptを返す
  // ヒント: std::optional<std::string> を返り値にします
  // ヒント: data_.find(key) を使ってキーを検索します
  // ヒント: data_.end() と比較して、見つかったか判定します

  // TODO: get_int関数を実装してください
  // キーが存在し、かつ整数に変換できる場合は値を返す
  // それ以外の場合はstd::nulloptを返す
  // ヒント: get()の結果をチェックして、std::stoi()で変換を試みます
  // ヒント: 変換に失敗した場合は例外が投げられるので、try-catchを使います

  // TODO: get_bool関数を実装してください
  // キーが存在し、値が"true"または"false"の場合はbool値を返す
  // それ以外の場合はstd::nulloptを返す
};

void exercise_1_7_1() {
  std::cout << "=== 演習 1.7.1: 設定ファイルパーサー ===" << std::endl;

  ConfigParser config;
  config.set("game_title", "My Awesome Game");
  config.set("screen_width", "1920");
  config.set("screen_height", "1080");
  config.set("fullscreen", "true");
  config.set("invalid_number", "abc");

  // TODO: get関数を使って、存在するキーの値を取得してください
  // ヒント: if (auto value = config.get("game_title"); value) { ... }

  // TODO: get関数を使って、存在しないキーの値を取得してください
  // value_or()を使ってデフォルト値を指定してください

  // TODO: get_int関数を使って、screen_widthを整数として取得してください

  // TODO: get_int関数を使って、invalid_numberを整数として取得を試みてください
  // 失敗することを確認してください

  // TODO: get_bool関数を使って、fullscreenをbool値として取得してください

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習: データベース風の検索
// ============================================================================

struct Player {
  int id;
  std::string name;
  int score;
};

// プレイヤーのリスト（簡易的なデータベース）
std::vector<Player> players = {
    {1, "Alice", 100},
    {2, "Bob", 85},
    {3, "Carol", 92},
    {4, "David", 78}};

// TODO: IDでプレイヤーを検索する関数を実装してください
// 見つかった場合はPlayerを、見つからなかった場合はstd::nulloptを返す
std::optional<Player> find_player_by_id(int id) {
  // TODO: ここに実装してください
  return std::nullopt;
}

// TODO: スコアが指定値以上の最初のプレイヤーを返す関数を実装してください
std::optional<Player> find_player_by_min_score(int min_score) {
  // TODO: ここに実装してください
  return std::nullopt;
}

void bonus_exercise() {
  std::cout << "=== ボーナス演習: プレイヤー検索 ===" << std::endl;

  // TODO: ID=2のプレイヤーを検索してください
  // 見つかった場合は名前とスコアを出力してください

  // TODO: ID=999のプレイヤーを検索してください（存在しない）
  // 見つからなかった場合は適切なメッセージを出力してください

  // TODO: スコアが90以上のプレイヤーを検索してください

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "std::optionalの演習\n" << std::endl;

  exercise_1_7_1();
  bonus_exercise();

  std::cout << "演習が完了しました！" << std::endl;
  std::cout << "solution.cppと比較して、答え合わせをしましょう。" << std::endl;
  return 0;
}
