#include <iostream>
#include <cstdlib>
using namespace std;

void bubble_sort(int *a, int len){
    int x, y;
    for(x = 1; x < len; x++) {
        for(y = x-1; y >= 0; y--) {
            if(a[y+1] < a[y]) {
                int tmp = a[y+1];
                a[y+1] = a[y];
                a[y] = tmp;
            }
        }
    }
}

#define ARRAY_LEN 10

int attr[ARRAY_LEN];

int find_sat(int *a, int cur, int rest) { // assume that a is sorted
    int x = a[cur];
    int y;
    if(rest == 0) {
        int i;
        for (i = 1; i < cur; i++) {
            attr[i] = 0;
        }
        int count = 0;
        for (i = 1; i < ARRAY_LEN; i++) {
            count = attr[i] == 0;
        }
        attr[0] = count;
        return 1;
    }
    if(cur == 0) {
        if(x <= 0 && rest != 0) {
            return 0;
        }
        if(x == 0 && rest == 0) {
        }
        if(rest % x == 0){
            return 1;
        }
        else {
            return 0;
        }
    }

    int count_right = 0;
    int i;
    for (i = cur + 1; i < ARRAY_LEN; i++){
        count_right += a[i] == x;
    }
    for (y = 0; y <= rest/x && (y <= cur + count_right || (y== cur + 1 + count_right && x == y ));
                y++){
        attr[cur] = y;
        int res = find_sat(a, cur-1, rest - y*x);
        if(res){
            return 1;
        }
    }
    return 0;
}

int main() {
    srand(time(NULL));
    int a[ARRAY_LEN];
    int i;
    for (i = 0; i < ARRAY_LEN; i++) {
        //a[i] = rand() % 200;
        a[i] = i;
        cout<< a[i] <<" ";
    }
    cout<< endl;
    bubble_sort(a, ARRAY_LEN);

    find_sat(a, 9, 10);


    for (i = 0; i < ARRAY_LEN; i++) {
        cout<< attr[i] <<" ";
    }
    cout<< endl;
    return 0;
}
