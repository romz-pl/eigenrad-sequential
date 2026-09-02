# set title 'Coulomb potential'
set xlabel 'radius [bohr]'
set ylabel 'Eigenfunction'
set terminal svg enhanced font "Arial,12"
set logscale x

set output "ell1_n0.svg"
plot 'ell1_n0.dat' title 'Coulomb potential, L = 1, n = 0'

set output "ell1_n1.svg"
plot 'ell1_n1.dat' title 'Coulomb potential, L = 1, n = 1'

set output "ell1_n2.svg"
plot 'ell1_n2.dat' title 'Coulomb potential, L = 1, n = 2'

set output "ell1_n3.svg"
plot 'ell1_n3.dat' title 'Coulomb potential, L = 1, n = 3'


