# list



## 应用

### bin箱排

把要排的数据分成箱,每个箱装数据相同的元素链,排完之后把每个箱的元素逐个连接起来

```cpp
#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <map>

using namespace std;

template<typename T>
class Node
{
private:
	int hash = 0;
	T member;
	Node* previous = nullptr;
	Node* successor = nullptr;
	T* content = nullptr;
};
template<typename T>
class list
{
	friend Node<T>;
	void bin_sort()
	{
		//create the bin
		vector<Node<T>> bottom;
		vector<Node<T>> top;

		for (Node<T>* i = first; i != last; i = i->successor)
		{
			int bin = i->hash;
			if (bottom[bin].empty())
				bottom[bin] = top[bin] = i;
			else
			{
				top[bin].successor = i;
				top[bin] = i;
			}

		}
		Node<T>* y = nullptr;
		for (size_t i = 0; i < size; ++i)
			if (bottom[i] != nullptr)
				//not empty
			{
				if (y == nullptr)
					first = bottom[i];
				else
					y->successor = i;
				y = top[i];

			}
		if (y != nullptr)
			y->successor = nullptr;

		delete[] bottom;
		delete[] top;
	}
private:
	size_t size;
	Node<T>* first;
	Node<T>* last;
};
class Info
{
public:
	int number;
};

int main()
{

}
```



### 基数排序p135

确定基数(radix),r.排序范围R,元素个数x,将这R内的x元素分几次以r为底的bin排,

