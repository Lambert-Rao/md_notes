









# 中南大学

# 自动化学院 语音信号处理课程实验报告



















> 专业	人工智能
>
> 班级	智能2103
>
> 姓名	饶逸石
>
> 学号	8207210519











## 高斯混合模型

### 代码解释

```python
# 初始化模型参数
# shape 是表示样本规模的二元组，(样本数, 特征数)
# K 表示模型个数
def init_params(shape, K):
    N, D = shape
    mu = np.random.rand(K, D)
    cov = np.array([np.eye(D)] * K)
    alpha = np.array([1.0 / K] * K)
    print("Parameters initialized.")
    print("mu:", mu, "cov:", cov, "alpha:", alpha, sep="\n")
    return mu, cov, alpha
这段代码的作用是初始化高斯混合模型的参数。高斯混合模型是一种聚类算法，它假设所有的数据都是由K个高斯分布混合而成的。

函数`init_params`接收两个参数：`shape`和`K`。`shape`是一个二元组，表示样本的规模，其中`N`是样本数，`D`是特征数。`K`表示模型的个数，也就是高斯分布的个数。

函数首先根据`shape`解包出`N`和`D`。然后，它初始化三个参数：`mu`、`cov`和`alpha`。

- `mu`是一个`K x D`的矩阵，表示每个高斯分布的均值。它是通过`np.random.rand(K, D)`生成的，所以每个元素都是在0到1之间的随机数。

- `cov`是一个`K x D x D`的张量，表示每个高斯分布的协方差矩阵。它是通过`np.array([np.eye(D)] * K)`生成的，所以每个高斯分布的协方差矩阵都是`D x D`的单位矩阵。

- `alpha`是一个长度为`K`的数组，表示每个高斯分布的权重。它是通过`np.array([1.0 / K] * K)`生成的，所以每个高斯分布的权重都是`1/K`。

最后，函数打印出这三个参数，并返回它们。
```

```python
def phi(Y, mu_k, cov_k):
    norm = mul_nor_1(mean=mu_k, cov=cov_k)
    return norm.pdf(Y)
这段代码定义了一个函数phi，它用于计算高斯混合模型中的某个高斯分布在给定数据点上的概率密度。

函数phi接收三个参数：Y、mu_k和cov_k。

Y是一个数据点。
mu_k是高斯分布的均值。
cov_k是高斯分布的协方差矩阵。
函数首先创建一个多元正态分布norm，其均值为mu_k，协方差矩阵为cov_k。这是通过调用mul_nor_1(mean=mu_k, cov=cov_k)实现的，其中mul_nor_1应该是一个创建多元正态分布的函数。

然后，函数返回norm.pdf(Y)，即数据点Y在norm分布下的概率密度。这是通过调用多元正态分布的pdf方法实现的。pdf是Probability Density Function的缩写，表示概率密度函数。
```

```python
# E 步：计算每个模型对样本的响应度
# Y 为样本矩阵，每个样本一行，只有一个特征时为列向量
# mu 为均值多维数组，每行表示一个样本各个特征的均值
# cov 为协方差矩阵的数组，alpha 对应的每个高斯模型的权重数组

def getExpectation(Y, mu, cov, alpha):
    # 样本数
    N = Y.shape[0]
    # 模型数
    K = alpha.shape[0]

    # 为避免使用单个高斯模型或样本，导致返回结果的类型不一致
    # 因此要求样本数和模型个数必须大于1
    assert N > 1, "There must be more than one sample!"
    assert K > 1, "There must be more than one gaussian model!"

    # 响应度矩阵，行对应样本，列对应响应度
    gamma = np.mat(np.zeros((N, K)))

    # 计算各模型中所有样本出现的概率，行对应样本，列对应模型
    prob = np.zeros((N, K))
    for k in range(K):
        prob[:, k] = phi(Y, mu[k], cov[k])
    prob = np.mat(prob)

    # 计算每个模型对每个样本的响应度
    for k in range(K):
        gamma[:, k] = alpha[k] * prob[:, k]
    for i in range(N):
        gamma[i, :] /= np.sum(gamma[i, :])
    return gamma
这段代码定义了一个函数getExpectation，它用于计算高斯混合模型的E步骤，即期望步骤。在这个步骤中，我们计算每个模型对每个样本的响应度。

函数getExpectation接收四个参数：Y、mu、cov和alpha。

Y是样本矩阵，每行表示一个样本，只有一个特征时为列向量。
mu是均值多维数组，每行表示一个样本各个特征的均值。
cov是协方差矩阵的数组。
alpha是每个高斯模型的权重数组。
函数首先获取样本数N和模型数K，然后创建一个N x K的零矩阵gamma，用于存储每个模型对每个样本的响应度。

然后，函数计算每个模型对每个样本的概率，存储在矩阵prob中。这是通过调用之前定义的函数phi实现的。

接着，函数计算每个模型对每个样本的响应度，存储在矩阵gamma中。响应度是模型的权重和模型对样本的概率的乘积，然后除以所有模型对该样本的响应度之和，以确保响应度之和为1。

最后，函数返回响应度矩阵gamma。
```

