# METAL
**M**odern **E**xpression **T**emplate assisted **A**utomatic differentiation **L**ibrary

## Introduction

This purely C++ header library is developed to simplify partial derivative computation by implementing efficient automatic differentiation (**_AD_**) algorithms. It realies heavily on the expression template design pattern (**_ET_**) to optimise away temporaries by interfacing with a linear algebra library ([**Eigen**](http://eigen.tuxfamily.org/)) that supports this approach. During local **_ET_** evaluation backward **_AD_**, while globally forward **_AD_** is used. This enables complex computations to be performed (e.g. numerical integration of differential equations) without running into issues with stack size (of the backward algortithm).

## Examples

```cpp
using metal;

Scalar a{ 1.0, "a" };
Scalar b{ 2.0, "b" };
Scalar c{ 3.0, "c" };
auto x = sin(a) / 2 + b * c
```

## Compilation

This is a **header-only** library, no compilation or installation (apart from including it in the part of the compiler) is needed.

## Dependencies

This project relies heavily on [**Eigen**](http://eigen.tuxfamily.org/). Minimal version of 3.3.x is reccomended (probably works with any Eigen3 version).

## Disclaimer

This project a work in progress.
