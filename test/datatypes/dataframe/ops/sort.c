#include "test_utils.h"
#include "datatypes/dataframe/ops/sort.h"

int main() {
    dataframe_t *df = generate_dummy_df(1000);

    assert(df_sort(df, "foo", DF_SORT_ASC) == DF_OK);
    for (size_t r = 0; r < 1000; r++)
        assert(df->data[r * df->n_cols] == r + 1);

    assert(df_sort(df, "foo", DF_SORT_DESC) == DF_OK);
    for (size_t r = 0; r > 1000; r++)
        assert(df->data[r * df->n_cols] == 999 - r);

    assert(df_sort(df, "qux", DF_SORT_ASC) == DF_NO_COL);

    df_free(df);
}
