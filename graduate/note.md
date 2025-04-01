NDCG 评价指标

lightcgn训练初始embedding

Adam优化器？

![image-20250315185550586](./assets/image-20250315185550586.png)

```
setx HTTP_PROXY http://localhost:7890
setx HTTPS_PROXY http://localhost:7890
```



```
C:\Users\Lambert\miniconda3\python.exe D:\Code\degree\LightGCN-PyTorch-master\code\main.py --decay=1e-4 --lr=0.001 --layer=3 --seed=2025 --dataset=bangumi "--topks=[30]" --recdim=64 
>>SEED: 2025
loading [../data/bangumi]
10092374 interactions for training
2472509 interactions for testing
bangumi Sparsity : 0.005321514076561994
bangumi is ready to go
===========config================
{'A_n_fold': 100,
 'A_split': False,
 'bigdata': False,
 'bpr_batch_size': 2048,
 'decay': 0.0001,
 'dropout': 0,
 'keep_prob': 0.6,
 'latent_dim_rec': 64,
 'lightGCN_n_layers': 3,
 'lr': 0.001,
 'multicore': 0,
 'pretrain': 0,
 'test_u_batch_size': 100}
cores for test: 8
comment: lgn
tensorboard: 1
LOAD: 0
Weight path: ./checkpoints
Test Topks: [30]
using bpr loss
===========end===================
use NORMAL distribution initilizer
loading adjacency matrix
generating adjacency matrix
D:\Code\degree\LightGCN-PyTorch-master\code\dataloader.py:351: RuntimeWarning: divide by zero encountered in power
  d_inv = np.power(rowsum, -0.5).flatten()
costing 188.05020260810852s, saved norm_mat...
D:\Code\degree\LightGCN-PyTorch-master\code\dataloader.py:330: UserWarning: torch.sparse.SparseTensor(indices, values, shape, *, device=) is deprecated.  Please use torch.sparse_coo_tensor(indices, values, shape, dtype=, device=). (Triggered internally at C:\cb\pytorch_1000000000000\work\torch\csrc\utils\tensor_new.cpp:620.)
  return torch.sparse.FloatTensor(index, data, torch.Size(coo.shape))
don't split the matrix
lgn is already to go(dropout:0)
load and save to D:\Code\degree\LightGCN-PyTorch-master\code\checkpoints\lgn-bangumi-3-64.pth.tar
[TEST]
{'precision': array([0.00122182]), 'recall': array([0.0014605]), 'ndcg': array([0.00154909])}

Process finished with exit code -1073741676 (0xC0000094)

```

```
C:\Users\Lambert\miniconda3\python.exe D:\Code\degree\LightGCN-PyTorch-master\code\main.py --decay=1e-4 --lr=0.003 --layer=3 --seed=2025 --dataset=bangumi "--topks=[20]" --recdim=64 --bpr_batch=8196 --a_fold=20 --testbatch=2048 --multicore=0 
>>SEED: 2025
loading [../data/bangumi]
10093538 interactions for training
2477623 interactions for testing
bangumi Sparsity : 0.005324172952523884
bangumi is ready to go
===========config================
{'A_n_fold': 20,
 'A_split': False,
 'bigdata': False,
 'bpr_batch_size': 8196,
 'decay': 0.0001,
 'dropout': 0,
 'keep_prob': 0.6,
 'latent_dim_rec': 64,
 'lightGCN_n_layers': 3,
 'lr': 0.003,
 'multicore': 0,
 'pretrain': 0,
 'test_u_batch_size': 2048}
cores for test: 8
comment: lgn
tensorboard: 1
LOAD: 0
Weight path: ./checkpoints
Test Topks: [20]
using bpr loss
===========end===================
use NORMAL distribution initilizer
loading adjacency matrix
successfully loaded...
don't split the matrix
lgn is already to go(dropout:0)
load and save to D:\Code\degree\LightGCN-PyTorch-master\code\checkpoints\lgn-bangumi-3-64.pth.tar
[TEST]
{'precision': array([0.0011749]), 'recall': array([0.00095619]), 'ndcg': array([0.00139442])}
forrtl: error (200): program aborting due to control-C event
Image              PC                Routine            Line        Source             
libifcoremd.dll    00007FFA24D1DF54  Unknown               Unknown  Unknown
KERNELBASE.dll     00007FFBA7254113  Unknown               Unknown  Unknown
KERNEL32.DLL       00007FFBA8F67374  Unknown               Unknown  Unknown
ntdll.dll          00007FFBA96DCC91  Unknown               Unknown  Unknown

Process finished with exit code 0

```
C:\Users\Lambert\miniconda3\python.exe D:\Code\degree\LightGCN-PyTorch-master\code\main.py --decay=1e-4 --lr=0.003 --layer=3 --seed=2025 --dataset=bangumi "--topks=[20]" --recdim=64 --bpr_batch=8196 --a_fold=20 --testbatch=2048 --multicore=0 --epoch=100 --dropout=1 
>>SEED: 2025
loading [../data/bangumi]
8746175 interactions for training
2163896 interactions for testing
bangumi Sparsity : 0.02871729092895383
bangumi is ready to go
===========config================
{'A_n_fold': 20,
 'A_split': False,
 'bigdata': False,
 'bpr_batch_size': 8196,
 'decay': 0.0001,
 'dropout': 1,
 'keep_prob': 0.6,
 'latent_dim_rec': 64,
 'lightGCN_n_layers': 3,
 'lr': 0.003,
 'multicore': 0,
 'pretrain': 0,
 'test_u_batch_size': 2048}
