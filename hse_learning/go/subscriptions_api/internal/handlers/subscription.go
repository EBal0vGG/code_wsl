package handlers

import (
    "database/sql"
    "encoding/json"
    "net/http"
    "time"
    "github.com/google/uuid"
    "note-api/internal/models"
)

// CreateSubscriptionHandler создаёт новую подписку
// @Summary Создать подписку
// @Description Добавляет подписку для указанного пользователя
// @Tags subscriptions
// @Accept json
// @Produce json
// @Param subscription body models.Subscription true "Подписка"
// @Success 201 {object} models.Subscription
// @Failure 400 {string} string "Неверный формат данных"
// @Failure 500 {string} string "Ошибка сервера"
// @Router /subscriptions [post]
func CreateSubscriptionHandler(db *sql.DB) http.HandlerFunc {
    return func(w http.ResponseWriter, r *http.Request) {
        // Парсим тело запроса в структуру Subscription
        var sub models.Subscription
        if err := json.NewDecoder(r.Body).Decode(&sub); err != nil {
            http.Error(w, "Неверный формат данных", http.StatusBadRequest)
            return
        }

        // Валидируем данные
        if err := sub.Validate(); err != nil {
            http.Error(w, err.Error(), http.StatusBadRequest)
            return
        }

        if err := models.CreateSubscription(db, &sub); err != nil {
            http.Error(w, "Ошибка сервера", http.StatusInternalServerError)
            return
        }

        // Возвращаем успешный ответ
        w.WriteHeader(http.StatusCreated)
        json.NewEncoder(w).Encode(sub)
    }
}


// GetSubscriptionsHandler возвращает все подписки пользователя
// @Summary Получить подписки
// @Description Получает все подписки для указанного пользователя
// @Tags subscriptions
// @Accept json
// @Produce json
// @Param user_id body string true "ID пользователя"
// @Success 200 {array} models.Subscription
// @Failure 400 {string} string "Неверный формат данных"
// @Failure 500 {string} string "Ошибка сервера"
// @Router /subscriptions [get]
func GetSubscriptionsHandler(db *sql.DB) http.HandlerFunc {
    return func(w http.ResponseWriter, r *http.Request) {
        var subr models.SubscriptionRequest
        err := json.NewDecoder(r.Body).Decode(&subr)
        if err != nil {
            http.Error(w, "Неверный формат данных", http.StatusBadRequest)
            return
        }

        // Валидируем данные
        if err := subr.Validate(); err != nil {
            http.Error(w, err.Error(), http.StatusBadRequest)
            return
        }

        subscriptions, err := models.GetSubscriptionsByUser(db, subr.UserID)
        if err != nil {
            http.Error(w, "Ошибка сервера", http.StatusInternalServerError)
            return
        }

        w.Header().Set("Content-Type", "application/json")
        json.NewEncoder(w).Encode(subscriptions)
    }
}

// CalculateTotalPriceHandler подсчитывает общую стоимость подписок за период
// @Summary Подсчитать общую стоимость подписок
// @Description Подсчитывает суммарную стоимость подписок пользователя за период
// @Tags subscriptions
// @Accept json
// @Produce json
// @Param period query string true "Период (например, 01-2025)"
// @Param service_name query string false "Название сервиса"
// @Param user_id body string true "ID пользователя"
// @Success 200 {integer} int
// @Failure 400 {string} string "Неверный формат данных"
// @Failure 500 {string} string "Ошибка сервера"
// @Router /subscriptions/total [get]
func CalculateTotalPriceHandler(db *sql.DB) http.HandlerFunc {
    return func(w http.ResponseWriter, r *http.Request) {
        var subRequest models.Subscription
        err := json.NewDecoder(r.Body).Decode(&subRequest)
        if err != nil {
            http.Error(w, "Неверный формат данных", http.StatusBadRequest)
            return
        }

        // Проверяем, что user_id передан
        if subRequest.UserID == "" {
            http.Error(w, "user_id не указан", http.StatusBadRequest)
            return
        }

        userID, err := uuid.Parse(subRequest.UserID)
        if err != nil {
            http.Error(w, "Неверный формат user_id", http.StatusBadRequest)
            return
        }

        period := r.URL.Query().Get("period")
        serviceName := r.URL.Query().Get("service_name")

        // Парсим период (например, "01-2025")
        t, err := time.Parse("01-2006", period)
        if err != nil {
            http.Error(w, "Неверный формат периода", http.StatusBadRequest)
            return
        }

        // Подсчитываем общую стоимость
        totalPrice, err := models.CalculateTotalPrice(db, userID, t, t.AddDate(0, 1, 0), serviceName)
        if err != nil {
            http.Error(w, "Ошибка сервера", http.StatusInternalServerError)
            return
        }

        w.Header().Set("Content-Type", "application/json")
        json.NewEncoder(w).Encode(totalPrice)
    }
}

// UpdateSubscriptionStatusHandler обновляет статус подписки
// @Summary Обновить статус подписки
// @Description Меняет статус подписки (например, активная, отменена)
// @Tags subscriptions
// @Accept json
// @Produce json
// @Param id path string true "ID подписки"
// @Param status body string true "Новый статус подписки"
// @Param user_id body string true "ID пользователя"
// @Success 200 {object} models.Subscription
// @Failure 400 {string} string "Неверный формат данных"
// @Failure 404 {string} string "Подписка не найдена"
// @Failure 500 {string} string "Ошибка сервера"
// @Router /subscriptions/{id}/status [put]
// func UpdateSubscriptionStatusHandler(db *sql.DB) http.HandlerFunc {
//     return func(w http.ResponseWriter, r *http.Request) {
//         var subRequest models.Subscription
//         err := json.NewDecoder(r.Body).Decode(&subRequest)
//         if err != nil {
//             http.Error(w, "Неверный формат данных", http.StatusBadRequest)
//             return
//         }

//         // Проверяем, что user_id передан
//         if subRequest.UserID == "" {
//             http.Error(w, "user_id не указан", http.StatusBadRequest)
//             return
//         }

//         userID, err := uuid.Parse(subRequest.UserID)
//         if err != nil {
//             http.Error(w, "Неверный формат user_id", http.StatusBadRequest)
//             return
//         }

//         id := mux.Vars(r)["id"]
//         var status string
//         err = json.NewDecoder(r.Body).Decode(&status)
//         if err != nil {
//             http.Error(w, "Неверный формат данных", http.StatusBadRequest)
//             return
//         }

//         // Обновляем статус подписки в базе данных
//         query := `UPDATE subscriptions SET status = $1 WHERE id = $2 AND user_id = $3 RETURNING id`
//         var subscriptionID uuid.UUID
//         err = db.QueryRow(query, status, id, userID).Scan(&subscriptionID)
//         if err != nil {
//             if err == sql.ErrNoRows {
//                 http.Error(w, "Подписка не найдена", http.StatusNotFound)
//                 return
//             }
//             http.Error(w, "Ошибка сервера", http.StatusInternalServerError)
//             return
//         }

//         // Возвращаем обновленную подписку
//         updatedSubscription, _ := models.GetSubscriptionByID(db, subscriptionID)
//         w.Header().Set("Content-Type", "application/json")
//         json.NewEncoder(w).Encode(updatedSubscription)
//     }
// }
