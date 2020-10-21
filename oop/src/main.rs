use crate::models::contract::*;
use crate::models::customer::*;
use crate::models::product::*;

fn main() {
    let p = Product {
        id: 1,
        name: "Gold Ring".to_string(),
        cost: 600,
    };

    println!("{}", p)
}
