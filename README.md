# C++ Playground

C++の学習リポジトリです。
以下は構想しているディレクトリ構成です：

```
cpp-playground/
├── README.md                    # リポジトリ概要
├── PROGRESS.md                  # 学習進捗管理
├── docs/
│   └── modern-cpp-curriculum.md # カリキュラム本体
│
├── CMakeLists.txt               # ルートCMake（全体ビルド用）
├── .clang-format                # コードスタイル統一
├── .gitignore
│
├── cpp17/                       # Phase 1
│   ├── CMakeLists.txt
│   ├── exercises/               # 小演習
│   │   ├── 01_structured_bindings/
│   │   │   ├── CMakeLists.txt
│   │   │   ├── main.cpp
│   │   │   └── README.md        # 課題説明・学んだこと
│   │   ├── 02_if_init/
│   │   ├── 03_ctad/
│   │   ├── 04_constexpr_if/
│   │   ├── 05_fold_expressions/
│   │   ├── 06_optional/
│   │   ├── 07_variant/
│   │   ├── 08_string_view/
│   │   ├── 09_filesystem/
│   │   └── 10_parallel_algorithms/
│   └── projects/                # 総合課題
│       └── asset_manager/
│           ├── CMakeLists.txt
│           ├── src/
│           ├── include/
│           └── README.md
│
├── cpp20/                       # Phase 2
│   ├── CMakeLists.txt
│   ├── exercises/
│   │   ├── 01_concepts_basic/
│   │   ├── 02_concepts_custom/
│   │   ├── 03_ranges_basic/
│   │   ├── 04_ranges_views/
│   │   ├── 05_coroutines_generator/
│   │   ├── 06_coroutines_async/
│   │   ├── 07_modules/
│   │   ├── 08_span/
│   │   ├── 09_format/
│   │   ├── 10_spaceship/
│   │   └── 11_jthread/
│   └── projects/
│       ├── event_system/
│       ├── data_pipeline/
│       └── async_loader/
│
├── cpp23/                       # Phase 3
│   ├── CMakeLists.txt
│   ├── exercises/
│   │   ├── 01_expected/
│   │   ├── 02_mdspan/
│   │   ├── 03_generator/
│   │   ├── 04_print/
│   │   ├── 05_deducing_this/
│   │   ├── 06_flat_containers/
│   │   └── 07_ranges_extended/
│   └── projects/
│       ├── config_parser/
│       └── image_processing/
│
├── cpp26/                       # Phase 4（実験的）
│   ├── CMakeLists.txt
│   ├── experiments/             # 提案段階の機能実験
│   │   ├── reflection/
│   │   ├── contracts/
│   │   └── pattern_matching/
│   └── notes/                   # 調査メモ
│
├── cross_cutting/               # 横断トピック
│   ├── CMakeLists.txt
│   ├── template_metaprogramming/
│   ├── memory_model/
│   ├── data_oriented_design/
│   └── benchmarks/              # パフォーマンス比較
│
├── sandbox/                     # 一時的な実験用
│   ├── CMakeLists.txt
│   └── scratch.cpp              # 気軽に試すファイル
│
└── libs/                        # 共通ユーティリティ（必要に応じて）
    ├── CMakeLists.txt
    └── include/
        └── playground/
            └── common.hpp
```

## 設計意図

| ディレクトリ     | 役割                                               |
| ---------------- | -------------------------------------------------- |
| `exercises/`     | 各トピックの小さな演習。1 ファイル〜数ファイル程度 |
| `projects/`      | 複数トピックを組み合わせた総合課題                 |
| `sandbox/`       | 気軽に試す場所。コミットしなくても OK              |
| `cross_cutting/` | 特定バージョンに依存しないトピック                 |
| `libs/`          | 複数プロジェクトで使い回すヘルパー                 |
