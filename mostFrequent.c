#include <stdio.h>
#include "histogram.c"
#include "utilities.c"

int main(int argc, char *argv[]) {

    //Checking if the user has entered the correct number of arguments
    if (argc < 2) {
        printf("Usage: %s <number of files> <filename 1> <filename 2> ... <filename n>\n", argv[0]);
        return 1;
    }

    //Opening files
    int fileNumber = atoi(argv[1]);
    FILE *files[fileNumber]; 

    for (int i = 0; i < fileNumber; i++) {
        files[i] = fopen(argv[i+2], "r");
        if (files[i] == NULL) {
            printf("Error opening file %s\n", argv[i+2]);
            return 1;
        }
    }
    
    //Initializing histogram
    Histogram individual_histograms[fileNumber];
    Histogram global_histogram;

    for (int i = 0; i < fileNumber; i++) {
        if (init(&individual_histograms[i]) != 0) {
            printf("Error initializing histograms\n");
        return 1;
        }
    }
    if (init(&global_histogram) != 0) {
        printf("Error initializing histograms\n");
        return 1;
    }

    //Reading words from files and inserting them into the histogram
    char word[100];

    for (int i = 0; i < fileNumber; i++) {
        while (fscanf(files[i], "%s", word) == 1) {
            adjust(word);
            insert(individual_histograms[i], word);
            insert(global_histogram, word);
        }
    }

    //Finding the most frequent word
    int mostFrequentWords[fileNumber], mostFrequentGlobal;

    for (int i = 0; i < fileNumber; i++) {
        mostFrequentWords[i] = mostFrequent(individual_histograms[i], word);
        printf("Most frequent word in file '%s' is '%s' (%d times)\n", argv[i+2], word, mostFrequentWords[i]);
    }

    mostFrequentGlobal = mostFrequent(global_histogram, word);
    printf("Most frequent word in all files is '%s' (%d times)\n", word, mostFrequentGlobal);

    //Freeing memory
    for (int i = 0; i < fileNumber; i++) {
        freeHistogram(individual_histograms[i]);
    }

    freeHistogram(global_histogram);
    
    for (int i = 0; i < fileNumber; i++) {
        fclose(files[i]);
    }
    
    return 0;   
}