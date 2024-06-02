#include "histogram.h"
#include <stdlib.h>
#include <string.h>

// Definition of the structure node
struct node {
    char *word;
    int occurrence;
    struct node *esq;
    struct node *dir;
};

// Definition of the structure tree
typedef struct node *Tree;


// Definition of the structure histogram
struct histogram {
    Tree root;
};

// Initializes the histogram
int init(Histogram *h) {
    *h = malloc(sizeof(struct histogram));
    if (*h == NULL) {
        return 1;
    }
    (*h)->root = NULL;
    return 0;
}

// Inserts a word into the histogram
int insert(Histogram h, char *word) {
    Tree *aux = &h->root;
    while (*aux != NULL) {
        if (strcmp((*aux)->word, word) == 0) {
            (*aux)->occurrence++;
            return 0;
        }
        if (strcmp((*aux)->word, word) < 0) {
            aux = &(*aux)->dir;
        } else {
            aux = &(*aux)->esq;
        }
    }
    *aux = malloc(sizeof(struct node));
    if (*aux == NULL) {
        return 1;
    }
    (*aux)->word = strdup(word);
    (*aux)->occurrence = 1;
    (*aux)->esq = NULL;
    (*aux)->dir = NULL;
    return 0;

}

// Auxiliary function to find the most frequent word
int auxMoreFrequent(Tree t, char *word, int *max) {
    if (t == NULL) {
        return 0;
    }
    int esq = auxMoreFrequent(t->esq, word, max);
    if (t->occurrence > *max) {
        *max = t->occurrence;
        strcpy(word, t->word);
    }
    int dir = auxMoreFrequent(t->dir, word, max);
    return esq + dir + t->occurrence;
}

// Finds the most frequent word in the histogram
int mostFrequent(Histogram h, char *word) {
    int max = 0;
    auxMoreFrequent(h->root, word, &max);
    return max;
}

// Frees the memory allocated for the tree
void freeTree(Tree t) {
    if (t == NULL) {
        return;
    }
    freeTree(t->esq);
    freeTree(t->dir);
    free(t->word);
    free(t);
}

// Frees the memory allocated for the histogram
void freeHistogram(Histogram h) {
    freeTree(h->root);
    free(h);
}