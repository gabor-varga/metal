#include "TestSuite.h"


inline double negate( double x ) { return -x; }
inline metal::ScalarUnaryOp< metal::Scalar, metal::UnaryNegateOp >
negate( const metal::Scalar& x ) { return -x; }

inline double add1( double x ) { return x + 1.0; }
inline metal::ScalarUnaryOp< metal::Scalar, metal::UnaryAdditionOp >
add1( const metal::Scalar& x ) { return x + 1.0; }

inline double add2( double x ) { return 1.0 + x; }
inline metal::ScalarUnaryOp< metal::Scalar, metal::UnaryAdditionOp >
add2( const metal::Scalar& x ) { return 1.0 + x; }

inline double sub1( double x ) { return x - 1.0; }
inline metal::ScalarUnaryOp< metal::Scalar, metal::UnarySubtractionOp< metal::SubtractMode::Normal > >
sub1( const metal::Scalar& x ) { return x - 1.0; }

inline double sub2( double x ) { return 1.0 - x; }
inline metal::ScalarUnaryOp< metal::Scalar, metal::UnarySubtractionOp< metal::SubtractMode::Reverse > >
sub2( const metal::Scalar& x ) { return 1.0 - x; }

inline double mul1( double x ) { return x * 2.0; }
inline metal::ScalarUnaryOp< metal::Scalar, metal::UnaryMultiplyOp >
mul1( const metal::Scalar& x ) { return x * 2.0; }

inline double mul2( double x ) { return 2.0 * x; }
inline metal::ScalarUnaryOp< metal::Scalar, metal::UnaryMultiplyOp >
mul2( const metal::Scalar& x ) { return 2.0 * x; }

inline double div1( double x ) { return x / 2.0; }
inline metal::ScalarUnaryOp< metal::Scalar, metal::UnaryDivisionOp< metal::DivisionMode::Normal > >
div1( const metal::Scalar& x ) { return x / 2.0; }

inline double div2( double x ) { return 2.0 / x; }
inline metal::ScalarUnaryOp< metal::Scalar, metal::UnaryDivisionOp< metal::DivisionMode::Reverse > >
div2( const metal::Scalar& x ) { return 2.0 / x; }

inline double sqr_( double x ) { return x * x; }
inline metal::ScalarUnaryOp< metal::Scalar, metal::SquareOp >
sqr_( const metal::Scalar& x ) { return sqr( x ); }

inline double cube_( double x ) { return x * x * x; }
inline metal::ScalarUnaryOp< metal::Scalar, metal::CubeOp >
cube_( const metal::Scalar& x ) { return cube( x ); }

inline double sqrt_( double x ) { return std::sqrt( x ); }
inline metal::ScalarUnaryOp< metal::Scalar, metal::SquareRootOp >
sqrt_( const metal::Scalar& x ) { return sqrt( x ); }


TEST_SCALAR_UNARY( "Unary negate operation", "[scalar_unary_negate]", negate, -10.0, 10.0, 100 )

TEST_SCALAR_UNARY( "Unary addition operator 1", "[scalar_unary_add_1]", add1, -10.0, 10.0, 100 )
TEST_SCALAR_UNARY( "Unary addition operator 2", "[scalar_unary_add_2]", add2, -10.0, 10.0, 100 )

TEST_SCALAR_UNARY( "Unary subtraction operator 1", "[scalar_unary_sub_1]", sub1, -10.0, 10.0, 100 )
TEST_SCALAR_UNARY( "Unary subtraction operator 2", "[scalar_unary_sub_2]", sub2, -10.0, 10.0, 100 )

TEST_SCALAR_UNARY( "Unary multiplication operator 1", "[scalar_unary_mul_1]", mul1, -10.0, 10.0, 100 )
TEST_SCALAR_UNARY( "Unary multiplication operator 2", "[scalar_unary_mul_2]", mul2, -10.0, 10.0, 100 )

TEST_SCALAR_UNARY( "Unary division operator 1", "[scalar_unary_div_1]", div1, -10.0, 10.0, 100 )
TEST_SCALAR_UNARY( "Unary division operator 2", "[scalar_unary_div_2]", div2, 1.0, 10.0, 100 )
TEST_SCALAR_UNARY( "Unary division operator 3", "[scalar_unary_div_3]", div2, -10.0, -1.0, 100 )

TEST_SCALAR_UNARY( "Square test", "[scalar_unary_sqr]", sqr_, -10.0, 10.0, 100 )
TEST_SCALAR_UNARY( "Cube test", "[scalar_unary_cube]", cube_, -10.0, 10.0, 100 )
TEST_SCALAR_UNARY( "Square root test", "[scalar_unary_sqrt]", sqrt, 0, 10.0, 100 )

TEST_SCALAR_UNARY( "Sine test", "[scalar_unary_sin]", sin, -Pi, Pi, 100 )
TEST_SCALAR_UNARY( "Cosine test", "[scalar_unary_cos]", cos, -Pi, Pi, 100 )
TEST_SCALAR_UNARY( "Tangent test", "[scalar_unary_tan]", tan, -Pi / 3, Pi / 3, 100 )

TEST_SCALAR_UNARY( "Sine hyperbolic test", "[scalar_unary_sinh]", sinh, -4 * Pi, 4 * Pi, 100 )
TEST_SCALAR_UNARY( "Cosine hyperbolic test", "[scalar_unary_cosh]", cosh, -4 * Pi, 4 * Pi, 100 )
TEST_SCALAR_UNARY( "Tangent hyperbolic test", "[scalar_unary_tanh]", tanh, -4 * Pi, 4 * Pi / 3, 100 )

TEST_SCALAR_UNARY( "Inverse sine test", "[scalar_unary_asin]", asin, -1.0, 1.0, 100 )
TEST_SCALAR_UNARY( "Inverse cosine test", "[scalar_unary_acos]", cos, -1.0, 1.0, 100 )
TEST_SCALAR_UNARY( "Inverse tangent test", "[scalar_unary_atan]", atan, -100.0, 100.0, 100 )

TEST_SCALAR_UNARY( "Inverse sine hyperbolic test", "[scalar_unary_asinh]", asinh, -100.0, 100.0, 100 )
TEST_SCALAR_UNARY( "Inverse cosine hyperbolic test", "[scalar_unary_acosh]", acosh, 1.0, 100.0, 100 )
TEST_SCALAR_UNARY( "Inverse tangent hyperbolic test", "[scalar_unary_atanh]", atanh, -1.0, 1.0, 100 )
