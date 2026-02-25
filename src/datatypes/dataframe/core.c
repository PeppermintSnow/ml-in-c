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
dataframe_t *df_create_from_array(const double *data, const size_t n_rows, const char *column_name) {
    if (data == NULL || column_name == NULL || n_rows == 0 || n_rows > SIZE_MAX / sizeof(*data))
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

    df->columns[0] = strdup(column_name);
    if (!df->columns[0])
        goto fail;

    memcpy(df->data, data, n_rows * sizeof(*df->data));
    df->n_rows = n_rows;
    df->n_columns = 1;

    return df;

fail:
    df_free(df);
    return NULL;
}

/**
 * Adds a new column/feature to an existing DataFrame.
 * Expands allocated memory and appends input data to the end of each row.
 */
int df_column_add(dataframe_t *df, const double *data, const size_t n_rows, const char *column_name) {
    if (n_rows != df->n_rows)
        return DF_ERR_ROW_MISMATCH;

    for (size_t i = 0; i < df->n_columns; i++)
        if (strcmp(column_name, df->columns[i]) == 0)
            return DF_ERR_DUPLICATE_COLUMN;

    if (df->n_columns + 1 > SIZE_MAX / df->n_rows)
        return -ENOMEM;

    double *tmp_data = malloc(df->n_rows * (df->n_columns + 1) * sizeof(*df->data));
    if (!tmp_data) 
        return -ENOMEM;

    char **tmp_columns = malloc((df->n_columns + 1) * sizeof(*df->columns));
    if (!tmp_columns)
        goto fail;

    char *tmp_column_name = strdup(column_name);
    if (!tmp_column_name)
        goto fail;

    for (size_t r = 0; r < df->n_rows; r++) {
        memcpy(
                &tmp_data[r * (df->n_columns + 1)],
                &df->data[r * df->n_columns],
                df->n_columns * sizeof(*df->data)
              );
        tmp_data[r * (df->n_columns + 1) + df->n_columns] = data[r];
    }

    size_t n_allocated = 0;
    for (size_t i = 0; i < df->n_columns; i++) {
        tmp_columns[i] = strdup(df->columns[i]);
        if (!tmp_columns[i])
            goto fail;
        n_allocated++;
    }

    tmp_columns[df->n_columns] = tmp_column_name;

    for (size_t i = 0; i < df->n_columns; i++)
        free(df->columns[i]);
    free(df->columns);
    free(df->data);

    df->data = tmp_data;
    df->columns = tmp_columns;
    df->n_columns++;

    return DF_OK;

fail:
    free(tmp_data);
    for (size_t i = 0; i < n_allocated; i++)
        free(tmp_columns[i]);
    free(tmp_columns);
    free(tmp_column_name);
    return -ENOMEM;
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
        return DF_ERR_NONEXISTENT_COLUMN;

    if (df->n_columns == 1)
        return DF_ERR_LAST_COLUMN;

    double *tmp_data = malloc(df->n_rows * (df->n_columns - 1) * sizeof(*df->data));
    if (!tmp_data)
        return -ENOMEM;

    char **tmp_columns = malloc((df->n_columns - 1) * sizeof(*df->columns));
    if (!tmp_columns)
        goto fail;

    size_t tmp_data_idx = 0;
    for (size_t r = 0; r < df->n_rows; r++) {
        for (size_t c = 0; c < df->n_columns; c++) {
            if (c == (size_t)column_idx)
                continue;
            tmp_data[tmp_data_idx++] = df->data[r * df->n_columns + c];
        }
    }

    size_t tmp_column_idx = 0;
    for (size_t i = 0; i < df->n_columns; i++) {
        if (i == (size_t)column_idx)
            continue;

        tmp_columns[tmp_column_idx] = strdup(df->columns[i]);
        if (!tmp_columns[tmp_column_idx])
            goto fail;
        tmp_column_idx++;
    }

    for (size_t i = 0; i < df->n_columns; i++) 
        free(df->columns[i]);
    free(df->columns);
    free(df->data);

    df->data = tmp_data;
    df->columns = tmp_columns;
    df->n_columns--;

    return DF_OK;

fail:
    free(tmp_data);
    for (size_t j = 0; j < tmp_column_idx; j++)
        free(tmp_columns[j]);
    free(tmp_columns);
    return -ENOMEM;
}

/*
 * Adds a row/entry to a DataFrame.
 */
int df_row_add(dataframe_t *df, const double *data, const size_t n_columns) {
    if (n_columns != df->n_columns)
        return DF_ERR_COLUMN_MISMATCH;

    if (df->n_rows + 1 > SIZE_MAX / df->n_columns)
        return -ENOMEM;

    double *tmp_data = malloc((df->n_rows + 1) * df->n_columns * sizeof(*df->data));
    if (!tmp_data) 
        return -ENOMEM;

    memcpy(tmp_data, df->data, df->n_rows * df->n_columns * sizeof(*df->data));
    memcpy(
            &tmp_data[df->n_rows * df->n_columns],
            data,
            df->n_columns * sizeof(*df->data)
          );

    free(df->data);

    df->data = tmp_data;
    df->n_rows++;

    return DF_OK;
}

/*
 * Deletes a row/entry from a DataFrame
 */
int df_row_delete(dataframe_t *df, const size_t index) {
    if (index > df->n_rows - 1) 
        return DF_ERR_NONEXISTENT_ROW;

    if (df->n_rows == 1)
        return DF_ERR_LAST_ROW;

    double *tmp_data = malloc((df->n_rows - 1) * df->n_columns * sizeof(*df->data));
    if (!tmp_data)
        return -ENOMEM;

    for (size_t r = 0; r < df->n_rows; r++) {
        if (r == index) continue;

        size_t r_shifted = (r > index) ? r - 1 : r;

        memcpy(
                &tmp_data[r_shifted * df->n_columns], 
                &df->data[r * df->n_columns],
                df->n_columns * sizeof(*df->data)
              );
    }

    free(df->data);

    df->data = tmp_data;
    df->n_rows--;

    return DF_OK;
}

/*
 * Displays the DataFrame in a table
 */
void df_display(const dataframe_t *df) {
    int widths[df->n_columns];
    for (size_t i = 0; i < df->n_columns; i++)
        widths[i] = strlen(df->columns[i]) + 4;

    printf("%zux%zu DataFrame\n", df->n_rows, df->n_columns);

    for (size_t i = 0; i < df->n_columns; i++) {
        char *name = df->columns[i];
        printf("%-*s", widths[i], name);
    }

    for (size_t r = 0; r < df->n_rows; r++) {
        printf("\n");
        for (size_t c = 0; c < df->n_columns; c++)
            printf("%-*.0lf", widths[c], df->data[r * df->n_columns + c]);
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
        for (size_t i = 0; i < df->n_columns; i++)
            free(df->columns[i]);
    free(df->columns);
    free(df);
}

