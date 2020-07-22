# Develop Note
## `Piece.id`
| 番号 | 駒 | 番号 | 成り |
|:---:|:---:|:---:|:---: |
| 1 | 歩 | 9 | と金 |
| 2 | 香 | 10 | 成香 |
| 3 | 桂 | 11 | 成桂 |
| 4 | 銀 | 12 | 成銀 |
| 5 | 金 | 13 | None |
| 6 | 角 | 14 | 馬 |
| 7 | 飛 | 15 | 竜 |
| 8 | 王 | 16 | None |
| 0 | 空 | -1 | 盤面の外 |

## `Piece.player`
| Num | Player |
| --- | --- |
| -1 | プレイヤーなし |
| 0 | 1P |
| 1 | 2P |
| 随時追加 |
| 2 | 3P |
| 3 | 4P |

## `Methods` 便利な関数をメモしとく
- `Calc::rotate2dVector(2dVec, string direction)`  
    *direction* -> `"right"` or `"left"` or `"reverse"`

## shogi.js
参考にしてもらっているJavaScriptのコード  
http://www.arts-net.co.jp/team/staff_blog/04/12574.html