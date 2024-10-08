#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int length(const char s[]) {
    int i = 0;
    while (s[i] != '\0') i++;
    return i;
}

void copy(char t[], const char s[]) {
    int i;
    for (i = 0; s[i] != '\0'; i++) {
        t[i] = s[i];
    }
    t[i] = '\0';
}

int compare(const char s[], const char t[]) {
    int i = 0;
    while (true) {
        if (s[i] < t[i]) return -1;
        if (s[i] > t[i]) return 1;
        if (s[i] == '\0') return 0;
        i++;
    }
}

void append(char t[], const char s[]) {
    int i, n = length(t);
    for (i = 0; s[i] != '\0'; i++) {
        t[n+i] = s[i];
    }
    t[n+i] = '\0';
}

int find(const char t[], const char s[]) {
    int i, n = length(t), m = length(s);
    bool found = false;
    for (i = 0; i <= n - m && !found; i++) {
        found = true;
        for (int j = 0; j < m && found; j++) {
            if (t[i+j] != s[j]) found = false;
        }
    }
    if (!found) i = 0;
    return i - 1;
}

void assert(bool b) {
    static int testNumber = 0;
    testNumber++;
    if (!b) {
        printf("Test %d failed\n", testNumber);
        exit(1);
    }
}

void testLength() {
    assert(length("") == 0);
    assert(length("c") == 1);
    assert(length("ca") == 2);
    assert(length("cat") == 3);
    char s[] = "dog";
    assert(length(s) == 3);
}

void testCopy() {
    char t[10];
    copy(t, "cat");
    assert(t[0] == 'c' && t[1] == 'a' && t[2] == 't' && t[3] == '\0');
    copy(t, "at");
    assert(t[0] == 'a' && t[1] == 't' && t[2] == '\0');
    copy(t, "t");
    assert(t[0] == 't' && t[1] == '\0');
    copy(t, "");
    assert(t[0] == '\0');
}

void testCompare() {
    assert(compare("cat", "dog") < 0);
    assert(compare("dog", "cat") > 0);
    assert(compare("cat", "cat") == 0);
    assert(compare("an", "ant") < 0);
    assert(compare("ant", "an") > 0);
    assert(compare("", "a") < 0);
    assert(compare("a", "") > 0);
    assert(compare("", "") == 0);
}

void testAppend() {
    char t[10] = {'c', 'a', 't', '\0', 'x'};
    append(t, "");
    assert(t[0] == 'c' && t[1] == 'a' && t[2] == 't' && t[3] == '\0' && t[4] == 'x');
    char u[10] = {'c', 'a', '\0', 'x', 'x'};
    append(u, "t");
    assert(u[0] == 'c' && u[1] == 'a' && u[2] == 't' && u[3] == '\0' && u[4] == 'x');
    char v[10] = {'\0', 'x', 'x', 'x', 'x'};
    append(v, "cat");
    assert(v[0] == 'c' && v[1] == 'a' && v[2] == 't' && v[3] == '\0' && v[4] == 'x');
}

void testFind() {
    assert(find("cat", "cat") == 0);
    assert(find("cat", "c") == 0);
    assert(find("cat", "t") == 2);
    assert(find("cat", "x") == -1);
    assert(find("banana", "an") == 1);
}

int main() {
    testLength();
    testCopy();
    testCompare();
    testAppend();
    testFind();
    printf("Tests all pass.");
    return 0;
}
