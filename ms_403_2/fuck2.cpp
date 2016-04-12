#include <iostream>
#include <string>
#include <cstring>
#include <cstdint>
#include <cstdio>
#include <vector>



using namespace std;

#define ALL_ONE ((uint32_t) (~0))

enum {
    forbidden = 0,
    unknown = 1,
    allow = 2
};

struct node {
    node *left, *right;
    uint32_t rule;
};

node root;

uint32_t ip_to_int(string& str) {
    uint32_t ip[4];
    const char *ip_str = str.c_str();
    sscanf(ip_str, "%d.%d.%d.%d", &ip[0], &ip[1], &ip[2], &ip[3]);
    return (ip[0] << 24) | (ip[1] << 16) | (ip[2] << 8) | ip[3];
}

void add_node(node* n, uint32_t ip, uint32_t mask, uint32_t rule) {
    if(mask == 0) {
        n->rule = rule;
        n->left = nullptr;
        n->right = nullptr;
    }
    else {
        if(n->left == nullptr) {
            n->left = new node;
            n->left->left = nullptr;
            n->left->right = nullptr;
            n->left->rule = n->rule;
        }
        if(n->right == nullptr) {
            n->right = new node;
            n->right->left = nullptr;
            n->right->right = nullptr;
            n->right->rule = n->rule;
        }
        if(0x80000000 & ip) {
            if(n->rule != rule && n->rule != unknown) {
                n->rule = unknown;
            }
            add_node(n->left, ip << 1, mask - 1, rule);
        }
        else {
            if(n->rule != rule && n->rule != unknown) {
                n->left->rule = n->rule;
                n->rule = unknown;
            }
            add_node(n->right, ip << 1, mask - 1, rule);
        }
    }
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

    add_node(&root, ip, mask, rule2);
}

bool find_node(node *n, uint32_t ip) {
    if(n->rule == forbidden) {
        return false;
    }
    else if(n->rule == allow) {
        return true;
    }
    else {
        if(0x80000000 & ip) {
            if(n->left == nullptr) {
                return true;
            }
            else {
                return find_node(n->left, ip << 1);
            }
        }
        else {
            if(n->right == nullptr) {
                return true;
            }
            else {
                return find_node(n->right, ip << 1);
            }
        }
    }
}

bool pass(string str) {
    uint32_t ip = ip_to_int(str);
    return find_node(&root, ip);
}

int main(){
    root.left = nullptr;
    root.right = nullptr;
    root.rule = allow;
    int n_entries, n_tests, i;
    cin >> n_entries;
    cin >> n_tests;
    //cin >> buffer;
    vector<char*> v;
    for(i = 0; i <= n_entries; i++) {
        char* buffer = new char[26];
        cin.getline(buffer, 26);
        if(strlen(buffer) >0) {
            v.push_back(buffer);
        }
    }

    for(i = 0; i < n_entries; i++) {
        add_entry(v[n_entries - i - 1]);
    }

    char buffer[32];
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

