#include<iostream>
#include<queue>
#include<cstdlib>

using namespace std;

struct bintree_node {
    int content;
    bintree_node *left;
    bintree_node *right;
    bintree_node(){
        content = 0;
    }
    bintree_node(int c) {
        content = c;
    }
};

int max2(int a, int b) {
    return (a>b ? a : b);
}
int max3(int a, int b, int c) {
    return (max2(a,b)>c ? max2(a,b) : c);
}

void find_max_dist(bintree_node *root, int *internal_max_dist, int *height) {
    if(root == NULL){
        cout<< "error : NULL root\n";
        exit(0);
    }
    if(!root->left && !root->right) {
        *internal_max_dist = 0;
        *height = 0;
        return;
    }
    int left_internal_max_dist = 0, right_internal_max_dist = 0;
    int left_height = 0, right_height = 0;
    int count = 0;
    if(root->left) {
        count += 1;
        find_max_dist(root->left, &left_internal_max_dist, &left_height);
    }
    if(root->right) {
        count += 1;
        find_max_dist(root->right, &right_internal_max_dist, &right_height);
    }
    int integrated_dist = count + left_height + right_height;
    *internal_max_dist = max3(left_internal_max_dist, right_internal_max_dist, integrated_dist);
    *height = max2(left_height, right_height) + 1;
}

int main() {
    int internal_max_dist;
    int height;
    bintree_node* tree = new bintree_node[10];
    tree[0].left = &tree[1];
    tree[0].right = &tree[2];
    tree[2].left = NULL;
    tree[2].right = NULL;
    //tree[1].left = NULL;
    //tree[1].right = NULL;
    tree[1].left = &tree[3];
    tree[1].right = &tree[4];
    tree[3].left = &tree[5];
    tree[3].right = NULL;
    tree[4].left = NULL;
    tree[4].right = &tree[6];
    tree[5].left = NULL;
    tree[5].right = NULL;
    tree[6].left = NULL;
    tree[6].right = &tree[7];
    tree[7].left = NULL;
    tree[7].right = NULL;

    find_max_dist(tree, &internal_max_dist, &height);
    cout<< internal_max_dist<< " "<< height<< endl;
    return 0;
}
