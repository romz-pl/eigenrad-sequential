# set title 'Coulomb potential'
set xlabel 'radius [bohr]'
set ylabel 'Eigenfunction'
set terminal svg enhanced font "Arial,12"
set logscale x

set output "ell0_n1.svg"
plot 'ell0_n1.dat' title 'Coulomb potential, L = 0, n = 1' with lines

set output "ell0_n2.svg"
plot 'ell0_n2.dat' title 'Coulomb potential, L = 0, n = 2'

set output "ell0_n3.svg"
plot 'ell0_n3.dat' title 'Coulomb potential, L = 0, n = 3'

set output "ell0_n4.svg"
plot 'ell0_n4.dat' title 'Coulomb potential, L = 0, n = 4'

