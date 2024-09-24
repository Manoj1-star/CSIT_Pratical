# Write a Program to Implement Genetics algorithm using Python

import random

# Parameters
population_size = 20
gene_length = 5  # Number of bits in each chromosome (5 bits for values between 0 and 31)
mutation_rate = 0.01
generations = 50

# Create a random individual
def create_individual():
    return [random.randint(0, 1) for _ in range(gene_length)]

# Create initial population
def create_population():
    return [create_individual() for _ in range(population_size)]

# Decode a chromosome to a number
def decode_chromosome(chromosome):
    return int(''.join(map(str, chromosome)), 2)

# Fitness function: We want to maximize x^2
def fitness(individual):
    x = decode_chromosome(individual)
    return x**2

# Selection function: Tournament selection
def select(population):
    tournament = random.sample(population, 3)
    tournament.sort(key=fitness, reverse=True)
    return tournament[0]

# Crossover function: Single-point crossover
def crossover(parent1, parent2):
    point = random.randint(1, gene_length - 1)
    child1 = parent1[:point] + parent2[point:]
    child2 = parent2[:point] + parent1[point:]
    return child1, child2

# Mutation function
def mutate(individual):
    for i in range(gene_length):
        if random.random() < mutation_rate:
            individual[i] = 1 - individual[i]

# Main Genetic Algorithm
def genetic_algorithm():
    population = create_population()

    for generation in range(generations):
        population = sorted(population, key=fitness, reverse=True)
        print(f'Generation {generation}: Best fitness = {fitness(population[0])}')
        
        new_population = population[:2]  # Elitism: carry over the best 2 individuals
        
        while len(new_population) < population_size:
            parent1 = select(population)
            parent2 = select(population)
            child1, child2 = crossover(parent1, parent2)
            mutate(child1)
            mutate(child2)
            new_population.extend([child1, child2])
        
        population = new_population[:population_size]
    
    best_individual = max(population, key=fitness)
    best_value = decode_chromosome(best_individual)
    print(f'Best individual: {best_individual}')
    print(f'Best value: {best_value}')
    print(f'Best fitness: {fitness(best_individual)}')

# Run the genetic algorithm
genetic_algorithm()
