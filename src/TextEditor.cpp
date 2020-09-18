#include<iostream>
#include<conio.h>
#include<fstream>
#include"TextEditor.h"

// private

void TextEditor::gotoxy(COORD coord){ // send cursor to positon on the screen
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

COORD TextEditor::get_xy(){ // get position cursor should be at based on curr
    COORD p{0, 0};
    for(Node* n = head; n != curr; n = n->get_next()){
        if(n->get_val() == '\n'){
            p.X = 0;
            p.Y += 1;
        }else{
            p.X += 1;
        }
    }
    if(!insert_at_begining)
        p.X += 1;
    return p;
}

void TextEditor::keyboard_input(){
    int key = getch();
    switch(key){
        case 27: // esc
            break;
        case 17: // ctrl q
            running = false;
            break;
        case 0: // special key
        case 224: // special key
            switch(getch()){
                case 72: //up
                    // move_up();
                    // if(index < 0)
                    //     index = 0;
                    break;
                case 80: //down
                    // move_down();
                    // if(index >= text.size())
                    //     index = text.size();
                    break;
                case 75: //left
                    if(curr == head)
                        insert_at_begining = true;
                    else if(curr->get_prev() != nullptr)
                        curr = curr->get_prev();
                    // index -= 1;
                    // if(index < 0)
                    //     index = 0;
                    break;
                case 77: //right
                    if(insert_at_begining)
                        insert_at_begining = false;
                    else if(curr->get_next() != nullptr)
                        curr = curr->get_next();
                    // index += 1;
                    // if(index >= text.size())
                    //     index = text.size();
                    break;
                default:
                    return;
            }
            break;
        case 23: // ctrl w
            system("cls");
            show_help();
            break;
        case 19: // ctrl s
            save_file(get_file_name());
            break;
        case 12: // ctrl l
            load_file(get_file_name());
            break;
        case '\b': // backspace
            {
                if(curr != nullptr){
                    Node* node_to_delete = curr;
                    curr = curr->get_prev();
                    if(curr == nullptr){
                        curr = node_to_delete->get_next();
                        head = curr;
                    }
                    node_to_delete->remove();
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
            key = '\n';
        default: // add key pressed to text
            if(head == nullptr){
                curr = new Node(key);
                head = curr;
            }else{
                if(insert_at_begining){
                    head = new Node(key);
                    curr->insert_before(head);
                    curr = head;
                }else{
                    curr->insert(new Node(key));
                    curr = curr->get_next();
                }
            }
            insert_at_begining = false;
    }
}

void TextEditor::save_file(std::string file_name){
    std::ofstream f(file_name);
    for(Node* n = head; n != nullptr; n = n->get_next())
        f << n->get_val();
    f.close();
}

void TextEditor::load_file(std::string file_name){
    delete_list();
    char ch;
    Node* tail;
    std::ifstream f(file_name);
    while(f.get(ch)){
        if(head == nullptr){
            head = new Node(ch);
            curr = head;
            tail = head;
        }else{
            curr = new Node(ch);
            tail->insert(curr);
            tail = curr;
        }
    }
    curr = head;
    insert_at_begining = true;
}

std::string TextEditor::get_file_name(){
    std::string file_name;
    system("cls");
    std::cout << "Enter file name to save to: ";
    std::cin >> file_name;
    return file_name;
}

void TextEditor::show_help(){
    std::cout << "Ctrl+w - Help menu" << std::endl;
    std::cout << "Ctrl+s - Save file" << std::endl;
    std::cout << "Ctrl+l - load file" << std::endl;
    std::cout << "Ctrl+q - quit" << std::endl;
    system("pause");
}

void TextEditor::move_up(){
    int newlines_reached = 0;
    int distance_away = 0;
    int distance_between = 0;
    int i;
    bool at_beginning = true;
    for(i = index; i > 0; i--){
        if(text[i] == '\n')
            newlines_reached += 1;
        if(newlines_reached == 0)
            distance_away++;
        else if(newlines_reached == 1)
            distance_between++;
        else{
            distance_away++;
            break;
        }
    }
    distance_away--;
    index = i + std::min(distance_away, distance_between);
}

void TextEditor::move_down(){
    int newlines_reached = 0;
    int distance_away = 0;
    int distance_between = 0;
    int i;
    for(i = index; i > 0; i--){
        if(text[i] == '\n')
            newlines_reached += 1;
        if(newlines_reached == 0)
            distance_away++;
        else{
            distance_away--;
            break;
        }
    }
    distance_away++;
    if(distance_away <= 0)
        distance_away = 1;
    newlines_reached = 0;
    for(i = index; i < text.size(); i++){
        if(text[i] == '\n')
            newlines_reached += 1;
        if(newlines_reached == 0){
        }else if(newlines_reached == 1)
            distance_between++;
        else
            break;
    }
    index = i - distance_between + std::min(distance_away, distance_between);
}

void TextEditor::print_text(){
    for(Node* n = head; n != nullptr; n = n->get_next())
        std::cout << n->get_val();
}

void TextEditor::delete_list(){
    while(head != nullptr){
        Node* node_to_delete = head;
        head = head->get_next();
        delete node_to_delete;
    }
    curr = nullptr;
}

// public

TextEditor::TextEditor(){
    text = "";
    head = nullptr;
    curr = nullptr;
    running = true;
    insert_at_begining = false;
    index = 0;
}

TextEditor::~TextEditor(){
    delete_list();
}

void TextEditor::run(){
    system("cls");
    show_help();
    system("cls");
    while(running){
        if(kbhit()){
            keyboard_input();
            system("cls");
            // std::cout << text;
            print_text();
            // Node* tail = head;
            // while(tail != nullptr && tail->get_next() != nullptr)
            //     tail = tail->get_next();
            // std::cout << std::endl;
            // for(;tail != nullptr; tail = tail->get_prev())
            //     std::cout << tail->get_val();
            gotoxy(get_xy());
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

