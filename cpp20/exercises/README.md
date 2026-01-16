# Phase 2: C++20演習

**Unreal Engine 5.7の最小要件であるC++20を学習します。**

## 📚 演習一覧

| # | トピック | 優先度 | UE対応 | 学習時間 |
|---|---------|--------|--------|---------|
| 01 | コンセプト（Concepts） | ⭐⭐⭐⭐⭐ | ✅ | 2-3時間 |
| 02 | レンジ（Ranges） | ⭐⭐⭐⭐⭐ | ✅ | 3-4時間 |
| 03 | コルーチン（Coroutines） | ⭐⭐⭐⭐ | ✅ | 3-4時間 |
| 04 | モジュール（Modules） | ⭐ | ⚠️ | 1時間 |
| 05 | std::span | ⭐⭐⭐⭐⭐ | ✅ | 1-2時間 |
| 06 | std::format | ⭐ | ⚠️ | 1時間 |
| 07 | 三方比較演算子（<=>） | ⭐⭐ | ✅ | 1時間 |
| 08 | constexpr拡張 | ⭐⭐⭐ | ✅ | 1-2時間 |
| 09 | 指定初期化子 | ⭐⭐⭐ | ✅ | 30分 |

**合計学習時間**: 14-20時間

## 🎯 学習戦略

### 最優先コース（UE必須）⭐⭐⭐⭐⭐

**まずこの3つを集中的に学習：**

```
1. Concepts (01)     → 型安全なテンプレート
2. Ranges (02)       → TArrayの処理を簡潔に
3. std::span (05)    → メモリ安全な配列操作
```

**推定時間**: 6-9時間
**効果**: UE 5.7で最も頻繁に使用する機能をマスター

### 推奨コース（実用的）⭐⭐⭐

```
4. Coroutines (03)              → 非同期処理
5. Designated Initializers (09)  → 構造体初期化
6. constexpr Extensions (08)     → コンパイル時処理
```

**推定時間**: 5-7時間
**効果**: より洗練されたコードが書ける

### オプショナルコース（余裕があれば）⭐

```
7. Three-way Comparison (07)  → カスタム型の比較
8. std::format (06)           → 文字列フォーマット
9. Modules (04)               → モジュールシステム
```

**推定時間**: 3時間
**効果**: 知識の幅が広がる

## 📖 各演習の特徴

### 01 - Concepts（必須）

**学ぶこと**:
- 型制約による安全なテンプレート
- 標準コンセプト（std::integral, std::floating_pointなど）
- 自作コンセプトの定義

**Rustとの比較**: トレイト境界（trait bounds）

**UEでの使用例**:
```cpp
template<typename T>
concept DerivedFromActor = std::is_base_of_v<AActor, T>;

template<DerivedFromActor T>
T* SpawnActor(UWorld* World) { ... }
```

### 02 - Ranges（必須）

**学ぶこと**:
- パイプライン構文（`|`演算子）
- views（filter, transform, take等）
- TArrayとの連携

**Rustとの比較**: イテレータアダプタ（`iter().map().filter()`）

**UEでの使用例**:
```cpp
TArray<AActor*> Actors;
auto NearbyEnemies = Actors
    | std::views::filter([](AActor* A) { return A->ActorHasTag("Enemy"); })
    | std::views::filter([](AActor* A) { return Distance(A) < 1000.0f; })
    | std::views::take(10);
```

### 03 - Coroutines

**学ぶこと**:
- co_await, co_yield, co_return
- ジェネレータの実装
- 非同期処理の基礎

**Rustとの比較**: async/await

**UEでの使用例**:
```cpp
Generator<int> RangeGenerator(int start, int end) {
    for (int i = start; i < end; ++i) {
        co_yield i;
    }
}
```

### 04 - Modules（実験的）

**学ぶこと**:
- export module構文
- import文

**注意**: UnrealBuildToolとの互換性が未確認。学習目的のみ。

### 05 - std::span（必須）

**学ぶこと**:
- 配列ビューの使い方
- TArrayからの変換
- メモリ安全性

**Rustとの比較**: &[T]（スライス）

**UEでの使用例**:
```cpp
void ProcessActors(std::span<AActor*> Actors) {
    for (AActor* Actor : Actors) { ... }
}

TArray<AActor*> MyActors;
ProcessActors(std::span(MyActors.GetData(), MyActors.Num()));
```

### 06 - std::format

**学ぶこと**:
- 型安全な文字列フォーマット

**注意**: UEではFString::Printfを使うことが多い。

### 07 - Three-way Comparison

**学ぶこと**:
- operator<=>の基本
- default実装

