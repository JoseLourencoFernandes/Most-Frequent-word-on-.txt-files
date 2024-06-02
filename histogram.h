#ifndef HISTOGRAM_H
#define HISTOGRAM_H

typedef struct histogram *Histogram;

int init(Histogram *h);

int insert (Histogram h, char *palavra);

int mostFrequent(Histogram h, char *palavra);

void freeHistogram(Histogram h);

#endif