# 2.1 コンセプト（Concepts）

## 概要

C++20で導入されたコンセプトは、テンプレート引数に制約を設けることができる機能です。

**Rustとの比較**: トレイト境界（trait bounds）に相当します。

```rust
// Rust
fn double<T: std::ops::Add<Output = T>>(x: T) -> T {
    x + x
}
```

```cpp
// C++20
template<std::integral T>
T double_value(T x) {
    return x * 2;
}
```

**UE 5.7での重要度**: ★★★★★（最優先）

## 学習内容

1. **基本的なrequires節**
   - テンプレート制約の基本
   - 標準コンセプトの使用

2. **標準コンセプト**
   - `std::integral`, `std::floating_point`
   - `std::copyable`, `std::movable`
   - `std::invocable`, `std::predicate`

3. **自作コンセプト**
   - requires式の書き方
   - 複合要件
   - ネストした要件

4. **UE 5.7での応用**
   - Actor型の制約
   - ジェネリックな数値処理
   - 型安全なオブジェクトプール

## ファイル

- **example.cpp**: 完全なサンプルコード
- **exercise.cpp**: 演習問題（TODOを埋める）
- **solution.cpp**: 解答例

## 演習課題

### 演習 2.1.1: Hashable コンセプト
`std::hash<T>`が使用可能な型を制約する`Hashable`コンセプトを作成せよ。

### 演習 2.1.2: Serializable コンセプト
`serialize()`と`deserialize()`メソッドを持つ型を制約する`Serializable`コンセプトを作成せよ。

### 演習 2.1.3: GameEntity コンセプト
ゲーム開発用の`GameEntity`コンセプトを設計せよ。以下の要件を満たすこと：
- `update(float delta_time)`メソッドを持つ
- `render()`メソッドを持つ
- `get_position()`メソッドで座標（x, y, z）を返す
- ムーブ可能である

## ビルド方法

```bash
# cpp20/exercises/01-concepts/ ディレクトリで
mkdir build && cd build
cmake ..
make

# 実行
./example
./exercise
./solution
```

## 参考リンク

- [cppreference - Concepts](https://en.cppreference.com/w/cpp/concepts)
- [modern-cpp-curriculum.md セクション 2.1](../../../docs/modern-cpp-curriculum.md)
- [unreal-engine-cpp20-guide.md](../../../docs/unreal-engine-cpp20-guide.md)

## 次のステップ

この演習を完了したら：
1. 次の演習: [02-ranges](../02-ranges/)
