// plotting lib.
use plotters::prelude::*;

use std::io;
use std::io::Write;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    // create graph picture and fill it by white color.
    let root = BitMapBackend::new("graph.png", (800, 800)).into_drawing_area();
    root.fill(&WHITE)?;
    // create area for graph.
    let mut chart = ChartBuilder::on(&root)
        .caption("Faber-Schauder system", ("sans-serif", 50).into_font())
        .margin(5)
        .x_label_area_size(30)
        .y_label_area_size(30)
        .build_cartesian_2d(-0.1f32..1.1f32, -0.1f32..1.1f32)?;

    chart.configure_mesh().draw()?;

    let colors = vec![&RED, &GREEN, &BLUE];

    // choose what to draw.
    let draw = read_i32("Draw a single function(1) or a pack(2)?: ");
    if draw == 1 {
        // if draw a single func.
        let n = read_i32("Choose number of function: ");

        let color = &RED;
        let closure = move |(x, y)| PathElement::new(vec![(x, y), (x + 20, y)], &RED);

        chart
            .draw_series(LineSeries::new(
                (0..=500000)
                    .map(|x| x as f32 / 500000.0)
                    .map(|x| (x, fi(x, n))),
                color,
            ))?
            .label(format!("fi{}(x)", n))
            .legend(closure);
    } else if draw == 2 {
        // if draw a pack of functions.
        let k = read_i32("Choose number of pack: ");
        if k < 1 {
            // k must be >= 1.
            panic!("k must be >= 1");
        }

        let mut ns = Vec::new();
        for i in 1..=2_i32.pow(k as u32) {
            ns.push(2_i32.pow(k as u32) + i);
        }

        for n in ns {
            let i = n % 3;
            let color = colors[i as usize];
            let closure = move |(x, y)| PathElement::new(vec![(x, y), (x + 20, y)], color);
            chart
                .draw_series(LineSeries::new(
                    (0..=500000)
                        .map(|x| x as f32 / 500000.0)
                        .map(|x| (x, fi(x, n))),
                    color,
                ))?
                .label(format!("fi{}(x)", n))
                .legend(closure);
        }
    }

    chart
        .configure_series_labels()
        .background_style(&WHITE.mix(0.8))
        .border_style(&BLACK)
        .draw()?;

    Ok(())
}

// fi is a func of Fabes-Schauder system.
fn fi(x: f32, n: i32) -> f32 {
    if n == 0 {
        return 1_f32;
    } else if n == 1 {
        return x;
    } else {
        let (k, i) = count_k_and_i(n);

        if x == (2_f32 * i - 1_f32) / 2_f32.powf(k + 1_f32) {
            return 1_f32;
        } else if (x < (i - 1_f32) / 2_f32.powf(k)) || (x > i / 2_f32.powf(k)) {
            return 0_f32;
        } else {
            let x1: f32;
            let x2 = (2_f32 * i - 1_f32) / 2_f32.powf(k + 1_f32);

            let y1 = 0_f32;
            let y2 = 1_f32;

            if x < (2_f32 * i - 1_f32) / 2_f32.powf(k + 1_f32) {
                x1 = (i - 1_f32) / 2_f32.powf(k);
            } else {
                x1 = (i) / 2_f32.powf(k);
            }

            return (-x1 * y2 + x2 * y1 - (y1 - y2) * x) / (x2 - x1);
        }
    }
}

// count_k_and_i is a helper func for getting k and i from n = 2^k + i.
fn count_k_and_i(n: i32) -> (f32, f32) {
    let k = (((n - 1) as f32).log2()).floor();
    let i = (n as f32 - 2_f32.powf(k)).round();
    return (k, i);
}

fn read_i32(comment: &str) -> i32 {
    print!("{}", comment);
    io::stdout().flush().unwrap();

    let mut string: String = String::new();

    io::stdin()
        .read_line(&mut string)
        .ok()
        .expect("Error read line!");

    return string.trim().parse::<i32>().unwrap();
}
