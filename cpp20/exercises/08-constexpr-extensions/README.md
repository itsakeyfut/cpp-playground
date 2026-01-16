# 2.5.4 constexpr拡張とconsteval

## 概要

C++20では、constexpr機能が大幅に拡張され、仮想関数や動的メモリ確保もコンパイル時に実行可能になりました。さらに、必ずコンパイル時に評価されることを保証する`consteval`と、静的初期化を保証する`constinit`が追加されました。

**Rustとの比較**: Rustの`const fn`に近い機能ですが、C++20の方が柔軟性が高いです。

```rust
// Rust
const fn square(x: i32) -> i32 {
    x * x
}
```

```cpp
// C++20
constexpr int square(int x) {
    return x * x;
}
```

**Unreal Engineとの関連**: ゲーム開発ではコンパイル時計算が重要です（テーブル生成、最適化等）。

## 学習内容

1. **constexpr仮想関数**
   - C++20で可能になった仮想関数のconstexpr化
   - コンパイル時の多態性

2. **consteval（即時関数）**
   - 必ずコンパイル時に評価される関数
   - ランタイムでの使用は禁止

3. **constinit（静的初期化）**
   - 静的変数の初期化順序問題を解決
   - 定数式での初期化を強制

4. **ゲーム開発での応用**
   - ルックアップテーブルの生成
   - コンパイル時ハッシュ計算
   - メタプログラミング

## ファイル

- **example.cpp**: 写経用の完全なサンプルコード
- **exercise.cpp**: 演習問題（TODOを埋める）
- **solution.cpp**: 解答例

## 演習課題

### 演習 2.5.4.1
constexpr仮想関数を使って、コンパイル時に図形の面積を計算せよ。

### 演習 2.5.4.2
constevalを使って、コンパイル時にフィボナッチ数を計算する関数を作成せよ。

### 演習 2.5.4.3
ゲーム用のダメージ計算テーブルをconstexprで生成せよ。

## ビルド方法

```bash
# cpp20/exercises/08-constexpr-extensions/ ディレクトリで
mkdir build && cd build
cmake ..
make

# 実行
./example
./exercise
./solution
```

## 参考リンク

- [cppreference - constexpr](https://en.cppreference.com/w/cpp/language/constexpr)
- [cppreference - consteval](https://en.cppreference.com/w/cpp/language/consteval)
- [cppreference - constinit](https://en.cppreference.com/w/cpp/language/constinit)
- [modern-cpp-curriculum.md セクション 2.5.4](../../../docs/modern-cpp-curriculum.md)
- [unreal-engine-cpp20-guide.md セクション 7](../../../docs/unreal-engine-cpp20-guide.md)

## ゲーム開発での応用例

```cpp
// ダメージ計算テーブルをコンパイル時に生成
constexpr auto GenerateDamageTable() {
    std::array<int, 100> table{};
    for (int level = 0; level < 100; ++level) {
        table[level] = 10 + level * 5;  // 基礎ダメージ + レベル補正
    }
    return table;
}

// コンパイル時に計算済み
constexpr auto DamageTable = GenerateDamageTable();

// ランタイムでは配列参照のみ（計算なし）
int GetDamage(int level) {
    return DamageTable[level];
}
```

## 次のステップ

この演習を完了したら：
1. 次の演習: [09-designated-initializers](../09-designated-initializers/)
