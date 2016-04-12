#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cassert>

using namespace std;

class heap {
    int *a;
    int k;
public:
    heap(int kk) {
        assert(kk>0);
        k = kk;
        a = new int[k];
    }

    int *get_heap(){
        return a;
    }

    void eat(int x) {
        if(x >= *a) {
            return;
        }
        *a = x;
        make_small_max_heap(a);
    }

    void init(int input[]){ //size k is expected
        int i;
        for(i = 0; i < k; i++) {
            a[i] = input[i];
        }
        heapify();
    }

    void heapify(){
        int iterate_time = k/2;
        int i;
        for(i = 0; i < iterate_time; i++) {
            make_small_max_heap(&a[iterate_time - i - 1]);
        }
    }

    inline int *glch(int *x) {
        assert(x - a < k);
        int dis = x - a;
        return a + 2*dis + 1;
    }
    inline int *grch(int *x) {
        assert(x - a < k);
        int dis = x - a;
        return a + 2*dis + 2;
    }

    void make_small_max_heap(int *root){
        assert(root - a < k);
        int *lch = glch(root);
        int *rch = grch(root);
        int *largest;
        if(lch > a + k) {
            return;
        }
        largest = lch;
        if(rch <= a + k){
            largest = *lch > *rch ? lch : rch;
        }
        if(*largest > *root){
            int tmp = *largest;
            *largest = *root;
            *root = tmp;
            make_small_max_heap(largest);
        }
    }
};

void find_least_k(int a[], int k, int amt) {
    int i;
    for(i = 0; i < amt; i++) {
        cout<< a[i]<< " ";
    }
    cout<< endl;

    heap* h = new heap(k);
    h->init(a);
    for(i = k; i < amt; i++){
        h->eat(a[i]);
    }

    a = h->get_heap();
    for(i = 0; i < k; i++) {
        cout<< a[i]<< " ";
    }
    cout<< endl;
}

int main() {
    srand(time(NULL));
    int a[30];
    int i;
    for(i = 0; i < 30; i++) {
        //a[i] = i;
        a[i] = rand()%100;
    }
    find_least_k(a, 10, 30);
}
