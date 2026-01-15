# cpp-playground ディレクトリ構成

## 概要

このドキュメントは、cpp-playground リポジトリのディレクトリ構成と設計方針を定義します。

**リポジトリの目的**:

- Unreal Engine 5.7 でのゲーム開発に向けたモダン C++（C++17〜C++26）の習得
- 各 C++標準の新機能を実際にコードを書いて理解する
- 学習の記録を残し、後から参照できるようにする

**設計原則**:

- 学習の進行に合わせた明確な構造
- C++20 をデフォルトとし、UE 5.7 互換性を重視
- 各バージョン別の演習を独立して管理
- 横断的なトピックを別ディレクトリで管理
- ビルドシステムとの統合
- 将来の拡張性を考慮

---

## ルートディレクトリ構成

```
cpp-playground/
├── .clang-format              # コードフォーマット設定（Google Style）
├── .clang-tidy                # 静的解析設定
├── .gitignore                 # Git除外設定
├── CMakeLists.txt             # ルートビルド設定
├── README.md                  # プロジェクト概要
│
├── docs/                      # ドキュメント
│   ├── architecture.md        # このファイル
│   ├── modern-cpp-curriculum.md  # 学習カリキュラム
│   ├── unreal-engine-cpp20-guide.md  # UE 5.7 向けガイド
│   ├── clang-format.md        # フォーマッタ説明
│   ├── clang-tidy.md          # 静的解析説明
│   └── cpp-compiler-support.md  # コンパイラサポート状況
│
├── cpp17/                     # C++17 演習・プロジェクト
├── cpp20/                     # C++20 演習・プロジェクト（メイン）
├── cpp23/                     # C++23 演習・プロジェクト
├── cpp26/                     # C++26 実験的機能
│
├── cross_cutting/             # 横断的トピック
├── libs/                      # 共通ユーティリティライブラリ
├── sandbox/                   # 一時的な実験・プロトタイプ
│
└── build/                     # ビルド成果物（.gitignore）
```

---

## 各ディレクトリの詳細

### 1. `docs/` - ドキュメント

学習に関するすべてのドキュメントを集約。

```
docs/
├── architecture.md               # ディレクトリ構成（このファイル）
├── modern-cpp-curriculum.md      # C++17-26 の学習カリキュラム
├── unreal-engine-cpp20-guide.md  # UE 5.7 向けの C++20 学習ガイド
├── clang-format.md               # コードフォーマッタの説明
├── clang-tidy.md                 # 静的解析ツールの説明
├── cpp-compiler-support.md       # コンパイラサポート状況
│
├── progress/                     # 学習進捗記録
│   ├── PROGRESS.md               # 全体の進捗状況
│   ├── phase1-cpp17.md           # Phase 1 進捗
│   ├── phase2-cpp20.md           # Phase 2 進捗
│   ├── phase3-cpp23.md           # Phase 3 進捗
│   └── phase4-cpp26.md           # Phase 4 進捗
│
├── references/                   # 参考資料・リンク集
│   ├── books.md                  # 推奨書籍リスト
│   ├── websites.md               # 有用なウェブサイト
│   └── papers.md                 # C++標準化提案文書
│
└── design/                       # 設計ドキュメント
    ├── coding-guidelines.md      # コーディング規約
    ├── build-system.md           # ビルドシステム設計
    └── testing-strategy.md       # テスト戦略
```

**用途**:

- 学習の記録と参照
- 進捗管理
- 設計方針の文書化

---

### 2. `cpp17/` - C++17 演習

C++17 の機能を学習するための演習とプロジェクト。

