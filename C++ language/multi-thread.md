###  thread

`thread.detach()`的话，句柄`t1` 已经无法管理这个线程了。当主线程结束，进程就结束了，线程没运行完。

thread是可以`std::move(t0)`的，转移控制权。

```c++
//this_thread functions
std::this_thread::get_id();
//让出当前线程
std::this_thread::yield();
std::this_thread::sleep_until (chrono::system_clock::now()+chrono::seconds(3));
std::this_thread::sleep_for(std::chrono::seconds(1));
```



###  mutex

```cpp
#include <functional>
#include <iostream>
#include <memory>
#include <tuple>
#include <chrono>
#include <map>
#include <future>
#include <condition_variable>

using namespace std;

class Tick {
 public:
  chrono::system_clock::time_point g_time_point;
  void producer(chrono::milliseconds t) {
    while (true) {
      unique_lock<mutex> lock(mutex_);
      g_time_point = chrono::system_clock::now();
      lock.unlock();
      this_thread::sleep_for(t);
    }
  };
  void consumer() {
    while (true) {
      cout << chrono::duration_cast<chrono::milliseconds>(g_time_point.time_since_epoch()).count() << endl;
      this_thread::sleep_for(500ms);
    }
  };
 private:
  mutex mutex_;

};

int main() {
  Tick tick;
  thread t1(&Tick::producer, &tick, 300ms);
  thread t3(&Tick::producer, &tick, 1000ms);
  thread t2(&Tick::consumer, &tick);
  t1.join();
}
```

注意看这段代码，我创建了两个生产者，一个消费者，然后通过循环的方式取出数据，为了传递消息，我不得不使用全局变量，这样的实现会导致消费者取出数据存在时间偏差。

### std::condition_variable

> std::condition_variable_any更加通用,这就可能产生额外的开销,所以std::condition_variable一般作为首选的类型

```c++
#include <functional>
#include <iostream>
#include <memory>
#include <tuple>
#include <chrono>
#include <map>
#include <future>
#include <condition_variable>
#include <queue>

using namespace std;

class Tick {
 public:
  void producer (chrono::milliseconds t)
  {
    while (true)
      {
        this_thread::sleep_for (t);
        unique_lock<mutex> lock (mutex_);
        msg_.push (chrono::system_clock::now ());
        con_var_.notify_one ();
      }
  };
  void consumer ()
  {
    while (true) {
        unique_lock<mutex> lock (mutex_);
        con_var_.wait (lock, [this] { return !msg_.empty (); });
      while (!msg_.empty()) {
        cout << chrono::duration_cast<chrono::milliseconds>(msg_.front().time_since_epoch()).count() << endl;
        msg_.pop();
      }
      lock.unlock();
      this_thread::sleep_for(1000ms);
    }
  };
 private:
  mutex mutex_;
  queue<chrono::system_clock::time_point> msg_;
  condition_variable con_var_;
};

int main ()
{
  Tick tick;
  cout<<"start point\n"<<chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count()<<endl;
  thread t1 (&Tick::producer, &tick, 300ms);
  thread t3 (&Tick::producer, &tick, 500ms);
  thread t2 (&Tick::consumer, &tick);
  t3.join ();
}
```

这里我们把代码修改为使用消息队列和条件变量的形式。

生产者线程在上锁后，把数据写入到消息队列，然后解锁。

消费者线程先上锁，然后`condition.wait()`，wait传入锁和条件谓词函数，判断失败会释放锁进入等待状态，判断成功则会重新获取锁，进入下面的操作，从消息队列中取出数据，注：取出之后再处理可以减小锁的粒度。

等到下一次有`notify`的时候，`wait()`会被唤醒，重新做检查。

> TODO：线程安全队列？p100

### future

问题引入

```c++
mutex m_result;
condition_variable cv_result;

void task(int a, int b, int &res) {
  unique_lock<mutex> lg(m_result);
  a *= 2;
  b *= 3;
  res = a + b;
  cv_result.notify_one();
}

int main() {
  int result{};
  thread t1(task, 1, 2, ref(result));
  cout << "result: " << result << endl;
  unique_lock<mutex> lg(m_result);
  cv_result.wait(lg, [&result] { return result != 0; });
  cout << "result: " << result << endl;
  t1.join();
}
```

为了异步地获取一个计算结果，我们需要开启一个线程，在函数中传递一个引用，为了保护变量需要加锁，为了不被阻塞，需要加条件变量，这样很**麻烦**。

我们介绍标准库的组件`<future>`.

由于运算速度问题我们有时候不能马上得到结果，这时需要启动一个异步任务，并在任务结束后取回结果，这就是`async`，`async`返回一个`future`对象，可以使用`get()`方法获取结果，此时会阻塞在`caller`线程。

```c++
int main() {
  auto future_time = async(Tick::Wait);//bind future and async:nonblocked here
  cout << "current time point:\n" << Tick::Now() << endl;
  this_thread::sleep_for(1s);
  cout << "current time point:\n" << Tick::Now() << endl;
  cout << "the time is: \n" << future_time.get() << endl;//blocked
}
```
使用`wait()`可以等待运行结束再继续，类似于`thread.join()`

```c++
int main() {
  auto future_time = async(Tick::Wait);
  cout << "current time point:\n" << Tick::Now() << endl;
  this_thread::sleep_for(1s);
  future_time.wait();
  cout << "current time point:\n" << Tick::Now() << endl;
  cout << "the time is: \n" << future_time.get() << endl;
}
```

注意：`future.get()`只能调用一次。

通过额外向 `async()`传入`std::launch::deferred`参数，可以使得任务被延迟到`wait()`或`get()`执行，而且是在调用者线程执行。

```c++
auto future_time = async(launch::deferred,Tick::Wait);
```

如果不调用甚至不会创建执行函数，所以务必把需要修改的变量作为返回值。

> 优先选用基于任务而非基于线程：基于任务提供了比基于线程更高的抽象级别，不需要进行线程管理
>

#### `std::package_task`

通过`std::package_task`把各种callable obk包装起来，方便作为线程入口。

```c++
int main() {
  packaged_task task(Tick::Wait);
  thread t1(std::ref(task));
  future result = task.get_future();
  t1.join();
  cout << result.get() << endl;
}
```

包装一个函数，然后丢入线程，获取future对象，等待线程结束，从future拿到结果。

####   `std::promise`

```c++
int Calculate(promise<int> &pr) {
  this_thread::sleep_for(2s);
  pr.set_value(1);
  return 0;
}
int main() {
  promise<int> pr;
  thread t1(Calculate, std::ref(pr));
  t1.join();
  auto f = pr.get_future();
  cout << f.get() << endl;
}
```

### 原子操作`<atomic>`

