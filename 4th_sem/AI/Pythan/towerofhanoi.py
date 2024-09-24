 # Write a Program to Implement Tower of Hanoi using Python.

print("Name : Manoj KC")
print("Level : Bsc. Csit(4th sem) ")
print("Section : B")

# Recursive Python function to solve Tower of Hanoi
def TowerOfHanoi(n, from_rod, to_rod, aux_rod):
    if n == 1:
        print(f"Move disk 1 from rod {from_rod} to rod {to_rod}")
        return
    TowerOfHanoi(n-1, from_rod, aux_rod, to_rod)
    print(f"Move disk {n} from rod {from_rod} to rod {to_rod}")
    TowerOfHanoi(n-1, aux_rod, to_rod, from_rod)

# Driver code
n = 4  # Number of disks
TowerOfHanoi(n, 'A', 'C', 'B')  # A, B, and C are the names of the rods
