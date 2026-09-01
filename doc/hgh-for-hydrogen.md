# Hartwigsen-Goedecker-Hutter pseudopotential for hydrogen

The potenial has the form

$$
V(r) = -\frac{Z_\mathrm{ion}}{r} \mathrm{erf}(w / \sqrt{2}) + \mathrm{exp}(-w^2 / 2) [C_1 + C_2 w^2 + C_3 w^3 + C_4 w^4]
$$

where $w = r / r_{\mathrm{loc}}$. The coefficients in the above equations are as follows:

$$
\begin{aligned}
C_1 &= -4.180237,\\
C_2 &= 0.725075,\\
C_3 &= C_4 = 0,\\
Z_{\mathrm{ion}} &= 1,\\
r_{\mathrm{loc}} &= 0.2.
\end{aligned}
$$

For details about the Hartwigsen-Goedecker-Hutter pseudopotential, refer to the following article:

+ C. Hartwigsen, S. Goedecker, and J. Hutter, *Relativistic separable dual-space Gaussian pseudopotentials from H to Rn*, [Phys. Rev. B 58, 3641](https://doi.org/10.1103/PhysRevB.58.3641)
