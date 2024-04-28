# EPOLL

[toc]

#### 参考链接

https://www.cnblogs.com/fnlingnzb-learner/p/5835573.html

https://www.6aiq.com/article/1564634702930

## 基本概念

时间复杂度为$O(1)$

## 三个接口

#### int epoll_create(int size);

创建一个epoll集合，返回特殊描述符epfd

#### int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);

控制epfd中的元素，常用op是`EPOLLIN`,`EPOLLOUT`和`EPOLLDEL`

每次工作后及时切换模式

```cpp
ev.events = EPOLLOUT;
ev.data.fd = clientfd;
epoll_ctl(epfd, EPOLL_CTL_MOD, clientfd, &ev);
```

断联需要释放fd

```cpp
epoll_ctl(epfd, EPOLL_CTL_DEL, clientfd, nullptr);
close(clientfd);
```

#### int epoll_wait(int epfd, struct epoll_event * events, int maxevents, int timeout);ddff

### LT和ET

ET要额外` ev.events=EPOLLIN|EPOLLET;`