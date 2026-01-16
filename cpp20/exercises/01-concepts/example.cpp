// コンセプト（Concepts）のサンプルコード
// このファイルは写経用です。コードを理解しながら写経してください。

#include <concepts>
#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

// ============================================================================
// 1. 基本的なrequires節
// ============================================================================

// 整数型のみを受け付ける関数（Rustのtrait boundsに相当）
template <typename T>
  requires std::integral<T>
T double_value(T x) {
  return x * 2;
}

// 省略構文（上と同じ意味）
template <std::integral T>
T triple_value(T x) {
  return x * 3;
}

// auto + コンセプト（最も簡潔）
std::integral auto quad_value(std::integral auto x) { return x * 4; }

void basic_requires_examples() {
  std::cout << "=== 基本的なrequires節 ===" << std::endl;

  int i = 10;
  std::cout << "double_value(10) = " << double_value(i) << std::endl;
  std::cout << "triple_value(10) = " << triple_value(i) << std::endl;
  std::cout << "quad_value(10) = " << quad_value(i) << std::endl;

  // 以下はコンパイルエラー（浮動小数点型は受け付けない）
  // double d = 3.14;
  // double_value(d);  // エラー！

  std::cout << std::endl;
}

// ============================================================================
// 2. 標準コンセプト
// ============================================================================

