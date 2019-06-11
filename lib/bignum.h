// Big number library, not very perfect, but can already be in use.
// Created on: Jun 4, 2010
// Last modified:  Jun 4, 2010
#pragma once
#ifndef BIGNUM_H
#define BIGNUM_H

#include <cstdio>
#include <cstring>

// Bugs:
// Only work for positive integers.
// Not yet overloaded operators that take an int as the first parameter,
//  e.g. Int<count> operator*(int, Int<count>);
// QUESTION: Do I really need to do so? Wouldn't it be like this? Especially when I declared the default value of count?
//  Int<count>(some 32-bit integer).operator*(the other Int)
template <int count>
class Int
{
 public:
	 Int();
	 Int(int);
	 Int(const Int<count>&);
	inline void input();
	inline void output() const;
	inline void outputln() const;
	inline const Int<count>& operator=(const Int<count>&);
	inline const Int<count>& operator+(const Int<count>&) const;
	inline const Int<count>& operator-(const Int<count>&) const;
	inline const Int<count>& operator*(const Int<count>&) const;
	inline const Int<count>& operator/(Int<count>) const;
	inline const Int<count>& operator%(const Int<count>&) const;
	inline const Int<count>& operator+=(const Int<count>&);
	inline const Int<count>& operator-=(const Int<count>&);
	inline const Int<count>& operator*=(const Int<count>&);
	inline const Int<count>& operator/=(const Int<count>&);
	inline const Int<count>& operator%=(const Int<count>&);
	inline bool operator<(const Int<count>&) const;
	inline bool operator<=(const Int<count>&) const;
	inline bool operator>(const Int<count>&) const;
	inline bool operator>=(const Int<count>&) const;
	inline bool operator==(const Int<count>&) const;
	inline bool operator!=(const Int<count>&) const;
 private:
	static const int N;
	// Lowest significant digit comes first
	int num[count];
	// dig stands for the number of elements used in the array
	int dig;
};
// Do not change the value of N, or you'll ruin everything!
template <int count>
const int Int<count>::N = 10000;

#include "bignum.cpp"
#endif /* BIGNUM_H */
