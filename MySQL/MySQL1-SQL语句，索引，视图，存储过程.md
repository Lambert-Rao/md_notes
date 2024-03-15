

# 索引，视图，存储

[toc]

几点要搞清楚的事情

1. sql语句

2. index原理，B+tree，索引优化，索引失效，SQL优化

3. 事务，隔离级别，锁，MVCC，读异常，死锁

4. mysql与redis混合

5. tidb？pika？rocksdb？持久化？



## MySQL网络模型

### 两种事务处理机制

#### OTLP

(On-Line Transaction Procesing)

联机事务处理

#### OLAP

(On-Line Analytical Procesing)

联合分析，重在分析

![image-20230309131827672](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202303091318784.png)

Redis是单reactor模型，而mysql使用io多路复用`select`+阻塞io ,所以mysql具有跨平台性质

![线程分配](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202303091054767.png)

mysql每次连接分配一个线程，每次阻塞在一条线程上，所以mysql是多线程并发处理命令的

mysql是短链接，会主动断开连接

![SQL层次](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202303101340211.png)

### server层

#### 连接池connection pool

连接到达时mysql分配一条线程去处理它

> server的连接池：server并发连接mysql，mysql连接池接受它们

查权限，限制

#### 词法分析

生产语法树

#### 过滤

#### 优化器

优化执行顺序

#### cache & buffer

把热点数据缓存在内存中

#### 管理器

备份等等

### 引擎层

数据的存储和查询

#### 可插拔存储引擎

通常用InnoDB

> select中的几个过程：建立连接，管理连接，校验用户信息

## 数据库设计三范式，反范式

> 这是一种空间和时间的关系，适用于所有关系型数据库

> 三范式的目的：减小空间占用

#### 列不可分

ex：订单信息的地址：湖南省：长沙市：岳麓区，不要连在一起储存

#### 依赖主键

用来建立联合索引 

确保表中的每一列都和主键相关，避免冗余存储（一张表里出现大量相同内容），建立独立性

如果表中的几列和主键部分相关（主键为多个列联合索引时），把它们（某几个和主键中的一项相关）单独拆成一张表

#### 直接依赖

（在2的基础上），直接依赖于谁，就取谁作为主键，建立分表

#### 反范式

ex：用户表里面存在冗余，避免联表查询降低速度 

##### 常用模式
1. 行有唯一键
2. 字段不可再分
3. 数据允许相对冗余

## CRUD

> **Create, Read, Update, Delete**

### 执行过程

![image-20230311215203674](https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202303112152776.png)

### SQL

标准的语言

#### DQL-DataQueryLanguage

select

#### DML-DataManipulateLanguage

insert
update

#### DDL-DataDefineLanguage

create

alter

drop

#### DCL-DataControlLanguage

grant

revoke

#### TCL—TransactionControlLanguage

commit

rollback

#### 五大约束 constraints

`NOT NULL`

`AUTO_INCREAMENT`

`UNIQUE`

`PRIMARY`

`FOREIGN KEY`

> 外键约束在InnoDB中有效，其他引擎不一定有效

```SQL
FOREIGN KEY (`parent_id`) REFERENCES `parent`(id) 
ON DELETE CASE -- 在删除时
ON UPDATE CASE -- 在更新时
CASCADE		   -- 行为
```

```SQL
-- 行为
CASCADE 子表做同样行为
SET NULL 更新子表相应字段为NULL
NO ACTION / RESTRICT 父类做相应行为报错（不让做）
```

#### 删除数据

`DROP` Table

速度最快，删除整张表的表结构和表数据，包括所有的索引，约束，触发器

**不能回滚**，危险指令，删库跑路，我是说重构数据库的时候使用

`TRUNCATE`

**不能回滚**

较快，删除表数据，其他保留，保留索引约束，触发器

以页为单位删除

`DELETE`

能够回滚

慢，删除一部分数据，其他保留

逐行删除

```SQL
DELETE something WHERE condition
```

## 高级查询

#### 分组

````sql
SELECT COUNT()
FROM
WHERE
GROUP BY
````

GROUP BY也算是一种去重，通过聚合函数合并

#### 分页查询

分页查询主要用于查看第N条 到 第M条的信息,通常和排序查询
一起使用

使用limit关键字,第一个参数表示从条记录开始显示,第二个
参数表示要显示的数目。表中默认第一条记录的参数为0。

```SQL
SELECT * FROM `table` LIMIT 1,2;
```

#### 聚合

```SQL
SUM AVG COUNT MAX MIN
```

#### 联表查询

联表构建了一个新的集合(by COLUMN CONDITIONS)，在新的集合上进行`SELECT`

```SQL
JOIN ON
LEFT JOIN
RIGHT JOIN
INNER JOIN
CROSS JOIN
-- sample
SELECT * FROM users A
JOIN email e on A.email != e.email
```

`LEFT JOIN`用`NULL`填充出现而没有被联合的值

| a    | b    | c    | d    |
| ---- | ---- | ---- | ---- |
|      | aa   | NULL | NULL |
| 2    | bb   | 2    | xx   |
| 3    | cc   | NULL | NULL |
| 4    | dd   | 4    | yy   |
| 5    | ee   | NULL | NULL |

`CROSS JOIN`返回笛卡尔积的所有交叉结果

```SQL
-- 几种条件判断
SELECT UPDATE DELETE * WHERE CONDITION
GROUP BY COLUMN HAVING CONDITION
JOIN ON CONDITION
```

#### 子查询

```mysql
-- 单行子查询，认为结果是一个字段
SELECT * FROM course WHERE eacher_id = (select tip from teacher where name='Alice')
-- 多行子查询，认为结果是一张表
IN EXISTS ALL ANY FROM
select * from student where id in (select id from teacher)-- (临时生成的TABLE)
```

#### 正则

```SQL
SELECT * FROM `teacher` WHERE `tname` REGEXP '^
谢';
```

s

#### 流程控制

## 视图，触发器

通常只用`SELECT`构建临时表，因为限制多，容易出错，只做查询

#### 权限管理

用视图隐藏表结构，我给你视图，但不给你内部表结构

#### 减小网络IO

使用视图指令，减少数据包大小，节约网络资源

#### 重构

用户端只使用VIEW_TABLE，后台修改VIEW的逻辑

#### 触发器

对一张表进行DML，触发额外行为

> 监视对象: table
> 监视事件: insert 、 update 、 delete
> 触发时间: before , after
> 触发事件: insert 、 update 、 delete

```SQL
CREATE VIEW view_table AS SELECT
```

mysql是磁盘数据库，落盘才会返回，和Redis相同的请求回应模式

## 一些小技巧

用‘`’引名称避免被识别为关键字

> \`ID`



```SQL
SELECT sid,AVG(num) FROM score
WHERE num>60
GROUP BY sid
HAVING num>60
```

