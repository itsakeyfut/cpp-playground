// コンセプト（Concepts）の演習問題
// TODOを埋めて、プログラムを完成させてください。

#include <concepts>
#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>

// ============================================================================
// 演習 2.1.1: Hashable コンセプト
// ============================================================================
// std::hash<T>が使用可能な型を制約するHashableコンセプトを作成せよ。
//
// ヒント:
// - requires式で std::hash<T> が使用可能かチェックする
// - std::hash<T>{}(t) が呼び出せることを確認する

// TODO: Hashableコンセプトを実装してください
template <typename T>
concept Hashable = false;  // この行を修正してください

// Hashableな型のみを受け付ける関数
template <Hashable T>
std::size_t compute_hash(const T& value) {
  return std::hash<T>{}(value);
}

void test_hashable_concept() {
  std::cout << "=== 演習 2.1.1: Hashableコンセプト ===" << std::endl;

  // TODO: 以下のコメントを外して動作確認してください
  // int x = 42;
  // std::string s = "Hello";
  // std::cout << "hash(42) = " << compute_hash(x) << std::endl;
  // std::cout << "hash(\"Hello\") = " << compute_hash(s) << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 演習 2.1.2: Serializable コンセプト
// ============================================================================
// serialize()とdeserialize()メソッドを持つ型を制約するSerializable
// コンセプトを作成せよ。
//
// 要件:
// - serialize()メソッドが std::string を返すこと
// - deserialize(const std::string&)メソッドが void を返すこと

// TODO: Serializableコンセプトを実装してください
template <typename T>
concept Serializable = false;  // この行を修正してください

// Serializableな型のサンプル実装（動作確認用）
struct SaveData {
  int level = 1;
  int score = 0;

  // TODO: serialize()メソッドを実装してください
  std::string serialize() const {
    // ヒント: std::to_string()を使ってlevelとscoreを文字列化
    return "";  // この行を修正してください
  }

  // TODO: deserialize()メソッドを実装してください
  void deserialize(const std::string& data) {
    // ヒント: 簡易的な実装でOK（例: "level,score"形式）
    // 実際のパースは省略して、固定値を設定しても良い
  }
};

// Serializableな型のみを受け付ける関数
template <Serializable T>
void save_to_string(const T& obj) {
  std::string data = obj.serialize();
  std::cout << "Serialized data: " << data << std::endl;
}

void test_serializable_concept() {
  std::cout << "=== 演習 2.1.2: Serializableコンセプト ===" << std::endl;

  // TODO: 以下のコメントを外して動作確認してください
  // SaveData save_data{5, 1000};
  // save_to_string(save_data);

  std::cout << std::endl;
}

// ============================================================================
// 演習 2.1.3: GameEntity コンセプト
// ============================================================================
// ゲーム開発用のGameEntityコンセプトを設計せよ。
//
// 要件:
// - update(float delta_time)メソッドを持つ（戻り値はvoid）
// - render()メソッドを持つ（戻り値はvoid）
// - get_position()メソッドでstd::tuple<float, float, float>を返す
// - ムーブ可能である（std::movable）

// TODO: GameEntityコンセプトを実装してください
template <typename T>
concept GameEntity = false;  // この行を修正してください

// GameEntityの具体的な実装例
class Enemy {
  float x_ = 0.0f;
  float y_ = 0.0f;
  float z_ = 0.0f;
  float health_ = 100.0f;

 public:
  // TODO: update()メソッドを実装してください
  void update(float delta_time) {
    // ヒント: 簡単な移動や状態更新を実装
  }

  // TODO: render()メソッドを実装してください
  void render() const {
    // ヒント: std::coutで出力するだけでOK
  }

  // TODO: get_position()メソッドを実装してください
  std::tuple<float, float, float> get_position() const {
    return {0.0f, 0.0f, 0.0f};  // この行を修正してください
  }
};

// GameEntityを扱うジェネリック関数
template <GameEntity T>
void simulate(T& entity, float delta_time) {
  entity.update(delta_time);
  entity.render();
  auto [x, y, z] = entity.get_position();
  std::cout << "Entity position: (" << x << ", " << y << ", " << z << ")"
            << std::endl;
}

void test_game_entity_concept() {
  std::cout << "=== 演習 2.1.3: GameEntityコンセプト ===" << std::endl;

  // TODO: 以下のコメントを外して動作確認してください
  // Enemy enemy;
  // simulate(enemy, 0.016f);  // 約60FPSの1フレーム分

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "C++20 コンセプト（Concepts）の演習問題\n" << std::endl;

  test_hashable_concept();
  test_serializable_concept();
  test_game_entity_concept();

  std::cout << "演習が完了しました！" << std::endl;
  std::cout
      << "全てのTODOを実装し、コンパイルエラーがなくなったら成功です。"
      << std::endl;
  return 0;
}
