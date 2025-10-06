.PHONY: test-db-up test-db-down test test-all build run clean docker-build docker-up docker-down docker-logs

# Запуск тестовой БД
test-db-up:
	docker-compose -f docker-compose.test.yml up -d

# Остановка тестовой БД
test-db-down:
	docker-compose -f docker-compose.test.yml down

# Запуск тестов (с автоматическим запуском БД)
test: test-db-up
	@echo "Waiting for test database to be ready..."
	@sleep 5
	go test ./internal/models/ -v
	@make test-db-down

# Запуск всех тестов
test-all: test-db-up
	@echo "Waiting for test database to be ready..."
	@sleep 5
	go test ./... -v
	@make test-db-down

# Запуск приложения локально
run:
	go run main.go

# Сборка приложения
build:
	go build -o note-api main.go

# Очистка
clean:
	rm -f note-api

# Swagger команды

# Генерация Swagger документации
swagger:
	@if ! command -v swag &> /dev/null; then \
		echo "Installing swag..."; \
		go install github.com/swaggo/swag/cmd/swag@latest; \
	fi
	go run github.com/swaggo/swag/cmd/swag@latest init -g main.go

# Docker команды

# Сборка Docker образа
docker-build:
	docker-compose build

# Запуск приложения в Docker
docker-up:
	docker-compose up -d

# Остановка приложения в Docker
docker-down:
	docker-compose down

# Просмотр логов
docker-logs:
	docker-compose logs -f

# Полный запуск (сборка + запуск)
docker-start: docker-build docker-up 