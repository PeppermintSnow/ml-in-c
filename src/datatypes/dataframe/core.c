#include "../../../include/datatypes/dataframe/core.h"
#include "../../../include/datatypes/dataframe/core_internal.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Creates a DataFrame with one feature/column from an array.
 * Allocates memory and copies input into the struct.
 */
dataframe_t *df_from_array(
    const double *data,
    const size_t n_rows, 
    const char *col,
    int *err_out
) {
    if (
        data == NULL 
        || col == NULL 
        || n_rows == 0 
        || n_rows > SIZE_MAX / sizeof(*data)
    )
        return df_fail(err_out, DF_BAD_ARG);

    struct dataframe *df = malloc(sizeof(struct dataframe));
    if (!df)
        return df_fail(err_out, DF_OOM);

    df->data = malloc(n_rows * sizeof(*df->data));
    if (!df->data)
        goto fail;

    df->columns = malloc(sizeof(*df->columns));
    if (!df->columns)
        goto fail;

    df->columns[0] = strdup(col);
    if (!df->columns[0])
        goto fail;

    memcpy(df->data, data, n_rows * sizeof(*df->data));
    df->n_rows = n_rows;
    df->n_cols = 1;

    if (err_out)
        *err_out = DF_OK;
    return df;

fail:
    df_free(df);
    return df_fail(err_out, DF_OOM);
}

/**
 * Fetch a column from a DataFrame.
 */
double *df_col_get(const dataframe_t *df, const char *col, int *err_out) {
    size_t col_idx = df_col_idx(df, col);

    if (col_idx == (size_t)-1)
        return df_fail(err_out, DF_NO_COL);
    
    double *col_data = malloc(df->n_rows * sizeof(double));
    if (!col_data)
        return df_fail(err_out, DF_OOM);

    for (size_t r = 0; r < df->n_rows; r++)
        col_data[r] = df->data[r * df->n_cols + col_idx];
        
    if (err_out)
        *err_out = DF_OK;
    return col_data;
}

/**
 * Adds a new column/feature to an existing DataFrame.
 * Expands allocated memory and appends input data to the end of each row.
 */
int df_col_append(dataframe_t *df, const double *data, const size_t n_rows, const char *col) {
    if (n_rows != df->n_rows)
        return DF_ROW_MISMATCH;

    for (size_t i = 0; i < df->n_cols; i++)
        if (strcmp(col, df->columns[i]) == 0)
            return DF_COL_EXISTS;

    if (df->n_cols + 1 > SIZE_MAX / df->n_rows)
        return DF_OOM;

    double *tmp_data = malloc(df->n_rows * (df->n_cols + 1) * sizeof(*df->data));
    if (!tmp_data) 
        return DF_OOM;

    char **tmp_cols = malloc((df->n_cols + 1) * sizeof(*df->columns));
    if (!tmp_cols)
        goto fail;

    char *tmp_col_name = strdup(col);
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
        tmp_cols[i] = strdup(df->columns[i]);
        if (!tmp_cols[i])
            goto fail;
        n_allocated++;
    }

    tmp_cols[df->n_cols] = tmp_col_name;

    for (size_t i = 0; i < df->n_cols; i++)
        free(df->columns[i]);
    free(df->columns);
    free(df->data);

    df->data = tmp_data;
    df->columns = tmp_cols;
    df->n_cols++;

    return DF_OK;

fail:
    if (tmp_data)
        free(tmp_data);
    if (tmp_cols)
        free(tmp_cols);
    for (size_t i = 0; i < n_allocated; i++)
        free(tmp_cols[i]);
    if (tmp_col_name)
        free(tmp_col_name);
    return DF_OOM;
}

/**
 * Deletes the specified column from a DataFrame.
 */
