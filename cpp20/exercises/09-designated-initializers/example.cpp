// 指定初期化子（Designated Initializers）のサンプルコード
// このファイルは写経用です。コードを理解しながら写経してください。

#include <iostream>
#include <string>
#include <vector>

// ============================================================================
// 1. 基本的な指定初期化子
// ============================================================================

struct Point2D {
  int x;
  int y;
};

void basic_designated_initializers() {
  std::cout << "=== 基本的な指定初期化子 ===" << std::endl;

  // 従来の方法
  Point2D p1 = {10, 20};
  std::cout << "Traditional: (" << p1.x << ", " << p1.y << ")" << std::endl;

  // 指定初期化子（C++20）
  Point2D p2 = {.x = 30, .y = 40};
  std::cout << "Designated: (" << p2.x << ", " << p2.y << ")" << std::endl;

  // 一部のメンバのみ指定（残りは0初期化）
  Point2D p3 = {.x = 50};
  std::cout << "Partial: (" << p3.x << ", " << p3.y << ")" << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 2. デフォルト値との組み合わせ
// ============================================================================

struct Config {
  int width = 800;
  int height = 600;
  bool fullscreen = false;
  std::string title = "My Game";
};

void default_values_with_designated() {
  std::cout << "=== デフォルト値との組み合わせ ===" << std::endl;

  // デフォルト値を使用
  Config cfg1 = {};
  std::cout << "Default: " << cfg1.width << "x" << cfg1.height
            << ", Fullscreen: " << cfg1.fullscreen << std::endl;

  // 一部のみ上書き
  Config cfg2 = {.width = 1920, .height = 1080, .fullscreen = true};
  std::cout << "Custom: " << cfg2.width << "x" << cfg2.height
            << ", Fullscreen: " << cfg2.fullscreen << std::endl;
  std::cout << "Title: " << cfg2.title << " (デフォルト値のまま)" << std::endl;

  // 特定のフィールドだけ変更
  Config cfg3 = {.fullscreen = true};
  std::cout << "Fullscreen only: " << cfg3.width << "x" << cfg3.height
            << ", Fullscreen: " << cfg3.fullscreen << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 3. ゲームキャラクターのステータス
// ============================================================================

struct CharacterStats {
  std::string name;
  int level = 1;
  int health = 100;
  int mana = 50;
  int attack = 10;
  int defense = 5;
};

void game_character_stats() {
  std::cout << "=== ゲームキャラクターのステータス ===" << std::endl;

  // 戦士（高HP、高防御）
  CharacterStats warrior = {.name = "Warrior",
                            .level = 1,
                            .health = 150,
                            .mana = 30,
                            .attack = 15,
                            .defense = 10};

  // 魔法使い（高MP、高攻撃）
  CharacterStats wizard = {.name = "Wizard",
                           .level = 1,
                           .health = 80,
                           .mana = 120,
                           .attack = 25,
                           .defense = 3};

  // 盗賊（バランス型）
  CharacterStats rogue = {
      .name = "Rogue", .level = 1, .health = 100, .mana = 60, .attack = 18};

  auto print_stats = [](const CharacterStats& c) {
    std::cout << c.name << " (Lv." << c.level << "): HP=" << c.health
              << ", MP=" << c.mana << ", ATK=" << c.attack
              << ", DEF=" << c.defense << std::endl;
  };

  print_stats(warrior);
  print_stats(wizard);
  print_stats(rogue);

  std::cout << std::endl;
}

// ============================================================================
// 4. ネストした構造体
// ============================================================================

struct Position {
  float x = 0.0f;
  float y = 0.0f;
  float z = 0.0f;
};

struct Entity {
  std::string name;
  Position position;
  float speed = 1.0f;
};

void nested_structures() {
  std::cout << "=== ネストした構造体 ===" << std::endl;

  // ネストした構造体も指定初期化子で初期化可能
  Entity player = {.name = "Player",
                   .position = {.x = 10.0f, .y = 20.0f, .z = 5.0f},
                   .speed = 2.5f};

  std::cout << player.name << " at (" << player.position.x << ", "
            << player.position.y << ", " << player.position.z << ")"
            << std::endl;
  std::cout << "Speed: " << player.speed << std::endl;

  // 一部のみ指定
  Entity enemy = {
      .name = "Enemy",
      .position = {.x = 50.0f}  // y, z はデフォルト値（0.0f）
  };

  std::cout << enemy.name << " at (" << enemy.position.x << ", "
            << enemy.position.y << ", " << enemy.position.z << ")" << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 5. UEスタイルの構造体（疑似コード）
// ============================================================================

// 注: 実際のUEコードではないが、UEスタイルを模倣
struct FCharacterStats {
  float Health = 100.0f;
  float Stamina = 100.0f;
  float Mana = 50.0f;
  float AttackPower = 10.0f;
  float DefensePower = 5.0f;
};

void ue_style_initialization() {
  std::cout << "=== UEスタイルの構造体初期化 ===" << std::endl;

  // 戦士のステータス
  FCharacterStats WarriorStats = {
      .Health = 150.0f, .Stamina = 120.0f, .Mana = 30.0f, .DefensePower = 12.0f};

  // 魔法使いのステータス
  FCharacterStats WizardStats = {
      .Health = 80.0f, .Mana = 150.0f, .AttackPower = 25.0f};

  auto PrintStats = [](const char* Name, const FCharacterStats& Stats) {
    std::cout << Name << ":" << std::endl;
    std::cout << "  Health: " << Stats.Health << std::endl;
    std::cout << "  Stamina: " << Stats.Stamina << std::endl;
    std::cout << "  Mana: " << Stats.Mana << std::endl;
    std::cout << "  Attack: " << Stats.AttackPower << std::endl;
    std::cout << "  Defense: " << Stats.DefensePower << std::endl;
  };

  PrintStats("Warrior", WarriorStats);
  std::cout << std::endl;
  PrintStats("Wizard", WizardStats);

  std::cout << std::endl;
}

// ============================================================================
// 6. 配列での使用
// ============================================================================

struct Color {
  std::string name;
  int r = 0, g = 0, b = 0;
};

void array_initialization() {
  std::cout << "=== 配列での使用 ===" << std::endl;

  // 配列の要素を指定初期化子で初期化
  Color palette[] = {
      {.name = "Red", .r = 255},
      {.name = "Green", .g = 255},
      {.name = "Blue", .b = 255},
      {.name = "Yellow", .r = 255, .g = 255},
      {.name = "Magenta", .r = 255, .b = 255},
  };

  std::cout << "Color palette:" << std::endl;
  for (const auto& color : palette) {
    std::cout << color.name << ": RGB(" << color.r << ", " << color.g << ", "
              << color.b << ")" << std::endl;
  }

  std::cout << std::endl;
}

// ============================================================================
// 7. 実用例：ゲーム設定の管理
// ============================================================================

struct GraphicsSettings {
  int resolution_width = 1920;
  int resolution_height = 1080;
  bool vsync = true;
  int anti_aliasing = 4;  // 0=off, 2=MSAA2x, 4=MSAA4x, 8=MSAA8x
  int shadow_quality = 3;  // 0=off, 1=low, 2=medium, 3=high, 4=ultra
};

struct GameSettings {
  GraphicsSettings graphics;
  float master_volume = 1.0f;
  float music_volume = 0.8f;
  float sfx_volume = 0.9f;
  bool show_fps = false;
};

void game_settings_example() {
  std::cout << "=== ゲーム設定の管理 ===" << std::endl;

  // 低スペックPC用の設定
  GameSettings low_preset = {
      .graphics = {.resolution_width = 1280,
                   .resolution_height = 720,
                   .vsync = true,
                   .anti_aliasing = 0,
                   .shadow_quality = 1},
      .show_fps = true};

  // 高スペックPC用の設定
  GameSettings ultra_preset = {.graphics = {.resolution_width = 3840,
                                            .resolution_height = 2160,
                                            .anti_aliasing = 8,
                                            .shadow_quality = 4}};

  auto print_settings = [](const char* preset_name,
                           const GameSettings& settings) {
    std::cout << preset_name << ":" << std::endl;
    std::cout << "  Resolution: " << settings.graphics.resolution_width << "x"
              << settings.graphics.resolution_height << std::endl;
    std::cout << "  Anti-aliasing: " << settings.graphics.anti_aliasing << "x"
              << std::endl;
    std::cout << "  Shadow quality: " << settings.graphics.shadow_quality
              << std::endl;
    std::cout << "  Show FPS: " << (settings.show_fps ? "Yes" : "No")
              << std::endl;
  };

  print_settings("Low Preset", low_preset);
  std::cout << std::endl;
  print_settings("Ultra Preset", ultra_preset);

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "C++20 指定初期化子のサンプル\n" << std::endl;

  basic_designated_initializers();
  default_values_with_designated();
  game_character_stats();
  nested_structures();
  ue_style_initialization();
  array_initialization();
  game_settings_example();

  std::cout << "全てのサンプルが完了しました！" << std::endl;
  return 0;
}
