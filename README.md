# EIGENRAD: adaptive radial Schrödinger solver for central potentials



The EIGENRAD package searches for the smallest eigenvalues, $E_{n, \ell}$, and the corresponding eigenvectors, $P_{n, \ell}$, of the radial Schrödinger equation in the following form:

$$
-\frac{1}{2}\frac{\mathrm{d}^2 P_{n, \ell}(r)}{\mathrm{d} r^2} + \left[V(r) + \frac{\ell (\ell + 1)}{2 r^2}\right] P_{n, \ell}(r) = E_{n, \ell}  P_{n, \ell}
$$

with angular momentum $\ell = 0, 1, 2, \ldots$ and potential function $V : [0, \infty] \rightarrow \mathbb{R}$. The index $n$ in the pair $(E_{n, \ell}, P_{n, \ell})$ refers to the calculated eigenvalue-eigenfunction pair. The equation is defined on the infinite interval $[0, \infty]$ and the eigenfunctions $P_{n, \ell}$ for each of indices $(n, \ell)$ fulfill the zero Dirichlet boundary conditions:

$$
\lim_{r \rightarrow 0}P_{n, \ell}(r) = \lim_{r \rightarrow \infty}P_{n, \ell}(r) = 0
$$