int df_col_drop(dataframe_t *df, const char *col) {
    size_t col_idx = df_col_idx(df, col);

    if (col_idx == (size_t)-1)
        return DF_NO_COL;

    if (df->n_cols == 1)
        return DF_LAST_COL;

    double *tmp_data = malloc(df->n_rows * (df->n_cols - 1) * sizeof(*df->data));
    if (!tmp_data)
        return DF_OOM;

    char **tmp_cols = malloc((df->n_cols - 1) * sizeof(*df->columns));
    if (!tmp_cols)
        goto fail;

    size_t tmp_data_idx = 0;
    for (size_t r = 0; r < df->n_rows; r++) {
        for (size_t c = 0; c < df->n_cols; c++) {
            if (c == col_idx)
                continue;
            tmp_data[tmp_data_idx++] = df->data[r * df->n_cols + c];
        }
    }

    size_t tmp_col_idx = 0;
    for (size_t i = 0; i < df->n_cols; i++) {
        if (i == col_idx)
            continue;
        tmp_cols[tmp_col_idx] = strdup(df->columns[i]);
        if (!tmp_cols[tmp_col_idx])
            goto fail;
        tmp_col_idx++;
    }

    for (size_t i = 0; i < df->n_cols; i++) 
        free(df->columns[i]);
    free(df->columns);
    free(df->data);

    df->data = tmp_data;
    df->columns = tmp_cols;
    df->n_cols--;

    return DF_OK;

fail:
    if (tmp_data)
        free(tmp_data);
    for (size_t j = 0; j < tmp_col_idx; j++)
        free(tmp_cols[j]);
    if (tmp_cols)
        free(tmp_cols);
    return DF_OOM;
}

/**
 * Fetch a row from a DataFrame.
 */
double *df_row_get(const dataframe_t *df, const size_t row_idx, int *err_out) {
    if (row_idx > df->n_rows)
        return df_fail(err_out, DF_NO_ROW);

    double *row_data = malloc(sizeof(struct dataframe));
    if (!row_data)
        return df_fail(err_out, DF_OOM);

    memcpy(
            row_data,
            &df->data[row_idx * df->n_cols], 
            df->n_cols * sizeof(*df->data)
          );

    if (err_out)
        *err_out = DF_OK;
    return row_data;
}

/**
 * Adds a row/entry to a DataFrame.
 */
int df_row_append(dataframe_t *df, const double *data, const size_t n_cols) {
    if (n_cols != df->n_cols)
        return DF_COL_MISMATCH;

    if (df->n_rows + 1 > SIZE_MAX / df->n_cols)
        return DF_OOM;

    double *tmp_data = malloc(
        (df->n_rows + 1) * df->n_cols * sizeof(*df->data)
    );
    if (!tmp_data) 
        return DF_OOM;

    memcpy(
        tmp_data, 
        df->data, 
        df->n_rows * df->n_cols * sizeof(*df->data)
    );
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
        return DF_NO_ROW;

    if (df->n_rows == 1)
        return DF_LAST_ROW;

    double *tmp_data = malloc((df->n_rows - 1) * df->n_cols * sizeof(*df->data));
    if (!tmp_data)
        return DF_OOM;

    for (size_t r = 0; r < df->n_rows; r++) {
        if (r == row_idx) 
            continue;

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
    if (df->data)
        free(df->data);
    if (df->columns) {
        for (size_t i = 0; i < df->n_cols; i++)
            if (df->columns[i])
                free(df->columns[i]);
        free(df->columns);
    }
    free(df);
}

const char *df_strerr(int err) {
    switch (err) {
        case DF_OK: return "No error";
        case DF_COL_EXISTS: return "Column already exists";
        case DF_NO_COL: return "Column not found";
        case DF_NO_ROW: return "Row not found";
        case DF_LAST_COL: return "Cannot delete last column";
        case DF_LAST_ROW: return "Cannot delete last row";
        case DF_ROW_MISMATCH: return "Data length does not match df->n_rows";
        case DF_COL_MISMATCH: return "Data length does not match df->n_columns";
        case DF_IO: return "I/O error";
        case DF_OOM: return "Out of memory";
        case DF_BAD_ARG: return "Bad argument";
        default: return "Unknown error";
    }
}
