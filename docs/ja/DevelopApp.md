# アプリケーションの開発方法
アプリケーション開発における一連の流れを説明する．

## 必要なパッケージのインストール（Ubuntu/WSL2）

```bash
sudo apt update
sudo apt install git ruby make gcc-arm-none-eabi
```

## 必要なパッケージのインストール（Windows）

① python3
- python3.exe -- https://pythonlinks.python.jp/ja から python-3.14.0-amd64.exe など
- ※必ず、「Add python.exe to PATH」にチェックを入れること

②　pyusb
― Windows PowerShellでpyusbをインストールしておく
```bash
pip install pyusb
```
- ※pyusbを入れ忘れると、後々「No module named usb」というエラーで落ちる

③libusb-win32ドライバー（一度変更しておけばOK）
- https://zadig.akeo.ie から zadig-2.9.exe をダウンロードし、インストールする
- 最初にSPIKE-RTをDFUモードで接続したら、zadigを起動し、「Options」→「List All Devices」→ 「LEGO Technic Large Hub in DFU Mode」を選ぶ
 - ドライバーを「WinUSB」から「libusb-win32」へ変更し、「Install Driver」を押す
- ※ドライバーが正しくないと、ファイル転送が「No backend available」で失敗する

## ソースコードの入手
以下により，ソースコードをクローンする．
```bash
git clone https://github.com/shimojima/spike-rt.git -b etrobo
```
以下，特に断りの無い限りトップディレクトリが`spike-rt` のディレクトリであるとする．
また，アプリケーション・ソースコードのディレクトリが `spike-rt/$appdir`に配置されているとする．

## 開発手順
RasPikeやRasPike-ARTに合わせて、sdk/workspace の中に、プロジェクトファイルを置きます。
例として、RasPike-ART の sample_c5_spike を移植して、sdk/workspace/sample_c5 に置きました。

### ビルド
```bash
cd ~/spike-rt/sdk/workspace
make img=sample_c5
```

asp.binファイルを sdk/workspace フォルダにコピーし、プロジェクトのフォルダ名を appdir に書き込みます。

中間ファイル等は、プロジェクトの下の build フォルダに生成されます。
カーネルライブラリ等も、必要に応じて自動生成されます。これらはプロジェクト共通のため、
~/spike-rt/build 以下に保存されます。

### クリーンアップ

プロジェクトの中間ファイル等を消すコマンド：
```bash
cd ~/spike-rt/sdk/workspace
make clean 
```
ただし、影響があるのは、appdir で指定されているプロジェクトだけです。appdirファイルがなかったり別の場所を指している場合は、ほかのプロジェクトのbuildフォルダは触りません。

カーネルライブラリ等も消したければ：
```bash
cd ~/spike-rt/sdk/workspace
make realclean 
```

## 書き込み
SPIKE Prime Hub に転送するファイルは、asp.bin です。

### HubのDFUモードへの遷移
- USBケーブルを抜き，Hubの電源を切る．
- Bluetoothボタンを押しながらUSBを接続する．
- ボタンのLEDが点滅するまで，Bluetoothボタンを押し続ける．

### 書き込みの実行
SPIKE Prime HubをDFUモードにしてPCに接続し、Windows上のpythonをWSL2から起動してasp.binをHubに書き込む
```bash
cd ~/spike-rt/sdk/workspace
make upload
```

sdk/workspace/asp.bin が転送されます。

## USBシリアルの接続
WindowsのTeratermなどでUSBシリアルに接続し，ログ出力を確認することができる．
一旦，Hub の電源をONにしてからでないと，接続できないことに注意する．

## 不要なフォルダ

以下のフォルダは、現時点で使っていません。
- spike-rt/common
- spike-rt/sample
- spike-rt/scripts
- spike-rt/test
- spike-rt/tools

