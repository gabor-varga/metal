#ifndef METAL_BINARYMULTIPLYOP_H
#define METAL_BINARYMULTIPLYOP_H


#include "ScalarBinaryOp.h"


namespace metal
{

/**
 * @brief Binary operation taken by \ref ScalarBinaryOp object to define the expression for
 * multiplying two expressions.
 *
 */
struct BinaryMultiplyOp
{
    /**
     * @brief Applies the transformation on the value of an expression.
     *
     * @param left LHS of the multiplication
     * @param right RHS of the multiplication
     * @return double Result of multiplication
     */
    double applyToValue( double left, double right ) const
    {
        return left * right;
    }

    /**
     * @brief Computes the partial derivative of the result w.r.t the LHS.
     *
     * @return double Partial w.r.t. the LHS
     */
    double leftPartial( double /*left*/, double right ) const
    {
        return right;
    }

    /**
     * @brief Computes the partial derivative of the result w.r.t the RHS.
     *
     * @return double Partial w.r.t. the RHS
     */
    double rightPartial( double left, double /*right*/ ) const
    {
        return left;
    }
};


/**
 * @brief Binary multiplication operator between two expressions.
 *
 * @tparam Left Type of the LHS expression
 * @tparam Right Type of the RHS expression
 * @param left LHS expression
 * @param right RHS expression
 * @return ScalarBinaryOp< Left, Right, BinaryAdditionOp > Expression that represents the
 * multiplication
 */
template< typename Left, typename Right >
ScalarBinaryOp< Left, Right, BinaryMultiplyOp > operator*(
    const ScalarBase< Left >& left, const ScalarBase< Right >& right )
{
    return ScalarBinaryOp< Left, Right, BinaryMultiplyOp >( static_cast< const Left& >( left ),
        static_cast< const Right& >( right ), BinaryMultiplyOp{} );
}

} // metal

#endif // METAL_BINARYMULTIPLYOP_H
