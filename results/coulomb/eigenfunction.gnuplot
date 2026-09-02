set xlabel 'radius [bohr]'
set ylabel 'Eigenfunction'
set terminal svg enhanced font "Arial,12"

do for [L=0:4] {
    do for [scale in "lin log"] {
        if (scale eq "log") { set logscale x }

        do for [n=0:3] {
            set output sprintf("./ell%d/ell%d_n%d_%s.svg", L, L, n, scale)
            plot sprintf("./ell%d/ell%d_n%d.dat", L, L, n) title sprintf("Coulomb potential, L = %d, n = %d", L, n)
        }

        unset logscale x
    }
}

set output