#include<Node.h>

// private



// Public

Node::Node():Node('A'){
}

Node::Node(char v){
    val = v;
    next = prev = nullptr;
}

void Node::set_val(char v){
    val = v;
}

void Node::set_next(Node* n){
    next = n;
}

void Node::set_prev(Node* n){
    prev = n;
}

char Node::get_val(){
    return val;
}

Node* Node::get_next(){
    return next;
}

Node* Node::get_prev(){
    return prev;
}
