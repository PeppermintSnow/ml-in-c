#ifndef ML_IN_C_TEST_UTILS_H
#define ML_IN_C_TEST_UTILS_H

#include <assert.h>
#include "datatypes/dataframe/core.h"

static inline dataframe_t *generate_dummy_df(size_t n) {
    double foo[n], bar[n], baz[n];
    for (size_t i = 0; i < n; i++) {
        foo[i] = i % 2 ? i : i + 2;
        bar[i] = i * 2;
        baz[i] = i * 3;
    }

    int err;
    dataframe_t *df = df_from_array(foo, n, "foo", &err);
    assert(err == DF_OK);

    assert(df_col_append(df, bar, n, "bar") == DF_OK);
    assert(df_col_append(df, baz, n, "baz") == DF_OK);

    return df;
}

#endif
