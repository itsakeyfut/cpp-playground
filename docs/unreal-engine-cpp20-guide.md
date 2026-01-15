# Unreal Engine 5.7 向け C++20 学習ガイド

## はじめに

このガイドは、Unreal Engine 5.7 でのゲーム開発に必要な C++20 の機能を学習するためのロードマップです。

**重要**: Unreal Engine 5.7 は **C++20 をデフォルトかつ最小要件**として使用します。

## Unreal Engine 5.7 の C++ サポート

### 公式情報

Unreal Engine 5.7 は C++20 をフルサポートしており、以下の方針があります：

- **言語バージョン**: C++20 がデフォルト
- **最小要件**: C++20 が必須
- **移行**: C++17 からの大幅なアップグレード（UE 5.6 以前から）

参考: [Epic C++ Coding Standard for Unreal Engine](https://dev.epicgames.com/documentation/en-us/unreal-engine/epic-cplusplus-coding-standard-for-unreal-engine)

## UE 5.7 で使える C++20 機能

### 優先度：高（必ず学ぶべき）

#### 1. コンセプト（Concepts）

**UE での用途**: テンプレート制約、型安全なジェネリックプログラミング

```cpp
// コンセプトの定義
template<typename T>
concept Numeric = std::is_arithmetic_v<T>;

// UE での使用例：ジェネリックな数値処理
template<Numeric T>
T Clamp(T Value, T Min, T Max) {
    return FMath::Clamp(Value, Min, Max);
}

// コンセプトを使った Actor の制約
template<typename T>
concept DerivedFromActor = std::is_base_of_v<AActor, T>;

template<DerivedFromActor T>
T* SpawnActor(UWorld* World, FVector Location) {
    return World->SpawnActor<T>(Location, FRotator::ZeroRotator);
}
```

**学習優先度**: ★★★★★

#### 2. 範囲（Ranges）

**UE での用途**: コレクションの操作、TArray の処理

```cpp
#include <ranges>

// UE の TArray を範囲で処理
TArray<AActor*> Actors;
GetWorld()->GetAllActors(Actors);

// フィルタリング
auto EnemyActors = Actors
    | std::views::filter([](AActor* Actor) {
        return Actor->ActorHasTag(TEXT("Enemy"));
    });

// 変換
auto Locations = Actors
    | std::views::transform([](AActor* Actor) {
        return Actor->GetActorLocation();
    });

// パイプライン操作
auto NearbyEnemies = Actors
    | std::views::filter([](AActor* Actor) {
        return Actor->ActorHasTag(TEXT("Enemy"));
    })
    | std::views::filter([PlayerLoc](AActor* Actor) {
        return FVector::Dist(Actor->GetActorLocation(), PlayerLoc) < 1000.0f;
    })
    | std::views::take(10);
```

**学習優先度**: ★★★★★

#### 3. コルーチン（Coroutines）

**UE での用途**: 非同期処理、タイムライン、シーケンス処理

```cpp
#include <coroutine>

// コルーチンでの遅延実行
struct DelayedAction {
    struct promise_type {
        DelayedAction get_return_object() { return {}; }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };
};

DelayedAction PlaySequence(AActor* Actor) {
    // アニメーション再生
    Actor->PlayAnimation();

    co_await std::suspend_always{};  // 待機

    // 次のアクション
    Actor->TriggerEffect();

    co_await std::suspend_always{};  // 待機

    // 完了
    Actor->OnSequenceComplete();
}
```

**学習優先度**: ★★★★☆

#### 4. std::span

**UE での用途**: 配列ビュー、メモリ安全性

```cpp
#include <span>

// TArray を span で扱う（コピーなし）
void ProcessActors(std::span<AActor*> Actors) {
    for (AActor* Actor : Actors) {
        // 処理
    }
}

// 使用例
TArray<AActor*> MyActors;
ProcessActors(std::span(MyActors.GetData(), MyActors.Num()));

// const span で読み取り専用
void DisplayActorNames(std::span<const AActor*> Actors) {
    for (const AActor* Actor : Actors) {
        UE_LOG(LogTemp, Log, TEXT("%s"), *Actor->GetName());
    }
}
```

**学習優先度**: ★★★★☆

### 優先度：中（推奨）

#### 5. 指定初期化子（Designated Initializers）

**UE での用途**: 構造体の初期化

```cpp
// UE の構造体初期化
USTRUCT()
struct FCharacterStats {
    UPROPERTY()
    float Health = 100.0f;

    UPROPERTY()
    float Stamina = 100.0f;

    UPROPERTY()
    float Mana = 50.0f;
};

// C++20 の指定初期化子
FCharacterStats Stats {
    .Health = 150.0f,
    .Stamina = 120.0f,
    .Mana = 80.0f
};
```

**学習優先度**: ★★★☆☆

#### 6. ラムダ式のテンプレート

**UE での用途**: ジェネリックなコールバック

```cpp
// テンプレートラムダ
auto GenericCompare = []<typename T>(const T& A, const T& B) {
    return A < B;
};

// UE での使用例：汎用ソート
TArray<int32> IntArray = {5, 2, 8, 1};
IntArray.Sort(GenericCompare);

TArray<float> FloatArray = {3.5f, 1.2f, 7.8f};
FloatArray.Sort(GenericCompare);

// Actor のソート
TArray<AActor*> Actors;
Actors.Sort([]<typename T>(const T& A, const T& B) {
    return A->GetName() < B->GetName();
});
```

**学習優先度**: ★★★☆☆

#### 7. constexpr 仮想関数

**UE での用途**: コンパイル時多態性

```cpp
struct ICalculator {
    constexpr virtual int Calculate(int x) const = 0;
    constexpr virtual ~ICalculator() = default;
};

struct Doubler : ICalculator {
    constexpr int Calculate(int x) const override {
        return x * 2;
    }
};

// コンパイル時に計算
constexpr int Result = [] {
    Doubler calc;
    return calc.Calculate(21);  // 42
}();
```

**学習優先度**: ★★☆☆☆

### 優先度：低（知っておくと良い）

#### 8. 3方比較演算子（<=>）

**UE での用途**: カスタム型の比較

```cpp
#include <compare>

USTRUCT()
struct FVersion {
    int32 Major;
    int32 Minor;
    int32 Patch;

    // 3方比較演算子
    auto operator<=>(const FVersion&) const = default;
};

// 使用例
FVersion V1{1, 2, 3};
FVersion V2{1, 2, 4};

if (V1 < V2) {  // 自動的に比較演算子が生成される
    UE_LOG(LogTemp, Log, TEXT("V1 is older"));
}
```

**学習優先度**: ★★☆☆☆

#### 9. std::format（C++20）

**UE での用途**: 型安全な文字列フォーマット

```cpp
#include <format>

// 型安全なフォーマット
std::string Message = std::format("Health: {}, Mana: {}", 100, 50);

// UE の FString に変換
FString UEMessage = FString(Message.c_str());

// または UE のフォーマット関数を使用
FString UEFormat = FString::Printf(TEXT("Health: %d, Mana: %d"), 100, 50);
```

**学習優先度**: ★☆☆☆☆（UE には独自のフォーマット機能がある）

## 学習できないC++20機能（UEで制限）

### 構造化束縛（Structured Bindings）

**Epic コーディング規約で制限される可能性**があります。

```cpp
// C++20 では可能だが、UE では推奨されない場合あり
auto [X, Y, Z] = Actor->GetActorLocation();

// UE では従来の方法を推奨
FVector Location = Actor->GetActorLocation();
float X = Location.X;
float Y = Location.Y;
float Z = Location.Z;
```

### モジュール（Modules）

UE のビルドシステム（UnrealBuildTool）との互換性が未確認です。

```cpp
// C++20 モジュール（UE では未サポート）
import std.core;

// UE では従来の #include を使用
#include "CoreMinimal.h"
```

## 学習ロードマップ

### フェーズ 1: 基礎（1-2週間）

1. **コンセプト**の基本を理解
2. **std::span**でメモリ安全な配列操作
3. **指定初期化子**で構造体を扱う

### フェーズ 2: 実践（2-3週間）

4. **範囲（Ranges）**でコレクション処理を学ぶ
5. **ラムダテンプレート**でジェネリックプログラミング
6. **constexpr仮想関数**でコンパイル時処理

### フェーズ 3: 応用（2-3週間）

7. **コルーチン**で非同期処理を実装
8. **3方比較演算子**でカスタム型の比較
9. 実際のUEプロジェクトで適用

## UE プロジェクトでの実践例

### 例1: コンセプトを使ったジェネリック関数

```cpp
// GameplayUtilities.h
#pragma once

#include <concepts>

template<typename T>
concept GameplayActor = std::is_base_of_v<AActor, T>;

template<GameplayActor T>
class TActorPool {
public:
    TArray<T*> Pool;

    T* Acquire(UWorld* World) {
        if (Pool.Num() > 0) {
            return Pool.Pop();
        }
        return World->SpawnActor<T>();
    }

    void Release(T* Actor) {
        Pool.Add(Actor);
    }
};
```

### 例2: 範囲を使ったアクター検索

```cpp
// ActorManager.cpp
#include <ranges>

TArray<AEnemy*> UActorManager::FindNearbyEnemies(FVector Location, float Radius) {
    TArray<AActor*> AllActors;
    GetWorld()->GetAllActors(AllActors);

    // 範囲で処理
    auto NearbyEnemies = AllActors
        | std::views::filter([](AActor* Actor) {
            return Cast<AEnemy>(Actor) != nullptr;
        })
        | std::views::transform([](AActor* Actor) {
            return Cast<AEnemy>(Actor);
        })
        | std::views::filter([Location, Radius](AEnemy* Enemy) {
            return FVector::Dist(Enemy->GetActorLocation(), Location) < Radius;
        });

    TArray<AEnemy*> Result;
    for (AEnemy* Enemy : NearbyEnemies) {
        Result.Add(Enemy);
    }

    return Result;
}
```

## Epic コーディング規約との違い

### 命名規則の違い

| 項目 | このプロジェクト（Google） | Epic スタイル |
|------|------------------------|--------------|
| クラス | `MyClass` | `FMyClass`, `UMyClass`, `AMyClass` |
| 関数 | `DoSomething()` | `DoSomething()` |
| 変数 | `my_variable` | `MyVariable` |
| メンバ変数 | `member_variable_` | `MemberVariable` |
| 定数 | `kConstant` | `CONSTANT` |

### ポインタ配置の違い

```cpp
// このプロジェクト（Google スタイル）
int* pointer;
AActor* actor;

// Epic スタイル
int *Pointer;
AActor *Actor;
```

### 推奨アプローチ

1. **学習フェーズ**: このプロジェクトでGoogleスタイルを使って**C++20の機能**を学ぶ
2. **移行フェーズ**: Epicスタイルの命名規則を理解する
3. **実装フェーズ**: UEプロジェクトでEpicスタイルを使う

**重要**: スタイルは変更可能。C++20の**機能そのもの**を理解することが最優先。

## 参考資料

### 公式ドキュメント

- [Epic C++ Coding Standard](https://dev.epicgames.com/documentation/en-us/unreal-engine/epic-cplusplus-coding-standard-for-unreal-engine)
- [Programming with C++ in Unreal Engine](https://dev.epicgames.com/documentation/en-us/unreal-engine/programming-with-cplusplus-in-unreal-engine)
- [Unreal Engine API Reference](https://dev.epicgames.com/documentation/en-us/unreal-engine/API)

### C++20 学習リソース

- [cppreference - C++20](https://en.cppreference.com/w/cpp/20)
- [C++20 の新機能](https://github.com/AnthonyCalandra/modern-cpp-features#cpp20)
- [Clang C++20 Status](https://clang.llvm.org/cxx_status.html)

### コミュニティ

- [Epic Developer Community Forums](https://forums.unrealengine.com/)
- [Unreal Slackers Discord](https://unrealslackers.org/)

## まとめ

### 学習の優先順位

1. ✅ **最優先**: コンセプト、範囲、std::span（UEで頻繁に使用）
2. ✅ **推奨**: ラムダテンプレート、指定初期化子（便利）
3. ✅ **余裕があれば**: コルーチン、constexpr仮想関数（高度）

### 次のステップ

1. このプロジェクトの `cpp20/` ディレクトリで各機能を実装
2. 小さなUEプロジェクトでC++20機能を試す
3. Epicコーディング規約を読んで、スタイルの違いを理解
4. 本格的なUE 5.7プロジェクトで実践

**重要**: C++20の機能を学ぶことで、UE 5.7での開発がより安全で効率的になります！
