#ifndef DATAFRAME_IO_H
#define DATAFRAME_IO_H

#include "./core.h"

/**
 * @brief Instantiates a DataFrame containing data from a CSV file.
 *
 * @param path Path to CSV file.
 * @return DataFrame with data from the CSV. NULL on error.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-01
 */
dataframe_t *df_read_csv(char *path);

/**
 * @brief Instantiates a DataFrame containing data from a CSV file.
 *
 * @param df Pointer of the DataFrame to save.
 * @param path Path of which to save the CSV file to.
 * @param precision Floating point precision of the data.
 * @return 0 on success, non-zero on failure.
 *
 * @author PeppermintSnow
 * @since 0.0.0
 * @version 0.0.0
 * @date 2026-03-01
 */
int df_write_csv(dataframe_t *df, char *path, int precision);

#endif
