# 2.3 コルーチン（Coroutines）

## 概要

C++20で導入されたコルーチンは、関数の実行を中断・再開できる機能です。

**Rustとの比較**: `async/await`に近いですが、C++のコルーチンはより低レベルで汎用的です。

```rust
// Rust (async/await)
async fn fetch_data() -> Result<Data, Error> {
    let response = http_client.get(url).await?;
    Ok(response.json().await?)
}
```

```cpp
// C++20 (コルーチン)
Generator<int> fibonacci() {
    int a = 0, b = 1;
    while (true) {
        co_yield a;
        auto tmp = a;
        a = b;
        b = tmp + b;
    }
}
```

**UE 5.7での重要度**: ★★★★☆（重要だが高度）

## 学習内容

1. **基本的なコルーチンキーワード**
   - `co_yield`: 値を生成して中断
   - `co_await`: 非同期操作の待機
   - `co_return`: コルーチンを終了

2. **ジェネレータの実装**
   - promise_typeの定義
   - コルーチンハンドル
   - イテレータインターフェース

3. **実用例**
   - フィボナッチ数列ジェネレータ
   - ファイル行読み込みジェネレータ
   - 遅延評価シーケンス

4. **UE 5.7での応用**
   - 非同期リソースローダー
   - フレーム分散処理
   - シーケンス実行

## ファイル

- **example.cpp**: 完全なサンプルコード
- **exercise.cpp**: 演習問題（TODOを埋める）
- **solution.cpp**: 解答例

## 演習課題

### 演習 2.3.1: フィボナッチ数列ジェネレータ
フィボナッチ数列を生成するジェネレータを実装せよ。

要件:
- `Generator<int>`型を使用
- `co_yield`で値を生成
- 無限に生成可能

### 演習 2.3.2: ファイル行読み込みジェネレータ
ファイルを1行ずつ読み込むジェネレータを実装せよ。

要件:
- `Generator<std::string>`型を使用
- ファイルをオープンしてから1行ずつyield
- ファイル終端で終了

## ビルド方法

```bash
# cpp20/exercises/03-coroutines/ ディレクトリで
mkdir build && cd build
cmake ..
make

# 実行
./example
./exercise
./solution
```

## 注意事項

コルーチンは実装が複雑です。まずは提供されたGenerator実装を理解し、
使い方に慣れてから、カスタムコルーチンの実装に挑戦してください。

## 参考リンク

- [cppreference - Coroutines](https://en.cppreference.com/w/cpp/language/coroutines)
- [modern-cpp-curriculum.md セクション 2.3](../../../docs/modern-cpp-curriculum.md)
- [unreal-engine-cpp20-guide.md](../../../docs/unreal-engine-cpp20-guide.md)

## 次のステップ

この演習を完了したら：
1. 次の演習: [04-modules](../04-modules/)
