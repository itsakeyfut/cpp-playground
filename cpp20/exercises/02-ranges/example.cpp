// レンジ（Ranges）のサンプルコード
// このファイルは写経用です。コードを理解しながら写経してください。

#include <algorithm>
#include <iostream>
#include <map>
#include <ranges>
#include <string>
#include <vector>

// ============================================================================
// 1. 基本的なパイプライン構文
// ============================================================================

void basic_pipeline_examples() {
  std::cout << "=== 基本的なパイプライン構文 ===" << std::endl;

  std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  // filter: 偶数のみ
  auto evens = nums | std::views::filter([](int n) { return n % 2 == 0; });

  std::cout << "偶数: ";
  for (int n : evens) {
    std::cout << n << " ";
  }
  std::cout << std::endl;

  // transform: 2乗
  auto squares =
      nums | std::views::transform([](int n) { return n * n; });

  std::cout << "2乗: ";
  for (int n : squares) {
    std::cout << n << " ";
  }
  std::cout << std::endl;

  // パイプラインの組み合わせ（遅延評価）
  auto result = nums | std::views::filter([](int n) { return n % 2 == 0; }) |
                std::views::transform([](int n) { return n * n; }) |
                std::views::take(3);

  std::cout << "偶数を2乗して最初の3つ: ";
  for (int n : result) {
    std::cout << n << " ";
  }
  std::cout << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 2. 主要なビュー
// ============================================================================

void views_examples() {
  std::cout << "=== 主要なビュー ===" << std::endl;

  std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  // take: 最初のN個
  std::cout << "最初の5個: ";
  for (int n : nums | std::views::take(5)) {
    std::cout << n << " ";
  }
  std::cout << std::endl;

  // drop: 最初のN個をスキップ
  std::cout << "最初の3個をスキップ: ";
  for (int n : nums | std::views::drop(3)) {
    std::cout << n << " ";
  }
  std::cout << std::endl;

  // take_while: 条件を満たす間
  std::cout << "5未満の要素: ";
  for (int n : nums | std::views::take_while([](int n) { return n < 5; })) {
    std::cout << n << " ";
  }
  std::cout << std::endl;

  // reverse: 逆順
  std::cout << "逆順: ";
  for (int n : nums | std::views::reverse) {
    std::cout << n << " ";
  }
  std::cout << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 3. keys/values（mapの処理）
// ============================================================================

void map_views_examples() {
  std::cout << "=== keys/valuesビュー ===" << std::endl;

  std::map<std::string, int> scores = {
      {"Alice", 100}, {"Bob", 85}, {"Carol", 92}, {"Dave", 78}};

  // keys: キーのみ取得
  std::cout << "プレイヤー名: ";
  for (const auto& name : scores | std::views::keys) {
    std::cout << name << " ";
  }
  std::cout << std::endl;

  // values: 値のみ取得
  std::cout << "スコア: ";
  for (int score : scores | std::views::values) {
    std::cout << score << " ";
  }
  std::cout << std::endl;

  // スコアが90以上のプレイヤーをフィルタ
  std::cout << "90点以上のプレイヤー: ";
  for (const auto& [name, score] :
       scores | std::views::filter([](const auto& p) { return p.second >= 90; })) {
    std::cout << name << "(" << score << ") ";
  }
  std::cout << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 4. レンジアルゴリズム
// ============================================================================

void range_algorithms_examples() {
  std::cout << "=== レンジアルゴリズム ===" << std::endl;

  std::vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6};

  // ranges::sort（イテレータペア不要）
  std::ranges::sort(nums);
  std::cout << "ソート後: ";
  for (int n : nums) {
    std::cout << n << " ";
  }
  std::cout << std::endl;

  // ranges::find
  auto it = std::ranges::find(nums, 5);
  if (it != nums.end()) {
    std::cout << "5が見つかりました（位置: "
              << std::distance(nums.begin(), it) << "）" << std::endl;
  }

  // ranges::any_of
  bool has_even = std::ranges::any_of(nums, [](int n) { return n % 2 == 0; });
  std::cout << "偶数が含まれる: " << (has_even ? "はい" : "いいえ")
            << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 5. プロジェクション（メンバへのアクセス指定）
// ============================================================================

struct Player {
  std::string name;
  int score;
  int level;
};

void projection_examples() {
  std::cout << "=== プロジェクション ===" << std::endl;

  std::vector<Player> players = {
      {"Alice", 100, 5}, {"Bob", 85, 3}, {"Carol", 92, 4}, {"Dave", 78, 2}};

  // scoreでソート（プロジェクションを使用）
  std::ranges::sort(players, {}, &Player::score);

  std::cout << "スコア順（昇順）:" << std::endl;
  for (const auto& p : players) {
    std::cout << "  " << p.name << ": " << p.score << " (Lv" << p.level << ")"
              << std::endl;
  }

  // scoreで降順ソート
  std::ranges::sort(players, std::greater{}, &Player::score);

  std::cout << "\nスコア順（降順）:" << std::endl;
  for (const auto& p : players) {
    std::cout << "  " << p.name << ": " << p.score << " (Lv" << p.level << ")"
              << std::endl;
  }

  // スコアが最大のプレイヤーを検索
  auto max_player =
      std::ranges::max_element(players, {}, &Player::score);
  std::cout << "\n最高スコア: " << max_player->name << " ("
            << max_player->score << "点)" << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 6. 実践例: ゲームエンティティの処理
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

void game_entity_example() {
  std::cout << "=== ゲームエンティティの処理 ===" << std::endl;

  std::vector<Entity> entities = {
      {"Enemy1", true, 10.0f, 0.0f, 0.0f},
      {"Enemy2", false, 5.0f, 0.0f, 0.0f},
      {"Enemy3", true, 15.0f, 0.0f, 0.0f},
      {"Item1", true, 3.0f, 0.0f, 0.0f},
      {"Enemy4", true, 20.0f, 0.0f, 0.0f},
      {"Item2", false, 8.0f, 0.0f, 0.0f}};

  float player_x = 0.0f, player_y = 0.0f, player_z = 0.0f;

  // アクティブなエンティティのみをフィルタ
  auto active_entities =
      entities | std::views::filter([](const Entity& e) { return e.active; });

  std::cout << "アクティブなエンティティ:" << std::endl;
  for (const auto& e : active_entities) {
    std::cout << "  " << e.name << " at (" << e.x << ", " << e.y << ", " << e.z
              << ")" << std::endl;
  }

  // アクティブなエンティティをコピーして距離でソート
  std::vector<Entity> active_vec;
  std::ranges::copy(active_entities, std::back_inserter(active_vec));

  std::ranges::sort(active_vec, {}, [=](const Entity& e) {
    return e.distance_from(player_x, player_y, player_z);
  });

  std::cout << "\n最も近い3つのエンティティ:" << std::endl;
  for (const auto& e : active_vec | std::views::take(3)) {
    float dist = e.distance_from(player_x, player_y, player_z);
    std::cout << "  " << e.name << " (距離: " << dist << ")" << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// 7. UE 5.7風の例: TArray風の処理
// ============================================================================

// 簡易的なTArray風のエイリアス（実際のUEではもっと複雑）
template <typename T>
using TArray = std::vector<T>;

class AActor {
 public:
  std::string name;
  bool has_tag_enemy = false;
  float x = 0.0f;
  float y = 0.0f;
  float z = 0.0f;

  AActor(std::string n, bool enemy, float px, float py, float pz)
      : name(n), has_tag_enemy(enemy), x(px), y(py), z(pz) {}

  bool ActorHasTag(const std::string& tag) const {
    return (tag == "Enemy" && has_tag_enemy);
  }

  float GetDistanceTo(float px, float py, float pz) const {
    float dx = x - px;
    float dy = y - py;
    float dz = z - pz;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
  }
};

void unreal_style_example() {
  std::cout << "=== UE 5.7風の例 ===" << std::endl;

  TArray<AActor*> actors;
  actors.push_back(new AActor("Enemy1", true, 10.0f, 0.0f, 0.0f));
  actors.push_back(new AActor("Player", false, 0.0f, 0.0f, 0.0f));
  actors.push_back(new AActor("Enemy2", true, 5.0f, 0.0f, 0.0f));
  actors.push_back(new AActor("Item", false, 3.0f, 0.0f, 0.0f));

  float player_x = 0.0f, player_y = 0.0f, player_z = 0.0f;

  // Enemyタグを持つActorをフィルタして距離でソート
  std::vector<AActor*> enemies;
  std::ranges::copy(actors | std::views::filter([](AActor* a) {
                      return a->ActorHasTag("Enemy");
                    }),
                    std::back_inserter(enemies));

  std::ranges::sort(enemies, {}, [=](AActor* a) {
    return a->GetDistanceTo(player_x, player_y, player_z);
  });

  std::cout << "最も近い敵:" << std::endl;
  for (AActor* enemy : enemies | std::views::take(2)) {
    float dist = enemy->GetDistanceTo(player_x, player_y, player_z);
    std::cout << "  " << enemy->name << " (距離: " << dist << ")" << std::endl;
  }

  // メモリ解放
  for (auto* actor : actors) {
    delete actor;
  }

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "C++20 レンジ（Ranges）のサンプル\n" << std::endl;

  basic_pipeline_examples();
  views_examples();
  map_views_examples();
  range_algorithms_examples();
  projection_examples();
  game_entity_example();
  unreal_style_example();

  std::cout << "全てのサンプルが完了しました！" << std::endl;
  return 0;
}
