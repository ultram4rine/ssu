#![allow(
    non_snake_case,
    unused_imports,
    unused_variables,
    dead_code
)]

mod boundary_conditions;
mod finite_difference;

use crate::finite_difference::fdm;

/// Left boundary condition.
fn u0() -> f64 {
    0.0
}

/// Right boundary condition.
fn ul(l: f64) -> f64 {
    0.0
}

/// A potential.
fn q(x: f64) -> f64 {
    0.0
}

fn main() {
    let l: f64 = 2.;
    let (x1, x2, x3) = (
        3_f64.powi(2) / l.powi(2) - 1.,
        3_f64.powi(2) / l.powi(2),
        3_f64.powi(2) / l.powi(2) + 1.,
    );

    let spectrum = fdm(q, l, 64, x1, x2, x3, 5);
    spectrum.into_iter().for_each(|lambda| {
        println!("{}", lambda);
    })
}
