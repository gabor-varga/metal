#ifndef METAL_UNARYADDITIONOP_H
#define METAL_UNARYADDITIONOP_H


#include "ScalarUnaryOp.h"


namespace metal
{

    template< typename Expr >
    class UnaryAdditionOp
    {

    public:
        using Input = typename Expr::Partial;
        using Output = Input;

        explicit UnaryAdditionOp( double scalar )
            : scalar_{ scalar }
        {
        }

        double applyToValue( double value ) const
        {
            return value + scalar_;
        }

        Output applyToPartial( double, const Input& partial ) const
        {
            return partial;
        }

    private:
        double scalar_;
    };

    template< typename Expr >
    ScalarUnaryOp< Expr, UnaryAdditionOp< Expr > > operator+(
        const ScalarBase< Expr >& expr, double addend )
    {
        return ScalarUnaryOp< Expr, UnaryAdditionOp< Expr > >(
            static_cast< const Expr& >( expr ), UnaryAdditionOp< Expr >( addend ) );
    }

    template< typename Expr >
    ScalarUnaryOp< Expr, UnaryAdditionOp< Expr > > operator+(
        double augend, const ScalarBase< Expr >& expr )
    {
        return expr + augend;
    }

} // metal

#endif // METAL_UNARYADDITIONOP_H
