package lora_custom_stack

import (
	"fmt"
)

// ham nay se ghep cac byte data thanh mot bien lon , vi du uint64_t

func Extractpayload_bytes(input []byte) ([]byte, [6]byte, error) {

	var empty [6]byte
	if len(input) < 2 {
		return nil, empty, fmt.Errorf("Input quá ngắn")
	}
	size := int(input[0])
	return_byte_data_slice := make([]byte, size)
	for i := 0; i < size; i++ {
		return_byte_data_slice[i] = input[i+1]
	}
	var return_byte_time_slice [6]byte
	for i, j := size, 0; i < size+6 && j < 6; i, j = i+1, j+1 {
		return_byte_time_slice[j] = input[i+1]
	}
	return return_byte_data_slice, return_byte_time_slice, nil
}

func Extractpayload_sendid_rtc(input []byte, size int) ([]byte, error) {
	if len(input) < 2 {

		return nil, fmt.Errorf(" INPUT IS TOO SHORT \n")

	}

	return_byte_slice := make([]byte, size)
	for i := 0; i < size; i++ {
		return_byte_slice[i] = input[i]
	}
	return return_byte_slice, nil
}

func ExtractData(input []byte) (uint64, error, byte) {
	if len(input) < 2 {
		return 0, fmt.Errorf("Input quá ngắn"), 0
	}

	size := int(input[0])

	// Kiểm tra đủ dữ liệu chưa
	if len(input) < size+2 {
		return 0, fmt.Errorf("Không đủ dữ liệu để ghép %d byte và đọc 1 byte sau đó", size), 0
	}

	var num uint64 = 0
	for i := 0; i < size; i++ {
		num = (num << 8) | uint64(input[i+1])
	}

	fmt.Println(num)

	singleByte := input[size+1]
	fmt.Println(uint8(singleByte))
	return num, nil, singleByte
}
