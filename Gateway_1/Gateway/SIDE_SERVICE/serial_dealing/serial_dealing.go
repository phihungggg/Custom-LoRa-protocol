package serial_dealing

import (
	"bufio"
	"fmt"
	"io"
)

func ReadSerial(port io.Reader, callback func([]byte)) {
	//var count int =0
	for {
		header := make([]byte, 1)
		_, err := io.ReadFull(port, header)
		if err != nil {
			fmt.Println("Error reading header byte:", err)
			continue
		}

		switch header[0] {
		case 0:

			// Sau header = 0, bạn cần đọc thêm 1 byte length
			lenBuf := make([]byte, 1)
			_, err = io.ReadFull(port, lenBuf)
			if err != nil {
				fmt.Println("Error reading length byte:", err)
				continue
			}

			length := int(lenBuf[0])
			payload := make([]byte, length)
			_, err = io.ReadFull(port, payload)
			if err != nil {
				fmt.Println("Error reading payload:", err)
				continue
			}
			callback(payload)

		case 1:
			reader := bufio.NewReader(port)
			for {
				_, err := reader.ReadBytes('\n')
				if err != nil {
					fmt.Println("Error reading line:", err)
					break // thay vì continue vô hạn -> break ra ngoài
				}
				//callback(line)
			}

		default:
			fmt.Println("Unknown header:", header[0])
		}
	}
}

/*

func ReadSerial(port io.Reader, something io.Writer, callback func([]byte)) {
	//var count int =0
	for {
		header := make([]byte, 1)
		_, err := io.ReadFull(port, header)
		if err != nil {
			fmt.Println("Error reading header byte:", err)
			continue
		}

		switch header[0] {
		case 0:

			// Sau header = 0, bạn cần đọc thêm 1 byte length
			lenBuf := make([]byte, 1)
			_, err = io.ReadFull(port, lenBuf)
			if err != nil {
				fmt.Println("Error reading length byte:", err)
				continue
			}

			length := int(lenBuf[0])
			payload := make([]byte, length)
			_, err = io.ReadFull(port, payload)
			if err != nil {
				fmt.Println("Error reading payload:", err)
				continue
			}
			callback(payload)

		case 1:
			reader := bufio.NewReader(port)
			for {
				_, err := reader.ReadBytes('\n')
				if err != nil {
					fmt.Println("Error reading line:", err)
					break // thay vì continue vô hạn -> break ra ngoài
				}
				//callback(line)
			}

		default:
			fmt.Println("Unknown header:", header[0])
		}
	}
}
*/

// WriteSerial gửi dữ liệu ra cổng serial theo định dạng: [header][length][payload]
func WriteSerial(port io.Writer, payload []byte) error {
	if len(payload) > 255 {
		return fmt.Errorf("payload too long (max 255 bytes)")
	}

	header := byte(0)
	length := byte(len(payload))

	// Gửi header
	_, err := port.Write([]byte{header})
	if err != nil {
		return fmt.Errorf("failed to write header: %v", err)
	}

	// Gửi độ dài
	_, err = port.Write([]byte{length})
	if err != nil {
		return fmt.Errorf("failed to write length: %v", err)
	}

	// Gửi payload
	_, err = port.Write(payload)
	if err != nil {
		return fmt.Errorf("failed to write payload: %v", err)
	}

	return nil
}
