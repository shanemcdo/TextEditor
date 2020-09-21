#ifndef TEXT_EDITOR
#define TEXT_EDITOR

#include<windows.h>
#include<string>
#include"Node.h"

class TextEditor{
private:
    Node* head;
    Node* curr;
    bool running;
    bool insert_at_begining;
    void gotoxy(COORD coord);
    COORD get_xy();
    void keyboard_input();
    void save_file(std::string file_name);
    void load_file(std::string file_name);
    std::string get_file_name();
    void show_help();
    void move_up();
    void move_down();
    void print_text();
    void delete_list();
    void insert_character(char key);
    void delete_character();
public:
    TextEditor();
    ~TextEditor();
    void run();
};

#endif //TEXT_EDITOR
