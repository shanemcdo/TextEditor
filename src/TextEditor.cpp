#include<iostream>
#include<conio.h>
#include<fstream>
#include"TextEditor.h"

// private

void TextEditor::gotoxy(COORD coord){
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

COORD TextEditor::get_xy(){
    int x = 0;
    int y = 0;
    for(int i = 0; i < index; i++){
        if(text[i] == '\n'){
            x = 0;
            y += 1;
        }else{
            x += 1;
        }
    }
    return COORD{x, y};
}

void TextEditor::keyboard_input(){
    int key = getch();
    switch(key){
        case 17:
            running = false;
            break;
        case 0:
        case 224:
            switch(getch()){
                case 72: //up
                    move_up();
                    break;
                case 80: //down
                    move_down();
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
        case '\b':
            if(text != ""){
                text.erase(index - 1, 1);
                index -= 1;
                if(index < 0)
                    index = 0;
            }
            break;
        case '\r':
            key = '\n';
        default:
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
