参照一下java核心技术(12ed)。

https://www.cnblogs.com/zhuyp1015/p/3702681.html

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

#### 数组

```java
int a[] = new int [10];
```

数据会自动初始化（0,false,null），访问有范围检查

复制数组是复制指针。

java只有一维数组，自建多维数组存储空间不连续。

#### 类型转换

不允许损失精度的类型转换，需要强制转换

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
//这样
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

`switch`仍然需要`break`

```java
int a = switch (b) {
            case 1 -> 1;
            case 2 -> {
                System.out.println("Hello");
                yield 2;}
            case 3 -> 3;
            default -> 5;
        };
```

我们可以在case中操作，但java没有rust那么智能，需要用`yield`来返回值。

```java
//另一种写法
switch (2) {
            case 1:
                b = 1;
            case 2: {
                System.out.println("Hello");
                b = 2;
            }
            case 3:
                b = 3;
            default:
                b = 5;
        };
```

如果要使用case x: 来判断，不加break就会一直执行下去。

java提供了标签break语法，很方便地跳出嵌套循环。

```java
label1:
        {
            if (con) break label1;
        }
```

大数 p77

java中不能自定义运算符重载。for,while都有，for each也有

```java
for (int element:collection) {
            System.out.println(i);
        }
```

### 命令行参数

```java
public static void main(String[] args)
```

```bash
java program -h
```

`args[0]=="-h"`，从实际参数开始

## 类

```java
Class ptr = new Class();
```

```java
class Person {
    public String name;
    private int age;
}
```

可变参数, 相当于数组

```java
class Group {
    private String[] names;

    public void setNames(String... names) {
        this.names = names;
    }
}
```

对象总是生成在堆上

```java
//继承
class Foo extends Bar
```

成员函数默认是虚函数，可以用`final`停止继承. 

```java
class Foo extends Bar {
    final void test();
}
```

纯虚函数

```java
abstract class Bar { public abstract void foo(); }
```



### 接口

比class更抽象的封装. 

### 迭代器

迭代器只是一个接口。 范围的开始是 <集合>.iterator，你必须用itr.hasNext()来查看是否到达集合尾。 使用itr.next()(是在C++中使用操作符++ 和*操作的结合)来获得下一个元素。 

```java
ArrayList myArrayList = new ArrayList();
Iterator itr = myArrayList.iterator();
while ( itr.hasNext() )
{
 System.out.println( itr.next() );
}
```

```java
ArrayList myArrayList = new ArrayList();
        for (Object o : myArrayList) {
            System.out.println(o);
        }
```

