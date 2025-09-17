package handle_columns_things

import (
	"database/sql"
	"errors"
	"example/SIDE_SERVICE/n_database_deal/normalize"
	"fmt"
	"reflect"
)

// remember to check values and columns if they match about quantity , if not , then please check before use this functiton
func CheckColumn_avaiable(db *sql.DB, tableName string, columnss map[string]int, values []interface{}) (error, []string) {
	fmt.Printf("%d", len(columnss))
	fmt.Printf("%d", len(values))

	if len(columnss) != len(values) {

		return errors.New(" values  and columns don't match about quantity "), nil
	}

	//argType := reflect.TypeOf(column_value_check_type)
	//fmt.Println("Type of value : ", argType)
	typee := make([]string, 0, len(values))

	query := fmt.Sprintf("PRAGMA table_info(%s);", tableName)

	fmt.Println(tableName)
	// Execute the query
	rows, err := db.Query(query)
	if err != nil {
		fmt.Println(" cannot  query")
		return err, nil
	}

	defer rows.Close()

	for rows.Next() {
		var pk int
		var cid int
		var name string
		var colType string
		var notnull int
		var dfltValue interface{}

		err := rows.Scan(&cid, &name, &colType, &notnull, &dfltValue, &pk)
		if err != nil {
			return err, nil
		}

		_, exist := columnss[name]
		if exist {
			argType := reflect.TypeOf(values[columnss[name]])
			if normalize.Normalize_type_for_data_variable(argType.String()) != normalize.Normalize_type_for_sqlite_columns(colType) {
				fmt.Printf(" name la \n%s", name)
				fmt.Printf("col type la \n %s", colType)
				fmt.Printf("arg type sau khi normalize %s", normalize.Normalize_type_for_data_variable(argType.String()))
				fmt.Printf(" coltype sau khi normalize %s", normalize.Normalize_type_for_sqlite_columns(colType))
				return errors.New(" type of value  and type of column didn't match each other \n "), nil
			}

			fmt.Printf(" type la \n")
			fmt.Printf(colType)
			typee = append(typee, normalize.Normalize_type_for_sqlite_columns(colType))

			fmt.Printf(" type sau khi bien doi la \n")

			fmt.Println(typee)
		}

	}

	return nil, typee

}