```python
# M 步：迭代模型参数
# Y 为样本矩阵，gamma 为响应度矩阵
def maximize(Y, gamma):
    # 样本数和特征数
    N, D = Y.shape
    # 模型数
    K = gamma.shape[1]

    #初始化参数值
    mu = np.zeros((K, D))
    cov = []
    alpha = np.zeros(K)

    # 更新每个模型的参数
    for k in range(K):
        # 第 k 个模型对所有样本的响应度之和
        Nk = np.sum(gamma[:, k])
        # 更新 mu
        # 对每个特征求均值
        mu[k, :] = np.sum(np.multiply(Y, gamma[:, k]), axis=0) / Nk
        # 更新 cov
        cov_k = (Y - mu[k]).T * np.multiply((Y - mu[k]), gamma[:, k]) / Nk
        cov.append(cov_k)
        # 更新 alpha
        alpha[k] = Nk / N
    cov = np.array(cov)
    return mu, cov, alpha
这段代码定义了一个函数maximize，它用于计算高斯混合模型的M步骤，即最大化步骤。在这个步骤中，我们根据每个模型的响应度来更新模型的参数。

函数maximize接收两个参数：Y和gamma。

Y是样本矩阵，每行表示一个样本，只有一个特征时为列向量。
gamma是响应度矩阵，每行对应一个样本，每列对应一个模型。
函数首先获取样本数N、特征数D和模型数K，然后初始化参数mu、cov和alpha。

然后，函数遍历每个模型，更新该模型的参数。更新的方法如下：

计算第k个模型对所有样本的响应度之和Nk。
更新均值mu。这是通过计算每个样本的特征值与其对应的响应度的乘积的总和，然后除以Nk实现的。
更新协方差矩阵cov。这是通过计算每个样本的特征值减去均值的结果，然后乘以其对应的响应度，再除以Nk实现的。
更新权重alpha。这是通过计算Nk除以样本总数N实现的。
最后，函数返回更新后的参数mu、cov和alpha。
```

```python
# 高斯混合模型 EM 算法
# 给定样本矩阵 Y，计算模型参数
# K 为模型个数
# times 为迭代次数
# 返回每个高斯模型的参数数组和对应的权值数组

def GMM_EM(Y, K, times):    
    mu, cov, alpha = init_params(Y.shape, K)
    for i in range(times):
        gamma = getExpectation(Y, mu, cov, alpha)
        mu, cov, alpha = maximize(Y, gamma)
    print("{sep} Result {sep}".format(sep="-" * 20))
    print("mu:", mu, "cov:", cov, "alpha:", alpha, sep="\n")
    return mu, cov, alpha
这段代码定义了一个函数GMM_EM，它实现了高斯混合模型的EM（Expectation-Maximization）算法。EM算法是一种迭代算法，用于找到高斯混合模型的参数，使得对给定的样本数据的似然函数的值最大。

函数GMM_EM接收三个参数：Y、K和times。

Y是样本矩阵，每行表示一个样本，只有一个特征时为列向量。
K是模型的个数，也就是高斯分布的个数。
times是迭代的次数。
函数首先调用init_params函数初始化模型的参数mu、cov和alpha。

然后，函数进入一个循环，循环times次。在每次循环中，函数先调用getExpectation函数计算每个模型对每个样本的响应度gamma，然后调用maximize函数更新模型的参数。

最后，函数打印出最终的模型参数，并返回它们。

这个函数实现的是EM算法的基本流程：首先初始化模型参数，然后交替进行E步骤（计算响应度）和M步骤（更新参数），直到满足停止条件（在这个函数中，停止条件是迭代达到指定的次数）。
```

```python
def gen_data():
    cov1 = np.mat("0.3 0;0 0.1")
    cov2 = np.mat("0.2 0;0 0.3")

    mu1 = np.array([0, 1])
    mu2 = np.array([2, 1])

    sample = np.zeros((100, 2))
    sample[:30, :] = mul_nor_2(mean=mu1, cov=cov1, size=30)
    sample[30:, :] = mul_nor_2(mean=mu2, cov=cov2, size=70)
    np.savetxt("sample.data", sample)

    plt.plot(sample[:30, 0], sample[:30, 1], "bo")
    plt.plot(sample[30:, 0], sample[30:, 1], "rs")
    plt.show()
gen_data()
```

```python
# 数据预处理
# 将所有数据都缩放到 0 和 1 之间
def scale_data(Y):
    # 对每一维特征分别进行缩放
    for i in range(Y.shape[1]):
        max_ = Y[:, i].max()
        min_ = Y[:, i].min()
        Y[:, i] = (Y[:, i] - min_) / (max_ - min_)
    
    return Y
```

```python
def test_gauss():    
    # 载入数据
    Y = np.loadtxt("sample.data")
    matY = np.matrix(Y, copy=True)

    # 模型个数，即聚类的类别个数
    K = 2

    # 数据预处理
    Y= scale_data(Y)

    # 计算 GMM 模型参数
    mu, cov, alpha = GMM_EM(matY, K, 100)

    # 根据 GMM 模型，对样本数据进行聚类，一个模型对应一个类别
    N = Y.shape[0]
    
    # 求当前模型参数下，各模型对样本的响应度矩阵
    gamma = getExpectation(matY, mu, cov, alpha)
    
    # 对每个样本，求响应度最大的模型下标，作为其类别标识
    category = gamma.argmax(axis=1).flatten().tolist()[0]
    
    # 将每个样本放入对应类别的列表中
    class1 = np.array([Y[i] for i in range(N) if category[i] == 0])
    class2 = np.array([Y[i] for i in range(N) if category[i] == 1])

    # 绘制聚类结果
    plt.plot(class1[:, 0], class1[:, 1], 'rs', label="class1")
    plt.plot(class2[:, 0], class2[:, 1], 'bo', label="class2")
    plt.legend(loc="best")
    plt.title("GMM Clustering By EM Algorithm")
    plt.show()
    
test_gauss()
```

### 分析高斯混合模型的基本原理及建模过程

高斯混合模型（Gaussian Mixture Model，GMM）是一种聚类算法，它假设数据是由多个高斯分布的混合生成的。每个高斯分布被称为一个组件，每个组件都有自己的均值和协方差。GMM的目标是学习每个组件的参数（均值和协方差）以及每个组件的权重。

GMM的基本原理是使用最大似然估计法来估计参数。由于直接计算最大似然估计是困难的，所以通常使用EM（Expectation-Maximization）算法来迭代地估计参数。

GMM的建模过程如下：

