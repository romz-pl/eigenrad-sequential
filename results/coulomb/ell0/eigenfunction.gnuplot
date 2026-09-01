# set title 'Coulomb potential'
set xlabel 'radius [bohr]'
set ylabel 'Eigenfunction'
set terminal svg enhanced font "Arial,12"
set logscale x

set output "ell0_n1.svg"
plot 'eig.dat_0' title 'Coulomb potential, L = 0, n = 1'

set output "ell0_n2.svg"
plot 'eig.dat_1' title 'Coulomb potential, L = 0, n = 2'