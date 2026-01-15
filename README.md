# cpp-playground

モダン C++（C++17〜C++26）の学習リポジトリ。

## 目的

- **Unreal Engine 5.7** でのゲーム開発に向けたモダン C++の習得
- 各 C++標準の新機能を実際にコードを書いて理解する
- 学習の記録を残し、後から参照できるようにする

### Unreal Engine 5.7 互換性

- UE 5.7 は **C++20** をデフォルト・最小要件として使用
- このプロジェクトのデフォルトC++標準は **C++20** に設定
- C++23/C++26 は学習目的で利用可能（UE本番コードでは使用不可）

## ディレクトリ構成

```
cpp-playground/
├── docs/                    # カリキュラム・ドキュメント
├── cpp17/                   # C++17 演習・プロジェクト
├── cpp20/                   # C++20 演習・プロジェクト
├── cpp23/                   # C++23 演習・プロジェクト
├── cpp26/                   # C++26 実験（提案段階の機能）
├── cross_cutting/           # 横断トピック（テンプレート、並行性、DOD）
├── sandbox/                 # 一時的な実験用
└── libs/                    # 共通ユーティリティ
```

## 必要環境

- **コンパイラ**: Clang 20+ / GCC 14+ / MSVC 19.39+（C++23完全サポート）
  - 現在の環境: Clang 20.1.6 ✅
- **CMake**: 3.20以上、4.0推奨
  - 現在の環境: CMake 4.0.3 ✅
- **ビルドツール**: Ninja（推奨）または Make

## ビルド方法

### 基本ビルド

```bash
# 全体ビルド
cmake -B build
cmake --build build

# 特定のバージョンのみビルド
cmake -B build -DBUILD_CPP23=OFF -DBUILD_CPP26=OFF
cmake --build build
```

### 厳格モード（推奨）

コード品質と安全性を重視する場合：

```bash
# Clang-Tidy静的解析を有効化
cmake -B build -DENABLE_CLANG_TIDY=ON
cmake --build build

# 警告をエラーとして扱う（厳格モード）
cmake -B build -DENABLE_WARNINGS_AS_ERRORS=ON
cmake --build build

# サニタイザーを有効化（デバッグ時）
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DENABLE_SANITIZERS=ON
cmake --build build
```

詳細は以下のドキュメントを参照：
- **[Unreal Engine 5.7向けC++20学習ガイド](docs/unreal-engine-cpp20-guide.md)** ⭐ 必読
- [clang-formatについて](docs/clang-format.md)
- [clang-tidyについて](docs/clang-tidy.md)
- [コンパイラサポート状況](docs/cpp-compiler-support.md)

## C++標準の指定

各演習は適切な C++標準でビルドされます：

| ディレクトリ | C++標準 | コンパイルオプション | UE 5.7互換性 | 備考 |
| ------------ | ------- | -------------------- | ------------ | ---- |
| cpp17/       | C++17   | `-std=c++17`         | ⚠️ 非推奨 | UE 5.6以前 |
| cpp20/       | C++20   | `-std=c++20`         | ✅ **必須** | **UE 5.7デフォルト** |
| cpp23/       | C++23   | `-std=c++23`         | ❌ 未サポート | 学習用のみ |
| cpp26/       | C++26   | `-std=c++26`         | ❌ 未サポート | 学習用・実験的 |

**重要**: Unreal Engine 5.7との互換性を考慮し、プロジェクトのデフォルトC++標準は**C++20**に設定されています。
