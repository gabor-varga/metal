#ifndef METAL_SCALARBINARYOP_H
#define METAL_SCALARBINARYOP_H


#include "ScalarBase.h"


namespace metal
{


template< typename Left, typename Right, typename Op >
class ScalarBinaryOp;


template< typename Left, typename Right, typename Op >
struct PartialSegment< ScalarBinaryOp< Left, Right, Op > >
{
    /** Alias for internal type */
    using Type = decltype( double{} * std::declval< Left >().at( ParameterPtr{} )
        + double{} * std::declval< Right >().at( ParameterPtr{} ) );
};


template< typename Left, typename Right, typename Op >
class ScalarBinaryOp : public ScalarBase< ScalarBinaryOp< Left, Right, Op > >
{

public:
    /** Alias for type of partial derivative vector. Using Eigen row vector */
    using Partial = EigenRowVector;

    /** Alias for Eigen segment ET to represent part of the derivative vector */
    using PartialSegment = typename PartialSegment< ScalarBinaryOp< Left, Right, Op > >::Type;

    /** Alias for the iterator */
    using IteratorType = Iterator< ScalarBinaryOp< Left, Right, Op > >;


    enum class ForwardCall
    {
        LeftExpr,
        RightExpr,
        ThisExpr
    };


    ScalarBinaryOp( const Left& left, const Right& right, const Op& op )
        : left_{ left }
        , right_{ right }
        , op_{ op }
        , lvalue_{ left_.value() }
        , rvalue_{ right_.value() }
        , value_{ op_.applyToValue( lvalue_, rvalue_ ) }
        , parameters_{ left_.parameters() }
    {
        const bool condition1 = parameters_.size() == 0;
        const bool condition2 = right_.size() && left_.parameterMap() != right_.parameterMap();

        if ( condition1 || condition2 )
        {
            const auto& params = right_.parameters();
            parameters_.insert( parameters_.end(), params.begin(), params.end() );
        }
        if ( condition2 )
        {
            std::sort( parameters_.begin(), parameters_.end() );
            parameters_.erase(
                std::unique( parameters_.begin(), parameters_.end() ), parameters_.end() );
        }
    }

    /**
     *  @copydoc ScalarBase::value()
     */
    double value() const
    {
        return value_;
    }

    /**
     *  @copydoc ScalarBase::partial()
     */
    Partial partial() const
    {
        return Partial{};
    }

    /**
     *  @copydoc ScalarBase::parameterMap()
     */
    ParameterMap parameterMap() const
    {
        return ParameterMap{};
    }

    /**
     *  @copydoc ScalarBase::dim()
     */
    size_t dim() const
    {
        const auto func = []( int tmp, const ParameterPtr& p ) { return tmp + p->dim(); };
        return std::accumulate( parameters_.begin(), parameters_.end(), size_t{ 0 }, func );
    }

    /**
     *  @copydoc ScalarBase::size()
     */
    size_t size() const
    {
        return parameters_.size();
    }

    /**
     *  @copydoc ScalarBase::parameters()
     */
    const ParameterPtrVector& parameters() const
    {
        return parameters_;
    }

    /**
     *  @copydoc ScalarBase::begin()
     */
    IteratorType begin() const
    {
        return IteratorType{ *this, ParameterMap{}.begin() };
    }

    /**
     *  @copydoc ScalarBase::end()
     */
    IteratorType end() const
    {
        return IteratorType{ *this, ParameterMap{}.end() };
    }

    /**
     *  @copydoc ScalarBase::contains()
     */
    bool contains( const ParameterPtr& p ) const
    {
        return std::find( parameters_.begin(), parameters_.end(), p ) != parameters_.end();
    }

    /**
     *  @copydoc ScalarBase::at()
     */
    PartialSegment at( const ParameterPtr& p ) const
    {
        return op_.leftPartial( lvalue_, rvalue_ ) * left_.at( p )
            + op_.rightPartial( lvalue_, rvalue_ ) * right_.at( p );
    }

    /**
     *  @copydoc ScalarBase::accum()
     */
    void accum( EigenRowVectorSegment& partial, double scalar, const ParameterPtr& p ) const
    {
        if ( left_.contains( p ) )
        {
            left_.accum( partial, scalar * op_.leftPartial( lvalue_, rvalue_ ), p );
        }
        if ( right_.contains( p ) )
        {
            right_.accum( partial, scalar * op_.rightPartial( lvalue_, rvalue_ ), p );
        }
    }

private:
    const Left& left_;

    const Right& right_;

    Op op_;

    double lvalue_;
    double rvalue_;
    double value_;

    ParameterPtrVector parameters_;
};

} // metal

#endif // METAL_SCALARBINARYOP_H
