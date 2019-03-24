#ifndef METAL_ITERATOR_H
#define METAL_ITERATOR_H


#include "Parameter.h"


namespace metal
{

template< typename Expr >
struct ImplementsParameterVector
{
    static const bool Value = true;
    using Type = ParameterPtrVector::const_iterator;
};


/**
 * @brief Iterator to represent a certain partial derivative in an expression.
 *
 * @tparam Expr Type of the expression the iterator refers to
 */
template< typename Expr >
class Iterator
{

public:
    /** Alias for record returned by dereferencing the iterator */
    using Record = std::pair< ParameterPtr, typename Expr::PartialSegment >;

    /** Internal pointer type of the record inside the referred expression */
    using Internal = typename ImplementsParameterVector< Expr >::Type;


    /**
     * @brief Construct a new Iterator object taking a reference
     * to the target object and the internal iterator.
     *
     * @param expr Object to refer to
     * @param iter Internal parameter iterator
     */
    Iterator( const Expr& expr, Internal iter )
        : expr_{ expr }
        , iter_{ iter }
    {
    }

    /**
     * @brief Equality comparison operator between iterators.
     *
     * @param other Other iterator object to compare with
     * @return true If this and the other iterator are equal
     * @return false If this and the other iterator are not equal
     */
    bool operator==( const Iterator& other )
    {
        return ( &expr_ == &other.expr_ && iter_ == other.iter_ );
    }

    /**
     * @brief Inequality comparison operator between iterators.
     *
     * @param other Other iterator object to compare with
     * @return true If this and the other iterator are not equal
     * @return false If this and the other iterator are equal
     */
    bool operator!=( const Iterator& other )
    {
        return !( *this == other );
    }

    /**
     * @brief Iterator increment (next) operator.
     *
     * @return Iterator& Reference to this incremented operator
     */
    Iterator& operator++()
    {
        ++iter_;
        return *this;
    }

    /**
     * @brief Dereferencing operator that returns the refered partial item.
     *
     * @return Record Composite of the parameter and partial derivative value
     */
    template< bool T = ImplementsParameterVector< Expr >::Value >
    typename std::enable_if< T, Record >::type operator*()
    {
        return std::make_pair( iter_, expr_.at( *iter_ ) );
    }

    /**
     * @brief Dereferencing operator that returns the refered partial item.
     *
     * @return Record Composite of the parameter and partial derivative value
     */
    template< bool T = ImplementsParameterVector< Expr >::Value >
    typename std::enable_if< !T, Record >::type operator*()
    {
        return std::make_pair( iter_->first, expr_.at( iter_->first ) );
    }

private:
    /** Referred object */
    const Expr& expr_;

    /** Internal wrapped iterator */
    Internal iter_;
};

} // metal

#endif // METAL_ITERATOR_H
