#include <iostream>
#include <cstdlib>

using namespace std;

void find_max_subarray(int a[], int amt){
    int i;
    int cur_max_l = 0;
    int cur_max_r = 0;
    int max_sum = a[0];
    int r_most_l = 0;
    int r_sum = a[0];
    for(i = 1; i < amt; i++) {
        if(r_sum < 0) {
            r_sum = a[i];
            r_most_l = i;
        }
        else {
            r_sum += a[i];
        }
        if(r_sum > max_sum) {
            cur_max_l = r_most_l;
            cur_max_r = i;
            max_sum = r_sum;
        }
    }
    for(i = cur_max_l; i <= cur_max_r; i++) {
        cout<< a[i] << " ";
    }
    cout<< "\nsum: "<< max_sum<< "\n";
}

int main(){
    int a[] = {1, -2, 3, 10, -4, 7, 2, -5};
    find_max_subarray(a, 8);
    return 0;
}
