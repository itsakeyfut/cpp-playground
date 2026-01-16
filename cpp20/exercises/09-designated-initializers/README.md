# 2.5.5 指定初期化子（Designated Initializers）★★★

## 概要

C++20で導入された指定初期化子は、構造体のメンバを名前で指定して初期化できる機能です。C言語では以前からサポートされていましたが、C++20で正式に標準化されました。

**Rustとの比較**: 構造体リテラルの名前付きフィールド初期化に相当します。

```rust
// Rust
struct Config {
    width: i32,
    height: i32,
    fullscreen: bool,
}

let config = Config {
    width: 1920,
    height: 1080,
    fullscreen: true,
};
```

```cpp
// C++20
struct Config {
    int width = 800;
    int height = 600;
    bool fullscreen = false;
};

Config config = {
    .width = 1920,
    .height = 1080,
    .fullscreen = true
};
```

**Unreal Engine 5.7での重要度**: ★★★（最高優先度）
UE 5.7では構造体の初期化に指定初期化子の使用が推奨されています。

## 学習内容

1. **基本的な指定初期化子**
   - `.member = value` 構文
   - デフォルト値との組み合わせ
   - 順序の制約

2. **UESTRUCTとの組み合わせ**
   - FCharacterStats等の初期化
   - UPROPERTY付きメンバの初期化

3. **実用例**
   - ゲームの設定構造体
   - キャラクターステータス
   - UI設定

## ファイル

- **example.cpp**: 写経用の完全なサンプルコード
- **exercise.cpp**: 演習問題（TODOを埋める）
- **solution.cpp**: 解答例

## 演習課題

### 演習 2.5.5.1
基本的な構造体に指定初期化子を使って値を設定せよ。

### 演習 2.5.5.2
ゲームキャラクターのステータス構造体を作成し、複数のキャラを初期化せよ。

### 演習 2.5.5.3
UEスタイルのFCharacterStats構造体を作成し、指定初期化子で初期化せよ。

## ビルド方法

```bash
# cpp20/exercises/09-designated-initializers/ ディレクトリで
mkdir build && cd build
cmake ..
make

# 実行
./example
./exercise
./solution
```

## 参考リンク

- [cppreference - Designated initializers](https://en.cppreference.com/w/cpp/language/aggregate_initialization#Designated_initializers)
- [modern-cpp-curriculum.md セクション 2.5.5](../../../docs/modern-cpp-curriculum.md)
- [unreal-engine-cpp20-guide.md セクション 5](../../../docs/unreal-engine-cpp20-guide.md)

## Unreal Engine 5.7での使用例

```cpp
// UE 5.7でのFCharacterStats初期化
USTRUCT(BlueprintType)
struct FCharacterStats {
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "Stats")
    float Health = 100.0f;

    UPROPERTY(BlueprintReadWrite, Category = "Stats")
    float Stamina = 100.0f;

    UPROPERTY(BlueprintReadWrite, Category = "Stats")
    float Mana = 50.0f;
};

// 指定初期化子で初期化（UE 5.7推奨）
FCharacterStats WarriorStats = {
    .Health = 150.0f,
    .Stamina = 120.0f,
    .Mana = 30.0f
};
```

## 重要な注意点

### C++20の制約

1. **順序制約**: メンバは定義順に指定する必要がある
   ```cpp
   struct Point { int x, y; };

   // OK
   Point p1 = {.x = 1, .y = 2};

   // エラー（順序が逆）
   Point p2 = {.y = 2, .x = 1};  // コンパイルエラー
   ```

2. **省略可能**: 指定しなかったメンバはデフォルト値または0初期化される
   ```cpp
   Point p3 = {.x = 1};  // y = 0
   ```

3. **配列や継承には使えない**

## 次のステップ

この演習を完了したら：
1. C++20 Phase 2の全演習が完了です！
2. 実際のUEプロジェクトで使ってみましょう
