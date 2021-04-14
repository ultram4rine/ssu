/// Replace Sturm–Liouville equation with finding eigenvalues
/// of matrix by finite difference approximation.
pub fn fdm(q: fn(f64) -> f64, u0: fn() -> f64, ul: fn(f64) -> f64, mut N: i64) -> f64 {
    N = 4;
    let h = 1.0 / (N as f64);
    let mut A = vec![];

    for i in 0..N - 1 {
        A.push(vec![]);
        for j in 0..N - 1 {
            if i == j {
                A[i as usize].push(2.0);
            } else if i == j + 1 || i == j - 1 {
                A[i as usize].push(-1.0);
            } else {
                A[i as usize].push(0.0);
            }
        }
    }

    let poly = move |lambda| D(A, N - 1, h, lambda);
    println!("{}", poly(9.37));
    0.0
}

/// Recurrent formula for the characteristic polynomial.
fn D(A: Vec<Vec<f64>>, m: i64, h: f64, lambda: f64) -> f64 {
    println!("m: {}", m);
    match m {
        0 => 1.0,
        1 => {
            (A[(m - 1) as usize][(m - 1) as usize] - h * h * lambda)
                * D(A.clone(), m - 1, h, lambda)
        }
        _ => {
            let i = (m - 1) as usize;
            (A[i][i] - h * h * lambda) * D(A.clone(), m - 1, h, lambda)
                - A[i][i - 1] * A[i - 1][i] * D(A.clone(), m - 2, h, lambda)
        }
    }
}
