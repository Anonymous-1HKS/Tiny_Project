#include <iostream>
#include <cassert>
class Matrix {
private:
    int mNumRows;
    int mNumCols;
    double** mData;
public:
    Matrix(int numRows, int numCols) {
        assert(numRows > 0);
        assert(numCols > 0);
        mNumRows = numRows;
        mNumCols = numCols;
        mData = new double*[mNumRows];
        for (int i = 0; i < mNumRows; i = i + 1) {
            mData[i] = new double[mNumCols];
            for (int j = 0; j < mNumCols; j = j + 1) {
                mData[i][j] = 0.0;
            }
        }
    }
    ~Matrix() {
        if (mData != nullptr) {
            for (int i = 0; i < mNumRows; i = i + 1) {
                delete[] mData[i];
            }
            delete[] mData;
        }
    }
    Matrix(const Matrix& other) {
        mNumRows = other.mNumRows;
        mNumCols = other.mNumCols;
        mData = new double*[mNumRows];
        for (int i = 0; i < mNumRows; i = i + 1) {
            mData[i] = new double[mNumCols];
            for (int j = 0; j < mNumCols; j = j + 1) {
                mData[i][j] = other.mData[i][j];
            }
        }
    }
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            if (mData != nullptr) {
                for (int i = 0; i < mNumRows; i = i + 1) {
                    delete[] mData[i];
                }
                delete[] mData;
            }
            mNumRows = other.mNumRows;
            mNumCols = other.mNumCols;
            mData = new double*[mNumRows];
            for (int i = 0; i < mNumRows; i = i + 1) {
                mData[i] = new double[mNumCols];
                for (int j = 0; j < mNumCols; j = j + 1) {
                    mData[i][j] = other.mData[i][j];
                }
            }
        }
        return *this;
    }
    int getNumRows() const {
        return mNumRows;
    }
    int getNumCols() const {
        return mNumCols;
    }
    double& operator()(int i, int j) {
        assert(i >= 1);
        assert(i <= mNumRows);
        assert(j >= 1);
        assert(j <= mNumCols);
        return mData[i - 1][j - 1];
    }
    const double& operator()(int i, int j) const {
        assert(i >= 1);
        assert(i <= mNumRows);
        assert(j >= 1);
        assert(j <= mNumCols);
        return mData[i - 1][j - 1];
    }
    Matrix operator-() const {
        Matrix result(mNumRows, mNumCols);
        for (int i = 0; i < mNumRows; i = i + 1) {
            for (int j = 0; j < mNumCols; j = j + 1) {
                result.mData[i][j] = -mData[i][j];
            }
        }
        return result;
    }
    Matrix operator+(const Matrix& other) const {
        assert(mNumRows == other.mNumRows);
        assert(mNumCols == other.mNumCols);
        Matrix result(mNumRows, mNumCols);
        for (int i = 0; i < mNumRows; i = i + 1) {
            for (int j = 0; j < mNumCols; j = j + 1) {
                result.mData[i][j] = mData[i][j] + other.mData[i][j];
            }
        }
        return result;
    }
    Matrix operator-(const Matrix& other) const {
        assert(mNumRows == other.mNumRows);
        assert(mNumCols == other.mNumCols);
        Matrix result(mNumRows, mNumCols);
        for (int i = 0; i < mNumRows; i = i + 1) {
            for (int j = 0; j < mNumCols; j = j + 1) {
                result.mData[i][j] = mData[i][j] - other.mData[i][j];
            }
        }
        return result;
    }
    Matrix operator*(const Matrix& other) const {
        assert(mNumCols == other.mNumRows);
        Matrix result(mNumRows, other.mNumCols);
        for (int i = 0; i < mNumRows; i = i + 1) {
            for (int j = 0; j < other.mNumCols; j = j + 1) {
                double sum = 0.0;
                for (int k = 0; k < mNumCols; k = k + 1) {
                    sum = sum + mData[i][k] * other.mData[k][j];
                }
                result.mData[i][j] = sum;
            }
        }
        return result;
    }
    Matrix operator*(double scalar) const {
        Matrix result(mNumRows, mNumCols);
        for (int i = 0; i < mNumRows; i = i + 1) {
            for (int j = 0; j < mNumCols; j = j + 1) {
                result.mData[i][j] = mData[i][j] * scalar;
            }
        }
        return result;
    }
    Matrix transpose() const {
        Matrix result(mNumCols, mNumRows);
        for (int i = 0; i < mNumRows; i = i + 1) {
            for (int j = 0; j < mNumCols; j = j + 1) {
                result.mData[j][i] = mData[i][j];
            }
        }
        return result;
    }
    double determinant() const {
        assert(mNumRows == mNumCols);
        int n = mNumRows;
        Matrix temp(*this);
        double det = 1.0;
        for (int i = 0; i < n; i = i + 1) {
            int pivot = i;
            for (int r = i + 1; r < n; r = r + 1) {
                if (std::abs(temp.mData[r][i]) > std::abs(temp.mData[pivot][i])) {
                    pivot = r;
                }
            }
            if (std::abs(temp.mData[pivot][i]) < 1e-9) {
                return 0.0;
            }
            if (pivot != i) {
                double* tRow = temp.mData[i];
                temp.mData[i] = temp.mData[pivot];
                temp.mData[pivot] = tRow;
                det = -det;
            }
            det = det * temp.mData[i][i];
            for (int r = i + 1; r < n; r = r + 1) {
                double factor = temp.mData[r][i] / temp.mData[i][i];
                for (int c = i; c < n; c = c + 1) {
                    temp.mData[r][c] = temp.mData[r][c] - factor * temp.mData[i][c];
                }
            }
        }
        return det;
    }
    Matrix inverse() const {
        assert(mNumRows == mNumCols);
        int n = mNumRows;
        Matrix aug(n, 2 * n);
        for (int i = 0; i < n; i = i + 1) {
            for (int j = 0; j < n; j = j + 1) {
                aug.mData[i][j] = mData[i][j];
            }
            aug.mData[i][i + n] = 1.0;
        }
        for (int i = 0; i < n; i = i + 1) {
            int pivot = i;
            for (int r = i + 1; r < n; r = r + 1) {
                if (std::abs(aug.mData[r][i]) > std::abs(aug.mData[pivot][i])) {
                    pivot = r;
                }
            }
            assert(std::abs(aug.mData[pivot][i]) > 1e-9);
            if (pivot != i) {
                double* tRow = aug.mData[i];
                aug.mData[i] = aug.mData[pivot];
                aug.mData[pivot] = tRow;
            }
            double pivotVal = aug.mData[i][i];
            for (int c = 0; c < 2 * n; c = c + 1) {
                aug.mData[i][c] = aug.mData[i][c] / pivotVal;
            }
            for (int r = 0; r < n; r = r + 1) {
                if (r != i) {
                    double factor = aug.mData[r][i];
                    for (int c = 0; c < 2 * n; c = c + 1) {
                        aug.mData[r][c] = aug.mData[r][c] - factor * aug.mData[i][c];
                    }
                }
            }
        }
        Matrix result(n, n);
        for (int i = 0; i < n; i = i + 1) {
            for (int j = 0; j < n; j = j + 1) {
                result.mData[i][j] = aug.mData[i][j + n];
            }
        }
        return result;
    }
    Matrix pseudoInverse() const {
        Matrix AT = this->transpose();
        if (mNumRows >= mNumCols) {
            Matrix ATA = AT * (*this);
            return ATA.inverse() * AT;
        } else {
            Matrix AAT = (*this) * AT;
            return AT * AAT.inverse();
        }
    }
    void print() const {
        for (int i = 0; i < mNumRows; i = i + 1) {
            for (int j = 0; j < mNumCols; j = j + 1) {
                std::cout << mData[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};
int main() {
    int r, c;
    std::cout << "Nhap so dong va so cot: ";
    std::cin >> r >> c;
    Matrix m(r, c);
    std::cout << "Nhap cac phan tu ma tran (dung chi so 1-based):" << std::endl;
    for (int i = 1; i <= r; i = i + 1) {
        for (int j = 1; j <= c; j = j + 1) {
            double val;
            std::cin >> val;
            m(i, j) = val;
        }
    }
    std::cout << "Ma tran vua nhap la:" << std::endl;
    m.print();
    if (r == c) {
        double det = m.determinant();
        std::cout << "Dinh thuc: " << det << std::endl;
        if (std::abs(det) > 1e-9) {
            std::cout << "Ma tran nghich dao la:" << std::endl;
            Matrix inv = m.inverse();
            inv.print();
        } else {
            std::cout << "Ma tran khong co nghich dao vi dinh thuc bang 0" << std::endl;
        }
    }
    std::cout << "Ma tran gia nghich dao (Pseudo-inverse) la:" << std::endl;
    Matrix pinv = m.pseudoInverse();
    pinv.print();
    return 0;
}
