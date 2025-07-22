#pragma once
/*
* Size
* Push_Back
* Pop_Back
* Insert
* Reserve
* 
*/


template<typename T>
class MKVector
{
public:
	MKVector();

	~MKVector();

	inline const size_t& Size() const{
		return m_size;
	}

	inline T& At(int index);

	void 
	Reserve(size_t capacity) noexcept;

	void Realloc() noexcept;

	void PushBack(const T& newElement);

	void Resize(size_t newSize);

	template<class ...Args>
	void EmplaceBack(Args&&... args);

	inline T& operator[](int index);

private:
	
	inline void Destroy(const T& element);

	size_t m_size{0};				// El número de elementos.
	size_t m_capacity{10};	// La memoria alojada, empieza con 10.
	T* m_data{nullptr};			// Puntero a el bloque de memoria en el heap.
};

//////////////////////////////////////////////////////////////////
//                      Implementaciones
//////////////////////////////////////////////////////////////////

template<typename T>
inline MKVector<T>::MKVector()
{
	Reserve(m_capacity);
}

template<typename T>
inline MKVector<T>::~MKVector() {
	if (m_data)
	{
		delete m_data;
		m_data = nullptr;
	}
}

template<typename T>
inline T& MKVector<T>::At(int index)
{
	return operator[](index);
}

template<typename T>
inline void MKVector<T>::Reserve(size_t numElements) noexcept
{
	m_data = (T*)malloc(numElements * sizeof(T));
	memset(m_data, 0, numElements * sizeof(T));
	m_capacity = numElements;
}

template<typename T>
inline void MKVector<T>::Realloc() noexcept
{
	m_capacity *= 2;

	T* newData = (T*)realloc(m_data, m_capacity * sizeof(T));

	m_data = newData;

}

template<typename T>
inline void MKVector<T>::PushBack(const T& newElement)
{
	if (m_size >= m_capacity)
	{
		Realloc();
	}

	m_data[m_size] = newElement;
	m_size++;
}

//TODO: Terminar esto
template<typename T>
inline void MKVector<T>::Resize(size_t newSize)
{
	
}


template<typename T>
inline T& MKVector<T>::operator[](int index)
{
	if (index < 0 || index >= m_size)
	{
		throw std::out_of_range("Index on MKVector is out of range.");
	}

	return m_data[index];
}

template<typename T>
inline void MKVector<T>::Destroy(const T& element)
{
	element.~T();
}

template<typename T>
template<class ...Args>
inline void MKVector<T>::EmplaceBack(Args && ...args)
{
	
	if (m_size >= m_capacity)
	{
		Realloc();
	}

	m_data[m_size] = T(std::forward<Args>(args)...);
	m_size++;
}
