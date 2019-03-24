#ifndef METAL_UNARYMULTIPLYOP_H
#define METAL_UNARYMULTIPLYOP_H


#include "ScalarUnaryOp.h"


namespace metal
{

/**
 * @brief Unary operation taken by \ref ScalarUnaryOp object to define the expression for
 * multiplying an expression with a floating point number.
 *
 * @tparam Expr Type of expression for which multiplication is defined
 */
template< typename Expr >
class UnaryMultiplyOp
{

public:
    /** Alias for partial type of the input expression */
    using Input = typename Partial< Expr >::Type;

    /** Alias for the output partial expression type */
    using Output = decltype( std::declval< Input >() * double{} );


    /**
     * @brief Construct a new Unary Multiply Op object with a scalar to multiply an expression
     * with.
     *
     * @param scalar Multiplier
     */
    explicit UnaryMultiplyOp( double scalar )
        : scalar_{ scalar }
    {
    }

    /**
     * @brief Applies the transformation on the value of an expression.
     *
     * @param value Value of the expression
     * @return double Transformed value
     */
    double applyToValue( double value ) const
    {
        return value * scalar_;
    }

    /**
     * @brief Applies the transformation on the partial of an expression.
     *
     * @param partial Partial of the expression
     * @return Output Transformed partial
     */
    Output applyToPartial( double, const Input& partial ) const
    {
        return partial * scalar_;
    }

private:
    /** Scalar to multiply the expression with */
    double scalar_;
};


/**
 * @brief Binary multiplication operator between an expression and a floating point number.
 *
 * @tparam Expr Type of the expression
 * @param expr Expression to multiply with
 * @param multiplier Floating point value to multiply with
 * @return ScalarUnaryOp< Expr, UnaryMultiplyOp< Expr > > Expression that represents the
 * multiplication
 */
template< typename Expr >
ScalarUnaryOp< Expr, UnaryMultiplyOp< Expr > > operator*(
    const ScalarBase< Expr >& expr, double multiplier )
{
    return ScalarUnaryOp< Expr, UnaryMultiplyOp< Expr > >(
        static_cast< const Expr& >( expr ), UnaryMultiplyOp< Expr >( multiplier ) );
}

/**
 * @brief Binary multiplication operator between a floating point number and an expression.
 *
 * @tparam Expr Expr Type of the expression
 * @param multiplier Floating point value to multiply
 * @param expr Expression to multiply
 * @return ScalarUnaryOp< Expr, UnaryMultiplyOp< Expr > > Expression that represents the
 * multiplication
 */
template< typename Expr >
ScalarUnaryOp< Expr, UnaryMultiplyOp< Expr > > operator*(
    double multiplier, const ScalarBase< Expr >& expr )
{
    return expr * multiplier;
}

} // metal

#endif // METAL_UNARYMULTIPLYOP_H
