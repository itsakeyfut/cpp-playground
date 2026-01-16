# 1.8 std::variant

## 概要

C++17で導入された`std::variant`は、型安全なユニオン（複数の型のうち1つを保持できる型）です。

**Rustとの比較**: `enum`（タグ付きユニオン）に相当します。

```rust
// Rust
enum Value {
    Int(i32),
    Float(f64),
    String(String),
}
```

```cpp
// C++17
using Value = std::variant<int, double, std::string>;
```

## 学習内容

1. **基本的な使い方**
   - variantの宣言と初期化
   - std::get<T>で値を取得
   - std::holds_alternativeで型を確認
   - std::visitでパターンマッチング

2. **実用例**
   - ゲームイベントシステム
   - パーサーの戻り値
   - 状態マシン

3. **高度なテクニック**
   - overloadedパターン
   - ラムダを使った訪問

## ファイル

- **example.cpp**: 写経用の完全なサンプルコード
- **exercise.cpp**: 演習問題（TODOを埋める）
- **solution.cpp**: 解答例

## 演習課題

### 演習 1.8.1
ゲームイベント（`PlayerMoved{x,y}`, `ItemPickedUp{item_id}`, `DamageTaken{amount}`）を`std::variant`で表現し、イベントハンドラを実装せよ。

## ビルド方法

```bash
mkdir build && cd build
cmake ..
make
./example
```

## 参考リンク

- [cppreference - std::variant](https://en.cppreference.com/w/cpp/utility/variant)
- [modern-cpp-curriculum.md セクション 1.8](../../../docs/modern-cpp-curriculum.md)
