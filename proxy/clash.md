---
title: clash core 使用方法
type: page
---

#  如何使用clash core premium代理

众所周知, 我们需要一些工具来访问互联网, 不过有个问题, 你联网之前怎么下载软件? 尤其是使用AUR的时候经常需要从git构建软件, 连不上github怎么办? 为了解决这些问题, 我选择使用`clash core premium`的`TUN mode`来解决最基础的连github.com的问题.

> clash有开源版本的core和闭源版本的premium版, 如果要使用虚拟网卡TUN, 那么我们需要选择闭源的premium版本.

TODO: 什么事TUN?

## 下载

首先, 需要下载`clash premium`

1. 鉴于现在clash删库了, 你最好自己有一个clash的备份, 我自己把clash core放在了一个安全的物理位置. 所以我只要导入到新的linux上就可以了. 如果你现在没有, 那就想办法在互联网上找吧.

- 关于如何导入, 展开说一下.
	- 如果你同一个网段下有其他设备, 那就很简单了, 只要用ssh连过去就行了.

    ```sh
    #ip查看当前设备ip地址
    #除去127.0.0.1的回环地址即可查到本机ip
    ip -brief addr
    #使用ssh scp发送文件
    scp path/to/clash_bin username@remote_new_linux:~/software/
    #你也可以使用rsync, 具体用法推荐安装一个tldr来查看
	  #这里只是导入到了$HOME/software下面, 因为我之后想要使用包管理器再安装到/usr/bin/clash, 如果你想直接在PATH里面使用, 那导入到/usr/local/bin下面吧.
    ```
	  
	- 或者你使用你的u盘, 这里推荐一个自动挂在u盘的包, 真的很好用, 原理应该是udev脚本: `simple-usb-automount`.
	
	  ```sh
	  sudo cp /usb/device/clash_bin ~/software/
	  ```

2. 当能够连接github后, 可以尝试使用软件包管理器安装`clash`, 或者如果你的国内软件源里有clash的话, 那你可以直接安装了.

```sh
#使用AUR安装, 这个包在archlinuxcn里面有
yay -S clash-premium-bin
# 软件信息:
# yay -Si clash-premium-bin
# Repository      : archlinuxcn
# Name            : clash-premium-bin
# Version         : 2023.08.17-1
# Description     : Close-sourced pre-built Clash binary with TUN support
# Architecture    : x86_64
# URL             : https://github.com/Dreamacro/clash/releases/tag/premium
# Licenses        : unknown
# Groups          : None
# Provides        : clash
# Depends On      : glibc
# Optional Deps   : None
# Conflicts With  : clash  clash-tun  clash-dev-git
# Replaces        : None
# Download Size   : 5.82 MiB
# Installed Size  : 18.52 MiB
# Packager        : lilac (on behalf of DDoSolitary) <DDoSolitary@gmail.com>
# Build Date      : Fri 18 Aug 2023 12:40:03 PM CST
# Validated By    : MD5 Sum  SHA-256 Sum  Signature
```

## 使用

### 准备工作文件夹

clash的使用需要两个东西`config.yaml`和`Country.mmdb`.

```sh
❯ pwd
/etc/clash
❯ ls
cache.db  config.bak  config.yaml  Country.mmdb
```