**UEでの使用例**:
```cpp
struct FVersion {
    int Major, Minor, Patch;
    auto operator<=>(const FVersion&) const = default;
};
```

### 08 - constexpr Extensions

**学ぶこと**:
- constexpr仮想関数
- consteval（コンパイル時のみ評価）
- constinit（静的初期化保証）

### 09 - Designated Initializers

**学ぶこと**:
- 構造体の指定初期化

**UEでの使用例**:
```cpp
USTRUCT()
struct FCharacterStats {
    UPROPERTY()
    float Health = 100.0f;
    UPROPERTY()
    float Stamina = 100.0f;
};

FCharacterStats Stats {
    .Health = 150.0f,
    .Stamina = 120.0f
};
```

## 🔧 ビルド方法

### 個別演習のビルド

```bash
cd 01-concepts
mkdir build && cd build
cmake ..
cmake --build . --config Release

# 実行
./Release/example.exe
./Release/exercise.exe
./Release/solution.exe
```

### 全演習の一括ビルド

```bash
# cpp20/ ディレクトリで
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

## 💡 学習のヒント

### Phase 1からの違い

- **Phase 1 (C++17)**: 便利な構文、型安全性の向上
- **Phase 2 (C++20)**: プログラミングパラダイムの変化

Phase 2は**より深い**理解が必要です。

### つまずきやすいポイント

1. **Concepts**: requires節の書き方
2. **Ranges**: 遅延評価の理解
3. **Coroutines**: promise_typeの実装

→ example.cppをしっかり読みましょう！

### 効率的な学習方法

```
1. README.mdを読む（10分）
   ↓
2. example.cppを実行して動作確認（10分）
   ↓
3. example.cppを写経しながら理解（30-60分）
   ↓
4. exercise.cppのTODOを埋める（30-60分）
   ↓
5. solution.cppで答え合わせ（10分）
```

**合計**: 1.5-3時間/演習

## 🎮 UE 5.7プロジェクトでの実践

Phase 2を完了したら、実際のUEプロジェクトで試してみましょう：

### 実践例1: Conceptsでアクター型を制約

```cpp
// YourProject/Source/YourProject/Public/GameplayUtilities.h
template<typename T>
concept GameplayActor = std::is_base_of_v<AActor, T>;

template<GameplayActor T>
TArray<T*> FindAllActorsOfType(UWorld* World) {
    TArray<AActor*> AllActors;
    TArray<T*> Result;
    // ...
    return Result;
}
```

### 実践例2: Rangesでエネミー検索

```cpp
// YourProject/Source/YourProject/Private/CombatSystem.cpp
TArray<AEnemy*> FindNearbyEnemies(FVector Location, float Radius) {
    TArray<AActor*> AllActors;
    GetWorld()->GetAllActors(AllActors);

    auto NearbyEnemies = AllActors
        | std::views::transform([](AActor* A) { return Cast<AEnemy>(A); })
        | std::views::filter([](AEnemy* E) { return E != nullptr; })
        | std::views::filter([Location, Radius](AEnemy* E) {
            return FVector::Dist(E->GetActorLocation(), Location) < Radius;
        });

    TArray<AEnemy*> Result;
    for (AEnemy* E : NearbyEnemies) {
        Result.Add(E);
    }
    return Result;
}
```

## ❓ トラブルシューティング

### コンパイラがC++20をサポートしていない

```bash
# 確認方法
g++ --version    # GCC 10.0以上
clang++ --version # Clang 10.0以上

# MSVCの場合
# Visual Studio 2019 16.8以上が必要
```

### Rangesのビルドエラー

```cpp
// 必要なヘッダーをインクルード
#include <ranges>
#include <algorithm>
```

### Coroutinesがビルドできない

コンパイラによってサポート状況が異なります。
- GCC 10以上
- Clang 10以上
- MSVC 2019 16.8以上

## 🎓 次のステップ

Phase 2を完了したら：

1. ✅ GitHubのIssue #12〜#20をクローズ
2. 📦 [総合課題1: 型安全なイベントシステム](../projects/event-system/)
3. 🔄 [総合課題2: データ処理パイプライン](../projects/data-pipeline/)
4. ⏳ [総合課題3: 非同期リソースローダー](../projects/async-loader/)
5. 🚀 [Phase 3: C++23](../../cpp23/)へ進む

## 📚 参考資料

- [UE 5.7 C++20 Guide](../../docs/unreal-engine-cpp20-guide.md)
- [Modern C++ Curriculum](../../docs/modern-cpp-curriculum.md)
- [cppreference - C++20](https://en.cppreference.com/w/cpp/20)

---

**重要**: Phase 2はUE 5.7開発の基礎です。時間をかけてしっかり学習しましょう！
