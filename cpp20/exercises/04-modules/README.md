# 2.4 モジュール（Modules）

## 概要

C++20で導入されたモジュールは、従来の`#include`に代わる新しいコード組織化の仕組みです。

**Rustとの比較**: `mod`/`use`システムに相当します。

```rust
// Rust
mod math {
    pub fn add(a: i32, b: i32) -> i32 {
        a + b
    }
}

use math::add;
```

```cpp
// C++20
export module math;

export int add(int a, int b) {
    return a + b;
}

// 別ファイル
import math;
```

**UE 5.7での重要度**: ★☆☆☆☆（実験的 - UnrealBuildToolとの互換性不明）

## 重要な注意事項

**モジュールは実験的機能です**:
- コンパイラサポートが限定的（GCC 11+, Clang 15+, MSVC 2019+）
- ビルドシステム（CMake）のサポートも発展途上
- UEのUnrealBuildToolとの互換性は未確認
- **学習目的のみ推奨 - 本番コードでは使用しないこと**

## 学習内容

1. **基本的なモジュール構文**
   - `export module`でモジュール定義
   - `import`でモジュールを使用
   - `export`で公開

2. **モジュールの利点**
   - コンパイル時間の短縮
   - マクロ汚染の防止
   - 依存関係の明確化

3. **制限事項**
   - ビルドシステムのサポート不足
   - ヘッダーユニットとの混在
   - UEとの互換性不明

## ファイル

- **README.md**: このファイル（詳細な説明）
- **example.cpp**: 簡単なモジュール使用例（ヘッダーベースの模擬実装）
- **exercise.cpp**: 演習問題
- **solution.cpp**: 解答例

## 演習課題

**注意**: この演習は概念理解のためのものです。実際のモジュールを使うには
コンパイラとビルドシステムの追加設定が必要です。

### 演習 2.4.1: 数学ライブラリモジュール（概念）
`export module math;`を使って、基本的な数学関数を提供するモジュールを設計せよ。

### 演習 2.4.2: モジュールインターフェース（概念）
公開する関数と非公開の実装を分離する設計を理解せよ。

## ビルド方法

```bash
# 注意: モジュールは標準的なビルド方法では動作しません
# 以下はヘッダーベースの代替実装を使った例です

mkdir build && cd build
cmake ..
make

# 実行
./example
./exercise
./solution
```

## モジュールの将来性

- **C++23以降**: より成熟した仕様
- **ビルドシステム**: CMake 3.28+で改善
- **UE対応**: 将来的には対応予定の可能性あり

## 学習方針

1. **現時点**: 概念を理解する（`export`, `import`の意味）
2. **将来**: コンパイラとビルドツールが成熟してから本格採用
3. **UE開発**: 従来の`#include`ベースを継続

## 参考リンク

- [cppreference - Modules](https://en.cppreference.com/w/cpp/language/modules)
- [modern-cpp-curriculum.md セクション 2.4](../../../docs/modern-cpp-curriculum.md)
- [GCC Modules Documentation](https://gcc.gnu.org/wiki/cxx-modules)

## 次のステップ

この演習を完了したら：
1. 次の演習: [05-span](../05-span/)
