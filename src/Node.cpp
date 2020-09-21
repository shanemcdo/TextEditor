#include<Node.h>

Node::Node():Node('A'){} // call constructor with val defaulting to 'A'

Node::Node(char v){ // 
    val = v; // set val equal to v
    next = prev = nullptr; // set next and prev equal to nullptr
}

void Node::set_val(char v){ // set val
    val = v;
}

void Node::set_next(Node* n){ // set next
    next = n;
}

void Node::set_prev(Node* n){ // set previous
    prev = n;
}

char Node::get_val(){ // gets the value
    return val;
}

Node* Node::get_next(){ // gets pointer to next
    return next;
}

Node* Node::get_prev(){ // gets pointer to previous
    return prev;
}

void Node::insert(Node* new_node){ // insert a new node after
    if(next != nullptr){ // if next exists
        new_node->set_next(next); // set new_node's next to next
        next->set_prev(new_node); // set next's previous to new_node
    }
    next = new_node; // set next to new_node
    new_node->set_prev(this); // set new_node's previous to current node
}

void Node::insert_before(Node* new_node){ // insert new node before
    if(prev != nullptr){ // if prev exists
        new_node->set_prev(prev); // set new_node's prev to prev
        prev->set_next(new_node); // set prev's next to new_node
    }
    prev = new_node; // set prev to new_node
    new_node->set_next(this); // set new_node's next to current node
}

void Node::remove(){ // delete current node
    if(prev != nullptr) // if previous exists
        prev->set_next(next); // set previous's next to next
    if(next != nullptr)
        next->set_prev(prev); // set previous's prev to prev
    delete this; // delete node
}
