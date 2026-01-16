# 1.2 if/switch初期化式

## 概要

C++17では、if文とswitch文に初期化式を書けるようになりました。これにより、変数のスコープを制限でき、コードが読みやすくなります。

**Rustとの比較**: `if let` に近い用途です。

```rust
// Rust
if let Some(value) = map.get(&key) {
    // use value
}
```

```cpp
// C++17
if (auto it = map.find(key); it != map.end()) {
    // use it
}
```

## 学習内容

1. **if初期化式**
   - 基本構文
   - スコープの制限
   - 従来の方法との比較

2. **switch初期化式**
   - 基本構文
   - 実用例

3. **実用パターン**
   - マップからの検索
   - ロックガードとの組み合わせ
   - オプション値の扱い

## ファイル

- **example.cpp**: 写経用の完全なサンプルコード
- **exercise.cpp**: 演習問題（TODOを埋める）
- **solution.cpp**: 解答例

## 演習課題

### 演習 1.2.1
キャッシュ（`std::unordered_map`）からデータを取得し、なければ計算して格納するコードをif初期化式で書け。

## ビルド方法

```bash
mkdir build && cd build
cmake ..
make
./example
```

## 参考リンク

- [cppreference - if statement](https://en.cppreference.com/w/cpp/language/if)
- [modern-cpp-curriculum.md セクション 1.2](../../../docs/modern-cpp-curriculum.md)
