mod models;

fn main() {
    let p = models::product::Product::new(1, "Gold Ring".to_string(), 600);

    let cust =
        models::customer::Customer::new(1, "Some name".to_string(), "89990000000".to_string());

    println!("{}, {}", p.id, cust.id)
}
