#pragma once
#include <iostream>
#define FIRST_ELEMENT 0
#define KEFF_SIZE 1.5
#define MAX_SIZE 5



template<typename T>
class MyVector
{
public:
	MyVector(T = T(), int sz = MAX_SIZE);
	MyVector(const MyVector<T>&);
	~MyVector();

	void add_element(T);

	bool delete_element(int);
	T& operator[](int) const;

	void sort();
	int Size() const { return size; }
	int MaxSize() const { return maxsize; }
	int find (const T) const;

	MyVector& operator=(MyVector<T>&);
	friend std::ostream& operator<<(std::ostream&, const MyVector&);
protected:
	int maxsize;
	int size;
	T* pdata;
private:
	void resize();
};



template<typename T>
MyVector<T>::MyVector(T obj, int sz) : maxsize(sz), size(0)
{
	if (sz <= 0)
	{
		maxsize = MAX_SIZE;           // если пользователь передал маленький размер вектора, то мы делаем его нормальным
		sz = maxsize;
	}
	pdata = new T[maxsize];
	if (obj)
		this->add_element(obj);
}

template <>
MyVector<char*>::MyVector(char* line, int sz) : maxsize(sz), size(0)
{
	if (sz <= 0)
	{
		maxsize = MAX_SIZE;           // если пользователь передал маленький размер вектора, то мы делаем его нормальным
		sz = maxsize;
	}
	pdata = new char* [sz];
	if (line)
	{
		pdata[FIRST_ELEMENT] = new char[strlen(line) + 1];
		strcpy_s((char*)pdata[FIRST_ELEMENT], strlen(line) + 1, line);
		size++;
	}
}


template<typename T>
void MyVector<T>::add_element(T obj)
{
	if (size == maxsize)
		this->resize();
	pdata[size++] = obj;
	sort();
}

template <>
void MyVector<char*>::add_element(char* str)
{
	if (size == maxsize)
		resize();
	pdata[size] = new char[strlen(str) + 1];
	strcpy_s((char*)pdata[size++], strlen(str) + 1, (char*)str);
	sort();
}



template<typename T>
MyVector<T>::MyVector(const MyVector<T>& obj) : size(obj.size), maxsize(obj.maxsize), pdata(nullptr)
{
	if (obj.size)
	{
		pdata = new T[maxsize];
		for (int i = 0; i < size; i++)
			pdata[i] = obj.pdata[i];
	}
}

template<>
MyVector<char*>::MyVector(const MyVector<char*>& vec) : size(vec.size), maxsize(vec.maxsize), pdata(nullptr)
{
	if (vec.size)
	{
		size = vec.size;
		maxsize = vec.maxsize;
		pdata = new char*[maxsize];
		for (int i = 0; i < vec.size; i++)
		{
			pdata[i] = new char[strlen(vec.pdata[i]) + 1];
			strcpy_s(pdata[i], strlen(vec.pdata[i]) + 1, vec.pdata[i]);
		}
	}
}

template <typename T>
MyVector<T>::~MyVector<T>()
{
	delete[] pdata;
	pdata = nullptr;
}

template<>
MyVector<char*>::~MyVector<char*>()
{
	for (int i = 0; i < size; i++)
		delete pdata[i];
 	delete[] pdata;
}

template <typename T>
bool MyVector<T>::delete_element(int index)
{
	if (size <= maxsize / 2)
		resize();
	if (index < 0 || index >= size)
		return false;
	T* arr = new T[size - 1];
	for (int i = 0, j = 0; i < size; j++, i++)
	{
		if (pdata[i] != pdata[index])
			arr[j] = pdata[i];
		else --j;
	}
	--size;
	delete pdata;
	pdata = arr;
	return true;
}

template<>
bool MyVector<char*>::delete_element(int index)
{
	if (size <= maxsize / 2)
		resize();
	if (index < 0 || index >= size)
		return false;
	if (size)
	{
		for (int i = index; i < size - 1; i++)
			pdata[i] = pdata[i + 1];
		size--;
		return true;
	}
	return false;
}

template <typename T>
T& MyVector<T>::operator[](int index) const
{
	return pdata[index];
}

template<>
void MyVector<char*>::sort()
{
	int  min = 0;
	if (!size)
		return;
	for (int i = 0; i < size - 1; i++)
	{
		min = i;
		for (int j = i + 1; j < size; j++)
			if (strcmp(pdata[min], pdata[j]) > 0)
				min = j;
		if (min != i)
			std::swap(pdata[i], pdata[min]);
	}
}

template <typename T>
void MyVector<T>::sort()
{
	int  min = 0;
	if (!size)
		return;
	for (int i = 0; i < size - 1; i++)
	{
		min = i;
		for (int j = i + 1; j < size; j++)
			if (pdata[min] > pdata[j])
				min = j;
		if (min != i)
			std::swap(pdata[i], pdata[min]);
	}
}

template<typename T>
int MyVector<T>::find(T obj) const
{
	for (int i = 0; i < size; i++)
		if (pdata[i] == obj)
			return i;
	return -1;
}

template<>
int MyVector<char*>::find(char* str) const
{
	for (int i = 0; i < size; i++)
		if (!strcmp(str, pdata[i]))
			return i;
	return -1;
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(MyVector<T>& obj)
{
	delete pdata;
	pdata = new T[obj.size];
	for (int i = 0; i < obj.size; i++)
		pdata[i] = obj[i];
	maxsize = obj.maxsize;
	size = obj.size;
	return *this;
}

template<>
MyVector<char*>& MyVector<char*>::operator=(MyVector& vec)
{
	for (int i = 0; i < size; i++)
		delete pdata[i];
	delete pdata;
	pdata = new char* [vec.size];
	for (int i = 0; i < vec.size; i++)
	{
		pdata[i] = new char[strlen(vec.pdata[i]) + 1];
		strcpy_s(pdata[i], strlen(vec.pdata[i]) + 1, vec.pdata[i]);
	}
	maxsize = vec.maxsize;
	size = vec.size;
	return *this;
}

template <typename T>
std::ostream& operator <<(std::ostream& out, MyVector<T>& obj)
{
	if (obj.Size())
		for (int i = 0; i < obj.Size(); i++)
			out << obj[i] << "  ";
	else out << "Вектор пуст!\n";
	return out;
}


template<>
void MyVector<char*>::resize()
{
	if (size == maxsize)
		maxsize *= 1.5;
	if (size <= maxsize / 2)
		maxsize /= 1.5;
	if (maxsize < MAX_SIZE)
		maxsize = MAX_SIZE;
	char** temp = new char* [maxsize];
	for (int i = 0; i < size; i++)
		temp[i] = pdata[i];
	delete[] pdata;
	pdata = temp;
}

template <typename T>
void MyVector<T>::resize()
{
	if (size == maxsize)
		maxsize *= 1.5;
	if (size <= maxsize / 2)
		maxsize /= 1.5;
	if (maxsize < MAX_SIZE)
		maxsize = MAX_SIZE;
	T* arr = new T[maxsize];
	for (int i = 0; i < size; i++)
		arr[i] = pdata[i];
	delete[] pdata;
	pdata = arr;
}