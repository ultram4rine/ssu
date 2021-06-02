#![allow(
    non_snake_case,
    unused_imports,
    unused_variables,
    dead_code
)]

mod finite_difference;
mod muller;

use crate::finite_difference::fdm;

/// A potential.
fn q(x: f64) -> f64 {
    0.
}

fn main() {
    let l: f64 = 1.;
    let (x1, x2, x3) = (
        3_f64.powi(2) / l.powi(2) - 1.,
        3_f64.powi(2) / l.powi(2),
        3_f64.powi(2) / l.powi(2) + 1.,
    );

    let spectrum = fdm(q, l, 256, x1, x2, x3, 5);
    spectrum.into_iter().for_each(|lambda| {
        println!("{}", lambda);
    })
}
