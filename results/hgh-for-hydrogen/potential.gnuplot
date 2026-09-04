set terminal svg enhanced font "Arial,12"
set xlabel 'radius [bohr]'
set ylabel 'HGH pseudopotential for hydrogen'


set output "potential_lin.svg"
plot [0.1:2] -1  lw 2.5 title "HGH pseudopotential for hydrogen"


set logscale x
set output "potential_log.svg"
plot [0.1:50] -1 lc rgb "red" lw 2.5 title "HGH pseudopotential for hydrogen"