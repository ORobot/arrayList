#ifndef __ARRAYLIST__
#define __ARRAYLIST__

#include <sstream>
#include <iostream>
#include <algorithm>
#include <exception>
#include <iterator>
#include "linearList.hpp"

template<class T>
class arrayList : public linearList<T>
{
public:
	class illegalParameterValue
	{
		public:
			illegalParameterValue(const std::string s) { std::cout << s << std::endl; }
			~illegalParameterValue() {}
	};
	class illegalIndex
	{
		public:
			illegalIndex(const std::string s) { std::cout << s << std::endl; }
			~illegalIndex() {}
	};

	
	arrayList(int initialCapacity = 10);
	arrayList(const arrayList<T>&);
	~arrayList() { delete[] element; }

	bool empty() const { return listSize == 0; }  //为空返回真, 否则为假
	int size() const { return listSize; }					//返回数组的大小
	void trimToSize();
	T& get(int theIndex) const;										//按索引访问元素
	int indexOf(const T& theElement) const;				//访问元素的索引
	int lastIndexOf(const T&) const;
	void insert(int theIndex, const T& theElement);
	void erase(int theIndex);
	void output(std::ostream& out) const;
	int capacity() const { return arrayLength; }
	void push_back(const T&);
	T pop_back();
	void clear();
	void removeRange(int startIndex, int endIndex);
	T set(int theIndex, const T& theElement);
	void setSize(int theNewSize);
	void reserve(int theCapacity);

	T& operator[](int theIndex);
	bool operator==(const arrayList<T>&) const;
	bool operator!=(const arrayList<T>&) const;
  
protected:
	int checkIndex(int theIndex) const;
	void changeLength1D();
	T* element;
	int arrayLength;
	int listSize;
};

template<class T>
void arrayList<T>::changeLength1D()
{
	T* nel = new T[2 * arrayLength];
	std::copy(element, element+listSize, nel);
	delete [] element;
	element = nel;
	arrayLength *= 2;
}

template<class T>
arrayList<T>::arrayList(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		std::ostringstream s;
		s << '\n' << "Initial Capacity = " << initialCapacity << ". Must be > 0" << std::endl;
		throw illegalParameterValue(s.str());
	}

	element = new T[initialCapacity];
	arrayLength = initialCapacity;
	listSize = 0;
}


template<class T>
arrayList<T>::arrayList(const arrayList<T>& other)
{
	if(*this == other)
		return;

	arrayLength = other.arrayLength;
	listSize = other.listSize;
	element = new T[arrayLength];
	std::copy(other.element, other.element + listSize, element);
}

template<class T>
int arrayList<T>::checkIndex(int theIndex) const
{
	if(theIndex < 0 || theIndex >= listSize)
	{
		std::ostringstream s;
		s << '\n' << "index = " << theIndex << " size = " << listSize << std::endl;
		throw illegalIndex(s.str());
	}
}

template<class T>
void arrayList<T>::trimToSize()
{
	arrayLength = listSize;
	T* temp = new T[arrayLength];
	std::copy(element, element+listSize, temp);
	delete[]element;
	element = temp;
}

template<class T>
T& arrayList<T>::get(int theIndex) const
{
	checkIndex(theIndex);
	return element[theIndex]; 
}

template<class T>
int arrayList<T>::indexOf(const T& theElement) const
{
	int theIndex = (int) (std::find(element, element+listSize, theElement) - element);

	if(theIndex == listSize)
		return -1;

	return theIndex;
}

template<class T>
int arrayList<T>::lastIndexOf(const T& theElement) const
{
	int theIndex = indexOf(theElement);
	for(int i = theIndex + 1; i < listSize; ++i)
	{
		if(element[i] == theElement)
		{
			theIndex = i;
		}
	}

	return theIndex;
}

template<class T>
void arrayList<T>::insert(int theIndex, const T& theElement)
{
	if(theIndex < 0 || theIndex > listSize)
	{
		std::ostringstream s;
		s << "The index = " << theIndex << "; the size = " << listSize << std::endl;
		throw illegalIndex(s.str());
	}

	if (listSize == arrayLength)
	{
		changeLength1D();
	}
	std::copy_backward(element+theIndex, element+listSize, element+listSize+1);
	element[theIndex] = theElement;
	listSize++;
}

template<class T>
void arrayList<T>::erase(int theIndex)
{
	checkIndex(theIndex);
	std::copy(element+theIndex+1, element+listSize, element+theIndex);
	listSize--;
	element[listSize].~T();
}

template<class T>
void arrayList<T>::output(std::ostream& os) const
{
	std::copy(element, element+listSize, std::ostream_iterator<T>(os, " "));
}

template<class T>
void arrayList<T>::push_back(const T& theElement)
{
	if(listSize == arrayLength)
		changeLength1D();

	element[listSize] = theElement;
	listSize++;
}

template<class T>
T arrayList<T>::pop_back()
{
	T temp= element[--listSize];
	return temp;
}

template<class T>
void arrayList<T>::clear()
{
	listSize = 0;
}

template<class T>
void arrayList<T>::removeRange(int startIndex, int endIndex)
{
	std::copy(element+endIndex + 1, element+listSize, element+startIndex);
	listSize -= endIndex - startIndex + 1;
}

template<class T>
T arrayList<T>::set(int theIndex, const T& theElement)
{
	checkIndex(theIndex);
	T temp = element[theIndex];
	element[theIndex] = theElement;
	return temp;
}

template<class T>
void arrayList<T>::setSize(int theNewSize)
{
	if(theNewSize == arrayLength)
		return;

	int newSize = std::min(arrayLength, theNewSize);
	T* temp = new T[theNewSize];
	std::copy(element, element+newSize, temp);
	delete []element;
	element = temp;
	arrayLength = theNewSize;
	listSize = std::min(newSize, listSize);
}

template<class T>
void arrayList<T>::reserve(int theCapacity)
{
	int newSize = std::max(theCapacity, arrayLength);
	if(newSize <= arrayLength)
		return;
	else
		setSize(newSize);
}

template<class T>
T& arrayList<T>::operator[](int theIndex)
{
	checkIndex(theIndex);
	return element[theIndex];
}

template<class T>
bool arrayList<T>::operator==(const arrayList<T>& rhl) const
{
	if(size() != rhl.size())
		return false;

	for(int i = 0; i < size(); ++i)
	{
		if(element[i] != rhl.element[i])
		{
			return false;
		}
	}

	return true;
}

template<class T>
bool arrayList<T>::operator!=(const arrayList<T>& rhl) const
{
	return !(*this == rhl);
}


#endif
