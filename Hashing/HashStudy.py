'''
CSCI 3104 PS4 Problem#4
Last names & hash functions
'''

import random
import os
import matplotlib.pyplot as plt
import threading

#Returns a list of last names from file
def parse_file(fileName):
    print("Parsing",fileName,"...")
    try:
        this_folder = os.path.dirname(os.path.abspath(__file__))
        file_name = os.path.join(this_folder, fileName)
        last_names_file = open(file_name)
    except OSError:
      print("Error! Cannot open: ", file_name)

    if(last_names_file):
        #readlines() reads until EOF and returns a list containing the lines
        lines = last_names_file.readlines()
        #Split into list (using \t as delimiter), index 0 always has the last name
        last_names = [line.split('\t')[0] for line in lines]
        print("Read in", len(last_names), "last names.")
        return last_names
    else:
        return "Error"
'''
 Returns index of a letter from Alphabet 
 f('A') = 1 , f('Z') = 26
'''
def f(letter):
    #A = (65 - 64) = 1
    ordinal_val = ord(letter) - 64
    if(ordinal_val >= 1 or ordinal_val <= 26):
        return ordinal_val 
    else:
        print("Not a letter!")
        return 

'''
 h_1(x) hash function
 l is the number of buckets in hash table
'''
def h1(x,l):
    sum = 0
    for xi in x:
        sum += f(xi)
    return sum % l

'''
h_2(x) hash function
'''
def h2(x,l,list_ai):
    sum = 0
    for i in range(len(x)):
        sum += f(x[i]) * list_ai[i]
    return sum % l

'''
 Generates a list of uniformaly random integers ai
 one for each letter in a name from {0,...,10000}
'''
def generate_list_ai(l, names):
    max_len = len(max(names, key = len))
    list_ai = [random.randint(0,10000) for i in range(max_len)]
    return list_ai

def gen_histogram(y, fileName, func_name):
    x = list(range(len(y)))
    plt.figure(figsize=(8,4))
    plt.plot(x, y, label=func_name)
    plt.ylabel("Count")
    plt.xlabel("Hash locations " + func_name)
    plt.legend()
    plt.title("Hash table load for function " + func_name)
    plt.savefig(fileName)
    plt.close()

#Part C
def find_longest_chain(last_names, l, func_name, list_ai):
    #Copies the list
    shuff_names = last_names[:]

    #Shuffle the list in place
    random.shuffle(shuff_names)

    #Made a list of all "bins"
    y = [0 for i in range(l)]

    longest_chain = []

    if func_name == "h1":
        for lname in shuff_names:
            y[h1(lname,l)] += 1
            longest_chain.append(max(y))
    else:
        for lname in shuff_names:
            y[h2(lname,l,list_ai)] += 1
            longest_chain.append(max(y))

    #Plotting
    x = list(range(len(longest_chain)))
    plt.figure(figsize=(8,4))
    plt.plot(x,longest_chain)
    plt.ylabel("Length of longest chain")
    plt.xlabel("Items hash, n")
    plt.title("Length of longest chain vs n for " + func_name)
    plt.savefig("longest_chain_plot_" + func_name + ".png")
    plt.close()

#Part D
def gen_collision_graph(last_names,l, func_name, list_ai):
    primes = prime_numbers(l)
    total_coll = []

    #Copies the list
    shuff_names = last_names[:]

    #Shuffle the list in place
    random.shuffle(shuff_names)

    for i in primes:
        y = [0 for j in range(i)]
        for lname in shuff_names:
            if (func_name == "h1"):
                y[h1(lname,i)] +=1
            else:
                y[h2(lname,i,list_ai)] += 1
        
        #The first one is not a collision...
        non_zero = len([j for j in y if j != 0])
        total_coll.append(sum(y) - non_zero)

    #Plot
    plt.figure(figsize=(8,4))
    x = primes
    plt.plot(x,total_coll)
    plt.ylabel("Total collisions")
    plt.xlabel("l")
    plt.title("Total collisions vs l for " + func_name)
    plt.savefig("collisions_vs_l_" + func_name + ".png")
    plt.close()

def prime_numbers(n):
    primes = []
    for num in range(1, n + 1):
        if num > 1:
            for i in range(2, num):
                if (num % i) == 0:
                    break
            else:
                primes.append(num)
    return primes

    
def main():
    l = 5987
    last_names = parse_file("dist.all.last.txt")

    ##################
    #Part A
    ##################

    #Uniform random 50% sample of last names
    unif_rand_sample_half = random.sample(last_names, k=int(len(last_names)/2) )
    list_ai = generate_list_ai(l,last_names)

    #Lists to count hash values
    y_h1_list = [0 for i in range(l)]
    y_h2_list = [0 for i in range(l)]

    for lname in unif_rand_sample_half:
        y_h1_list[h1(lname,l)] += 1

    for lname in unif_rand_sample_half:
        y_h2_list[h2(lname,l,list_ai)] += 1

    print("ai values:", list_ai)

    gen_histogram(y_h1_list, "h1_plot.png", "h1(x)")
    gen_histogram(y_h2_list, "h2_plot.png", "h2(x)")

    ##################
    #Part C
    ##################

    find_longest_chain(last_names,l,"h1", list_ai)
    find_longest_chain(last_names,l,"h2", list_ai)

    ##################
    #Part D
    ##################

    gen_collision_graph(last_names,l,"h1",list_ai)
    gen_collision_graph(last_names,l,"h2",list_ai)

    
if __name__ == '__main__':
    main()