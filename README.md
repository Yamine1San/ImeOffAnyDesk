# ImeOffAnyDesk

## アプリ概要

AnyDeskでリモートPCを操作中に、ホストPCのIMEがONになったらOFFにする常駐アプリです。
<br>ホストPCのIMEをOFFにしたままリモートPCのIMEだけをONとOFFの切り替えが可能になります。
<br>AnyDeskでの日本語の入力が快適になります。

## ダウンロード

v1.0.0<br>
https://github.com/Yamine1San/ImeOffAnyDesk/releases/tag/v1.0.0


## 起動方法

`起動するとタスクトレイに常駐します。`

* スタートアップフォルダに入れておく(おすすめ)
* ダブルクリックで実行する 


## 終了方法

* タスクトレイのアイコンを右クリックして終了を選択する<br>


## 処理概要


### AnyDeskでリモートPCを操作中の判定方法

フォアグラウンドのアプリがAnyDesk.exeであり、ウインドウタイトルが「 - AnyDesk」で終わっている時にリモートPCを操作中と判断しています。

### 処理の詳細

* 1秒おきにAnyDeskでリモートPCを操作中か判定する。
* リモートPC操作中の場合、0.2秒おきにホストPCのIMEの状態をチェックし、ホストPCのIMEがONになったら即座にOFFにする。

