#ifndef METAL_BINARYADDITIONOP_H
#define METAL_BINARYADDITIONOP_H


#include "ScalarBinaryOp.h"


namespace metal
{


    class BinaryAdditionOp
    {

    public:
        
        double applyToValue( double left, double right ) const
        {
            return left + right;
        }

        double leftPartial( double, double ) const
        {
            return 1.0;
        }
       
        double rightPartial( double, double ) const
        {
            return 1.0;
        }
    };


    template< typename Left, typename Right >
    ScalarBinaryOp< Left, Right, BinaryAdditionOp > operator+(
        const ScalarBase< Left >& left, const ScalarBase< Right >& right )
    {
        return ScalarBinaryOp< Left, Right, BinaryAdditionOp >( static_cast< const Left& >( left ),
            static_cast< const Right& >( right ), BinaryAdditionOp{} );
    }

} // metal

#endif // METAL_BINARYADDITIONOP_H
