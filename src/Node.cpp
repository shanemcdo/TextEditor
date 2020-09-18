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

void Node::insert(Node* new_node){
    if(next != nullptr){
        new_node->set_next(next);
        next->set_prev(new_node);
    }
    next = new_node;
    new_node->set_prev(this);
}

void Node::insert_before(Node* new_node){
    if(prev != nullptr){
        new_node->set_prev(prev);
        prev->set_next(new_node);
    }
    prev = new_node;
    new_node->set_next(this);
}

void Node::remove(){
    if(prev != nullptr)
        prev->set_next(next);
    if(next != nullptr)
        next->set_prev(prev);
    delete this;
}
