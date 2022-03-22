#pragma once
#ifndef vector_h
#define vector_h

#include <iterator>
#include <limits>
#include <stdexcept>

template<class T>
class Vector {
public:
	typedef T data_type;
	typedef size_t size_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef std::ptrdiff_t difference_type;
    Vector() : 
        m_size(0), 
        m_capacity(0) {
        *m_data = new T[m_capacity];
    }
    Vector(size_type count, const T& value = T()) : m_size(count), m_capacity(calculateGrowth(count)) {
        *m_data = new T[m_capacity];
        std::fill_n(m_data, count, value);
    }
    Vector(iterator first, iterator last) {
        m_size = last - first;
        m_capacity = last - first;
        *m_data = new T[m_capacity];
        std::copy(first, last, m_data);
    }
    Vector(std::initializer_list<T> init) {
        m_size = init.size();
        m_capacity = calculateGrowth(m_size);
        *m_data = new T[m_capacity];
        std::copy(init.begin(), init.end(), m_data);
    }
    size_type max_size() const {
        return std::numeric_limits<size_type>::max();
    }

    size_type capacity() const {
        return m_capacity;
    }

    size_type size() const {
        return m_size;
    }
       
    ~Vector() {
        if (m_data != nullptr) {
            for (size_type i = 0; i < size(); i++) delete &m_data[i];
            delete[] &m_data;
            m_data = nullptr;
        }
    }
    T& at(size_type pos) {
        if (pos < size() && pos >= 0) return m_data[pos];
        throw std::out_of_range("position is out of range");
    }

    const T& at(size_type pos) const {
        if (pos < size() && pos >= 0) return m_data[pos];
        throw std::out_of_range("position is out of range");
    }
    iterator begin() noexcept { return m_data; }
    const_iterator begin() const noexcept { return m_data; }
    const_iterator cbegin() const noexcept { return begin(); }
    iterator end() noexcept { return begin() + m_size; }
    const_iterator end() const noexcept { return begin() + m_size;}
    const_iterator cend() const noexcept { return end(); }
    reverse_iterator rbegin() noexcept { return reverse_iterator(m_data + m_size); }
    const_reverse_iterator rbegin() const noexcept {
        return rbegin();
    }
    reverse_iterator rend() noexcept {return reverse_iterator(m_data);}
    const_reverse_iterator rend() const noexcept {return rend();}
    T& operator[](size_type pos) {return m_data[pos];}

    const T& operator[](size_type pos) const {return m_data[pos];}

    T& front() {return m_data[0];}
    const T& front() const {return m_data[0];}
    T& back() {return m_data[size() - 1];}
    const T& back() const {return m_data[size() - 1];}
    const T* data() const noexcept {return m_data;}
    bool empty() const {
        return size() == 0;
    }
    void push_back(const T& item) {
        if (size() >= capacity()) {
            reallocate(capacity() + 1);
        }
        m_data[m_size] = item;
        m_size++;
    }
    void pop_back() {
        delete (end() - 1);
        --m_size;
    }

    iterator insert(const_iterator pos, const T& value) {
        return insert(pos, 1, value);
    }

    iterator insert(const_iterator pos, T&& value) {
        difference_type index = pos - begin();

        if (index < 0 || index > size()) {
            throw new std::out_of_range("Insert index is out of range");
        }
        if (size() == capacity()) reallocate(capacity() + 1);
        iterator it = &m_data[index];
        std::move(it, end(), it + 1);
        *it = std::move(value);
        m_size++;
        return it;
    }

    iterator insert(const_iterator pos, size_type count, const T& value) {
        const difference_type index = pos - begin();

        if (index < 0 || index > size()) {
            throw new std::out_of_range("Insert index is out of range");
        }

        if (size() + count > capacity()) {
            reallocate(capacity() + count);
        }

        iterator it = &m_data[index];

        std::move(it, end(), it + count);
        std::fill_n(it, count, value);

        m_size += count;

        return it;
    }

