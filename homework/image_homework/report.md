# Inkin 书法评分系统

> 饶逸石 8207210519

## 工作内容

我在小组中负责后端开发部分，主题代码使用Golang和Gin框架开发。此外，我也负责了工程管理，三端协调和项目部署的工作。

项目架构图如下：

![](./assets/ink.png)

有[git记录](https://github.com/CSU-YKF/mozhi/commits/main/?author=Lambert-Rao)为证：

![img](./assets/ZGymSZz.png)

## ![img](./assets/mNbyBRg.png)

## 项目结构

我参考了Go项目的标准结构，主题代码在`internal`部分，

代码仓库：https://github.com/CSU-YKF/mozhi

![img](./assets/WAvVMCD.png)

这是开发中的项目树形结构，包含算法部分，后端部分和前端部分

```sh
 .
├──  algorithms
│   ├──  __init__.py
│   ├──  assessment
│   │   ├──  __init__.py
│   │   ├──  feature_extraction.py
│   │   ├──  handwrite.png
│   │   ├──  li_pre.png
│   │   ├──  main.py
│   │   ├──  preprocessing.py
│   │   ├──  registration.py
│   │   ├──  scoring.py
│   │   └──  SRAFE.py
│   ├──  comment
│   │   ├── 󰌠 __pycache__
│   │   ├──  claude_comment.py
│   │   ├──  ernie_comment.py
│   │   └──  '新建 文本文档.txt'
│   ├──  dataset
│   │   ├──  data
│   │   ├──  dataset_gnt.py
│   │   ├──  dataset_png.py
│   │   ├──  gnt_to_png.py
│   │   ├──  HWDB
│   │   └──  test_data
│   ├──  deepmodel
│   │   ├──  2023-12-13-21-25.log
│   │   ├──  2023-12-13-21.log
│   │   ├──  2023-12-13-22.log
│   │   ├──  __init__.py
│   │   ├── 󰌠 __pycache__
│   │   ├──  data
│   │   ├──  dataset_net.py
│   │   ├──  e3c.py
│   │   ├──  log
│   │   ├──  log.py
│   │   ├──  main.py
│   │   ├──  models.py
│   │   ├──  resnet.py
│   │   ├──  resnet50.pth
│   │   └──  vig
│   ├──  main.py
│   ├──  pb
│   │   ├── 󰌠 __pycache__
│   │   ├──  assess_pb2.py
│   │   └──  assess_pb2_grpc.py
│   ├──  README.md
│   ├──  recognize
│   │   ├──  __init__.py
│   │   ├──  HWDB.py
│   │   ├──  main.py
│   │   ├──  recognition.py
│   │   └──  train.py
│   ├──  start.sh
│   └──  utils
│       ├──  single_pre
│       └──  whol_pre
├── 󰒍 api
│   ├──  buf.gen.yaml
│   └──  pb
│       ├──  assess.proto
│       └──  buf.yaml
├──  build
│   └──  build.sh
├──  cmd
│   └──  server
│       ├──  main.go
│       └──  server
├──  config
│   └──  config.yaml
├──  docker-compose.yml
├──  Dockerfile
├──  docs
│   ├──  project.zh-CN.md
│   ├──  README.md
│   └──  sql
│       ├──  datastructure.sql
│       └──  Dockerfile
├──  go.mod
├──  go.sum
├──  internal
│   ├──  core
│   │   ├──  config.go
│   │   └──  server.go
│   ├──  data
│   │   ├──  assess.go
│   │   ├──  db.go
│   │   ├──  image.go
│   │   ├──  info.go
│   │   └──  token.go
│   ├──  http
│   │   ├──  download.go
│   │   ├──  error.go
│   │   ├──  info.go
│   │   └──  upload.go
│   ├──  rpc
│   │   └──  pb
│   ├──  support
│   │   └──  error.go
│   └──  user
│       ├──  login.go
│       └──  register.go
├──  LICENSE
├──  log
│   ├──  2023-12-14_18-09-59.log
│   ├──  2023-12-14_18-13-52.log
│   ├──  2023-12-14_18-14-52.log
│   ├──  2023-12-14_18-19-52.log
│   ├──  2023-12-14_18-20-32.log
│   ├──  2023-12-14_18-22-08.log
│   ├──  2023-12-14_18-28-57.log
│   ├──  2023-12-14_18-39-50.log
│   ├──  2023-12-14_18-55-35.log
│   ├──  2023-12-14_19-08-02.log
│   ├──  2023-12-14_19-14-26.log
│   ├──  2023-12-14_19-23-58.log
│   ├──  2023-12-14_19-24-35.log
│   ├──  2023-12-14_19-26-53.log
│   ├──  2023-12-14_19-34-44.log
│   ├──  2023-12-14_19-35-06.log
│   ├──  2023-12-14_19-37-25.log
│   ├──  2023-12-14_20-13-27.log
│   ├──  2023-12-14_20-14-13.log
│   ├──  2023-12-15_15-47-56.log
│   ├──  2023-12-27_09-02-15.log
│   ├──  2023-12-27_09-03-12.log
│   ├──  2023-12-27_09-03-36.log
│   ├──  2023-12-27_09-04-08.log
│   ├──  2023-12-27_09-05-47.log
│   ├──  2023-12-27_09-06-19.log
│   ├──  2023-12-28_21-56-23.log
│   ├──  2023-12-28_21-57-11.log
│   ├──  2023-12-28_22-00-26.log
│   ├──  2023-12-28_22-03-37.log
│   ├──  2023-12-28_22-07-36.log
│   ├──  2023-12-28_22-08-45.log
│   ├──  2023-12-28_22-09-35.log
│   ├──  2023-12-28_22-12-17.log
│   ├──  2023-12-28_22-12-45.log
│   ├──  2023-12-28_22-14-16.log
│   ├──  2023-12-28_22-16-21.log
│   ├──  2023-12-28_22-22-38.log
│   ├──  2023-12-28_22-23-02.log
│   ├──  2023-12-28_22-24-46.log
│   ├──  2023-12-28_22-25-30.log
│   ├──  2023-12-28_22-32-42.log
│   ├──  2023-12-28_22-35-08.log
│   └──  2023-12-28_22-36-31.log
├──  README.md
├──  server
├──  test
│   └──  main.go
├── 󰌠 venv
│   ├──  bin
│   │   ├──  activate
│   │   ├──  activate.csh
│   │   ├──  activate.fish
│   │   ├──  activate.nu
│   │   ├──  activate.ps1
│   │   ├──  activate_this.py
│   │   ├──  pip
│   │   ├──  pip-3.11
│   │   ├──  pip3
│   │   ├──  pip3.11
│   │   ├──  python ⇒ /usr/bin/python3.11
│   │   ├──  python3 ⇒ python
│   │   ├──  python3.11 ⇒ python
│   │   ├──  wheel
│   │   ├──  wheel-3.11
│   │   ├──  wheel3
│   │   └──  wheel3.11
│   ├──  lib
│   │   └──  python3.11
│   └──  pyvenv.cfg
└──  web
    ├──  dist
    │   ├──  assets
    │   ├──  css
    │   ├──  favicon.ico
    │   ├──  font
    │   ├──  image
    │   ├──  index.html
    │   ├──  Login.html
    │   ├──  make.html
    │   ├──  painter.html
    │   └──  Template.html
    ├──  Dockerfile
    ├── 󰁯 Dockerfile.bak
    ├──  front
    │   ├──  index.html
    │   ├──  jsconfig.json
    │   ├──  node_modules
    │   ├──  package-lock.json
    │   ├──  package.json
    │   ├──  public
    │   ├──  README.md
    │   ├──  src
    │   └──  vite.config.js
    └──  nginx.conf
```

## 心得体会

学了一门新编程语言，过程中学习了Docker虚拟化技术，还算是有所收获。