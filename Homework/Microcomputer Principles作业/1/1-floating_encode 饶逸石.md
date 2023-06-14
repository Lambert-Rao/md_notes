## 浮点数编码

今日闲来无事，写一下陈老师作业，哎呀，不知道陈老师留了些甚么作业，不妨看看群里怎么说，<img src="https://raw.githubusercontent.com/Limpol-Rao/image_host/main/img/202303031548213.png" alt="image-20230303154839185" style="zoom: 50%;" />，好，我们就按这位同学说的，写一下作业。

什么叫带小数点，就是浮点数呗，转二进制？我懂了，我已经理解了一切，这是在问我浮点数的编码啊，

后来我想了一下，好像理解错了，其实这里问的是把小数点前后分别转二进制。

### d2b flaot

> 1. 将整数部分转换为二进制。使用除以2取余数法，将整数部分不断除以2并记录余数，直到商为0为止。最后将记录的余数倒序排列即可得到二进制整数部分。
> 2. 将小数部分转换为二进制。使用乘以2取整数法，将小数部分不断乘以2并取整数部分，直到小数部分为0或者达到所需精度为止。将记录的整数部分按顺序排列即可得到二进制小数部分。
> 3. 将整数部分和小数部分合并。将二进制整数部分和小数部分用小数点连接起来即可得到最终的二进制表示。

那我这么闲，写个代码实现一下吧

```c++
string int_part_covert(int n,string s="")
{
    if(n==0)
        return s;
    else
    {
        s= (n%2?"1":"0")+ s;
        n/=2;
        return int_part_covert(n,s);
    }
}
string decimal_part_convert(double num, int precision)
{
    string result = ".";
    while(precision-- > 0)
    {
        num *= 2;
        if(num >= 1)
        {
            result += "1";
            num -= 1;
        }
        else
        {
            result += "0";
        }
    }
    return result;
}
string d2b(double a)
{
    int int_part = static_cast<int> (a);
    double decimal_part = a - int_part;
    return int_part_covert(int_part)+ decimal_part_convert(decimal_part,8);
}
```

在ChatGPT的帮助下写完了，我的手指仿佛一个世纪都没有写代码一样僵硬。

### 那么，现在复习一下IEEE 754

$$
V=(-1)^s\times M \times 2^E
$$

sign s决定正负

significand（这怎么起的名？重要部分？） M是一个二进制小数 $$1\sim1-\varepsilon$$

exponent E对浮点数加权 

在double中上面三段分别编码为1,11,52位。这个编码的主要思想是二进制科学计数法，M表示基数，E表示阶数。

这里浮点的编码分为四种情况：

1. 规格化，表示一个$$\left[1,2\right)$$的数呈上$$2^E$$，这个E是可以从负到正的，规格化数在原点附近更密集。
2. 非规格化，一组等差的数，集中在原点附近，用e置0表示
3. 特殊值，INF和NaN

简单写了一下，这个编码是真有意思。
