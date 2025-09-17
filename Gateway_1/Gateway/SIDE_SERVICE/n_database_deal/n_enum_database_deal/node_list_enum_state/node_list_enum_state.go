package node_list_enum_state

type node_list_enum_state int

type node_list_enum_state_string string

const Node_list_Columns_length_defined = 8

// enum for getting data from the one_for_all_query
const (
	ID_OF_NODE_LIST_           node_list_enum_state = 0
	PING_INTERVAL_OF_NODE_LIST node_list_enum_state = 1
	NODE_ID_OF_NODE_LIST       node_list_enum_state = 2
	NODE_ADDRESS_OF_NODE_LIST  node_list_enum_state = 3
	AES_KEY_OF_NODE_LIST       node_list_enum_state = 4
	IS_ACK_NEEDDED             node_list_enum_state = 5
	CREATED_AT_OF_NODE_LIST    node_list_enum_state = 6
	UPDATED_AT_OF_NODE_LIST    node_list_enum_state = 7
)

// enum for get string of that column in order to sprintf query

const (
	ID_OF_NODE_LIST_STRING            node_list_enum_state_string = "id"
	PING_INTERVAL_OF_NODE_LIST_STRING node_list_enum_state_string = "ping_interval"
	NODE_ID_OF_NODE_LIST_STRING       node_list_enum_state_string = "node_id"
	NODE_ADDRESS_OF_NODE_LIST_STRING  node_list_enum_state_string = "node_address"
	AES_KEY_OF_NODE_LIST_STRING       node_list_enum_state_string = "AES_KEY"
	IS_ACK_NEEDDED_STRING             node_list_enum_state_string = "is_ack_needed"
	CREATED_AT_OF_NODE_LIST_STRING    node_list_enum_state_string = "created_at"
	UPDATED_AT_OF_NODE_LIST_STRING    node_list_enum_state_string = "updated_at"
)

const (
	NODE_LIST_TABLE_NAME node_list_enum_state_string = "node_list"
)

var Node_list_enum_state_array = []node_list_enum_state_string{
	ID_OF_NODE_LIST_STRING,
	PING_INTERVAL_OF_NODE_LIST_STRING,
	NODE_ID_OF_NODE_LIST_STRING,
	NODE_ADDRESS_OF_NODE_LIST_STRING,
	AES_KEY_OF_NODE_LIST_STRING,
	IS_ACK_NEEDDED_STRING,
	CREATED_AT_OF_NODE_LIST_STRING,
	UPDATED_AT_OF_NODE_LIST_STRING,
}
