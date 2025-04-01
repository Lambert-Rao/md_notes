## 关于推荐算法的学习

> [推荐系统：协同过滤CF和基于内容的推荐CB - 大胖子球花 - 博客园](https://www.cnblogs.com/chason95/articles/10276158.html)

### 基于内容的推荐(CB,Content-based Recommendations):

我爱吃鳕鱼，所以我应该也爱吃鲈鱼，利用了两者都是鱼这一特征

### 协同过滤（Collaborative Filtering，简称CF）

我爱吃鳕鱼，鱿鱼姐也爱吃鳕鱼，所以如果我爱吃槽子糕，那鱿鱼姐可能也爱吃槽子糕

#### 基于用户的协同过滤：寻找目标用户喜好的k个邻居，然后根据k邻居的历史喜好进行推荐

#### 基于物品的协同过滤(Item CF,Item based Collaborative Filtering)：利用喜欢该item的用户可能也喜欢的item进行推荐

![image-20250220095701398](./assets/image-20250220095701398.png)

![img](https://img2018.cnblogs.com/blog/1372735/201901/1372735-20190117113059216-1527968826.png)

Embedding 技术：处理稀疏的特征

 $ q_ {1} $ , $ p_ {v} $ $ \in $ Rf.