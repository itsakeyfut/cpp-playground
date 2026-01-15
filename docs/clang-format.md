# .clang-format について

## .clang-format とは

`.clang-format`は、C/C++のコードフォーマッターである**clang-format**の設定ファイルです。プロジェクトのルートディレクトリに配置することで、コードスタイルを統一的に管理できます。

clang-formatは、LLVMプロジェクトの一部として開発されたツールで、C/C++/Objective-C/JavaScriptなどのコードを自動的に整形します。

## なぜ使うのか

### メリット

1. **コードスタイルの統一**: チーム全体で一貫したコーディングスタイルを維持できる
2. **レビューの効率化**: フォーマットの議論を減らし、ロジックに集中できる
3. **自動化**: エディタやCIパイプラインと統合して自動フォーマットが可能
4. **可読性向上**: 統一されたスタイルでコードが読みやすくなる
5. **安全性の基盤**: 一貫したスタイルは、Clang-Tidyなどの静的解析ツールと組み合わせることで、より安全なコードベースを構築できる

## 基本的な使い方

### コマンドライン

```bash
# ファイルを整形（変更を表示するのみ）
clang-format file.cpp

# ファイルを整形して上書き
clang-format -i file.cpp

# ディレクトリ内のすべてのファイルを整形
find src -name "*.cpp" -o -name "*.h" | xargs clang-format -i

# Gitで変更されたファイルのみ整形
git diff --name-only --diff-filter=ACM | grep '\.\(cpp\|h\)$' | xargs clang-format -i
```

### エディタ統合

多くのエディタ（VSCode, Vim, Emacsなど）がclang-formatに対応しており、保存時に自動フォーマットすることができます。

**VSCode**: C/C++拡張をインストール後、設定で`"editor.formatOnSave": true`を有効化

**Vim/Neovim**: clang-format.pyスクリプトを使用、またはプラグイン経由

## 主要なベーススタイル

clang-formatには以下の主要なプリセットがあります：

| スタイル | 特徴 | インデント | ポインタ配置 | 行長 |
|---------|------|-----------|------------|------|
| **LLVM** | LLVMプロジェクト標準 | 2スペース | 右寄せ | 80 |
| **Google** | Googleスタイルガイド準拠 | 2スペース | 左寄せ | 80 |
| **Chromium** | Chromiumプロジェクト | 2スペース | 左寄せ | 80 |
| **Mozilla** | Mozillaプロジェクト | 2スペース | 左寄せ | 80 |
| **WebKit** | WebKitプロジェクト | 4スペース | 左寄せ | - |
| **Microsoft** | Microsoftスタイル | 4スペース | 左寄せ | 120 |

## このプロジェクトの選択: Google スタイル

このプロジェクト（cpp-playground）では**Googleスタイル**をベースにしています。

### Googleスタイルを選んだ理由

1. **厳格で詳細**: [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)は最も詳細で厳格
2. **安全性重視**: 大規模プロジェクトでの安全性とレビュー可能性を重視した設計
3. **業界標準**: 多くの企業やオープンソースプロジェクトで採用
4. **Clang-Tidyとの相性**: `google-*`チェックと完全に統合可能
5. **一貫性の徹底**: 曖昧さを排除した明確なルール

### カスタマイズ内容

Googleスタイルをベースに、以下のカスタマイズを適用しています：

```yaml
# ベース設定
BasedOnStyle: Google
Standard: c++20

# インデント: 4スペース（Googleのデフォルトは2）
IndentWidth: 4
# 理由: 可読性向上、特にネストが深い場合

# 行の長さ: 100文字（Googleのデフォルトは80）
ColumnLimit: 100
# 理由: 現代のモニター環境に適応

# 短い関数: 禁止（GoogleのデフォルトはInline）
AllowShortFunctionsOnASingleLine: None
# 理由: より厳格に、一貫性を重視
```

## Googleスタイルの主な特徴

### 1. ポインタと参照の配置（左寄せ）

```cpp
// Google スタイル（このプロジェクト）
int* pointer;
int& reference;
const std::string& param;

// LLVMスタイル（使わない）
int *pointer;
int &reference;
```

