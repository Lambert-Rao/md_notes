 作为已经使用c++一年的资深程序员，面对java工程无法下手，于是决定简单学一下java，简单总结一下学习过程，重点在于从c++迁移到java。

参照一下java核心技术(12ed)。

## 安装环境

```bash
sudo pacman -S jdk-openjdk
java --version
```

## 命令行运行程序

java的gcc呢？

```bash
[lambert@Laptop-Lambert src]$ javac Hello.java 
#javac是编译器，编译Hello.java
[lambert@Laptop-Lambert src]$ java Hello
java程序启动虚拟机，运行Hello，不要加class
Hello World
[lambert@Laptop-Lambert src]$ ls
-rw-r--r-- 1 lambert lambert 415  5月 3日 18:59 Hello.class
-rw-r--r-- 1 lambert lambert 118  5月 3日 17:15 Hello.java
```

```java
public class Hello{

    public static void  main(String[] args){
        System.out.println("Hello World");
    }
}
```

## 基本程序结构

类是程序逻辑的一个容器，定义了程序的行为。源代码文件使用public class相同的名字`Hello.java`。

> 所有函数都是某个类的方法。所以main函数有个壳类。
>
> 不使用main返回值做状态码。

### 数据类型

类型大小与机器无关

```java
int 
short
long
byte
//无unsigned
float
double
char//utf-16
boolean
enum
```

```java
int a = 3;
final int A =3;//const
static int b = 3;
enum Size {BIG,SMALL};
```

#### 类型转换

不允许损失精度的类型转换，强制转换

```java
double x = 3.3337;
int a = (int) x;
int b = (int) Math.round(x);
```

#### switch

```java
String num = switch (n)
{
        case 0 -> "Zero";
        case 1 -> "One";
        default -> "NaN";
}
```

switch是expression

#### 其他

位运算，关系运算都在。

```java
<<, >>算数移位
>>>逻辑移位
```

### 字符串

Unicode序列

```java
String str = "Lambert";
str.substring(0,3);//字符索引，没有截断字节问题
```

字符串不能修改

```java
String a = "Hello".substring(0, 3)+ "p!";
```

字符串可以共享访问

不能用`==`比较字符串，它比的是指针

```java
s.equal(t);
```

空串`""`不等于`null`

```java
"我".lengh()==1
```

p49 更多String api

#### 除此之外

String builder  p54

### 输入输出

```java
Scanner sc = new Scanner(System.in);
System.out.println("What's your name?");
String name = sc.nextLine();
// sc.next() 读一个词，还有其他的nextXX()方法
System.out.println("Hello " + name + "!");
```

保护密码的Console p57

#### 格式化

使用`System.out.printf("format");`来格式化输出

`String msg = String.format("");`来获得字符串

#### 文件

Scanner sc = new Scanner(Path.*of*("src/input.txt"), StandardCharsets.*UTF_8*);

### 控制流程

