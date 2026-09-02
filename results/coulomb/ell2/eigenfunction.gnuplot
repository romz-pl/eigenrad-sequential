set xlabel 'radius [bohr]'
set ylabel 'Eigenfunction'
set terminal svg enhanced font "Arial,12"

do for [scale in "lin log"] {
    if (scale eq "log") { set logscale x }

    do for [n=0:3] {
        set output sprintf("ell2_n%d_%s.svg", n, scale)
        plot sprintf("ell2_n%d.dat", n) title sprintf("Coulomb potential, L = 2, n = %d", n)
    }

    unset logscale x
}

set output