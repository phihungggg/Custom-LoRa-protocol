package decode_payload

import (
	"fmt"

	"example/SIDE_SERVICE/aes_dealing"
	"example/SIDE_SERVICE/random_bsht_libs"
)

func Decode_payload(payload []byte, aes_key string) ([]byte, error) {
	error_byte := [1]byte{0}
	aes_key_byte, err := random_bsht_libs.HexStringToByteArray(aes_key)

	fmt.Printf(" decode _payload over here \n")

	fmt.Println(aes_key_byte)

	fmt.Println(" Raw slice:", payload)

	if err != nil {
		fmt.Printf(err.Error())
		return error_byte[:], err
	}

	return_bytes, errr := aes_dealing.DecryptECB(aes_key_byte, payload)

	if errr != nil {
		fmt.Printf(errr.Error())

		return error_byte[:], errr
	}
	fmt.Println(return_bytes)

	return return_bytes, nil
}
