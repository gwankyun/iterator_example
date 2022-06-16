#pragma once
#include "common.hpp"

template<typename Iter>
struct LegacyIterator
    : public Indirection<LegacyIterator<Iter>, Iter>
    , public Increment<LegacyIterator<Iter>, Iter>
    , public Assignment<LegacyIterator<Iter>, Iter>
{
    typedef typename Iter::difference_type difference_type;
    typedef typename Iter::value_type value_type;
    typedef typename Iter::pointer pointer;
    typedef typename Iter::reference reference;

    typedef std::input_iterator_tag iterator_category;

    LegacyIterator() : m_iter(NULLPTR) {}

    LegacyIterator(const LegacyIterator& other) : m_iter(other.m_iter) {}

    ~LegacyIterator() {}

    LegacyIterator(pointer ptr) : m_iter(ptr) {}

    LegacyIterator& operator=(const pointer ptr)
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
