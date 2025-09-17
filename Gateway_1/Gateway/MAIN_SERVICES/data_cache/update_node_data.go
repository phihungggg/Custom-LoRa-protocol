package data_cache

import (
	"bytes"
	"database/sql"
	"encoding/binary"
	"errors"
	"fmt"
	"log"

	//"errors"
	"example/SIDE_SERVICE/n_database_deal"
	"example/SIDE_SERVICE/n_database_deal/n_enum_database_deal"
	"example/SIDE_SERVICE/n_database_deal/n_enum_database_deal/ADC_NODE_CURRENT_STATE"

	//"example/SIDE_SERVICE/n_database_deal/n_enum_database_deal/ADC_node"
	"example/SIDE_SERVICE/n_database_deal/n_enum_database_deal/BUTTON_DOWNLINK_CURRENT_STATE"
	"example/SIDE_SERVICE/n_database_deal/n_enum_database_deal/BUTTON_UPLINK_CURRENT_STATE"
	"example/SIDE_SERVICE/n_database_deal/n_enum_database_deal/node_authentication_key"
	"example/SIDE_SERVICE/n_database_deal/n_enum_database_deal/node_downlink_data_history"
	"example/SIDE_SERVICE/n_database_deal/n_enum_database_deal/node_list_enum_state"
	"example/SIDE_SERVICE/n_database_deal/n_enum_database_deal/node_map"
	"example/SIDE_SERVICE/n_database_deal/n_enum_database_deal/node_uplink_data_history"
	"example/SIDE_SERVICE/n_database_deal/n_enum_database_deal/user_data_enum"
	"example/SIDE_SERVICE/random_bsht_libs"
	"example/SIDE_SERVICE/tunnel"
	"strings"
)

// take node_list rows
func Update_node_data(db *sql.DB, Tunnel tunnel.Tunnel_of_table_in_database_sqlite3, raw_data []byte) {

	fmt.Println("  update node data ")
	node_id, err := random_bsht_libs.ConvertNodeID_from_string_to_id((*Tunnel.Data_get)[0][node_list_enum_state.NODE_ID_OF_NODE_LIST]) // lay id tu tunnel cua stack truoc

	node_address := (*Tunnel.Data_get)[0][node_list_enum_state.NODE_ADDRESS_OF_NODE_LIST]

	if err != nil {
		fmt.Printf(err.Error())
		return
	}
	_, dataget, errr := n_database_deal.Take_every_row_match_those_input(db, "node_map", []string{"node_id"}, node_id) // lay mot row  trong node map khop voi node id cu the
	if errr != nil {
		fmt.Printf(errr.Error())
		return
	}

	node_name := (*dataget)[0][node_map.NODE_NAME_OF_NODE_MAP]

	table_to_request := ham_tao_chuoi_de_dan_toi_bang_can_thiet_CURRENT_STATE(node_name)
	fmt.Println(" ben duoi ham tao chuoi ")
	fmt.Println(table_to_request)
	clm_arrs, errr4 := chose_appropriate_columns_based_on_table_for_UPDATE(table_to_request)
	if errr4 != nil {
		fmt.Printf(errr4.Error())
		return
	}
	fmt.Println(" ben duoi ham chon cot  ")

	querystring, errr2 := taoquery_UPDATE(table_to_request, clm_arrs[:], "node_address=?")
	if errr2 != nil {
		fmt.Printf(errr2.Error())
		return
	}
	fmt.Println(" ben duoi ham  tao query   ")
	querystring = strings.Replace(querystring, " WHERE", ", receive_date = DATETIME('now','localtime') WHERE", 1)
	fmt.Println(" ben duoi ham  replace   ")
	{

		var parameter_slice []interface{}
		if table_to_request == string(ADC_NODE_CURRENT_STATE.ADC_NODE_TABLE_NAME) {
			if len(raw_data) == 4 {

				f := bytesToFloat32(raw_data)
				fmt.Println("ADC NODE CURRENT STATE")

				//fmt.Println("ADC NODE CURRENT STATE")
				parameter_slice = make([]interface{}, 2)
				parameter_slice[0] = f
				parameter_slice[1] = node_address

			} else {
				fmt.Printf(" raw data of adc node is wrong about length \n")
				fmt.Println(len(raw_data))
				return
			}

		} else if table_to_request == string(BUTTON_UPLINK_CURRENT_STATE.BUTTON_UPLINK_CURRENT_STATE_TABLE_NAME) {

			fmt.Println("BUTTON UPLINK CURRENT STATE")
			parameter_slice = make([]interface{}, 2)

			parameter_slice[0] = raw_data[0]
			parameter_slice[1] = node_address

		}

		fmt.Println(" query string 1")

		fmt.Println(querystring)

		_, errss := db.Exec(querystring, parameter_slice...)

		if errss != nil {
			// xử lý lỗi ở đây
			log.Printf("Exec failed: %v", errss)
			return
		}
	}

	//end of update current state table

	// now insert_data_into uplink_history

	uplink_table_name := string(node_uplink_data_history.NODE_UPLINK_DATA_HISTORY_TABLE_NAME)
	var clm_arrs_uplink_history []string

	clm_arrs_uplink_history, errr = chose_appropriate_columns_based_on_table_for_INSERTION(uplink_table_name)

	querystring_uplink, err3 := taoquery_INSERTION(uplink_table_name, clm_arrs_uplink_history[:])
	if err3 != nil {
		fmt.Printf(err3.Error())
		return
	}

	{
		var parameter_slice []interface{}

		raw_data, err := BytesToUint32BE(raw_data)

		if err != nil {

			fmt.Printf(err.Error())
			return
		}
		parameter_slice = make([]interface{}, 2)

		parameter_slice[0] = node_address
		parameter_slice[1] = raw_data

		fmt.Println(" query string 2")

		fmt.Println(querystring_uplink)

		_, erss2 := db.Exec(querystring_uplink, parameter_slice...)

		if erss2 != nil {
			// xử lý lỗi ở đây
			log.Printf("Exec failed: %v", erss2)
			return
		}

	}

}

