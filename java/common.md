```java
import java.util.*; // 导入java.util包中的所有类，例如List、Map、Set等
import java.io.*; // 导入java.io包中的所有类，例如File、InputStream、OutputStream等
import java.net.*; // 导入java.net包中的所有类，例如URL、URLConnection等
import java.lang.*; // 导入java.lang包中的所有类，例如String、Object、Math等
import java.math.*; // 导入java.math包中的所有类，例如BigInteger、BigDecimal等
import java.text.*; // 导入java.text包中的所有类，例如DateFormat、NumberFormat等
import java.time.*; // 导入java.time包中的所有类，例如LocalDate、LocalTime、Instant等
```

```java
Scanner in = new Scanner(System.in);
while(scan.hasNextLine())
int n = in.nextInt();
String s = in.nextLine();
```

```java
int[] array = new int[10]; 
int[] array = {1, 2, 3, 4, 5}; 
Arrays.sort(array);
int[] copiedArray = Arrays.copyOf(array, array.length); // 复制数组
boolean isEqual = Arrays.equals(array1, array2); // 比较两个数组是否相等
String arrayStr = Arrays.toString(array); // 将数组转换为字符串
```

```java
// 将数字转换为二进制字符串
int num = 10;
String binaryString = Integer.toBinaryString(num);
System.out.println(binaryString); // 输出 "1010"

// 将二进制字符串转换为数字
String binaryString = "1010";
int num = Integer.parseInt(binaryString, 2);
```

```java
// 创建一个String
String str = "Hello World";
// 获取字符串的长度
int length = str.length();
// 获取字符串中的某个字符
char ch = str.charAt(0); // 获取第一个字符

// 获取子字符串
String subStr = str.substring(1, 4); // 获取从第1个字符到第3个字符的子字符串
// 检查字符串是否包含某个子字符串
boolean contains = str.contains("World");
// 替换字符串中的字符或子字符串
String replacedStr = str.replace("World", "Java");

// 将字符串转换为字符数组
char[] charArray = str.toCharArray();

// 创建一个StringBuilder
StringBuilder sb = new StringBuilder();

// 添加字符串
sb.append("Hello");
sb.append(" ");
sb.append("World");

// 插入字符串
sb.insert(5, " Java");

// 删除字符串
sb.delete(5, 10);

// 反转字符串
sb.reverse();

// 获取StringBuilder的长度
int sbLength = sb.length();

// 将StringBuilder转换为String
String sbStr = sb.toString();
```

```java
import java.util.ArrayList;

// 创建一个空的ArrayList
ArrayList<String> list = new ArrayList<String>();

// 添加元素
list.add("Hello");
// 在指定位置添加元素
list.add(1, "Java");

// 获取元素
String element = list.get(0); // 获取第一个元素
// 修改元素
list.set(0, "Hi"); // 将第一个元素修改为"Hi"
// 删除元素
list.remove(0); // 删除第一个元素

// 获取ArrayList的大小
int size = list.size();
// 检查ArrayList是否为空
boolean isEmpty = list.isEmpty();

// 清空ArrayList
list.clear();

// 检查ArrayList是否包含某个元素
boolean contains = list.contains("World");

// 将ArrayList转换为数组
String[] array = list.toArray(new String[0]);

// 遍历ArrayList
for(String str : list) {
    System.out.println(str);
}
```

```java
import java.util.HashSet;
import java.util.Set;

// 创建一个空的Set
Set<String> set = new HashSet<String>();

// 添加元素
set.add("Hello");
set.add("World");

// 检查Set是否包含某个元素
boolean contains = set.contains("World");

// 删除元素
set.remove("Hello");

// 获取Set的大小
int size = set.size();

// 检查Set是否为空
boolean isEmpty = set.isEmpty();

// 清空Set
set.clear();

// 遍历Set
for(String str : set) {
    System.out.println(str);
}
```


```java
import java.util.HashMap;
import java.util.Map;

// 创建一个空的Map
Map<String, Integer> map = new HashMap<String, Integer>();

// 添加元素
map.put("one", 1);
map.put("two", 2);

// 获取元素
Integer value = map.get("one");

// 检查Map是否包含某个键
boolean containsKey = map.containsKey("one");
// 检查Map是否包含某个值
boolean containsValue = map.containsValue(1);

// 删除元素
map.remove("one");

// 获取Map的大小
int size = map.size();
// 检查Map是否为空
boolean isEmpty = map.isEmpty();

// 清空Map
map.clear();

// 遍历Map的键
for(String key : map.keySet()) {
    System.out.println(key);
}

// 遍历Map的值
for(Integer val : map.values()) {
    System.out.println(val);
}

// 遍历Map的键值对
for(Map.Entry<String, Integer> entry : map.entrySet()) {
    System.out.println(entry.getKey() + ": " + entry.getValue());
}

// 使用getOrDefault获取元素，如果键不存在，则返回默认值
Integer value = map.getOrDefault("three", 3);
System.out.println(value); // 输出 "3"
```

```java
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

// 创建一个List
List<Integer> list = Arrays.asList(1, 2, 3, 4, 5);

// 使用Lambda表达式遍历List
list.forEach(item -> System.out.println(item));

// 使用Stream和Lambda表达式过滤List
List<Integer> filteredList = list.stream()
    .filter(item -> item > 2)
    .collect(Collectors.toList());

// 使用Stream和Lambda表达式对List进行映射操作
List<Integer> mappedList = list.stream()
    .map(item -> item * 2)
    .collect(Collectors.toList());

// 使用Stream和Lambda表达式对List进行归约操作
int sum = list.stream()
    .reduce(0, (a, b) -> a + b);

// 使用Stream和Lambda表达式对List进行排序
List<Integer> sortedList = list.stream()
    .sorted((a, b) -> b - a)
    .collect(Collectors.toList());
```

```java
// 计算绝对值
int absValue = Math.abs(-10); // 输出 "10"
double absValueDouble = Math.abs(-10.6); // 输出 "10.6"

// 计算平方根
double sqrtValue = Math.sqrt(16); // 输出 "4.0"

// 计算立方根
double cbrtValue = Math.cbrt(27); // 输出 "3.0"

// 计算乘方
double powValue = Math.pow(2, 3); // 输出 "8.0"

// 计算最大值和最小值
int maxValue = Math.max(5, 9); // 输出 "9"
int minValue = Math.min(5, 9); // 输出 "5"

// 计算随机数
double randomValue = Math.random(); // 输出一个0.0到1.0之间的随机数

// 计算正弦、余弦和正切
double sinValue = Math.sin(Math.PI / 2); // 输出 "1.0"
double cosValue = Math.cos(Math.PI / 2); // 输出 "0.0"
double tanValue = Math.tan(Math.PI / 4); // 输出 "1.0"

// 计算四舍五入
long roundValue = Math.round(10.6); // 输出 "11"
// 计算自然指数
double expValue = Math.exp(1); // 输出 "2.718281828459045"
// 计算自然对数
double logValue = Math.log(Math.E); // 输出 "1.0"
// 计算以10为底的对数
double log10Value = Math.log10(100); // 输出 "2.0"
// 计算以2为底的对数
double log2Value = Math.log(4) / Math.log(2); // 输出 "2.0"
// 计算指数函数减1的值
double expm1Value = Math.expm1(1); // 输出 "1.718281828459045"
// 计算自然对数加1的值
double log1pValue = Math.log1p(Math.E - 1); // 输出 "1.0"
```