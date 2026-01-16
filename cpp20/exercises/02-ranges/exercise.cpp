// レンジ（Ranges）の演習問題
// TODOを埋めて、プログラムを完成させてください。

#include <algorithm>
#include <cctype>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

// ============================================================================
// 演習 2.2.1: 文字列のフィルタリングと変換
// ============================================================================
// 文字列のリストから、5文字以上のものだけをフィルタリングし、
// 大文字に変換して出力せよ。
//
// ヒント:
// - std::views::filter で5文字以上をフィルタ
// - std::views::transform で大文字に変換
// - std::toupper() を使って文字を大文字化

void test_string_filtering() {
  std::cout << "=== 演習 2.2.1: 文字列のフィルタリングと変換 ===" << std::endl;

  std::vector<std::string> words = {"cat",  "dog",     "elephant", "mouse",
                                    "lion", "giraffe", "ant",      "zebra"};

  std::cout << "元の文字列: ";
  for (const auto& word : words) {
    std::cout << word << " ";
  }
  std::cout << std::endl;

  // TODO: 5文字以上の文字列をフィルタして大文字に変換
  // ヒント: パイプライン構文を使用
  // auto filtered = words | std::views::filter(...) |
  // std::views::transform(...);

  std::cout << "5文字以上を大文字化: ";
  // TODO: filteredをイテレートして出力
  // for (const auto& word : filtered) {
  //     std::cout << word << " ";
  // }
  std::cout << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 演習 2.2.2: ゲームエンティティの処理
// ============================================================================
// ゲームのエンティティリストから、アクティブなもののみをフィルタリングし、
// 距離でソートして最も近い3つを取得せよ。

// TODO: Entity構造体を定義してください
struct Entity {
  std::string name;
  bool active;
  float x, y, z;

  // TODO: 指定座標からの距離を計算するメソッドを実装
  float distance_from(float px, float py, float pz) const {
    // ヒント: √((x-px)² + (y-py)² + (z-pz)²)
    return 0.0f;  // この行を修正してください
  }
};

void test_entity_filtering() {
  std::cout << "=== 演習 2.2.2: ゲームエンティティの処理 ===" << std::endl;

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

  // TODO: アクティブなエンティティのみをフィルタ
  // ヒント: std::views::filter を使用
  // auto active_entities = entities | std::views::filter(...);

  // TODO: アクティブなエンティティをvectorにコピー
  // std::vector<Entity> active_vec;
  // std::ranges::copy(active_entities, std::back_inserter(active_vec));

  // TODO: 距離でソート（プレイヤー位置からの距離）
  // ヒント: std::ranges::sort とプロジェクション（ラムダ式）を使用
  // std::ranges::sort(active_vec, {}, [=](const Entity& e) { ... });

  // TODO: 最も近い3つを出力
  // for (const auto& e : active_vec | std::views::take(3)) {
  //     float dist = e.distance_from(player_x, player_y, player_z);
  //     std::cout << "  " << e.name << " (距離: " << dist << ")" <<
  //     std::endl;
  // }

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "C++20 レンジ（Ranges）の演習問題\n" << std::endl;

  test_string_filtering();
  test_entity_filtering();

  std::cout << "演習が完了しました！" << std::endl;
  std::cout
      << "全てのTODOを実装し、コンパイルエラーがなくなったら成功です。"
      << std::endl;
  return 0;
}