1. **初始化**：选择模型的组件数，然后随机初始化每个组件的参数（均值和协方差）和权重。
2. **E步骤**：使用当前的模型参数，计算每个样本属于每个组件的后验概率。这个后验概率也被称为响应度。
3. **M步骤**：使用计算出的响应度，重新估计每个组件的参数和权重。具体来说，每个组件的权重是所有样本对该组件的响应度的平均值，均值是每个样本的值乘以其对该组件的响应度的总和除以所有样本对该组件的响应度的总和，协方差是每个样本的值减去均值的平方乘以其对该组件的响应度的总和除以所有样本对该组件的响应度的总和。
4. **迭代**：重复E步骤和M步骤，直到模型参数收敛，或者达到预设的最大迭代次数。

GMM是一种软聚类算法，它可以给出每个样本属于每个组件的概率。这使得GMM能够处理属于多个组件的样本，也使得GMM能够处理形状为椭圆的聚类。

## 隐马尔科夫词性标注

```python
import os
file_path =os.path.join(os.getcwd(),"./data2/corpus_POS.txt" )#数据路径
```

```python
start_c={}#开始概率，就是一个字典，state:chance=Word/lines
transport_c={}#转移概率，是字典：字典，state:{state:num,state:num....}   num=num(state1)/num(statess)
emit_c={}#观测概率，也是一个字典，state:{word:num,word,num}  num=num(word)/num(words)
这段代码定义了三个字典，它们分别用于存储隐马尔可夫模型（HMM）的三个基本参数：初始状态概率、转移概率和发射概率。

start_c = {}：这个字典用于存储初始状态概率。键是状态，值是该状态的概率。这个概率是通过计算某个状态作为起始状态的次数除以总的行数得到的。

transport_c = {}：这个字典用于存储转移概率。它是一个嵌套的字典，外层字典的键是状态，值是另一个字典。内层字典的键是状态，值是从外层字典的状态转移到内层字典的状态的次数。这个概率是通过计算某个状态转移到另一个状态的次数除以总的状态转移次数得到的。

emit_c = {}：这个字典用于存储发射概率。它也是一个嵌套的字典，外层字典的键是状态，值是另一个字典。内层字典的键是观测值（例如，单词），值是在给定外层字典的状态下，观测到内层字典的观测值的次数。这个概率是通过计算在某个状态下观测到某个观测值的次数除以在该状态下观测到的所有观测值的次数得到的。
```

```python
Count_dic = {}  # 一个属性下的所有单词，为了求解emit
state_list = ['Ag', 'a', 'ad', 'an', 'Bg', 'b', 'c', 'Dg',
'd', 'e', 'f', 'h', 'i', 'j', 'k', 'l',
'Mg', 'm', 'Ng', 'n', 'nr', 'ns', 'nt', 'nx',
'nz', 'o', 'p', 'q', 'Rg', 'r', 's','na',
'Tg', 't','u', 'Vg', 'v', 'vd', 'vn','vvn',
'w', 'Yg', 'y', 'z']
lineCount=-1#句子总数，为了求出开始概率
for state0 in state_list:
    transport_c[state0]={}
    for state1 in state_list:
        transport_c[state0][state1]=0.0
    emit_c[state0]={}
    start_c[state0]=0.0
vocabs=[]
classify=[]
class_count={}
for state in state_list:
    class_count[state]=0.0
    
with open(file_path,encoding="gbk") as file:
    lines = file.readlines()
    for line in lines:  
        line=line.strip()
        if not line:continue
        lineCount+=1#应该在有内容的行处加 1
        words=line.split(" ")#分解为多个单词
        for word in words:
            position=word.index('/')  #如果是[中国人民/n]
            if '[' in word and ']' in word:
                vocabs.append(word[1:position])
                vocabs.append(word[position+1:-1])
                break
            if  '[' in word:
                vocabs.append(word[1:position])
                classify.append(word[position+1:])
                break
            if ']' in  word:
                vocabs.append(word[:position])
                classify.append(word[position+1:-1])
                break
            vocabs.append(word[:position])
            classify.append(word[position+1:])

        if  len(vocabs)!=len(classify):
            print('词汇数量与类别数量不一致')
            break  #不一致退出程序
        else:
            for n in range(0,len(vocabs)):
                class_count[classify[n]]+=1.0
                if vocabs[n] in emit_c[classify[n]]:
                    emit_c[classify[n]][vocabs[n]] += 1.0
                else:
                    emit_c[classify[n]][vocabs[n]] = 1.0
                if n==0:
                    start_c[classify[n]] += 1.0
                else:
                    transport_c[classify[n-1]][classify[n]]+=1.0
        vocabs = []
        classify = []
for state in state_list:
    start_c[state]=start_c[state]*1.0/lineCount
    for li in emit_c[state]:
        emit_c[state][li]=emit_c[state][li]/class_count[state]
    for li in transport_c[state]:
        transport_c[state][li]=transport_c[state][li]/class_count[state]
这段代码是在处理一个词性标注的任务，它使用了隐马尔可夫模型（HMM）。这段代码的主要目标是从一个标注了词性的语料库中学习HMM的参数，包括初始状态概率、转移概率和发射概率。

首先，它定义了一些变量和字典来存储这些参数和其他必要的信息。

然后，它打开一个文件（路径存储在file_path变量中），并逐行读取文件。

对于每一行，它首先将行分割成单词。每个单词都是一个形式为"word/POS"的字符串，其中"word"是单词，"POS"是词性。

然后，它将每个单词分割成单词部分和词性部分，并将它们分别添加到vocabs和classify列表中。

如果vocabs和classify的长度不相等，它会打印一条错误消息并退出程序。

否则，它会遍历vocabs和classify，并更新start_c、transport_c和emit_c字典。

最后，它将start_c、emit_c和transport_c字典中的计数转换为概率。

这段代码的结果是三个字典start_c、transport_c和emit_c，它们分别存储了HMM的初始状态概率、转移概率和发射概率。这些参数可以用于后续的词性标注任务。
```

