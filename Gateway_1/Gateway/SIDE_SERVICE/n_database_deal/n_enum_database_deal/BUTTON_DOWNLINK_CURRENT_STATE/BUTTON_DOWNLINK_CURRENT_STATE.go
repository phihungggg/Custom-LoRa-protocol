package BUTTON_DOWNLINK_CURRENT_STATE

type button_downlink_current_state int
type button_downlink_current_state_string string

const Button_Columns_length_defined = 4

// enum for getting data from the one_for_all_query
const (
	ID_OF_BUTTON_COLUMNS_DOWNLINK_CURRENT_STATE            button_downlink_current_state = 0
	NODE_ADRESS_OF_BUTTON_COLUMNS_DOWNLINK_CURRENT_STATE   button_downlink_current_state = 1
	RAW_DATA_OF_BUTTON_COLUMNS_DOWNLINK_CURRENT_STATE      button_downlink_current_state = 2
	RECEIVED_DATE_OF_BUTTON_COLUMNS_DOWNLINK_CURRENT_STATE button_downlink_current_state = 3
)
const (
	ID_OF_BUTTON_COLUMNS_DOWNLINK_CURRENT_STATE_STRING            button_downlink_current_state_string = "id"
	NODE_ADRESS_OF_BUTTON_COLUMNS_DOWNLINK_CURRENT_STATE_STRING   button_downlink_current_state_string = "node_address"
	RAW_DATA_OF_BUTTON_COLUMNS_DOWNLINK_CURRENT_STATE_STRING      button_downlink_current_state_string = "current_button_pressed"
	RECEIVED_DATE_OF_BUTTON_COLUMNS_DOWNLINK_CURRENT_STATE_STRING button_downlink_current_state_string = "latest_received_date"
)





var BUTTON_DOWNLINK_CURRENT_STATE_array = [Button_Columns_length_defined]button_downlink_current_state_string{
	ID_OF_BUTTON_COLUMNS_DOWNLINK_CURRENT_STATE_STRING,
	NODE_ADRESS_OF_BUTTON_COLUMNS_DOWNLINK_CURRENT_STATE_STRING,
	RAW_DATA_OF_BUTTON_COLUMNS_DOWNLINK_CURRENT_STATE_STRING,
	RECEIVED_DATE_OF_BUTTON_COLUMNS_DOWNLINK_CURRENT_STATE_STRING,
}




const (
	BUTTON_DOWNLINK_CURRENT_STATE_TABLE_NAME string = "BUTTON_DOWNLINK_CURRENT_STATE"
)
