/// Replace Sturm-Liouville equation with finding eigenvalues
/// of matrix by finite difference approximation.
///
/// # Arguments
///
/// * `q` - Potential q(x).
/// * `l` - End of the segment.
/// * `N` - Number of intervals of the grid.
/// * `x1, x2, x3` - Initial approximation.
/// * `n` - Number of eigenvalues to find.
pub fn fdm(
    q: fn(f64) -> f64,
    l: f64,
    N: i64,
    x1: f64,
    x2: f64,
    x3: f64,
    n: i64,
) -> Vec<f64> {
    let h = l / (N as f64);

    let poly = |lambda| {
        D(
            N - 1,
            lambda,
            h,
            q,
            2. + h.powi(2) * q(h * (N as f64 - 2.))
                - h.powi(2) * lambda,
            1.,
        )
    };

    let mut spectrum = vec![];
    for i in 1..=n {
        let lambda = muller_method(
            poly,
            x1 * (i as f64).powi(2),
            x2 * (i as f64).powi(2),
            x3 * (i as f64).powi(2),
            1e-8,
            100,
        );
        spectrum.push(lambda);
    }

    spectrum
}

/// Recurrent formula for the characteristic polynomial (tail recursion).
fn D(
    m: i64,
    lambda: f64,
    h: f64,
    q: fn(f64) -> f64,
    val: f64,
    prev: f64,
) -> f64 {
    match m {
        0 => prev,
        1 => D(
            m - 1,
            lambda,
            h,
            q,
            (2. + h.powi(2) * q(h * (m as f64 - 1.))
                - h.powi(2) * lambda)
                * val,
            val,
        ),
        _ => D(
            m - 1,
            lambda,
            h,
            q,
            (2. + h.powi(2) * q(h * (m as f64 - 1.))
                - h.powi(2) * lambda)
                * val
                - -1. * -1. * prev,
            val,
        ),
    }
}

fn muller_method<F>(
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