```
cpp17/
├── CMakeLists.txt                # C++17 用ビルド設定
│
├── exercises/                    # 個別の演習課題
│   ├── 01-structured-bindings/   # 構造化束縛
│   │   ├── CMakeLists.txt
│   │   ├── main.cpp
│   │   └── README.md
│   ├── 02-if-init/               # if/switch 初期化式
│   ├── 03-ctad/                  # クラステンプレート引数推論
│   ├── 04-constexpr-if/          # constexpr if
│   ├── 05-fold-expressions/      # fold expressions
│   ├── 06-optional/              # std::optional
│   ├── 07-variant/               # std::variant
│   ├── 08-string-view/           # std::string_view
│   ├── 09-filesystem/            # std::filesystem
│   └── 10-parallel-algorithms/   # 並列アルゴリズム
│
├── projects/                     # 統合プロジェクト
│   ├── asset-manager/            # Phase 1 総合課題
│   │   ├── CMakeLists.txt
│   │   ├── src/
│   │   ├── include/
│   │   ├── tests/
│   │   └── README.md
│   └── ...
│
├── tests/                        # 単体テスト
│   ├── CMakeLists.txt
│   └── test_*.cpp
│
└── benchmarks/                   # パフォーマンス測定
    ├── CMakeLists.txt
    └── bench_*.cpp
```

**命名規則**:

- 演習: `01-topic-name/` （番号付き、ハイフン区切り）
- プロジェクト: `project-name/` （説明的な名前）
- ファイル: `snake_case.cpp`, `snake_case.h`

**各演習の構成**:

```
exercises/XX-topic-name/
├── CMakeLists.txt      # ビルド設定
├── main.cpp            # メインコード
├── README.md           # 課題説明・学習メモ
└── solution.cpp        # 解答例（任意）
```

---

### 3. `cpp20/` - C++20 演習（メイン）

**最も重要なディレクトリ**。UE 5.7 の最小要件である C++20 を集中的に学習。

```
cpp20/
├── CMakeLists.txt                # C++20 用ビルド設定
│
├── exercises/                    # 個別の演習課題
│   ├── 01-concepts/              # コンセプト
│   │   ├── basic-concepts/
│   │   ├── standard-concepts/
│   │   ├── custom-concepts/
│   │   └── README.md
│   ├── 02-ranges/                # レンジ
│   │   ├── views/
│   │   ├── algorithms/
│   │   ├── pipelines/
│   │   └── README.md
│   ├── 03-coroutines/            # コルーチン
│   │   ├── generators/
│   │   ├── async-tasks/
│   │   └── README.md
│   ├── 04-modules/               # モジュール（実験的）
│   ├── 05-span/                  # std::span
│   ├── 06-format/                # std::format
│   ├── 07-three-way-comparison/  # 三方比較演算子
│   ├── 08-constexpr-extensions/  # constexpr 拡張
│   ├── 09-designated-initializers/  # 指定初期化子
│   └── 10-misc/                  # その他の機能
│
├── projects/                     # 統合プロジェクト
│   ├── event-system/             # 型安全なイベントシステム
│   ├── data-pipeline/            # データ処理パイプライン
│   └── async-loader/             # 非同期リソースローダー
│
├── unreal-examples/              # UE 5.7 向けサンプル
│   ├── concepts-in-ue/           # UE でのコンセプト活用
│   ├── ranges-with-tarray/       # TArray との連携
│   ├── coroutines-gameplay/      # ゲームプレイでの活用
│   └── README.md
│
├── tests/                        # 単体テスト
└── benchmarks/                   # パフォーマンス測定
```

**重要度の高い機能**（UE 5.7 で実際に使用）:

1. コンセプト（Concepts）
2. レンジ（Ranges）
3. std::span
4. コルーチン（Coroutines）
5. 指定初期化子

---

### 4. `cpp23/` - C++23 演習

C++23 の新機能を学習。UE では未サポートだが、将来を見据えて学習。

