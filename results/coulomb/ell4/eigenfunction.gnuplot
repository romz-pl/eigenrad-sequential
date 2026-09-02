# set title 'Coulomb potential'
set xlabel 'radius [bohr]'
set ylabel 'Eigenfunction'
set terminal svg enhanced font "Arial,12"


set output "ell4_n0_lin.svg"
plot 'ell4_n0.dat' title 'Coulomb potential, L = 4, n = o'

set output "ell4_n1_lin.svg"
plot 'ell4_n1.dat' title 'Coulomb potential, L = 4, n = 1'

set output "ell4_n2_lin.svg"
plot 'ell4_n2.dat' title 'Coulomb potential, L = 4, n = 2'

set output "ell4_n3_lin.svg"
plot 'ell4_n3.dat' title 'Coulomb potential, L = 4, n = 3'


set logscale x

set output "ell4_n0_log.svg"
plot 'ell4_n0.dat' title 'Coulomb potential, L = 4, n = o'

set output "ell4_n1_log.svg"
plot 'ell4_n1.dat' title 'Coulomb potential, L = 4, n = 1'

set output "ell4_n2_log.svg"
plot 'ell4_n2.dat' title 'Coulomb potential, L = 4, n = 2'

set output "ell4_n3_log.svg"
plot 'ell4_n3.dat' title 'Coulomb potential, L = 4, n = 3'