void standard_concepts_examples() {
  std::cout << "=== 標準コンセプト ===" << std::endl;

  // 型カテゴリのコンセプト
  static_assert(std::integral<int>);
  static_assert(std::integral<long>);
  static_assert(std::floating_point<float>);
  static_assert(std::floating_point<double>);

  std::cout << "型カテゴリのコンセプト:" << std::endl;
  std::cout << "  std::integral<int>: "
            << std::integral<int> << std::endl;
  std::cout << "  std::floating_point<double>: "
            << std::floating_point<double> << std::endl;

  // オブジェクトのコンセプト
  static_assert(std::movable<std::string>);
  static_assert(std::copyable<int>);

  std::cout << "\nオブジェクトのコンセプト:" << std::endl;
  std::cout << "  std::movable<std::string>: "
            << std::movable<std::string> << std::endl;
  std::cout << "  std::copyable<int>: " << std::copyable<int>
            << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 3. 自作コンセプト: Printable
// ============================================================================

// std::coutで出力可能な型を制約
template <typename T>
concept Printable = requires(T t) {
  { std::cout << t } -> std::same_as<std::ostream&>;
};

// Printableな型のみを受け付ける関数
void print(const Printable auto& value) {
  std::cout << "Value: " << value << std::endl;
}

void printable_concept_example() {
  std::cout << "=== Printableコンセプト ===" << std::endl;

  print(42);
  print(3.14);
  print("Hello, Concepts!");
  print(std::string("C++20"));

  std::cout << std::endl;
}

// ============================================================================
// 4. 自作コンセプト: Number（四則演算が可能）
// ============================================================================

template <typename T>
concept Number = requires(T a, T b) {
  { a + b } -> std::convertible_to<T>;
  { a - b } -> std::convertible_to<T>;
  { a * b } -> std::convertible_to<T>;
  { a / b } -> std::convertible_to<T>;
};

template <Number T>
T calculate_average(T a, T b) {
  return (a + b) / static_cast<T>(2);
}

void number_concept_example() {
  std::cout << "=== Numberコンセプト ===" << std::endl;

  std::cout << "average(10, 20) = " << calculate_average(10, 20) << std::endl;
  std::cout << "average(3.5, 7.5) = " << calculate_average(3.5, 7.5)
            << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 5. 自作コンセプト: Container（コンテナの制約）
// ============================================================================

template <typename T>
concept Container = requires(T c) {
  typename T::value_type;     // value_type型が存在
  typename T::iterator;       // iterator型が存在
  { c.begin() } -> std::input_iterator;  // begin()がイテレータを返す
  { c.end() } -> std::input_iterator;    // end()がイテレータを返す
  { c.size() } -> std::convertible_to<std::size_t>;  // size()が呼べる
};

// Containerコンセプトを満たす型のみを受け付ける
template <Container C>
void print_container(const C& container) {
  std::cout << "Container size: " << container.size() << ", elements: [";
  bool first = true;
  for (const auto& elem : container) {
    if (!first) std::cout << ", ";
    std::cout << elem;
    first = false;
  }
  std::cout << "]" << std::endl;
}

void container_concept_example() {
  std::cout << "=== Containerコンセプト ===" << std::endl;

  std::vector<int> vec = {1, 2, 3, 4, 5};
  print_container(vec);

  std::vector<std::string> strings = {"Hello", "C++20", "Concepts"};
  print_container(strings);

  std::cout << std::endl;
}

// ============================================================================
// 6. コンセプトの組み合わせ: GameEntity
// ============================================================================

// ゲームエンティティの要件を定義
template <typename T>
concept GameEntity = std::movable<T> && requires(T e, float dt) {
  { e.update(dt) } -> std::same_as<void>;
  { e.render() } -> std::same_as<void>;
  { e.get_position() } -> std::convertible_to<std::tuple<float, float, float>>;
};

// GameEntityコンセプトを満たす具体的なクラス
class Player {
  float x_ = 0.0f;
  float y_ = 0.0f;
  float z_ = 0.0f;

 public:
  void update(float delta_time) {
    x_ += 1.0f * delta_time;  // 移動シミュレーション
  }

  void render() const { std::cout << "  Rendering Player" << std::endl; }

  std::tuple<float, float, float> get_position() const {
    return {x_, y_, z_};
  }
};

// GameEntityを扱うジェネリック関数
template <GameEntity T>
void simulate_entity(T& entity, float delta_time) {
  entity.update(delta_time);
  entity.render();
  auto [x, y, z] = entity.get_position();
  std::cout << "  Position: (" << x << ", " << y << ", " << z << ")"
            << std::endl;
}

void game_entity_concept_example() {
  std::cout << "=== GameEntityコンセプト ===" << std::endl;

  Player player;
  std::cout << "Initial state:" << std::endl;
  simulate_entity(player, 0.0f);

  std::cout << "\nAfter update (dt=1.0):" << std::endl;
  simulate_entity(player, 1.0f);

  std::cout << std::endl;
}

// ============================================================================
// 7. UE 5.7風の例: Actor型の制約
// ============================================================================

// 仮想的なAActorベースクラス（UEのAActorに相当）
class AActor {
 public:
  virtual ~AActor() = default;
  std::string GetName() const { return "Actor"; }
};

class AEnemy : public AActor {
 public:
  std::string GetName() const { return "Enemy"; }
};

// AActorから派生した型のみを受け付けるコンセプト
template <typename T>
concept DerivedFromActor = std::is_base_of_v<AActor, T>;

// UE風のジェネリック関数
template <DerivedFromActor T>
void LogActorInfo(const T& actor) {
  std::cout << "Actor type: " << actor.GetName() << std::endl;
}

void unreal_style_concept_example() {
  std::cout << "=== UE 5.7風のコンセプト ===" << std::endl;

  AActor base_actor;
  AEnemy enemy;

  LogActorInfo(base_actor);
  LogActorInfo(enemy);

  // 以下はコンパイルエラー（AActorから派生していない）
  // int x = 10;
  // LogActorInfo(x);  // エラー！

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "C++20 コンセプト（Concepts）のサンプル\n" << std::endl;

  basic_requires_examples();
  standard_concepts_examples();
  printable_concept_example();
  number_concept_example();
  container_concept_example();
  game_entity_concept_example();
  unreal_style_concept_example();

  std::cout << "全てのサンプルが完了しました！" << std::endl;
  return 0;
}
