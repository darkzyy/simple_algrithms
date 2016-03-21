#include <iostream>
using namespace std;

struct node {
    int content;
    node *next;
};

int is_joined_simple(node *n1, node *n2) {
    node *p1, *p2;
    p1 = n1;
    p2 = n2;
    while(n1 != NULL) {
        p1 = n1;
        n1 = n1->next;
    }
    while(n2 != NULL) {
        p2 = n2;
        n2 = n2->next;
    }
    return p1 == p2;
}

node *test_cycle(node *n){
    node *p1, *p2;
    p1 = n;
    p2 = n;
    while(p1 != NULL && p1->next != NULL) {
        p1 = p1->next->next;
        p2 = p2->next;
        if(p1 == p2) {
            return p1;
        }
    }
    return NULL;
}

int is_joined(node *n1, node *n2){
    node* has_cycle1;
    node* has_cycle2;
    has_cycle1 = test_cycle(n1);
    has_cycle2 = test_cycle(n2);
    if(has_cycle1 == NULL && has_cycle1 == NULL) {
        return is_joined_simple(n1, n2);
    }
    if((!has_cycle1 && has_cycle2) || (!has_cycle2 && has_cycle1)) {
        return 0;
    }
    n1 = has_cycle1;
    n2 = has_cycle2;
    node *p1 = n1;
    while(1) {
        n1 = n1->next;
        if (n1 == n2) {
            return 1;
        }
        if (p1 == n1) {
            return 0;
        }
    }
}

int main() {
    node *a01 = new node;
    node *a02 = new node;
    node *a03 = new node;
    node *a04 = new node;
    node *a05 = new node;
    a01->next = a03;
    a02->next = a03;
    a03->next = a04;
    a04->next = a05;
    a05->next = a03;
    cout<< test_cycle(a01)<< endl;
    cout<< test_cycle(a02)<< endl;
    cout<< test_cycle(a03)<< endl;
    cout<< test_cycle(a04)<< endl;
    cout<< test_cycle(a05)<< endl;
    cout<< is_joined(a01, a02)<< endl;
    return 0;
}








