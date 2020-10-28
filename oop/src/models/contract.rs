use crate::models::customer::Customer;
use crate::models::product::Product;

pub struct Contract {
    pub id: u64,
    pub customer: Customer,
    pub products: Vec<Product>,
    pub return_date: String,
    pub factual_return_date: String,
    pub start_cost: u64,
    pub buyback_cost: u64,
    pub closed: bool,
}

impl Contract {
    pub fn new(
        id: u64,
        customer: Customer,
        products: Vec<Product>,
        return_date: String,
        factual_return_date: String,
        start_cost: u64,
        buyback_cost: u64,
        closed: bool,
    ) -> Contract {
        Contract {
            id: id,
            customer: customer,
            products: products,
            return_date: return_date,
            factual_return_date: factual_return_date,
            start_cost: start_cost,
            buyback_cost: buyback_cost,
            closed: closed,
        }
    }
}

pub struct ContractsList {
    pub contracts: Vec<Contract>,
}
