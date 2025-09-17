package n_database_deal

import (
	"database/sql"
	"errors"
	n_enum "example/N_ENUM"
	"example/SIDE_SERVICE/n_database_deal/handle_columns_things"
	"fmt"
	"log"

	_ "github.com/mattn/go-sqlite3"
)

func tableExists(db *sql.DB, tableName string) (bool, error) {
	var exists bool
	query := `SELECT COUNT(*) FROM sqlite_master WHERE type='table' AND name=?;`
	err := db.QueryRow(query, tableName).Scan(&exists)
	return exists, err
}

// this function read if values in columns actually match or not , but not return every values
func IF_that_data_have_in_database(db *sql.DB, table_name string, columns []string, values ...interface{}) error {
	exists, err := tableExists(db, table_name)
	if err != nil {
		log.Fatal(err)
	}
	if exists {
		fmt.Printf("Table '%s' exists.\n", table_name)

	} else {
		fmt.Printf("Table '%s' does not exist.\n", table_name)
		return errors.New("Table does not exist.\n")
	}
	map_columns := make(map[string]int)

	for i := 0; i < len(columns); i++ {
		map_columns[columns[i]] = i
	}

	slice_values := make([]interface{}, 0)

	for i := 0; i < len(values); i++ {
		slice_values = append(slice_values, values[i])
	}

	err, array_type := handle_columns_things.CheckColumn_avaiable(db, table_name, map_columns, slice_values) // you just need use this when the table is not strict about type , use this to ensure type of values match with type of columns

	if err != nil {

		fmt.Printf(" some error happens at check column avaiable")
		return err
	}

	fmt.Printf("before check if values %d %d", len(columns), len(slice_values))
	err = handle_columns_things.Checkifvalues_avaiable(db, table_name, columns, slice_values, array_type)

	if err != nil {
		//fmt.Printf("Loi xay ra sau handle_columns_things.Checkifvalues_avaiable ")
		//log.Fatal(err)
		return err
	}

	return nil
}

// this function check if values input match any rows of table , and then return every row that match , and their  data
func If_those_data_have_in_database_and_return_their_rows(db *sql.DB, table_name string, columns []string, values ...interface{}) (int, *[][]string, error) {
	exists, err := tableExists(db, table_name)
	if err != nil {
		log.Fatal(err)
	}
	if exists {
		fmt.Printf("Table '%s' exists.\n", table_name)

	} else {
		fmt.Printf("Table '%s' does not exist.\n", table_name)
		return 0, nil, errors.New("Table does not exist.\n")
	}
	map_columns := make(map[string]int)

	for i := 0; i < len(columns); i++ {
		map_columns[columns[i]] = i
	}

	slice_values := make([]interface{}, 0)

	for i := 0; i < len(values); i++ {
		slice_values = append(slice_values, values[i])
	}

	err, array_type := handle_columns_things.CheckColumn_avaiable(db, table_name, map_columns, slice_values) // you just need use this when the table is not strict about type , use this to ensure type of values match with type of columns

	if err != nil {

		fmt.Printf(" some error happens at check column avaiable")
		return 0, nil, err
	}

	//err = handle_columns_things.Checkifvalues_avaiable(db, table_name, columns, slice_values, array_type)

	columns_count, data, err2 := handle_columns_things.Checkifvalues_avaiable_and_return_their_rows(db, table_name, columns, slice_values, array_type)
	if err2 != nil {
		//fmt.Printf("Loi xay ra sau handle_columns_things.Checkifvalues_avaiable ")
		//log.Fatal(err)
		return columns_count, nil, err2
	}

	return columns_count, data, nil
}

func check_if_columns_match_values(columns []string, values ...interface{}) error {

	if len(columns) != len(values) {

		fmt.Printf("%d\n", len(columns))
		fmt.Printf("%d\n", len(values))
		return errors.New(" vvvvvalues  and columns don't match about quantity ")
	}

	return nil
}

func join(s []string, sep string) string {
	result := ""
	for i, str := range s {
		if i != 0 {
			result += sep
		}
		result += str
	}
	return result
}

func Action_to_database_CRUD(username *string, id *string, role *string, table_name string, database_name string, database_driver string, crud n_enum.CRUD, columns []string, values ...interface{}) error {

	var err error
	var db *sql.DB

	fmt.Printf("%d\n", len(columns))
	fmt.Printf("%d\n", len(values))

	err = check_if_columns_match_values(columns, values...)

	if err != nil {
		return err
	}
	db, err = sql.Open(database_driver, database_name)
	if err != nil {
		log.Fatal(err)
	}
	defer db.Close()

	switch crud {

	case n_enum.Create:
		fmt.Println("Performing Create operation")

	case n_enum.Update:
		fmt.Println("Performing Update operation")

	case n_enum.Read:
		fmt.Println("Performing Read operation")
		err = IF_that_data_have_in_database(db, table_name, columns, values...)
		if err != nil {
			//log.Fatal(err)
			return err
		} else {

			//find_a_specific_Column( )

			/*
				row := db.QueryRow("SELECT role FROM user WHERE username = ?")
				var aes_key string
				err = row.Scan(&aes_key)
			*/

			fmt.Printf(" everything is fine")

		}
	case n_enum.Delete:
		fmt.Println("Performing Delete operation")
	}

	//err := if_that_data_have_in_database(db, table_name)
	return nil
}

func find_a_specific_Column(columns []string, column_you_want_to_find string) string {
	for _, column := range columns {
		if column == column_you_want_to_find { // Khớp chính xác
			return column
		}
	}
	return "" // Trả về chuỗi rỗng nếu không tìm thấy
}

func Take_every_row_match_those_input(db *sql.DB, table_name string, columns []string, values ...interface{}) (int, *[][]string, error) {

	var err error

	fmt.Printf("%d\n", len(columns))
	fmt.Printf("%d\n", len(values))

	err = check_if_columns_match_values(columns, values...)
	if err != nil {
		return 0, nil, err
	}

	fmt.Println("Performing Read operation")

	var columns_num int
	var data *[][]string
	columns_num, data, err = If_those_data_have_in_database_and_return_their_rows(db, table_name, columns, values...)
	if err != nil {
		//log.Fatal(err)
		return 0, nil, err
	} else {
		fmt.Printf(" everything is fine")
	}

	return columns_num, data, nil
}
