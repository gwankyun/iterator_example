#pragma once
#include <cstddef> // std::size_t std::ptrdiff_t
#include <iterator> // std::input_iterator_tag

#ifndef NULLPTR
#  define NULLPTR nullptr
#endif

template<typename D, typename T>
struct Indirection
{
    //typedef typename T::reference reference;

    typename T::reference operator*()
    {
        return T::indirection(as_derived().get());
    }

    typename T::reference operator*() const
    {
        return T::indirection(as_derived().get());
    }

    D& as_derived()
    {
        return static_cast<D&>(*this);
    }

    const D& as_derived() const
    {
        return static_cast<const D&>(*this);
    }
};

template<typename D, typename T>
struct Increment
{
    D& operator++()
    {
        static_assert(std::is_same_v<D&, decltype(as_derived())>);
        T::prefix_increment(as_derived().get());
        return as_derived();
    }

    const D& operator++() const
    {
        T::prefix_increment(as_derived().get());
        return as_derived();
    }

    D operator++(int)
    {
        D temp = as_derived();
        T::prefix_increment(as_derived().get());
        return temp;
    }

    D& as_derived()
    {
        return static_cast<D&>(*this);
    }

    const D& as_derived() const
    {
        return static_cast<const D&>(*this);
    }
};

template<typename D, typename T>
struct Decrement
{
    D& operator--()
    {
        static_assert(std::is_same_v<D&, decltype(as_derived())>);
        T::prefix_decrement(as_derived().get());
        return as_derived();
    }

    const D& operator--() const
    {
        T::prefix_decrement(as_derived().get());
        return as_derived();
    }

    D operator--(int)
    {
        D temp = as_derived();
        T::prefix_decrement(as_derived().get());
        return temp;
    }

    D& as_derived()
    {
        return static_cast<D&>(*this);
    }

    const D& as_derived() const
    {
        return static_cast<const D&>(*this);
    }
};

//template<typename D, typename T>
//struct Subscript
//{
//    typedef typename T::reference reference;
//    typedef typename T::difference_type difference_type;
//
//    reference operator[](difference_type n)
//    {
//        return Iter::subscript(m_iter, n);
//    }
//
//    reference operator[](difference_type n) const
//    {
//        return Iter::subscript(m_iter, n);
//    }
//
//    D& as_derived()
//    {
//        return static_cast<D&>(*this);
//    }
//
//    const D& as_derived() const
//    {
//        return static_cast<const D&>(*this);
//    }
//};

