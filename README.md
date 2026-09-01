# EIGENRAD: adaptive Schrödinger solver

## Problem Definition

The **EIGENRAD** package searches for the smallest eigenvalues, $E_{n, \ell}$, and the corresponding eigenvectors, $P_{n, \ell}$, of the **radial Schrödinger equation** in the following form:

$$
-\frac{1}{2}\frac{\mathrm{d}^2 P_{n, \ell}(r)}{\mathrm{d} r^2} + \left[V(r) + \frac{\ell (\ell + 1)}{2 r^2}\right] P_{n, \ell}(r) = E_{n, \ell}  P_{n, \ell}
$$

with angular momentum $\ell = 0, 1, 2, \ldots$ and potential function $V : [0, \infty] \rightarrow \mathbb{R}$. The index $n$ in the pair $(E_{n, \ell}, P_{n, \ell})$ refers to the calculated eigenvalue-eigenfunction pair. The equation is defined on the infinite interval $[0, \infty]$ and the eigenfunctions $P_{n, \ell}$ for each of indices $(n, \ell)$ fulfill the zero Dirichlet boundary conditions:

$$
\lim_{r \rightarrow 0}P_{n, \ell}(r) = \lim_{r \rightarrow \infty}P_{n, \ell}(r) = 0
$$

## Implemented Algorithm

The EIGENRAD package numerically solves the radial Schrödinger equation. It uses the $h$-adaptive, high-order finite element method with Lobbato polynomials. The Galerkin formulation of the finite element method was applied for discretization and matrix formulation.

Details of the algorithm is fully described in the article:

+ Z. Romanowski, *Application of h-adaptive, high order finite element method to solve radial Schrödinger equation*,
   [Molecular Physics vol. 107, pp. 1339-1348  (2009)](https://www.tandfonline.com/doi/abs/10.1080/00268970902873554)

The algorithm was also used for solution of Kohn_sham equation for atomic system. The results were described in the article:

+ Z. Romanowski, *Adaptive solver of a Kohn-Sham equation for an atom*,
   [Modelling and Simulation in Materials Science and Engineering vol. 17, 045001 (2009)](https://iopscience.iop.org/article/10.1088/0965-0393/17/4/045001/meta)
