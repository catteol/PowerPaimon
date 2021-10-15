# PowerPaimon
![GitHub release (latest by date)](https://img.shields.io/github/v/release/rexent-gx/PowerPaimon?color=green)
![GitHub Release Date](https://img.shields.io/github/release-date/rexent-gx/PowerPaimon)
<div style="text-align: center;">
  <img src="https://user-images.githubusercontent.com/27722971/137457248-20981d46-2433-48b2-98eb-734d97307c6e.png" />
</div>

## ダウンロード
**[こちら](https://github.com/rexent-gx/genshin-fps-unlock-gui/releases/latest)から最新版(.exe/64bit)をダウンロードできます**

## 概要
 - タスクトレイ常駐型アプリケーションです
 - デフォルト60FPS制限を解除し、最高240FPSまで対応します
 - ボーダーレスでの表示に対応します

## 使用方法
 - 動作には[Visual C++ 2019 Redistributable (x64)](https://aka.ms/vs/16/release/vc_redist.x64.exe)がインストールされている必要があります
 - [Release](https://github.com/rexent-gx/genshin-fps-unlock-gui/releases/latest)ページから最新版の.exeファイルをダウンロードして下さい
 - 任意の場所で実行して下さい
   - 動作に管理者権限が必要となります
   - .exeファイルと同一ディレクトリに設定ファイル(.ini)を自動で作成します
 - **操作や確認が必要な場合は通知が送られるので、上手く動かない場合は通知を確認してみて下さい。全画面アプリケーションが実行中の場合等、Windowsの設定によっては通知がサイレントになる場合があります。**
 - 初回起動時のみ手動で原神を起動して下さい。次回以降はPowerPaimon起動時に連動して原神が起動します
 - 右クリックメニューから各種設定が行なえます。
   - デフォルト設定は144FPS、ボーダーレス無効です
 - ボーダーレスモードが有効の場合、**Alt+Enter**でフルスクリーンとボーダーレスが切り替わります
 - 原神を終了すると自動でPowerPaimonも終了します。操作は不要です

## 注意
 - 起動時に既に原神を起動していると正常に動作しません
 - **ボーダーレスの無効/有効切り替えは次回起動時から反映されます。**
 - ボーダーレスを有効にしたにも関わらずフルスクリーン挙動（別ウィンドウを開くと原神が非表示になってしまう等）となる場合、**Alt+Enter**を押してみて下さい
 - クラッシュした場合等タスクトレイにアイコンが残ったままになる事象を確認しています
    - カーソルでなぞれば消えます（？）
    - 他ソフトウェアでも同様の現象が見られるのでWindows側の問題かもしれません
 - C++ほぼ触らないのでバグ等あるかもしれません
 - メモリアクセス及び変更を行うことは規約に違反するので、ご利用は全て自己責任でお願いします
 - コンパイル方法及びその他注意事項は、[フォーク元](https://github.com/34736384/genshin-fps-unlock)から加筆転載した下記英語版Readmeを参照して下さい


# English version

## Download
**You can download the latest ".exe(64bit)" file from [HERE](https://github.com/rexent-gx/genshin-fps-unlock-gui/releases/latest).**

## About
 - Working in System Tray
 - Unlock 60 FPS limit up to 240 FPS in the game
 - Enable Borderless mode

## Note
 - This is an external program uses **WriteProcessMemory** to write the desired fps to  the game
 - Handle protection bypass is already included
 - Does not require a driver for R/W access
 - Should works for future updates

 ## Usage
 - Make sure you have the [Visual C++ 2019 Redistributable (x64)](https://aka.ms/vs/16/release/vc_redist.x64.exe) installed
 - If it is your first time running, run unlocker as admin, then the unlocker will ask you to open the game. This only need to be done once, it's used for acquiring the game path. Then it'll be saved to a config file. After the config is made you can start the game via the unlocker in future sessions.
 - Place the compiled exe anywhere you want
 - Make sure your game is closed, the unlocker will automatically start the game for you
 - Run the exe as administrator, and leave the exe running
 >It requires adminstrator because the game needs to be started by the unlocker and the game requires such permission
 - To inject reshade, place the reshade dll in the same folder as the unlocker

## Compiling
 - Use  Visual Studio 2019 Community Edition to compile
 - Not required but I know it works on this version

 ## Notes
 - Tested on a new account for two weeks and no bans so far (AR30), can't guaranteed it will be safe forever, But honestly though, I doubt they would ban you for this.
 - Modifying game memory with an unauthorized third party application is a violation of the ToS, so use it at your own risk
 - If you want to change keybinds or the default fps then you can edit the defines at the top of the source
 - The reason that I didn't made it to be place in the same folder of the game exe is because the game will attempt to verify the files before logging on, and it will treat the unlocker as a game file too which will fail the file integrity check. Producing an 31-4302 error.


# 原神解锁FPS限制

 - 工作原理类似于外部辅助，通过**WriteProcessMemory**把FPS数值写进游戏
 - 不需要通过驱动进行读写操作
 - 支持国服和外服
 - 理论上支持后续版本，不需要更新源码
 - 如果需要更新我会尽快更新

## 编译

 - 用VS2019编译，其他版本的也应该可以，没测试过
## 食用指南
 - 运行前确保系统已安装[Visual C++ 2019 Redistributable (x64)](https://aka.ms/vs/16/release/vc_redist.x64.exe)
 - 第一次运行的话先以管理员运行，然后手动打开游戏，这样解锁器能够获取到游戏路经并保存在配置文件里，这只需要执行一次，以后就可以直接用解锁器启动游戏了
 - 解锁器放哪都行
 - 运行之前确保游戏是关闭的
 - 用管理员运行解锁器
 - 解锁器不能关掉
>使用管理员运行是因为游戏必须由解锁器启动，游戏本身就需要管理员权限了，所以负责启动的也是需要的

## 注意
- 已经在新号上测试了两星期，目前并没有任何异常，冒险等级30
- 使用未认证的第三方软件修改游戏数据是违反了协议条款的，后果自负
- 想要更改热键的话，修改下源里开头的定义 （[热键码](http://cherrytree.at/misc/vk.htm)）
- 至于为啥我没写成能在和游戏同一个目录下运行是因为游戏登录的时候会进行文件完整性检测，如果游戏目录内有其他文件也会当做是游戏的文件进行检测。如果把解锁器和游戏放一起的话游戏会把解锁器当成游戏文件检测，从而导致报错（31-4302）
- 要转载的话随便，毕竟开源，可以的话就注明下出处
- 这么个破工具请不要拿去倒卖
