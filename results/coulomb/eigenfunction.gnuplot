set xlabel 'radius [bohr]'
set terminal svg enhanced font "Arial,12"
set pointsize 0.5

do for [L=0:4] {
    do for [scale in "lin log"] {
        if (scale eq "log") {
            set logscale x
            W = 1 # plus sign
        }
        else {
            W = 7 # filled circle
        }

        do for [n=0:3] {
            set ylabel 'Function P(r)'
            set output sprintf("./ell%d/P/ell%d_n%d_%s.svg", L, L, n, scale)
            plot sprintf("./ell%d/ell%d_n%d.dat", L, L, n) \
                using 1:2 \
                with points pt W lc rgb "red" \
                title sprintf("Function P(r), L = %d, n = %d", L, n)

            set ylabel 'Function R(r) = P(r) / r'
            set output sprintf("./ell%d/R/ell%d_n%d_%s.svg", L, L, n, scale)
            plot sprintf("./ell%d/ell%d_n%d.dat", L, L, n) \
                using 1:3 \
                with points pt W lc rgb "navy blue" \
                title sprintf("Function R(r) = P(r) / r, L = %d, n = %d", L, n)
        }

        unset logscale x
    }
}

set output