func ham_tao_chuoi_de_dan_toi_bang_can_thiet_CURRENT_STATE(input string) string {
	current_state := "_CURRENT_STATE"
	result := input + current_state
	return result
}

func taoquery_UPDATE(table string, clmArr []string, where string) (string, error) {
	if len(clmArr) == 0 {
		return "", fmt.Errorf("column list must be non-empty")
	}
	if strings.TrimSpace(where) == "" {
		return "", fmt.Errorf("WHERE clause is required to avoid updating all rows")
	}

	// Tạo phần SET với placeholder
	setParts := make([]string, len(clmArr))
	for i, col := range clmArr {
		setParts[i] = fmt.Sprintf("%s = ?", col)
	}
	setClause := strings.Join(setParts, ", ")

	// Ghép câu lệnh SQL
	query := fmt.Sprintf("UPDATE %s SET %s WHERE %s", table, setClause, where)

	return query, nil
}

func taoquery_INSERTION(table string, clmArr []string) (string, error) {
	if len(clmArr) == 0 {
		return "", fmt.Errorf("column count and data count must match and be non-zero")
	}

	// Tạo chuỗi cột
	columns := strings.Join(clmArr, ", ")

	placeholders := strings.Repeat("?,", len(clmArr))
	placeholders = strings.TrimRight(placeholders, ",")

	// Ghép câu lệnh SQL
	query := fmt.Sprintf("INSERT INTO %s (%s) VALUES (%s)", table, columns, placeholders)

	return query, nil
}

// đây là 3 func cơ bản khi update data của một node trong database, còn cơ bản hơn nữa thì chỉ có update uplink hay downlink history ,

// ham nay de cap nhat mac dinh gia tri cho cac node chua co name trong bang node_map
//func update_unnamed_node_CURRENT_STATE() {

//func update_specific_node_CURRENT_STATE() {

func update_uplink_history() {

}

func update_downlink_history() {

}

//

// ham nay phucc vu cho operate
/*
func gan_table_names_cho_clm_arrs(input []interface{}) []string {
	clm_arrs := make([]string, len(input))

	for i, v := range input {

		clm_arrs[i] = string(v)

	}

	return clm_arrs
}
*/

// de su dung func nay , phai lien ket voi

