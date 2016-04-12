#include <iostream>
#include <cstring>

using namespace std;

void print_word(char *str){
    char *start = str;
    while(*str && *str != ' ') {
        str++;
    }
    if(! *str) {
        cout<< start;
        return ;
    }
    char *next = str + 1;
    *str = '\0';
    print_word(next);
    cout<< " "<< start;
}

const char *sentence = "I am a student.";
int main(){
    char* s = new char[100];
    strcpy(s, sentence);
    cout<< "\"";
    print_word(s);
    cout<< "\"";
    cout<< endl;
    return 0;
}
