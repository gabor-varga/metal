#ifndef METAL_BINARYMULTIPLYOP_H
#define METAL_BINARYMULTIPLYOP_H


#include "ScalarBinaryOp.h"


namespace metal
{

class BinaryMultiplyOp
{

public:
    double applyToValue( double left, double right ) const
    {
        return left * right;
    }

    double leftPartial( double /*left*/, double right ) const
    {
        return right;
    }

    double rightPartial( double left, double /*right*/ ) const
    {
        return left;
    }
};


template< typename Left, typename Right >
ScalarBinaryOp< Left, Right, BinaryMultiplyOp > operator*(
    const ScalarBase< Left >& left, const ScalarBase< Right >& right )
{
    return ScalarBinaryOp< Left, Right, BinaryMultiplyOp >( static_cast< const Left& >( left ),
        static_cast< const Right& >( right ), BinaryMultiplyOp{} );
}

} // metal

#endif // METAL_BINARYMULTIPLYOP_H
