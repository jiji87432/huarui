# huarui
华锐行情接收
## WonderTrader（WT）解析：QuoteFactory模块
**说明：行情接口为中泰证券的XTP，该接口为市场常用，WT已经实现了它的parser，开发环境为WIndows。 **
### 执行程序配置
按如下的配置说明进行配置即可以使用QuoteFactory.exe来接收行情。
首先是配置文件，以下的文件要放在QuoteFactory可执行文件的同目录下，具体包括dtcfg.yaml、mdparsers.yaml、logcfgdt.yaml和statemonitor.yaml，这些配置文件都可以从WT主目录下的dist/QuoteFactory文件夹下复制到，其中要修改的是dtcfg.yaml和mdparsers.yaml两个文件，具体如下，配置项如果没有特别说明的则可以直接复制粘贴。
1. **dtcfg.yaml**
```yaml
basefiles:
    #这下面对应的四个文件要在../common/下面放好，哪个不需要放目前还没确定过，但holidays.json和stk_sessions.json是确定需要的，stk_sessions.json文件缺失的话会导致服务没法保存行情数据，这些文件可以从wtpy的dev分支下的demos/commons找到。
    commodity: ../common/stk_comms.json
    contract: ../common/stocks.json
    holiday: ../common/holidays.json
    session: ../common/stk_sessions.json
#顶点广播配置，还没搞明白，待后续解答，可以先保持这段配置不变
broadcaster:
    active: true
    bport: 3997
    broadcast:
    -   host: 255.255.255.255
        port: 9001
        type: 2
    multicast_:
    -   host: 224.169.169.169
        port: 9002
        sendport: 8997
        type: 0
    -   host: 224.169.169.169
        port: 9003
        sendport: 8998
        type: 1
    -   host: 224.169.169.169
        port: 9004
        sendport: 8999
        type: 2
parsers: mdparsers.yaml
statemonitor: statemonitor.yaml
writer:
    async: true
    groupsize: 20
    #行情数据的保存目录
    path: ../STK_Data
    savelog: false
```

2. ** mdparsers.yaml**
```yaml
parsers:
-   active: true
    buffsize: 128
    clientid: 1
    #你想要订阅的股票代码，据作者说不做code的配置则认为是订阅全市场代码，还没测试过
    code: SSE.000001,SSE.600009,SSE.600036,SSE.600276,SZSE.000001
    hbinterval: 15
    host: xtp行情服务地址
    id: parser
    module: ParserXTP
    pass: 你的xtp密码
    port: xtp行情服务端口
    protocol: 1
    user: 你的xtp用户名
```
### 调试配置
1. 调试时候相应的配置文件要放在src/QuoteFactory的相应路径下面，src/QuoteFactory对应于QuoteFactory.exe的当前路径。
2. 把WtDataStorage.dll复制到src/QuoteFactory下面，还要把xtpquoteapi.dll和生成好的parserXTP.dll复制到src/QuoteFactory/parsers下面。
3. 然后你就可以在**Visual Studio**下对程序断点、单步...愉快地调试代码了。

