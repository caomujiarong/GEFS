
#ifndef UINT
#define UINT unsigned int
#endif

#define SAFE_DELETE(_p) { delete _p; _p = nullptr; }
#define SAFE_DELETE_ARRAY(_p) { delete[] _p; _p = nullptr; }
#define SAFE_FREE_ARRAY(_p) { free(_p); _p = nullptr; }

template<class T>
struct TArray {
    UINT    m_NumElements = 0;
    T*      m_pElements = nullptr;

    TArray() { m_NumElements = 0; m_pElements = nullptr; }

    TArray(UINT count, bool bSetMemZero = false) {
        m_NumElements = count;
        if (count > 0)
        {
            m_pElements = new T[count];
            if (bSetMemZero)
            {
                memset(m_pElements, 0, sizeof(T) * m_NumElements);
            }
        }
    }

    ~TArray() { Clear(); }

    UINT size() { return m_NumElements; }
    
    T& operator[](UINT index) {
        assert(index < m_NumElements);
        return m_pElements[index];
    }

    // Copy constructor (disable - use move)
    TArray(const TArray& arr) = delete;
    // Copy assignment (disable - use move)
    TArray& operator=(const TArray& arr) = delete;

    // Move constructor
    TArray(TArray&& arr) : m_NumElements(arr.m_NumElements), m_pElements(arr.m_pElements) {
        arr.m_NumElements = 0;
        arr.m_pElements = nullptr;
    }

    // Move assignment. Transfer ownership from input arg.
    TArray& operator=(TArray&& arr) {
        // Self-assignment detection
        if (&arr == this) return *this;

        // Release any resource we're holding
        Clear();

        // Transfer ownership of arr.m_ptr to m_ptr
        m_NumElements = arr.m_NumElements;
        m_pElements = arr.m_pElements;
        arr.m_NumElements = 0;
        arr.m_pElements = nullptr;

        return *this;
    }

    // insert/remove functions (also we might just use the generic vector param def and cast to T)
    // Note this does shallow copy only.
    T* Insert(UINT position, UINT count = 1, bool bSetMemZero = false) {
        // clamp position to end of array
        if (position > m_NumElements) {
            position = m_NumElements;
        }

        T* pNewData = new T[m_NumElements + count];
        if (bSetMemZero) {
            memset(pNewData, 0, sizeof(T) * count);
        }

        if (position > 0) {
            // shallow copy elements before insertion
            memcpy(pNewData, m_pElements, sizeof(T) * position);
        }

        if (position < m_NumElements) {
            // shallow copy elements after insertion
            memcpy(pNewData + (position + count), m_pElements + position, sizeof(T) * (m_NumElements - position));
        }

        delete[] (m_pElements);
        m_pElements = pNewData;
        m_NumElements += count;
        return m_pElements + position;
    }

    // Note: this does not work optimally with move constructors/destructors.
    // Use VectorParamDef version for recursive behavior.
    void Remove(UINT position, UINT count = 1) {
        if (count == 0 || position + count > m_NumElements) {
            return;
        }

        T* pNewData = nullptr;
        if (m_NumElements > count) {
            pNewData = new T[(m_NumElements - count)];
        }
        if (position > 0) {
            // shallow copy elements before deleted chunk
            memcpy(pNewData, m_pElements, sizeof(T) * position);
        }
        if (position + count < m_NumElements) {
            // shallow copy elements after deleted chunk
            memcpy(pNewData + position, m_pElements + (position + count), sizeof(T) * (m_NumElements - position - count));
        }

        delete[] (m_pElements);
        m_pElements = pNewData;
        m_NumElements -= count;
    }

    void Clear() {
        SAFE_DELETE_ARRAY(m_pElements);
        m_NumElements = 0;
    }
};