#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define EQUAL 0
#define OK 0
#define FALSE -1
#define ERROR -1
#define OVERFLOW -2

typedef int Status;

typedef struct{
    char *ch;
    int length;
}HString;

HString T, S, Sub, S1, S2;

Status Initialize(HString *T) {
    T->ch = NULL;
    T->length = 0;
    
    return OK;
}

Status Assign(HString *T, char *chars) {
    int a = (int)strlen(chars);
    T->length = a;
    T->ch = (char*)malloc((T->length) * sizeof(HString));
    
    int i;
    for (i = 0; i < a; i++) {
        T->ch[i] = chars[i];
    }
    
    return OK;
}

Status Clear(HString *T) {
    if (T->ch) {
        T->ch = NULL;
    }
    T->length = 0;
    return OK;
}

Status Destroy(HString *T) {
    Clear(T);
    
    return OK;
}

int Length(HString *T) {
    int i = 0;
    
    while (T->ch[i] != '\0') {
        i++;
    }
    
    return i;
}

Status Copy(HString *T, HString *S) {
    int a = Length(S);
    
    Clear(T);
    T->length = a;
    T->ch = (char*)malloc((T->length) * sizeof(HString));
    
    for (size_t i = 0; i < a; i++) {
        T->ch[i] = S->ch[i];
    }
    
    return OK;
}

Status Copy_part(HString *S, HString *Sub, int pos, int len) {
    Clear(Sub);
    Sub->length = len;
    Sub->ch = (char*)malloc((Sub->length) * sizeof(HString));
    
    int i, j = pos-1;
    for (i = 0; i < len; i++) {
        Sub->ch[i] = S->ch[j];
        j++;
    }
    
    return OK;
}

int Compare(HString *T, HString *S) {
    int a = Length(T);
    int b = Length(S);
    int c = a > b ? a : b;
    
    for (size_t i = 0; i < c; i++) {
        if (T->ch[i] > S->ch[i]) {
            return TRUE;
        }
        else if (T->ch[i] < S->ch[i]) {
            return FALSE;
        }
        else {
            continue;
        }
    }
    return EQUAL;
}

Status Insert(HString *S, HString *T, int pos) {
    int a = Length(S);
    int b = Length(T);
    S->length = a + b;
    
    int i, j = 0;
    S->ch[a+b] = '\0';
    for (i = a + b-1; i >= pos + b-1; i--) {
        S->ch[i] = S->ch[i-b];
    }
    
    for (i = pos-1; i < pos + b-1; i++) {
        S->ch[i] = T->ch[j];
        j++;
    }
    return TRUE;
}

Status Delete(HString *S, int pos, int len) {
    int a = Length(S);
    S->length = a - len;
    
    int i;
    for (i = pos-1; i < a - len; i++) {
        S->ch[i] = S->ch[i + len];
    }
    for (i = a - len; i < a; i++) {
        S->ch[i] = '\0';
    }
    return OK;
}

Status SubString(HString *T, HString *Sub, int pos, int len) {
    Clear(Sub);
    Sub->length = len;
    Sub->ch = (char*)malloc((Sub->length) * sizeof(HString));
    
    int i, j = 0;
    for (i = pos-1; i < pos + len - 1; i++) {
        Sub->ch[j] = T->ch[i];
        j++;
    }
    return OK;
}

Status Concat(HString *S1, HString *S2, HString *Sub) {
    int a = Length(S1);
    int b = Length(S2);
    
    Clear(Sub);
    Sub->length = a + b;
    Sub->ch = (char*)malloc((Sub->length) * sizeof(HString));
    
    int i, j = 0;
    for (i = 0; i < a; i++) {
        Sub->ch[i] = S1->ch[i];
    }
    for (i = a; i < a + b; i++) {
        Sub->ch[i] = S2->ch[j];
        j++;
    }
    return OK;
}

Status Traversal(HString *T) {
    int letters[128];
    memset(letters, 0, sizeof(letters));
    int i = 0;
    
    while (T->ch[i] != '\0') {
        letters[T->ch[i] - 'A' + 65]++;
        i++;
    }
    
    for (i = 0; i < 128; i++) {
        printf("%d(%c) : %d\n", i, i, letters[i]);
    }
    
    return OK;
}

int Index(HString *S, HString *T, HString *Sub) {
    int a = Length(S);
    int b = Length(T);
    
    if (a < b) {
        return ERROR;
    }
    else {
        int i;
        for (i = 1; i < a; i++) {
            Clear(Sub);
            Sub->length = b;
            Sub->ch = (char*)malloc((Sub->length) * sizeof(HString));
            Copy_part(S, Sub, i, b);
            if (Compare(Sub, T) == 0) {
                return i;
            }
            else {
                continue;
            }
        }
    }
    return FALSE;
}

void Get_next(HString *T, int *next) {
    int j = 0, k = -1;
    next[0] = -1;
    
    while(j < Length(T))
    {
        if(k == -1 || T->ch[j] == T->ch[k])
        {
            j++;
            k++;
            next[j] = k;
        }
        else
        {
            k = next[k];
        }
    }
}

int KMP(HString *S, HString *T) {
    int i = 0, j = 0;
    int a = Length(S);
    int b = Length(T);
    
    int next[b];
    Get_next(T, next);
    
    while (i < a && j < b) {
        if (j == -1 || S->ch[i] == T->ch[j]) {
            i++;
            j++;
        }
        else {
            j = next[j];
        }
    }
    if (j == b) {
        return i - b + 1;
    }
    else {
        return ERROR;
    }
}

Status Replace(HString *S, HString *T, HString *V) {
    while (KMP(S, T) != -1) {
        int a = Length(T);
        int pos = KMP(S, T);
        
        Delete(S, pos, a);
        Insert(S, V, pos);
    }
    return OK;
}

int main(int argc, char const *argv[]) {
    
    return 0;
}
