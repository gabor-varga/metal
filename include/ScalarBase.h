#ifndef METAL_SCALARBASE_H
#define METAL_SCALARBASE_H


#include "Parameter.h"
#include <exception>
#include <iomanip>
#include <iostream>

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Weverything"
#include <Eigen/Core>
#pragma clang diagnostic pop
#elif defined __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <Eigen/Core>
#pragma GCC diagnostic pop
#else
#include <Eigen/Core>
#endif


namespace metal
{

/* Alias for eigen row vector */
using EigenRowVector = Eigen::Matrix< double, 1, -1 >;

/* Alias for eigen row vector segment */
using EigenRowVectorSegment = Eigen::VectorBlock< EigenRowVector, -1 >;

/* Alias for eigen row vector const segment */
using EigenRowVectorConstSegment = Eigen::VectorBlock< const EigenRowVector, -1 >;


/**
 * @brief Type trait for the partial type of a specific ET class
 *
 * @tparam Expr Type of the specific ET class
 */
template< typename Expr >
struct Partial
{
    /** Alias for internal type */
    using Type = EigenRowVector;
};

/**
 * @brief Type trait for the partial segment type of a specific ET class
 *
 * @tparam Expr Type of the specific ET class
 */
template< typename Expr >
struct PartialSegment
{
    /** Alias for internal type */
    using Type = EigenRowVectorConstSegment;
};


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
    /** Alias for partial segment returned by \ref at method */
    using PartialSegmentType = typename PartialSegment< Expr >::Type;

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
     * @brief Returns the dimension of the partial derivative vector.
     *
     * @return size_t Size of the derivative vector
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
     * @see parameters
     */
    size_t size() const
    {
        return static_cast< const Expr& >( *this ).size();
    }

    /**
     * @brief Returns the vector of parameters that take part in the partial computation.
     *
     * @return ParameterPtrVector Vector of parameters in partial computation
     *
     * @see size
     */
    ParameterPtrVector parameters() const
    {
        return static_cast< const Expr& >( *this ).parameters();
    }

    /**
     * @brief Checks for exitance of a parameter in the expression.
     *
     * @param p Parameter to check existance of
     * @return true Expression contains partial w.r.t. the parameter
     * @return false Expression does not contains partial w.r.t. the parameter
     *
     * @see at
     */
    bool contains( const ParameterPtr& p ) const
    {
        return static_cast< const Expr& >( *this ).contains( p );
    }

    /**
     * @brief Returns the part of the partial derivative vector that refers to the specified
     * parameter.
     *
     * @throws std::runtime_error
     *
     * @param p Parameter to get partial derivative of
     * @return PartialSegmentType Partial derivative vector
     *
     * @see contains
     */
    PartialSegmentType at( const ParameterPtr& p ) const
    {
        return static_cast< const Expr& >( *this ).at( p );
    }

    /**
     * @brief Accumulates the target partial vector with the partial vector information coming from
     * the expression.
     *
     * @param partial Target partial vector segment
     * @param scalar Partial multiplier
     * @param p Parameter to add information of
     */
    void accum( EigenRowVectorSegment& partial, double scalar, const ParameterPtr& p ) const
    {
        static_cast< const Expr& >( *this ).accum( partial, scalar, p );
    }
};


namespace detail
{

    inline void printHeader( std::ostream& os, const ParameterPtrVector& params, int precision )
    {
        const int minWidth = precision + 8;

        os << std::setw( minWidth ) << "Value";
        for ( const auto& p : params )
        {
            const auto& name = p->name();
            const int pad = p->dim() == 1 ? 1 : 4;
            const int width = std::max( minWidth, static_cast< int >( name.size() ) + pad );

            os << " |";
            if ( p->dim() == 1 )
            {
                os << std::setw( width ) << name;
            }
            else
            {
                for ( int k = 0; k < p->dim(); k++ )
                {
                    const std::string nameWithIndex = name + "[" + std::to_string( k ) + "]";
                    os << std::setw( width ) << nameWithIndex;
                }
            }
        }
        os << std::endl;
    }

    template< typename Expr >
    void printValue( std::ostream& os, const ScalarBase< Expr >& expr, int precision )
    {
        const int minWidth = precision + 8;

        os << std::setw( minWidth ) << std::scientific << std::setprecision( precision )
           << expr.value();
        for ( const auto& p : expr.parameters() )
        {
            const int pad = p->dim() == 1 ? 1 : 4;
            const int width = std::max( minWidth, static_cast< int >( p->name().size() ) + pad );

            if ( expr.contains( p ) )
            {
                const auto partial = expr.at( p );
                os << " |";
                for ( int j = 0; j < partial.size(); j++ )
                    os << std::setw( width ) << std::scientific << std::setprecision( precision )
                       << partial[j];
            }
            else
            {
                os << " |";
                os << std::scientific << std::setprecision( precision )
                   << std::setw( width * p->dim() ) << "";
            }
        }
        os << std::endl;
    }

} // detail


/**
 * @brief Generic output stream function for any \ref ScalarBase types.
 *
 * @tparam Expr Type of the expression to be printed
 * @param os Output stream to print to
 * @param expr Expression to print
 * @return std::ostream& Modified output stream
 */
template< typename Expr >
std::ostream& operator<<( std::ostream& os, const ScalarBase< Expr >& expr )
{
    const int prec = static_cast< int >( os.precision() );
    detail::printHeader( os, expr.parameters(), prec );
    detail::printValue( os, expr, prec );
    return os;
}

} // metal

#endif // METAL_SCALARBASE_H
