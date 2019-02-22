# METAL
**M**odern **E**xpression **T**emplate assisted **A**utomatic differentiation **L**ibrary

## Introduction

This purely C++ header library is developed to simplify partial derivative computation by implementing efficient automatic differentiation (**_AD_**) algorithms. It realies heavily on the expression template design pattern (**_ET_**) to optimise away temporaries by interfacing with a linear algebra library ([Eigen](http://eigen.tuxfamily.org/)) that supports this approach. During local **_ET_** evaluation backward **_AD_**, while globally forward **_AD_** is used. This enables complex computations to be performed (e.g. numerical integration of differential equations) without running into issues with stack size (of the backward algortithm).

## Disclaimer

This project a work in progress.
