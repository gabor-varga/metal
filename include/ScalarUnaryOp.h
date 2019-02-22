#ifndef DIFF_SCALARUNARYOP_H
#define DIFF_SCALARUNARYOP_H


#include "ScalarBase.h"
#include <math.h>


namespace diff
{

    template< typename Expr, typename Op >
    class ScalarUnaryOp : public ScalarBase< ScalarUnaryOp< Expr, Op > >
    {

    public:
        using Partial = typename Op::Output;
        using PartialSegment = decltype( std::declval< Partial >().segment( int(), int() ) );
        using Record = std::pair< ParameterPtr, PartialSegment >;
        using Iterator = Iterator< ScalarUnaryOp< Expr, Op > >;


        ScalarUnaryOp( const Expr& expr, const Op& op )
            : expr_( expr )
            , op_( op )
            , partial_( op_.applyToPartial( expr_.value(), expr_.partial() ) )
        {
        }

        double value() const
        {
            return op_.applyToValue( expr_.value() );
        }

        Partial partial() const
        {
            return partial_;
        }

        auto parameterMap() const
        {
            return expr_.parameterMap();
        }

        size_t dim() const
        {
            return expr_.dim();
        }

        size_t size() const
        {
            return expr_.size();
        }

        ParameterPtrVector parameters() const
        {
            return expr_.parameters();
        }

        Iterator begin() const
        {
            return Iterator( *this, expr_.parameterMap().begin() );
        }

        Iterator end() const
        {
            return Iterator( *this, expr_.parameterMap().end() );
        }

    private:
        const Expr& expr_;

        Op op_;

        Partial partial_;
    };
    

    template< typename Expr >
    class UnaryAdditionOp
    {

    public:
        using Input = typename Expr::Partial;
        using Output = Input;

        explicit UnaryAdditionOp( double scalar )
            : scalar_( scalar )
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
    ScalarUnaryOp< Expr, UnaryAdditionOp< Expr > > operator+( const ScalarBase< Expr >& scalar, double additee )
    {
        return ScalarUnaryOp< Expr, UnaryAdditionOp< Expr > >( static_cast< const Expr& >( scalar ), UnaryAdditionOp< Expr >( additee ) );
    }

    template< typename Expr >
    ScalarUnaryOp< Expr, UnaryAdditionOp< Expr > > operator+( double additee, const ScalarBase< Expr >& scalar )
    {
        return scalar + additee;
    }


    template< typename Expr >
    class UnaryMultiplyOp
    {

    public:
        using Input = typename Expr::Partial;
        using Output = decltype( std::declval< Input >().operator*( double() ) );

        explicit UnaryMultiplyOp( double scalar )
            : scalar_( scalar )
        {
        }

        double applyToValue( double value ) const
        {
            return value * scalar_;
        }

        Output applyToPartial( double, const Input& partial ) const
        {
            return partial * scalar_;
        }

    private:
        double scalar_;
    };


    template< typename Expr >
    ScalarUnaryOp< Expr, UnaryMultiplyOp< Expr > > operator*( const ScalarBase< Expr >& scalar, double multiplier )
    {
        return ScalarUnaryOp< Expr, UnaryMultiplyOp< Expr > >( static_cast< const Expr& >( scalar ), UnaryMultiplyOp< Expr >( multiplier ) );
    }

    template< typename Expr >
    ScalarUnaryOp< Expr, UnaryMultiplyOp< Expr > > operator*( double multiplier, const ScalarBase< Expr >& scalar )
    {
        return scalar * multiplier;
    }


    template< typename Expr >
    struct SineOp
    {
        using Input = typename Expr::Partial;
        using Output = decltype( std::declval< Input >().operator*( double() ) );

        double applyToValue( double value ) const
        {
            return sin( value );
        }

        Output applyToPartial( double value, const Input& partial ) const
        {
            return partial * cos( value );
        }
    };

    template< typename Expr >
    ScalarUnaryOp< Expr, SineOp< Expr > > sin( const ScalarBase< Expr >& scalar )
    {
        return ScalarUnaryOp< Expr, SineOp< Expr > >( static_cast< const Expr& >( scalar ), SineOp< Expr >() );
    }

} // diff

#endif // DIFF_SCALARUNARYOP_H