```python
def hmm_viterbi(obs, states, start_p, trans_p, emit_p):
    path = {}
    V = [{}]  # 记录第几次的概率
    for state in states:
        V[0][state] = start_p[state] * emit_p[state].get(obs[0], 0)
        path[state] = [state]
    for n in range(1, len(obs)):
        V.append({})
        newpath = {}
        for k in states:
            pp,pat=max([(V[n - 1][j] * trans_p[j].get(k,0) * emit_p[k].get(obs[n], 0) ,j )for j in states])
            V[n][k] = pp
            newpath[k] = path[pat] + [k]
        path=newpath
    (prob, state) = max([(V[len(obs) - 1][y], y) for y in states])
    return prob, path[state]
这段代码实现了Viterbi算法，这是一种动态规划算法，用于寻找最有可能产生观察序列的隐藏状态序列，特别是在隐马尔可夫模型（HMM）和其他类似的统计模型中。

函数hmm_viterbi接收五个参数：

obs：观察序列，即我们实际看到的数据（例如，单词序列）。
states：隐藏状态的集合（例如，词性）。
start_p：初始状态概率，即每个状态作为序列的第一个状态的概率。
trans_p：转移概率，即给定当前状态，下一个状态是每个可能状态的概率。
emit_p：发射概率，即给定当前状态，观察到每个可能观察值的概率。
函数的主要步骤如下：

初始化路径和V（记录每个时间步的概率）。

对于观察序列中的每个观察值，计算给定当前状态和观察值，最有可能的状态序列和其概率。

选择最后一个时间步中最有可能的状态。

返回最有可能的状态序列及其概率。

这个函数的返回值是一个元组，包含最有可能的状态序列的概率和状态序列本身。
```

```python
test_strs=["今天 天气 特别 好",
           "欢迎 大家 的 到来",
           "请 大家  喝茶",
           "你 的 名字 是 什么"
           ]

for li in range(0,len(test_strs)):
    test_strs[li]=test_strs[li].split()
for li in test_strs:
    p,out_list=hmm_viterbi(li,state_list,start_c,transport_c,emit_c)
    print(list(zip(li,out_list)))
这段代码使用了之前定义的hmm_viterbi函数来对一些测试句子进行词性标注。

它首先定义了一个包含四个句子的列表test_strs。

然后，它遍历test_strs中的每个句子，并使用split函数将句子分割成单词列表。

对于test_strs中的每个句子，它调用hmm_viterbi函数来找到最有可能的词性序列。hmm_viterbi函数的参数包括单词列表、状态列表（即词性列表）、初始状态概率、转移概率和发射概率。

最后，它打印出每个单词及其对应的最有可能的词性。这是通过使用zip函数将单词列表和词性列表组合成一个元组列表来实现的。

这段代码的结果是打印出每个测试句子中每个单词的最有可能的词性。
```





### 分析隐马尔可夫过程的原理

隐马尔可夫模型（Hidden Markov Model，HMM）是一种统计模型，用于描述一个含有隐含未知参数的马尔可夫过程。其难点在于从可观察的参数中确定该过程的参数，然后利用这些参数来作进一步的分析，如模式识别。

HMM包含两个序列：一个是可观察序列，另一个是隐藏序列。隐藏序列的状态只能通过可观察序列间接推断出来。

HMM有三个基本问题：

1. **评估问题**：给定模型参数和观察序列，计算在模型下观察序列出现的概率。这个问题通常通过前向-后向算法解决。
2. **解码问题**：给定模型参数和观察序列，找出最可能的隐藏状态序列。这个问题通常通过Viterbi算法解决。
3. **学习问题**：给定观察序列，调整模型参数以最大化观察序列的概率。这个问题通常通过Baum-Welch算法（一种特殊的EM算法）解决。

HMM广泛应用于语音识别、自然语言处理、生物信息学等领域。

前向-后向算法是一种在隐马尔可夫模型（Hidden Markov Model，HMM）中用于解决评估问题的算法。评估问题是指：给定模型参数和观察序列，计算在模型下观察序列出现的概率。

前向-后向算法包含两个部分：前向算法和后向算法。

**前向算法**：

前向算法是通过动态规划的方式，从前到后计算在时间点t状态为i且观察到序列O的概率。这个概率被称为前向概率。

**后向算法**：

后向算法也是通过动态规划的方式，但是它是从后到前计算在时间点t状态为i且从t+1到最后的观察序列的概率。这个概率被称为后向概率。

前向-后向算法的最终目标是计算出给定模型下，观察序列出现的概率。这个概率可以通过将最后一个时间点的所有前向概率相加得到。

前向-后向算法不仅可以用于评估问题，还可以用于预测问题，即预测在给定模型和观察序列下，每个时间点的状态的概率。这个概率可以通过前向概率和后向概率的乘积，然后归一化得到。

Viterbi算法是一种在隐马尔可夫模型（Hidden Markov Model，HMM）中用于解决解码问题的动态规划算法。解码问题是指：给定模型参数和观察序列，找出最可能的隐藏状态序列。

Viterbi算法的基本思想是在每个时间点，对每个状态，都保留一个最优路径（即概率最大的路径）。这个路径是从开始到当前时间点，经过这个状态的路径。然后，从这些路径中选择概率最大的路径。

Viterbi算法的步骤如下：

1. **初始化**：在时间点1，每个状态的最优路径就是开始状态到该状态的转移概率乘以该状态生成观察值的概率。
2. **递推**：对于每个后续的时间点，每个状态的最优路径是从所有可能的前一个状态到该状态的路径中选择一个概率最大的路径。这个概率是前一个状态的最优路径的概率、前一个状态到该状态的转移概率、和该状态生成当前观察值的概率的乘积。
3. **回溯**：在最后一个时间点，选择一个概率最大的状态，然后沿着这个状态的最优路径回溯到开始，就得到了最可能的隐藏状态序列。

