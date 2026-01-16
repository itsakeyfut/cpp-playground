// コンセプト（Concepts）の演習問題 - 解答例

#include <concepts>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <type_traits>

// ============================================================================
// 演習 2.1.1: Hashable コンセプト（解答）
// ============================================================================

template <typename T>
concept Hashable = requires(T t) {
  { std::hash<T>{}(t) } -> std::convertible_to<std::size_t>;
};

template <Hashable T>
std::size_t compute_hash(const T& value) {
  return std::hash<T>{}(value);
}

void test_hashable_concept() {
  std::cout << "=== 演習 2.1.1: Hashableコンセプト（解答） ===" << std::endl;

  int x = 42;
  std::string s = "Hello";

  std::cout << "hash(42) = " << compute_hash(x) << std::endl;
  std::cout << "hash(\"Hello\") = " << compute_hash(s) << std::endl;

  // 型チェック
  static_assert(Hashable<int>);
  static_assert(Hashable<std::string>);
  static_assert(Hashable<double>);

  std::cout << "✓ Hashableコンセプトが正しく動作しています。" << std::endl;
  std::cout << std::endl;
}

// ============================================================================
// 演習 2.1.2: Serializable コンセプト（解答）
// ============================================================================

template <typename T>
concept Serializable = requires(T t, const std::string& s) {
  { t.serialize() } -> std::same_as<std::string>;
  { t.deserialize(s) } -> std::same_as<void>;
};

struct SaveData {
  int level = 1;
  int score = 0;

  std::string serialize() const {
    std::ostringstream oss;
    oss << level << "," << score;
    return oss.str();
  }

  void deserialize(const std::string& data) {
    // 簡易的なパース実装
    std::istringstream iss(data);
    char comma;
    iss >> level >> comma >> score;
  }
};

template <Serializable T>
void save_to_string(const T& obj) {
  std::string data = obj.serialize();
  std::cout << "Serialized data: " << data << std::endl;
}

template <Serializable T>
T load_from_string(const std::string& data) {
  T obj;
  obj.deserialize(data);
  return obj;
}

void test_serializable_concept() {
  std::cout << "=== 演習 2.1.2: Serializableコンセプト（解答） ===" << std::endl;

  SaveData save_data{5, 1000};
  save_to_string(save_data);

  // シリアライズ → デシリアライズのテスト
  std::string serialized = save_data.serialize();
  SaveData loaded = load_from_string<SaveData>(serialized);

  std::cout << "Original: level=" << save_data.level
            << ", score=" << save_data.score << std::endl;
  std::cout << "Loaded: level=" << loaded.level << ", score=" << loaded.score
            << std::endl;

  // 型チェック
  static_assert(Serializable<SaveData>);

  std::cout << "✓ Serializableコンセプトが正しく動作しています。" << std::endl;
  std::cout << std::endl;
}

// ============================================================================
// 演習 2.1.3: GameEntity コンセプト（解答）
// ============================================================================

template <typename T>
concept GameEntity = std::movable<T> && requires(T e, float dt) {
  { e.update(dt) } -> std::same_as<void>;
  { e.render() } -> std::same_as<void>;
  { e.get_position() } -> std::convertible_to<std::tuple<float, float, float>>;
};

class Enemy {
  float x_ = 0.0f;
  float y_ = 0.0f;
  float z_ = 0.0f;
  float health_ = 100.0f;
  float velocity_x_ = 1.0f;

 public:
  void update(float delta_time) {
    // 移動シミュレーション
    x_ += velocity_x_ * delta_time;

    // 体力減少（デモ用）
    health_ -= 0.1f * delta_time;
  }

  void render() const {
    std::cout << "  Rendering Enemy (health: " << health_ << ")" << std::endl;
  }

  std::tuple<float, float, float> get_position() const { return {x_, y_, z_}; }
};

class Projectile {
  float x_ = 0.0f;
  float y_ = 0.0f;
  float z_ = 0.0f;
  float speed_ = 10.0f;

