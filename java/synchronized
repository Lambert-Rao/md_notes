# synchronized

## `synchronized`锁定的是什么元素？

- 修饰方法：

  - 静态方法：锁定class

  - 非静态：锁定方法的调用者实例

  这里锁定的是`data`, 也就是调用者。

 ``` java
 public class PlayGround {
     public static void main(String[] args) {
         Data data = new Data();
         data.print();
     }
 }
 
 class Data {
     public synchronized void print() {
         System.out.println("Data");
     }
 }
 ```

-  修饰代码块
  - 锁定的是传入的`Class`或者`instance`