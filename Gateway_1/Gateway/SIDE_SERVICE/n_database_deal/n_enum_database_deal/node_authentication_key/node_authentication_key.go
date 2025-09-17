package node_authentication_key

type node_authentication_key int

type node_authentication_key_string string

const node_authentication_key_length_defined = 3

const (
	ID_OF_NODE_AUTHENTICATION_KEY node_authentication_key = 0

	NODE_ADDRESS_OF_AUTHENTICATION_KEY node_authentication_key = 1

	AUTHENTICATION_KEY node_authentication_key = 2
)

const (
	ID_OF_NODE_AUTHENTICATION_KEY_STRING node_authentication_key_string = "id"

	NODE_ADDRESS_OF_AUTHENTICATION_KEY_STRING node_authentication_key_string = "node_adđress"

	AUTHENTICATION_KEY_STRING node_authentication_key_string = "Authentication_KEY"
)

const (
	NODE_AUTHENTICATION_KEY_TABLE_NAME node_authentication_key_string = "node_authentication_key"
)

var Node_authentication_key_array = []node_authentication_key_string{
	ID_OF_NODE_AUTHENTICATION_KEY_STRING,
	NODE_ADDRESS_OF_AUTHENTICATION_KEY_STRING,
	AUTHENTICATION_KEY_STRING,
}


