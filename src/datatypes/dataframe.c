#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
    #include "..\\..\\include\\datatypes\\dataframe.h"
#else
    #include "../../include/datatypes/dataframe.h"
#endif

/**
 * Creates a DataFrame with one feature/column from an array.
 * Allocates memory and copies input into the struct.
 */
DataFrame *DF_fromArray(double *data, int numRows, char *name) {
    DataFrame *df = malloc(sizeof(DataFrame));

    if (!df) {
        fprintf(stderr, "Failed to allocate memory for the DataFrame.\n");
        return NULL;
    }

    df->data = malloc(numRows * sizeof(double));
    if (!df->data) {
        fprintf(stderr, "Failed to allocate memory for the DataFrame rows.\n");
        DF_free(df);
        return NULL;
    }

    df->featureNames = malloc(sizeof(char*));
    if (!df->featureNames) {
        fprintf(stderr, "Failed to allocate memory for the DataFrame column names.\n");
        DF_free(df);
        return NULL;
    }

    df->featureNames[0] = malloc(strlen(name) + 1);
    if (!df->featureNames[0]) {
        fprintf(stderr, "Failed to allocate memory for the DataFrame column names.\n");
        DF_free(df);
        return NULL;
    }

    // TODO: Handle edge-cases like empty column

    strcpy(df->featureNames[0], name);
    df->numRows = numRows;
    df->numCols = 1;
    memcpy(df->data, data, numRows * sizeof(double));

    return df;
}

/**
 * Adds a new column/feature to an existing DataFrame.
 * Expands allocated memory and appends input data to the end of each row.
 */
int DF_addColumn(DataFrame *df, double *data, char *name) {
    int oldNumCols = df->numCols;
    int newNumCols = oldNumCols + 1;

    // Why does memory management have to be this painful
    double *oldData = malloc(df->numRows * oldNumCols * sizeof(double));
    if (!oldData) {
        fprintf(stderr, "Failed to allocate memory for the DataFrame backup rows.\n");
        return -1;
    }
    memcpy(oldData, df->data, df->numRows * oldNumCols * sizeof(double));

    double *newData = realloc(df->data, df->numRows * newNumCols * sizeof(double));
    if (!newData) {
        fprintf(stderr, "Failed to reallocate memory for the DataFrame rows.\n");
        free(oldData);
        return -1;
    }

    char **newFeatureNames = realloc(df->featureNames, newNumCols * sizeof(char*));
    if (!newFeatureNames) {
        fprintf(stderr, "Failed to reallocate memory for the DataFrame feature names.\n");
        free(oldData);
        return -1;
    }

    // Update rows
    for (int i = 0; i < df->numRows; i++) {
          for (int j = 0; j < oldNumCols; j++) {
            // Copy old rows to new
            newData[i * newNumCols + j] = oldData[i * oldNumCols + j];
        }
        // Fill gaps with new column
        newData[i * newNumCols + oldNumCols] = data[i];
    }
    free(oldData);

    // Update column names
    char *newName = strdup(name);
    if (!newName) {
        fprintf(stderr, "Failed to allocate memory for the new column name.\n");
        return -1;
    }

    // TODO: Handle edge-cases like empty column or length mismatch

    // Update DataFrame if all went well :D
    df->data = newData;
    df->featureNames = newFeatureNames;
    df->featureNames[oldNumCols] = newName;
    df->numCols = newNumCols;

    return 0;
}

// TODO: Add DF_fromCSV()
// TODO: Add DF_addRows()

/**
 * Frees all memory allocated by the DataFrame.
 */
void DF_free(DataFrame *df) {
    if (!df) return;
    free(df->data);
    if (df->featureNames) {
        for (int i = 0; i < df->numCols; i++) {
            free(df->featureNames[i]);
        }
    }
    free(df->featureNames);
    free(df);
}

