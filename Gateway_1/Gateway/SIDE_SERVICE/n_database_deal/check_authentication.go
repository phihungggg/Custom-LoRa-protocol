package n_database_deal

import (
	"bytes"
	"database/sql"
	"errors"
	"fmt"

	"example/SIDE_SERVICE/random_bsht_libs"
)

func Check_authentication(authentication_key []byte, db *sql.DB, table_name string, node_address string, column_to_get string) error {
	query := fmt.Sprintf("SELECT %s FROM %s WHERE node_address = ?", column_to_get, table_name)
	row := db.QueryRow(query, node_address)

	var authentication_key_get string
	err := row.Scan(&authentication_key_get)
	if err != nil {

		fmt.Printf(err.Error())

		return err
	}
	
	var bytes_of_authentication_key_get []byte
	bytes_of_authentication_key_get, err = random_bsht_libs.HexStringToByteArray(authentication_key_get)

	if err != nil {

		fmt.Printf(err.Error())

		return err
	}
	if bytes.Equal(authentication_key, bytes_of_authentication_key_get) {
		fmt.Println("Authentication key matched!")
	} else {
		fmt.Println("Authentication key does not match.")
		return errors.New("authentication key mismatch")

	}
	return nil
}
