#include <errno.h>
#include <stdint.h>
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
dataframe_t *df_create_from_array(const double *data, const size_t n_rows, const char *col_name) {
    if (data == NULL || col_name == NULL || n_rows == 0 || n_rows > SIZE_MAX / sizeof(*data))
        return NULL;

    struct dataframe *df = malloc(sizeof(struct dataframe));
    if (!df)
        return NULL;

    df->data = malloc(n_rows * sizeof(*df->data));
    if (!df->data)
        goto fail;

    df->columns = malloc(sizeof(*df->columns));
    if (!df->columns)
        goto fail;

    df->columns[0] = strdup(col_name);
    if (!df->columns[0])
        goto fail;

    memcpy(df->data, data, n_rows * sizeof(*df->data));
    df->n_rows = n_rows;
    df->n_cols = 1;

    return df;

fail:
    df_free(df);
    return NULL;
}

/**
 * Fetch a column from a DataFrame.
 */
double *df_col_get(dataframe_t *df, const char *col_name) {
    ssize_t col_idx = -1;
    for (size_t i = 0; i < df->n_cols; i++) {
        if (strcmp(col_name, df->columns[i]) == 0) {
            col_idx = i;
            break;
        }
    }

    if (col_idx == -1)
        return NULL;
    
    double *col_data = malloc(df->n_rows * sizeof(double));
    if (!col_data)
        return NULL;

    for (size_t r = 0; r < df->n_rows; r++)
        col_data[r] = df->data[r * df->n_cols + col_idx];
        
    return col_data;
}

/**
 * Adds a new column/feature to an existing DataFrame.
 * Expands allocated memory and appends input data to the end of each row.
 */
int df_col_append(dataframe_t *df, const double *data, const size_t n_rows, const char *col_name) {
    if (n_rows != df->n_rows)
        return DF_ERR_ROW_MISMATCH;

    for (size_t i = 0; i < df->n_cols; i++)
        if (strcmp(col_name, df->columns[i]) == 0)
            return DF_ERR_DUPLICATE_COLUMN;

    if (df->n_cols + 1 > SIZE_MAX / df->n_rows)
        return -ENOMEM;

    double *tmp_data = malloc(df->n_rows * (df->n_cols + 1) * sizeof(*df->data));
    if (!tmp_data) 
        return -ENOMEM;

    char **tmp_columns = malloc((df->n_cols + 1) * sizeof(*df->columns));
    if (!tmp_columns)
        goto fail;

    char *tmp_col_name = strdup(col_name);
    if (!tmp_col_name)
        goto fail;

    for (size_t r = 0; r < df->n_rows; r++) {
        memcpy(
                &tmp_data[r * (df->n_cols + 1)],
                &df->data[r * df->n_cols],
                df->n_cols * sizeof(*df->data)
              );
        tmp_data[r * (df->n_cols + 1) + df->n_cols] = data[r];
    }

    size_t n_allocated = 0;
    for (size_t i = 0; i < df->n_cols; i++) {
        tmp_columns[i] = strdup(df->columns[i]);
        if (!tmp_columns[i])
            goto fail;
        n_allocated++;
    }

    tmp_columns[df->n_cols] = tmp_col_name;

    for (size_t i = 0; i < df->n_cols; i++)
        free(df->columns[i]);
    free(df->columns);
    free(df->data);

    df->data = tmp_data;
    df->columns = tmp_columns;
    df->n_cols++;

    return DF_OK;

fail:
    free(tmp_data);
    for (size_t i = 0; i < n_allocated; i++)
        free(tmp_columns[i]);
    free(tmp_columns);
    free(tmp_col_name);
    return -ENOMEM;
}

/**
 * Deletes the specified column from a DataFrame.
 */
