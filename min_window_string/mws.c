#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cdebug.h"

static inline int idx(char x) {
    return (int)(x - 'A');
}

char* minWindow(char* s, char* t) {
    int char_counter[26];
    memset((void *) char_counter, 0, 26 * sizeof(int));
    while (*t) {
        char_counter[idx(*t++)] = 1;
    }
    int i;
    int t_unique = 0;
    int s_counter[26];
    for (i = 0; i < 26; i++) {
        t_unique += char_counter[i];
        s_counter[i] = 0;
    }

    int state = -1; // not satisfied
    int s_unique = 0;

    char *lptr = s, *rptr = s;
    int min_len = 0x7fffffff, min_l = -1, min_r = -1;
    while(1) {
        if(state == -1) {
            if(*(rptr) == '\0') {
                break;
            }

            log_var(lptr-s);
            log_var(rptr-s);
            if(char_counter[idx(*rptr)]) { // a char in T
                if(!s_counter[idx(*rptr)]) { // first time to encounter it
                    s_unique += 1;
                    if(s_unique == t_unique) {
                        state = 0; // OK
                        int cur_min_len = rptr - lptr;
                        if(cur_min_len < min_len) {
                            min_len = cur_min_len;
                            min_l = lptr - s;
                            min_r = rptr - s;
                        }
                    }
                }
                s_counter[idx(*rptr)] += 1;
            }
            rptr++;
        }
        else { // satisfied, delete!
            log_var(lptr-s);
            log_var(rptr-s);
            log("%c", *lptr);
            if(char_counter[idx(*lptr)]) {
                if(s_counter[idx(*lptr)] == 1) { //only *lptr remains in lptr ~ rptr
                    log();
                    state = -1;
                    s_unique -= 1;
                    int cur_min_len = rptr - lptr;
                    if(cur_min_len < min_len) {
                        min_len = cur_min_len;
                        min_l = lptr - s;
                        min_r = rptr - s;
                    }
                }
                s_counter[idx(*lptr)] -= 1;
            }
            lptr++;
        }
    }
    log();
    if(min_len == 0x7fffffff) {
        s[0] = '\0';
        return s + min_l;
    }
    else {
        if(s[min_r] != '\0') {
            s[min_r] = '\0';
        }
        log();
        return s + min_l;
    }
}

int main() {
    char* s = "ADOBECODEBANC";
    char* t = "ABC";
    printf("-- %s -- \n", minWindow(s, t));
    return 0;
}

