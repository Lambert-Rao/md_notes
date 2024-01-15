import numpy as np


def object(x):
	return np.sum(x ** 2)


NP = 50
D = 5
G = 100
w, c1, c2 = 0.5, 1.5, 1.5
P = np.random.uniform(-5, 5, size=(NP, D))  # 从均匀分布(-5, 5)中随机采样
V = np.zeros((NP, D))
F = [object(ind) for ind in P]
G_best = P[np.argmin(F)]
P_best = np.copy(P)
for g in range(G):
	for i in range(NP):
		r1, r2 = np.random.uniform(size=2)
		V[i] = w * V[i] + c1 * r1 * (P_best[i] - P[i]) + c2 * r2 * (G_best - P[i])
		P[i] += V[i]
		if object(P[i]) < object(P_best[i]):
			P_best[i] = P[i]
		if object(P[i]) < object(G_best):
			G_best = P[i]

print(f"最优解：{G_best}")
print(f"最小值：{object(G_best)}")
