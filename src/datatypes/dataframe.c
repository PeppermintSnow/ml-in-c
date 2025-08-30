#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
    #include "..\\..\\include\\datatypes\\dataframe.h"
#else
    #include "../../include/datatypes/dataframe.h"
#endif

// Initializes a DataFrame with from an array of doubles with specified length and a column name.
DataFrame *DF_fromArray(double *X, int length, char *col) {
    DataFrame *df = malloc(sizeof(DataFrame));

    if (!df) {
        fprintf(stderr, "Failed to allocate memory for the DataFrame.\n");
        return NULL;
    }

    df->rows = malloc(length * sizeof(double));
    if (!df->rows) {
        fprintf(stderr, "Failed to allocate memory for the DataFrame rows.\n");
        DF_free(df);
        return NULL;
    }

    df->columnNames = malloc(sizeof(char*));
    if (!df->columnNames) {
        fprintf(stderr, "Failed to allocate memory for the DataFrame column names.\n");
        DF_free(df);
        return NULL;
    }

    df->columnNames[0] = malloc(strlen(col) + 1);
    if (!df->columnNames[0]) {
        fprintf(stderr, "Failed to allocate memory for the DataFrame column names.\n");
        DF_free(df);
        return NULL;
    }

    // TODO: Handle edge-cases like empty column

    strcpy(df->columnNames[0], col);
    df->length = length;
    df->nFeatures = 1;
    memcpy(df->rows, X, length * sizeof(double));

    return df;
}

// Add new column to an existing DataFrame
int DF_addColumn(DataFrame *df, double *X, char *newCol) {
    int oldFeatures = df->nFeatures;
    int newFeatures = oldFeatures + 1;

    // Why does memory management have to be this painful
    double *oldRows = malloc(df->length * oldFeatures * sizeof(double));
    if (!oldRows) {
        fprintf(stderr, "Failed to allocate memory for the DataFrame backup rows.\n");
        return -1;
    }
    memcpy(oldRows, df->rows, df->length * oldFeatures * sizeof(double));

    double *newRows = realloc(df->rows, df->length * newFeatures * sizeof(double));
    if (!newRows) {
        fprintf(stderr, "Failed to reallocate memory for the DataFrame rows.\n");
        free(oldRows);
        return -1;
    }

    char **newColumns = realloc(df->columnNames, newFeatures * sizeof(char*));
    if (!newColumns) {
        fprintf(stderr, "Failed to reallocate memory for the DataFrame column names.\n");
        free(oldRows);
        return -1;
    }

    // Update rows
    for (int i = 0; i < df->length; i++) {
          for (int j = 0; j < oldFeatures; j++) {
            // Copy old rows to new
            newRows[i * newFeatures + j] = oldRows[i * oldFeatures + j];
        }
        // Fill gaps with new column
        newRows[i * newFeatures + oldFeatures] = X[i];
    }
    free(oldRows);

    // Update column names
    char *newColumnName = strdup(newCol);
    if (!newColumnName) {
        fprintf(stderr, "Failed to allocate memory for the new column name.\n");
        return -1;
    }

    // TODO: Handle edge-cases like empty column or length mismatch

    // Update DataFrame if all went well :D
    df->rows = newRows;
    df->columnNames = newColumns;
    df->columnNames[oldFeatures] = newColumnName;
    df->nFeatures = newFeatures;

    return 0;
}

// TODO: Add DF_fromCSV()
// TODO: Add DF_addRows()

// Free DataFrame from memory
void DF_free(DataFrame *df) {
    if (!df) return;
    free(df->rows);
    if (df->columnNames) {
        for (int i = 0; i < df->nFeatures; i++) {
            free(df->columnNames[i]);
        }
    }
    free(df->columnNames);
    free(df);
}

