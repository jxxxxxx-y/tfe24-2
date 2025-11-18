#ifndef MY_VECTOR_HPP
#define MY_VECTOR_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fmt/format.h>
// Template class myVector

// !!!! size is equal to size of vector, capacity are the free places

template <typename T>
class myvector {

public:
    
    myvector() noexcept{
        int m_count = 0;
        m_arr = new T[m_count];
        m_size = 0;
        m_capacity = m_count;
        m_space = m_count;
        
    }

    explicit myvector(size_t count){
        m_arr = new T[count];
        m_size = 0;
        m_capacity = count;
        m_space = count;
        }

    myvector(const myvector &other){



    }

    ~myvector(){
        delete[] m_arr;
        m_arr = nullptr;
        m_size = 0;
        m_capacity = 0;
    }

    void status() const noexcept{
        fmt::println("size: {}, capacity: {}", m_size, m_capacity);
        fmt::println(" ");
    }

    int  size() const noexcept{
        fmt::println("size: {}", m_size);
        fmt::println(" ");
        return m_size;
    }

    int capacity() const noexcept{
        fmt::println("capacity: {}", m_capacity);
        fmt::println(" ");
        return m_capacity;
    }

    void push_back(const T& value){
        if (m_space == 0){
            fmt::println("Vector is full, double vector size.");
            if(m_capacity == 0){
                m_capacity = 1;
            }
            size_t temp_new_capacity = m_capacity * 2;
            size_t temp_new_size = temp_new_capacity - (m_capacity - m_space);
            size_t temp_new_space = temp_new_capacity - temp_new_size;

            // copy member from old to new m_arr
            T* m_arr_new = new T[temp_new_capacity];
            for (size_t i = 0; i < m_capacity; i++){
                m_arr_new[i] = m_arr[i];
                }
            delete[] m_arr;

            // update member variable
            m_arr = m_arr_new;
            m_size = temp_new_size;
            m_capacity = temp_new_capacity;
            m_space = temp_new_space;

            // pushback value
            //fmt::println("push back of new value.\n");
            size_t position = m_capacity - m_space;
            m_arr[position] = value;
            m_size ++;
            m_space --;
        }
        else {
            size_t position = m_capacity - m_space;
            m_arr[position] = value;
            m_size ++;
            m_space --;
        }
        
    }

    /*
    const T& at(size_t index) const{
        return m_arr[index];
    }
    */

    T resize(size_t new_capacity){
        
        size_t temp_new_size = m_size;

        // copy member from old to new m_arr
        T* m_arr_new = new T[new_capacity];
        for (size_t j = 0; j < new_capacity; j++){
            m_arr_new[j] =  0;
        }
        for (size_t i = 0; i < m_capacity; i++){
            m_arr_new[i] = m_arr[i];
            }
        delete[] m_arr;

        // update member variable
        m_arr = m_arr_new;
        m_capacity = new_capacity;
        m_size = temp_new_size;
        return m_capacity;
    }
    T value_at(size_t index){
        fmt::println("Value at index {}: {}", index, m_arr[index]);
        return m_arr[index];
    }

    void clear() noexcept{
        delete[] m_arr;
        m_arr = nullptr;
        m_size = 0;
        m_capacity = 0;
    }

    T* m_arr;
    size_t m_size;
    size_t m_capacity;
    size_t m_space;
};
#endif // MY_VECTOR_HPP