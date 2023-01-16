#pragma once
#include "Node.h"

//IMPORTANT: DO NOT MODIFY THIS FILE


//
// Sample tree
//
//      A:1
//     /   \
//    /     \
//   B:2    C:3
//  /  \    /
// D:4 E:5 F:6
//  \
//  G:7
class SampleTree
{
public:
	using ValueType = int;

	Node<int> g = Node<int>(7);
	Node<int> f = Node<int>(6);
	Node<int> e = Node<int>(5);
	Node<int> d = Node<int>(4, nullptr, &g);
	Node<int> c = Node<int>(3, &f, nullptr);
	Node<int> b = Node<int>(2, &d, &e);
	Node<int> a = Node<int>(1, &b, &c);
	
	Node<int>* rootptr = &a;

	const size_t nodesCount = 7;
};


//
// A tree that is NOT height-balanced
//
//      A:1
//     /   \
//    /     \
//   B:2    C:3
//  /       /
// D:4     F:6
//  \
//  G:7
class NonHeightBalancedTree
{
public:
	using ValueType = int;

	Node<int> g = Node<int>(7);
	Node<int> f = Node<int>(6);
	Node<int> d = Node<int>(4, nullptr, &g);
	Node<int> c = Node<int>(3, &f, nullptr);
	Node<int> b = Node<int>(2, &d, nullptr);
	Node<int> a = Node<int>(1, &b, &c);
	
	Node<int>* rootptr = &a;
};


//
// Sample tree
//
//      A:1
//     /   \
//    /     \
//   C:3    B:2
//    \    /  \
//    F:6 E:5 D:4
//            /
//          G:7
class MirrorCopyOfSample
{
public:
	using ValueType = int;

	Node<int> g = Node<int>(7);
	Node<int> f = Node<int>(6);
	Node<int> e = Node<int>(5);
	Node<int> d = Node<int>(4, &g, nullptr);
	Node<int> c = Node<int>(3, nullptr, &f);
	Node<int> b = Node<int>(2, &e, &d);
	Node<int> a = Node<int>(1, &c, &b);

	Node<int>* rootptr = &a;
};
