//dynamic array actually occupies more space
struct Matrix {
    int nrows, ncols;
    int** val;
    Matrix() {}
    Matrix(int nrows, int ncols) : nrows(nrows), ncols(ncols) {
        val = new int*[nrows];
        for (int r = 0; r < nrows; r++) {
            val[r] = new int[ncols];
            for (int c = 0; c < ncols; c++) val[r][c] = 0;
        }
    }
    Matrix operator* (const Matrix& other) const {
        assert(ncols == other.nrows);
        Matrix res(nrows, other.ncols);
        for (int i = 0; i < nrows; i++)
            for (int j = 0; j < ncols; j++)
                for (int k = 0; k < res.ncols; k++)
                    res.val[i][k] += val[i][j] * other.val[j][k];
        return res;
    }
    Matrix operator^ (const int& expo) const {
        if (expo == 1) return *this;
        Matrix res = (*this) ^ (expo/2);
        res = res * res;
        if (expo % 2) res = res * (*this);
        return res;
    }
};
