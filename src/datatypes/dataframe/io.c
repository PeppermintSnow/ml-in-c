#include "../../../include/datatypes/dataframe/core.h"
#include "../../../include/datatypes/dataframe/io.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline void arr_free(char **arr, size_t n) {
    for (size_t i = 0; i < n; i++)
        free(arr[i]);
    free(arr);
} 

dataframe_t *df_read_csv(char *path) {
    FILE *fptr = fopen(path, "r");
    if (!fptr)
        return NULL;

    struct dataframe *df = calloc(1, sizeof(struct dataframe));
    if (!df)
        return NULL;

    char buffer[BUFSIZ];

    fgets(buffer, BUFSIZ, fptr);
    buffer[strcspn(buffer, "\n")] = '\0';

    // count rows
    df->n_rows = 0;
    while (fgets(buffer, BUFSIZ, fptr))
        df->n_rows++;

    fseek(fptr, 0L, SEEK_SET);
    fgets(buffer, BUFSIZ, fptr);

    // count cols
    df->n_cols = 1;
    char *tmp = buffer;
    while (*tmp) {
        if (*tmp++ == ',')
            df->n_cols++;
    };

    df->columns = malloc(df->n_cols * sizeof(*df->columns));
    if (!df->columns)
        goto fail;

    size_t col_idx = 0;
    char *col_name = strtok(buffer, ",");
    while (col_name) {
        col_name[strcspn(col_name, "\n")] = '\0';

        df->columns[col_idx++] = strdup(col_name);
        if (!df->columns[col_idx - 1])
            goto fail;

        col_name = strtok(NULL, ",");
    }

    df->data = malloc(df->n_rows * df->n_cols * sizeof(*df->data));
    if (!df->data)
        goto fail;

    size_t row_idx = 0;
    while (fgets(buffer, BUFSIZ, fptr)) {
        buffer[strcspn(buffer, "\n")] = '\0';

        char *data = strtok(buffer, ",");
        size_t row_col_idx = 0;
        while (data) {
            double value = 0;
            for (size_t i = 0; data[i] != '\0'; i++) {
                if (!(data[i] >= 48 && data[i] <= 57))
                    goto fail;
                value = value * 10 + (data[i] - '0');
            }

            df->data[row_idx * df->n_cols + row_col_idx++] = value;

            data = strtok(NULL, ",");
        }

        // row-col mismatch if not equal
        if (row_col_idx != df->n_cols)
            goto fail;

        row_idx++;
    }

    fclose(fptr);

    return df;

fail:
    fclose(fptr);
    df_free(df);
    return NULL;
}

int df_write_csv(dataframe_t *df, char *path, int precision) {
    FILE *fptr = fopen(path, "w");
    if (!fptr)
        return errno;

    fprintf(fptr, "%s", df->columns[0]);
    for (size_t i = 1; i < df->n_cols; i++)
        fprintf(fptr, ",%s", df->columns[i]);

    for (size_t r = 0; r < df->n_rows; r++) {
        fprintf(fptr, "\n%.*lf", precision, df->data[r * df->n_cols]);
        for (size_t c = 1; c < df->n_cols; c++) {
            fprintf(fptr, ",%.*lf", precision, df->data[r * df->n_cols + c]);
        }
    }

    fclose(fptr);

    return DF_OK;
}
