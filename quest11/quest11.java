//I wanted to try doing this exercise using a search-tree, since I haven't done that in ages. 
package quest11;
import java.util.*;

class Node {
    String name;
    Node parent;
    ArrayList<Node> children = new ArrayList<>();

    Node(String name, Node parent) {
        this.name = name;
        this.parent = parent;
    }
}

public class quest11 { 

static boolean existsInParents(Node current, String target) {
    while (current != null) {
        if (current.name.equals(target)) {
            return true;
        }
        current = current.parent;
    }
    return false;
}

static void search(Node current, HashMap<String, ArrayList<String>> graph) {
    ArrayList<String> moves = graph.get(current.name);
    if (moves == null) {
        return;
    }
    for (String move : moves) {
        if (existsInParents(current, move)) {
            continue;
        }
        Node child = new Node(move, current);
        current.children.add(child);
        search(child, graph);
    }
}

//This is superflous and not needed for the exercise, but just something I wanted for fun... Still don't get the print exactly like I want it... 
static void printTree(Node node, int depth) {
    for (int i = 0; i < depth; i++) {
        System.out.print(" ");
        }
    System.out.println(node.name);
    for (Node child : node.children) {
        printTree(child, depth + 1);
    }
}

static int countPaths(Node node) {
    if (node.name.equals("out")) {
        return 1;
    }

    int paths = 0;

    for (Node child : node.children) {
        paths += countPaths(child);
    }

    return paths;
}

    public static void main(String[] args) {
            String[] grid = {
                "aaa: you hhh",
                "you: bbb ccc",
                "bbb: ddd eee",
                "ccc: ddd eee fff",
                "ddd: ggg",
                "eee: out",
                "fff: out",
                "ggg: out",
                "hhh: ccc fff iii",
                "iii: out"
            };

            String startPoint = "you";
            int paths = 0;
            Node root = new Node(startPoint, null);

            HashMap<String, ArrayList<String>> graph = new HashMap<>();

            for (String line : grid) {
                String[] parts = line.split(": ");
                String from = parts[0];
                ArrayList<String> moves = new ArrayList<>();
                for (String move : parts[1].split(" ")) {
                    moves.add(move);
                }
                graph.put(from, moves);
            }
            
            search(root, graph);  
            printTree(root, paths); 
            System.out.println(countPaths(root));       
    }
}