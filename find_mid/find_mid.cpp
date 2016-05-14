#include <iostream>
#include <vector>
#include "debug.h"

using namespace std;

class MedianFinder {
    private:
        vector<int> minheap;

        vector<int> maxheap;

        void fix_heap(vector<int>& heap, bool (*cmp) (int, int)) {
            if(heap.size() <= 1) {
                return;
            }
            unsigned int idx = heap.size() - 1;
            unsigned int par_idx = idx/2;
            while(par_idx > 0) {
                if(cmp(heap[idx], heap[par_idx])) { // broken
                    int tmp = heap[idx];
                    heap[idx] = heap[par_idx];
                    heap[par_idx] = tmp;
                }
                idx = par_idx;
                par_idx = idx/2;
            }
        }

        void fix_heap_down(vector<int>& heap, bool (*cmp) (int, int)) {
            if(heap.size() <= 1) {
                return;
            }
            unsigned int par_idx = 1;
            while(par_idx != heap.size() - 1) {
                unsigned int m_idx = par_idx;
                unsigned int l_idx = par_idx*2;
                unsigned int r_idx = par_idx*2 + 1;
                if(l_idx < heap.size() && !cmp(heap[m_idx], heap[l_idx])) {
                    m_idx = l_idx;
                }
                if(r_idx < heap.size() && !cmp(heap[m_idx], heap[r_idx])) {
                    m_idx = r_idx;
                }
                if(par_idx == m_idx) {
                    break;
                }
                else {
                    int tmp = heap[par_idx];
                    heap[par_idx] = heap[m_idx];
                    heap[m_idx] = tmp;

                    par_idx = m_idx;
                }
            }
        }

        static bool bigger(int x, int y) {
            return x > y;
        }
        static bool less(int x, int y) {
            return x < y;
        }

    public:

        MedianFinder() {
            minheap.push_back(0);
            maxheap.push_back(0);
            // start from 1, for the convenience of idx calculation
        }

        // Adds a number into the data structure.
        void addNum(int num) {
            if (num > maxheap[1]) {
                minheap.push_back(num);
                fix_heap(minheap, less);
            }
            else {
                maxheap.push_back(num);
                fix_heap(maxheap, bigger);
            }
            if (maxheap.size() - minheap.size() == 2) {
                minheap.push_back(maxheap[1]);
                fix_heap(minheap, less);
                maxheap[1] = maxheap.back();
                maxheap.pop_back();
                fix_heap_down(maxheap, bigger);
            }
            else if (minheap.size() - maxheap.size() == 2) {
                maxheap.push_back(minheap[1]);
                fix_heap(maxheap, bigger);
                minheap[1] = minheap.back();
                minheap.pop_back();
                fix_heap_down(minheap, less);
            }
        }

        // Returns the median of current data stream
        double findMedian() {
            if (minheap.size() > maxheap.size()) {
                log();
                return (double) minheap[1];
            }
            else if (minheap.size() < maxheap.size()) {
                log();
                return (double) maxheap[1];
            }
            else {
                log();
                return (((double) maxheap[1]) + ((double) minheap[1]))/2;
            }
        }
};

// Your MedianFinder object will be instantiated and called as such:
// MedianFinder mf;
// mf.addNum(1);
// mf.findMedian();
//
int main () {
    MedianFinder mf;
    cout << mf.findMedian() <<endl;
    return 0;
}
