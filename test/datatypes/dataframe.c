#include <assert.h>
#include <stdio.h>
#include <string.h>
#ifdef _WIN32
    #include "..\\..\\include\\datatypes\\dataframe.h"
#else
    #include "../../include/datatypes/dataframe.h"
#endif

DataFrame *test_DF_fromArray();
void test_DF_addColumn(DataFrame *df);

// TODO: Add edge-case tests
int main() {
    DataFrame *df = test_DF_fromArray();
    test_DF_addColumn(df);
    DF_free(df);
}

DataFrame *test_DF_fromArray() {
    double X[] = {1, 2, 3, 4, 5, 6};
    int lenX = sizeof(X) / sizeof(X[0]);
    char columnName[] = "numbers";
    DataFrame *df = DF_fromArray(X, lenX, columnName);

    assert(df != NULL);
    assert(df->numCols == 1);
    assert(df->numRows == 6);
    assert(df->featureNames != NULL);
    assert(strcmp(df->featureNames[0], columnName) == 0);
    for (int i = 0; i < lenX; i++) {
        assert(df->data[i] == X[i]);
    }
    return df;
}

void test_DF_addColumn(DataFrame *df) {
    char nameX0[] = "numbers";
    char nameX1[] = "numbers1";
    char nameX2[] = "numbers2";
    double X0[] = {1, 2, 3, 4, 5, 6};
    double X1[] = {0, 0, 0, 0, 0, 0};
    double X2[] = {9, 9, 9, 9, 9, 9};

    DF_addColumn(df, X1, nameX1);
    DF_addColumn(df, X2, nameX2);

    assert(df != NULL);
    assert(df->numCols == 3);
    assert(df->numRows == 6);
    assert(df->featureNames != NULL);
    assert(strcmp(df->featureNames[0], nameX0) == 0);
    assert(strcmp(df->featureNames[1], nameX1) == 0);
    assert(strcmp(df->featureNames[2], nameX2) == 0);
    for (int i = 0; i < df->numRows; i++) {
        printf("row %d: %.1f = %.1f\n", i, df->data[i * df->numCols], X0[i]);
        printf("row %d: %.1f = %.1f\n", i * df->numCols + 1, df->data[i * df->numCols + 1], X1[i]);
        printf("row %d: %.1f = %.1f\n", i * df->numCols + 2, df->data[i * df->numCols + 2], X2[i]);
        assert(df->data[i * df->numCols] == X0[i]);
        assert(df->data[i * df->numCols + 1] == X1[i]);
        assert(df->data[i * df->numCols + 2] == X2[i]);
    }
}
