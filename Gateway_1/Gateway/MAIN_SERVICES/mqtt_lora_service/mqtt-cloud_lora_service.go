package mqtt_lora_service

import (
	"fmt"

	//	"example/SIDE_SERVICE/n_database_deal"

	//	"example/SIDE_SERVICE/n_database_deal/n_enum_database_deal" //
	//	"example/N_ENUM"
	"github.com/tarm/serial"
	//	"example/SIDE_SERVICE/serial_dealing"
	"database/sql"
	"time"



			"example/SIDE_SERVICE/random_bsht_libs"

	//	"example/SIDE_SERVICE/decode_payload"

	//"example/SIDE_SERVICE/split_authentication_key_from_decoded_payload"

	"example/MAIN_SERVICES/lora_custom_stack"

		"example/SIDE_SERVICE/mqtt_package"
	
)

func Mqtt_lora_service_run(byte_address, data []byte ,  mqtt_object_input mqtt_package.Mqtt_object  ,db *sql.DB ,lora_object *lora_custom_stack.Lora_object) {



	//var lora_object lora_custom_stack.Lora_object
	lora_object.Recognize_address(byte_address[:], db).Decode_payload(data[:]).Check_authentication().Extract_raw_data()
	if lora_object.Get_if_stack_successfully_finsshied_its_job() == false {
		fmt.Printf("something wrong with the payload \n")
		return
	}
	
	data_to_get:=   random_bsht_libs.ByteArrayToHexString(lora_object.Get_raw_data())    





	mqtt_object_input.Set_data(data_to_get)

	mqtt_object_input.Mqtt_do_mqtt_things("deobiet/1")

	

	//

}

func open_serial() *serial.Port {

	c := &serial.Config{Name: "/dev/ttyS1", Baud: 115200, ReadTimeout: time.Millisecond * 500}
	s, err := serial.OpenPort(c)
	if err != nil {
		panic(err)
	}

	return s
}
