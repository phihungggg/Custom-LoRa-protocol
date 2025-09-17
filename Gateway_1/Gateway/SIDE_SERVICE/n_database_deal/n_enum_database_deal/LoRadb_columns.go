package n_enum_database_deal

import (
	"example/SIDE_SERVICE/n_database_deal/n_enum_database_deal/ADC_NODE_CURRENT_STATE"
	"example/SIDE_SERVICE/n_database_deal/n_enum_database_deal/BUTTON_DOWNLINK_CURRENT_STATE"
	"example/SIDE_SERVICE/n_database_deal/n_enum_database_deal/BUTTON_UPLINK_CURRENT_STATE"
	"example/SIDE_SERVICE/n_database_deal/n_enum_database_deal/node_authentication_key"
	"example/SIDE_SERVICE/n_database_deal/n_enum_database_deal/node_downlink_data_history"
	"example/SIDE_SERVICE/n_database_deal/n_enum_database_deal/node_list_enum_state"
	"example/SIDE_SERVICE/n_database_deal/n_enum_database_deal/node_uplink_data_history"
	"example/SIDE_SERVICE/n_database_deal/n_enum_database_deal/user_data_enum"
)

var columns_nums = 10

type N_database_object struct {
	howmany_tables int

	something []string
}

var All_data_tables_name = []string{
	string(ADC_NODE_CURRENT_STATE.ADC_NODE_TABLE_NAME),
	string(BUTTON_DOWNLINK_CURRENT_STATE.BUTTON_DOWNLINK_CURRENT_STATE_TABLE_NAME),
	string(BUTTON_UPLINK_CURRENT_STATE.BUTTON_UPLINK_CURRENT_STATE_TABLE_NAME),
	string(node_authentication_key.NODE_AUTHENTICATION_KEY_TABLE_NAME),
	string(node_downlink_data_history.NODE_DOWNLINK_DATA_HISTORY_TABLE_NAME),
	string(node_list_enum_state.NODE_LIST_TABLE_NAME),
	string(node_uplink_data_history.NODE_UPLINK_DATA_HISTORY_TABLE_NAME),
	string(user_data_enum.User_table_name),
}
