package handle_columns_things

import (
	"database/sql"
	"errors"
	"fmt"
)

//remember to check values and columns if they match about quantity , if not , then please check before use this function

func Checkifvalues_avaiable(db *sql.DB, tableName string, columnss []string, values []interface{}, typee []string) error {

	if len(columnss) == 0 || len(values) == 0 {
		return errors.New(" column or values have length equal to 0 , which mean illegal for this function")
	}

	slice_values := make([]interface{}, 0)

	for i := 0; i < len(values); i++ {
		slice_values = append(slice_values, values[i])
	}

	if len(columnss) != len(slice_values) {
		return errors.New(" values  and columns don't match about quantity ")
	}

	switch len(columnss) {
	case 1:
		//fmt.Printf(fmt.Sprintf("SELECT COUNT(1) FROM %s WHERE %s = %s", tableName, columnss[0], values[0]))

		var query string
		switch values[0].(type) {

		case string:

			query = fmt.Sprintf("SELECT COUNT(1) FROM %s WHERE %s = %s", tableName, columnss[0], values[0])
		case int:
			query = fmt.Sprintf("SELECT COUNT(1) FROM %s WHERE %s = %d", tableName, columnss[0], values[0])

		}

		fmt.Println(query)
		var count int
		err := db.QueryRow(query).Scan(&count)
		if err != nil {
			return err
		}
	default:
		var count int
		var and string = " AND"

		var query string
		switch values[0].(type) {

		case string:
			if typee[0] == "string" {
				query = fmt.Sprintf("SELECT COUNT(1) FROM %s WHERE %s = '%s'", tableName, columnss[0], values[0])

			} else {
				query = fmt.Sprintf("SELECT COUNT(1) FROM %s WHERE %s = %s", tableName, columnss[0], values[0])
			}

			break

		case int:
			if typee[0] == "string" {
				query = fmt.Sprintf("SELECT COUNT(1) FROM %s WHERE %s = '%d'", tableName, columnss[0], values[0])

			} else {
				query = fmt.Sprintf("SELECT COUNT(1) FROM %s WHERE %s = %d", tableName, columnss[0], values[0])
			}

			break

		}
		for i := 1; i < len(columnss); i++ {
			var new_pair string
			if typee[i] == "string" {
				new_pair = fmt.Sprintf(" %s = '%s'", columnss[i], values[i])
				fmt.Println(" happens in default ")
				fmt.Println(new_pair)
			} else {
				new_pair = fmt.Sprintf(" %s = %s", columnss[i], values[i])
				fmt.Println(new_pair)
			}
			query = query + and + new_pair
			fmt.Println(query)
			if i == len(columnss)-1 {
				query = query + ";"
			}
		}
		fmt.Printf(query)
		err := db.QueryRow(query).Scan(&count)

		if err != nil {

			fmt.Printf(" error at default state \n")
			return err
		}

		if count > 0 {

			fmt.Printf(" it does have specific ")

		}
		if count == 0 {
			fmt.Printf(" khong co gi ca ?")
			return errors.New(" ")
		}

	}

	return nil

}

