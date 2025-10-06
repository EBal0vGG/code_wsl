package main

import (
	"log/slog"
	// "os"
)

func LogUserAction(logger *slog.Logger, user string, action string) {
	logger.Info("user action",
	"user", user,
	"action", action,
	)    
}

// func main() {
// 	LogUserAction(slog.New(slog.NewTextHandler(os.Stdout, nil)), "GGGGGGG", "AAA")
// }
