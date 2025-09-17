package db_class

import (
	"database/sql"

	_ "github.com/mattn/go-sqlite3"
)

type database struct {
	database_object *sql.DB

	driver string

	database_file string
}

func (db *database) Get_database_object() *sql.DB {

	return db.database_object

}

func (db *database) Get_driver() string {

	return db.driver
}

func (db *database) Get_database_file() string {

	return db.database_file

}

/*
	func (db *database) set_database_object() error {
		var err error
		db.database_object, err = sql.Open(db.driver, db.database_file)
		if err != nil {
			log.Fatal(err)
			return err
		}
		return nil
	}
*/

func (db *database) Set_driver(driverr string) {

	db.driver = driverr

}

func (db *database) Set_database_file(database_filess string) {

	db.database_file = database_filess

}

func NewDatabase(driver, databaseFile string) *database {

	db := &database{
		driver:        driver,
		database_file: databaseFile,
	}

	// Initialize the database connection

	return db
}
