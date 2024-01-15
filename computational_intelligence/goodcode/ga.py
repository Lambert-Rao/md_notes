import numpy as np
from numpy.random import randint,rand
import math

def object_function(x):
    return -x ** 2 + 5

def fitness(x:np.array):
    y = object_function(x)
    min = np.min(y)
    return y - min
    

def rand_init(min: np.float64,max:np.float64,scale:np.float64,popsize:int):
    bit_num = math.ceil(math.log2(max - min)/scale)
    return np.random.randint(0,2,(popsize,bit_num))

def decode(bin:np.array,min,max,scale):
    delta = (max - min) / (2 ** bin.shape[0] - 1)
    result:np.float64 = 0
    for i in range(bin.shape[0]):
        result += (bin[i] * (2 ** i))* delta
    return min + result 

def decode_population(population:np.array,min,max,scale):
    result = []
    for i in range(population.shape[0]):
        result.append(decode(population[i],min,max,scale))
    return np.array(result)

def wheel_select(fitnesses:np.array,population:np.array) -> np.array:
    fitness_sum = np.sum(fitnesses)
    new_population = []  # 创建一个空的列表
    probability = fitnesses / fitness_sum
    for _ in range(population.shape[0]):
        index = np.random.choice(range(population.shape[0]), p=probability)
        new_population.append(population[index])  # 将选中的个体添加到列表中
    return np.array(new_population)  # 将列表转换为numpy数组

def crossover(population:np.array,crossover_rate:np.float64=0.05):
    """
    :param crossover_rate: 交叉率,随机选cr对个体进行交叉
    """ 
    crossover_num = math.ceil(population.shape[0] * crossover_rate)
    for _ in range(crossover_num):
        a = randint(0,population.shape[0])
        b = randint(0,population.shape[0])
        cross_point = randint(0,population.shape[1])
        population[a][cross_point:],population[b][cross_point:] = population[b][cross_point:],population[a][cross_point:]
    return population

def mutation(population:np.array,mutation_rate:np.float64):
    """
    :param mutation_rate: 变异率,这里是每个基因位点的变异率
    """
    for _ in range(population.shape[0]):
        for j in range(population.shape[1]):
            if rand() < mutation_rate:
                population[_][j] = 1 - population[_][j]
    return population


def main(min = -5,max = 5,scale = 1e-2,popsize=20,iterations=100):
    population = rand_init(min,max,scale,popsize)
    for _ in range(iterations):
        x = decode_population(population,min,max,scale)
        fitnesses = fitness(x)
        population = wheel_select(fitnesses,population)
        population = crossover(population)
        population = mutation(population,0.01)
    y = object_function(decode_population(population,min,max,scale))
    best_index = np.argmax(y)
    print("best x: ",decode(population[best_index],min,max,scale))
    print("best y: ",y[best_index])
        

if __name__ == "__main__":
    main()