Viterbi算法的时间复杂度和空间复杂度都是线性的，所以它非常适合于处理大规模的数据。

Baum-Welch算法，也被称为前向-后向算法，是一种在隐马尔可夫模型（Hidden Markov Model，HMM）中用于解决学习问题的算法。学习问题是指：给定观察序列，调整模型参数以最大化观察序列的概率。

Baum-Welch算法实际上是一种特殊的EM（Expectation-Maximization）算法。EM算法是一种迭代算法，用于找到使得似然函数最大的参数值。

Baum-Welch算法的步骤如下：

1. **初始化**：选择初始的模型参数。
2. **E步骤**：使用当前的模型参数，计算每个时间点的每个状态的后验概率，以及每两个时间点的每两个状态的联合后验概率。这个步骤可以通过前向-后向算法实现。
3. **M步骤**：使用计算出的后验概率，重新估计模型的参数。具体来说，状态的初始概率是第一个时间点的后验概率，状态转移概率是两个时间点的联合后验概率除以第一个时间点的后验概率，观察概率是所有生成该观察值的后验概率的总和除以所有后验概率的总和。
4. **迭代**：重复E步骤和M步骤，直到模型参数收敛，或者达到预设的最大迭代次数。

Baum-Welch算法可以找到局部最优的模型参数，但是不能保证找到全局最优。因此，通常需要多次运行Baum-Welch算法，每次使用不同的初始参数，然后选择最好的结果。

## 基于HMM-GMM的单字识别

### 代码解释

```python
#训练数据路径
train_data_path =os.path.join(os.getcwd(),"./asr/data3/training_data" )
#测试数据路径
test_data_path = os.path.join(os.getcwd(),"./asr/data3/test_data" )
```

```python
# 生成wavdict，key=wavid，value=wavfile
def gen_wavlist(wavpath):
    wavdict = {}
    labeldict = {}
    for (dirpath, dirnames, filenames) in os.walk(wavpath):
        for filename in filenames:
            if filename.endswith('.wav'):
                filepath = os.sep.join([dirpath, filename])
                fileid = filename.strip('.wav')
                wavdict[fileid] = filepath
                label = fileid.split('_')[1]
                labeldict[fileid] = label
    return wavdict, labeldict
这段代码定义了一个函数 gen_wavlist，它接收一个参数 wavpath，这个参数应该是一个包含 .wav 文件的目录路径。

函数的主要工作是遍历 wavpath 目录及其子目录中的所有文件，并为每个 .wav 文件创建两个字典条目：

wavdict：键是 .wav 文件的文件名（不包括扩展名），值是文件的完整路径。
labeldict：键是 .wav 文件的文件名（不包括扩展名），值是文件名中 _ 后面的部分。
函数最后返回这两个字典。

例如，如果有一个文件名为 123_hello.wav 的文件，那么 wavdict 将包含一个条目 {123_hello: '完整文件路径'}，labeldict 将包含一个条目 {123_hello: 'hello'}。
```

```python
CATEGORY = ['1', '2', '3', '4', '5', '6', '7', '8', '9', '10']
# 读取训练所需数据
wavdict, labeldict = gen_wavlist(train_data_path)
# 读取测试所需数据
testdict, testlabel = gen_wavlist(test_data_path)

这段代码首先定义了一个名为 CATEGORY 的列表，包含了 '1' 到 '10' 的字符串。

然后，它调用了前面定义的 gen_wavlist 函数两次，一次是用训练数据路径 train_data_path，一次是用测试数据路径 test_data_path。

gen_wavlist(train_data_path) 返回的两个字典被赋值给 wavdict 和 labeldict。wavdict 包含了训练数据的 .wav 文件的文件名（不包括扩展名）和对应的完整路径，labeldict 包含了训练数据的 .wav 文件的文件名（不包括扩展名）和对应的标签。

gen_wavlist(test_data_path) 返回的两个字典被赋值给 testdict 和 testlabel。testdict 包含了测试数据的 .wav 文件的文件名（不包括扩展名）和对应的完整路径，testlabel 包含了测试数据的 .wav 文件的文件名（不包括扩展名）和对应的标签。

这样，你就有了训练和测试数据的文件路径和对应的标签，可以用于后续的模型训练和测试。
```

```python
# 特征提取，feat = compute_mfcc(wadict[wavid])
def compute_mfcc(file):
    fs, audio = wavfile.read(file)
    mfcc_feat = mfcc(audio, samplerate=(fs/2), numcep=26)
    return mfcc_feat
这段代码定义了一个名为 compute_mfcc 的函数，它接收一个参数 file，这个参数应该是一个 .wav 文件的路径。

函数的主要工作是读取 .wav 文件并计算其 MFCC（Mel Frequency Cepstral Coefficients）特征。

fs, audio = wavfile.read(file)：使用 scipy.io.wavfile.read 函数读取 .wav 文件，返回采样率 fs 和音频数据 audio。

mfcc_feat = mfcc(audio, samplerate=(fs/2), numcep=26)：使用 python_speech_features.mfcc 函数计算音频数据的 MFCC 特征。这里，采样率被设为原始采样率的一半，MFCC 特征的数量被设为 26。

函数最后返回计算得到的 MFCC 特征。

MFCC 是一种常用于语音识别和音乐信息检索的特征，它可以有效地表示音频信号的频谱形状。
```

