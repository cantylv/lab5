#pragma once
#include <iostream>
#include "my_vector.h"

template <typename T>
class MySet : public MyVector<T>
{
public:
	MySet(T el = T()) : MyVector<T>(el) {};

	MySet<T> operator+(const MySet<T>&);
	MySet<T> operator-(const MySet<T>&);
	MySet<T> operator*(const MySet<T>&);

	bool operator ==  (const MySet<T>&) const;
	MySet<T>& operator+=(const MySet<T>&);
	MySet<T>& operator-=(const MySet<T>&);
	MySet<T>& operator*=(const MySet<T>&);
	MySet<T>& operator =(const MySet<T>&);
	void add_element(T);
	void delete_element(T);
	bool is_element(T) const;
};

template<typename T>
bool MySet<T>::is_element(T obj) const
{
	for (int i = 0; i < this->size; i++)
		if (this->pdata[i] == obj)
			return true;
	return false;
}

template<>
bool MySet<char*>::is_element(char* str) const
{
	for (int i = 0; i < this->size; i++)
		if (!strcmp(str, this->pdata[i]))
			return true;
	return false;
}



template <typename T>
void MySet<T>::add_element(T obj)
{
	if (is_element(obj))
		return;
	MyVector<T>::add_element(obj);
}

template <>
void MySet<char*>::add_element(char* obj)
{
	if (is_element(obj))
		return;
	MyVector<char*>::add_element(obj);
}



template<typename T>
MySet<T> MySet<T>::operator+(const MySet<T>& obj)
{
	MySet<T> multitude = *this;
	for (int i = 0; i < obj.Size(); i++)
		if (!(*this).is_element(obj[i]))
			multitude.add_element(obj[i]);
	return multitude;
}

template<>
MySet<char*> MySet<char*>::operator+ (const MySet<char*>& obj)
{
	MySet<char*> multitude = *this;
	for (int i = 0; i < obj.Size(); i++)
		if (!(*this).is_element(obj[i]))
			multitude.add_element(obj[i]);
	return multitude;
}



template <typename T>
void MySet<T>::delete_element(T obj)
{
	if (is_element(obj))
	{
		int index = 0;
		for (int i = 0; i < this->size; i++)
			if (this->pdata[i] == obj)
				index = i;
		MyVector<T>::delete_element(index);
	}
}

template <>
void MySet<char*>::delete_element(char* obj)
{
	if (!is_element(obj))
		return;
	if (size)
	{
		int index = 0;
		for (int i = 0; i < size; i++)
			if (!strcmp(this->pdata[i], obj))
				index = i;
		MyVector<char*>::delete_element(index);
	}
}




template<typename T>
MySet<T> MySet<T>::operator-(const MySet<T>& obj)
{
	MySet<T> multitude = *this;
	for (int i = 0; i < obj.Size(); i++)
		if ((*this).is_element(obj[i]))
			multitude.delete_element(obj[i]);
	return multitude;
}

template<>
MySet<char*> MySet<char*>::operator-(const MySet<char*>& obj)
{
	MySet<char*> multitude = *this;
	for (int i = 0; i < obj.Size(); i++)
		if ((*this).is_element(obj[i]))
			multitude.delete_element(obj[i]);
	return multitude;
}




template <typename T>
MySet<T> MySet<T>::operator*(const MySet<T>& obj)
{
	MySet<T> multitude;
	for (int i = 0; i < obj.Size(); i++)
		if ((*this).is_element(obj[i]))
			multitude.add_element(obj[i]);
	return multitude;
}

template <>
MySet<char*> MySet<char*>::operator*(const MySet<char*>& obj)
{
	MySet<char*> multitude;
	for (int i = 0; i < obj.Size(); i++)
		if ((*this).is_element(obj[i]))
			multitude.add_element(obj[i]);
	return multitude;
}




template<typename T>
bool MySet<T>::operator==(const MySet<T>& obj) const
{
	int coincidence = 0;
	if (this->size != obj.size)
		return false;
	for (int i = 0; i < this->size; i++)
		if (this->is_element(obj.pdata[i]))
			++coincidence;
	return coincidence == this->size ? true : false;
}

template <typename T>
MySet<T>& MySet<T>::operator = (const MySet<T>& set)
{
	delete[] this->pdata;
	this->pdata = new T[set.size];
	for (int i = 0; i < set.size; i++)
		this->pdata[i] = set.pdata[i];
	this->maxsize = set.maxsize;
	this->size = set.size;
	return *this;
}



template <>
MySet<char*>& MySet<char*>:: operator = (const MySet<char*>& set)
{
	for (int i = 0; i < size; i++)
		delete pdata[i];
	delete pdata;
	pdata = new char* [set.size];
	for (int i = 0; i < set.size; i++)
	{
		pdata[i] = new char[strlen(set.pdata[i]) + 1];
		strcpy_s(pdata[i], strlen(set.pdata[i]) + 1, set.pdata[i]);
	}
	maxsize = set.maxsize;
	size = set.size;
	return *this;
}

template<typename T>
MySet<T>& MySet<T>::operator+=(const MySet<T>& obj)
{
	return (*this) = (*this) + obj;
}

template <typename T>
MySet<T>& MySet<T>::operator-=(const MySet<T>& obj)
{
	return (*this) = (*this) - obj;
}

template <typename T>
MySet<T>& MySet<T>::operator*=(const MySet<T>& obj)
{
	return (*this) = (*this) * obj;
}

