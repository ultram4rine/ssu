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
	fmt.Printf("ID: %d\nName: %s\nCost: %d\n", p.ID, p.Name, p.Cost)
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

// Products is a slice of products.
type Products []Product

// Print prints each product in slice.
func (ps Products) Print() {
	for _, p := range ps {
		p.Print()
	}
}

// ToXML encodes slice of products to XML file.
func (ps Products) ToXML(filepath string) error {
	for _, p := range ps {
		if err := p.ToXML(filepath); err != nil {
			return err
		}
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
	fmt.Printf("ID: %d\nName: %s\nPhone: %s\n", c.ID, c.Name, c.Phone)
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

// Customers is a slice of customers.
type Customers []Customer

// Print prints each customer in slice.
func (cs Customers) Print() {
	for _, c := range cs {
		c.Print()
	}
}

// ToXML encodes slice of customers to XML file.
func (cs Customers) ToXML(filepath string) error {
	for _, c := range cs {
		if err := c.ToXML(filepath); err != nil {
			return err
		}
	}
	return nil
}

// Contract struct describes a contract between pawnshop and customer.
type Contract struct {
	ID            int       `xml:"id" db:"id"`
	CustomerID    int       `xml:"customerID" db:"customer_id"`
	Products      []Product `xml:"products"`
	ReturnDate    time.Time `xml:"returnDate" db:"return_date"`
	FactualReturn time.Time `xml:"factualReturn" db:"factual_return_date"`
	StartCost     int       `xml:"startCost" db:"start_cost"`
	BuybackCost   int       `xml:"buybackCost" db:"buyback_cost"`
	Closed        bool      `xml:"closed" db:"closed"`
}

// Print func printing contract to console.
func (c Contract) Print() {
	fmt.Printf("ID: %d\nCustomer ID: %d\nProducts: %v\nReturn date: %v\nFactual return date: %v\nStart cost: %d\nBuyback cost: %d\nClosed: %v\n", c.ID, c.CustomerID, c.Products, c.ReturnDate, c.FactualReturn, c.StartCost, c.BuybackCost, c.Closed)
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

// Contracts is a slice of contracts.
type Contracts []Contract

// Print prints each contract in slice.
func (cs Contracts) Print() {
	for _, c := range cs {
		c.Print()
	}
}

// ToXML encodes slice of contracts to XML file.
func (cs Contracts) ToXML(filepath string) error {
	for _, c := range cs {
		if err := c.ToXML(filepath); err != nil {
			return err
		}
	}
	return nil
}
