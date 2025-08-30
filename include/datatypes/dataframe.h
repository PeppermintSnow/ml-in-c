#ifndef DATAFRAME_H
#define DATAFRAME_H

// An optimized 1D array that represents a matrix of length x nFeatures
typedef struct {
    double *rows;       // Flattened array for performance
    int length;         // Length/number of samples
    int nFeatures;      // Number of features in a row
    char **columnNames; // List of column names
} DataFrame;

DataFrame *DF_fromArray(double *X, int length, char *col);
int DF_addColumn(DataFrame *df, double *X, char *newCol);
void DF_free(DataFrame *df);
#endif
