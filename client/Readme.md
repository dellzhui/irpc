## 安装方法

1、将bin里的四个文件复制到当前目录，然后将当前目录加入PATH

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



3、使用Beyond Compare比较两个文件或目录

```shell
irpc bcompare $1 $2
```



4、使用Beyond Compare比较当前仓库修改

仅适应于：只是文件内容修改，不牵扯到重命名、git add等，也即仅比较not staged commit

```shell
GDF
```



4、使用Beyond Compare

```shell
# 进查看当前内容修改，包含staged、not staged，使用以下命令不加参数即可
GBC

# 查看历史提交修改，则传图commit，如
GBC fb120bd15462583e8656158c75f9e9a1ef046869
```



5、使用tig查看git log，在界面内切换到要view diff的commit，按快捷键v，自动调用GBC ${commit_id}

```shell
tig
```

