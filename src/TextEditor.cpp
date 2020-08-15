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
                    break;
                case 80: //down
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