int df_col_drop(dataframe_t *df, const char *col_name) {
    ssize_t col_idx = -1;
    for (size_t i = 0; i < df->n_cols; i++) {
        if (strcmp(col_name, df->columns[i]) == 0) {
            col_idx = i;
            break;
        }
    }

    if (col_idx == -1)
        return DF_ERR_NONEXISTENT_COLUMN;

    if (df->n_cols == 1)
        return DF_ERR_LAST_COLUMN;

    double *tmp_data = malloc(df->n_rows * (df->n_cols - 1) * sizeof(*df->data));
    if (!tmp_data)
        return -ENOMEM;

    char **tmp_columns = malloc((df->n_cols - 1) * sizeof(*df->columns));
    if (!tmp_columns)
        goto fail;

    size_t tmp_data_idx = 0;
    for (size_t r = 0; r < df->n_rows; r++) {
        for (size_t c = 0; c < df->n_cols; c++) {
            if (c == (size_t)col_idx)
                continue;
            tmp_data[tmp_data_idx++] = df->data[r * df->n_cols + c];
        }
    }

    size_t tmp_col_idx = 0;
    for (size_t i = 0; i < df->n_cols; i++) {
        if (i == (size_t)col_idx)
            continue;

        tmp_columns[tmp_col_idx] = strdup(df->columns[i]);
        if (!tmp_columns[tmp_col_idx])
            goto fail;
        tmp_col_idx++;
    }

    for (size_t i = 0; i < df->n_cols; i++) 
        free(df->columns[i]);
    free(df->columns);
    free(df->data);

    df->data = tmp_data;
    df->columns = tmp_columns;
    df->n_cols--;

    return DF_OK;

fail:
    free(tmp_data);
    for (size_t j = 0; j < tmp_col_idx; j++)
        free(tmp_columns[j]);
    free(tmp_columns);
    return -ENOMEM;
}

/**
 * Fetch a row from a DataFrame.
 */
double *df_row_get(dataframe_t *df, const size_t row_idx) {
    if (row_idx > df->n_rows)
        return NULL;

    double *row_data = malloc(sizeof(struct dataframe));
    if (!row_data)
        return NULL;

    memcpy(
            row_data,
            &df->data[row_idx * df->n_cols], 
            df->n_cols * sizeof(*df->data)
          );

    return row_data;
}

/**
 * Adds a row/entry to a DataFrame.
 */
int df_row_append(dataframe_t *df, const double *data, const size_t n_cols) {
    if (n_cols != df->n_cols)
        return DF_ERR_COLUMN_MISMATCH;

    if (df->n_rows + 1 > SIZE_MAX / df->n_cols)
        return -ENOMEM;

    double *tmp_data = malloc((df->n_rows + 1) * df->n_cols * sizeof(*df->data));
    if (!tmp_data) 
        return -ENOMEM;

    memcpy(tmp_data, df->data, df->n_rows * df->n_cols * sizeof(*df->data));
    memcpy(
            &tmp_data[df->n_rows * df->n_cols],
            data,
            df->n_cols * sizeof(*df->data)
          );

    free(df->data);

    df->data = tmp_data;
    df->n_rows++;

    return DF_OK;
}

/**
 * Deletes a row/entry from a DataFrame
 */
int df_row_drop(dataframe_t *df, const size_t row_idx) {
    if (row_idx > df->n_rows - 1) 
        return DF_ERR_NONEXISTENT_ROW;

    if (df->n_rows == 1)
        return DF_ERR_LAST_ROW;

    double *tmp_data = malloc((df->n_rows - 1) * df->n_cols * sizeof(*df->data));
    if (!tmp_data)
        return -ENOMEM;

    for (size_t r = 0; r < df->n_rows; r++) {
        if (r == row_idx) continue;

        size_t r_shifted = (r > row_idx) ? r - 1 : r;

        memcpy(
                &tmp_data[r_shifted * df->n_cols], 
                &df->data[r * df->n_cols],
                df->n_cols * sizeof(*df->data)
              );
    }

    free(df->data);

    df->data = tmp_data;
    df->n_rows--;

    return DF_OK;
}

/**
 * Displays the DataFrame in a table
 */
void df_display(const dataframe_t *df) {
    int widths[df->n_cols];
    for (size_t i = 0; i < df->n_cols; i++)
        widths[i] = strlen(df->columns[i]) + 4;

    printf("%zux%zu DataFrame\n", df->n_rows, df->n_cols);

    for (size_t i = 0; i < df->n_cols; i++) {
        char *name = df->columns[i];
        printf("%-*s", widths[i], name);
    }

    for (size_t r = 0; r < df->n_rows; r++) {
        printf("\n");
        for (size_t c = 0; c < df->n_cols; c++)
            printf("%-*.0lf", widths[c], df->data[r * df->n_cols + c]);
    }

    printf("\n");
}

/**
 * Frees all memory allocated by the DataFrame.
 */
void df_free(dataframe_t *df) {
    if (!df) 
        return;

    free(df->data);
    if (df->columns)
        for (size_t i = 0; i < df->n_cols; i++)
            free(df->columns[i]);
    free(df->columns);
    free(df);
}

