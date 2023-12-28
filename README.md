# PowerPaimon
![GitHub release (latest by date)](https://img.shields.io/github/v/release/rexent-gx/PowerPaimon?color=green)
![GitHub Release Date](https://img.shields.io/github/release-date/rexent-gx/PowerPaimon)
<div style="text-align: center;">
  <img src="https://github.com/rexent-gx/PowerPaimon/assets/27722971/db39fbd3-d476-476b-8ced-290a0bbdbca2" />
</div>

## ダウンロード
**[こちら](https://github.com/rexent-gx/PowerPaimon/releases/latest)から最新版(.exe/64bit)をダウンロードできます**  

## 概要
 - デフォルトの60FPS上限を解除し、420FPSまでの上限解除を行うソフトウェアです。
 - **WriteProcessMemory**を使用してゲーム内のFPS設定値を上書きしています。
  - HoYoverseはFPS上限解除ソフトウェアの存在を認知しており、FPS上限解除のみの使用であればBANの対象にはならないそうです。
  - 現状BANの報告等はありませんが、自己責任で使用してください。また、サードパーティーのプラグインやDLLを使用する場合についても自己責任でお願いします。
 - ボーダーレスウィンドウモードやカスタム解像度、省電力モードなど、いくつかのオプションを追加することができます。

## 使用方法
### 起動
 1. 動作には[.NET Desktop Runtime 8.0.0](https://dotnet.microsoft.com/en-us/download/dotnet/thank-you/runtime-desktop-8.0.0-windows-x64-installer)が必要です。多くのシステムでは自動的にインストール済みですが、起動しない場合はこちらをインストールしてみてください。
 1. [Release](https://github.com/rexent-gx/PowerPaimon/releases/latest)ページから最新版の.exeファイルを**原神のゲームディレクトリ以外の**任意の場所にダウンロードし、起動してください。
    > 原神は実行に管理者権限が必要なため、PowerPaimonの動作には管理者権限が必要です。
    - プロセスメモリにアクセスする関係上、Windows Securityやウイルス対策ソフトにウイルスと判断される場合があります。この場合、PowerPaimonを検査から除外するよう設定してください。
    - SmartScreenに弾かれた場合は、ダイアログの『詳細情報』から実行してください。
 1. GUIで各種設定が行えるほか、『原神を起動』ボタンを選択することで原神を起動できます。既に原神が起動されていると正常に動作しません。
    - 初回起動時は初期設定画面が表示されます。レジストリから自動で原神のインストールディレクトリを判別しますが、取得できなかった場合は『参照』ボタンから手動で設定してください。
 1. 原神起動後はタスクトレイに最小化されます。タスクトレイアイコンをダブルクリックすることでメインウィンドウを表示できます。

### 設定
 - 左側のFPSフェーダーを操作、またはテキストボックスへ値を入力してFPS上限を設定します。
 - `一般設定`タブはPowerPaimon本体に関する設定です。
   - `起動時に最小化` - PowerPaimonをタスクトレイに最小化した状態で起動します。
   - `自動終了` - 原神の終了時に連動してPowerPaimonを終了します。
   - `省電力モード` - 原神のバックグラウンド移行時にFPS上限を10FPS、プロセス優先度を低に設定します。
   - `表示言語` - PowerPaimonのUI言語を設定できます。
 - `原神起動設定`タブは原神プログラム本体に関する設定です。
   - `ボーダーレスウィンドウ` - 起動時に`-popupwindow`オプションを追加し、ボーダーレスウィンドウでの表示にします。ウィンドウ切り替えなどでフォーカスを失っても非表示になりません。
   - `フルスクリーン` - 有効時はフルスクリーンで起動します。
     - `Borderless`モード - ボーダーレスモードで起動します。上記のボーダーレスウィンドウモードとは異なり非アクティブ時には非表示になりますが、Exclusiveモードより高速にウィンドウの切り替えが行えます。
     - `Exclusive`モード - 排他フルスクリーンモードで起動します。デスクトップの描画を行わない為最もパフォーマンスが良いですが、ウィンドウの切り替えに多少時間がかかります。
   - `カスタム解像度` - 有効時には指定された解像度で起動します。
   - `モニター番号` - 原神を表示するモニタ番号を指定します。
   - `プロセス優先度` - 原神のプロセス優先度を設定します。
   - `モバイルUIを使用` - スマホ版のUIで起動します。タッチ機能のあるラップトップ等で使えるかもしれません。キーボード/マウス操作は受け付けないようなので、普通のPCではあまり使用しないと思います。

## 注意
 - ボーダーレスモードを有効にしたにも関わらず別ウィンドウに切り替えると非表示になってしまう場合や、フルスクリーンモードなのにウィンドウ枠が表示されてしまう場合、**Alt+Enter**を押してみて下さい
 - PowerPaimon使用時に帰元ノ庭のギミックが正常に動作しない問題を確認しています。一部ギミックはフレームレートに依存した挙動をする可能性があるので、正常に動作しない場合はPowerPaimonを使用せずに再試行してみてください。
   - 上限FPSを60に設定すれば動くかもしれませんが、確認できないので情報をお待ちしています。

## コンパイル
 - Visual Studio 2022 Community Editionを使用してコンパイルが可能です。

## バージョン履歴
### v3.0.0
- 本家FPS Unlockerの.NET Core以降に追従し、使用言語をC#に変更
- GUIを更新
- 起動オプションの追加
- 言語切り替え機能を実装

### v2.0.0
- 本家FPS Unlockerのアップデートを取り込み
- GUIを更新
- バージョン4.3への対応
- その他バグ修正

### v1.0.0
- GUIを実装
- ホットキー機能を削除
- ボーダーレスモードの実装


# English version

## Download
**Download latest release from [HERE](https://github.com/rexent-gx/PowerPaimon/releases/latest)(.exe/64bit only)**  

## 概要
 - This tool helps you to unlock the 60 fps limit in the game, up to 420 fps.
 - It uses **WriteProcessMemory** to overwrite the desired fps to the game.
 - Handle protection bypass is already included.
  - HoYoverse is well aware of this tool, and you will not get banned for using ONLY fps unlock.
  - If you are using this tool or other third-party plugins, you are doing it at your own risk.
 - Add some options like Borderless windowed mode, Custom resolution, Power saving to the game.

## Usage
### Launch
 1. Make sure you have the [.NET Desktop Runtime 8.0.0](https://dotnet.microsoft.com/en-us/download/dotnet/thank-you/runtime-desktop-8.0.0-windows-x64-installer) (Usually it should come installed)
 1. Download latest .exe from [Release](https://github.com/rexent-gx/PowerPaimon/releases/latest) and save it anywhere you want **except for the game folder**.
    > It requires adminstrator because the game needs to be started by the unlocker and the game requires such permission.
    - Because of accessing process memory, security softwares (e.g. Windows Security, AntiVirus softwares) detect this tool as a malware. In this case, add this tool to exclusion.
 1. You can configure as you like in GUI, and launch the game. Make sure your game is closed.
 1. Run the exe as administrator, and leave the exe running.

## Compiling
 - Use Visual Studio 2022 Community Edition to compile.

## Version History
### v3.0.0
- Merge upstream updates and rewrite in .NET Core(C#)
- Update GUI
- Add launch options
- Multilanguage support

### v2.0.0
- Merge upstream updates
- Update GUI
- Compatible with 4.3 update
- Bugfix

### v1.0.0
- Add GUI
- Remove Hotkey
- Implement borderless mode