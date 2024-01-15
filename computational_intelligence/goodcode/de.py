import numpy as np


def object(x):
    return np.sum(x ** 2)


NP = 50
D = 5
G = 100
F, CR = 0.5, 0.3  # 差分权重, 交叉概率
P = np.random.uniform(-5, 5, size=(NP, D))
F = [object(ind) for ind in P]
G_best = P[np.argmin(F)]
for g in range(G):
    for i in range(NP):
        a, b, c = P[np.random.choice(NP, 3)]
        mutant = a + F * (b - c)
        trial = np.copy(P[i])
        for j in range(D):
            if np.random.rand() < CR:
                trial[j] = mutant[j]
        if object(trial) < object(P[i]):
            P[i] = trial
        if object(trial) < object(G_best):
            G_best = trial

print(f"最优解：{G_best}")
print(f"最小值：{object(G_best)}")
