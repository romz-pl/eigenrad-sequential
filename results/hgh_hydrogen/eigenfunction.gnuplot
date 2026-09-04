set xlabel 'radius [bohr]'
set terminal svg enhanced font "Arial,12"
set pointsize 0.5

array Scales[2] = ["lin", "log"]
array Quantities[2] = ["P", "R"]

do for [L=0:4] {
    do for [si=1:2] {
        scale = Scales[si]
        if (scale eq "log") {
            set logscale x
            W = 1  # plus sign
        } else {
            unset logscale x
            W = 7  # filled circle
        }

        do for [n=0:3] {
            do for [qi=1:2] {
                quantity = Quantities[qi]
                col = qi + 1  # column 2 for P, column 3 for R

                if (quantity eq "P") {
                    set ylabel 'Function P(r)'
                    color = "red"
                    label = sprintf("Function P(r), L = %d, n = %d", L, n)
                } else {
                    set ylabel 'Function R(r) = P(r) / r'
                    color = "navy"
                    label = sprintf("Function R(r) = P(r) / r, L = %d, n = %d", L, n)
                }

                set output sprintf("./ell%d/%s/n%d_%s.svg", L, quantity, n, scale)
                plot sprintf("./ell%d/n%d.dat", L, n) \
                    using 1:col \
                    with points pt W lc rgb color \
                    title label
            }
        }
    }
    unset logscale x
}

set output
