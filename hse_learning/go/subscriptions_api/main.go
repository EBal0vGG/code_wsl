// @title Note API
// @version 1.0
// @description API для управления заметками (CRUD + аутентификация)
// @host localhost:8080
// @BasePath /
// @securityDefinitions.apikey BearerAuth
// @in header
// @name Authorization

package main

import (
	"context"
	"log"
	"net/http"
	"os"
	"os/signal"
	"syscall"
	"time"

	"github.com/gorilla/mux"

	"note-api/internal/handlers"
	"note-api/internal/middleware"
	"note-api/internal/utils"

	_ "note-api/docs"

	httpSwagger "github.com/swaggo/http-swagger"

	"github.com/joho/godotenv"

)

func main() {
	// Загружаем .env
	if err := godotenv.Load(); err != nil {
	    log.Println("Не удалось загрузить .env файл")
	}

    // Загружаем конфигурацию и подключаемся к базе данных
    db, err := utils.ConnectDB()
    if err != nil {
        log.Fatal("Ошибка подключения к базе данных:", err)
    }
    defer db.Close()

    r := mux.NewRouter()
    r.Use(middleware.LoggingMiddleware)

    // Защищённые маршруты
    subscriptionRouter := r.PathPrefix("/subscriptions").Subrouter()
    subscriptionRouter.Use(middleware.AuthMiddleware)
    subscriptionRouter.HandleFunc("", handlers.CreateSubscriptionHandler(db)).Methods("POST")
    subscriptionRouter.HandleFunc("", handlers.GetSubscriptionsHandler(db)).Methods("GET")
    subscriptionRouter.HandleFunc("/total", handlers.CalculateTotalPriceHandler(db)).Methods("GET")

    r.HandleFunc("/ping", func(w http.ResponseWriter, r *http.Request) {
        w.Write([]byte("pong\n"))
    })

    r.PathPrefix("/swagger/").Handler(httpSwagger.WrapHandler)

    srv := &http.Server{
        Addr:    ":" + config.ServerPort,
        Handler: r,
    }

    log.Fatal(srv.ListenAndServe())
}