func Checkifvalues_avaiable_and_return_their_rows(db *sql.DB, tableName string, columnss []string, values []interface{}, typee []string) (int, *[][]string, error) {
	fmt.Printf(" now will check count of columns , hehe \n")

	//  lay so luong cot truoc
	columns_num, err_col := GetColumnCount(db, tableName)

	if err_col != nil {
		fmt.Printf(err_col.Error())
		return 0, nil, err_col
	}

	if len(columnss) == 0 || len(values) == 0 {
		return 0, nil, errors.New(" column or values have length equal to 0 , which mean illegal for this function")

	}

	slice_values := make([]interface{}, 0)

	for i := 0; i < len(values); i++ {
		slice_values = append(slice_values, values[i])
	}

	if len(columnss) != len(slice_values) {

		return 0, nil, errors.New(" values  and columns don't match about quantity ")
	}

	switch len(columnss) {
	case 1:
		//fmt.Printf(fmt.Sprintf("SELECT COUNT(1) FROM %s WHERE %s = %s", tableName, columnss[0], values[0]))

		var query string
		switch values[0].(type) {

		case string:

			if typee[0] == "string" {
				query = fmt.Sprintf("SELECT * FROM %s WHERE %s = '%s';", tableName, columnss[0], values[0])
			} else {

				query = fmt.Sprintf("SELECT * FROM %s WHERE %s = %s;", tableName, columnss[0], values[0])

			}

		case int:
			if typee[0] == "string" {
				query = fmt.Sprintf("SELECT * FROM %s WHERE %s = '%d';", tableName, columnss[0], values[0])
			} else {

				query = fmt.Sprintf("SELECT * FROM %s WHERE %s = %d;", tableName, columnss[0], values[0])

			}
		}

		fmt.Println(query)
		//var count int

		rows, err_rows := db.Query(query)
		//err := db.QueryRow(query).Scan(&count)
		if err_rows != nil {
			return 0, nil, err_rows
		}
		var result [][]string
		for rows.Next() {
			values := make([]interface{}, columns_num)

			valuesPtr := make([]interface{}, columns_num)
			for i := range values {
				valuesPtr[i] = &values[i]
			}
			err_deobiet := rows.Scan(valuesPtr...)
			if err_deobiet != nil {
				fmt.Printf("error \n")
				return columns_num, nil, err_deobiet
			}
			row_values := make([]string, columns_num)
			for i, val := range values {
				if val == nil {
					row_values[i] = "NULL"
				} else {
					row_values[i] = fmt.Sprintf("%v", val)
				}
			}
			result = append(result, row_values)
		}

		return columns_num, &result, nil

		//	return 1,

	default:

		var and string = " AND"

		var query string
		switch values[0].(type) {

		case string:
			if typee[0] == "string" {
				query = fmt.Sprintf("SELECT * FROM %s WHERE %s = '%s'", tableName, columnss[0], values[0])

			} else {
				query = fmt.Sprintf("SELECT * FROM %s WHERE %s = %s ", tableName, columnss[0], values[0])
			}

			break

		case int:
			if typee[0] == "string" {
				query = fmt.Sprintf("SELECT * FROM %s WHERE %s = '%d' ", tableName, columnss[0], values[0])

			} else {
				query = fmt.Sprintf("SELECT * FROM %s WHERE %s = %d ", tableName, columnss[0], values[0])
			}

			break

		default:

			fmt.Printf(" fukcing default \n")

		}
		for i := 1; i < len(columnss); i++ {
			var new_pair string
			switch values[i].(type) {
			case string:
				if typee[i] == "string" {
					new_pair = fmt.Sprintf(" %s = '%s'", columnss[i], values[i])
					fmt.Println(" happens in default ")
					fmt.Println(new_pair)
				} else {
					new_pair = fmt.Sprintf(" %s = %s ", columnss[i], values[i])
					fmt.Println(new_pair)
				}
				query = query + and + new_pair
				fmt.Println(query)
				if i == len(columnss)-1 {
					query = query + ";"
				}
				break
			case int:

				if typee[i] == "string" {
					new_pair = fmt.Sprintf(" %s = '%d'", columnss[i], values[i])
					fmt.Println(" happens in default ")
					fmt.Println(new_pair)
				} else {
					new_pair = fmt.Sprintf(" %s = %d ", columnss[i], values[i])
					fmt.Println(new_pair)
				}
				query = query + and + new_pair
				fmt.Println(query)
				if i == len(columnss)-1 {
					query = query + ";"
				}
				break
			default:
				fmt.Printf(" fucking default \n")

			}
		}

		fmt.Printf(query)

		rows, err_rows := db.Query(query)
		if err_rows != nil {
			fmt.Printf(err_rows.Error())
			return columns_num, nil, err_rows

		}

		var result [][]string

		for rows.Next() {
			values := make([]interface{}, columns_num)

			valuesPtr := make([]interface{}, columns_num)

			for i := range values {
				valuesPtr[i] = &values[i]
			}
			err_deobiet := rows.Scan(valuesPtr...)
			if err_deobiet != nil {
				fmt.Printf("error \n")
				return columns_num, nil, err_deobiet
			}
			row_values := make([]string, columns_num)
			for i, val := range values {
				if val == nil {
					row_values[i] = "NULL"
				} else {
					row_values[i] = fmt.Sprintf("%v", val)
				}
			}
			result = append(result, row_values)
		}
		return columns_num, &result, nil
	}

	return 0, nil, fmt.Errorf(" loi khong xac dinh \n")
}

func getColumnCount(db *sql.DB, tableName string) (int, error) {
	// Truy vấn PRAGMA table_info
	rows, err := db.Query("PRAGMA table_info(" + tableName + ")")
	if err != nil {
		return 0, fmt.Errorf("failed to get table info: %v", err)
	}
	defer rows.Close()

	// Đếm số cột
	count := 0
	for rows.Next() {
		count++
	}
	if count == 0 {
		return 0, fmt.Errorf("table %s does not exist or has no columns", tableName)
	}
	return count, nil
}
