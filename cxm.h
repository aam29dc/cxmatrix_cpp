#ifndef CXM_H
#define CXM_H

#include <iostream>
#include <assert.h>

namespace cxm {
	template <typename T = double>
	class Matrix {
	private:
		unsigned int _rows, _cols;
		T* _data;
		static unsigned int _count;
	public:
		Matrix(const unsigned int rows = 1, const unsigned int cols = 1, const T x = 0) : _rows(rows), _cols(cols) {
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

		~Matrix() {
			_rows = _cols = 0;
			if (_data != nullptr) {
				delete[] _data;
			}
			Matrix<T>::_count--;
		}

		Matrix(const Matrix<T>& X);
		Matrix(Matrix<T>&& move) noexcept;

		int getRows() const;
		int getCols() const;
		static int getCount();

		Matrix<T>& operator = (const Matrix<T> X);
		bool operator == (const Matrix<T>& X) const;
		inline bool operator != (const Matrix<T>& X) const;
		T operator () (const unsigned int row, const unsigned int col) const;
		T operator () (const unsigned int x) const;
		inline T operator [] (const unsigned int x) const;
		Matrix<T>& operator - ();
		inline Matrix<T>& operator + (const Matrix<T>& X);
		inline Matrix<T>& operator - (const Matrix<T>& X);
		inline Matrix<T>& operator * (const Matrix<T>& X);
		inline Matrix<T>& operator * (const T x);
		inline Matrix<T>& operator / (const T x);
		Matrix<T>& operator += (const Matrix<T>& X);
		Matrix<T>& operator -= (const Matrix<T>& X);
		Matrix<T>& operator *= (const Matrix<T>& X);
		Matrix<T>& operator *= (const T x);
		Matrix<T>& operator /= (const T x);

		void abs();
		void printMatrix() const;
		T getEntry(const unsigned int row, const unsigned int col) const;
		T getEntry(const unsigned int x) const;
		void setEntry(const unsigned int row, const unsigned int col, const T data);
		void setEntry(const unsigned int x, const T data);
		void setList(const T* const arr, const unsigned int len);
	};

	template <typename T>
	unsigned int Matrix<T>::_count = 0;
}

#endif