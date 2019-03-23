#ifndef METAL_UNARYMATHOP_H
#define METAL_UNARYMATHOP_H


#include "ScalarUnaryOp.h"
// #include <math.h>


namespace metal
{

/**
 * @brief Unary operation taken by \ref ScalarUnaryOp object to define the expression for
 * computing the sine of an expression.
 *
 * @tparam Expr Type of expression to compute sine of
 */
template< typename Expr >
struct SineOp
{
    /** Alias for partial type of the input expression */
    using Input = typename Expr::Partial;

    /** Alias for the output partial expression type */
    using Output = decltype( std::declval< Input >().operator*( double{} ) );


    /**
     * @brief Applies the transformation on the value of an expression.
     *
     * @param value Value of the expression
     * @return double Transformed value
     */
    double applyToValue( double value ) const
    {
        return sin( value );
    }

    /**
     * @brief Applies the transformation on the partial of an expression.
     *
     * @param value Value of the expression
     * @param partial Partial of the expression
     * @return Output Transformed partial
     */
    Output applyToPartial( double value, const Input& partial ) const
    {
        return partial * cos( value );
    }
};


/**
 * @brief Sine function that takes an expression and creates a new expression with applied
 * transformation.
 *
 * @tparam Expr Type of the expression
 * @param expr Expression to apply sine to
 * @return ScalarUnaryOp< Expr, SineOp< Expr > > Expression that represents the
 * sine operation
 */
template< typename Expr >
ScalarUnaryOp< Expr, SineOp< Expr > > sin( const ScalarBase< Expr >& expr )
{
    return ScalarUnaryOp< Expr, SineOp< Expr > >(
        static_cast< const Expr& >( expr ), SineOp< Expr >() );
}

} // metal

#endif // METAL_UNARYMATHOP_H
