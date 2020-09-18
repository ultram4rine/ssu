package models

import (
	"encoding/xml"
	"fmt"
	"os"
	"time"
)

// Product struct describes a product in pawnshop.
type Product struct {
	ID   int    `xml:"id" db:"id"`
	Name string `xml:"name" db:"name"`
	Cost int    `xml:"cost" db:"cost"`
}

// Print func printing product to console.
func (p Product) Print() {
	fmt.Printf("ID: %d\nName: %s\nCost: %d", p.ID, p.Name, p.Cost)
}

// ToXML function encodes product to xml and write it to file.
func (p Product) ToXML(filepath string) error {
	b, err := xml.MarshalIndent(p, "", " ")
	if err != nil {
		return err
	}
	b = append(b, '\n')

	file, err := os.OpenFile(filepath, os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
	if err != nil {
		return err
	}
	defer file.Close()

	if _, err := file.Write(b); err != nil {
		return err
	}

	return nil
}

// Customer struct describes a customer of pawnshop.
type Customer struct {
	ID    int    `xml:"id" db:"id"`
	Name  string `xml:"name" db:"name"`
	Phone string `xml:"phone" db:"phone"`
}

// Print func printing customer to console.
func (c Customer) Print() {
	fmt.Printf("ID: %d\nName: %s\nPhone: %s", c.ID, c.Name, c.Phone)
}

// ToXML function encodes customer to xml and write it to file.
func (c Customer) ToXML(filepath string) error {
	b, err := xml.MarshalIndent(c, "", " ")
	if err != nil {
		return err
	}
	b = append(b, '\n')

	file, err := os.OpenFile(filepath, os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
	if err != nil {
		return err
	}
	defer file.Close()

	if _, err := file.Write(b); err != nil {
		return err
	}

	return nil
}

// Contract struct describes a contract between pawnshop and customer.
type Contract struct {
	ID            int       `xml:"id" db:"id"`
	CustomerID    int       `xml:"customerID" db:"cutomer_id"`
	Products      []Product `xml:"products"`
	ReturnDate    time.Time `xml:"returnDate" db:"return_date"`
	FactualReturn time.Time `xml:"factualReturn" db:"factual_return_date"`
	StartCost     int       `xml:"startCost" db:"start_cost"`
	BuybackCost   int       `xml:"buybackCost" db:"buyback_cost"`
	Closed        bool      `xml:"closed" db:"closed"`
}

// Print func printing contract to console.
func (c Contract) Print() {
	fmt.Printf("ID: %d\nCustomer ID: %d\nProducts: %v\nReturn date: %v\nFactual return date: %v\nStart cost: %d\nBuyback cost: %d\nClosed: %v", c.ID, c.CustomerID, c.Products, c.ReturnDate, c.FactualReturn, c.StartCost, c.BuybackCost, c.Closed)
}

// ToXML function encodes contract to xml and write it to file.
func (c Contract) ToXML(filepath string) error {
	b, err := xml.MarshalIndent(c, "", " ")
	if err != nil {
		return err
	}
	b = append(b, '\n')

	file, err := os.OpenFile(filepath, os.O_APPEND|os.O_CREATE|os.O_WRONLY, 0644)
	if err != nil {
		return err
	}
	defer file.Close()

	if _, err := file.Write(b); err != nil {
		return err
	}

	return nil
}
