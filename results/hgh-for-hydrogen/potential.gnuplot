set terminal svg enhanced font "Arial,12"

set xlabel 'radius [bohr]'
set ylabel 'HGH pseudopotential for hydrogen'

C1 = -4.180237
C2 =  0.725075
rloc = 0.2

V(x) = -erf(x/rloc) / x \
       + exp(-(x/rloc)**2 / 2) * (C1 + C2 * (x/rloc)**2)

set style line 1 linewidth 2.5

# Linear x axis
unset logscale x
set output 'potential_lin.svg'

plot [0:2] V(x) with lines ls 1 \
    title 'HGH pseudopotential for hydrogen'


# Logarithmic x axis
set logscale x
set output 'potential_log.svg'

plot [0.0001:50] V(x) with lines ls 1 \
    title 'HGH pseudopotential for hydrogen'