func chose_appropriate_columns_based_on_table_for_INSERTION(input_string string) ([]string, error) {

	is_correct_table_names := false
	tables := n_enum_database_deal.All_data_tables_name
	for _, value := range tables {

		if value == input_string {
			is_correct_table_names = true
			break
		}
	}
	if is_correct_table_names == false {

		return nil, errors.New("not_correct\n")
	}

	var clm_arrs []string
	switch input_string {
	case string(ADC_NODE_CURRENT_STATE.ADC_NODE_TABLE_NAME):
		slice := ADC_NODE_CURRENT_STATE.GetADCNode_INSERTION_Columns()
		clm_arrs = make([]string, len(slice))
		for i, v := range slice {
			clm_arrs[i] = string(v)
		}
	case BUTTON_DOWNLINK_CURRENT_STATE.BUTTON_DOWNLINK_CURRENT_STATE_TABLE_NAME:
		slice := BUTTON_DOWNLINK_CURRENT_STATE.BUTTON_DOWNLINK_CURRENT_STATE_array[:]
		clm_arrs = make([]string, len(slice))
		for i, v := range slice {
			clm_arrs[i] = string(v)
		}
	case string(BUTTON_UPLINK_CURRENT_STATE.BUTTON_UPLINK_CURRENT_STATE_TABLE_NAME):
		slice := BUTTON_UPLINK_CURRENT_STATE.GetBUTTONUPLINK_INSERTION_Columns()
		clm_arrs = make([]string, len(slice))
		for i, v := range slice {
			clm_arrs[i] = string(v)
		}
	case string(node_authentication_key.AUTHENTICATION_KEY_STRING):
		slice := node_authentication_key.Node_authentication_key_array[:]
		clm_arrs = make([]string, len(slice))
		for i, v := range slice {
			clm_arrs[i] = string(v)
		}
	case string(node_downlink_data_history.NODE_DOWNLINK_DATA_HISTORY_TABLE_NAME):
		slice := node_downlink_data_history.Node_downlink_data_history_array[:]
		clm_arrs = make([]string, len(slice))
		for i, v := range slice {
			clm_arrs[i] = string(v)
		}
	case string(node_list_enum_state.NODE_LIST_TABLE_NAME):
		slice := node_list_enum_state.Node_list_enum_state_array[:]
		clm_arrs = make([]string, len(slice))
		for i, v := range slice {
			clm_arrs[i] = string(v)
		}
	case string(node_uplink_data_history.NODE_UPLINK_DATA_HISTORY_TABLE_NAME):
		slice := node_uplink_data_history.GetNODEUPLINK_INSERTION_Columns()
		clm_arrs = make([]string, len(slice))
		for i, v := range slice {
			clm_arrs[i] = string(v)
		}
	case user_data_enum.User_table_name:
		slice := user_data_enum.User_array[:]
		clm_arrs = make([]string, len(slice))
		for i, v := range slice {
			clm_arrs[i] = string(v)
		}
	}
	return clm_arrs, nil
}

func chose_appropriate_columns_based_on_table_for_UPDATE(input_string string) ([]string, error) {

	is_correct_table_names := false
	tables := n_enum_database_deal.All_data_tables_name
	for _, value := range tables {

		if value == input_string {
			is_correct_table_names = true
			break
		}
	}
	if is_correct_table_names == false {

		return nil, errors.New("not_correct\n")
	}

	var clm_arrs []string
	switch input_string {
	case string(ADC_NODE_CURRENT_STATE.ADC_NODE_TABLE_NAME):
		slice := ADC_NODE_CURRENT_STATE.GetADCNode_UPDATE_Columns()
		clm_arrs = make([]string, len(slice))
		for i, v := range slice {
			clm_arrs[i] = string(v)
		}

	case string(BUTTON_UPLINK_CURRENT_STATE.BUTTON_UPLINK_CURRENT_STATE_TABLE_NAME):
		slice := BUTTON_UPLINK_CURRENT_STATE.GetBUTTONUPLINK_UPDATE_Columns()
		clm_arrs = make([]string, len(slice))
		for i, v := range slice {
			clm_arrs[i] = string(v)
		}

	case string(node_uplink_data_history.NODE_UPLINK_DATA_HISTORY_TABLE_NAME):
		slice := node_uplink_data_history.GetNODEUPLINK_UPDATE_Columns()
		clm_arrs = make([]string, len(slice))
		for i, v := range slice {
			clm_arrs[i] = string(v)
		}

	}
	return clm_arrs, nil
}

func bytesToFloat32(b []byte) float32 {
	var f float32
	// Nếu dữ liệu là little endian:
	binary.Read(bytes.NewReader(b), binary.LittleEndian, &f)
	return f
}

func BytesToUint32BE(b []byte) (uint32, error) {
	if len(b) < 4 {
		return 0, fmt.Errorf("need 4 bytes, got %d", len(b))
	}
	return binary.BigEndian.Uint32(b[:4]), nil
}
