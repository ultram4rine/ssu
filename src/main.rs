use plotters::prelude::*;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let root = BitMapBackend::new("graph.png", (640, 480)).into_drawing_area();
    root.fill(&WHITE)?;
    let mut chart = ChartBuilder::on(&root)
        .caption("Faber-Schauder system", ("sans-serif", 50).into_font())
        .margin(5)
        .x_label_area_size(30)
        .y_label_area_size(30)
        .build_cartesian_2d(0f32..1f32, 0f32..1f32)?;

    chart.configure_mesh().draw()?;

    let colors = [&RED, &GREEN, &BLUE, &YELLOW, &MAGENTA, &CYAN];

    for n in 12..13 {
        let i = n % 6;
        let color = &RED;

        chart
            .draw_series(LineSeries::new(
                (0..=500000)
                    .map(|x| x as f32 / 500000.0)
                    .map(|x| (x, fi(x, n))),
                &RED,
            ))?
            .label(format!("fi{}(x)", n))
            .legend(|(x, y)| PathElement::new(vec![(x, y), (x + 20, y)], &RED));
    }

    chart
        .configure_series_labels()
        .background_style(&WHITE.mix(0.8))
        .border_style(&BLACK)
        .draw()?;

    Ok(())
}

fn fi(x: f32, n: i32) -> f32 {
    if n == 0 {
        return 1_f32;
    } else if n == 1 {
        return x;
    } else {
        let (k, i) = count_k_and_i(n);

        if ((2_f32 * i - 2_f32) / 2_f32.powf(k) <= x) && (x <= 2_f32 * i / 2_f32.powf(k)) {
            return 1_f32 - (x * 2_f32.powf(k) - 2_f32 * i + 1_f32).abs();
        } else {
            return 0_f32;
        }
    }
}

fn count_k_and_i(n: i32) -> (f32, f32) {
    let k = (((n - 1) as f32).log2()).floor();
    let i = (n as f32 - 2_f32.powf(k)).round();
    return (k, i);
}
