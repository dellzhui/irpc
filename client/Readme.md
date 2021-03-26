## 安装方法

1、将tar里的四个文件解压到当前目录，然后将当前目录加入PATH
```shell
export PATH="`pwd`:${PATH}"
echo "export PATH=\"`pwd`:${PATH}\"" >> ~/.bashrc
```

2、修改配置

修改脚本文件`irpc`，将以下全局变量修改为实际值

|Prop|Desc|
|:--:|:--:|
|LOCAL_SAMBA_PATH|见下文|
|REMOTE_SAMBA_PATH|见下文|
|REMOTE_SERVER_IP|windows主机IP地址，一般不会改变的那个，建议设置为NAT网卡或HOST网卡的地址|
|LCOAL_IP|Linux虚拟机IP地址，一般不会改变的那个，建议设置为NAT网卡或HOST网卡的地址|

确定`LOCAL_SAMBA_PATH`、`REMOTE_SAMBA_PATH`的值：
> 执行 sudo cat /etc/samba/smb.conf，
> 找到samba共享的设置，一般为：


```
[root]
        comment = ROOT
        path = /home
        browseable = yes
        writable = yes
```
则：
> LOCAL_SAMBA_PATH="/home"
> 
> REMOTE_SAMBA_PATH="root"

![](https://jijiantuku-image.oss-cn-beijing.aliyuncs.com/markdown_img/2021/03/25/20210325_174700_e3ee28105024886ea5caaced5bfcf58b.png)

3、防止从windows端拷贝到linux端文件格式变化
```shell
dos2unix irpc N E
chmod 755 irpc* N E
```

## 使用方法
1、基于samba服务，使用windows exploer打开samba共享目录
```shell
# 不加参数，默认打开当前路径；也可打开指定目录，将路径名（相对、绝对都可）作为参数即可
E
```

2、基于samba服务，使用windows编辑器打开指定的文本文件
```shell
N 文件名
```