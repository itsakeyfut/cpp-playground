// std::optionalの演習 - 解答例

#include <iostream>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

// ============================================================================
// 演習 1.7.1: 設定ファイルのパーサー
// ============================================================================

class ConfigParser {
 private:
  std::unordered_map<std::string, std::string> data_;

 public:
  void set(const std::string& key, const std::string& value) {
    data_[key] = value;
  }

  // キーに対応する値を取得（存在しない場合はnullopt）
  std::optional<std::string> get(const std::string& key) const {
    auto it = data_.find(key);
    if (it != data_.end()) {
      return it->second;
    }
    return std::nullopt;
  }

  // 整数値として取得
  std::optional<int> get_int(const std::string& key) const {
    auto value = get(key);
    if (!value) {
      return std::nullopt;
    }

    try {
      return std::stoi(*value);
    } catch (...) {
      return std::nullopt;
    }
  }

  // bool値として取得
  std::optional<bool> get_bool(const std::string& key) const {
    auto value = get(key);
    if (!value) {
      return std::nullopt;
    }

    if (*value == "true") {
      return true;
    } else if (*value == "false") {
      return false;
    }
    return std::nullopt;
  }
};

void exercise_1_7_1() {
  std::cout << "=== 演習 1.7.1: 設定ファイルパーサー ===" << std::endl;

  ConfigParser config;
  config.set("game_title", "My Awesome Game");
  config.set("screen_width", "1920");
  config.set("screen_height", "1080");
  config.set("fullscreen", "true");
  config.set("invalid_number", "abc");

  // 存在するキーの取得
  if (auto title = config.get("game_title"); title) {
    std::cout << "Game Title: " << *title << std::endl;
  }

  // 存在しないキーの取得（デフォルト値を使用）
  std::string developer = config.get("developer").value_or("Unknown Developer");
  std::cout << "Developer: " << developer << std::endl;

  // 整数値の取得
  if (auto width = config.get_int("screen_width"); width) {
    std::cout << "Screen Width: " << *width << " pixels" << std::endl;
  }

  // 無効な整数値の取得を試みる
  if (auto invalid = config.get_int("invalid_number"); !invalid) {
    std::cout << "invalid_number は整数に変換できません" << std::endl;
  }

  // bool値の取得
  if (auto fullscreen = config.get_bool("fullscreen"); fullscreen) {
    std::cout << "Fullscreen: " << (*fullscreen ? "Yes" : "No") << std::endl;
  }

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

std::vector<Player> players = {
    {1, "Alice", 100},
    {2, "Bob", 85},
    {3, "Carol", 92},
    {4, "David", 78}};

// IDでプレイヤーを検索
std::optional<Player> find_player_by_id(int id) {
  for (const auto& player : players) {
    if (player.id == id) {
      return player;
    }
  }
  return std::nullopt;
}

// スコアが指定値以上の最初のプレイヤーを検索
std::optional<Player> find_player_by_min_score(int min_score) {
  for (const auto& player : players) {
    if (player.score >= min_score) {
      return player;
    }
  }
  return std::nullopt;
}

void bonus_exercise() {
  std::cout << "=== ボーナス演習: プレイヤー検索 ===" << std::endl;

  // ID=2のプレイヤーを検索
  if (auto player = find_player_by_id(2); player) {
    std::cout << "Found player: " << player->name
              << " (score: " << player->score << ")" << std::endl;
  }

  // ID=999のプレイヤーを検索（存在しない）
  if (auto player = find_player_by_id(999); !player) {
    std::cout << "Player with ID=999 not found" << std::endl;
  }

  // スコアが90以上のプレイヤーを検索
  if (auto player = find_player_by_min_score(90); player) {
    std::cout << "First player with score >= 90: " << player->name
              << " (score: " << player->score << ")" << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "std::optionalの演習 - 解答例\n" << std::endl;

  exercise_1_7_1();
  bonus_exercise();

  std::cout << "お疲れ様でした！" << std::endl;
  return 0;
}
