#include "TestSuite.h"


inline double add( double x, double y ) { return x + y; }
inline metal::ScalarBinaryOp< metal::Scalar, metal::Scalar, metal::BinaryAdditionOp >
add( const metal::Scalar& x, const metal::Scalar& y ) { return x + y; }

inline double sub( double x, double y ) { return x - y; }
inline metal::ScalarBinaryOp< metal::Scalar, metal::Scalar, metal::BinarySubtractionOp >
sub( const metal::Scalar& x, const metal::Scalar& y ) { return x - y; }

inline double mul( double x, double y ) { return x * y; }
inline metal::ScalarBinaryOp< metal::Scalar, metal::Scalar, metal::BinaryMultiplyOp >
mul( const metal::Scalar& x, const metal::Scalar& y ) { return x * y; }

inline double div( double x, double y ) { return x / y; }
inline metal::ScalarBinaryOp< metal::Scalar, metal::Scalar, metal::BinaryDivisionOp >
div( const metal::Scalar& x, const metal::Scalar& y ) { return x / y; }

inline double arctan2( double x, double y ) { return atan2( x, y ); }
inline metal::ScalarBinaryOp< metal::Scalar, metal::Scalar, metal::Atan2Op >
arctan2( const metal::Scalar& x, const metal::Scalar& y ) { return atan2( x, y ); }


TEST_SCALAR_BINARY( "Binary addition operation", "[scalar_binary_add]", add, -10, 10, -10, 10, 100 )
TEST_SCALAR_BINARY( "Binary subtraction operation", "[scalar_binary_sub]", sub, -10, 10, -10, 10, 100 )
TEST_SCALAR_BINARY( "Binary multiplication operation", "[scalar_binary_mul]", mul, -10, 10, -10, 10, 100 )
TEST_SCALAR_BINARY( "Binary division operation", "[scalar_binary_div]", div, -10, 10, -10, 10, 100 )
TEST_SCALAR_BINARY( "Binary arc tangent operation", "[scalar_binary_atan2]", arctan2, -10, 10, -10, 10, 100 )