```python
class Model():    
def __init__(self, CATEGORY=None, n_comp=3, n_mix = 3, cov_type='diag', n_iter=1000):
# CATEGORY: 所有标签的列表
# n_comp:   每个孤立词中的状态数
# n_mix:    每个状态包含的混合高斯数量
# cov_type: 协方差矩阵的类型
# n_iter:   训练迭代次数
        super(Model, self).__init__()
        self.CATEGORY = CATEGORY
        self.category = len(CATEGORY)
        self.n_comp = n_comp
        self.n_mix = n_mix
        self.cov_type = cov_type
        self.n_iter = n_iter
        # 关键步骤，初始化models，返回特定参数的模型的列表
        self.models = []
        for k in range(self.category):
            model = hmm.GMMHMM(n_components=self.n_comp, n_mix = self.n_mix, 
                                covariance_type=self.cov_type, n_iter=self.n_iter)
            self.models.append(model)

    # 模型训练
    def train(self, wavdict=None, labeldict=None):
        for k in range(10):
            subdata = []
            model = self.models[k]
            for x in wavdict:
                if labeldict[x] == self.CATEGORY[k]:
                    mfcc_feat = compute_mfcc(wavdict[x])
                    model.fit(mfcc_feat)

    # 使用特定的测试集合进行测试
    def test(self, wavdict=None, labeldict=None):
        result = []
        for k in range(self.category):
            subre = []
            label = []
            model = self.models[k]
            for x in wavdict:
                mfcc_feat = compute_mfcc(wavdict[x])
                # 生成每个数据在当前模型下的得分情况
                re = model.score(mfcc_feat)
                subre.append(re)
                label.append(labeldict[x])
            # 汇总得分情况
            result.append(subre)
        # 选取得分最高的种类
        result = np.vstack(result).argmax(axis=0)
        # 返回种类的类别标签
        result = [self.CATEGORY[label] for label in result]
        print('识别得到结果：\n',result)
        print('原始标签类别：\n',label)
        # 检查识别率，为：正确识别的个数/总数
        totalnum = len(label)
        correctnum = 0
        for i in range(totalnum):
            if result[i] == label[i]:
                correctnum += 1 
        print('识别率:', correctnum/totalnum)


    def save(self, path="models.pkl"):
        # 利用external joblib保存生成的hmm模型
        joblib.dump(self.models, path)


    def load(self, path="models.pkl"):
        # 导入hmm模型
        self.models = joblib.load(path)
这段代码定义了一个名为 Model 的类，它用于训练和测试基于 HMM-GMM 的语音识别模型。

__init__ 方法：初始化模型。接收参数包括标签列表 CATEGORY，每个孤立词中的状态数 n_comp，每个状态包含的混合高斯数量 n_mix，协方差矩阵的类型 cov_type，训练迭代次数 n_iter。方法中创建了一个 GMMHMM 模型列表 self.models，每个标签对应一个模型。

train 方法：训练模型。接收参数为 .wav 文件的字典 wavdict 和对应的标签字典 labeldict。方法中，对每个标签对应的模型，使用对应标签的 .wav 文件的 MFCC 特征进行训练。

test 方法：测试模型。接收参数为 .wav 文件的字典 wavdict 和对应的标签字典 labeldict。方法中，对每个标签对应的模型，使用所有 .wav 文件的 MFCC 特征计算得分，最后选取得分最高的模型对应的标签作为识别结果，并计算识别率。

save 方法：保存模型。接收参数为保存路径 path。方法中，使用 joblib.dump 函数保存 self.models 到指定路径。

load 方法：加载模型。接收参数为加载路径 path。方法中，使用 joblib.load 函数从指定路径加载模型到 self.models。

这个类提供了一个完整的 HMM-GMM 语音识别模型的训练、测试、保存和加载的流程。
```

```python
# 模型训练
models = Model(CATEGORY=CATEGORY)
models.train(wavdict=wavdict, labeldict=labeldict)
```

```python
# 模型测试
models.test(wavdict=testdict, labeldict=testlabel)
```



### 分析利用GMM-HMM模型实现孤立词语音识别的基本原理与流程。

孤立词语音识别是一种特定的语音识别任务，其中系统被训练来识别预定义的单词列表。这些单词在语音流中是孤立的，也就是说，它们被静音或其他非语音声音分隔开。GMM-HMM模型是实现孤立词语音识别的一种常见方法。

基本原理：

1. **GMM（高斯混合模型）**：GMM是一种概率模型，用于表示随机变量的概率分布。在语音识别中，GMM用于建立声学模型，即将声学特征（如MFCC）映射到特定的语音单元（如音素或单词）。
2. **HMM（隐马尔可夫模型）**：HMM是一种统计模型，用于描述一个含有隐含未知参数的马尔可夫过程。在语音识别中，HMM用于建立语言模型，即描述语音单元（如音素或单词）的序列的概率。

基本流程：

1. **特征提取**：从语音信号中提取有用的特征，如MFCC。
2. **训练**：使用训练数据（已标记的语音信号）训练GMM-HMM模型。对于每个孤立词，都训练一个HMM，其中GMM用于表示HMM的每个状态。训练的目标是最大化训练数据的对数概率。
3. **识别**：对于给定的测试语音信号，计算其在每个孤立词的HMM上的对数概率，选择对数概率最大的孤立词作为识别结果。
4. **评估**：使用测试数据（已标记的语音信号）评估模型的性能，通常使用识别率作为评价指标。

以上就是利用GMM-HMM模型实现孤立词语音识别的基本原理与流程。



## 基于GMM-HMM的连续词识别

### 代码解释

