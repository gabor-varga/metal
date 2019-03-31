#ifndef METAL_BINARYDIVISIONOP_H
#define METAL_BINARYDIVISIONOP_H


#include "ScalarBinaryOp.h"


namespace metal
{

/**
 * @brief Binary operation taken by \ref ScalarBinaryOp object to define the expression for
 * dividing two expressions.
 *
 */
class BinaryDivisionOp
{

public:
/**
     * @brief Applies the transformation on the value of an expression.
     *
     * @param left LHS of the division
     * @param right RHS of the division
     * @return double Result of division
     */
    double applyToValue( double left, double right ) const
    {
        return left / right;
    }

    /**
     * @brief Computes the partial derivative of the result w.r.t the LHS.
     *
     * @return double Partial w.r.t. the LHS
     */
    double leftPartial( double /*left*/, double right ) const
    {
        return 1.0 / right;
    }

    /**
     * @brief Computes the partial derivative of the result w.r.t the RHS.
     *
     * @return double Partial w.r.t. the RHS
     */
    double rightPartial( double left, double right ) const
    {
        return -left / ( right * right );
    }
};


/**
 * @brief Binary division operator between two expressions.
 *
 * @tparam Left Type of the LHS expression
 * @tparam Right Type of the RHS expression
 * @param left LHS expression
 * @param right RHS expression
 * @return ScalarBinaryOp< Left, Right, BinaryAdditionOp > Expression that represents the
 * division
 */
template< typename Left, typename Right >
ScalarBinaryOp< Left, Right, BinaryDivisionOp > operator/(
    const ScalarBase< Left >& left, const ScalarBase< Right >& right )
{
    return ScalarBinaryOp< Left, Right, BinaryDivisionOp >( static_cast< const Left& >( left ),
        static_cast< const Right& >( right ), BinaryDivisionOp{} );
}

} // metal

#endif // METAL_BINARYDIVISIONOP_H
