#ifndef TEXT_EDITOR
#define TEXT_EDITOR

#include<windows.h>
#include<string>
#include"Node.h"

class TextEditor{
private:
    std::string text;
    Node* head;
    Node* curr;
    bool running;
    int index;
    void gotoxy(COORD coord);
    COORD get_xy();
    void keyboard_input();
    void save_file(std::string file_name);
    void load_file(std::string file_name);
    std::string get_file_name();
    void show_help();
    void move_up();
    void move_down();
public:
    TextEditor();
    ~TextEditor();
    void run();
};

#endif //TEXT_EDITOR
