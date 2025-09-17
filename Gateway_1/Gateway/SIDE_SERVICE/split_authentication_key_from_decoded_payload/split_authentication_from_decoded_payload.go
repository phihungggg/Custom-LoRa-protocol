package split_authentication_key_from_decoded_payload

func Split(length_of_authentication_key uint, payload []byte) ([]byte, []byte, []byte) {
	authentication := make([]byte, length_of_authentication_key)

	copy(authentication, payload[2:length_of_authentication_key+2])
	remaining := payload[length_of_authentication_key+2:]
	before := payload[:2]
	return before, authentication, remaining
}
