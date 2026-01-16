# Phase 2: C++20学習教材

**Phase 2はUnreal Engine 5.7の最小要件です！** C++20の4大機能（Concepts, Ranges, Coroutines, Modules）を中心に学習します。

## 🎯 重要度について

UE 5.7での実用性を基準に優先度を設定しています：

- ⭐⭐⭐⭐⭐ **最優先** - UE開発で頻繁に使用
- ⭐⭐⭐ **推奨** - 便利で使用機会がある
- ⭐ **余裕があれば** - UEには代替機能がある

## 📚 演習一覧

| # | トピック | Issue | 優先度 | UE対応 |
|---|---------|-------|--------|--------|
| 01 | [コンセプト（Concepts）](exercises/01-concepts/) | [#12](https://github.com/itsakeyfut/cpp-playground/issues/12) | ⭐⭐⭐⭐⭐ | ✅ |
| 02 | [レンジ（Ranges）](exercises/02-ranges/) | [#13](https://github.com/itsakeyfut/cpp-playground/issues/13) | ⭐⭐⭐⭐⭐ | ✅ |
| 03 | [コルーチン（Coroutines）](exercises/03-coroutines/) | [#14](https://github.com/itsakeyfut/cpp-playground/issues/14) | ⭐⭐⭐⭐ | ✅ |
| 04 | [モジュール（Modules）](exercises/04-modules/) | [#15](https://github.com/itsakeyfut/cpp-playground/issues/15) | ⭐ | ⚠️ 実験的 |
| 05 | [std::span](exercises/05-span/) | [#16](https://github.com/itsakeyfut/cpp-playground/issues/16) | ⭐⭐⭐⭐⭐ | ✅ |
| 06 | [std::format](exercises/06-format/) | [#17](https://github.com/itsakeyfut/cpp-playground/issues/17) | ⭐ | ⚠️ UEはFString::Printf |
| 07 | [三方比較演算子（<=>）](exercises/07-three-way-comparison/) | [#18](https://github.com/itsakeyfut/cpp-playground/issues/18) | ⭐⭐ | ✅ |
| 08 | [constexpr拡張](exercises/08-constexpr-extensions/) | [#19](https://github.com/itsakeyfut/cpp-playground/issues/19) | ⭐⭐⭐ | ✅ |
| 09 | [指定初期化子](exercises/09-designated-initializers/) | [#20](https://github.com/itsakeyfut/cpp-playground/issues/20) | ⭐⭐⭐ | ✅ |

## 🚀 クイックスタート

### 方法1: 個別の演習をビルド

```bash
cd exercises/01-concepts
mkdir build && cd build
cmake ..
cmake --build . --config Release

# 実行
./Release/example.exe    # サンプルコードを見る
./Release/exercise.exe   # 演習に取り組む
./Release/solution.exe   # 解答例を確認
```

### 方法2: 全演習を一括ビルド

```bash
# cpp20/ ディレクトリで
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

## 📖 Phase 2の特徴

### C++20の4大機能

1. **Concepts（コンセプト）** - 型制約で安全なジェネリックプログラミング
2. **Ranges（レンジ）** - 関数型プログラミング風のデータ処理
3. **Coroutines（コルーチン）** - 非同期処理の簡潔な記述
4. **Modules（モジュール）** - ヘッダーに代わる新しいモジュールシステム

### Rustユーザーへの対応

| C++20 | Rust |
|-------|------|
| `std::span<T>` | `&[T]` (slice) |
| Concepts | Trait bounds |
| Ranges | Iterator adapters |
| Coroutines | async/await |
| Modules | mod/use |

## 🎯 推奨学習順序

### ステップ1: 必須機能（最優先）
**UE 5.7で頻繁に使用する機能**

1. ✅ **01 - Concepts** - 型安全なテンプレート
2. ✅ **02 - Ranges** - TArrayとの連携
3. ✅ **05 - span** - メモリ安全な配列操作

→ この3つを最初に学習することを強く推奨

### ステップ2: 推奨機能
**便利で実用的な機能**

4. ✅ **03 - Coroutines** - 非同期処理
5. ✅ **09 - Designated Initializers** - 構造体初期化
6. ✅ **08 - constexpr Extensions** - コンパイル時処理

### ステップ3: 余裕があれば
**知っておくと良い機能**

7. ⚠️ **07 - Three-way Comparison** - カスタム型の比較
8. ⚠️ **06 - format** - 文字列フォーマット（UEはFString::Printf）
9. ⚠️ **04 - Modules** - 実験的（UE未サポート）

## 🎮 Unreal Engine 5.7との互換性

### ✅ 使える機能（積極的に使うべき）

- **Concepts** - Actor、Component等の型制約に最適
- **Ranges** - TArrayの処理を簡潔に
- **std::span** - 配列の参照渡しに最適
- **Coroutines** - ゲームプレイの非同期処理
- **Designated Initializers** - USTRUCT初期化

### ⚠️ 制限がある機能

- **Modules** - UnrealBuildToolとの互換性未確認
- **std::format** - FString::Printfを推奨

### 📝 UE 5.7でのコーディング例

```cpp
// Concepts - Actor型の制約
template<typename T>
concept DerivedFromActor = std::is_base_of_v<AActor, T>;

template<DerivedFromActor T>
T* SpawnActor(UWorld* World, FVector Location) {
    return World->SpawnActor<T>(Location, FRotator::ZeroRotator);
}

// Ranges - TArrayの処理
TArray<AActor*> Actors;
auto EnemyActors = Actors
    | std::views::filter([](AActor* Actor) {
        return Actor->ActorHasTag(TEXT("Enemy"));
    });

// std::span - TArrayのビュー
void ProcessActors(std::span<AActor*> Actors) {
    for (AActor* Actor : Actors) {
        // 処理
    }
}
ProcessActors(std::span(MyArray.GetData(), MyArray.Num()));

// Designated Initializers - 構造体初期化
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

## 📋 学習の進め方

### Phase 1とPhase 2の違い

- **Phase 1 (C++17)** - 便利な構文糖衣、型安全性の向上
- **Phase 2 (C++20)** - プログラミングパラダイムの変化、UE 5.7必須

Phase 2は**より実践的**で、**UE開発に直結**する内容です。

### 学習フロー

```
1. example.cpp を実行・理解
   ↓
2. UE 5.7での使用例を確認（README.md）
   ↓
3. exercise.cpp のTODOを埋める
   ↓
4. solution.cpp で答え合わせ
   ↓
5. 実際のUEプロジェクトで試す
```

## 🔧 要件

- **C++20対応コンパイラ**
  - GCC 10.0以上
  - Clang 10.0以上
  - MSVC 2019 16.8以上（Visual Studio 2019）

- **CMake 3.20以上**

- **Unreal Engine 5.7**（実践用）

## 💡 Phase 2で学ぶこと

### Before (C++17)

```cpp
// 従来の方法
template<typename T>
void process(T value) {
    static_assert(std::is_integral_v<T>, "Must be integral");
    // ...
}
```

### After (C++20)

```cpp
// Conceptsを使った方法
template<std::integral T>
void process(T value) {
    // ...
}
```

**より安全**で、**より読みやすい**コードが書けるようになります。

## 🎓 総合課題

Phase 2を完了したら、以下の総合課題に挑戦：

1. 📦 [型安全なイベントシステム](projects/event-system/) - Issue [#21](https://github.com/itsakeyfut/cpp-playground/issues/21)
2. 🔄 [データ処理パイプライン](projects/data-pipeline/) - Issue [#22](https://github.com/itsakeyfut/cpp-playground/issues/22)
3. ⏳ [非同期リソースローダー](projects/async-loader/) - Issue [#23](https://github.com/itsakeyfut/cpp-playground/issues/23)

## 🔗 参考資料

### 公式ドキュメント

- [Epic C++ Coding Standard](https://dev.epicgames.com/documentation/en-us/unreal-engine/epic-cplusplus-coding-standard-for-unreal-engine)
- [UE 5.7 C++20 Guide](../docs/unreal-engine-cpp20-guide.md)
- [Modern C++ Curriculum](../docs/modern-cpp-curriculum.md)

### C++20学習リソース

- [cppreference - C++20](https://en.cppreference.com/w/cpp/20)
- [C++20 Features](https://github.com/AnthonyCalandra/modern-cpp-features#cpp20)
- [Clang C++20 Status](https://clang.llvm.org/cxx_status.html)

## ❓ よくある質問

### Q1: Phase 1を完了していないとダメ？

**A**: Phase 2から始めても大丈夫ですが、以下の知識は前提とします：
- 構造化束縛
- if初期化式
- std::optional
- std::variant

### Q2: UE 5.7なしでも学習できる？

**A**: できます！純粋なC++20として学習し、後でUEに適用できます。

### Q3: 一番重要な演習は？

**A**: **Concepts**, **Ranges**, **std::span** の3つです。これだけは必ずマスターしてください。

## 🚀 次のステップ

Phase 2を完了したら：

1. ✅ GitHubのIssue #12〜#20をクローズ
2. 🎮 総合課題に挑戦
3. 🔥 [Phase 3: C++23](../cpp23/) へ進む（UE未対応だが将来を見据えて）
4. 🎯 実際のUE 5.7プロジェクトで実践

---

**重要**: C++20はUE 5.7の最小要件です。ゲーム開発者として、これらの機能を理解することは必須です！