 public:
  void update(float delta_time) { x_ += speed_ * delta_time; }

  void render() const { std::cout << "  Rendering Projectile" << std::endl; }

  std::tuple<float, float, float> get_position() const { return {x_, y_, z_}; }
};

template <GameEntity T>
void simulate(T& entity, float delta_time) {
  entity.update(delta_time);
  entity.render();
  auto [x, y, z] = entity.get_position();
  std::cout << "  Position: (" << x << ", " << y << ", " << z << ")"
            << std::endl;
}

// 複数のGameEntityをまとめて処理
template <GameEntity... Entities>
void simulate_all(float delta_time, Entities&... entities) {
  (simulate(entities, delta_time), ...);  // fold expression
}

void test_game_entity_concept() {
  std::cout << "=== 演習 2.1.3: GameEntityコンセプト（解答） ===" << std::endl;

  Enemy enemy;
  Projectile projectile;

  std::cout << "フレーム1 (dt=0.016s):" << std::endl;
  simulate_all(0.016f, enemy, projectile);

  std::cout << "\nフレーム2 (dt=0.016s):" << std::endl;
  simulate_all(0.016f, enemy, projectile);

  // 型チェック
  static_assert(GameEntity<Enemy>);
  static_assert(GameEntity<Projectile>);

  std::cout << "\n✓ GameEntityコンセプトが正しく動作しています。" << std::endl;
  std::cout << std::endl;
}

// ============================================================================
// おまけ: UE 5.7風のコンセプト活用例
// ============================================================================

// UE風の基底クラス
class AActor {
 public:
  virtual ~AActor() = default;
  virtual std::string GetName() const { return "Actor"; }
};

// Actorから派生した型のコンセプト
template <typename T>
concept ActorDerived = std::is_base_of_v<AActor, T>;

// オブジェクトプール（コンセプトで型安全）
template <ActorDerived T>
class TActorPool {
  std::vector<T*> pool_;

 public:
  ~TActorPool() {
    for (auto* actor : pool_) {
      delete actor;
    }
  }

  T* Acquire() {
    if (!pool_.empty()) {
      T* actor = pool_.back();
      pool_.pop_back();
      return actor;
    }
    return new T();
  }

  void Release(T* actor) { pool_.push_back(actor); }

  std::size_t GetPoolSize() const { return pool_.size(); }
};

class AEnemy : public AActor {
 public:
  std::string GetName() const override { return "Enemy"; }
};

void test_unreal_style_example() {
  std::cout << "=== おまけ: UE 5.7風のコンセプト活用例 ===" << std::endl;

  TActorPool<AEnemy> enemy_pool;

  // プールから取得
  AEnemy* enemy1 = enemy_pool.Acquire();
  AEnemy* enemy2 = enemy_pool.Acquire();

  std::cout << "Acquired: " << enemy1->GetName() << std::endl;
  std::cout << "Acquired: " << enemy2->GetName() << std::endl;

  // プールに返却
  enemy_pool.Release(enemy1);
  enemy_pool.Release(enemy2);

  std::cout << "Pool size after release: " << enemy_pool.GetPoolSize()
            << std::endl;

  std::cout << "✓ UE風のコンセプトが正しく動作しています。" << std::endl;
  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "C++20 コンセプト（Concepts）の演習問題 - 解答例\n"
            << std::endl;

  test_hashable_concept();
  test_serializable_concept();
  test_game_entity_concept();
  test_unreal_style_example();

  std::cout << "全ての演習が完了しました！" << std::endl;
  std::cout << "\nコンセプトの利点:" << std::endl;
  std::cout << "  ✓ コンパイル時の型チェック" << std::endl;
  std::cout << "  ✓ わかりやすいエラーメッセージ" << std::endl;
  std::cout << "  ✓ ドキュメントとしての役割" << std::endl;
  std::cout << "  ✓ テンプレートの制約を明示的に" << std::endl;

  return 0;
}
