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
  
  //Size
  inline const size_t Size() const;
  
  inline const size_t Capacity() const;
  
  inline const bool Empty() const;
  
  //Element Access
	inline const T& At(int index) const;
  
  inline const T& operator[](int index) const;
  
  inline const T& Front() const;
  
  inline const T& Back() const;

  inline const T* Data() const noexcept;
  
  //Operations
	void Reserve(size_t capacity) noexcept;

	void Realloc() noexcept;

	void PushBack(const T& newElement);

  void PopBack();

	void Resize(size_t newSize); //Needs tuning

	template<class ...Args>
	void EmplaceBack(Args&&... args);

private:

	size_t m_size{0};				// El número de elementos.
	size_t m_capacity{8};	// La memoria alojada, empieza con 10.
	T* m_data{nullptr};			// Puntero a el bloque de memoria en el heap.
};

//------------------------------------------------------------
//                      Implementaciones
//------------------------------------------------------------

//Construct/Distruct
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

//--------------------Size------------------------------
template<typename T>
inline const size_t MKVector<T>::Size() const
{
  return m_size;
}

template<typename T>
inline const size_t MKVector<T>::Capacity() const
{
  return m_capacity;
}

template<typename T>
inline const bool MKVector<T>::Empty() const
{
  return (m_size == 0) ? true : false;
}


//--------------------Element Access------------------------------
template<typename T>
inline const T& MKVector<T>::At(int index) const
{
	return operator[](index);
}

template<typename T>
inline const T& MKVector<T>::operator[](int index) const
{
  if (index < 0 || index >= m_size)
  {
    throw std::out_of_range("Index on MKVector is out of range.");
  }

  return m_data[index];
}

template<typename T>
inline const T& MKVector<T>::Front() const
{
  return m_data[0];
}

template<typename T>
inline const T& MKVector<T>::Back() const
{
  return m_data[m_size - 1];
}

template<typename T>
inline const T* MKVector<T>::Data() const noexcept
{
  return &m_data;
}


//------------------------------Operations--------------------
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
  if(m_size == m_capacity) return;
  
  // 8 size & 8 cap -> 9 size || 8 cap & 9 size
  if(m_size > m_capacity)
  {
    m_capacity *= 2; // -> x2
    
    T* newData = (T*)realloc(m_data, m_capacity * sizeof(T));

    m_data = newData;
  }
  
  // 16 cap & 8 size -> 7 size || 8 cap & 7 size
  if (m_size - 1 < m_capacity / 2) {
    
    m_capacity /= 2; // -> /2

    T* newData = (T*)realloc(m_data, m_capacity * sizeof(T));

    m_data = newData;
  }

}

template<typename T>
inline void MKVector<T>::PushBack(const T& newElement)
{
  m_size++;
  Realloc();
  m_data[m_size -1] = newElement;
}


//16 elements before -> 15 elements later
template <typename T>
inline void MKVector<T>::PopBack()
{
  m_size--;
  Realloc();
  m_data[m_size].~T();
  
}

/* Situaciones
*  - newSize > capacity
*  - newSize < m_capacity
*  -   
*/

template<typename T>
inline void MKVector<T>::Resize(size_t newSize)
{
  if(newSize == m_size) return;
  
  //Si 5 < 10 -> todos los posteriores se destruyen
  if (newSize < m_size)
  {
    for (size_t i = m_size; i > newSize; --i)
    {
      PopBack();
    }
  }
  
  if(newSize > m_size)
  {
    for (size_t i = m_size; i < newSize; ++i) {
      PushBack(T());
    }
  }
}

template<typename T>
template<class ...Args>
inline void MKVector<T>::EmplaceBack(Args && ...args)
{
  m_size++;
  Realloc();
	m_data[m_size - 1] = T(std::forward<Args>(args)...);
}
