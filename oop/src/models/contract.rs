use std::time::Instant;

pub struct Contract {
    pub id: u64,
    pub customer: Customer,
    pub products: [Product],
    pub return_date: Instant,
    pub factual_return_date: Instant,
    pub start_cost: u64,
    pub buyback_cost: u64,
    pub closed: bool,
}
