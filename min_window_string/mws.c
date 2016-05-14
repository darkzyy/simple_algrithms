#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cdebug.h"

static inline int idx(char x) {
    return (int)(x - '\0');
}

char* minWindow(char* s, char* t) {
    int char_counter[128];
    memset((void *) char_counter, 0, 128 * sizeof(int));
    while (*t) {
        char_counter[idx(*t++)] += 1;
    }
    int i;
    int t_unique = 0;
    int s_counter[128];
    for (i = 0; i < 128; i++) {
        t_unique += char_counter[i] > 0;
        s_counter[i] = 0;
    }

    int state = -1; // not satisfied
    int s_sat = 0;

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
                if(s_counter[idx(*rptr)] == char_counter[idx(*rptr)] - 1) {
                    s_sat += 1;
                    if(s_sat == t_unique) {
                        state = 0; // OK
                        int cur_min_len = rptr - lptr;
                        if(cur_min_len < min_len) {
                            min_len = cur_min_len;
                            min_l = lptr - s;
                            min_r = rptr - s + 1;
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
                log_var(s_counter[idx(*lptr)]);
                log_var(char_counter[idx(*lptr)]);
                if(s_counter[idx(*lptr)] == char_counter[idx(*lptr)]) {
                    //only *lptr remains in lptr ~ rptr
                    log();
                    s_sat -= 1;
                    state = -1;
                    int cur_min_len = (rptr -1) - lptr;
                    log("removed %c", *lptr);
                    if(cur_min_len < min_len) {
                        log("replaced");
                        min_len = cur_min_len;
                        min_l = lptr - s;
                        min_r = rptr - s;
                    }
                    else {
                        log_var(lptr-s);
                        log_var(rptr-s);
                        log("%c", *lptr);
                    }
                }
                s_counter[idx(*lptr)] -= 1;
            }
            lptr++;
        }
    }
    log();
    if(min_len == 0x7fffffff) {
        log();
        char *ret = malloc(sizeof(char)*1);
        ret[0] = '\0';
        return ret;
    }
    else {
        log_var(min_l);
        log_var(min_r);
        char *ret = malloc(sizeof(char)*(min_r - min_l + 1));
        strncpy(ret, s + min_l, (min_r - min_l));
        ret[min_r - min_l] = '\0';
        log();
        return ret;
    }
}

int main() {
    //char* s = "AAB";
    //char* s = "CCcAABB";
    //char* s = "CAAAAAAAABCAAAB";
    //char* s = "ADOBECODEBNC";
    //char* s = "fasdfasdfASGRBANC";
    //char* t = "CBAA";
    char *s = "adobecodebanc";
    char *t = "abcda";
    printf("-- %s -- \n", minWindow(s, t));
    return 0;
}

