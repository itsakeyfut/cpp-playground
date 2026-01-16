// 指定初期化子（Designated Initializers）の演習 - 解答例

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

  Rectangle rect = {.width = 100, .height = 50};

  int area = rect.width * rect.height;
  std::cout << "Rectangle: " << rect.width << "x" << rect.height
            << ", Area: " << area << std::endl;

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

  CharacterStats warrior = {.name = "Warrior",
                            .level = 1,
                            .health = 150,
                            .mana = 30,
                            .attack = 15,
                            .defense = 10};

  CharacterStats wizard = {.name = "Wizard",
                           .level = 1,
                           .health = 80,
                           .mana = 120,
                           .attack = 25,
                           .defense = 3};

  CharacterStats rogue = {.name = "Rogue",
                          .level = 1,
                          .health = 100,
                          .mana = 60,
                          .attack = 18,
                          .defense = 7};

  std::vector<CharacterStats> party = {warrior, wizard, rogue};

  std::cout << "パーティー編成:" << std::endl;
  for (const auto& character : party) {
    std::cout << character.name << " (Lv." << character.level << "): "
              << "HP=" << character.health << ", MP=" << character.mana
              << ", ATK=" << character.attack << ", DEF=" << character.defense
              << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// 演習 2.5.5.3: UEスタイルのFCharacterStats
// ============================================================================

struct FCharacterStats {
  float Health = 100.0f;
  float Stamina = 100.0f;
  float Mana = 50.0f;
  float AttackPower = 10.0f;
  float DefensePower = 5.0f;
};

void exercise_2_5_5_3() {
  std::cout << "=== 演習 2.5.5.3: UEスタイルのFCharacterStats ==="
            << std::endl;

  FCharacterStats WarriorStats = {
      .Health = 150.0f, .Stamina = 120.0f, .Mana = 30.0f, .DefensePower = 12.0f};

  FCharacterStats WizardStats = {
      .Health = 80.0f, .Mana = 150.0f, .AttackPower = 25.0f};

  FCharacterStats RogueStats = {
      .Health = 110.0f, .Stamina = 140.0f, .AttackPower = 18.0f};

  auto PrintStats = [](const char* ClassName, const FCharacterStats& Stats) {
    std::cout << ClassName << ": HP=" << Stats.Health
              << ", Stamina=" << Stats.Stamina << ", Mana=" << Stats.Mana
              << ", ATK=" << Stats.AttackPower
              << ", DEF=" << Stats.DefensePower << std::endl;
  };

  PrintStats("Warrior", WarriorStats);
  PrintStats("Wizard", WizardStats);
  PrintStats("Rogue", RogueStats);

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

  GameSettings low_preset = {
      .graphics = {.resolution_width = 1280,
                   .resolution_height = 720,
                   .anti_aliasing = 0,
                   .shadow_quality = 1},
      .show_fps = true};

  GameSettings medium_preset = {.graphics = {.anti_aliasing = 2,
                                             .shadow_quality = 2}};

  GameSettings ultra_preset = {
      .graphics = {.resolution_width = 3840,
                   .resolution_height = 2160,
                   .anti_aliasing = 8,
                   .shadow_quality = 4},
      .difficulty = 3};

  auto print_preset = [](const char* preset_name,
                         const GameSettings& settings) {
    std::cout << preset_name << ":" << std::endl;
    std::cout << "  Resolution: " << settings.graphics.resolution_width << "x"
              << settings.graphics.resolution_height << std::endl;
    std::cout << "  Anti-aliasing: " << settings.graphics.anti_aliasing << "x"
              << std::endl;
    std::cout << "  Shadow quality: " << settings.graphics.shadow_quality
              << std::endl;
    std::cout << "  VSync: " << (settings.graphics.vsync ? "On" : "Off")
              << std::endl;
    std::cout << "  Show FPS: " << (settings.show_fps ? "Yes" : "No")
              << std::endl;
    std::cout << "  Difficulty: " << settings.difficulty << std::endl;
    std::cout << "  Master volume: " << settings.audio.master_volume
              << std::endl;
  };

  print_preset("Low Preset", low_preset);
  std::cout << std::endl;
  print_preset("Medium Preset", medium_preset);
  std::cout << std::endl;
  print_preset("Ultra Preset", ultra_preset);

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "指定初期化子の演習 - 解答例\n" << std::endl;

  exercise_2_5_5_1();
  exercise_2_5_5_2();
  exercise_2_5_5_3();
  bonus_exercise();

  std::cout << "お疲れ様でした！" << std::endl;
  std::cout << "\nUnreal Engine 5.7での活用:" << std::endl;
  std::cout << "指定初期化子はUE 5.7で推奨される構造体初期化方法です。"
            << std::endl;
  std::cout << "USTRUCTを使った実際のプロジェクトでぜひ活用してください！"
            << std::endl;
  return 0;
}
