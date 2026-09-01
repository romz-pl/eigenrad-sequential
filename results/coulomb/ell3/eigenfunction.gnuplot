# set title 'Coulomb potential'
set xlabel 'radius [bohr]'
set ylabel 'Eigenfunction'
set terminal svg enhanced font "Arial,12"
set logscale x

set output "ell3_n1.svg"
plot 'ell3_n1.dat' title 'Coulomb potential, L = 2, n = 1'

set output "ell3_n2.svg"
plot 'ell3_n2.dat' title 'Coulomb potential, L = 2, n = 2'

set output "ell3_n3.svg"
plot 'ell3_n3.dat' title 'Coulomb potential, L = 2, n = 3'

set output "ell3_n4.svg"
plot 'ell3_n4.dat' title 'Coulomb potential, L = 2, n = 4'

