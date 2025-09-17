package BUTTON_UPLINK_CURRENT_STATE

type button_uplink_current_state int

type button_uplink_current_state_string string

const Button_Columns_length_defined = 4
const columns_number_need_to_Be_add_when_insertion_happens = 2

// enum for getting data from the one_for_all_query
const (
	ID_OF_BUTTON_COLUMNS_UPLINK_CURRENT_STATE            button_uplink_current_state = 0
	NODE_ADRESS_OF_BUTTON_COLUMNS_UPLINK_CURRENT_STATE   button_uplink_current_state = 1
	RAW_DATA_OF_BUTTON_COLUMNS_UPLINK_CURRENT_STATE      button_uplink_current_state = 2
	RECEIVED_DATE_OF_BUTTON_COLUMNS_UPLINK_CURRENT_STATE button_uplink_current_state = 3
)

const (
	ID_OF_BUTTON_COLUMNS_UPLINK_CURRENT_STATE_STRING            button_uplink_current_state_string = "id"
	NODE_ADRESS_OF_BUTTON_COLUMNS_UPLINK_CURRENT_STATE_STRING   button_uplink_current_state_string = "node_address"
	RAW_DATA_OF_BUTTON_COLUMNS_UPLINK_CURRENT_STATE_STRING      button_uplink_current_state_string = "current_button_pressed"
	RECEIVED_DATE_OF_BUTTON_COLUMNS_UPLINK_CURRENT_STATE_STRING button_uplink_current_state_string = "latest_received_date"
)

// enum for get string of that column in order to sprintf query

/*
var BUTTON_UPLINK_CURRENT_STATE_array = []button_uplink_current_state_string{

	ID_OF_BUTTON_COLUMNS_UPLINK_CURRENT_STATE_STRING,
	NODE_ADRESS_OF_BUTTON_COLUMNS_UPLINK_CURRENT_STATE_STRING,
	RAW_DATA_OF_BUTTON_COLUMNS_UPLINK_CURRENT_STATE_STRING,
	RECEIVED_DATE_OF_BUTTON_COLUMNS_UPLINK_CURRENT_STATE_STRING,
}

*/

func GetBUTTONUPLINK_INSERTION_Columns() []button_uplink_current_state_string {
	return []button_uplink_current_state_string{

		NODE_ADRESS_OF_BUTTON_COLUMNS_UPLINK_CURRENT_STATE_STRING,
		RAW_DATA_OF_BUTTON_COLUMNS_UPLINK_CURRENT_STATE_STRING,
	}
}

func GetBUTTONUPLINK_UPDATE_Columns() []button_uplink_current_state_string {
	return []button_uplink_current_state_string{

		//NODE_ADRESS_OF_BUTTON_COLUMNS_UPLINK_CURRENT_STATE_STRING,
		RAW_DATA_OF_BUTTON_COLUMNS_UPLINK_CURRENT_STATE_STRING,
	}
}

const (
	BUTTON_UPLINK_CURRENT_STATE_TABLE_NAME button_uplink_current_state_string = "BUTTON_UPLINK_CURRENT_STATE"
)
