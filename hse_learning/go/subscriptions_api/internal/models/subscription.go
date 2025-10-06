package models

import (
    "time"
    "errors"
    "database/sql"
    "github.com/google/uuid"
)

// Subscription соответствует таблице subscriptions
type Subscription struct {
    ID          uuid.UUID  `json:"id"`
    UserID      uuid.UUID  `json:"user_id"`
    ServiceName string     `json:"service_name"`
    Price       int        `json:"price"` // Стоимость подписки в рублях
    StartDate   time.Time  `json:"start_date"` // Месяц и год начала подписки
    EndDate     *time.Time `json:"end_date,omitempty"` // Опционально дата окончания подписки
}

// SubscriptionRequest - структура для запроса подписок пользователя
type SubscriptionRequest struct {
    UserID uuid.UUID `json:"user_id"`
}

// Validate проверяет корректность данных запроса на создание подписки
func (sub *Subscription) Validate() error {
    // Проверка на пустой userID
    if sub.UserID == uuid.Nil {
        return errors.New("user_id не может быть пустым")
    }

    // Проверка на пустое название сервиса
    if sub.ServiceName == "" {
        return errors.New("service_name не может быть пустым")
    }

    // Проверка на цену подписки (должна быть положительной)
    if sub.Price <= 0 {
        return errors.New("price должен быть положительным числом")
    }

    // Проверка корректности формата StartDate (например, "01-2025")
    if !isValidStartDate(sub.StartDate) {
        return errors.New("неверный формат start_date, должен быть месяц-год")
    }

    // Если EndDate присутствует, проверяем, что он не раньше, чем StartDate
    if sub.EndDate != nil && sub.EndDate.Before(sub.StartDate) {
        return errors.New("end_date не может быть раньше start_date")
    }

    return nil
}

// Validate проверяет корректность данных запроса на получение подписок пользователя
func (sub *SubscriptionRequest) Validate() error {
    // Проверка на пустой userID
    if sub.UserID == uuid.Nil {
        return errors.New("user_id не может быть пустым")
    }

    return nil
}

// Проверка на корректность формата StartDate (например, 01-2025)
func isValidStartDate(date time.Time) bool {
    // Проверяем, что месяц и год указаны
    // В данной функции предполагаем, что формат уже правильный
    return date.Year() > 0 && date.Month() > 0
}

// CreateSubscription добавляет новую подписку
func CreateSubscription(db *sql.DB, sub *Subscription) error {
    query := `
        INSERT INTO subscriptions (user_id, service_name, price, start_date, end_date)
        VALUES ($1, $2, $3, $4, $5) RETURNING id`
    return db.QueryRow(query, sub.UserID, sub.ServiceName, sub.Price, sub.StartDate, sub.EndDate).Scan(&sub.ID)
}

// GetSubscriptionsByUser возвращает все подписки пользователя
func GetSubscriptionsByUser(db *sql.DB, userID uuid.UUID) ([]Subscription, error) {
    query := "SELECT id, user_id, service_name, price, start_date, end_date FROM subscriptions WHERE user_id=$1"
    rows, err := db.Query(query, userID)
    if err != nil {
        return nil, err
    }
    defer rows.Close()

    var subscriptions []Subscription
    for rows.Next() {
        var sub Subscription
        if err := rows.Scan(&sub.ID, &sub.UserID, &sub.ServiceName, &sub.Price, &sub.StartDate, &sub.EndDate); err != nil {
            return nil, err
        }
        subscriptions = append(subscriptions, sub)
    }
    return subscriptions, nil
}

// CalculateTotalPrice возвращает общую стоимость подписок за период
func CalculateTotalPrice(db *sql.DB, userID uuid.UUID, startDate time.Time, endDate time.Time, serviceName string) (int, error) {
    query := `
        SELECT SUM(price) FROM subscriptions
        WHERE user_id = $1 AND start_date >= $2 AND start_date <= $3 AND (service_name = $4 OR $4 = '')`
    var totalPrice int
    err := db.QueryRow(query, userID, startDate, endDate, serviceName).Scan(&totalPrice)
    if err != nil {
        return 0, err
    }
    return totalPrice, nil
}

// GetSubscriptionByID возвращает подписку по её ID
func GetSubscriptionByID(db *sql.DB, id uuid.UUID) (*Subscription, error) {
    query := `SELECT id, user_id, service_name, price, start_date, end_date FROM subscriptions WHERE id = $1`
    var sub Subscription
    err := db.QueryRow(query, id).Scan(&sub.ID, &sub.UserID, &sub.ServiceName, &sub.Price, &sub.StartDate, &sub.EndDate)
    if err != nil {
        if err == sql.ErrNoRows {
            return nil, nil // Подписка не найдена
        }
        return nil, err
    }
    return &sub, nil
}