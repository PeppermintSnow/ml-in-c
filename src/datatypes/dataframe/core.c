#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
    #include "..\\..\\..\\include\\datatypes\\dataframe\\core.h"
#else
    #include "../../../include/datatypes/dataframe/core.h"
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
    for (int rowIdx = 0; rowIdx < df->numRows; rowIdx++) {
          for (int colIdx = 0; colIdx < oldNumCols; colIdx++) {
            // Copy old rows to new
            newData[rowIdx * newNumCols + colIdx] = oldData[rowIdx * oldNumCols + colIdx];
        }
        // Fill gaps with new column
        newData[rowIdx * newNumCols + oldNumCols] = data[rowIdx];
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

/*
 * Deletes the specified column from a DataFrame.
 */
int DF_deleteColumn(DataFrame *df, char *name) {
    // offset is -1 if no matches
    // column index = offset for strided access
    int offset = -1;
    for (int i = 0; i < df->numCols; i++) {
        if (strcmp(name, df->featureNames[i]) == 0) {
            offset = i;
        }
    }

    // Delete column if match was found
    if (offset >= 0) {
        // Allocate memory for df->numCols - 1 column
        double *newData = malloc(df->numRows * (df->numCols - 1) * sizeof(double));
        if (!newData) {
            fprintf(stderr, "Failed to allocate memory for the new DataFrame rows.\n");
            return -1;
        }

        // Copy data excluding the data of target column
        int dataIdx = 0;
        for (int rowIdx = 0; rowIdx < df->numRows; rowIdx++) {
            for (int colIdx = 0; colIdx < df->numCols; colIdx++) {
                int index = rowIdx * df->numCols + colIdx;
                int skipIndex = rowIdx * df->numCols + offset;
                if (index != skipIndex) {
                    newData[dataIdx] = df->data[index];
                    dataIdx++;
                }
            }
            printf("\n");
        }

        // Allocate memory for df->numCols - 1 featureNames
        char **newFeatureNames = realloc(df->featureNames, (df->numCols - 1) * sizeof(char*));
        if (!newFeatureNames) {
            fprintf(stderr, "Failed to reallocate memory for the DataFrame feature names.\n");
            free(newData);
            return -1;
        }

        // Delete column name from featureNames by shifting to left from offset to end - 1
        for (int i = offset; i < df->numCols - 1; i++) {
            newFeatureNames[i] = df->featureNames[i + 1];
        }

        df->featureNames = newFeatureNames;
        df->data = newData;
        df->numCols = df->numCols - 1;

        return 0;
    }

    return 1;
}

/*
 * Adds a row/entry to a DataFrame.
 */
int DF_addRow(DataFrame *df, double *data) {
    // TODO: Finish implementation
}

/*
 * Deletes a row/entry from a DataFrame
 */
int DF_deleteRow(DataFrame *df, double index) {
    // TODO: Finish implementation
}

/*
 * Displays the DataFrame in a table
 */
void DF_display(DataFrame *df) {
    // Compute column widths
    int colWidths[df->numCols];
    for (int i = 0; i < df->numCols; i++) {
        colWidths[i] = strlen(df->featureNames[i]) + 4;
    }

    printf("%dx%d DataFrame\n", df->numRows, df->numCols);

    for (int i = 0; i < df->numCols; i++) {
        char *name = df->featureNames[i];
        printf("%-*s", colWidths[i], name);
    }

    for (int rowIdx = 0; rowIdx < df->numRows; rowIdx++) {
        printf("\n");
        for (int colIdx = 0; colIdx < df->numCols; colIdx++) {
            printf("%-*.0lf", colWidths[colIdx], df->data[rowIdx * df->numCols + colIdx]);
        }
    }
}

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

