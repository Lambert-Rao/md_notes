

> 本文作者 张力涛





## 一、概念



1. MySQL：databases

1. 列：同类数据

1. 行：关联数据



## 二、语法



### 一、create



1.  create database (database's name) 创建数据库 

1.  create table (table's name)创建表 

1.  create table'name as select * from table's name 创建新表，并把另一张表的内容复制到表中 

1.  create index index's name on table's name(column's name) 创建索引 

1.  auto_increment 每次插入新纪录时，自动创建主键字段的值 

1. 插入新纪录时，主键字段会自动添加一个唯一的值
2. 默认的开始值为1，每条新记录递增1
3. alter table table's name auto_increment=number 让auto_increment序列以其他值起始

1.  数据类型： 

1. varchar(n) 字符串，最大长度为n（长度可变）
2. char(n) 字符串，最大长度为n（长度不可变，会自动填充空格）
3. int 整数值（没有小数点）
4. bigint 整数值（没有小数点）精度19
5. decimal(p,s) 精确数值，精度p，小数点后位数s（即小数点前有p-s位，小数点后有s位）
6. timestamp 存储年、月、日、小时、分、秒的值
7. ......



#### 约束



- not null 某列不能存储null值

- unique 该值具有唯一性

- primary key 主键（相当于not null和unique的结合）

- foreign key 外键（与另一个表中的值完全匹配）

- check 保证列中的值满足某个特定条件

- default 规定没有给列赋值时的默认值



### 二、select



1. select * from (table's name) 从表中提取所有数据

1. select (culumn's name) from (table's name) 从表中提取某一列所有的数据

1. select distinct (culumn's name) from (table's name) 从表中提取不同的数据

1. select count(*) from (table's name) 从表中提取所有数据的数量

1. select *&column's name from (table's name) where (condition) 从表中提取所有（或某一列的）（当列的数据为...)的数据 

- 包括：=（等于）,<（小于）,>（大于）,>=（小于或等于）,<=（大于或等于）,<>（不等于）,between...and...（在...和...之间）,like'...'（有...特征）,in（'...','...'）（为列指定多个可能的值）

- 通配符：%（替代多个字符）,_（替代一个字符）,charlist（字符列中任何单一字符）,^charlist & !charlist（不在字符列中的任何单一字符）

1. select column1's name, aggregate_function(column2's name) from table's name where condition group by column1's name 对column1进行分组（aggregate_function(column2's name)指对分组后的每个组执行的聚合函数
2. select column's name from table's name order by column's name ASC|DESC 排序（升序|降序）

- limit n 返回前n条记录
- offset m 跳过m条记录
- limit n，m 从第m条记录开始，返回前n条记录（相当于limt n offset m）
- union 连接两个或多个select语句的结果组合到一个结果集合，并去除重复的行（列数和数据类型必须相同）
- union all 连接两个或多个select语句的结果组合到一个结果集合，但不去除重复行（性能更好）



### 三、insert



1. insert into table's name values(value1,value2,...) 在表中插入值

1. insert into table'sname (column1,column2,...) values(value1,value2,...) 在表中某列插入值

1. insert into table's name select * from table's name 从一张表中提取值并复制到另一张已存在的表中



### 四、update



1. update table's name set column1=value1，column2=value2,... where condition 更新表中数据（condition用于指定哪个数据需要修改）



### 五、删除



1. delete from table‘s name where condition 删除表中某个数据（condition指定哪些数据需要删除）

1. drop index index' name on table's name 从表中删除索引

1. drop table table's name 删除表

1. drop database database's name 删除数据库

1. truncate table table's name 清空表的数据但保留表的结构（注意：表的主键自增值将被重置为默认的起始值）



### 六、alter



1. alter table table's name add column's name datatype 在某张表中添加列（datatype用于指定列的数据类型）

1. alter table table's name drop column column's name 删除某张表中的某一列

1. alter table table's name modify column column's name datatype 修改某张表中的数据类型



### 七、join



1. select column1's name,column2's name from table1's name inner join table2's name on table1's name.column1's name = table2's name.column2's name where condition 内连接（求交集）（condition 用于指定哪个数据需要被查询）

- select a.column1's name,b.column2's name from table1's name as a inner join table2's name as b on a.column1's name = b.column2's name



###  八、条件



1. and：二者必须同时成立

1. or：二者只要有一个成立即可



### 九、执行顺序



- FROM：确定数据来源，即指定表
- JOIN...ON：确定关联表和关联条件
- WHERE：指定过滤条件，过滤出满足条件的数据
- GROUP BY：按指定的字段对过滤后的数据进行分组
- HAVING：对分组之后的数据指定过滤条件
- SELECT：查找想要的字段数据
- DISTINCT：针对查找出来的数据进行去重
- ORDER BY：对去重后的数据指定字段进行排序
- LIMIT：对去重后的数据限制获取到的条数，即分页

![img](https://cdn.nlark.com/yuque/0/2024/webp/43172723/1712048116875-8f406751-c9bd-4e10-b0d4-fe388e9e308d.webp)



### 十、执行计划（explain）



1. id	值代表执行优先性，值越大，优先级越高，越优先执行；值相等可划分为一组，组内按从上往下的顺序依次执行（null值表示最后执行）
2. select_type	表示select查询的类型
   ● SIMPLE	最简单的select查询语句，查询中不含子查询和union等操作
   ● PRIMARY	查询中包含子查询，最外层将被标记为PRIMARY
   ● SUBQUERY	若select或where中包含了子查询，该查询将被标记为SUBQUERY
   ● MATERIALIZED	被物化的子查询，即针对对应的子查询将其物化为一个临时表
   ● DERIVED	若from中包含了子查询，该查询将被标记为DERIVED
   ● UNION	union操作中，查询中处于内层的select
   ● UNION RESULT	union操作的结果，代表一个结果集，对应的id为null值
3. table	代表对应步骤加载的是哪张表，对于临时表，最后的数字代表产生该表对应步骤的id
4. partitions	代表查询时匹配的分区信息，对于非分区表，值为null，对于分区表，值为对应的分区。
5. type		代表访问类型，查询性能排序如下：
   ● system > const > eq_ef > ref > fulltext > ref_or_null > index_merge > unique_subquery >index_subquery > range > index > ALL（常见）
   ● const >eq_ref > ref > range > index > ALL（实际开发）（通常至少要在range级别或以上）
   a. system	该表只有一行，相当于系统表
   b. const	该表最多有一个匹配的行，且读取位置为查询的开始（相当于指定了主键或唯一索引的值，并直接按照主键或唯一索引进行读取，或者连接的部分为一个常量）
   c. eq_ref	使用唯一性索引，即索引为主键（primary key）或唯一非 NULL 索引（unique key）, 表中只有一条记录与之匹配，where后面通常使用 = 来连接
   d. ref	区别于eq_ref，ref表示使用非唯一性索引，返回匹配的所有行
   e. fulltext	联接是使用索引执行的
   f. ref_or_null			类似于ref，区别在于ref_or_null会额外搜索包含null值的行
   g. index_merge		使用了两个以上的索引
   h. unique_subquery	替换in形式下子查询的eq_ref，让子查询返回不重复的集合
   i. index_subquery		区别于unique_subquery，替换in形式下子查询的ref，用于非唯一索引，可以返回重复值
   j. range	使用一个索引检索指定范围的行，where后面通常使用=,<,<=,>,>=,<=>,is null,between...and,in(),like等
   k. index	遍历索引树以找到匹配的行
   l. ALL	与index类似，但ALL是从硬盘读取，遍历全表以找到匹配的行
6. possible_keys	代表通过哪些索引，能让我们在表中找到想要的记录，即可能用到的索引，但实际查询中不一定能用到
7. key		区别于possible_keys，代表查询中实际使用到的索引，若没有使用索引，则为null值
8. key_len	代表查询用到的索引长度（字节数），原则上越短越好（只计算where条件中用到的索引长度，排序和分组中用到的索引长度不会计算）

- 单列索引	计算整个所引长度
- 多列索引	需要计算查询中实际使用到的列

1. ref		代表索引的哪些列被引用了，通常是对应字段或const（常量）
2. rows	代表根据表的统计信息和索引使用情况，估算要找到我们所需的信息，需要读取的行数（注意不是所需数据的行数）（原则上值越小越好）
3. filetered	代表数据经过过滤后，剩下满足条件的记录数量的比例（百分比的值）
4. Extra	额外的信息

1.  Using index		对应的select操作使用了覆盖索引，即查询的列被索引覆盖 

- 覆盖索引	我们所需要查询的数据（一个或几个字段）只需要通过索引就可以返回，而不必通过二级索引，查到主键之后再通过主键查询整行数据（即select*）
- 想要使用到覆盖索引，只能select需要的字段，且该字段建了索引，不可以select*

1.  Using where		查询时未找到可用的索引，进而通过 where 条件过滤获取所需数据（不是所有带 where 语句的查询都会显示 Using where ）
2. Using temporary	查询后结果需要用临时表来存储，一般在排序或分组查询时用到
3. Using filesort		表示无法利用索引完成的排序操作，即 order by 的字段没有索引（如果 order by 字段有索引就会用到覆盖索引，所以通常这样的SQL都是需要优化的）
4. Using join buffer	联表查询时，如果表的连接条件没有用到索引，就需要有一个连接缓冲区来存储中间结果
5. Impossible where	表示 where 语句不太正确，导致没有符合条件的行
6. No tables used	表示查询语句中没有 from 子句，或者有 from dual 子句