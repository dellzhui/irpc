## 使用方法
1、双击运行，首次运行后，界面如下：

![](https://jijiantuku-image.oss-cn-beijing.aliyuncs.com/markdown_img/2021/04/13/20210413_190246_a0a5b2b1cb85a46500c2d757fff5e0a9.png)

如果出现以下提示，则选中三个框后点击允许：

![](https://jijiantuku-image.oss-cn-beijing.aliyuncs.com/markdown_img/2021/03/26/20210326_134419_95cd7710d231ce3792c613aaf4b0935c.png)
> 这是由于该程序须开启10121端口监听

2、选择文本编辑器程序
点击浏览按钮，选择windows端打开文本文件的编辑器程序，比如notepad++.exe，如下：

![](https://jijiantuku-image.oss-cn-beijing.aliyuncs.com/markdown_img/2021/03/25/20210325_175909_a3429d53662eb2689a1d668bde636c6b.png)

选择完成后界面如下：

![](https://jijiantuku-image.oss-cn-beijing.aliyuncs.com/markdown_img/2021/04/13/20210413_190325_2e200dcc2d5befe2bf92055547cd1d72.png)



同理，选择Beyond Compare路径，如下：

![](https://jijiantuku-image.oss-cn-beijing.aliyuncs.com/markdown_img/2021/04/13/20210413_190425_9b8eee911463e894580032c3eb17f5c4.png)

点击启动按钮后，界面如下：

![](https://jijiantuku-image.oss-cn-beijing.aliyuncs.com/markdown_img/2021/04/13/20210413_190435_c125b24b236d215d16802dea3b4c2e2d.png)

至此服务启动成功





## 将服务程序添加到开机自启动

1、建立该程序的软链接文件，如下：

![](https://jijiantuku-image.oss-cn-beijing.aliyuncs.com/markdown_img/2021/03/25/20210325_182305_eeda047543ad2c6176b5927419ae54ad.png)

2、将软链接文件copy到Windows以下目录内：

```
C:\ProgramData\Microsoft\Windows\Start Menu\Programs\StartUp
```




## QoA
1.程序启动失败，报错如下：

![](https://jijiantuku-image.oss-cn-beijing.aliyuncs.com/markdown_img/2021/03/25/20210325_180106_e4a6bde25b6fdaa6d264660db1552856.png)

解决方法：
> （1）打开任务任务管理器，找到`irpc_server.exe`程序，将其全部kill，如下

![](https://jijiantuku-image.oss-cn-beijing.aliyuncs.com/markdown_img/2021/03/25/20210325_180159_6805a5f114fe46fa1e74e71b36f6867a.png)

> （2）重新启动irpc_server.exe



2、如何更换文本编辑器

（1）点击浏览按钮，选择新的文件编辑器程序（exe文件）

（2）点击重启按钮



3、是否每次启动都要重新选择文本编辑器程序

无须，首次配置后，会在当前目录下生成config.json文件，下次启动时自动加载该配置文件并自动启动服务