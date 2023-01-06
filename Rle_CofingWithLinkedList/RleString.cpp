#include "RleString.h"
#include <iostream>
// TODO Write your implementation here

//helping function to get the element at current node

char RleString::GetNth(Node* head, size_t index)
{

	Node* current = head;

	int count = 0;
	while (current != NULL) {
		if (count == index)
			return (current->symbol);
		count++;
		current = current->next;
	}	
}

void RleString::copy(const RleString& other)
{
	rleString = new Node[other.strSize + 1];
	this->strSize = other.strSize;
	for (size_t i = 0; i < other.strSize; i++)
	{
		this->rleString[i].symbol = other.rleString[i].symbol;
		this->rleString[i].count = other.rleString[i].count;
		this->rleString[i].next = other.rleString[i].next;
	}
}

void RleString::clear()
{
	delete[] rleString;
}

RleString::RleString()
{
	rleString = new Node[1];
	rleString = NULL;
	strSize = 0;
}

RleString::RleString(const std::string& str)
{
	size_t n = str.length();
	rleString = new Node[n+1];
	strSize = 0;
	for (size_t i = 0; i < n; i++) {
		int count = 1;
		if (strSize >= 1) {
			rleString[strSize - 1].next = &rleString[strSize];
			rleString[strSize - 1].next = &rleString[strSize];
		}

		rleString[strSize].symbol = str[i];
		rleString[strSize].count = count;
		rleString[strSize].next = NULL;
	   ++strSize;
	}
}

RleString::RleString(const RleString& other)
{
	copy(other);
}

RleString& RleString::operator=(const RleString& other)
{
	if (this != &other) {
		clear();
		copy(other);
	}
	return *this;
	// TODO: insert return statement here
}

RleString::~RleString()
{
	clear();
}

std::string RleString::toString() const
{
	std::string result = "";
	if (rleString == NULL) return result;
	for (size_t i = 0; i < strSize; i++)
	{
		for (size_t j = 0; j < rleString[i].count; j++)
		{
			result += rleString[i].symbol;
		}
	}
	return result;
}

bool RleString::operator==(const RleString& other) const
{
	if (strSize != other.strSize) return false;
	for (size_t i = 0; i < other.strSize; i++)
	{
		if (this->rleString[i].symbol != other.rleString[i].symbol) return false;
		if (this->rleString[i].count != other.rleString[i].count) return false;
	}
	return true;
}

bool RleString::operator==(const std::string& str) const
{

	for (size_t i = 0; i < strSize; i++)
	{
		if (rleString[i].symbol != str[i]) return false;
	}
	return true;

}

size_t RleString::size() const noexcept
{
	return strSize;
}

void RleString::insertAt(size_t index, char value)
{
	if (index > strSize) throw std::out_of_range("Too big index!");
	std::string make;
	make.push_back(value);
	if (strSize == 0) {
		RleString rle = RleString(make);
		copy(rle);
		
	}	
	else {
		for (size_t i = strSize; i > index; --i) {
			rleString[i] = rleString[i - 1];
		}
		rleString[index].symbol = value;
		rleString[index].count = 1;
		if (index > 1) {
			rleString[index - 1].next = &rleString[index];			
		}
		++strSize;
	}
}

void RleString::removeAt(size_t index)
{
	if (index >= strSize) throw std::out_of_range("Too big index");

	if (rleString[index].count > 1) {
		rleString[index].count--;
		if (index > 1) rleString[index - 1].next = &rleString[index];
	} 
	else {
		for (size_t i = index; i < strSize-1; ++i) {
			if (i >= 1) {
				rleString[i - 1].next = &rleString[i + 1];
			}
			rleString[i].symbol = rleString[i + 1].symbol;
			rleString[i].count = rleString[i + 1].count;
			rleString[i].next->symbol = i < strSize - 2 ? rleString[i + 2].symbol : ' ';
			rleString[i].next->count = i < strSize - 2 ? rleString[i + 2].count : 0;
		}

	  strSize--;
	}
	
}

void RleString::reverse()
{
	Node* reversed = new Node[strSize];
	for (size_t i = 0; i < strSize; i++)
	{
		reversed[i] = rleString[strSize - 1 - i];
	}
	rleString = reversed;
}

bool RleString::contains(const RleString& rle) const
{
	Node* ptr1 =rleString , *ptr2 = rle.rleString;

	if (rleString == NULL && rle.rleString == NULL)
		return true;
	if (rle.rleString == NULL) return true;
	if (rleString == NULL ||
		(rleString != NULL && rle.rleString == NULL))
		return false;

	int i = 0, j = 0;

	while (i < strSize && j < rle.strSize) {

		if (rleString[i].symbol == rle.rleString[j].symbol && rleString[i].count == rle.rleString[j].count) {

			i++;
			j++;

			if (j == rle.strSize)
				return true;
		}
		else {
			i = i - j + 1;
			j = 0;
		}
	}

	return false;
}
