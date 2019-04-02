#include "catch.hpp"
#include "FastVec.h"


using FastVec = metal::FastVec< double >;


inline bool equal( double left, double right )
{
    return std::fabs( left - right ) <= 0.0;
}


TEST_CASE( "FastVec can be constructed", "[fastvec_construct]" )
{
    SECTION( "Default and zero size constructor" )
    {
        const FastVec x;
        REQUIRE( x.data() == nullptr );
        REQUIRE( x.size() == 0 );

        const FastVec y{ 0 };
        REQUIRE( y.data() == nullptr );
        REQUIRE( y.size() == 0 );
    }

    SECTION( "Sized constructor, including value" )
    {
        const int s = 4;
        const FastVec x{ s };
        REQUIRE( x.data() != nullptr );
        REQUIRE( x.size() == s );

        const double v = 2.0;
        const FastVec y{ s, v };
        REQUIRE( y.data() != nullptr );
        REQUIRE( y.size() == s );
        for ( int i = 0; i < y.size(); i++ )
        {
            REQUIRE( equal( y.data()[i], v ) );
        }
    }

    SECTION( "Copy and move constructor" )
    {
        const int s = 4;
        const double v = 2.0;
        const FastVec x{ s, v };

        const FastVec y{ x };
        REQUIRE( y.data() != nullptr );
        REQUIRE( x.data() != y.data() );
        REQUIRE( x.size() == y.size() );
        for ( int i = 0; i < y.size(); i++ )
        {
            REQUIRE( equal( x.data()[i], y.data()[i] ) );
        }

        const FastVec z{ FastVec{ s, v } };
        REQUIRE( z.data() != nullptr );
        REQUIRE( x.data() != z.data() );
        REQUIRE( x.size() == z.size() );
        for ( int i = 0; i < z.size(); i++ )
        {
            REQUIRE( equal( x.data()[i], z.data()[i] ) );
        }
    }

    SECTION( "Copy and move assignment" )
    {
        const int s = 4;
        const double v = 2.0;
        const FastVec x{ s, v };

        const int s2 = 2;
        FastVec y{ s2 };
        y = x;
        REQUIRE( y.data() != nullptr );
        REQUIRE( x.data() != y.data() );
        REQUIRE( x.size() == y.size() );
        for ( int i = 0; i < y.size(); i++ )
        {
            REQUIRE( equal( x.data()[i], y.data()[i] ) );
        }

        FastVec z{ s2 };
        z = FastVec{ s, v };
        REQUIRE( z.data() != nullptr );
        REQUIRE( x.data() != z.data() );
        REQUIRE( x.size() == z.size() );
        for ( int i = 0; i < z.size(); i++ )
        {
            REQUIRE( equal( x.data()[i], z.data()[i] ) );
        }
    }
}


TEST_CASE( "FastVec supports segment proxy object", "[fastvec_segment]" )
{
    SECTION( "Add segment to vector" )
    {
        const int s1 = 2;
        const double v1 = 2.0;
        const FastVec x{ s1, v1 };

        const int s2 = 4;
        const double v2 = 1.0;
        FastVec y{ s2, v2 };
        
        y.segment( 1, 2 ) += x;
        REQUIRE( y.data() != nullptr );
        REQUIRE( y.size() == s2 );
        REQUIRE( equal( y.data()[0], v2 ) );
        REQUIRE( equal( y.data()[1], v2 + v1 ) );
        REQUIRE( equal( y.data()[2], v2 + v1 ) );
        REQUIRE( equal( y.data()[3], v2 ) );
    }

    SECTION( "Add segment to segment" )
    {
        const int s1 = 4;
        const double v1 = 2.0;
        const FastVec x{ s1, v1 };

        const int s2 = 4;
        const double v2 = 1.0;
        FastVec y{ s2, v2 };
        
        y.segment( 1, 2 ) += x.segment( 1, 2 );
        REQUIRE( y.data() != nullptr );
        REQUIRE( y.size() == s2 );
        REQUIRE( equal( y.data()[0], v2 ) );
        REQUIRE( equal( y.data()[1], v2 + v1 ) );
        REQUIRE( equal( y.data()[2], v2 + v1 ) );
        REQUIRE( equal( y.data()[3], v2 ) );
    }
}
