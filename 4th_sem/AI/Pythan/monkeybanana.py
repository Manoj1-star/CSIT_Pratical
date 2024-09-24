print("Name : Manoj KC")
print("Level : Bsc. Csit(4th sem) ")
print("Section : B")

from typing import Set

# Define Position class with a string representation for locations
class Position:
    def __str__(self):
        return getattr(self, "locname", "unknown")  # Default to "unknown" if locname not set

# Define classes with HasHeight and HasPosition properties
class HasHeight:
    height: int

class HasPosition:
    at: Position

# Define Monkey, PalmTree, Box, and Banana classes
class Monkey(HasHeight, HasPosition):
    pass

class PalmTree(HasHeight, HasPosition):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.height = 2  # Default height for palm trees

class Box(HasHeight, HasPosition):
    pass

class Banana(HasHeight, HasPosition):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.owner = None  # Initialize owner as None
        self.height = 0    # Initialize height
        self.attached = None  # Initialize attached palm tree
        self.at = None     # Initialize position attribute

# World class to store locations
class World:
    locations: Set[Position]

# Initialize positions
p1 = Position()
p1.locname = "Position A"
p2 = Position()
p2.locname = "Position B"
p3 = Position()
p3.locname = "Position C"

# Initialize world, monkey, box, palm tree, and banana
w = World()
w.locations = {p1, p2, p3}

m = Monkey()
m.height = 0  # Monkey starts on the ground
m.at = p1

box = Box()
box.height = 2
box.at = p2

palm_tree = PalmTree()
palm_tree.at = p3

banana = Banana()
banana.attached = palm_tree

# Action definitions
def go(monkey: Monkey, where: Position):
    assert where in w.locations
    assert monkey.height < 1, "Monkey can only move while on the ground"
    monkey.at = where
    return f"Monkey moved to {where}"

def push(monkey: Monkey, box: Box, where: Position):
    assert monkey.at == box.at
    assert where in w.locations
    assert monkey.height < 1, "Monkey can only move the box while on the ground"
    box.at = where
    return f"Monkey moved box to {where}"

def climb_up(monkey: Monkey, box: Box):
    assert monkey.at == box.at
    monkey.height += box.height
    return "Monkey climbs the box"

def grasp(monkey: Monkey, banana: Banana):
    print(f"Monkey's position: {monkey.at}, Banana's position: {banana.at}")
    print(f"Monkey's height: {monkey.height}, Banana's height: {banana.height}")
    assert monkey.height == banana.height, f"Monkey height {monkey.height} does not match banana height {banana.height}"
    assert monkey.at == banana.at, f"Monkey is not at the same position as the banana"
    banana.owner = monkey
    return "Monkey takes the banana"

# Inference functions
def infer_owner_at(palm_tree: PalmTree, banana: Banana):
    assert banana.attached == palm_tree
    banana.at = palm_tree.at
    return "Remembered that if banana is on the palm tree, its location is where the palm tree is"

def infer_banana_height(palm_tree: PalmTree, banana: Banana):
    assert banana.attached == palm_tree
    banana.height = palm_tree.height
    return "Remembered that if banana is on the tree, its height equals the tree's height"

# Run the actions manually
def run_scenario():
    actions = [
        lambda: go(m, p2),                      # Move monkey to Position B
        lambda: push(m, box, p3),              # Push box to Position C
        lambda: infer_owner_at(palm_tree, banana),  # Ensure banana's location is updated
        lambda: infer_banana_height(palm_tree, banana),  # Infer banana height from palm tree
        lambda: go(m, p3),                     # Move monkey to Position C (where the banana is)
        lambda: climb_up(m, box),              # Climb up the box
        lambda: grasp(m, banana)               # Attempt to grasp the banana
    ]
    
    results = []
    for action in actions:
        try:
            result = action()
            results.append(result)
        except AssertionError as e:
            results.append(f"AssertionError: {e}")
            # Print the current state for debugging
            results.append(f"Monkey position: {m.at}, height: {m.height}")
            results.append(f"Box position: {box.at}, height: {box.height}")
            results.append(f"Banana position: {banana.at if banana.at else 'None'}, height: {banana.height}, owner: {banana.owner}")
            results.append(f"PalmTree position: {palm_tree.at}, height: {palm_tree.height}")
            break
    
    return results

# Ensure the banana's position is updated when attached to the palm tree
def infer_owner_at(palm_tree: PalmTree, banana: Banana):
    assert banana.attached == palm_tree, "Banana is not attached to the palm tree"
    banana.at = palm_tree.at
    return f"Banana's position updated to {banana.at} (Palm tree's location)"

# Execute the scenario and print results
print('\n'.join(run_scenario()))
