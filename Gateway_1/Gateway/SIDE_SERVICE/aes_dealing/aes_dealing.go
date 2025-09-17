package aes_dealing

import (
	"crypto/aes"

	//"encoding/base64"
	"fmt"
)

// Zero-padding cho đủ bội số 16
func padZero(data []byte) []byte {
	padLen := aes.BlockSize - (len(data) % aes.BlockSize)
	if padLen == aes.BlockSize {
		return data // Không cần pad nếu đã vừa đủ
	}
	padded := make([]byte, len(data)+padLen)
	copy(padded, data)
	return padded
}

// Encrypt AES-ECB
func EncryptECB(key []byte, plaintext []byte) ([]byte, error) {
	padded := padZero(plaintext)

	block, err := aes.NewCipher(key)
	if err != nil {
		return nil, fmt.Errorf("new cipher error: %v", err)
	}

	encrypted := make([]byte, len(padded))
	for start := 0; start < len(padded); start += aes.BlockSize {
		block.Encrypt(encrypted[start:start+aes.BlockSize], padded[start:start+aes.BlockSize])
	}
	return encrypted, nil
}

// Decrypt AES-ECB
func DecryptECB(key []byte, ciphertext []byte) ([]byte, error) {
	if len(ciphertext)%aes.BlockSize != 0 {
		return nil, fmt.Errorf("ciphertext must be multiple of %d bytes", aes.BlockSize)
	}

	block, err := aes.NewCipher(key)
	if err != nil {
		return nil, fmt.Errorf("new cipher error: %v", err)
	}

	decrypted := make([]byte, len(ciphertext))
	for start := 0; start < len(ciphertext); start += aes.BlockSize {
		block.Decrypt(decrypted[start:start+aes.BlockSize], ciphertext[start:start+aes.BlockSize])
	}
	return decrypted, nil
}
