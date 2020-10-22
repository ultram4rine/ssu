pub struct Product {
    pub id: u64,
    pub name: String,
    pub cost: u64,
}

impl Product {
    pub fn new(id: u64, name: String, cost: u64) -> Product {
        Product {
            id: id,
            name: name,
            cost: cost,
        }
    }
}
