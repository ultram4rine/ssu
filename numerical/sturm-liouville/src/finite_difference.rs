use crate::muller::muller_method;

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
