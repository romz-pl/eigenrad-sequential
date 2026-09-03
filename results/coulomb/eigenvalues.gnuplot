set terminal svg enhanced font "Arial,12"
set xlabel 'radius [bohr]'
set pointsize 0.5
set logscale y

do for [ell=0:4] {
    set output sprintf("./ell%d/eigenvalue_log.svg", ell)

    plot for [n=0:3] \
         sprintf("./ell%d/eigenvalues-convergence.dat", ell) \
         using 1:(column(n+4)) \
         with linespoints lw 1.5 pt 7 ps 2 \
         lc rgb word("red blue green olive", n+1) \
         title sprintf("Eigval n=%d", n)
}