```python
#训练数据路径
data_path = os.path.join(os.getcwd(), "data4")
#模型保存路径
model_path = "hmm_gmm_model.pkl"
```
```python
def wav2mfcc(label, data_path):
    trng_data = {}
    write_pickle = True
    mfccs = []
    rate, sig = wvf.read(data_path)
    mfcc_feat = mfcc(sig, rate)
    mfccs.append(mfcc_feat)
    trng_data[label] = mfccs

    return trng_data

这段代码是用于将音频文件转换为MFCC（Mel Frequency Cepstral Coefficients）特征的函数。MFCC是一种在音频处理和语音识别中常用的特征。

函数的输入参数是标签（label）和数据路径（data_path）。标签通常用于标记音频数据的类别，数据路径则是音频文件的位置。

函数的主要步骤如下：

初始化一个空字典trng_data，用于存储转换后的MFCC特征。
初始化一个空列表mfccs，用于临时存储MFCC特征。
使用wvf.read(data_path)读取音频文件，返回采样率（rate）和信号数据（sig）。
使用mfcc(sig, rate)函数将信号数据转换为MFCC特征。
将MFCC特征添加到mfccs列表中。
将标签和对应的MFCC特征存入trng_data字典中。
最后，函数返回包含MFCC特征的字典trng_data。
```

```python
def obtain_config(label):
    conf = {label: {}}
    conf[label]["n_components"] = 2
    conf[label]["n_mix"] = 2
    return conf
这段代码定义了一个名为obtain_config的函数，它接受一个参数label，并返回一个包含特定配置的字典。

函数的主要步骤如下：

初始化一个字典conf，其中包含一个键为label的空字典。
在conf[label]字典中设置键"n_components"的值为2。
在conf[label]字典中设置键"n_mix"的值为2。
最后，函数返回包含配置的字典conf。

这个函数可能用于生成某种模型或算法的配置。在混合高斯模型（Gaussian Mixture Model，GMM）中，n_components可能表示高斯分布的数量，n_mix可能表示混合成分的数量。具体含义取决于这个配置如何被使用。
```

```python
def get_hmm_gmm(label, trng_data=None, GMM_config=None, model_path="hmm_gmm_model.pkl", from_file=False):
    hmm_gmm = {}
    if not from_file:

        hmm_gmm[label] = GMMHMM(
            n_components=GMM_config[label]["n_components"],
            n_mix=GMM_config[label]["n_mix"])
        if trng_data[label]:
            hmm_gmm[label].fit(np.vstack(trng_data[label]))
        pickle.dump(hmm_gmm, open(model_path, "wb"))
    else:
        hmm_gmm = pickle.load(open(model_path, "rb"))
    return hmm_gmm
    
这段代码定义了一个名为get_hmm_gmm的函数，它用于创建或加载一个基于混合高斯模型的隐马尔可夫模型（GMM-HMM）。

函数的输入参数包括：

label：标签，用于标记模型。
trng_data：训练数据，用于训练模型。默认为None。
GMM_config：GMM-HMM模型的配置信息。默认为None。
model_path：模型文件的路径。默认为"hmm_gmm_model.pkl"。
from_file：一个布尔值，用于指示是否从文件中加载模型。默认为False。
函数的主要步骤如下：

初始化一个空字典hmm_gmm，用于存储模型。
如果from_file为False，即不从文件中加载模型，则创建一个新的GMM-HMM模型，模型的参数由GMM_config提供。如果trng_data[label]存在，则使用这些数据训练模型。最后，将模型保存到文件中。
如果from_file为True，即从文件中加载模型，则直接从文件中加载模型。
最后，函数返回包含模型的字典hmm_gmm。
```

```python
def train(data_path, model_path):
    with open(os.path.join(data_path, "label.txt")) as f:
        label = f.readline()

    data_path = os.path.join(data_path, "train.wav")

    train_data = wav2mfcc(label, data_path)
    GMM_config = obtain_config(label)
    hmm_gmm = get_hmm_gmm(label, train_data, GMM_config, model_path)
    return hmm_gmm
    
这段代码定义了一个名为train的函数，它用于训练一个基于混合高斯模型的隐马尔可夫模型（GMM-HMM）。

函数的输入参数包括：

data_path：数据文件的路径。
model_path：模型文件的路径。
函数的主要步骤如下：

打开位于data_path下的"label.txt"文件，并读取第一行作为标签label。
更新data_path，使其指向"train.wav"文件。
使用wav2mfcc函数将音频文件转换为MFCC特征，得到训练数据train_data。
使用obtain_config函数获取GMM-HMM模型的配置信息GMM_config。
使用get_hmm_gmm函数创建并训练GMM-HMM模型，得到hmm_gmm。
最后，函数返回训练好的模型hmm_gmm。
```

```python
def test_file(test_file, hmm_gmm):
    rate, sig = wvf.read(test_file)
    mfcc_feat = mfcc(sig, rate)
    pred = {}
    for model in hmm_gmm:
        pred[model] = hmm_gmm[model].score(mfcc_feat)
    return get_nbest(pred, 2), pred
    
这段代码定义了一个名为test_file的函数，它用于对给定的音频文件进行测试，并返回预测结果。

函数的输入参数包括：

test_file：测试音频文件的路径。
hmm_gmm：一个包含训练好的GMM-HMM模型的字典。
函数的主要步骤如下：

使用wvf.read(test_file)读取音频文件，返回采样率（rate）和信号数据（sig）。
使用mfcc(sig, rate)函数将信号数据转换为MFCC特征。
初始化一个空字典pred，用于存储预测结果。
遍历hmm_gmm字典中的每一个模型，使用模型对MFCC特征进行评分，将评分结果存入pred字典中。
使用get_nbest(pred, 2)函数获取评分最高的两个模型。
最后，函数返回评分最高
```

