#include<iostream>
#include<conio.h>
#include<fstream>
#include"TextEditor.h"

// private

void TextEditor::gotoxy(COORD coord){ // send cursor to positon on the screen
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

COORD TextEditor::get_xy(){ // get position cursor should be at based on curr
    COORD p{-1, 0}; // create COORD p
    if(curr == head && insert_at_begining) // at very beginning of file
        p.X++; // increase p to {0, 0}
    else if(curr != nullptr){
        Node* curr_next = curr->get_next();
        for(Node* n = head; n != curr_next; n = n->get_next()){ // loop through list and stop at curr's next
            if(n->get_val() == '\n'){ // if newline
                p.X = -1; // reset x to zero
                p.Y++; // increment y
            }else{
                p.X++; // increment x
            }
        }
        if(!insert_at_begining) // if not inserting at the beginning shift 1 to the right visually
            p.X++; // increment x
    }
    return p;
}

void TextEditor::keyboard_input(){
    int key = getch(); // get key
    switch(key){
        case 27: // esc
            break;
        case 17: // ctrl q
            running = false; // stop the main loop
            break;
        case 0: // special key
        case 224: // special key
            switch(getch()){
                case 72: //up
                    move_up();
                    // if(index < 0)
                    //     index = 0;
                    break;
                case 80: //down
                    move_down();
                    // if(index >= text.size())
                    //     index = text.size();
                    break;
                case 75: //left
                    if(curr == head) // if at beginning
                        insert_at_begining = true; // insert at beginning is true
                    else if(curr->get_prev() != nullptr) // if there is a previous
                        curr = curr->get_prev(); // set current to previous
                    // index -= 1;
                    // if(index < 0)
                    //     index = 0;
                    break;
                case 77: //right
                    if(insert_at_begining) // if insert at beginning
                        insert_at_begining = false; // insert at beginning is false
                    else if(curr != nullptr && curr->get_next() != nullptr) // if there is a next
                        curr = curr->get_next(); // set current to next
                    // index += 1;
                    // if(index >= text.size())
                    //     index = text.size();
                    break;
                default: // default case
                    break;
            }
            break;
        case 23: // ctrl w
            system("cls"); // clear screen
            show_help(); // display help menu
            break;
        case 19: // ctrl s
            save_file(get_file_name()); // save file after asking for input
            break;
        case 12: // ctrl l
            load_file(get_file_name()); // load file after asking for input
            break;
        case '\b': // backspace
            { // this brace is done to create variable node_to_delete
                if(curr != nullptr){ // if current is empty
                    Node* node_to_delete = curr; // copy address of current node
                    curr = curr->get_prev(); // set current node to previous
                    if(curr == nullptr){ // if the now current node is nullptr
                        curr = node_to_delete->get_next(); // set current node to the last current nodes next
                        head = curr; // set head to current
                        if(curr == nullptr) // if its still nullptr then the screen is empty
                            insert_at_begining = true; // insert at beginning set to true
                    }
                    node_to_delete->remove(); // delete the node that was current
                }
                // if(text != ""){
                //     text.erase(index - 1, 1);
                //     index -= 1;
                //     if(index < 0)
                //         index = 0;
                // }
            }
            break;
        case '\r': // enter key
            key = '\n'; // set key to newline character
        default: // add key pressed to text
            if(head == nullptr){ // if screen empty
                curr = new Node(key); // create current node
                head = curr; // set head equal to current node
            }else{ // if screen not empty
                if(insert_at_begining){ // if inserting at beginning (curr has to equal head here)
                    head = new Node(key); // create new head
                    curr->insert_before(head); // insert new head before current head
                    curr = head; // set current node to the same spot as head
                }else{ // not inserting at beginning
                    curr->insert(new Node(key)); // insert after current node
                    curr = curr->get_next(); // move current node to node just created
                }
            }
            insert_at_begining = false; // insert at beginning turns false after every new character
    }
}

void TextEditor::save_file(std::string file_name){ // saves text to file
    std::ofstream f(file_name); // open file
    for(Node* n = head; n != nullptr; n = n->get_next()) // loop through linked list starting with head
        f << n->get_val(); // write current character to file
    f.close(); // close file
}

void TextEditor::load_file(std::string file_name){ // loads text from a file
    delete_list(); // delete current saved list
    char ch;
    Node* tail;
    std::ifstream f(file_name); // open file
    while(f.get(ch)){ // loop through file and read character one at a time
        if(head == nullptr){ // if head is nullptr
            head = new Node(ch); // create head
            curr = head; // set current to head
            tail = head; // set tail to head
        }else{ // head exists
            curr = new Node(ch); // create new node
            tail->insert(curr); // set the next of tail to be the new node
            tail = curr; // set new node to be new tail
        }
    }
    curr = head; // set cursor at beginning
    insert_at_begining = true; // set cursor before first character
    f.close(); // close file
}

std::string TextEditor::get_file_name(){ // get user input and return a string
    std::string file_name;
    system("cls"); // clear screen
    std::cout << "Enter file name to save to: "; // output text
    std::cin >> file_name; // get input
    return file_name;
}

void TextEditor::show_help(){ // show help menu
    std::cout << "Ctrl+w - Help menu" << std::endl;
    std::cout << "Ctrl+s - Save file" << std::endl;
    std::cout << "Ctrl+l - load file" << std::endl;
    std::cout << "Ctrl+q - quit" << std::endl;
    system("pause"); // pause screen
}

void TextEditor::move_up(){ // move up one line while maintaining x positon
    int distance_away = 0; // number of characters away from previous new line character
    int line_length = 0; // length of previous line
    bool at_top = false; // if the cursor made it to the top of the screen
    for(int i = 0; i < 2;){ // create int i at zero and stop when i is above or equal to 2
        if(i == 0) distance_away++; // increment distance_away if i is zero
        else if(i == 1) line_length++; // increment line_length if i is 1
        if(curr->get_val() == '\n') i++; // increment i if the current node is a newline
        Node* prev = curr->get_prev(); // get previous node
        if(prev != nullptr) curr = prev; // track previous if its not nullptr
        else{ // if prev is nullptr
            at_top = true; // we are at the top of the file
            break; // break the loop
        }
    }
    if(at_top){ // if we are at the top of the file
        line_length--; // deincrement line_length
        distance_away -= 2; // deincrement distance_away by 2
    }
    int dist = std::min(distance_away, line_length); // find the smallest between the line_length and the distance_away
    if(dist < 0 && curr == head) insert_at_begining = true; // if dist negative and curr is at the top then put the cursor before the first char
    for(int i = 0; i < dist && curr->get_next() != nullptr; i++) curr = curr->get_next(); // track the current node dist number of steps forward
}

void TextEditor::move_down(){
    Node* n = curr;
    int distance_away = 0;
    int line_length = 0;
    while(n->get_val() != '\n'){
        distance_away++;
        Node* prev = n->get_prev();
        if(prev != nullptr) n = prev;
        else break;
    }
    if(insert_at_begining) distance_away--;
    do{
        Node* next = curr->get_next();
        if(next != nullptr) curr = next;
        else return;
    }while(curr->get_val() != '\n');
    n = curr->get_next();
    while(n != nullptr && n->get_val() != '\n'){
        line_length++;
        Node* next = n->get_next();
        if(next != nullptr) n = next;
        else break;
    }
    int dist = std::min(distance_away, line_length);
    for(int i = 0; i < dist && curr->get_next() != nullptr; i++) curr = curr->get_next();
    insert_at_begining = false; // insert at beginning is false
    // int newlines_reached = 0;
    // int distance_away = 0;
    // int distance_between = 0;
    // int i;
    // for(i = index; i > 0; i--){
    //     if(text[i] == '\n')
    //         newlines_reached += 1;
    //     if(newlines_reached == 0)
    //         distance_away++;
    //     else{
    //         distance_away--;
    //         break;
    //     }
    // }
    // distance_away++;
    // if(distance_away <= 0)
    //     distance_away = 1;
    // newlines_reached = 0;
    // for(i = index; i < text.size(); i++){
    //     if(text[i] == '\n')
    //         newlines_reached += 1;
    //     if(newlines_reached == 0){
    //     }else if(newlines_reached == 1)
    //         distance_between++;
    //     else
    //         break;
    // }
    // index = i - distance_between + std::min(distance_away, distance_between);
}

void TextEditor::print_text(){ // prints the contents of the linked list
    for(Node* n = head; n != nullptr; n = n->get_next()) // loop through entire list starting with head
        std::cout << n->get_val(); // print current character in list
}

void TextEditor::delete_list(){ // deletes the linked list
    while(head != nullptr){ // loop while head isn't nullptr
        Node* node_to_delete = head; // save current node memory adress to delete
        head = head->get_next(); // track head to next node
        delete node_to_delete; // delete saved node
    } // by the end head is nullptr because that is the exit condition
    curr = nullptr; // set curr also equal to nullptr
}

// public

TextEditor::TextEditor(){ // constructor
    text = "";
    head = nullptr;
    curr = nullptr;
    running = true;
    insert_at_begining = true;
    index = 0;
}

TextEditor::~TextEditor(){ // deconstructor
    delete_list(); // destroy list
}

void TextEditor::run(){
    system("cls"); // clear screen
    show_help(); // show help menu
    system("cls"); // clear screen
    while(running){ // main loop
        if(kbhit()){ // if a key has been touched
            keyboard_input(); // get keyboard input and act on it
            system("cls"); // clear screen
            // std::cout << text;
            print_text(); // print screen
            // Node* tail = head;
            // while(tail != nullptr && tail->get_next() != nullptr)
            //     tail = tail->get_next();
            // std::cout << std::endl;
            // for(;tail != nullptr; tail = tail->get_prev())
            //     std::cout << tail->get_val();
            gotoxy(get_xy()); // move cursor to curr
        }
    }
    // Node* n = new Node('1');
    // n->insert_before(new Node('2'));
    // n->get_prev()->insert_before(new Node('3'));
    // Node* h = n->get_prev()->get_prev();
    // while(h != nullptr){
    //     Node* d = h;
    //     std::cout << h->get_val();
    //     h = h->get_next();
    //     delete d;
    // }
}

