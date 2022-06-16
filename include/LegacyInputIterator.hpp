#pragma once
#include "common.hpp"
#include "LegacyIterator.hpp"

template<typename Iter>
struct LegacyInputIterator
    : public Indirection<LegacyInputIterator<Iter>, Iter>
    , public Increment<LegacyInputIterator<Iter>, Iter>
    , public Assignment<LegacyInputIterator<Iter>, Iter>
    , public MemberAccess<LegacyInputIterator<Iter>, Iter>
    , public Equality<LegacyInputIterator<Iter>, Iter>
{
#ifdef __cpp_lib_concepts
    using iterator_concept = std::input_iterator_tag;
#endif

    typedef typename Iter::difference_type difference_type;
    typedef typename Iter::value_type value_type;
    typedef typename Iter::pointer pointer;
    typedef typename Iter::reference reference;

    typedef std::input_iterator_tag iterator_category;

    LegacyInputIterator() {}

    LegacyInputIterator(const LegacyInputIterator& other)
    : m_iter(other.m_iter)
    {}

    ~LegacyInputIterator() {}

    LegacyInputIterator(pointer ptr) : m_iter(ptr) {}

    LegacyInputIterator& operator=(const pointer ptr)
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