    iterator insert(const_iterator pos, iterator first, iterator last) {
        const difference_type count = last - first;
        const difference_type index = pos - begin();

        if (size() + count > capacity()) {
            reallocate(capacity() + count);
        }

        iterator it = &m_data[index];
        std::move(it, end(), it + count);
        std::copy(first, last, it);

        m_size += count;

        return it;
    }

    iterator insert(const_iterator pos, std::initializer_list<T> ilist) {
        const difference_type count = ilist.size();
        const difference_type index = pos - begin();

        if (size() + count > capacity()) {
            reallocate(capacity() + count);
        }

        iterator it = &m_data[index];
        std::move(it, end(), it + count);
        std::copy(ilist.begin(), ilist.end(), it);

        m_size += count;

        return it;
    }
    void clear() {
        for (size_type i = 0; i < size(); i++)
            delete data() + i;
        m_size = 0;
    }
    void reserve(size_type ncap) {
        if (ncap > max_size())
            throw new std::length_error("capacity cannot be larger than max size");
        if (ncap > capacity())
            reallocate(capacity() + ncap);
        m_capacity = ncap;
    }
    iterator erase(const_iterator pos) {
        const difference_type index = pos - begin();
        delete &m_data[index];
        for (auto i = index; i < size() - 1; i++) {
            &m_data[i] = &m_data[i + 1]; 
            delete &m_data[i + 1];
        }
        m_size--;
        iterator it = &m_data[index];
        return it;
    }

    //insult: https://stackoverflow.com/questions/39414610/why-are-are-stdallocators-construct-and-destroy-functions-deprecated-in-c17
    /*
    iterator erase(const_iterator pos) {
        const difference_type index = pos - begin();
        _allocator.destroy(&_data[index]);

        for (auto i = index; i < size() - 1; i++) {
            _allocator.destroy(&_data[i + 1]);
            _allocator.construct(&_data[i], m_data[i + 1]);
        }

        _size--;
        iterator it = &_data[index];

        return it;
    }

    iterator erase(const_iterator first, const_iterator last) {
        const difference_type startIndex = first - begin();
        const difference_type endIndex = last - begin();

        for (difference_type i = 0; i < endIndex - startIndex; i++) {
            _allocator.destroy(&_data[startIndex + i]);
            _allocator.construct(&_data[startIndex + i], _data[endIndex + i]);
        }

        _size -= endIndex - startIndex;
        iterator it = &_data[startIndex];

        return it;
    }*/
    template <typename... Args>
    void emplace_back(Args&&... args) {
        if (m_size >= m + m_capacity)
            reallocate(m_capacity + m_capacity / 2);
        new(&m_data[m_size]) T(std::forward<Args>(args)...);
        return m_data[m_size++];
    }
private:
    size_type m_size = 0;
    size_type m_capacity = 0;
    T* m_data;

    size_type calculateGrowth(size_type newSize) const {
        if (capacity() > max_size() - capacity() / 2) return newSize;
        const size_type geometric = capacity() * 1.5;
        if (geometric < newSize) return newSize;
        return geometric;
    }

    void reallocate(size_type minSize) {
        const size_type newCapacity = calculateGrowth(minSize);
        T* newData = new T[newCapacity];
        for (size_type i = 0; i < m_size; i++) newData[i] = m_data[i];
        delete [] &m_data;
        m_data = newData;
        m_capacity = newCapacity;
    }
};

#endif // !vector_h

template< class T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs) {
    if (lhs.size() != rhs.size()) return false;
    for (int i = 0; i < lhs.size(); i++)
        if (lhs.at(i) != rhs.at(i)) return false;
    return true;
}
template< class T>
bool operator!=(const const Vector<T> lhs, const Vector<T>& rhs) {
    return !(lhs == rhs);
}
template< class T>
bool operator<(const Vector<T>& lhs, const Vector<T>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template< class T>
bool operator>(const Vector<T>& lhs, const Vector<T>& rhs) {
    return rhs < lhs;
}

template< class T, class Alloc>
bool operator<=(const Vector<T>& lhs, const Vector<T>& rhs) {
    return !(rhs < lhs);
}

template< class T>
bool operator>=(const Vector<T>& lhs, const Vector<T>& rhs) {
    return !(lhs < rhs);
}