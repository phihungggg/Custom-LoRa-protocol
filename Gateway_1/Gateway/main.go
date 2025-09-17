package main

import (
	"database/sql"
	"fmt"
	"net"

	//"context"

	//"example/SIDE_SERVICE/n_database_deal"
	//"example/N_ENUM"

	//"github.com/gin-contrib/cors"

	//"example/SIDE_SERVICE/serial_dealing"

	//"database/sql"
	//"time"

	"strconv"
	"time"

	//"github.com/tarm/serial"

	"example/MAIN_SERVICES/web_admin/run"

	"example/SIDE_SERVICE/serial_dealing"

	"github.com/tarm/serial"

	"example/MAIN_SERVICES/mqtt_lora_service"
	"example/SIDE_SERVICE/mqtt_package"

	//"example/MAIN_SERVICES/mqtt_lora_service"

	"example/MAIN_SERVICES/data_cache"
	"example/MAIN_SERVICES/lora_custom_stack"
	"example/SIDE_SERVICE/n_database_deal/db_class"

	//"encoding/binary"

	"log"

	"github.com/hashicorp/mdns"
)

func main() {

	router := run.Get_router_ready()

	//go run_mDNS()

	//log.Println("mDNS started")

	//side service : mqtt
	mqtt_object := init_mqtt_object()
	//

	//side  sersvice : serial
	s := open_serial()
	//

	// khoi dong database
	db := init_database()
	defer db.Close()
	//

	//tao lora stack
	var lora_object lora_custom_stack.Lora_object

	//

	// when callback happens( its mean lora data is received) , then run MAIN SERVICES
	go serial_dealing.ReadSerial(s, func(data []byte) {
		//trich dia chi
		fmt.Printf("Data received (decimal): %v\n", data)
		var byte_address [2]byte
		byte_address[0] = data[0]
		byte_address[1] = data[1]
		//
		//chay service chuyen tu lora  sang mqtt
		mqtt_lora_service.Mqtt_lora_service_run(byte_address[:], data[2:], mqtt_object, db, &lora_object)
		//debug mqtt_cloud_lora_service

		//
		bytess := lora_object.Get_raw_data()
		////val := binary.LittleEndian.Uint64(byte)

		// data cache service
		data_cache.Update_node_data(db, lora_object.Tunnel, bytess)
	})

	// Start Gin server
	router.Run(":8081")

}

// Example functions

// Dummy data

func update_node_data_uplink_history(db_final_object *sql.DB, rawdata string, node_address string) error {
	insertStmt := `INSERT INTO node_data_uplink_history  (node_address,raw_data) VALUES (?, ?)`
	_, errorr := db_final_object.Exec(insertStmt, node_address, rawdata)
	if errorr != nil {
		errorMessage := errorr.Error()
		fmt.Printf(errorMessage)

	}

	return nil
}

// this function will update button
func update_button_uplink_current_state(db_final_object *sql.DB, current_button_state string, node_address string) error {

	db_final_object, err := sql.Open("sqlite3", "LoRa.db")

	if err != nil {

		return err
	}

	insertStmt := `INSERT INTO node_data_uplink_history  (node_address,current_button_pressed) VALUES (?, ?)`

	_, errorr := db_final_object.Exec(insertStmt, node_address, current_button_state)

	if errorr != nil {
		errorMessage := errorr.Error()
		fmt.Printf(errorMessage)

	}
	return nil
}

func ham_tao_chuoi_de_dan_toi_bang_can_thiet(input string) string {
	current_state := "_CURRENT_STATE"
	result := input + current_state
	return result
}

func ConvertNodeID(nodeIDStr string) (int, error) {
	id, err := strconv.Atoi(nodeIDStr)
	if err != nil {
		return 0, fmt.Errorf("không thể chuyển node_id '%s' sang int: %v", nodeIDStr, err)
	}
	return id, nil
}

func open_serial() *serial.Port {

	c := &serial.Config{Name: "/dev/ttyS1", Baud: 115200, ReadTimeout: time.Millisecond * 500}
	s, err := serial.OpenPort(c)
	if err != nil {
		panic(err)
	}

	return s
}

func init_database() *sql.DB {

	create_database := db_class.NewDatabase("sqlite3", "LoRa.db")
	db, err := sql.Open(create_database.Get_driver(), create_database.Get_database_file())
	if err != nil {
		errormessage := err.Error()
		fmt.Printf(errormessage)
	}

	return db

}
func init_mqtt_object() mqtt_package.Mqtt_object {
	var mqtt_object mqtt_package.Mqtt_object
	mqtt_object.Mqtt_init("tls://r12d0e8e.ala.asia-southeast1.emqxsl.com:8883", "emqx_cloudefa033", "draxd", "deobietmatkhau")
	return mqtt_object
}

func run_mDNS() {

	infor := []string{"gateway"}
	ip := net.ParseIP("192.168.1.5")
	service, err := mdns.NewMDNSService("gateway", "_http._tcp", "", "", 8081, []net.IP{ip}, infor)
	if err != nil {
		log.Fatalf("mDNS service creation failed: %v", err)
	}
	server, _ := mdns.NewServer(&mdns.Config{Zone: service})
	defer server.Shutdown()
	select {}
}
