# METAL
**M**odern **E**xpression **T**emplate assisted **A**utomatic differentiation **L**ibrary

## Introduction

This header-only C++ library is developed to simplify partial derivative computation by implementing efficient automatic differentiation (**_AD_**). 

It realies heavily on the expression template design pattern (**_ET_**) to optimise away temporaries by interfacing with a linear algebra library ([**Eigen**](http://eigen.tuxfamily.org/)) that supports this approach. During local **_ET_** evaluation backward **_AD_**, while globally forward **_AD_** is used. This enables complex computations to be performed (e.g. numerical integration of differential equations) without running into issues with stack size (of the backward algorithm).

Apart from using [Eigen](http://eigen.tuxfamily.org/), it is also designed to be used together with it allow vectorizing computations.

## Examples

```cpp
metal::Scalar a{ 1.0, "a" };
metal::Scalar b{ 2.0, "b" };
metal::Scalar c{ 3.0, "c" };
metal::Scalar x = sin( a ) * 0.5 + b * c;
```

## Testing

[**Catch2**](https://github.com/catchorg/Catch2) is integrated for testing. A single-header version is included in the repository test folder.

## Compilation

This is a **header-only** library. To compile the tests and examples a c++11 compatible compiler is required.

## Dependencies

This project relies heavily on [**Eigen**](http://eigen.tuxfamily.org/). Minimal version of 3.3.x is reccomended (probably works with any Eigen3 version).

## Disclaimer

This project a work in progress.
