#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

int attachable[102][102][102];
int dyeable[102][102][102];

bool is_attachable(int z, int y, int x) {
    if(attachable[z][y][x + 1]) return true;
    if(attachable[z][y][x - 1]) return true;
    if(attachable[z][y + 1][x]) return true;
    if(attachable[z][y - 1][x]) return true;
    if(attachable[z + 1][y][x]) return true;
    if(attachable[z - 1][y][x]) return true;
    return false;
}

void freex(vector<int *> *input) {
    unsigned int i;
    unsigned int in_size = input->size();
    for (i = 0; i < in_size; i++) {
        delete [] (*input)[i];
    }
}

vector<int *> *expand(vector<int *> *input) {
    vector<int *> *shell = new vector<int *>;
    unsigned int i;
    unsigned int in_size = input->size();
    for (i = 0; i < in_size; i++) {
        int z, y, x;
        z = (*input)[i][0];
        y = (*input)[i][1];
        x = (*input)[i][2];
        if(dyeable[z][y][x + 1]) {
            if (x + 1 == 100) {
                (*shell)[0] = nullptr;
                freex(input);
                return shell;
            }
            int *v = new int[3];
            v[0] = z;
            v[1] = y;
            v[2] = x + 1;
            shell->push_back(v);
        }
        if(dyeable[z][y][x - 1]) {
            if (x - 1 == 1) {
                (*shell)[0] = nullptr;
                freex(input);
                return shell;
            }
            int *v = new int[3];
            v[0] = z;
            v[1] = y;
            v[2] = x - 1;
            shell->push_back(v);
        }
        if(dyeable[z][y + 1][x]) {
            if (y + 1 == 100) {
                (*shell)[0] = nullptr;
                freex(input);
                return shell;
            }
            int *v = new int[3];
            v[0] = z;
            v[1] = y + 1;
            v[2] = x;
            shell->push_back(v);
        }
        if(dyeable[z][y - 1][x]) {
            if (y - 1 == 1) {
                (*shell)[0] = nullptr;
                freex(input);
                return shell;
            }
            int *v = new int[3];
            v[0] = z;
            v[1] = y - 1;
            v[2] = x;
            shell->push_back(v);
        }
        if(dyeable[z + 1][y][x]) {
            if (z + 1 == 100) {
                (*shell)[0] = nullptr;
                freex(input);
                return shell;
            }
            int *v = new int[3];
            v[0] = z + 1;
            v[1] = y;
            v[2] = x;
            shell->push_back(v);
        }
        if(dyeable[z - 1][y][x]) {
            int *v = new int[3];
            v[0] = z - 1;
            v[1] = y;
            v[2] = x;
            shell->push_back(v);
        }
    }
    freex(input);
    return shell;
}

bool is_accessible(int z, int y, int x) {
    vector<int *> *shell = new vector<int *>;
    int *v = new int[3];
    v[0] = z;
    v[1] = y;
    v[2] = x;
    shell->push_back(v);
    while(true) {
        shell = expand(shell);
        if((*shell)[0] == nullptr) {
            freex(shell);
            int z,y,x;
            for (z = 1; z < 102; z++) {
                for (y = 0; y < 102; y++) {
                    for (x = 0; x < 102; x++) {
                        if(attachable[z][y][x] == 0)
                            dyeable[z][y][x] = 1;
                    }
                }
            }
            return true;
        }
        if(shell->size() == 0) {
            int z,y,x;
            for (z = 1; z < 102; z++) {
                for (y = 0; y < 102; y++) {
                    for (x = 0; x < 102; x++) {
                        if(attachable[z][y][x] == 0)
                            dyeable[z][y][x] = 1;
                    }
                }
            }
            return false;
        }
    }
}

int main() {
    int n_samples;
    cin >> n_samples;
    while(n_samples) {
        int z,y,x;
        for (z = 1; z < 102; z++) {
            for (y = 0; y < 102; y++) {
                for (x = 0; x < 102; x++) {
                    attachable[z][y][x] = 0;
                    dyeable[z][y][x] = 1;
                }
            }
        }

        for (y = 0; y < 102; y++) {
            for (x = 0; x < 102; x++) {
                attachable[0][y][x] = 1;
            }
        }
        
        int n_tests;
        cin >> n_tests;
        while(n_tests) {

            n_tests -= 1;
        }
        n_samples -= 1;
    }

    return 0;
}
