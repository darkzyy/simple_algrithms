#include <iostream>
#include <string>
#include <cstring>
#include <cstdint>
#include <cstdio>
#include <vector>
#include "debug.h"


using namespace std;

#define ALL_ONE ((uint32_t) (~0))

enum {
    forbidden = 0,
    unknown = 1,
    allow = 2
};

struct  node {
    uint32_t *array;
    int rule;
};

node table[1<<16];

uint32_t ip_to_int(string& str) {
    uint32_t ip[4];
    const char *ip_str = str.c_str();
    sscanf(ip_str, "%d.%d.%d.%d", &ip[0], &ip[1], &ip[2], &ip[3]);
    return (ip[0] << 24) | (ip[1] << 16) | (ip[2] << 8) | ip[3];
}

void add_entry(string str){
    unsigned int rule2;
    uint32_t mask = 32;
    unsigned long ip_start, ip_len;
    if(str.compare(0, 5, "allow") == 0){
        rule2 = allow;
        ip_start = 6;
    }
    else {
        rule2 = forbidden;
        ip_start = 5;
    }

    unsigned long found = str.find('/');
    if(found == string::npos){
        ip_len = str.length() - ip_start;
    }
    else {
        ip_len = found - ip_start;
        sscanf(str.substr(found + 1).c_str(), "%d", &mask);
    }

    string ip_str = str.substr(ip_start, ip_len);
    uint32_t ip = ip_to_int(ip_str);

    //cout << str << endl;
    ////log_var(ip);
    //log_var(rule2);

    uint32_t entry_start, entry_end;
    entry_start = mask == 32 ? ip : (ip & (ALL_ONE << (32 - mask)));
    entry_end = mask == 32 ? ip : (ip | (ALL_ONE >> mask));
    //log_var(entry_start);
    //log_var(entry_end);
    if(mask <= 16) {
        uint32_t i;
        for(i = (entry_start >> 16); i <= (entry_end >> 16); i++) {
            table[i].rule = rule2;
            table[i].array = nullptr;
        }
    }
    else {
        unsigned int idx = entry_start >> 16;
        table[idx].rule = unknown;
        table[idx].array = new uint32_t[1<<16];
        memset((void *)table[idx].array, unknown, 1 << 16);
        uint32_t i;
        for(i = (entry_start & (ALL_ONE >> 16)); i <= (entry_end & (ALL_ONE >> 16)); i++) {
            table[idx].array[i] = rule2;
        }
    }
}

bool pass(string str) {
    uint32_t ip = ip_to_int(str);
    //cout << str << endl;
    //log_var(ip);
    uint32_t hi = ip >> 16;
    uint32_t lo = ip & (ALL_ONE >> 16);
    if(table[hi].rule == allow) {
        return true;
    }
    else if(table[hi].rule == forbidden) {
        return false;
    }
    else {
        if(table[hi].array[lo] == allow){
            return true;
        }
        else{
            return false;
        }
    }
}

int main(){
    int n_entries, n_tests, i;
    char buffer[100];
    cin >> n_entries;
    cin >> n_tests;
    //cin >> buffer;
    vector<string> v;
    for(i = 0; i <= n_entries; i++) {
        cin.getline(buffer, 100);
        if(strlen(buffer) >0) {
            v.push_back((string) buffer);
        }
    }

    for(i = 0; i < n_entries; i++) {
        add_entry(v[n_entries - i - 1]);
    }

    for(i = 0; i < n_tests; i++) {
        cin.getline(buffer, 100);
        if(pass((string) buffer)){
            cout << "YES" <<endl;
        }
        else {
            cout << "NO" <<endl;
        }
    }
    return 0;
}
