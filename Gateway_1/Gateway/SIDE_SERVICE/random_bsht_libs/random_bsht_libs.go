package random_bsht_libs

import (
	
	"crypto/rand"
	"fmt"
	"strconv"
	"strings"
)

func GenerateRandomHex_n_Bytes(num int) ([]byte, error) {
	bytes := make([]byte, num)

	_, err := rand.Read(bytes)

	if err != nil {
		return nil, err
	}

	return bytes, nil
}

func ByteArrayToHexString(bytes []byte) string {
	parts := make([]string, len(bytes))
	for i, b := range bytes {
		parts[i] = fmt.Sprintf("0x%02X", b)
	}
	return strings.Join(parts, ",")
}

func HexStringToByteArray(hexStr string) ([]byte, error) {
	// Remove all whitespaces
	hexStr = strings.ReplaceAll(hexStr, " ", "")
	// Split by comma
	parts := strings.Split(hexStr, ",")
	bytes := make([]byte, len(parts))

	for i, part := range parts {
		// Remove "0x" or "0X" prefix if exists
		part = strings.TrimPrefix(part, "0x")
		part = strings.TrimPrefix(part, "0X")

		// Parse hex string to byte
		val, err := strconv.ParseUint(part, 16, 8)
		if err != nil {
			return nil, fmt.Errorf("invalid hex byte: %s", part)
		}
		bytes[i] = byte(val)
	}
	return bytes, nil
}



func ConvertNodeID_from_string_to_id(nodeIDStr string) (int, error) {
	id, err := strconv.Atoi(nodeIDStr)
	if err != nil {
		return 0, fmt.Errorf("không thể chuyển node_id '%s' sang int: %v", nodeIDStr, err)
	}
	return id, nil
}
