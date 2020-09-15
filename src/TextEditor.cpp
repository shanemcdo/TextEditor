#include<iostream>
#include<conio.h>
#include<fstream>
#include<sstream>
#include"TextEditor.h"

// private

void TextEditor::gotoxy(COORD coord){ // send cursor to positon on the screen
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

COORD TextEditor::get_xy(){ // get position cursor should be at based on index
    COORD p{0, 0};
    for(int i = 0; i < index; i++){
        if(text[i] == '\n'){
            p.X = 0;
            p.Y += 1;
        }else{
            p.X += 1;
        }
    }
    return p;
}

void TextEditor::keyboard_input(){
    int key = getch();
    switch(key){
        case 17: // ctrl q
            running = false;
            break;
        case 0: // special key
        case 224: // special key
            switch(getch()){
                case 72: //up
                    move_up();
                    if(index < 0)
                        index = 0;
                    break;
                case 80: //down
                    move_down();
                    if(index >= text.size())
                        index = text.size();
                    break;
                case 75: //left
                    index -= 1;
                    if(index < 0)
                        index = 0;
                    break;
                case 77: //right
                    index += 1;
                    if(index >= text.size())
                        index = text.size();
                    break;
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
            if(text != ""){
                text.erase(index - 1, 1);
                index -= 1;
                if(index < 0)
                    index = 0;
            }
            break;
        case '\r': // enter key
            key = '\n';
        case 27: // esc
            break;
        default: // add key pressed to text
            text.insert(index, std::string(1, key));
            index += 1;
            if(index >= text.size())
                index = text.size();
    }
}

void TextEditor::save_file(std::string file_name){
    std::ofstream f(file_name);
    f << text;
    f.close();
}

void TextEditor::load_file(std::string file_name){
    std::ostringstream strm;
    std::ifstream f(file_name);
    strm << f.rdbuf();
    f.close();
    text = "";
    text = strm.str();
    index = 0;
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

// public

TextEditor::TextEditor(){
    text = "";
    running = true;
    index = 0;
}

void TextEditor::run(){
    system("cls");
    show_help();
    system("cls");
    while(running){
        if(kbhit()){
            keyboard_input();
            system("cls");
            std::cout << text;
            gotoxy(get_xy());
        }
    }
}
