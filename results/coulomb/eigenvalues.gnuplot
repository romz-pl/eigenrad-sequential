set terminal svg enhanced font "Arial,12"
set xlabel 'adaptive step'
set pointsize 0.5

file(ell) = sprintf("./ell%d/eigenvalues-convergence.dat", ell)
colors = "red blue green olive"

# Eigenvalue convergence
set logscale y
set ylabel 'Eigenvalue difference'

do for [ell=0:4] {
    set output sprintf("./ell%d/eigenvalue_log.svg", ell)

    plot for [n=0:3] file(ell) using 1:(column(n+4)) \
        with linespoints lw 1.5 pt 7 ps 2 \
        lc rgb word(colors, n+1) \
        title sprintf("Eigval n=%d", n)
}

# Degrees of freedom
unset logscale y
set ylabel 'Space dimension'

do for [ell=0:4] {
    set output sprintf("./ell%d/dofs.svg", ell)

    plot file(ell) using 1:2 \
        with points pt 3 ps 2 \
        lc rgb "red" \
        title "Dofs"
}