**理由**: 型の一部として扱う。`int*`は「intへのポインタ型」という解釈。

**注意**: 複数宣言時の落とし穴を避けるため、1行1宣言を推奨
```cpp
// 危険（避けるべき）
int* a, b;  // bはポインタではない！

// 安全（推奨）
int* a;
int* b;
```

### 2. 波括弧のスタイル（K&R/Attach）

```cpp
// Google スタイル
class MyClass {
    void Method() {
        if (condition) {
            DoSomething();
        }
    }
};

// Allman スタイル（使わない）
class MyClass
{
    void Method()
    {
        if (condition)
        {
            DoSomething();
        }
    }
};
```

### 3. 短い構文の扱い（厳格）

このプロジェクトでは、Googleのデフォルトよりも厳格に設定しています：

```cpp
// × 禁止: 短いif文を1行に
if (condition) return true;

// ○ 正しい: 常に波括弧とブロック
if (condition) {
    return true;
}

// × 禁止: 短い関数を1行に（Googleデフォルトではインライン関数はOK）
inline int GetValue() { return value_; }

// ○ 正しい: 常に複数行
inline int GetValue() {
    return value_;
}

// ○ 例外: ラムダ式は1行可
auto lambda = [](int x) { return x * 2; };
```

### 4. インクルードの並び順

Googleスタイルでは、厳格なインクルード順序を定めています：

```cpp
// 1. 関連ヘッダー（.cppファイルの場合、対応する.h）
#include "my_class.h"

// 2. C標準ライブラリ
#include <stdio.h>
#include <stdlib.h>

// 3. C++標準ライブラリ
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// 4. その他のライブラリ
#include <boost/algorithm/string.hpp>
#include <gtest/gtest.h>
```

各グループ内はアルファベット順に自動ソートされます。

### 5. 関数パラメータの折り返し

```cpp
// Google スタイル: 見やすく、レビューしやすい
void LongFunctionName(
    const std::string& param1,
    const std::vector<int>& param2,
    std::unique_ptr<Handler> handler);

// すべてのパラメータが見やすく、git diffでも変更が明確
```

### 6. コンストラクタ初期化子リスト

```cpp
// Google スタイル
Constructor()
    : member1_(value1), member2_(value2), member3_(value3) {
    // コンストラクタ本体
}

// 長い場合は改行
Constructor()
    : member1_(value1),
      member2_(value2),
      member3_(value3),
      member4_(value4) {
    // コンストラクタ本体
}
```

### 7. アクセス指定子のインデント

```cpp
class MyClass {
public:  // 1段階戻す（AccessModifierOffset: -1）
    MyClass();
    void PublicMethod();

private:
    int private_member_;
    void PrivateMethod();
};
```

### 8. 名前空間

```cpp
namespace my_namespace {

// インデントなし（NamespaceIndentation: None）
class MyClass {
    // ...
};

void Function() {
    // ...
}

}  // namespace my_namespace  ← 自動コメント追加
```

## LLVMスタイルとの比較

### 主な違い

| 項目 | LLVM | Google（このプロジェクト） |
|------|------|------------|
| **インデント** | 2スペース | 4スペース（カスタム） |
| **ポインタ配置** | `int *ptr` | `int* ptr` |
| **行の長さ** | 80文字 | 100文字（カスタム） |
| **短い関数** | All（すべて1行可） | None（すべて複数行） |
| **スタイルガイド** | 比較的柔軟 | 非常に厳格 |

### コード例の比較

```cpp
// ===== LLVM スタイル =====
class Calculator {
public:
  int add(int a, int b) { return a + b; }  // 1行OK

  void process(std::vector<int> &data) {  // 参照が右寄せ
    for (int i = 0; i < data.size(); i++) {
      // ...
    }
  }
};

// ===== Google スタイル（このプロジェクト） =====
class Calculator {
public:
    int Add(int a, int b) {  // 必ず複数行、関数名はCamelCase
        return a + b;
    }

    void Process(std::vector<int>& data) {  // 参照が左寄せ
        for (int i = 0; i < data.size(); i++) {
            // ...
        }
    }

private:
    int result_;  // メンバ変数は末尾にアンダースコア
};
```

