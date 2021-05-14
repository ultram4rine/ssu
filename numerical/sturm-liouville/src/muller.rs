pub fn muller_method<F>(
    f: F,
    mut x1: f64,
    mut x2: f64,
    mut x3: f64,
    eps: f64,
    n: i64,
) -> f64
where
    F: Fn(f64) -> f64,
{
    let mut xn: f64 = 0.;

    // divided differences.
    let fst_div_diff = |x1, x2| (f(x1) - f(x2)) / (x1 - x2);
    let snd_div_diff = |x1, x2, x3| {
        (fst_div_diff(x1, x2) - fst_div_diff(x2, x3)) / (x1 - x3)
    };

    let mut cond = false;
    let mut discrepancy = (x3 - x2).abs();

    for _ in 0..n {
        let w = fst_div_diff(x3, x2) + fst_div_diff(x3, x1)
            - fst_div_diff(x2, x1);

        let denom1 = w
            + (w.powi(2)
                - 4. * f(x3) * snd_div_diff(x3, x2, x1))
            .sqrt();
        let denom2 = w
            - (w.powi(2)
                - 4. * f(x3) * snd_div_diff(x3, x2, x1))
            .sqrt();

        let denom = if denom1.abs() > denom2.abs() {
            denom1
        } else {
            denom2
        };

        xn = x3 - 2. * f(x3) / denom;

        // Garwick technique. While |xn+1 - xn| decreases, continue the calculation.
        if (xn - x3).abs() < eps {
            cond = true;
        }
        if cond && (xn - x3).abs() > discrepancy {
            break;
        }

        x1 = x2;
        x2 = x3;
        x3 = xn;

        discrepancy = (xn - x3).abs();
    }

    xn
}
