#ifndef METAL_UNARYADDITIONOP_H
#define METAL_UNARYADDITIONOP_H


#include "ScalarUnaryOp.h"


namespace metal
{

/**
 * @brief Unary operation taken by \ref ScalarUnaryOp object to define the expression for adding
 * an expression and to a floating point number.
 *
 * @tparam Expr Type of expression to which addition is defined
 */
template< typename Expr >
class UnaryAdditionOp
{

public:
    /** Alias for partial type of the input expression */
    using Input = typename Expr::Partial;

    /** Alias for the output partial expression type */
    using Output = Input;


    /**
     * @brief Construct a new Unary Addition Op object with a scalar to add to an expression.
     *
     * @param scalar Addend
     */
    explicit UnaryAdditionOp( double scalar )
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
        return value + scalar_;
    }

    /**
     * @brief Applies the transformation on the partial of an expression.
     *
     * @param partial Partial of the expression
     * @return Output Transformed partial
     */
    Output applyToPartial( double, const Input& partial ) const
    {
        return partial;
    }

private:
    /** Scalar to be added to the expression */
    double scalar_;
};


/**
 * @brief Binary addition operator between an expression and a floating point number.
 *
 * @tparam Expr Type of the expression
 * @param expr Expression to add to
 * @param addend Floating point value to add
 * @return ScalarUnaryOp< Expr, UnaryAdditionOp< Expr > > Expression that represents the
 * addition
 */
template< typename Expr >
ScalarUnaryOp< Expr, UnaryAdditionOp< Expr > > operator+(
    const ScalarBase< Expr >& expr, double addend )
{
    return ScalarUnaryOp< Expr, UnaryAdditionOp< Expr > >(
        static_cast< const Expr& >( expr ), UnaryAdditionOp< Expr >( addend ) );
}

/**
 * @brief Binary addition operator between a floating point number and an expression.
 *
 * @tparam Expr Expr Type of the expression
 * @param augend Floating point value to add to
 * @param expr Expression to add
 * @return ScalarUnaryOp< Expr, UnaryAdditionOp< Expr > > Expression that represents the
 * addition
 */
template< typename Expr >
ScalarUnaryOp< Expr, UnaryAdditionOp< Expr > > operator+(
    double augend, const ScalarBase< Expr >& expr )
{
    // Since addition is commutative, just delegate
    return expr + augend;
}

} // metal

#endif // METAL_UNARYADDITIONOP_H
