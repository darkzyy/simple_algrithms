#include <iostream>
#include <cstdlib>

using namespace std;

struct BinaryTreeNode { // a node in the binary tree
    int m_nValue; // value of node
    BinaryTreeNode *m_pLeft; // left child of node
    BinaryTreeNode *m_pRight; // right child of node
    BinaryTreeNode(int v){
        m_nValue = v;
    }
};

#define MAX_HEIGHT 100
int stack[MAX_HEIGHT];
int cur = 0;

void post_order_tranverse(BinaryTreeNode* node, int expected_value) {
    stack[cur++] = node->m_nValue;
    if(node->m_nValue == expected_value) {
        int i;
        for(i = 0; i < cur; i++) {
            if(i==0) {
                cout<< stack[i]<< " ";
            }
            else {
                cout<< stack[i]-stack[i-1]<< " ";
            }
        }
        cout<<endl;
    }

    if(node->m_pLeft != NULL) {
        node->m_pLeft->m_nValue += node->m_nValue;
        post_order_tranverse(node->m_pLeft, expected_value);
    }
    if(node->m_pRight != NULL) {
        node->m_pRight->m_nValue += node->m_nValue;
        post_order_tranverse(node->m_pRight, expected_value);
    }
    cur--;
}

int main() {
    BinaryTreeNode *root = new BinaryTreeNode(10);
    BinaryTreeNode *left = new BinaryTreeNode(5);
    BinaryTreeNode *right = new BinaryTreeNode(12);
    root->m_pLeft = left;
    root->m_pRight = right;
    left->m_pLeft = new BinaryTreeNode(4);
    left->m_pRight = new BinaryTreeNode(7);
    cout<< "1"<< endl;
    post_order_tranverse(root, 22);
    return 0;
}