```
cpp23/
├── CMakeLists.txt
│
├── exercises/
│   ├── 01-expected/              # std::expected（Result型）
│   ├── 02-mdspan/                # 多次元配列ビュー
│   ├── 03-generator/             # std::generator
│   ├── 04-print/                 # std::print/println
│   ├── 05-deducing-this/         # 明示的オブジェクトパラメータ
│   ├── 06-flat-containers/       # flat_map/flat_set
│   ├── 07-ranges-extensions/     # Ranges 拡張
│   └── 08-stacktrace/            # std::stacktrace
│
├── projects/
│   ├── config-parser/            # 堅牢なコンフィグパーサー
│   └── image-processor/          # 画像処理ライブラリ
│
├── tests/
└── benchmarks/
```

---

### 5. `cpp26/` - C++26 実験的機能

提案段階の C++26 機能を実験。

```
cpp26/
├── CMakeLists.txt
│
├── experiments/                  # 実験的コード
│   ├── reflection/               # 静的リフレクション
│   ├── contracts/                # 契約プログラミング
│   ├── execution/                # Senders/Receivers
│   └── pattern-matching/         # パターンマッチング
│
└── README.md                     # 注意事項・サポート状況
```

**注意**:

- コンパイラサポートが不完全な可能性
- 仕様が変更される可能性
- 学習・実験目的のみ

---

### 6. `cross_cutting/` - 横断的トピック

C++バージョンに依存しない、あるいは複数バージョンにまたがるトピック。

```
cross_cutting/
├── CMakeLists.txt
│
├── templates/                    # テンプレートメタプログラミング
│   ├── sfinae/
│   ├── type-traits/
│   ├── variadic-templates/
│   ├── concepts-vs-sfinae/
│   └── README.md
│
├── concurrency/                  # 並行性・並列性
│   ├── threads/
│   ├── atomic/
│   ├── memory-model/
│   ├── synchronization/
│   ├── parallel-algorithms/
│   └── README.md
│
├── dod/                          # データ指向設計
│   ├── soa-vs-aos/               # Structure of Arrays vs Array of Structures
│   ├── cache-efficiency/
│   ├── hot-cold-separation/
│   └── README.md
│
├── performance/                  # パフォーマンス最適化
│   ├── move-semantics/
│   ├── rvo-nrvo/
│   ├── constexpr-optimization/
│   └── README.md
│
├── memory-management/            # メモリ管理
│   ├── smart-pointers/
│   ├── custom-allocators/
│   ├── memory-pools/
│   └── README.md
│
└── design-patterns/              # デザインパターン（モダンC++版）
    ├── creational/
    ├── structural/
    ├── behavioral/
    └── README.md
```

**用途**:

- 基礎的だが重要なトピック
- C++バージョンによる進化を比較
- ゲーム開発で必須の知識

---

### 7. `libs/` - 共通ユーティリティライブラリ

各演習やプロジェクトで共通して使うライブラリコード。

```
libs/
├── CMakeLists.txt
│
├── common/                       # 汎用ユーティリティ
│   ├── include/common/
│   │   ├── math.h
│   │   ├── string_utils.h
│   │   └── timer.h
│   ├── src/
│   └── CMakeLists.txt
│
├── testing/                      # テスト用ユーティリティ
│   ├── include/testing/
│   │   ├── test_helpers.h
│   │   └── mock_objects.h
│   └── CMakeLists.txt
│
└── benchmarking/                 # ベンチマーク用ユーティリティ
    ├── include/benchmarking/
    │   └── benchmark_helpers.h
    └── CMakeLists.txt
```

**方針**:

- ヘッダオンリーライブラリを優先
- 静的リンクライブラリとして提供
- 各演習から簡単にリンクできる構造

---

### 8. `sandbox/` - 実験・プロトタイプ

一時的な実験やアイデアの検証用。

```
sandbox/
├── CMakeLists.txt                # シンプルな構成
├── experiment1.cpp
├── experiment2.cpp
├── prototype/
│   └── ...
└── README.md                     # 注意書き
```

**用途**:

- 新しいアイデアの迅速な検証
- StackOverflow のコードスニペット検証
- 一時的なデバッグコード

**注意**:

- コード品質の基準は緩い
- 長期保存には不向き
- 有用なコードは適切なディレクトリへ移動

