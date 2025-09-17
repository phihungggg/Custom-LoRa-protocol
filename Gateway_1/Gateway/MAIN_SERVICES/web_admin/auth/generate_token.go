package auth

import (
	"fmt"
	"time"

	"github.com/golang-jwt/jwt/v5"
)

const (
	Prefix = "Fe_" // in tribute to Iron Session (Fe = Iron)
)

var secretKey = []byte("ongnoimayne")

// GenerateToken creates a new auth token
func CreateToken(username string, role string, id string) (string, error) {

	claims := jwt.NewWithClaims(jwt.SigningMethodHS256, jwt.MapClaims{

		"sub": username,
		"id":  id,
		"iss": "rules_over_dashboard",
		"aud": role,
		"exp": time.Now().Add(time.Hour).Unix(),
		"iat": time.Now().Unix(),
	})

	tokenString, err := claims.SignedString(secretKey)
	if err != nil {

		fmt.Printf(err.Error())

		return "", err
	}

	return tokenString, nil
}
