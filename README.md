# EIGENRAD: adaptive Schrödinger solver

## Problem

The **EIGENRAD** package searches for the smallest eigenvalues, $E_{n, \ell}$, and the corresponding eigenvectors, $P_{n, \ell}$, of the **radial Schrödinger equation** in the following form:

$$
-\frac{1}{2}\frac{\mathrm{d}^2 P_{n, \ell}(r)}{\mathrm{d} r^2} + \left[V(r) + \frac{\ell (\ell + 1)}{2 r^2}\right] P_{n, \ell}(r) = E_{n, \ell}  P_{n, \ell}
$$

with angular momentum $\ell = 0, 1, 2, \ldots$ and potential function $V : [0, \infty] \rightarrow \mathbb{R}$. The index $n = 1, 2, 3, \ldots$ in the pair $(E_{n, \ell}, P_{n, \ell})$ refers to the calculated eigenvalue-eigenfunction pair. The equation is defined on the infinite interval $[0, \infty]$ and the eigenfunctions $P_{n, \ell}$ for each of indices $(n, \ell)$ fulfill the zero Dirichlet boundary conditions:

$$
\lim_{r \rightarrow 0}P_{n, \ell}(r) = \lim_{r \rightarrow \infty}P_{n, \ell}(r) = 0
$$

## Algorithm

The **EIGENRAD** package numerically solves the radial Schrödinger equation. It uses the **$h$-adaptive, high-order finite element method with Lobbato polynomials**. The Galerkin formulation of the finite element method was applied for discretization and matrix formulation.

The following article fully describes the details of the algorithm:

+ Z. Romanowski, *Application of h-adaptive, high order finite element method to solve radial Schrödinger equation*,
   [Molecular Physics vol. 107, pp. 1339-1348  (2009)](https://doi.org/10.1080/00268970902873554)

The algorithm was also used to solve the Kohn-Sham equation for an atomic system. The results are described in the following article:

+ Z. Romanowski, *Adaptive solver of a Kohn-Sham equation for an atom*,
   [Modelling and Simulation in Materials Science and Engineering vol. 17, 045001 (2009)](https://doi.org/10.1088/0965-0393/17/4/045001)

The application of Lobbato polynomials in the high-order finite element method is described in the following book:

+ P. Šolín, L. Segeth, I. Doležel, *High-Order Finite Element Method* [2003](https://doi.org/10.1201/9780203488041)



## Implementation

The **EIGENRAD** package is written in C++ and uses the following external libraries: BLAS, [LAPACK](https://github.com/reference-lapack/lapack), and [GoogleTest (gtest)](https://github.com/google/googletest). The build system is implemented using [CMake](https://cmake.org/).

## Available potentials, their numerical eigenvalues, and their eigenfunctions

The EIGENRAD package provides native definitions of the potentials commonly used in theoretical physics and chemistry. Each available potential has been applied to evaluate selected eigenvalues and their corresponding eigenfunctions. Convergence analysis of the numerically calculated eigenvalues is presented in both tabular and graphical form. The following potentials have been thoroughly analysed so far:

+ [Coulomb potential](./results/coulomb/README.md)
+ [Hartwigsen-Goedecker-Hutter pseudopotential for hydrogen](./results/hgh_hydrogen/README.md)
