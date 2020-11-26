#[derive(Clone, Debug, Serialize, Deserialize, PartialEq)]
pub struct Customer {
    pub id: u64,
    pub name: String,
    pub phone: String,
}

impl Customer {
    pub fn new(id: u64, name: String, phone: String) -> Customer {
        Customer {
            id: id,
            name: name,
            phone: phone,
        }
    }
}

#[derive(Debug, Serialize, Deserialize, PartialEq)]
pub struct CustomersList {
    pub customers: Vec<Customer>,
}

impl CustomersList {
    pub fn new(customers: Vec<Customer>) -> CustomersList {
        CustomersList {
            customers: customers,
        }
    }

    pub fn add(&mut self, customer: Customer) {
        let item = self.customers.to_vec().into_iter().find(|x| x == &customer);
        match item {
            Some(c) => println!("Customers list already contains customer with {} id", c.id),
            None => self.customers.push(customer),
        }
    }

    pub fn remove(&mut self, customer: Customer) {
        let item = self.customers.to_vec().into_iter().find(|x| x == &customer);
        match item {
            Some(_) => {
                let index = self.customers.iter().position(|x| *x == customer).unwrap();
                self.customers.remove(index);
            }
            None => println!(
                "Customers list doesn't contains customer with {} id",
                customer.id
            ),
        }
    }
}