---

## ビルドシステム設計

### CMake 構成

```
cpp-playground/
├── CMakeLists.txt                # ルート設定
│   ├── グローバルオプション
│   ├── コンパイラ設定
│   ├── Clang-Tidy 統合
│   ├── 警告レベル設定
│   └── サブディレクトリ追加
│
├── cpp17/CMakeLists.txt          # C++17 標準設定
├── cpp20/CMakeLists.txt          # C++20 標準設定
├── cpp23/CMakeLists.txt          # C++23 標準設定
├── cpp26/CMakeLists.txt          # C++26 標準設定
├── cross_cutting/CMakeLists.txt
├── libs/CMakeLists.txt
└── sandbox/CMakeLists.txt
```

### ビルドオプション

```cmake
# 基本オプション
cmake -B build \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_CPP17=ON \
    -DBUILD_CPP20=ON \
    -DBUILD_CPP23=OFF \
    -DBUILD_CPP26=OFF

# 厳格モード
cmake -B build \
    -DENABLE_CLANG_TIDY=ON \
    -DENABLE_WARNINGS_AS_ERRORS=ON \
    -DENABLE_SANITIZERS=ON
```

---

## 命名規則

### ディレクトリ名

- **演習**: `XX-topic-name/` （例: `01-concepts/`, `02-ranges/`）
- **プロジェクト**: `project-name/` （例: `event-system/`, `asset-manager/`）
- **ライブラリ**: `library-name/` （例: `common/`, `testing/`）

### ファイル名

- **ソースファイル**: `snake_case.cpp`
- **ヘッダファイル**: `snake_case.h`
- **テストファイル**: `test_component.cpp`
- **ベンチマーク**: `bench_algorithm.cpp`
- **ドキュメント**: `kebab-case.md` or `UPPERCASE.md`

### コード内の命名（Google Style 準拠）

```cpp
// namespace: lower_case
namespace my_namespace {

// Class/Struct: CamelCase
class MyClass {
public:
    // Function: CamelCase
    void DoSomething();

    // Member variable: lower_case with trailing underscore
    int member_variable_;

private:
    std::string private_member_;
};

// Constant: kCamelCase
const int kMaxSize = 100;

// Variable: lower_case
int local_variable = 42;

// Enum class: CamelCase
enum class Color {
    kRed,    // kCamelCase
    kGreen,
    kBlue
};

}  // namespace my_namespace
```

---

## Git ワークフロー

### ブランチ戦略

```
main                              # 安定版（学習完了したコード）
  ├── feature/cpp17-exercises     # C++17 演習開発
  ├── feature/cpp20-concepts      # C++20 コンセプト学習
  ├── feature/ue57-examples       # UE 5.7 サンプル
  └── experiment/reflection       # 実験的機能
```

### コミットメッセージ

```
<type>(<scope>): <subject>

<body>

<footer>
```

**Type**:

- `feat`: 新しい演習やプロジェクト
- `fix`: バグ修正
- `docs`: ドキュメント更新
- `refactor`: リファクタリング
- `test`: テスト追加
- `chore`: ビルドシステムや設定変更

**例**:

```
feat(cpp20): Add concepts basic exercises

- Add standard concepts examples
- Add custom concept definitions
- Add exercises with solutions

Refs: modern-cpp-curriculum.md Phase 2
```

---

## 学習進捗管理

### PROGRESS.md フォーマット

