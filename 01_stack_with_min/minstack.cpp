#include <iostream>
#include <cstdlib>

using namespace std;

struct list_node {
    int content;
    list_node *next;
    list_node(int val){
        content = val;
    }
};

class stack{
protected:
    list_node *bot;
    list_node *top;
public:
    void push(int v);
    int pop();
    int get_top() {
        return top->content;
    }
    stack(){
        bot = new list_node(0);
        top = bot;
    }
};

void stack::push(int v){
    list_node *tmp = new list_node(v);
    tmp->next = top;
    top = tmp;
}

int stack::pop(){
    if(top == bot) {
        cerr<<"pop in empty stack\n";
        exit(0);
    }
    int tmp = top->content;
    list_node *tnode = top;
    top = top->next;
    delete tnode;
    return tmp;
}

class min_stack {
protected:
    stack* real_stack;
    stack* m_stack;
    int min;
public:
    void push(int v);
    int pop();
    int get_min();
    min_stack() {
        real_stack = new stack();
        m_stack = new stack();
        min = 0x7fffffff;
    }
};

void min_stack::push(int v) {
    real_stack->push(v);
    if(v < min) {
        min = v;
    }
    m_stack->push(min);
}

int min_stack::pop() {
    m_stack->pop();
    return real_stack->pop();
}

int min_stack::get_min(){
    return m_stack->get_top();
}

int main(){
    min_stack *ms = new min_stack;
    int i;
    for(i = 0; i < 15; i++) {
        ms->push(i);
    }
    for(i = 0; i < 15; i++) {
        cout<<"min: "<<ms->get_min();
        cout<<"; pop: "<<ms->pop()<<" ";
        cout<<endl;
    }
    return 0;
}





