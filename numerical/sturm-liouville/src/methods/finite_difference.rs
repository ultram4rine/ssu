/// Replace Sturm–Liouville equation with finding eigenvalues
/// of matrix by finite difference approximation.
pub fn fdm(q: fn(f64) -> f64, u0: fn() -> f64, ul: fn(f64) -> f64, N: i64) -> Vec<f64> {
    let h = 1. / (N as f64);
    let mut A = vec![];

    for i in 0..N - 1 {
        A.push(vec![]);
        for j in 0..N - 1 {
            if i == j {
                A[i as usize].push(2.);
            } else if i == j + 1 || i == j - 1 {
                A[i as usize].push(-1.);
            } else {
                A[i as usize].push(0.);
            }
        }
    }

    let poly = |lambda| {
        D(
            N - 1,
            lambda,
            A.clone(),
            h,
            {
                let i = (N - 2) as usize;
                A[i][i] - h.powi(2) * lambda
            },
            1.,
        )
    };

    let mut spectrum = vec![];
    for n in 1..=5 {
        let lambda = parabola_method(
            poly,
            8. * (n as f64).powi(2),
            9. * (n as f64).powi(2),
            10. * (n as f64).powi(2),
            1e-8,
        );
        spectrum.push(lambda);
    }

    spectrum
}

/// Recurrent formula for the characteristic polynomial (tail recursion).
fn D(m: i64, lambda: f64, A: Vec<Vec<f64>>, h: f64, val: f64, prev: f64) -> f64 {
    match m {
        0 => prev,
        1 => {
            let i = (m - 1) as usize;
            D(
                m - 1,
                lambda,
                A.clone(),
                h,
                (A[i][i] - h.powi(2) * lambda) * val,
                val,
            )
        }
        _ => {
            let i = (m - 1) as usize;
            D(
                m - 1,
                lambda,
                A.clone(),
                h,
                (A[i][i] - h.powi(2) * lambda) * val - A[i][i - 1] * A[i - 1][i] * prev,
                val,
            )
        }
    }
}

fn parabola_method<F>(f: F, mut x1: f64, mut x2: f64, mut x3: f64, eps: f64) -> f64
where
    F: Fn(f64) -> f64,
{
    let mut xn: f64 = 0.;

    // divided differences.
    let fst_div_diff = |x1, x2| (f(x1) - f(x2)) / (x1 - x2);
    let snd_div_diff = |x1, x2, x3| (fst_div_diff(x1, x2) - fst_div_diff(x2, x3)) / (x1 - x3);

    let mut cond = false;
    let mut discrepancy = (x3 - x2).abs();

    // number of iterations.
    let n = 1000;
    for _ in 0..n {
        let a = snd_div_diff(x3, x2, x1);
        let b = a * (x3 - x2) + fst_div_diff(x3, x2);
        let c = f(x3);

        let disc = b.powf(2.) - 4. * a * c;
        let z1 = (-b + disc.sqrt()) / (2. * a);
        let z2 = (-b - disc.sqrt()) / (2. * a);

        let z = if z1.abs() < z2.abs() { z1 } else { z2 };
        xn = x3 + z;

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
