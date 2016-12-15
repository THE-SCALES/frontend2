# frontend2

こちらがバックエンド課題置き場所となっております<br>

[開発環境(バックエンド)]
OS:Ubuntu 14.03<br>
使用ライブラリ:OpenGL<br>

中間における主な課題点と改善<br>

クラス設計<br>
main.cppの1つのファイルに膨大なコードを乗せて可読性を下げないように<br>
クラス毎にファイルを分けコード行数を圧縮するよう心掛け行った<br>
しかし、当たり判定の関数だけ圧縮が上手くいかなかった。
<br>

実装したかった機能<br>
ビリヤードファウル処理<br>
壁の反射判定重複回避<br>

各ファイルにおける役割と機能紹介<br>
<br>
sphere.cpp…ビリヤード球クラス<br>
<br>
hole.cpp…ポケットクラス<br>
<br>
object.cpp…ポリゴンオブジェクトクラス<br>
<br>
main.cpp…ゲーム処理と表示<br>
<br>
<br>
