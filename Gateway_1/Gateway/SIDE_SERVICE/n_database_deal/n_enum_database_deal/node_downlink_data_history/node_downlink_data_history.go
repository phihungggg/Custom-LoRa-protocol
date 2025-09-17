package node_downlink_data_history

type node_downlink_data_history int
type node_downlink_data_history_string string

const Nodedownlink_Columns_length_defined = 4

// enum for getting data from the one_for_all_query
const (
	ID_OF_NODE_DOWNLINK_HISTORY            node_downlink_data_history = 0
	NODE_ADRESS_OF_NODE_DOWNLINK_HISTORY   node_downlink_data_history = 1
	RAW_DATA_OF_NODE_DOWNLINK_HISTORY      node_downlink_data_history = 2
	RECEIVED_DATE_OF_NODE_DOWNLINK_HISTORY node_downlink_data_history = 3
)

// enum for get string of that column in order to sprintf query
const (
	ID_OF_NODE_DOWNLINK_HISTORY_STRING           node_downlink_data_history_string = "id"
	NODE_ADRESS_OF_NODE_DOWNLINK_HISTORY_STRING  node_downlink_data_history_string = "node_address"
	RAW_DATA_OF_NODE_DOWNLINK_HISTORY_STRING     node_downlink_data_history_string = "raw_data"
	RECEIVE_DATE_OF_NODE_DOWNLINK_HISTORY_STRING node_downlink_data_history_string = "receive_date"
)

const (
	NODE_DOWNLINK_DATA_HISTORY_TABLE_NAME node_downlink_data_history_string = "node_authentication_key"
)

var Node_downlink_data_history_array = []node_downlink_data_history_string{
	ID_OF_NODE_DOWNLINK_HISTORY_STRING,
	NODE_ADRESS_OF_NODE_DOWNLINK_HISTORY_STRING,

	RAW_DATA_OF_NODE_DOWNLINK_HISTORY_STRING,
	RECEIVE_DATE_OF_NODE_DOWNLINK_HISTORY_STRING,
}
