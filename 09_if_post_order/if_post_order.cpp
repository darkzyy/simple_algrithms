#include<iostream>

using namespace std;

int is_post_order(int *a, int start, int end) {
    if(end == start) {
        return 1;
    }
    int root = a[end];
    int i = 0;
    for (i = end - 1; i >= start; i--) {
        if(a[i] <= root) { // a[i] should be root of left child
            int j;
            for(j = i; j >= start; j--) {
                if(a[j] >= root) {
                    return 0;
                }
            }
            if(i < end - 1) { // right child exist
                return is_post_order(a, start, i) && is_post_order(a, i + 1, end - 1);
            }
            else {
                return is_post_order(a, start, i);
            }
        }
    }
    return is_post_order(a, start, end - 1);
}

int main(){
    //int a[] = {5, 7, 6, 9, 11, 10, 8};
    //int a[] = {7, 4, 6, 5};
    int a[] = {2, 1, 0};
    cout<< is_post_order(a, 0, sizeof(a)/sizeof(int))<< endl;
    return 0;
}