## フォーマットの確認と適用

### 差分を確認

```bash
# フォーマット後の差分を表示
clang-format -style=file main.cpp | diff main.cpp -
```

### プロジェクト全体を整形

```bash
# 全ファイルを整形
find . -name "*.cpp" -o -name "*.h" | xargs clang-format -i

# または、Gitで管理されているファイルのみ
git ls-files '*.cpp' '*.h' | xargs clang-format -i
```

### CI/CDでのフォーマットチェック

```bash
# フォーマットが正しいかチェック（差分があればエラー）
find src -name "*.cpp" -o -name "*.h" | \
  xargs clang-format --dry-run -Werror

# 終了コード0: フォーマットOK
# 終了コード1: フォーマット違反あり
```

## Clang-Tidyとの連携

このプロジェクトでは、clang-formatとclang-tidyを組み合わせて使用します：

```bash
# 1. フォーマット（スタイル統一）
clang-format -i src/*.cpp

# 2. 静的解析（バグ検出）
clang-tidy src/*.cpp
```

- **clang-format**: コードの**見た目**を整える（インデント、空白、改行など）
- **clang-tidy**: コードの**品質**を向上させる（バグ、パフォーマンス、安全性）

詳細は[docs/clang-tidy.md](clang-tidy.md)を参照してください。

## エディタ設定例

### VSCode (.vscode/settings.json)

```json
{
  "editor.formatOnSave": true,
  "C_Cpp.clang_format_style": "file",
  "C_Cpp.codeAnalysis.clangTidy.enabled": true,
  "C_Cpp.codeAnalysis.clangTidy.path": "clang-tidy"
}
```

### .editorconfig（補助的に使用）

```ini
[*.{cpp,h}]
charset = utf-8
end_of_line = lf
insert_final_newline = true
trim_trailing_whitespace = true
```

## よくある質問

### Q: なぜインデント4スペースなのですか？

A: Googleのデフォルトは2スペースですが、このプロジェクトでは可読性を優先して4スペースに設定しています。特にネストが深い場合や、モダンC++の機能（ラムダ、テンプレートなど）を使う際に見やすくなります。

### Q: 既存のコードを一度に全部フォーマットすべきですか？

A: 大規模な変更になる場合は、以下のアプローチを推奨します：
1. 新規ファイルは必ずフォーマット済みで作成
2. 編集するファイルは編集時にフォーマット
3. 時間をかけて段階的に移行

一度にすべて変更すると、git blameが見づらくなる問題があります。

### Q: Googleスタイルは厳しすぎませんか？

A: 安全性と一貫性を重視するなら、厳格なルールはメリットです。特に：
- 大規模プロジェクトでの混乱を防ぐ
- コードレビューが効率的になる
- 新しいメンバーが参加しやすい
- バグの混入を減らせる

### Q: LLVMスタイルに変更できますか？

A: はい、`.clang-format`の`BasedOnStyle: Google`を`BasedOnStyle: LLVM`に変更するだけです。ただし、プロジェクト全体で統一することが重要です。

## まとめ

このプロジェクトでは：

1. **Googleスタイル**をベースにした厳格なフォーマット
2. **インデント4スペース**で可読性を向上
3. **行長100文字**で現代的な環境に対応
4. **短い構文を禁止**してより一貫性のあるコード
5. **Clang-Tidyと連携**して安全性を確保

これらの設定により、読みやすく、保守しやすく、安全なC++コードベースを構築できます。

## References

- [Clang-Format Style Options（公式ドキュメント）](https://clang.llvm.org/docs/ClangFormatStyleOptions.html)
- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
- [LLVM Coding Standards](https://llvm.org/docs/CodingStandards.html)
- [【完全ガイド】clang-format でコードスタイルを完璧に統一する 7 つの実践テクニック](https://dexall.co.jp/articles/?p=1706)
- [clang-format の導入手順と使い方](https://zenn.dev/masaki_wk/articles/20220911-clang-format)
