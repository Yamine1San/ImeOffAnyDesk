# ImeOffAnyDeskに関して

## 概要

AnyDeskでリモートPCを操作中に、ホストPCのIMEがONになったらOFFにするアプリです。

## ダウンロード

v1.0.0<br>
https://github.com/Yamine1San/ImeOffAnyDesk/releases/tag/v1.0.0

## 操作方法

起動するとタスクトレイに常駐します。<br>
その状態でAnyDeskでリモートPCを操作中にIMEをONにするとOFFになります。<br>
終了させるにはタスクトレイのアイコンを右クリックして終了を選択してください。<br>

## 処理詳細

### AnyDeskでリモートPCを操作中の判定

フォアグラウンドのアプリがAnyDesk.exeであり、ウインドウタイトルが「 - AnyDesk」で終わっている事。

### 処理の内容

1秒おきにAnyDeskでリモートPCを操作中か判定<br>
操作中の場合、0.2秒おきにIMEの状態をチェックし、ONになっていたらOFFにする。<br>

