#ifndef METAL_ITERATOR_H
#define METAL_ITERATOR_H


#include "Parameter.h"


namespace metal
{

    /**
     * @brief Iterator to represent a certain partial derivative in an object.
     *
     * @tparam T Type of the object the iterator refers to
     */
    template< typename T >
    class Iterator
    {

    public:
        /** Alias for record returned by dereferencing the iterator */
        using Record = std::pair< ParameterPtr, typename T::PartialSegment >;

        /** Internal pointer type of the parameter map inside the referred object */
        using Internal = decltype( std::declval< T >().parameterMap().begin() );

        /**
         * @brief Construct a new Iterator object taking a reference
         * to the target object and the internal iterator.
         *
         * @param object Object to refer to
         * @param iter Internal parameter iterator
         */
        Iterator( const T& object, Internal iter )
            : object_{ object }
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
            return ( &object_ == &other.object_ && iter_ == other.iter_ );
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
        Record operator*()
        {
            return std::make_pair(
                iter_->first, object_.partial().segment( iter_->second, iter_->first->dim() ) );
        }

    private:
        /** Referred object */
        const T& object_;

        /** Internal wrapped iterator */
        Internal iter_;
    };

} // metal

#endif // METAL_ITERATOR_H
