// 指定初期化子（Designated Initializers）の演習
// TODOコメントを埋めて、プログラムを完成させてください。

#include <iostream>
#include <string>
#include <vector>

// ============================================================================
// 演習 2.5.5.1: 基本的な指定初期化子
// ============================================================================

struct Rectangle {
  int width;
  int height;
};

void exercise_2_5_5_1() {
  std::cout << "=== 演習 2.5.5.1: 基本的な指定初期化子 ===" << std::endl;

  // TODO: 指定初期化子を使ってRectangleを初期化してください
  // 幅: 100, 高さ: 50
  // Rectangle rect = { ... };

  // TODO: 面積を計算して出力してください
  // int area = rect.width * rect.height;
  // std::cout << "Rectangle: " << rect.width << "x" << rect.height
  //           << ", Area: " << area << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 演習 2.5.5.2: ゲームキャラクターのステータス
// ============================================================================

struct CharacterStats {
  std::string name;
  int level = 1;
  int health = 100;
  int mana = 50;
  int attack = 10;
  int defense = 5;
};

void exercise_2_5_5_2() {
  std::cout << "=== 演習 2.5.5.2: ゲームキャラクターのステータス ==="
            << std::endl;

  // TODO: 3種類のキャラクターを作成してください
  // 1. 戦士（Warrior）: HP=150, MP=30, ATK=15, DEF=10
  // 2. 魔法使い（Wizard）: HP=80, MP=120, ATK=25, DEF=3
  // 3. 盗賊（Rogue）: HP=100, MP=60, ATK=18, DEF=7

  // CharacterStats warrior = { ... };
  // CharacterStats wizard = { ... };
  // CharacterStats rogue = { ... };

  // TODO: 3つのキャラクターをvectorに格納してください
  // std::vector<CharacterStats> party = { ... };

  // TODO: 全キャラクターの情報を出力してください
  // for (const auto& character : party) {
  //   std::cout << character.name << " (Lv." << character.level << "): "
  //             << "HP=" << character.health << ", MP=" << character.mana
  //             << ", ATK=" << character.attack << ", DEF=" << character.defense
  //             << std::endl;
  // }

  std::cout << std::endl;
}

// ============================================================================
// 演習 2.5.5.3: UEスタイルのFCharacterStats
// ============================================================================

// TODO: FCharacterStats構造体を定義してください
// メンバ変数（すべてfloat型、デフォルト値付き）:
// - Health = 100.0f
// - Stamina = 100.0f
// - Mana = 50.0f
// - AttackPower = 10.0f
// - DefensePower = 5.0f

// struct FCharacterStats {
//   // TODO: メンバ変数を定義
// };

void exercise_2_5_5_3() {
  std::cout << "=== 演習 2.5.5.3: UEスタイルのFCharacterStats ==="
            << std::endl;

  // TODO: 戦士のステータスを作成（指定初期化子を使用）
  // Health=150, Stamina=120, Mana=30, DefensePower=12
  // FCharacterStats WarriorStats = { ... };

  // TODO: 魔法使いのステータスを作成
  // Health=80, Mana=150, AttackPower=25
  // FCharacterStats WizardStats = { ... };

  // TODO: 盗賊のステータスを作成
  // Health=110, Stamina=140, AttackPower=18
  // FCharacterStats RogueStats = { ... };

  // TODO: 各キャラクターのステータスを出力してください
  // 形式: "Warrior: HP=150, Stamina=120, ..."

  std::cout << std::endl;
}

// ============================================================================
// ボーナス演習: ゲーム設定の管理
// ============================================================================

struct GraphicsSettings {
  int resolution_width = 1920;
  int resolution_height = 1080;
  bool vsync = true;
  int anti_aliasing = 4;
  int shadow_quality = 3;
};

struct AudioSettings {
  float master_volume = 1.0f;
  float music_volume = 0.8f;
  float sfx_volume = 0.9f;
};

struct GameSettings {
  GraphicsSettings graphics;
  AudioSettings audio;
  bool show_fps = false;
  int difficulty = 2;  // 0=easy, 1=normal, 2=hard, 3=very hard
};

void bonus_exercise() {
  std::cout << "=== ボーナス演習: ゲーム設定プリセット ===" << std::endl;

  // TODO: 3つの設定プリセットを作成してください
  // 1. 低スペック用（Low）:
  //    - 解像度: 1280x720
  //    - アンチエイリアス: 0
  //    - 影品質: 1
  //    - FPS表示: true
  //
  // 2. バランス用（Medium）:
  //    - 解像度: 1920x1080
  //    - アンチエイリアス: 2
  //    - 影品質: 2
  //
  // 3. 高スペック用（Ultra）:
  //    - 解像度: 3840x2160
  //    - アンチエイリアス: 8
  //    - 影品質: 4
  //    - 難易度: 3

  // GameSettings low_preset = { ... };
  // GameSettings medium_preset = { ... };
  // GameSettings ultra_preset = { ... };

  // TODO: 各プリセットの情報を出力してください
  // 形式: "Low Preset: 1280x720, AA:0x, Shadow:1, ..."

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "指定初期化子の演習\n" << std::endl;

  exercise_2_5_5_1();
  exercise_2_5_5_2();
  exercise_2_5_5_3();
  bonus_exercise();

  std::cout << "演習が完了しました！" << std::endl;
  std::cout << "solution.cppと比較して、答え合わせをしましょう。" << std::endl;
  return 0;
}
