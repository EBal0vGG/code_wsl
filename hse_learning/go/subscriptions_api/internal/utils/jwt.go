package utils

import (
    "os"
    "time"

    "github.com/golang-jwt/jwt/v5"
)

var jwtSecret []byte

func init() {
    jwtSecret = []byte(os.Getenv("JWT_SECRET"))
}

func GenerateJWT(userId int, username string) (string, error) {
    claims := jwt.MapClaims{
        "user_id":  userId,
        "username": username,
        "exp":      time.Now().Add(time.Hour * 72).Unix(),
    }

    token := jwt.NewWithClaims(jwt.SigningMethodHS256, claims)

    return token.SignedString(jwtSecret)
}
