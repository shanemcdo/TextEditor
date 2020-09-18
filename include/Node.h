#ifndef NODE_H
#define NODE_H

class Node {
private:
    char val;
    Node* next;
    Node* prev;
public:
    Node();
    Node(char v);
    void set_val(char v);
    void set_next(Node* n);
    void set_prev(Node* n);
    char get_val();
    Node* get_next();
    Node* get_prev();
    void insert(Node* new_node);
    void remove();
};

#endif /* NODE_H */
