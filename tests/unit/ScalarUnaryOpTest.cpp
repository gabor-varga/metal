#include "TestSuite.h"


double negate( double x ) { return -x; }
metal::ScalarUnaryOp< metal::Scalar, metal::UnaryNegateOp >
negate( const metal::Scalar& x ) { return -x; }

double add1( double x ) { return x + 1.0; }
metal::ScalarUnaryOp< metal::Scalar, metal::UnaryAdditionOp >
add1( const metal::Scalar& x ) { return x + 1.0; }

double add2( double x ) { return 1.0 + x; }
metal::ScalarUnaryOp< metal::Scalar, metal::UnaryAdditionOp >
add2( const metal::Scalar& x ) { return 1.0 + x; }

double sub1( double x ) { return x - 1.0; }
metal::ScalarUnaryOp< metal::Scalar, metal::UnarySubtractionOp< metal::SubtractMode::Normal > >
sub1( const metal::Scalar& x ) { return x - 1.0; }

double sub2( double x ) { return 1.0 - x; }
metal::ScalarUnaryOp< metal::Scalar, metal::UnarySubtractionOp< metal::SubtractMode::Reverse > >
sub2( const metal::Scalar& x ) { return 1.0 - x; }

double mul1( double x ) { return x * 2.0; }
metal::ScalarUnaryOp< metal::Scalar, metal::UnaryMultiplyOp >
mul1( const metal::Scalar& x ) { return x * 2.0; }

double mul2( double x ) { return 2.0 * x; }
metal::ScalarUnaryOp< metal::Scalar, metal::UnaryMultiplyOp >
mul2( const metal::Scalar& x ) { return 2.0 * x; }

double div1( double x ) { return x / 2.0; }
metal::ScalarUnaryOp< metal::Scalar, metal::UnaryDivisionOp< metal::DivisionMode::Normal > >
div1( const metal::Scalar& x ) { return x / 2.0; }

double div2( double x ) { return 2.0 / x; }
metal::ScalarUnaryOp< metal::Scalar, metal::UnaryDivisionOp< metal::DivisionMode::Reverse > >
div2( const metal::Scalar& x ) { return 2.0 / x; }


TEST_SCALAR( "Unary negate operation", "[scalar_unary_negate]", negate, -10, 10, 100 )

TEST_SCALAR( "Unary addition operator 1", "[scalar_unary_add_1]", add1, -10, 10, 100 )
TEST_SCALAR( "Unary addition operator 2", "[scalar_unary_add_2]", add2, -10, 10, 100 )

TEST_SCALAR( "Unary subtraction operator 1", "[scalar_unary_sub_1]", sub1, -10, 10, 100 )
TEST_SCALAR( "Unary subtraction operator 2", "[scalar_unary_sub_2]", sub2, -10, 10, 100 )

TEST_SCALAR( "Unary multiplication operator 1", "[scalar_unary_mul_1]", mul1, -10, 10, 100 )
TEST_SCALAR( "Unary multiplication operator 2", "[scalar_unary_mul_2]", mul2, -10, 10, 100 )

TEST_SCALAR( "Unary division operator 1", "[scalar_unary_div_1]", div1, -10, 10, 100 )
TEST_SCALAR( "Unary division operator 2", "[scalar_unary_div_2]", div2, 1.0, 10, 100 )
TEST_SCALAR( "Unary division operator 3", "[scalar_unary_div_3]", div2, -10, -1.0, 100 )

TEST_SCALAR( "Sine test", "[scalar_unary_sin]", sin, -Pi, Pi, 100 )
TEST_SCALAR( "Cosine test", "[scalar_unary_cos]", cos, -Pi, Pi, 100 )
TEST_SCALAR( "Tangent test", "[scalar_unary_tan]", tan, -Pi / 3, Pi / 3, 100 )
