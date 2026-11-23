from pathlib import Path
script_dir = Path(__file__).parent
input_file = script_dir / "input.txt"
#Never worked with trees in Python so this was a nice exercise
class Node:
    def __init__(self, name, parent=None):
        self.name = name
        #Java, Node parent;
        self.parent = parent
        #Java ArrayList<Node> children = new ArrayList<>();
        self.children = []

def exists_in_parents(current, target):
    while current is not None:
        if current.name == target:
            return True
        current = current.parent
    return False

def search(current, graph):
    #Java, ArrayList<String> moves = graph.get(current.name);
    #Python = dict.get(). dict no arrayList
    moves = graph.get(current.name)
    if moves is None:
        return
    for move in moves:
        if exists_in_parents(current, move):
            continue
        #Java: Node child = new Node(move, current)
        child = Node(move, current)
        current.children.append(child)
        search(child, graph)

def print_tree(node, depth):
    print(" " * depth + node.name)
    for child in node.children:
        print_tree(child, depth + 1)

def count_paths(node):
    if node.name == "out":
        return 1
    paths = 0
    for child in node.children:
        paths += count_paths(child)
    return paths

def main():
    grid = []

    with open(input_file, "r") as f:
        for line in f:
            grid.append(line.strip())

    start_point = "you"
    root = Node(start_point)

    #Java uses HashMap<String,ArrayList<String>>
    graph = {}

    for line in grid:
        parts = line.split(": ")
        from_node = parts[0]

        #Java ArrayList<String> move = new ArrayList<>();
        moves = []
        for move in parts[1].split(" "):
            moves.append(move)
        graph[from_node] = moves
    search(root, graph)
    print_tree(root, 0)
    print("Paths to out: ", count_paths(root))

main()