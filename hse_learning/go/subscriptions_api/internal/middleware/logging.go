package middleware

import (
    "log"
    "net/http"
    "time"
)

// LoggingMiddleware — middleware для логирования запросов
func LoggingMiddleware(next http.Handler) http.Handler {
    return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
        start := time.Now()

        // Логируем информацию о запросе
        log.Printf("Method: %s, URL: %s, Time: %s", r.Method, r.URL.Path, start.Format(time.RFC3339))

        next.ServeHTTP(w, r)

        // Логируем время выполнения
        log.Printf("Handled %s %s in %s", r.Method, r.URL.Path, time.Since(start))
    })
}
