package n_database_deal



func normalize_type_for_sqlite_columns(columns_type string) string {
	switch columns_type {

	case "TEXT":
		return "string"

	case "INT":
		return "int"

	case "REAL":
		return "float"

	default:
		return "unknown"

	}
}

func normalize_type_for_data_variable(variable_type string) string {
	switch variable_type {
	case "int", "int8", "int32", "int64", "uint", "uint8", "uint32", "unint64":
		return "int"

	case "float32", "float64":
		return "float"

	case "string":
		return "string"
	default:
		return "unknown"
	}
}
