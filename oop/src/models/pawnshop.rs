use crate::models::contract::ContractsList;
use crate::models::customer::CustomersList;
use crate::models::product::ProductsList;

#[derive(Debug, Serialize, Deserialize, PartialEq)]
pub struct Pawnshop {
    pub contracts: ContractsList,
    pub customers: CustomersList,
    pub products: ProductsList,
}

impl Pawnshop {
    pub fn new(
        contracts: ContractsList,
        customers: CustomersList,
        products: ProductsList,
    ) -> Pawnshop {
        Pawnshop {
            contracts: contracts,
            customers: customers,
            products: products,
        }
    }
}
