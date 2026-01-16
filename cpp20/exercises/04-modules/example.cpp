// モジュール（Modules）のサンプルコード
// 注意: これはモジュールの「概念」を示すヘッダーベースの実装です。
//       実際のモジュール構文はコンパイラサポートが必要です。

#include <iostream>
#include <string>
#include <vector>

// ============================================================================
// モジュールの概念説明
// ============================================================================

/*
実際のC++20モジュール構文（コンパイラサポートが必要）:

// math.ixx (モジュールインターフェースユニット)
export module math;

export int add(int a, int b) {
    return a + b;
}

export int multiply(int a, int b) {
    return a * b;
}

// 非公開（exportなし）
int internal_helper() {
    return 42;
}

---

// main.cpp
import math;  // #includeの代わりにimport

int main() {
    int result = add(1, 2);  // OK
    // internal_helper();    // エラー: 非公開
}
*/

// ============================================================================
// 1. モジュールの基本概念（ヘッダーベースの模擬実装）
// ============================================================================

// 従来の方法（#include）
namespace math_traditional {
int add(int a, int b) { return a + b; }
int multiply(int a, int b) { return a * b; }
int internal_helper() { return 42; }  // 外部から見えてしまう
}  // namespace math_traditional

void traditional_example() {
  std::cout << "=== 従来の方法（namespace） ===" << std::endl;

  int sum = math_traditional::add(1, 2);
  int product = math_traditional::multiply(3, 4);

  std::cout << "1 + 2 = " << sum << std::endl;
  std::cout << "3 * 4 = " << product << std::endl;

  // 問題: internal_helper()も見えてしまう
  int helper_result = math_traditional::internal_helper();
  std::cout << "internal_helper()も呼べてしまう: " << helper_result
            << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 2. モジュール風の実装（名前空間 + 内部リンケージ）
// ============================================================================

namespace math_module {
// 公開インターフェース
int add(int a, int b) { return a + b; }
int multiply(int a, int b) { return a * b; }

// 非公開実装（匿名名前空間）
namespace {
int internal_helper() { return 42; }
}  // namespace
}  // namespace math_module

void module_style_example() {
  std::cout << "=== モジュール風の実装 ===" << std::endl;

  int sum = math_module::add(5, 7);
  int product = math_module::multiply(3, 8);

  std::cout << "5 + 7 = " << sum << std::endl;
  std::cout << "3 * 8 = " << product << std::endl;

  // math_module::internal_helper(); // エラー: 見えない

  std::cout << "非公開の関数は外部から呼べません" << std::endl;
  std::cout << std::endl;
}

// ============================================================================
// 3. モジュールの利点
// ============================================================================

void module_benefits() {
  std::cout << "=== モジュールの利点 ===" << std::endl;

  std::cout << "1. コンパイル時間の短縮" << std::endl;
  std::cout << "   - ヘッダーは毎回パース、モジュールは1回だけ" << std::endl;
  std::cout << "   - 大規模プロジェクトで効果大" << std::endl;

  std::cout << "\n2. マクロ汚染の防止" << std::endl;
  std::cout << "   - モジュールはマクロをエクスポートしない" << std::endl;
  std::cout << "   - #defineによる名前衝突が起きない" << std::endl;

  std::cout << "\n3. 依存関係の明確化" << std::endl;
  std::cout << "   - importで明示的に依存を宣言" << std::endl;
  std::cout << "   - 循環依存の問題が減る" << std::endl;

  std::cout << "\n4. カプセル化の向上" << std::endl;
  std::cout << "   - exportしたものだけが公開される" << std::endl;
  std::cout << "   - 実装の詳細を完全に隠蔽できる" << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 4. モジュール構文の例（疑似コード）
// ============================================================================

void module_syntax_example() {
  std::cout << "=== モジュール構文の例 ===" << std::endl;

  std::cout << "基本構文（実際のコードではありません）:" << std::endl;
  std::cout << R"(
// geometry.ixx
export module geometry;

export struct Point {
    double x, y;
};

export double distance(Point a, Point b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

// 非公開
namespace {
    double square(double x) { return x * x; }
}

---

// main.cpp
import geometry;

int main() {
    Point p1{0, 0};
    Point p2{3, 4};
    double dist = distance(p1, p2);  // OK
    // square(5);  // エラー: 非公開
}
)" << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 5. UE 5.7との互換性に関する注意
// ============================================================================

void unreal_compatibility_notes() {
  std::cout << "=== UE 5.7との互換性 ===" << std::endl;

  std::cout << "現状の問題点:" << std::endl;
  std::cout << "  ✗ UnrealBuildToolがモジュールを完全サポートしていない"
            << std::endl;
  std::cout << "  ✗ UEの既存コードベースは #include ベース" << std::endl;
  std::cout << "  ✗ リフレクションシステム（UCLASS等）との統合が不明"
            << std::endl;

  std::cout << "\n推奨事項:" << std::endl;
  std::cout << "  ✓ 概念として理解する（将来の準備）" << std::endl;
  std::cout << "  ✓ 実際のUEプロジェクトでは従来の方法を使用" << std::endl;
  std::cout << "  ✓ C++23/26で成熟してから本格採用を検討" << std::endl;

  std::cout << "\n代替手段（現在のUE開発）:" << std::endl;
  std::cout << "  • Unreal Modularity System (UE独自のモジュール)"
            << std::endl;
  std::cout << "  • 適切な名前空間とヘッダー分割" << std::endl;
  std::cout << "  • IWYU (Include What You Use) の活用" << std::endl;

  std::cout << std::endl;
}

// ============================================================================
// 6. 実践的なモジュール設計パターン（概念）
// ============================================================================

// パターン1: 型定義とユーティリティ関数
namespace game_types {
struct Vector3 {
  float x, y, z;
};

struct Transform {
  Vector3 position;
  Vector3 rotation;
  Vector3 scale;
};

// 公開ユーティリティ
float dot(const Vector3& a, const Vector3& b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

// 非公開実装
namespace {
float length_squared(const Vector3& v) {
  return dot(v, v);
}
}  // namespace
}  // namespace game_types

// パターン2: インターフェースと実装の分離
namespace renderer {
// 公開インターフェース
class IRenderer {
 public:
  virtual ~IRenderer() = default;
  virtual void render() = 0;
};

// 非公開実装
namespace {
class OpenGLRenderer : public IRenderer {
 public:
  void render() override {
    std::cout << "    OpenGL rendering..." << std::endl;
  }
};
}  // namespace

// ファクトリー関数（公開）
IRenderer* create_renderer() { return new OpenGLRenderer(); }
}  // namespace renderer

void design_patterns_example() {
  std::cout << "=== モジュール設計パターン ===" << std::endl;

  std::cout << "パターン1: 型とユーティリティ" << std::endl;
  game_types::Vector3 v1{1.0f, 2.0f, 3.0f};
  game_types::Vector3 v2{4.0f, 5.0f, 6.0f};
  float result = game_types::dot(v1, v2);
  std::cout << "  dot product = " << result << std::endl;

  std::cout << "\nパターン2: インターフェース分離" << std::endl;
  renderer::IRenderer* r = renderer::create_renderer();
  r->render();
  delete r;

  std::cout << std::endl;
}

// ============================================================================
// メイン関数
// ============================================================================

int main() {
  std::cout << "C++20 モジュール（Modules）のサンプル\n" << std::endl;
  std::cout << "注意: これは概念理解のためのヘッダーベース実装です"
            << std::endl;
  std::cout << "実際のモジュール構文を使うにはコンパイラの追加設定が必要です\n"
            << std::endl;

  traditional_example();
  module_style_example();
  module_benefits();
  module_syntax_example();
  unreal_compatibility_notes();
  design_patterns_example();

  std::cout << "全てのサンプルが完了しました！" << std::endl;
  std::cout << "\n重要: モジュールは将来の技術です" << std::endl;
  std::cout << "現時点では概念を理解し、実際の使用は将来に備えましょう"
            << std::endl;
  return 0;
}
