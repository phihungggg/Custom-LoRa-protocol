package node_map

type node_map int

type node_map_string string

const node_map_length_defined = 4

// enum for getting data from the one_for_all_query
const (
	ID_OF_NODE_MAP        node_map = 0
	NODE_ID_OF_NODE_MAP   node_map = 1
	NODE_NAME_OF_NODE_MAP node_map = 2
)

// enum for get string of that column in order to sprintf query

const (
	ID_OF_NODE_MAP_STRING        node_map_string = "id"
	NODE_ID_OF_NODE_MAP_STRING   node_map_string = "node_id"
	NODE_NAME_OF_NODE_MAP_STRING node_map_string = "node_name"
)

const (
	NODE_MAP_TABLE_NAME node_map_string = "node_map"
)

var Node_map_array = []node_map_string{
	ID_OF_NODE_MAP_STRING,
	NODE_ID_OF_NODE_MAP_STRING,
	NODE_NAME_OF_NODE_MAP_STRING,
}
