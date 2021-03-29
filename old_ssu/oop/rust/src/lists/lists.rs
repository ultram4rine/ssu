pub trait List<T> {
    fn new_list(list: Vec<T>) -> Self;
    fn add_item(&mut self, item: T);
    fn remove_item(&mut self, item: T);
}
