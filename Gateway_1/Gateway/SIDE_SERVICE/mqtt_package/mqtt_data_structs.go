package mqtt_package

type temp_hum_mqtt_json_payload struct {
	Temp     float64 `json:"temp"`
	Humidity int     `json:"humidity"`
}

type button_mqtt_json_payload struct {
	Button_state bool `json:"button_state"`
}

type adc_mqtt_json_payload struct {
	Adc_value int `json:"adc_value"`
}
