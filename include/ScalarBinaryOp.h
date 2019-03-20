#ifndef METAL_SCALARBINARYOP_H
#define METAL_SCALARBINARYOP_H


#include "ScalarBase.h"
#include <numeric>


namespace metal
{

    template< typename Left, typename Right, typename Op >
    class ScalarBinaryOp : public ScalarBase< ScalarBinaryOp< Left, Right, Op > >
    {

    public:
        /** Alias for type of partial derivative vector. Using Eigen row vector */
        using Partial = Eigen::Matrix< double, 1, -1 >;

        /** Alias for Eigen segment ET to represent part of the derivative vector */
        using PartialSegment = decltype( std::declval< Partial >().segment( int(), int() ) );

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
            , partial_{}
            , parameterMap_{}
        {
            if ( left_.parameterMap() == right_.parameterMap() )
            {
                // forwardCall_ = ForwardCall::LeftExpr;
                parameterMap_ = left_.parameterMap();
                partial_ = left_.partial() + right_.partial();
            }
            else if ( left_.size() == 0 )
            {
                // forwardCall_ = ForwardCall::RightExpr;
                parameterMap_ = right_.parameterMap();
                partial_ = right_.partial();
            }
            else if ( right_.size() == 0 )
            {
                // forwardCall_ = ForwardCall::RightExpr;
                parameterMap_ = left_.parameterMap();
                partial_ = left_.partial();
            }
            else
            {
                // forwardCall_ = ForwardCall::ThisExpr;
                ParameterPtrVector params = left_.parameters();
                const auto& rparams = right_.parameters();
                params.insert( params.end(), rparams.begin(), rparams.end() );
                std::sort( params.begin(), params.end() );
                params.erase( std::unique( params.begin(), params.end() ), params.end() );

                const int totalDim = std::accumulate( params.begin(), params.end(), 0,
                    []( int tmp, const auto& p ) { return tmp + p->dim(); } );
                partial_.setZero( totalDim );

                int id = 0;
                for ( const auto& p : params )
                {
                    const int dim = p->dim();
                    parameterMap_[p] = id;

                    if ( left_.parameterMap().count( p ) )
                    {
                        // partial_.segment( id, dim )
                        //     += op_.leftPartial( left_.value(), right_.value() ) * left_.at( p );
                        partial_.segment( id, dim )
                            += op_.leftPartial( left_.value(), right_.value() )
                            * left_.partial().segment( left_.parameterMap().at( p ), p->dim() );
                    }
                    if ( right_.parameterMap().count( p ) )
                    {
                        // partial_.segment( id, dim )
                        //     += op_.rightPartial( left_.value(), right_.value() ) * right_.at( p );
                        partial_.segment( id, dim )
                            += op_.rightPartial( left_.value(), right_.value() )
                            * right_.partial().segment( right_.parameterMap().at( p ), p->dim() );
                    }

                    id += dim;
                }
            }
        }

        /**
         *  @copydoc ScalarBase::value()
         */
        double value() const
        {
            return op_.applyToValue( left_.value(), right_.value() );
        }

        /**
         *  @copydoc ScalarBase::partial()
         */
        Partial partial() const
        {
            return partial_;
        }

        /**
         *  @copydoc ScalarBase::parameterMap()
         */
        auto parameterMap() const
        {
            return parameterMap_;
        }

        /**
         *  @copydoc ScalarBase::dim()
         */
        size_t dim() const
        {
            return static_cast< size_t >( partial_.size() );
        }

        /**
         *  @copydoc ScalarBase::size()
         */
        size_t size() const
        {
            return parameterMap_.size();
        }

        /**
         *  @copydoc ScalarBase::parameters()
         */
        ParameterPtrVector parameters() const
        {
            return left_.parameters();
        }

        /**
         *  @copydoc ScalarBase::begin()
         */
        IteratorType begin() const
        {
            return IteratorType( *this, parameterMap_.begin() );
        }

        /**
         *  @copydoc ScalarBase::end()
         */
        IteratorType end() const
        {
            return IteratorType( *this, parameterMap_.end() );
        }

        /**
         *  @copydoc ScalarBase::at()
         */
        auto at( const ParameterPtr& p ) const
        {
            if ( parameterMap_.count( p ) == 0 )
            {
                throw std::runtime_error(
                    "Error! Parameter not present in partials: '" + p->name() + "'" );
            }

            return partial_.segment( parameterMap_.at( p ), p->dim() );
        }

    private:
        const Left& left_;

        const Right& right_;

        Op op_;

        Partial partial_;

        ParameterMap parameterMap_;

        // ForwardCall forwardCall_;

        // bool sameParameters_;
    };

} // metal

#endif // METAL_SCALARBINARYOP_H
