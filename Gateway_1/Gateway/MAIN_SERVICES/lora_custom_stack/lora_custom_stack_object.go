package lora_custom_stack

import (
	"time"

	"example/SIDE_SERVICE/random_bsht_libs"
	"fmt"

	"example/SIDE_SERVICE/n_database_deal"

	"database/sql"

	"example/SIDE_SERVICE/n_database_deal/n_enum_database_deal/node_list_enum_state"

	"example/SIDE_SERVICE/decode_payload"

	//	"errors"

	//	"strconv"
	"example/SIDE_SERVICE/split_authentication_key_from_decoded_payload"

	"example/SIDE_SERVICE/tunnel"
)

// tunnel

// luat bat thanh van : cac truong xac dinh roi thi se la string, con cac truong nao chua cac data chua duoc hoan thien , chang han nhu
// decoded_payload , remmaining_after_split_authenticaiton hoac la raw data ccan giu o kieu du lieu byte de de thao tac
type Lora_object struct {
	AES_key           string
	authenticaion_key string
	node_id           int
	node_name         string
	node_address      string
	created_at        time.Time
	updated_at        time.Time

	Tunnel  tunnel.Tunnel_of_table_in_database_sqlite3
	dataget *[][]string

	is_ack_needed                         bool
	current_raw_data                      []byte
	is_first_stack_done                   bool
	is_second_stack_done                  bool
	is_third_stack_done                   bool
	is_fourth_stack_done                  bool
	decoded_payload                       []byte
	remaining_after_split_authentication  []byte
	raw_data                              []byte
	daily_send_count                      [2]byte
	current_payload_rtc                   [4]byte
	where_is_stack_have_error_at          int
	if_stack_sucessfully_finished_its_job bool
	error_detection                       uint8
	db                                    *sql.DB
}

func (l *Lora_object) Get_if_stack_successfully_finsshied_its_job() bool {
	return l.if_stack_sucessfully_finished_its_job
}

func (l *Lora_object) Get_raw_data() []byte {
	return l.raw_data
}

// if you have any other type of address , please implement this interface , thanks

func (l *Lora_object) Get_data_get_from_sql_query() *[][]string {
	return l.dataget
}

type check_address_interface interface {
	Recognize_address(byte_address []byte) *check_address_interface
}

func (l *Lora_object) Recognize_address(byte_address []byte, db *sql.DB) *(Lora_object) {

	//var return_object lora_custom_stack.Lora_object

	l.is_first_stack_done = true

	address_string := random_bsht_libs.ByteArrayToHexString(byte_address[:])
	fmt.Println("address string la", address_string)
	fmt.Println("\n")

	columns_count, dataget, errr := n_database_deal.Take_every_row_match_those_input(db, "node_list", []string{"node_address"}, address_string)

	l.Tunnel.Data_get = dataget
	l.Tunnel.Name_of_tunnel = "node_list"

	//l.dataget = dataget
	if errr != nil {

		fmt.Printf(errr.Error())

		l.is_first_stack_done = false

	}

	if columns_count != node_list_enum_state.Node_list_Columns_length_defined {

		fmt.Errorf(" columns count khong khop voi column_nums  define \n ")
		l.is_first_stack_done = false
	}

	aes_key := (*dataget)[0][node_list_enum_state.AES_KEY_OF_NODE_LIST]

	l.db = db
	l.AES_key = aes_key

	l.node_address = address_string
	return l
}

func (l *Lora_object) Decode_payload(data []byte) *(Lora_object) {

	if l.is_first_stack_done == false {
		l.where_is_stack_have_error_at = 1
		return l
	}
	decoded_payload, err2 := decode_payload.Decode_payload(data[:], l.AES_key)
	if err2 != nil {
		fmt.Printf(err2.Error())

		l.is_second_stack_done = false
		return l
	}
	l.decoded_payload = decoded_payload
	//str := strconv.Itoa(int(numbyte))

	l.is_second_stack_done = true

	return l
}

func (l *Lora_object) Check_authentication() *(Lora_object) {
	if l.where_is_stack_have_error_at != 0 {

		return l
	}

	if l.is_second_stack_done == false {
		l.where_is_stack_have_error_at = 2
		return l
	}

	/*
		do something wrong then it  set_is_thrid_stack_done(false)
	*/
	_, authentication_key_from_decoded_payload, remaining := split_authentication_key_from_decoded_payload.Split(4, l.decoded_payload)

	err3 := n_database_deal.Check_authentication(authentication_key_from_decoded_payload, l.db, "node_authentication_key", l.node_address, "Authentication_KEY")

	if err3 != nil {

		fmt.Printf(err3.Error())
		l.is_third_stack_done = false
		return l
	}
	l.remaining_after_split_authentication = append(l.remaining_after_split_authentication, remaining...)
	l.authenticaion_key = random_bsht_libs.ByteArrayToHexString(authentication_key_from_decoded_payload[:])
	l.is_third_stack_done = true
	return l

}

func (l *Lora_object) Extract_raw_data() *(Lora_object) {
	if l.where_is_stack_have_error_at != 0 {
		return l
	}
	if l.is_third_stack_done == false {
		l.where_is_stack_have_error_at = 3
		return l
	}

	numbyte, timesrtc, err4 := Extractpayload_bytes(l.remaining_after_split_authentication)

	l.daily_send_count[0] = timesrtc[0]
	l.daily_send_count[1] = timesrtc[1]
	l.current_payload_rtc[0] = timesrtc[2]
	l.current_payload_rtc[1] = timesrtc[3]
	l.current_payload_rtc[2] = timesrtc[4]
	l.current_payload_rtc[3] = timesrtc[5]

	if err4 != nil {

		fmt.Printf(err4.Error())
		l.is_fourth_stack_done = false
		return l
	}
	l.is_fourth_stack_done = true

	l.if_stack_sucessfully_finished_its_job = true
	l.raw_data = numbyte
	return l

}

func (l *Lora_object) Extract_times_of_payload() *(Lora_object) {

	return l
}
