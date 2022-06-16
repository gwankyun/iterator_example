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

template<typename Iter>
struct LegacyOutputIterator
    : public Indirection<LegacyOutputIterator<Iter>, Iter>
    , public Increment<LegacyOutputIterator<Iter>, Iter>
    , public MemberAccess<LegacyOutputIterator<Iter>, Iter>
{
#ifdef __cpp_lib_concepts
    using iterator_concept = std::output_iterator_tag;
#endif
    typedef typename Iter::difference_type difference_type;
    typedef typename Iter::value_type value_type;
    typedef typename Iter::pointer pointer;
    typedef typename Iter::reference reference;

    typedef std::output_iterator_tag iterator_category;

    LegacyOutputIterator() {}

    LegacyOutputIterator(const LegacyOutputIterator& other)
    : m_iter(other.m_iter)
    {}

    ~LegacyOutputIterator() {}

    LegacyOutputIterator(pointer ptr) : m_iter(ptr) {}

    LegacyOutputIterator& operator=(const pointer ptr)
    {
        m_iter = ptr;
        return *this;
    }

    pointer& get()
    {
        return m_iter;
    }

    const pointer& get() const
    {
        return m_iter;
    }

private:
    pointer m_iter;
};
