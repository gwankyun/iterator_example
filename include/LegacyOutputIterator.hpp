#pragma once
#include "common.hpp"
#include "LegacyIterator.hpp"

// struct LegacyOutput
// {
//     typedef LegacyIterator<T> Iter_t;
//     LegacyOutput(Iter_t ptr) : m_iter(ptr) {}
//     // LegacyOutput(LegacyOutputIterator iter) : m_iter(iter.m_iter) {}
//     ~LegacyOutput() {}
//     template <typename Output>
//     LegacyOutput &operator=(Output output)
//     {
//         // *m_ptr = output;
//         *m_iter = output;
//         return *this;
//     }
//     operator T()
//     {
//         return *m_iter;
//     }
//     // T* m_ptr;
//     Iter_t m_iter;
// };

template<typename T>
struct LegacyOutputIterator
{
    typedef LegacyIterator<T> Iter_t;
#ifdef __cpp_lib_concepts
    using iterator_concept = std::output_iterator_tag;
#endif
    typedef typename Iter_t::difference_type difference_type;
    typedef typename Iter_t::value_type value_type;
    typedef typename Iter_t::pointer pointer;
    typedef typename Iter_t::reference reference;
    typedef std::output_iterator_tag iterator_category;

    LegacyOutputIterator() {}

    LegacyOutputIterator(const LegacyOutputIterator& other)
    : m_iter(other.m_iter)
    {}
    
    LegacyOutputIterator& operator=(const LegacyOutputIterator& other)
    {
        if (this != &other)
        {
            m_iter = other.m_iter;
        }
        return *this;
    }

    ~LegacyOutputIterator() {}

    reference operator*()
    {
        return *m_iter;
    }

    LegacyOutputIterator& operator++()
    {
        m_iter++;
        return *this;
    }

    LegacyOutputIterator operator++(int)
    {
        LegacyOutputIterator temp = *this;
        ++(*this);
        return temp;
    }

    LegacyOutputIterator(T* ptr) : m_iter(ptr) {}

    LegacyOutputIterator& operator=(const T* ptr)
    {
        m_iter = ptr;
        return *this;
    }

private:
    Iter_t m_iter;
};

