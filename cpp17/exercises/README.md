# Phase 1: C++17演習

このディレクトリには、C++17の主要機能を学習するための10個の演習が含まれています。

## 演習一覧

| # | トピック | 優先度 | ファイル |
|---|---------|--------|---------|
| 01 | 構造化束縛（Structured Bindings） | 高 | [01-structured-bindings/](01-structured-bindings/) |
| 02 | if/switch初期化式 | 高 | [02-if-init/](02-if-init/) |
| 03 | クラステンプレート引数推論（CTAD） | 中 | [03-ctad/](03-ctad/) |
| 04 | constexpr if | 高 | [04-constexpr-if/](04-constexpr-if/) |
| 05 | fold expressions | 中 | [05-fold-expressions/](05-fold-expressions/) |
| 06 | 属性（Attributes） | 低 | [06-attributes/](06-attributes/) |
| 07 | std::optional | 高 | [07-optional/](07-optional/) |
| 08 | std::variant | 高 | [08-variant/](08-variant/) |
| 09 | std::string_view | 高 | [09-string-view/](09-string-view/) |
| 10 | std::filesystem | 高 | [10-filesystem/](10-filesystem/) |

## 学習方法

### 1. 写経フェーズ
```bash
cd 01-structured-bindings
mkdir build && cd build
cmake ..
make
./example  # サンプルコードを実行して動作を確認
```

`example.cpp`を見ながら、C++17の機能を理解します。

### 2. 演習フェーズ
```bash
./exercise  # TODOを埋める前の状態を確認
```

`exercise.cpp`のTODOコメントを埋めて、自分で実装します。

### 3. 答え合わせフェーズ
```bash
./solution  # 解答例を実行
```

自分の実装と`solution.cpp`を比較します。

## 全演習を一括ビルド

```bash
# cpp17/ ディレクトリで
mkdir build && cd build
cmake ..
make

# 特定の演習を実行
./exercises/01-structured-bindings/example
./exercises/02-if-init/exercise
```

## 推奨学習順序

1. **必須（優先度：高）**
   - 01, 02, 04, 07, 08, 09, 10

2. **推奨（優先度：中）**
   - 03, 05

3. **余裕があれば（優先度：低）**
   - 06

## 各演習の構成

各演習ディレクトリには以下のファイルが含まれています：

- **README.md**: 詳細な説明、Rustとの比較、参考リンク
- **example.cpp**: 写経用の完全なサンプルコード
- **exercise.cpp**: 演習用（TODOを埋める）
- **solution.cpp**: 解答例
- **CMakeLists.txt**: ビルド設定

## トラブルシューティング

### コンパイラがC++17をサポートしていない

```bash
# GCC
g++ --version  # 7.0以上が必要

# Clang
clang++ --version  # 5.0以上が必要

# MSVC
# Visual Studio 2017以上が必要
```

### ビルドエラーが発生する

```bash
# ビルドディレクトリをクリーン
rm -rf build
mkdir build && cd build
cmake ..
make VERBOSE=1  # 詳細なビルドログを表示
```

## 次のステップ

Phase 1を完了したら：

1. GitHubのIssue #1〜#11をクローズ
2. [Phase 2: C++20](../../cpp20/exercises/)へ進む
3. 総合課題: [ミニアセットマネージャー](../projects/asset-manager/)に挑戦

## 参考資料

- [modern-cpp-curriculum.md](../../docs/modern-cpp-curriculum.md)
- [cppreference - C++17](https://en.cppreference.com/w/cpp/17)
- [C++17 Features](https://github.com/AnthonyCalandra/modern-cpp-features#cpp17)
