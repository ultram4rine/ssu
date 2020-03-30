fn boundary_start(x: f64, k: f64, l: f64) -> f64 {
    use std::f64;
    let pi = f64::consts::PI;

    return k * ((k * pi * x) / l).sin();
}

fn boundary_end(x: f64, k: f64, l: f64) -> f64 {
    use std::f64;
    let pi = f64::consts::PI;

    return k * x * ((k * pi * x) / l).sin();
}

fn main() {
    // method variables.
    const a: f64 = 1_f64; // a in utt = uxx is 1.
    const h: f64 = 0.125;
    const l: f64 = h / a; // so alpha == 1.

    // equation variables.
    const x_start: f64 = 0_f64;
    const x_end: f64 = 1_f64;
    const t_start: f64 = 0_f64;
    const t_end: f64 = 0.2;

    // boundary functions variables.
    let k = 2_f64;
    let l_in_denominator = 1_f64;

    const ts_size: u64 = (t_end / l) as u64;
    let mut ts: [[f64; xs_size as usize]; ts_size as usize] =
        [[0_f64; xs_size as usize]; ts_size as usize];

    const xs_size: u64 = (x_end / h) as u64;
    let mut xs: [f64; xs_size as usize] = [0_f64; xs_size as usize];

    xs[0] = boundary_start(x_start, k, l_in_denominator);
    xs[xs_size as usize - 1] = boundary_end(x_end, k, l_in_denominator);

    let mut t = 0_f64;
    let mut x = 0_f64;

    let mut i = 0;
    let mut j = 0;

    'loop_for_t: loop {
        'loop_for_x: loop {
            if i + 1 == xs_size as usize {
                break 'loop_for_x;
            }

            i += 1;
            x += h;
            xs[i] = boundary_start(x, k, l_in_denominator);
        }
        if j + 1 == ts_size as usize {
            break 'loop_for_t;
        }

        ts[i] = xs;
        j += 1;
        t += l;
    }
}