`Country.mmdb`应该是提供ip和地理数据对应关系的数据文件,可以在[这里](https://github.com/Dreamacro/maxmind-geoip/releases)下到. 按道理启动clash的时候会自动下载这个文件, 但如果你连接不上外网, 还是手动下载吧.

`config.yaml`自然是我们的配置文件, 由于删库, 我现在找不到clash的文档了, 不过暂且看我现在的配置:

```yaml
mixed-port: 7890
allow-lan: true
bind-address: '*'
mode: rule
log-level: info
external-controller: '127.0.0.1:9090'
dns:
    enable: true
    ipv6: false
    default-nameserver: [223.5.5.5, 119.29.29.29]
    enhanced-mode: fake-ip
    fake-ip-range: 198.18.0.1/16
    use-hosts: true
    nameserver: ['https://doh.pub/dns-query', 'https://dns.alidns.com/dns-query']
    fallback: ['tls://1.0.0.1:853', 'https://cloudflare-dns.com/dns-query', 'https://dns.google/dns-query', 'https://dns.cloudflare.com/dns-query']
    fallback-filter: { geoip: true, ipcidr: [240.0.0.0/4, 0.0.0.0/32] }
tun:
       enable: true
       stack: system # or gvisor
         # dns-hijack:
         #     - 8.8.8.8:53
         # - tcp://8.8.8.8:53
         # - any:53
         #  - tcp://any:53
       auto-route: true # manage `ip route` and `ip rules`
       auto-redir: true # manage nftable REDIRECT
       auto-detect-interface: true # conflict with `interface-name`
#下面是节点的信息, 这些是通过订阅链接可以导入的
proxies:
  - {name: example proxy, server: proxy.server, port: 10023, type: ss, cipher: aes-128-gcm, password: ed63e316-6b40-45eb-b4e1-5663612e6ee5}
  ...
#这里是流量选择的信息, 一般是提供商帮你写好的
proxy-groups:
  - name: 节点选择
    type: select
    proxies:
      - 自动选择
      - 全球直连
  ...

```

这里我启用了tun, 如果不想启用, 把tun对应的几行注释掉就可以. 配置应该比较好懂, 需要修改的大概就是端口号吧, 如果你想改的话.

### 启动!

可以看到我刚才把配置文件放到`/etc/clash/`了, 如果你只是临时测试, 或者想要放到其他位置也是可以的. 只要目录中有我们刚才提到的那两个文件就可以工作了.

```sh
#记得放到$PATH能触及的地方,或者手动指定位置: path/to/clash
#-d也就是'directory'来指定工作目录
#如果需要使用tun, 必须使用super user启动
sudo clash -d /etc/clash/
```

如果正常就会看到类似如下信息:

```sh
11:04:53 INF [Config] initial compatible provider name=🎯 全球直连
11:04:53 INF [Config] initial compatible provider name=🔰 节点选择
11:04:53 INF [Config] initial compatible provider name=🚫 运营劫持
...
#一些绑定端口和协议的信息
11:04:53 INF inbound create success inbound=mixed addr=:7890 network=tcp
11:04:53 INF inbound create success inbound=mixed addr=:7890 network=udp
11:04:53 INF [API] listening addr=127.0.0.1:9090
11:04:53 INF [Inbound] TUN listening iface=utun gateway=198.18.0.1
#下面开始就是连接的信息了
11:04:53 INF [UDP] connected lAddr=198.18.0.1:56339 rAddr=192.168.3.1:53 mode=rule rule=IPCIDR(192.168.0.0/16) proxy=🎯 全球直连[DIRECT]
11:04:53 INF [UDP] connected lAddr=198.18.0.1:44363 rAddr=192.168.3.1:53 mode=rule rule=IPCIDR(192.168.0.0/16) proxy=🎯 全球直连[DIRECT]
11:04:53 INF [UDP] connected lAddr=198.18.0.1:44361 rAddr=192.168.3.1:53 mode=rule 
...
```

如果有问题, 会以红色显示错误和警告信息, 认真看一般都可以解决, 常见的有几个:

1. 端口占用, 使用你的端口查看工具看一下, 我使用的是procs, 看看是不是之前开启过, 或者是其他软件占用了端口.

```sh
❯ ps 7890 # 使用了alias别名
```
| PID   | User | State | Nice | TTY | CPU [%] | MEM [%] | VmSize | VmRSS  | TCP          | UDP                         | Read [B/s] | Write [B/s] | CPU Time | Start            | Command                      |
|-------|------|-------|------|-----|---------|---------|--------|--------|--------------|------------------------------|------------|-------------|----------|------------------|-------------------------------|
| 43639 | root | S     | 0    |     | 4.3     | 0.1     | 5.197G | 35.078M| [7890, 9090] | [7890, 40224, 45906]         | 0          | 0           | 00:00:00 | 2023/12/10 11:10 | /usr/bin/clash -d /etc/clash/ |
2. 权限不足, 正如我刚才说的, 启动TUN需要管理员权限.
3. 配置文件错误, 检查配置文件有没有拼写错误, 用yaml lsp或者在线工具检查一下语法.

### 浏览器

此时配置之后, 因为使用了TUN, 命令行中应该也被代理了, 可以使用软件包安装软件了. 

使用浏览器的话, 有可能无法直接走代理, 下载浏览器代理插件, 这里我使用的是[SwitchyOmega](https://github.com/FelisCatus/SwitchyOmega), 如果此时访问不了chrome store, 试试edge浏览器, 毕竟微软服务在国内还是能用的.

### 开机自启

我使用systemd来实现开机自启

创建一个文件`/etc/systemd/system/clash.service`, 写入下面内容, 注意把启动路径和-d 参数修改成你自己的.

```sh
[Unit]
Description=Clash daemon, A rule-based proxy in Go.
After=network-online.target

[Service]
Type=simple
Restart=always
ExecStart=/usr/bin/clash -d /etc/clash

[Install]
WantedBy=multi-user.target
```