```markdown
# 学習進捗

## 現在の Phase: Phase 2 - C++20

## 完了したトピック

### Phase 1: C++17

- [x] 1.1 構造化束縛
- [x] 1.2 if/switch 初期化式
- [x] 1.3 クラステンプレート引数推論
- [x] 1.4 constexpr if
- [x] 1.5 fold expressions
- [x] 1.6 属性
- [x] 1.7 std::optional
- [x] 1.8 std::variant
- [x] 1.9 std::string_view
- [x] 1.10 std::filesystem
- [x] P1 総合課題: ミニアセットマネージャー

### Phase 2: C++20（進行中）

- [x] 2.1 コンセプト（Concepts）
- [ ] 2.2 レンジ（Ranges）- 進行中
- [ ] 2.3 コルーチン（Coroutines）
- [ ] 2.4 モジュール（Modules）
- [ ] 2.5 その他の機能

## 次のセッション

- 2.2 レンジの views と algorithms の続きから開始
- 演習 2.2.2 を完了させる
```

---

## テスト戦略

### 単体テスト

各演習・プロジェクトに対応するテストを作成。

```cpp
// cpp20/tests/test_concepts.cpp
#include <concepts>
#include <gtest/gtest.h>

TEST(ConceptsTest, IntegralConcept) {
    EXPECT_TRUE(std::integral<int>);
    EXPECT_FALSE(std::integral<float>);
}
```

**テストフレームワーク**: Google Test（推奨）

### ベンチマーク

パフォーマンスが重要な機能は計測。

```cpp
// cpp20/benchmarks/bench_ranges.cpp
#include <benchmark/benchmark.h>
#include <ranges>

static void BM_RangesPipeline(benchmark::State& state) {
    for (auto _ : state) {
        // ベンチマーク対象
    }
}
BENCHMARK(BM_RangesPipeline);
```

**ベンチマークライブラリ**: Google Benchmark（推奨）

---

## 将来の拡張計画

### Phase 5: Unreal Engine 統合（将来）

UE プロジェクトとの統合を想定。

```
unreal-integration/              # 将来追加予定
├── ue-project/                  # UE 5.7 プロジェクト
│   ├── Source/
│   ├── Content/
│   └── Config/
│
└── examples/                    # 学習コードの UE 移植
    ├── concepts-gameplay/
    ├── ranges-ecs/
    └── coroutines-ai/
```

### Phase 6: 高度なトピック（将来）

```
advanced/                        # 将来追加予定
├── compiler-internals/          # コンパイラの内部動作
├── abi-compatibility/           # ABI 互換性
├── optimization-techniques/     # 最適化テクニック
└── low-level-programming/       # 低レベルプログラミング
```

---

## 参考資料

### プロジェクト構成の参考

- [LLVM Project Structure](https://llvm.org/docs/GettingStarted.html#directory-layout)
- [Google Test Best Practices](https://google.github.io/googletest/)
- [Modern CMake Tutorial](https://cliutils.gitlab.io/modern-cmake/)

### コーディング規約

- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
- [Epic C++ Coding Standard](https://dev.epicgames.com/documentation/en-us/unreal-engine/epic-cplusplus-coding-standard-for-unreal-engine)

---

## まとめ

### ディレクトリ構成の特徴

1. **明確な分離**: C++バージョン別、トピック別に明確に分離
2. **段階的な学習**: 演習 → プロジェクト → 統合の流れ
3. **UE 5.7 対応**: C++20 を中心に、実用的な学習パス
4. **品質保証**: テスト、ベンチマーク、静的解析の統合
5. **拡張性**: 将来の機能追加を考慮した設計

### 運用ガイドライン

1. **新しい演習の追加**:

   - 適切なディレクトリ（`cppXX/exercises/`）に配置
   - `README.md` で課題内容を記録
   - `CMakeLists.txt` を追加
   - テストを書く（可能な限り）

2. **学習の進め方**:

   - `docs/modern-cpp-curriculum.md` に従う
   - 各演習を順番に進める
   - `docs/progress/PROGRESS.md` を更新
   - 完了したらコミット

3. **コード品質の維持**:

   - Clang-Format で自動フォーマット
   - Clang-Tidy で静的解析
   - コンパイラ警告を無視しない
   - テストを書く習慣

4. **ドキュメントの更新**:
   - 学びを `README.md` に記録
   - 疑問点・気づきをメモ
   - 参考資料のリンクを追加
