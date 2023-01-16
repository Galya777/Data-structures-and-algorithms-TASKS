#include "catch2/catch_all.hpp"
#include "Allocator.h"
#include "Node.h"
#include "SampleTree.h"
#include "Solution.h"

//IMPORTANT: DO NOT MODIFY THIS FILE

///
/// Checks whether two trees have the same structure and node values
///
template <typename T>
bool sameTrees(const Node<T>* a, const Node<T>* b)
{
    if(a == nullptr || b == nullptr)
        return a == b;

    return
        a->data == b->data &&
        sameTrees(a->left, b->left) &&
        sameTrees(a->right, b->right);
}

TEST_CASE("sameTrees() returns true for two empty trees", "[template]")
{
	Node<int>* empty = nullptr;
	REQUIRE(sameTrees(empty, empty));
}

TEST_CASE("sameTrees() returns false when comparing an empty and a non-empty tree", "[template]")
{
	Node<int>* empty = nullptr;
	Node<int> n;
	SECTION("Left is non-empty, right is empty") {
		REQUIRE_FALSE(sameTrees(&n, empty));
	}
	SECTION("Left is empty, right is non-empty") {
		REQUIRE_FALSE(sameTrees(empty, &n));
	}
}

TEST_CASE("sameTrees() returns true when comparing equivalent trees", "[template]")
{
	SampleTree t1, t2;
	REQUIRE(sameTrees(t1.rootptr, t2.rootptr));
}

TEST_CASE("sameTrees() returns false when comparing different trees", "[template]")
{
	SampleTree t1;
	NonHeightBalancedTree t2;

	REQUIRE_FALSE(sameTrees(t1.rootptr, t2.rootptr));
}

TEST_CASE("isHeightBlanced() returns true for the empty tree", "[solution]")
{
	REQUIRE(isHeightBalanced(nullptr));
}

TEST_CASE("isHeightBlanced() returns true for a single-node tree", "[solution]")
{
	Node<int> leaf;
	REQUIRE(isHeightBalanced(&leaf));
}

TEST_CASE("isHeightBlanced() returns true for a height-balanced tree", "[solution]")
{
	SampleTree t;
	REQUIRE(isHeightBalanced(t.rootptr));
}

TEST_CASE("isHeightBlanced() returns false for a NON-height-balanced tree", "[solution]")
{
	NonHeightBalancedTree t;
	REQUIRE_FALSE(isHeightBalanced(t.rootptr));
}

template <typename T>
using DebugNodeAllocator = DebugAllocator<Node<T>>;

TEST_CASE("free() does not throw for an empty tree and performs no allocations", "[solution]")
{
	DebugNodeAllocator<int> allocator;
	CHECK_NOTHROW(free(nullptr, allocator));
	CHECK(allocator.totalAllocationsCount() == 0);
}

TEST_CASE("free() correctly frees all nodes of a tree", "[solution]")
{
	DebugNodeAllocator<int> allocator;
	
	//
	// Builds a tree of the following type:
	//
	//      *
	//     / \
	//    *   *
	//   /     \
	//  *       *
	//
	Node<int>* rootptr = allocator.buy();
	rootptr->left = allocator.buy();
	rootptr->right = allocator.buy();
	rootptr->left->left = allocator.buy();
	rootptr->right->right = allocator.buy();

	size_t totalElements = 5;

	REQUIRE(allocator.allocationsCount()      == totalElements);
	REQUIRE(allocator.totalAllocationsCount() == totalElements);

	CHECK_NOTHROW(free(rootptr, allocator));

	CHECK(allocator.allocationsCount()      == 0); // All nodes have been released
	CHECK(allocator.totalAllocationsCount() == totalElements); // No new allocations were made
}

TEST_CASE("cloneMirror() returns nullptr when passed nulptr and makes no allocations", "[solution]")
{
	DebugNodeAllocator<int> allocator;
	CHECK(cloneMirror(nullptr, allocator) == nullptr);
	CHECK(allocator.totalAllocationsCount() == 0);
}

TEST_CASE("cloneMirror() returns a single-leaf node when copying a single-node tree and makes only one allocation", "[solution]")
{
	DebugNodeAllocator<int> allocator;
	int value = 42;
	Node<int> leaf(value);
	Node<int>* clone = nullptr;

	CHECK_NOTHROW(clone = cloneMirror(&leaf, allocator));

	REQUIRE(clone != nullptr);

	CHECK(clone->isLeaf());
	CHECK(clone->data == value);

	CHECK(allocator.totalAllocationsCount() == 1);
}

TEST_CASE("cloneMirror() correctly creates a mirror clone of a tree and performs only the necessary number of allocations", "[solution]")
{
	DebugNodeAllocator<int> allocator;
	SampleTree original;
	MirrorCopyOfSample expected;

	Node<int>* clone = nullptr;

	CHECK_NOTHROW(clone = cloneMirror(original.rootptr, allocator));

	REQUIRE(clone != nullptr);

	CHECK(sameTrees(expected.rootptr, clone));

	CHECK(allocator.totalAllocationsCount() == original.nodesCount);
}