# 1.7 std::optional

## 概要

C++17で導入された`std::optional`は、値が存在するかしないかを表現できる型です。

**Rustとの比較**: `Option<T>` に相当します。

```rust
// Rust
fn find_value(vec: &Vec<i32>, target: i32) -> Option<i32> {
    vec.iter().find(|&&x| x == target).copied()
}
```

```cpp
// C++17
std::optional<int> find_value(const std::vector<int>& v, int target) {
    for (int x : v) {
        if (x == target) return x;
    }
    return std::nullopt;  // Rustの None
}
```

## 学習内容

1. **基本的な使い方**
   - std::nulloptの使用
   - has_value()で存在確認
   - value()とoperator*で値を取得
   - value_or()でデフォルト値を指定

2. **実用例**
   - 検索関数の戻り値
   - 設定ファイルのパーサー
   - エラーハンドリング

3. **注意点**
   - value()は例外を投げる可能性がある
   - operator*は値が存在しない場合は未定義動作

## ファイル

- **example.cpp**: 写経用の完全なサンプルコード
- **exercise.cpp**: 演習問題（TODOを埋める）
- **solution.cpp**: 解答例

## 演習課題

### 演習 1.7.1
設定ファイルのパーサーを作れ。キーが存在しない場合は`std::nullopt`を返すこと。

## ビルド方法

```bash
mkdir build && cd build
cmake ..
make
./example
```

## 参考リンク

- [cppreference - std::optional](https://en.cppreference.com/w/cpp/utility/optional)
- [modern-cpp-curriculum.md セクション 1.7](../../../docs/modern-cpp-curriculum.md)
