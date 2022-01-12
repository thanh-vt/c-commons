#include <stdlib.h>
#include <stdio.h>
#include <common-var.h>
#include <string.h>
#include <common-array.h>

arr_string *scanStringArr(int length) {
    arr_string *arrString = calloc(1, sizeof(arr_string));
    arrString->arr = calloc(length, sizeof(char *));
    arrString->size = length;
    printf(">>> Start input array of strings:\n");
    for (int i = 0; i < length; ++i) {
        (arrString->arr)[i] = calloc(sizeof(char), BUFFER_SIZE_SM);
        printf("- Enter element #%d:\n", i);
        scanf("%s", (arrString->arr)[i]);
    }
    printf("<<< End input array of strings.\n");
    return arrString;
}

arr_string *readStringArr(char *fileName) {
    arr_string *pArrString = calloc(1, sizeof(arr_string));
    FILE *fp;
    char *buff = calloc(BUFFER_SIZE, sizeof(char));
    fp = fopen(fileName, "r");
    fgets(buff, BUFFER_SIZE, (FILE *) fp);
//    printf("String: %s\n", buff);
    int capacity = ARRAY_CAPACITY;
    int index = 0;
    char **arr = calloc(capacity, sizeof(char *));
    char *token = strtok(buff, DELIM);
    while (token != NULL) {
        arr[index] = calloc(1, sizeof(char ) * strlen(token) + 1);
        strcpy(arr[index], token);
//        printf("%d - %s\n", index, arr[index]);
        index++;
        if (index >= capacity) {
            capacity += ARRAY_CAPACITY;
            char **arrTmp = realloc(arr, capacity);
            if (arrTmp != NULL) {
                arr = arrTmp;
            } else {
                printf("Cannot allocate memory!");
            }
        }
        token = strtok(NULL, DELIM);
    }
    pArrString->arr = arr;
    pArrString->size = index;
    fclose(fp);
    free(buff);
    return pArrString;
}

void printStringArr(arr_string *arrString) {
    printf("[");
    for (int i = 0; i < arrString->size; ++i) {
        if (i == arrString->size - 1) {
            printf("%s", arrString->arr[i]);
        } else {
            printf("%s, ", arrString->arr[i]);
        }
    }
    printf("]");
}

void freeStringArr(arr_string *arrString) {
    for (int i = 0; i < arrString->size; ++i) {
        free(arrString->arr[i]);
    }
    free(arrString->arr);
}