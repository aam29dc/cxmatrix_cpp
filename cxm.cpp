#include "cxm.h"

using namespace cxm;

template <typename T>
Matrix(const unsigned int rows, const unsigned int cols, const T x) : _rows(rows), _cols(cols) {
	static_assert(
		sizeof(T) == sizeof(int) || sizeof(T) == sizeof(float) || sizeof(T) == sizeof(double) || sizeof(T) == sizeof(long long),
		"Unsupported Matrix type."
		);

	_data = new T[_rows * _cols];

	for (unsigned int i = 0; i < _rows * _cols; i++) {
		_data[i] = x;
	}

	Matrix<T>::_count++;
}

template <typename T>
~Matrix() {
	_rows = _cols = 0;
	if (_data != nullptr) {
		delete[] _data;
	}
	Matrix<T>::_count--;
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& X) {
	_data = new T[X.getRows() * X.getCols()];
	_rows = X.getRows();
	_cols = X.getCols();

	for (unsigned int i = 0; i < X.getRows() * X.getCols(); i++) {
		_data[i] = X.getEntry(i);
	}

	Matrix<T>::_count++;
}

template <typename T>
Matrix<T>::Matrix(Matrix<T>&& move) noexcept {
	if (move._data != nullptr) {
		_data = move._data;

		move._data = nullptr;

		_rows = move._rows;
		_cols = move._cols;

		move._rows = 0;
		move._cols = 0;
	}
}

template <typename T>
int Matrix<T>::getRows() const {
	return _rows;
}

template <typename T>
int Matrix<T>::getCols() const {
	return _cols;
}

template <typename T>
int Matrix<T>::getCount() {
	return _count;
}

template <typename T>
Matrix<T>& Matrix<T>::operator = (const Matrix<T> X) {
	if (_data != nullptr) delete[] _data;
	_data = new T[X.getRows() * X.getCols()];
	_rows = X.getRows();
	_cols = X.getCols();

	for (unsigned int i = 0; i < _rows * _cols; i++) {
		_data[i] = X.getEntry(i);
	}
	return *this;
}

template <typename T>
bool Matrix<T>::operator == (const Matrix<T>& X) const {
	if (_cols != X.getCols() || _rows != X.getRows()) return false;

	for (int i = 0; i < _cols * _rows; i++) {
		if (_data[i] != X.getEntry(i)) return false;
	}
	return true;
}

template <typename T>
inline bool Matrix<T>::operator != (const Matrix<T>& X) const {
	return !(Matrix<T>::operator == (X));
}

template <typename T>
T Matrix<T>::operator () (const unsigned int row, const unsigned int col) const {
	assert(row < _rows&& col < _cols);
	return _data[row * _cols + col];
}

template <typename T>
T Matrix<T>::operator () (const unsigned int x) const {
	assert(x < _rows* _cols);
	return _data[x];
}

template <typename T>
inline T Matrix<T>::operator [] (const unsigned int x) const {
	return Matrix<T>::operator () (x);
}

template <typename T>
Matrix<T>& Matrix<T>::operator - () {
	for (unsigned int i = 0; i < _rows * _cols; i++) {
		_data[i] = -(_data[i]);
	}
	return *this;
}

template <typename T>
inline Matrix<T>& Matrix<T>::operator + (const Matrix<T>& X) {
	return (*this) += X;
}

template <typename T>
inline Matrix<T>& Matrix<T>::operator - (const Matrix<T>& X) {
	return (*this) -= X;
}

template <typename T>
inline Matrix<T>& Matrix<T>::operator * (const Matrix<T>& X) {
	return (*this) *= X;
}

template <typename T>
inline Matrix<T>& Matrix<T>::operator * (const T x) {
	return (*this) *= x;
}

template <typename T>
inline Matrix<T>& Matrix<T>::operator / (const T x) {
	return (*this) /= x;
}

template <typename T>
Matrix<T>& Matrix<T>::operator += (const Matrix<T>& X) {
	assert(X.getRows() == _rows && X.getCols() == _cols);

	for (unsigned int i = 0; i < _rows * _cols; i++) {
		_data[i] += X.getEntry(i);
	}
	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator -= (const Matrix<T>& X) {
	assert(X.getRows() == _rows && X.getCols() == _cols);

	for (unsigned int i = 0; i < _rows * _cols; i++) {
		_data[i] -= X.getEntry(i);
	}
	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator *= (const Matrix<T>& X) {
	assert(X.getRows() == _cols && X.getCols() == _rows);

	Matrix<T> result(_rows, X.getCols());
	T entry = 0;

	for (unsigned int i = 0; i < _rows; i++) {
		for (unsigned int j = 0; j < X.getCols(); j++) {
			entry = 0;
			for (unsigned int k = 0; k < _cols; k++) {
				entry += _data[i * _cols + k] * X.getEntry(j + X.getCols() * k);
			}
			result.setEntry(i * X.getCols() + j, entry);
		}
	}

	return *this = result;
}

template <typename T>
Matrix<T>& Matrix<T>::operator *= (const T x) {
	for (unsigned int i = 0; i < _rows * _cols; i++) {
		_data[i] *= x;
	}
	return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator /= (const T x) {
	assert(x != 0);

	for (unsigned int i = 0; i < _rows * _cols; i++) {
		_data[i] /= x;
	}
	return *this;
}

template <typename T>
void Matrix<T>::abs() {
	for (unsigned int i = 0; i < _rows * _cols; i++) {
		if (_data[i] < 0) {
			_data[i] = -_data[i];
		}
	}
}

template <typename T>
void Matrix<T>::printMatrix() const {
	std::cout << std::endl;
	for (unsigned int i = 0; i < _rows * _cols; i++) {
		std::cout << _data[i] << "\t";
		if ((i + 1) % _cols == 0 && i != 0) std::cout << std::endl;
	}
}

template <typename T>
T Matrix<T>::getEntry(const unsigned int row, const unsigned int col) const {
	assert(row < _rows&& col < _cols);
	return _data[row * _cols + col];
}

template <typename T>
T Matrix<T>::getEntry(const unsigned int x) const {
	assert(x < _rows* _cols);
	return _data[x];
}

template <typename T>
void Matrix<T>::setEntry(const unsigned int row, const unsigned int col, const T data) {
	assert(row < _rows&& col < _cols);
	_data[row * _cols + col] = data;
}

template <typename T>
void Matrix<T>::setEntry(const unsigned int x, const T data) {
	assert(x < _rows* _cols);
	_data[x] = data;
}

template <typename T>
void Matrix<T>::setList(const T* const arr, const unsigned int len) {
	assert(len <= _rows * _cols);

	for (unsigned int i = 0; i < len; i++) {
		_data[i] = arr[i];
	}
}

int main()
{
	cxm::Matrix<double> A(3, 3, 1);
	cxm::Matrix<double> B(3, 3, 2);
	cxm::Matrix<double> C(3, 3, 3);
	cxm::Matrix<double> D(3, 3);

	D = A + B + C;

	D.printMatrix();

	D *= (A * B * C);

	D.printMatrix();
	return 0;
}