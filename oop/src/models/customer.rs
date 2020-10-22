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
