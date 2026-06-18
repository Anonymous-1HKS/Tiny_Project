#include <iostream>
class Vector {
private:
    int mSize;
    double* mData;
public:
    Vector(int size) {
        mSize = size;
        if (mSize > 0) {
            mData = new double[mSize];
            for (int i = 0; i < mSize; i = i + 1) {
                mData[i] = 0.0;
            }
        } else {
            mData = nullptr;
        }
    }
    ~Vector() {
        if (mData != nullptr) {
            delete[] mData;
        }
    }
    Vector(const Vector& other) {
        mSize = other.mSize;
        if (mSize > 0) {
            mData = new double[mSize];
            for (int i = 0; i < mSize; i = i + 1) {
                mData[i] = other.mData[i];
            }
        } else {
            mData = nullptr;
        }
    }
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            if (mData != nullptr) {
                delete[] mData;
            }
            mSize = other.mSize;
            if (mSize > 0) {
                mData = new double[mSize];
                for (int i = 0; i < mSize; i = i + 1) {
                    mData[i] = other.mData[i];
                }
            } else {
                mData = nullptr;
            }
        }
        return *this;
    }
    double& operator[](int index) {
        return mData[index];
    }
    double& operator()(int index) {
        return mData[index - 1];
    }
    int getSize() {
        return mSize;
    }
    void print() {
        std::cout << "[ ";
        for (int i = 0; i < mSize; i = i + 1) {
            std::cout << mData[i] << " ";
        }
        std::cout << "]" << std::endl;
    }
};
int main() {
    int n;
    std::cout << "Nhap kich thuoc vector: ";
    std::cin >> n;
    Vector v(n);
    std::cout << "Nhap " << n << " phan tu cho vector:" << std::endl;
    for (int i = 0; i < n; i = i + 1) {
        double val;
        std::cin >> val;
        v[i] = val;
    }
    std::cout << "Vector ban vua nhap la: ";
    v.print();
    return 0;
}
