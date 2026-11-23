//In Rust we need to learn about ownership and borrowing.
//So I am going to use Rc, Weak, RefCell
use std::cell::RefCell; 
use std::rc::{Rc, Weak};
use std::collections::HashMap;
use std::fs;

type NodeRef = Rc<RefCell<Node>>;

#[derive(Debug)] //Automatically generate code so I can print this struct for debugging. Allows me to run println!("{:?}", root) without errors. Not required but usefull for development.
struct Node {
    name: String,
    parent: Option<Weak<RefCell<Node>>>, //Children hold a Weak reference to the parent. The parent owns the children through Rc. Prevents memory leaks and reference cycles.
    //RC only gives shared access, RefCell ensures that I can run current.children.push(child) later... This wouldn't be possible with only Rc.
    children: Vec<NodeRef>, //Rc is used to identify Reference Counted Node, which makes it so a node can have multiple owners, required for later.
}

//this is instead of the class Node in Java, rust doesn't have constructor but does this impl with a fn instead.
impl Node {
    fn new(name: &str) -> NodeRef {
        Rc::new(
            RefCell::new(Node {
                name: name.to_string(),
                parent: None,
                children: Vec::new(),
            })
        )
    }
}

fn exists_in_parents(mut current: NodeRef, target: &str) -> bool {
    loop {
        if current.borrow().name == target {   //if this leads to errors the change it to "if current.borrow().name.as_str() = target"
            return true;
        }
        //in Java, current = current.parent; it's just a node
        //Because in rust my parent is Option<Weak<RefCell<Node>>> which would be. Maybe there is a parent -> Option -> Weak reference -> RefCell -> Node
        //If we're at current: NodeRef. And we want to look at the name. Then we first have to borrow()... current.borrow().name
        let next_parent =
            current.borrow()
                .parent
                .as_ref()
                .and_then(|p| p.upgrade());
                //.unwrap() would end it here, and we would thus not go to the next step.

            match next_parent {
                Some(parent) => current = parent,
                None => return false,
        }
    }
}

fn search(current: NodeRef, graph: &HashMap<String, Vec<String>>) {
        let moves = match graph.get(&current.borrow().name) {  //moves is an Option<&Vec<String>> which won't work with my for loop bellow, need to change it first.
            Some(moves) => moves,
            None => return,
            };

            for move_name in moves {
                if exists_in_parents(current.clone(), move_name) { //need current.clone() is you only do current then it will move into the function and no longer exist...
                    continue;
                }

                let child = Node::new(move_name);

                //We need it mutable in order to set the parent
                child.borrow_mut().parent = 
                    Some(Rc::downgrade(&current));  //creates the weak reference 
                
                    //again need mutable borrow, push not add, we add a clone of the child not the actuall child since we don't want to remove the reference from future use.
                current
                    .borrow_mut()
                    .children.push(child.clone());

                search(child, graph);
        }
}

fn print_tree(node: NodeRef, depth: usize) {
    for _ in 0..depth {
        print!(" ");
    }
    println!("{}", node.borrow().name);

    let children = node.borrow().children.clone();  //really need to remember this .borrow()...
    for child in children {
        print_tree(child, depth + 1);
    }
}

fn count_paths(node: NodeRef) -> i32 {
    if node.borrow().name == "out" {
        return 1;
    }
    let mut paths = 0;

    let children = node.borrow().children.clone();
    for child in children {
        paths += count_paths(child);
    }
    paths
}

fn main() {
    let contents = fs::read_to_string("input.txt")
        .expect("This file can't read");

    let grid: Vec<String> = contents
            .lines()
            .map(|line| line.trim().to_string())
            .collect();

    let start_point = "you";
    let root = Node::new(start_point);

    let mut graph: HashMap<String, Vec<String>> = HashMap::new();

    for line in &grid {
        let parts: Vec<&str> = line.split(':').collect();
        if parts.len() != 2 {
            continue;
        }
        
        let from = parts[0].trim();

        let moves: Vec<String> = parts[1]
            .split_whitespace()
            .map(|s| s.to_string())
            .collect();
        graph.insert(from.to_string(), moves);    
    }

    search(root.clone(), &graph);
    print_tree(root.clone(), 0);
    println!("{}", count_paths(root));
}