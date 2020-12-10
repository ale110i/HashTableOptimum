#include <stdio.h>
#include <vector>
#include <string>
#include "HashTableFT.hpp"
#include "HashTableFT.cpp"


template<typename type> type custom_in(){
    type input;
    int_fast64_t a;
    a = getchar_unlocked();
    while (a != '\n'){
        input += a;
        a = getchar_unlocked();
    }
    return input;
}

template<typename type> void custom_out(type element){
    for (int_fast64_t i = 0; i < element.size(); ++i){
        putchar_unlocked(element[i]);
    }
}

int main(){
    HashTable<std::string> table("", "DELETED", &hasher<std::string>);
    
    std::string line = "";
    char command = ' ';
    char symbol = ' ';
    bool success = false;
    
    while(true){
        command = getchar_unlocked();
        if (command == EOF){
            break;
        }
        symbol = getchar_unlocked();
        line = custom_in<std::string>();
        
        success = false;
        
        switch (command) {
            case '+':{
                success = table.insert_element(line);
                break;
            }
            case '?':{
                success = table.check_element(line);
                break;
            }
            case '-':{
                if (!table.check_element(line)){
                    success = false;
                }
                else {
                    success = true;
                    table.delete_element(line);
                }
                break;
            }
            default:{
                break;
            }
        }
        
        if (success){
            custom_out<std::string>("OK\n");
        }
        else {
            custom_out<std::string>("FAIL\n");
        }
    }
    
    return 0;
}
