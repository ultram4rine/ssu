mod methods;

use crate::methods::finite_difference::fdm;
use crate::methods::galerkin::galerkin_method;
use crate::methods::newton::newton_method;
use crate::methods::shooting::shooting_method;

fn q(x: f64) -> f64 {
    x.sin()
}

fn main() {
    println!("{:?}", shooting_method(q));
}
