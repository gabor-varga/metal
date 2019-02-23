#ifndef METAL_SCALARBASE_H
#define METAL_SCALARBASE_H


#include "Iterator.h"
#include <exception>
#include <iostream>


namespace metal
{

    /**
     * @brief Base class for the expression template (ET) design pattern of scalar differential
     * algebra system.
     *
     * All classes that take part in the ET system inherits from this class with
     * themselves as the template argument. Provides the interface that ET classes has to implement.
     *
     * @tparam Expr Type of the derived ET class
     */
    template< typename Expr >
    class ScalarBase
    {

    public:
        /**
         * @brief Returns the value of the expression.
         *
         * @return double Scalar value
         */
        double value() const
        {
            return static_cast< const Expr& >( *this ).value();
        }

        /**
         * @brief Returns the partial derivative vector of the expression, as stored inside the
         * derived class.
         *
         * There is no information returned on the assembly or order of stored parameters. The order
         * and dimension of the derivatives can be retrieved using the \ref parameterMap method.
         *
         * @return auto Partial derivative vector
         *
         * @see dim
         */
        auto partial() const
        {
            return static_cast< const Expr& >( *this ).partial();
        }

        /**
         * @brief Returns the associative mapping between parameters and the position/dimension they
         * are stored in the derivative vector.
         *
         * The values of the map store the starting id and the span of the parameter in the
         * derivative vector.
         *
         * @return auto Parameter map to decode partial vector
         *
         * @see size
         * @see parameters
         */
        auto parameterMap() const
        {
            return static_cast< const Expr& >( *this ).parameterMap();
        }

        /**
         * @brief Returns the dimension of the partial derivative vector returned by \ref partial.
         *
         * @return size_t Size of the derivative vector
         *
         * @see partial
         */
        size_t dim() const
        {
            return static_cast< const Expr& >( *this ).dim();
        }

        /**
         * @brief Returns the number of parameters stored and returned by the \ref parameters
         * method.
         *
         * @return size_t Number of parameters associated with the derivatives
         *
         * @see parameterMap
         * @see parameters
         */
        size_t size() const
        {
            return static_cast< const Expr& >( *this ).size();
        }

        /**
         * @brief Returns the vector of parameters that take part in the partial computation.
         * Essentially returns the keys of the map given by \ref parameterMap.
         *
         * @return ParameterPtrVector Vector of parameters in partial computation
         *
         * @see parameterMap
         * @see size
         */
        ParameterPtrVector parameters() const
        {
            return static_cast< const Expr& >( *this ).parameters();
        }

        /**
         * @brief Returns an iterator pointing to the beginning of the partial derivatives iterable.
         *
         * This is not the same iterator as one would use with the map returend by \ref parameterMap
         * method. It directly associates the parameters with the segment of the partial derivative
         * vector they refer to.
         *
         * @return Iterator< Expr > Iterator pointing to the beginning of the iterable partials
         *
         * @see end
         * @see at
         */
        Iterator< Expr > begin() const
        {
            return static_cast< const Expr& >( *this ).begin();
        }

        /**
         * @brief Returns an iterator pointing to the beginning of the partial derivatives iterable.
         *
         * This is not the same iterator as one would use with the map returend by \ref parameterMap
         * method. It directly associates the parameters with the segment of the partial derivative
         * vector they refer to.
         *
         * @return Iterator< Expr > Iterator pointing to the beginning of the iterable partials

         * @see begin
         * @see at
         */
        Iterator< Expr > end() const
        {
            return static_cast< const Expr& >( *this ).end();
        }

        /**
         * @brief Returns the part of the partial derivative vector that refers to the specified
         * parameter.
         *
         * @throws std::runtime_error
         *
         * @param p Parameter to get partial derivative of
         * @return auto Partial derivative vector
         */
        auto at( const ParameterPtr& p ) const
        {
            if ( parameterMap().count( p ) == 0 )
            {
                throw std::runtime_error(
                    "Error! Parameter not present in partials: '" + p->name() + "'" );
            }

            const auto& record = parameterMap().at( p );
            return partial().segment( record.first, record.second );
        }
    };


    /**
     * @brief Generic output stream function for any \ref ScalarBase types.
     *
     * @tparam Expr Type of the expression to be printed
     * @param os Output stream to print to
     * @param scalar Expression to be printed
     * @return std::ostream& Modified output stream
     */
    template< typename Expr >
    std::ostream& operator<<( std::ostream& os, const ScalarBase< Expr >& scalar )
    {
        os << scalar.value();
        os << " ( ";
        for ( const auto& entry : scalar )
        {
            os << entry.first->name() << ": " << entry.second << " ";
        }
        os << ")";
        return os;
    }

} // metal

#endif // METAL_SCALARBASE_H
