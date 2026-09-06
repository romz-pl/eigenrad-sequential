set terminal svg enhanced font "Arial,12"
set xlabel 'radius [bohr]'
set ylabel 'Coulomb potential'

set output "potential_lin.svg"
plot [0.1:2] -1/x lw 2.5 title "Coulomb potential for Z = 1"

set logscale x
set output "potential_log.svg"
plot [0.1:50] -1/x lc rgb "red" lw 2.5 title "Coulomb potential for Z = 1"

unset logscale x
unset output