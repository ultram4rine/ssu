use plotters::prelude::*;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let root = BitMapBackend::new("graph.png", (640, 480)).into_drawing_area();
    root.fill(&WHITE)?;
    let mut chart = ChartBuilder::on(&root)
        .caption("y=x^2", ("sans-serif", 50).into_font())
        .margin(5)
        .x_label_area_size(30)
        .y_label_area_size(30)
        .build_cartesian_2d(-1f32..1f32, -0.1f32..1f32)?;

        chart.configure_mesh().draw()?;

        chart
            .draw_series(LineSeries::new(
                (-50..=50).map(|x| x as f32 / 50.0).map(|x| (x, x * x)),
                &RED,
            ))?
            .label("y = x^2")
            .legend(|(x, y)| PathElement::new(vec![(x, y), (x + 20, y)], &RED));
    
        chart
            .configure_series_labels()
            .background_style(&WHITE.mix(0.8))
            .border_style(&BLACK)
            .draw()?;
    
        Ok(())

    for x in 0..10 {
        println!(
            "x: {x}, fi: {fi}",
            x = x as f64 * 0.1,
            fi = fi(x as f64 * 0.1, 32)
        );
    }
}

fn fi(x: f64, n: i64) -> f64 {
    if n == 0 {
        return 1_f64;
    } else if n == 1 {
        return x;
    } else {
        let (k, i) = count_k_and_i(n);

        if x == (2_f64 * i - 1_f64) / (2_f64.powf(k + 1_f64)) {
            return 1_f64;
        } else if (x <= (i - 1_f64) / 2_f64.powf(k)) && (x >= i / 2_f64.powf(k)) {
            return 0_f64;
        } else {
            return (1_f64 - x * 2_f64.powf(k + 1_f64) - 2_f64 * i + 1_f64).abs();
        }
    }
}

fn count_k_and_i(n: i64) -> (f64, f64) {
    let k = (((n - 1) as f64).log2()).floor();
    let i = (n as f64 - 2_f64.powf(k)).round();
    return (k, i);
}
