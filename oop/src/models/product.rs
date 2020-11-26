extern crate serde;
extern crate serde_xml_rs;

#[derive(Clone, Debug, Serialize, Deserialize, PartialEq)]
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

#[derive(Debug, Serialize, Deserialize, PartialEq)]
pub struct ProductsList {
    pub products: Vec<Product>,
}

impl ProductsList {
    pub fn new(products: Vec<Product>) -> ProductsList {
        ProductsList { products: products }
    }

    pub fn add(&mut self, product: Product) {
        let item = self.products.to_vec().into_iter().find(|x| x == &product);
        match item {
            Some(p) => println!("Products list already contains customer with {} id", p.id),
            None => self.products.push(product),
        }
    }

    pub fn remove(&mut self, product: Product) {
        let item = self.products.to_vec().into_iter().find(|x| x == &product);
        match item {
            Some(_) => {
                let index = self.products.iter().position(|x| *x == product).unwrap();
                self.products.remove(index);
            }
            None => println!(
                "Products list doesn't contains product with {} id",
                product.id
            ),
        }
    }
}
