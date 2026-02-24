#include <asm-generic/errno-base.h>
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
 *
 * TODO: Error handling
 *           - Empty array
 *           - Row count mismatch
 */
dataframe_t *df_create_from_array(const double *data, const int n_rows, const char *column_name) {
    struct dataframe *df = malloc(sizeof(struct dataframe));
    if (!df)
        return NULL;

    df->data = malloc(n_rows * sizeof(*df->data));
    if (!df->data) {
        free(df);
        return NULL;
    } 

    df->columns = malloc(sizeof(*df->columns));
    if (!df->columns) {
        df_free(df);
        return NULL;
    }

    df->columns[0] = strdup(column_name);
    if (!df->columns[0]) {
        df_free(df);
        return NULL;
    }

    memcpy(df->data, data, n_rows * sizeof(*df->data));
    df->n_rows = n_rows;
    df->n_columns = 1;

    return df;
}

/**
 * Adds a new column/feature to an existing DataFrame.
 * Expands allocated memory and appends input data to the end of each row.
 *
 * TODO: Error handling
 *          - Data/Row count mismatch
 *          - Duplicate column name
 */
int df_column_add(dataframe_t *df, const double *data, const char *column_name) {
    double *tmp_data = malloc(df->n_rows * (df->n_columns + 1) * sizeof(*df->data));
    if (!tmp_data) 
        return -ENOMEM;

    char **tmp_columns = malloc((df->n_columns + 1) * sizeof(*df->columns));
    if (!tmp_columns) {
        free(tmp_data);
        return -ENOMEM;
    }

    char *tmp_column_name = strdup(column_name);
    if (!tmp_column_name) {
        free(tmp_data);
        free(tmp_columns);
        return -ENOMEM;
    }

    for (size_t r = 0; r < df->n_rows; r++) {
        for (size_t c = 0; c < df->n_columns; c++) {
            // copy old to tmp with a padding at the end of each row
            tmp_data[r * (df->n_columns + 1) + c] = df->data[r * df->n_columns + c];
        }
        // fill padded gaps with new data
        tmp_data[r * (df->n_columns + 1) + df->n_columns] = data[r];
    }
    
    for (size_t i = 0; i < df->n_columns; i++) {
        char *column = strdup(df->columns[i]);
        if (!column) {
            free(tmp_data);
            free(tmp_columns);
            free(tmp_column_name);
            return -ENOMEM;
        }

        tmp_columns[i] = column;
        free(df->columns[i]);
    }

    tmp_columns[df->n_columns] = tmp_column_name;

    free(df->data);
    free(df->columns);

    df->data = tmp_data;
    df->columns = tmp_columns;
    df->n_columns++;

    return 0;
}

/*
 * Deletes the specified column from a DataFrame.
 */
int df_column_delete(dataframe_t *df, const char *column_name) {
    ssize_t column_idx = -1;
    for (size_t i = 0; i < df->n_columns; i++) {
        if (strcmp(column_name, df->columns[i]) == 0) {
            column_idx = i;
            break;
        }
    }

    if (column_idx == -1)
        return 1;

    double *tmp_data = malloc(df->n_rows * (df->n_columns - 1) * sizeof(*df->data));
    if (!tmp_data)
        return -ENOMEM;

    char **tmp_columns = malloc((df->n_columns - 1) * sizeof(*df->columns));
    if (!tmp_columns) {
        free(tmp_data);
        return -ENOMEM;
    }

    size_t tmp_data_idx = 0;
    for (size_t r = 0; r < df->n_rows; r++) {
        for (size_t c = 0; c < df->n_columns; c++) {
            if (c == (size_t)column_idx)
                continue;

            tmp_data[tmp_data_idx] = df->data[r * df->n_columns + c];
            tmp_data_idx++;
        }
    }

    size_t tmp_column_idx = 0;
    for (size_t i = 0; i < df->n_columns; i++) {
        if (i == (size_t)column_idx) continue;
        char *tmp_column_name = strdup(df->columns[i]);
        if (!tmp_column_name) {
            for (size_t j = 0; j < tmp_column_idx; j++)
                free(tmp_columns[j]);
            free(tmp_columns);
            free(tmp_data);
            return -ENOMEM;
        }

        tmp_columns[tmp_column_idx] = tmp_column_name;
        tmp_column_idx++;
    }

    for (size_t i = 0; i < df->n_columns; i++) 
        free(df->columns[i]);
    free(df->columns);
    free(df->data);

    df->data = tmp_data;
    df->columns = tmp_columns;
    df->n_columns--;

    return 0;
}

/*
 * Adds a row/entry to a DataFrame.
 */
int df_row_add(dataframe_t *df, const double *data) {
    double *tmp_data = malloc((df->n_rows + 1) * df->n_columns * sizeof(*df->data));
    if (!tmp_data) 
        return -ENOMEM;

    memcpy(tmp_data, df->data, df->n_rows * df->n_columns * sizeof(*df->data));
    for (size_t c = 0; c < df->n_columns; c++)
        tmp_data[df->n_rows * df->n_columns + c] = data[c];

    free(df->data);

    df->data = tmp_data;
    df->n_rows++;

    return 0;
}

/*
 * Deletes a row/entry from a DataFrame
 */
// int df_row_delete(dataframe_t *df, const size_t index) {
//     // TODO: Finish implementation
// }

/*
 * Displays the DataFrame in a table
 */
void df_display(const dataframe_t *df) {
    // Compute column widths
    int widths[df->n_columns];
    for (size_t i = 0; i < df->n_columns; i++) {
        widths[i] = strlen(df->columns[i]) + 4;
    }

    printf("%zux%zu DataFrame\n", df->n_rows, df->n_columns);

    for (size_t i = 0; i < df->n_columns; i++) {
        char *name = df->columns[i];
        printf("%-*s", widths[i], name);
    }

    for (size_t r = 0; r < df->n_rows; r++) {
        printf("\n");
        for (size_t c = 0; c < df->n_columns; c++) {
            printf("%-*.0lf", widths[c], df->data[r * df->n_columns + c]);
        }
    }

    printf("\n");
}

/**
 * Frees all memory allocated by the DataFrame.
 */
void df_free(dataframe_t *df) {
    if (!df) return;
    free(df->data);
    if (df->columns) {
        for (size_t i = 0; i < df->n_columns; i++) {
            free(df->columns[i]);
        }
    }
    free(df->columns);
    free(df);
}

