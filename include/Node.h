#ifndef NODE_H
#define NODE_H

class Node {
private:
    char val; // value stored in node
    Node* next; // pointer to next node
    Node* prev; // pointer to previous node
public:
    Node(); // constructor
    Node(char v); // constructor that intializes val
    void set_val(char v); // sets val
    void set_next(Node* n); // sets next
    void set_prev(Node* n); // sets prev
    char get_val(); // returns val
    Node* get_next(); // returns next
    Node* get_prev(); // returns prev
    void insert(Node* new_node); // insert node after
    void insert_before(Node* new_node); // insert node before
    void remove(); // delete node
};

#endif /* NODE_H */
