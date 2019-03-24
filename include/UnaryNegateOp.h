#ifndef METAL_UNARYNEGATEOP_H
#define METAL_UNARYNEGATEOP_H


#include "ScalarUnaryOp.h"


namespace metal
{

/**
 * @brief Unary operation taken by \ref ScalarUnaryOp object to define the expression for
 * computing the negation of an expression.
 *
 * @tparam Expr Type of expression to compute negation of
 */
template< typename Expr >
struct NegateOp
{
    /** Alias for partial type of the input expression */
    using Input = typename Partial< Expr >::Type;

    /** Alias for the output partial expression type */
    using Output = decltype( -std::declval< Input >() );


    /**
     * @brief Applies the transformation on the value of an expression.
     *
     * @param value Value of the expression
     * @return double Transformed value
     */
    double applyToValue( double value ) const
    {
        return -value;
    }

    /**
     * @brief Applies the transformation on the partial of an expression.
     *
     * @param partial Partial of the expression
     * @return Output Transformed partial
     */
    Output applyToPartial( double, const Input& partial ) const
    {
        return -partial;
    }
};


/**
 * @brief Negate function that takes an expression and creates a new expression with applied
 * transformation.
 *
 * @tparam Expr Type of the expression
 * @param expr Expression to apply negation to
 * @return ScalarUnaryOp< Expr, NegateOp< Expr > > Expression that represents the
 * sine operation
 */
template< typename Expr >
ScalarUnaryOp< Expr, NegateOp< Expr > > operator-( const ScalarBase< Expr >& expr )
{
    return ScalarUnaryOp< Expr, NegateOp< Expr > >(
        static_cast< const Expr& >( expr ), NegateOp< Expr >() );
}

} // metal

#endif // METAL_UNARYNEGATEOP_H