cores for test: 8
comment: lgn
tensorboard: 1
LOAD: 0
Weight path: ./checkpoints
Test Topks: [20]
using bpr loss
===========end===================
use NORMAL distribution initilizer
loading adjacency matrix
generating adjacency matrix
costing 58.73864793777466s, saved norm_mat...
don't split the matrix
lgn is already to go(dropout:1)
load and save to D:\Code\degree\LightGCN-PyTorch-master\code\checkpoints\lgn-bangumi-3-64.pth.tar
[TEST]
{'precision': array([0.00625512]), 'recall': array([0.00273602]), 'ndcg': array([0.00645609])}
EPOCH[1/100] loss0.302-|Sample:1.27|
EPOCH[2/100] loss0.227-|Sample:1.28|
EPOCH[3/100] loss0.198-|Sample:1.26|
EPOCH[4/100] loss0.180-|Sample:1.27|
EPOCH[5/100] loss0.168-|Sample:1.29|
EPOCH[6/100] loss0.158-|Sample:1.25|
EPOCH[7/100] loss0.149-|Sample:1.30|
EPOCH[8/100] loss0.143-|Sample:1.28|
EPOCH[9/100] loss0.138-|Sample:1.33|
EPOCH[10/100] loss0.133-|Sample:1.29|
[TEST]
{'precision': array([0.24233699]), 'recall': array([0.1365947]), 'ndcg': array([0.28194095])}
EPOCH[11/100] loss0.129-|Sample:1.30|
EPOCH[12/100] loss0.126-|Sample:1.34|
EPOCH[13/100] loss0.123-|Sample:1.27|
EPOCH[14/100] loss0.120-|Sample:1.27|
EPOCH[15/100] loss0.118-|Sample:1.25|
EPOCH[16/100] loss0.116-|Sample:1.25|
EPOCH[17/100] loss0.114-|Sample:1.25|
EPOCH[18/100] loss0.112-|Sample:1.27|
EPOCH[19/100] loss0.110-|Sample:1.29|
EPOCH[20/100] loss0.109-|Sample:1.25|
[TEST]
{'precision': array([0.26527277]), 'recall': array([0.15242848]), 'ndcg': array([0.30944636])}
EPOCH[21/100] loss0.107-|Sample:1.25|
EPOCH[22/100] loss0.106-|Sample:1.27|
EPOCH[23/100] loss0.104-|Sample:1.28|
EPOCH[24/100] loss0.104-|Sample:1.27|
EPOCH[25/100] loss0.103-|Sample:1.26|
EPOCH[26/100] loss0.101-|Sample:1.27|
EPOCH[27/100] loss0.100-|Sample:1.26|
EPOCH[28/100] loss0.099-|Sample:1.26|
EPOCH[29/100] loss0.099-|Sample:1.29|
EPOCH[30/100] loss0.097-|Sample:1.36|
[TEST]
{'precision': array([0.27679493]), 'recall': array([0.16125589]), 'ndcg': array([0.32323486])}
EPOCH[31/100] loss0.097-|Sample:1.27|
EPOCH[32/100] loss0.096-|Sample:1.27|
EPOCH[33/100] loss0.095-|Sample:1.26|
EPOCH[34/100] loss0.095-|Sample:1.26|
EPOCH[35/100] loss0.094-|Sample:1.27|
EPOCH[36/100] loss0.094-|Sample:1.27|
EPOCH[37/100] loss0.093-|Sample:1.29|
EPOCH[38/100] loss0.093-|Sample:1.30|
EPOCH[39/100] loss0.092-|Sample:1.27|
EPOCH[40/100] loss0.092-|Sample:1.28|
[TEST]
{'precision': array([0.2822903]), 'recall': array([0.1654106]), 'ndcg': array([0.33021135])}
EPOCH[41/100] loss0.091-|Sample:1.26|
EPOCH[42/100] loss0.091-|Sample:1.35|
EPOCH[43/100] loss0.090-|Sample:1.26|
EPOCH[44/100] loss0.090-|Sample:1.28|
EPOCH[45/100] loss0.089-|Sample:1.26|
EPOCH[46/100] loss0.089-|Sample:1.25|
EPOCH[47/100] loss0.089-|Sample:1.26|
EPOCH[48/100] loss0.088-|Sample:1.27|
EPOCH[49/100] loss0.088-|Sample:1.26|
EPOCH[50/100] loss0.088-|Sample:1.28|
[TEST]
{'precision': array([0.28605218]), 'recall': array([0.16813596]), 'ndcg': array([0.33451647])}
EPOCH[51/100] loss0.087-|Sample:1.28|
EPOCH[52/100] loss0.087-|Sample:1.29|
EPOCH[53/100] loss0.087-|Sample:1.27|
EPOCH[54/100] loss0.087-|Sample:1.27|
EPOCH[55/100] loss0.086-|Sample:1.28|
EPOCH[56/100] loss0.086-|Sample:1.26|
EPOCH[57/100] loss0.086-|Sample:1.27|
EPOCH[58/100] loss0.086-|Sample:1.31|
EPOCH[59/100] loss0.085-|Sample:1.26|
EPOCH[60/100] loss0.086-|Sample:1.27|
[TEST]
{'precision': array([0.288185]), 'recall': array([0.1701518]), 'ndcg': array([0.33696945])}
EPOCH[61/100] loss0.085-|Sample:1.27|
EPOCH[62/100] loss0.085-|Sample:1.27|
EPOCH[63/100] loss0.085-|Sample:1.29|
EPOCH[64/100] loss0.085-|Sample:1.27|
EPOCH[65/100] loss0.085-|Sample:1.26|
EPOCH[66/100] loss0.084-|Sample:1.26|
EPOCH[67/100] loss0.084-|Sample:1.26|
EPOCH[68/100] loss0.084-|Sample:1.28|
EPOCH[69/100] loss0.084-|Sample:1.27|
EPOCH[70/100] loss0.084-|Sample:1.29|
[TEST]
{'precision': array([0.28911574]), 'recall': array([0.17122229]), 'ndcg': array([0.33864916])}
EPOCH[71/100] loss0.083-|Sample:1.29|
EPOCH[72/100] loss0.084-|Sample:1.27|
EPOCH[73/100] loss0.084-|Sample:1.26|
EPOCH[74/100] loss0.084-|Sample:1.27|
EPOCH[75/100] loss0.083-|Sample:1.28|
EPOCH[76/100] loss0.083-|Sample:1.25|
EPOCH[77/100] loss0.083-|Sample:1.26|
EPOCH[78/100] loss0.083-|Sample:1.26|
EPOCH[79/100] loss0.083-|Sample:1.26|
EPOCH[80/100] loss0.083-|Sample:1.26|
[TEST]
{'precision': array([0.29003625]), 'recall': array([0.17175063]), 'ndcg': array([0.33970462])}
EPOCH[81/100] loss0.082-|Sample:1.25|
EPOCH[82/100] loss0.083-|Sample:1.25|
EPOCH[83/100] loss0.082-|Sample:1.28|
EPOCH[84/100] loss0.082-|Sample:1.28|
EPOCH[85/100] loss0.082-|Sample:1.27|
EPOCH[86/100] loss0.082-|Sample:1.26|
EPOCH[87/100] loss0.082-|Sample:1.29|
EPOCH[88/100] loss0.082-|Sample:1.26|
EPOCH[89/100] loss0.082-|Sample:1.25|
EPOCH[90/100] loss0.082-|Sample:1.28|
[TEST]
{'precision': array([0.29046936]), 'recall': array([0.17234374]), 'ndcg': array([0.34042917])}
EPOCH[91/100] loss0.082-|Sample:1.26|
EPOCH[92/100] loss0.082-|Sample:1.25|
EPOCH[93/100] loss0.082-|Sample:1.31|
EPOCH[94/100] loss0.082-|Sample:1.27|
EPOCH[95/100] loss0.082-|Sample:1.25|
EPOCH[96/100] loss0.081-|Sample:1.29|
EPOCH[97/100] loss0.081-|Sample:1.26|
EPOCH[98/100] loss0.082-|Sample:1.26|
EPOCH[99/100] loss0.081-|Sample:1.26|
EPOCH[100/100] loss0.081-|Sample:1.25|

Process finished with exit code 0

```