#ifndef METAL_UNARYMATHOP_H
#define METAL_UNARYMATHOP_H


#include "ScalarUnaryOp.h"
#include <cmath>


namespace metal
{

/**
 * @brief Unary operation taken by \ref ScalarUnaryOp object to define the expression for
 * computing the square of an expression.
 */
struct SquareOp
{
    /**
     * @brief Applies the transformation on the value of an expression.
     *
     * @param value Value of the expression
     * @return double Transformed value
     */
    double applyToValue( double value ) const
    {
        return value * value;
    }

    /**
     * @brief Computes the partial derivative of the unary operation.
     *
     * @return double Partial
     */
    double partial( double value ) const
    {
        return 2 * value;
    }
};


/**
 * @brief Sine function that takes an expression and creates a new expression with applied
 * transformation.
 *
 * @tparam Expr Type of the expression
 * @param expr Expression to apply square to
 * @return ScalarUnaryOp< Expr, SquareOp > Expression that represents the square
 */
template< typename Expr >
ScalarUnaryOp< Expr, SquareOp > sqr( const ScalarBase< Expr >& expr )
{
    return ScalarUnaryOp< Expr, SquareOp >(
        static_cast< const Expr& >( expr ), SquareOp{} );
}

} // metal

#endif // METAL_UNARYMATHOP_H
