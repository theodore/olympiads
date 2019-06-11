#pragma once
#ifndef TREAP_H
#define TREAP_H

#include <cstddef>

namespace Tree
{
	template <typename data_t>
	class Treap
	{
	public:
		Treap(const size_t n);
		~Treap();
		void insert(const data_t& data);
		void remove(const data_t& data);
		int  find(const data_t& data);
#ifdef DB
		void output();
#endif
	private:
		int  rotate(const int x, const int d);

		struct node_t
		{
			void init(const data_t& data);
			data_t v;
			int w, c, s[2];
		};

		node_t* const node;
		int* const path;
		int root, nc;
	};
}

#include "treap.cpp"

#endif /* TREAP_H */
