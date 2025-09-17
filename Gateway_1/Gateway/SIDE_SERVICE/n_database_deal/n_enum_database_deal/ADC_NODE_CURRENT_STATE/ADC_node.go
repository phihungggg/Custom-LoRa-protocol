package ADC_NODE_CURRENT_STATE

type ADC_node int

type ADC_node_string string

const ADC_node_Columns_length_defined = 5
const columns_number_need_to_Be_add_when_insertion_happens = 2
const (
	ID_OF_ADC_NODE           ADC_node = 0
	NODE_ADDRESS_OF_ADC_NODE ADC_node = 1
	ADC_VALUE                ADC_node = 2
	receive_date             ADC_node = 3
)

const (
	ID_OF_ADC_NODE_STRING               ADC_node_string = "id"
	NODE_ADDRESS_OF_ADC_NODE_STRING     ADC_node_string = "node_address"
	SENDING_INTERVAL_OF_ADC_NODE_STRING ADC_node_string = "sending_interval"
	ADC_VALUE_STRING                    ADC_node_string = "adc_value"
	receive_date_STRING                 ADC_node_string = "received_date"
)

func GetADCNode_INSERTION_Columns() []ADC_node_string {
	return []ADC_node_string{

		NODE_ADDRESS_OF_ADC_NODE_STRING,

		ADC_VALUE_STRING,
	}
}

func GetADCNode_UPDATE_Columns() []ADC_node_string {
	return []ADC_node_string{

		//NODE_ADDRESS_OF_ADC_NODE_STRING,

		ADC_VALUE_STRING,
	}
}

/*
var Adc_node_array = [ADC_node_Columns_length_defined]ADC_node_string{
	ID_OF_ADC_NODE_STRING,
	NODE_ADDRESS_OF_ADC_NODE_STRING,
	SENDING_INTERVAL_OF_ADC_NODE_STRING,
	ADC_VALUE_STRING,
	receive_date_STRING,
}
*/

const (
	ADC_NODE_TABLE_NAME ADC_node_string = "ADC_NODE_CURRENT_STATE"
)
