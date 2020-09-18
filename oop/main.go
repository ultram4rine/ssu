package main

import (
	"log"

	"github.com/ultram4rine/ssu/oop/models"

	"github.com/jmoiron/sqlx"
	_ "github.com/mattn/go-sqlite3"
)

var db *sqlx.DB

func init() {
	db, err := sqlx.Connect("sqlite3", "pawnshop.db")
	if err != nil {
		log.Fatalf("Failed to connect to DB: %s", err)
	}

	if _, err = sqlx.LoadFile(db, "schema.sql"); err != nil {
		log.Fatalf("Failed to create DB schema: %s", err)
	}
}

func main() {
	var (
		goldRing = models.Product{
			ID:   1,
			Name: "Gold Ring",
			Cost: 500,
		}
		silverRing = models.Product{
			ID:   2,
			Name: "Silver Ring",
			Cost: 300,
		}
	)

	if err := goldRing.ToXML("products.xml"); err != nil {
		log.Fatalf("Failed to encode %s product to XML: %s", goldRing.Name, err)
	}
	if err := silverRing.ToXML("products.xml"); err != nil {
		log.Fatalf("Failed to encode %s product to XML: %s", silverRing.Name, err)
	}
}
