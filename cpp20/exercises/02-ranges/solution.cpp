// レンジ（Ranges）の演習問題 - 解答例

#include <algorithm>
#include <cctype>
#include <cmath>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

// ============================================================================
// 演習 2.2.1: 文字列のフィルタリングと変換（解答）
// ============================================================================

std::string to_upper(const std::string& str) {
  std::string result = str;
  std::ranges::transform(result, result.begin(),
                         [](unsigned char c) { return std::toupper(c); });
  return result;
}

void test_string_filtering() {
  std::cout << "=== 演習 2.2.1: 文字列のフィルタリングと変換（解答） ==="
            << std::endl;

  std::vector<std::string> words = {"cat",  "dog",     "elephant", "mouse",
                                    "lion", "giraffe", "ant",      "zebra"};

  std::cout << "元の文字列: ";
  for (const auto& word : words) {
    std::cout << word << " ";
  }
  std::cout << std::endl;

  // 5文字以上の文字列をフィルタして大文字に変換
  auto filtered =
      words | std::views::filter([](const std::string& s) { return s.length() >= 5; }) |
      std::views::transform([](const std::string& s) { return to_upper(s); });

  std::cout << "5文字以上を大文字化: ";
  for (const auto& word : filtered) {
    std::cout << word << " ";
  }
  std::cout << std::endl;

  std::cout << "✓ 文字列のフィルタリングと変換が正しく動作しています。"
            << std::endl;
  std::cout << std::endl;
}

// ============================================================================
// 演習 2.2.2: ゲームエンティティの処理（解答）
// ============================================================================

struct Entity {
  std::string name;
  bool active;
  float x, y, z;

  float distance_from(float px, float py, float pz) const {
    float dx = x - px;
    float dy = y - py;
    float dz = z - pz;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
  }
};

void test_entity_filtering() {
  std::cout << "=== 演習 2.2.2: ゲームエンティティの処理（解答） ==="
            << std::endl;

  std::vector<Entity> entities = {
      {"Enemy1", true, 10.0f, 0.0f, 0.0f},
      {"Enemy2", false, 5.0f, 0.0f, 0.0f},  // 非アクティブ
      {"Enemy3", true, 15.0f, 0.0f, 0.0f},
      {"Item1", true, 3.0f, 0.0f, 0.0f},
      {"Enemy4", true, 20.0f, 0.0f, 0.0f},
      {"Item2", false, 8.0f, 0.0f, 0.0f}  // 非アクティブ
  };

  float player_x = 0.0f;
  float player_y = 0.0f;
  float player_z = 0.0f;

  std::cout << "プレイヤー位置: (" << player_x << ", " << player_y << ", "
            << player_z << ")" << std::endl;

  std::cout << "\n全エンティティ:" << std::endl;
  for (const auto& e : entities) {
    std::cout << "  " << e.name << " (active: " << e.active
              << ", pos: " << e.x << ")" << std::endl;
  }

  // アクティブなエンティティのみをフィルタ
  auto active_entities = entities | std::views::filter([](const Entity& e) {
                           return e.active;
                         });

  std::cout << "\nアクティブなエンティティ:" << std::endl;
  for (const auto& e : active_entities) {
    std::cout << "  " << e.name << std::endl;
  }

  // アクティブなエンティティをvectorにコピー
  std::vector<Entity> active_vec;
  std::ranges::copy(active_entities, std::back_inserter(active_vec));

  // 距離でソート（プレイヤー位置からの距離）
  std::ranges::sort(active_vec, {}, [=](const Entity& e) {
    return e.distance_from(player_x, player_y, player_z);
  });

  // 最も近い3つを出力
  std::cout << "\n最も近い3つのエンティティ:" << std::endl;
  for (const auto& e : active_vec | std::views::take(3)) {
    float dist = e.distance_from(player_x, player_y, player_z);
    std::cout << "  " << e.name << " (距離: " << dist << ")" << std::endl;
  }

  std::cout << "\n✓ エンティティの処理が正しく動作しています。" << std::endl;
  std::cout << std::endl;
}

// ============================================================================
// おまけ: より複雑な例
// ============================================================================

struct GameObject {
  std::string name;
  std::string type;  // "enemy", "item", "npc"
  bool active;
  float x, y, z;
  int priority;  // 優先度（低い方が高優先）

  float distance_from(float px, float py, float pz) const {
    float dx = x - px;
    float dy = y - py;
    float dz = z - pz;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
  }
};

void advanced_example() {
  std::cout << "=== おまけ: 複雑なフィルタリングとソート ===" << std::endl;

  std::vector<GameObject> objects = {
      {"Enemy1", "enemy", true, 10.0f, 0.0f, 0.0f, 2},
      {"Item1", "item", true, 3.0f, 0.0f, 0.0f, 1},
      {"Enemy2", "enemy", false, 5.0f, 0.0f, 0.0f, 2},
      {"NPC1", "npc", true, 7.0f, 0.0f, 0.0f, 3},
      {"Item2", "item", true, 12.0f, 0.0f, 0.0f, 1},
      {"Enemy3", "enemy", true, 15.0f, 0.0f, 0.0f, 2}};

  float player_x = 0.0f, player_y = 0.0f, player_z = 0.0f;

  // 複雑な条件でフィルタリング
  // - アクティブである
  // - 敵またはアイテムである
  // - 距離が20以内である
  auto nearby_targets =
      objects |
      std::views::filter([](const GameObject& obj) { return obj.active; }) |
      std::views::filter([](const GameObject& obj) {
        return obj.type == "enemy" || obj.type == "item";
      }) |
      std::views::filter([=](const GameObject& obj) {
        return obj.distance_from(player_x, player_y, player_z) <= 20.0f;
      });

  // vectorにコピーしてソート（優先度 → 距離の順）
  std::vector<GameObject> targets;
  std::ranges::copy(nearby_targets, std::back_inserter(targets));

  std::ranges::sort(targets, [=](const GameObject& a, const GameObject& b) {
    if (a.priority != b.priority) {
      return a.priority < b.priority;  // 優先度が低い方が先
    }
    return a.distance_from(player_x, player_y, player_z) <
           b.distance_from(player_x, player_y, player_z);
  });

  std::cout << "優先ターゲット（優先度順、距離順）:" << std::endl;
  for (const auto& obj : targets) {
    float dist = obj.distance_from(player_x, player_y, player_z);
    std::cout << "  " << obj.name << " (" << obj.type
              << ", 優先度: " << obj.priority << ", 距離: " << dist << ")"
              << std::endl;
  }

  std::cout << "\n✓ 複雑なフィルタリングが正しく動作しています。"
            << std::endl;
  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "C++20 レンジ（Ranges）の演習問題 - 解答例\n" << std::endl;

  test_string_filtering();
  test_entity_filtering();
  advanced_example();

  std::cout << "全ての演習が完了しました！" << std::endl;
  std::cout << "\nレンジの利点:" << std::endl;
  std::cout << "  ✓ 遅延評価（必要なときだけ計算）" << std::endl;
  std::cout << "  ✓ パイプライン構文で読みやすい" << std::endl;
  std::cout << "  ✓ コピー不要（ビューは参照）" << std::endl;
  std::cout << "  ✓ 関数型プログラミング風の記述" << std::endl;

  return 0;
}
