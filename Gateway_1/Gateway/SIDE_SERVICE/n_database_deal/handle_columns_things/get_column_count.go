package handle_columns_things

import (
	"database/sql"
	"fmt"

	_ "github.com/mattn/go-sqlite3"
)

func GetColumnCount(db *sql.DB, tableName string) (int, error) {
	query := fmt.Sprintf("PRAGMA table_info(%s);", tableName)

	rows, err := db.Query(query)
	if err != nil {
		return 0, err
	}
	defer rows.Close()

	count := 0
	for rows.Next() {
		count++
	}

	return count, nil
}
