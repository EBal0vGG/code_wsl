package main

import (
	"log/slog"
	"os"
)

func LogHTTPRequest(logger *slog.Logger, method, path string, status int, durationMs int64) {
	logger.Info("http request",
		"method", method,
		"path", path,
		"status", status,
		"duration_ms", durationMs,
	)    
}

func main() {
	LogHTTPRequest(slog.New(slog.NewTextHandler(os.Stdout, nil)), "GET", "/cc/cd", 200, 299999)
}
