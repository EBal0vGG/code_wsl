package main

import (
	"fmt"
)

// Order представляет информацию о заказе.
type Order struct {
    OrderNumber  int
    CustomerName string
    OrderAmount  float64
}

// OrderLogger представляет журнал заказов и хранит записи о заказах.
type OrderLogger struct {
	// Orders []Order
}

// NewOrderLogger создает новый экземпляр OrderLogger.
func NewOrderLogger() *OrderLogger {
    return &OrderLogger{}
}

func (logger *OrderLogger) AddOrder(order Order) {
	fmt.Printf("Добавлен заказ #%d, Имя клиента: %s, Сумма заказа: $%.2f\n", 
				order.OrderNumber, order.CustomerName, order.OrderAmount)
}

// func main() {
// 	orderLogger := NewOrderLogger()
// 	orderLogger.AddOrder(Order {1, "ABC", 22.99} )
// }
