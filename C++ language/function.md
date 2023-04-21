```c++
#include <functional>
#include <iostream>
#include <memory>

using namespace std;

template <typename... Args>
using Callback = function<void(Args...)>;

class XBaseSocket {
 public:
  template <typename Func>
  void SetCallback(Func &&func) {
    callback_ = std::forward<Func>(func);
  }
  template <typename... Args>
  void UseCallback(Args... args) {
    std::apply(callback_, std::forward_as_tuple(args...));
  }
  XBaseSocket() { cout << "XBaseSocket" << endl; }
  ~XBaseSocket() { cout << "~XBaseSocket" << endl; }
  auto ShareSocket() {
    return make_shared<XBaseSocket>(*this);
  }

 private:
  Callback<int, int> callback_{};  // Specify the parameter types for the callback
};

int main() {
  XBaseSocket socket;
  int a = 10;
  int b = 20;
  socket.SetCallback([a, b](int c, int d) { std::cout << a + b + c + d << std::endl; });
  a = 20;
  socket.UseCallback(a, a);
}
```
在这段代码中，为了能在运行时调用参数，我们必须事前指定参数类型`Callback<int, int> callback_{};`不过`[捕获]`的数据可以随意使用。