```python
#获取topN的结果
def get_nbest(d, n):
    return heapq.nlargest(n, d, key=lambda k: d[k])


def predict_label(file, hmm_gmm):
    predicted = test_file(file, hmm_gmm)
    return predicted


wave_path = os.path.join(data_path, "train.wav")
predicted, probs = predict_label(wave_path, hmm_gmm)

print("PREDICTED: %s" % predicted[0])

这段代码主要用于预测给定音频文件的标签。

get_nbest(d, n)函数：这个函数接收一个字典d和一个整数n作为参数，返回字典中值最大的n个键。这个函数使用了heapq.nlargest函数，它可以返回一个列表中最大的n个元素。在这里，lambda k: d[k]用于指定比较的是字典的值，而不是键。

predict_label(file, hmm_gmm)函数：这个函数接收一个文件路径file和一个GMM-HMM模型hmm_gmm作为参数，返回预测的标签。它通过调用test_file函数来进行预测。

wave_path = os.path.join(data_path, "train.wav")：这行代码用于构造音频文件的路径。

predicted, probs = predict_label(wave_path, hmm_gmm)：这行代码调用predict_label函数对音频文件进行预测，并将预测的标签和所有模型的评分结果分别赋值给predicted和probs。

print("PREDICTED: %s" % predicted[0])：这行代码打印出评分最高的模型，即预测的标签。
```

### 分析利用GMM-HMM模型实现连续词语音识别的基本原理与流程。

GMM-HMM模型是语音识别中常用的一种模型，其中GMM代表高斯混合模型，HMM代表隐马尔可夫模型。

基本原理：

1. 高斯混合模型（Gaussian Mixture Model，GMM）：GMM是一种概率模型，用于表示多个高斯分布的混合。在语音识别中，GMM用于建立声学模型，即将音频信号的特征（如MFCC）与语音单元（如音素）之间建立关联。
2. 隐马尔可夫模型（Hidden Markov Model，HMM）：HMM是一种统计模型，用于描述一个隐藏的马尔可夫过程。在语音识别中，HMM用于建立语言模型，即描述语音单元之间的转移概率。

基本流程：

1. 预处理：首先，对音频数据进行预处理，包括分帧、窗函数处理、快速傅里叶变换等，提取出音频的MFCC特征。
2. 训练声学模型：然后，使用GMM对每个语音单元的MFCC特征进行建模，得到声学模型。
3. 训练语言模型：接着，使用HMM对语音单元之间的转移概率进行建模，得到语言模型。
4. 识别：最后，对于给定的音频数据，先提取MFCC特征，然后通过声学模型和语言模型进行识别，输出识别结果。

在语音识别中，GMM（高斯混合模型）和HMM（隐马尔可夫模型）的合作主要体现在声学模型和语言模型的建立上。

1. GMM用于建立声学模型：声学模型是用来描述音频信号的特征（如MFCC）与语音单元（如音素）之间的关系。GMM是一种概率模型，它可以用多个高斯分布的混合来表示复杂的分布，因此可以用来对每个语音单元的特征分布进行建模。
2. HMM用于建立语言模型：语言模型是用来描述语音单元之间的转移概率。HMM是一种统计模型，它可以描述一个隐藏的马尔可夫过程，因此可以用来对语音单元之间的转移概率进行建模。

在语音识别过程中，首先通过GMM声学模型将音频信号的特征映射到各个语音单元，然后通过HMM语言模型计算各个语音单元之间的转移概率，最后通过综合这两个模型的结果，得到最可能的语音识别结果。

在这段代码中，GMM（高斯混合模型）和HMM（隐马尔可夫模型）的作用主要体现在声学模型的建立和语音识别过程中。

1. GMM的作用：在`wav2mfcc`函数中，音频文件被转换为MFCC特征，这些特征是音频信号的一种表征。然后在`get_hmm_gmm`函数中，使用这些MFCC特征和GMM的配置信息（由`obtain_config`函数提供）来创建一个GMM-HMM模型。在这个过程中，GMM被用来对每个语音单元的特征分布进行建模，这就是声学模型的建立过程。
2. HMM的作用：在`get_hmm_gmm`函数中，创建了一个GMM-HMM模型，这个模型是GMM和HMM的结合。在这个模型中，HMM被用来描述语音单元之间的转移概率。然后在`test_file`函数中，使用这个模型对测试音频文件进行预测。在这个过程中，HMM被用来计算各个语音单元之间的转移概率，然后根据这些概率来预测最可能的语音识别结果，这就是语音识别过程。

举个例子，假设我们有一个音频文件，它包含了一个人说的一句话。首先，我们使用`wav2mfcc`函数将音频文件转换为MFCC特征，然后使用`obtain_config`函数获取GMM的配置信息，接着使用`get_hmm_gmm`函数创建一个GMM-HMM模型并使用MFCC特征来训练这个模型。这个过程就是声学模型的建立过程，其中GMM被用来对每个语音单元的特征分布进行建模。然后，我们可以使用`test_file`函数和这个模型来对其他音频文件进行预测。在这个过程中，HMM被用来计算各个语音单元之间的转移概率，然后根据这些概率来预测最可能的语音识别结果。这就是语音识别过程，其中HMM的作用就体现出来了。

### 对比分析利用GMM-HMM模型实现孤立词语音识别与连续词语音识别在实现方法上的相同与不同之处。

孤立词语音识别和连续词语音识别都可以使用GMM-HMM模型进行实现，但在实现方法上存在一些不同之处。

相同之处：

1. 都需要对音频数据进行预处理，如提取MFCC特征。
2. 都需要使用GMM-HMM模型进行训练和预测。GMM用于建立声学模型，HMM用于建立语言模型。

不同之处：

1. 孤立词语音识别：每个词都是独立的，不需要考虑词与词之间的关系。因此，HMM模型中的状态通常对应于单个词或音素。训练时，每个词的音频数据都被视为一个独立的序列。
2. 连续词语音识别：需要考虑词与词之间的关系，因此HMM模型中的状态可能需要对应于更复杂的语言单位，如音节、词或短语。训练时，整个句子的音频数据被视为一个连续的序列。

在实际应用中，连续词语音识别的难度通常会更高，因为需要处理更复杂的语言结构和更长的序列数据。但是，连续词语音识别也更符合实际的语音识别场景，因此在许多应用中更为常见。
