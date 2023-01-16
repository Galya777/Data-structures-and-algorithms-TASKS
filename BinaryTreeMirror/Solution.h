#pragma once

#include "Allocator.h"
#include "Node.h"

#include <stdexcept>
#include <algorithm>

int getHeigh(Node<int>* rootptr) {
    if (rootptr == nullptr) return 0;

    return std::max(getHeigh(rootptr->left), getHeigh(rootptr->right)) + 1;
}

bool isHeightBalanced(Node<int>* rootptr)
{
    if (rootptr == nullptr) return true;
    if (abs(getHeigh(rootptr->left)-getHeigh(rootptr->right))>1) return false;
    return isHeightBalanced(rootptr->left)&&isHeightBalanced(rootptr->right);
}

template <typename AllocatorType>
void free(Node<int>* rootptr, AllocatorType& allocator)
{
    if (rootptr == nullptr) return;
   
    free(rootptr->left, allocator);
    free(rootptr->right, allocator);
 allocator.release(rootptr);
}

template <typename AllocatorType>
Node<int>* cloneMirror(Node<int>* rootptr, AllocatorType& allocator)
{
    if (rootptr == nullptr) return nullptr;
    Node<int>* clone = allocator.buy();
    if (!rootptr) {
        throw std::bad_alloc();
        free(clone, allocator);
    }  
    clone->left = cloneMirror(rootptr->right, allocator);
    clone->right = cloneMirror(rootptr->left, allocator);
    clone->data = rootptr->data;
    return clone;
}
