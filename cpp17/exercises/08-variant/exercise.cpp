// std::variantの演習
// TODOコメントを埋めて、プログラムを完成させてください。

#include <iostream>
#include <string>
#include <variant>
#include <vector>

// ============================================================================
// overloadedヘルパー（提供済み）
// ============================================================================

template <class... Ts>
struct overloaded : Ts... {
  using Ts::operator()...;
};
template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

// ============================================================================
// 演習 1.8.1: ゲームイベントシステム
// ============================================================================

// TODO: 以下の構造体を定義してください

// PlayerMoved: プレイヤーが移動した
// メンバ: float x, float y

// ItemPickedUp: アイテムを拾った
// メンバ: int item_id, std::string item_name

// DamageTaken: ダメージを受けた
// メンバ: int amount, std::string source

// TODO: GameEventをstd::variantで定義してください
// using GameEvent = std::variant<...>;

void exercise_1_8_1() {
  std::cout << "=== 演習 1.8.1: ゲームイベントシステム ===" << std::endl;

  // TODO: イベントのベクターを作成してください
  // 以下のイベントを含めてください:
  // - PlayerMoved{10.5f, 20.3f}
  // - ItemPickedUp{1, "Health Potion"}
  // - DamageTaken{15, "Goblin"}
  // - PlayerMoved{15.0f, 25.0f}
  // - ItemPickedUp{2, "Sword"}

  // TODO: std::visitとoverloadedパターンを使って、各イベントを処理してください
  // 出力形式:
  // - PlayerMoved: "Player moved to (X, Y)"
  // - ItemPickedUp: "Picked up ITEM_NAME (ID: ITEM_ID)"
  // - DamageTaken: "Took AMOUNT damage from SOURCE"

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習: パーサーの結果
// ============================================================================

// TODO: 以下の構造体を定義してください

// IntValue: 整数値
// メンバ: int value

// FloatValue: 浮動小数点値
// メンバ: double value

// StringValue: 文字列値
// メンバ: std::string value

// ParseError: パースエラー
// メンバ: std::string error_message

// TODO: ParseResultをstd::variantで定義してください
// using ParseResult = std::variant<...>;

// TODO: 文字列をパースする関数を実装してください
// - 整数に変換できる場合はIntValue
// - 浮動小数点に変換できる場合はFloatValue
// - 数値でない場合はStringValue
// - 空文字列の場合はParseError
// ヒント: std::stoi, std::stodを使い、例外をキャッチします
ParseResult parse_value(const std::string& str) {
  // TODO: ここに実装してください
  return ParseError{"Not implemented"};
}

void bonus_exercise() {
  std::cout << "=== ボーナス演習: パーサー ===" << std::endl;

  std::vector<std::string> inputs = {"42", "3.14", "hello", "", "123"};

  // TODO: 各入力をパースして、結果を出力してください
  // std::visitとoverloadedパターンを使用してください
  // 出力形式:
  // - IntValue: "Integer: VALUE"
  // - FloatValue: "Float: VALUE"
  // - StringValue: "String: VALUE"
  // - ParseError: "Error: ERROR_MESSAGE"

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "std::variantの演習\n" << std::endl;

  exercise_1_8_1();
  bonus_exercise();

  std::cout << "演習が完了しました！" << std::endl;
  std::cout << "solution.cppと比較して、答え合わせをしましょう。" << std::endl;
  return 0;
}
