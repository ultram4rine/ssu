#![allow(
    non_snake_case,
    unused_imports,
    unused_variables,
    dead_code
)]

mod methods;

use crate::methods::finite_difference::fdm;
use crate::methods::galerkin::galerkin_method;
use crate::methods::newton::newton_method;
use crate::methods::shooting::shooting_method;

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
    let spectrum = fdm(q, u0, ul, 128);
    spectrum.into_iter().for_each(|lambda| {
        println!("{}", lambda);
    })
}
