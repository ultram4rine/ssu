use rusqlite::{Connection, Result};

pub trait DB<T> {
    fn to_db(&self, conn: &Connection) -> Result<()>;
    fn from_db(conn: &Connection) -> Result<Vec<T>>;
}
