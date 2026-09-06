set terminal svg enhanced font "Arial,12"
set xlabel 'radius [bohr]'
set ylabel 'Soft-Coulomb potential: Z = 1, a = 1, q = 2'

V(x) = -1/sqrt(x*x + 1*1)

set output "potential_lin.svg"
plot [0.1:2] V(x) lw 2.5

set logscale x
set output "potential_log.svg"
plot [0.1:50] V(x) lc rgb "red" lw 2.5

unset logscale x
unset output