package models

import (
	"database/sql"
	"testing"
	"time"

	_ "github.com/lib/pq"
)

func TestCredentials_Validate(t *testing.T) {
	tests := []struct {
		name    string
		creds   Credentials
		wantErr bool
	}{
		{
			name: "valid credentials",
			creds: Credentials{
				Username: "testuser",
				Password: "password123",
			},
			wantErr: false,
		},
		{
			name: "username too short",
			creds: Credentials{
				Username: "ab",
				Password: "password123",
			},
			wantErr: true,
		},
		{
			name: "password too short",
			creds: Credentials{
				Username: "testuser",
				Password: "123",
			},
			wantErr: true,
		},
		{
			name: "empty username",
			creds: Credentials{
				Username: "",
				Password: "password123",
			},
			wantErr: true,
		},
		{
			name: "empty password",
			creds: Credentials{
				Username: "testuser",
				Password: "",
			},
			wantErr: true,
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			err := tt.creds.Validate()
			if (err != nil) != tt.wantErr {
				t.Errorf("Credentials.Validate() error = %v, wantErr %v", err, tt.wantErr)
			}
		})
	}
}

func TestNote_Validate(t *testing.T) {
	tests := []struct {
		name    string
		note    Note
		wantErr bool
	}{
		{
			name: "valid note",
			note: Note{
				Title:   "Test Note",
				Content: "Test content",
			},
			wantErr: false,
		},
		{
			name: "empty title",
			note: Note{
				Title:   "",
				Content: "Test content",
			},
			wantErr: true,
		},
		{
			name: "empty content is ok",
			note: Note{
				Title:   "Test Note",
				Content: "",
			},
			wantErr: false,
		},
	}

	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			err := tt.note.Validate()
			if (err != nil) != tt.wantErr {
				t.Errorf("Note.Validate() error = %v, wantErr %v", err, tt.wantErr)
			}
		})
	}
}

// setupTestDB создаёт тестовую БД для интеграционных тестов
func setupTestDB(t *testing.T) *sql.DB {
	// Используем тестовую БД на порту 5433
	db, err := sql.Open("postgres", "postgres://postgres:password@localhost:5433/note_api_test?sslmode=disable")
	if err != nil {
		t.Skipf("Skipping test: cannot connect to test database: %v", err)
	}

	// Ждём, пока БД будет готова
	for i := 0; i < 10; i++ {
		err = db.Ping()
		if err == nil {
			break
		}
		time.Sleep(1 * time.Second)
	}
	if err != nil {
		t.Skipf("Skipping test: database not ready: %v", err)
	}

	// Очищаем таблицы перед тестом
	db.Exec("DELETE FROM notes")
	db.Exec("DELETE FROM users")

	return db
}

func TestGetUserByUsername(t *testing.T) {
	db := setupTestDB(t)
	defer db.Close()

	// Создаём тестового пользователя
	user := &User{
		Username:     "testuser",
		PasswordHash: "hashedpassword",
	}
	err := CreateUser(db, user)
	if err != nil {
		t.Fatalf("Failed to create test user: %v", err)
	}

	// Тестируем получение пользователя
	foundUser, err := GetUserByUsername(db, "testuser")
	if err != nil {
		t.Errorf("GetUserByUsername() error = %v", err)
		return
	}

	if foundUser.Username != "testuser" {
		t.Errorf("GetUserByUsername() username = %v, want %v", foundUser.Username, "testuser")
	}

	// Тестируем случай, когда пользователь не найден
	_, err = GetUserByUsername(db, "nonexistent")
	if err == nil {
		t.Error("GetUserByUsername() should return error for nonexistent user")
	}
}

func TestCreateUser(t *testing.T) {
	db := setupTestDB(t)
	defer db.Close()

	user := &User{
		Username:     "newuser",
		PasswordHash: "hashedpassword",
	}

	// Тестируем создание пользователя
	err := CreateUser(db, user)
	if err != nil {
		t.Errorf("CreateUser() error = %v", err)
	}

	// Проверяем, что пользователь создался
	foundUser, err := GetUserByUsername(db, "newuser")
	if err != nil {
		t.Errorf("Failed to find created user: %v", err)
		return
	}

	if foundUser.Username != "newuser" {
		t.Errorf("CreateUser() username = %v, want %v", foundUser.Username, "newuser")
	}

	// Тестируем создание пользователя с тем же именем (должно вернуть ошибку)
	err = CreateUser(db, user)
	if err == nil {
		t.Error("CreateUser() should return error for duplicate username")
	}
}

func TestCreateNote(t *testing.T) {
	db := setupTestDB(t)
	defer db.Close()

	// Создаём тестового пользователя
	user := &User{
		Username:     "testuser",
		PasswordHash: "hashedpassword",
	}
	err := CreateUser(db, user)
	if err != nil {
		t.Fatalf("Failed to create test user: %v", err)
	}

	note := &Note{
		UserID:  user.ID,
		Title:   "Test Note",
		Content: "Test content",
	}

	// Тестируем создание заметки
	err = CreateNote(db, note)
	if err != nil {
		t.Errorf("CreateNote() error = %v", err)
	}
}

func TestGetNotesByUser(t *testing.T) {
	db := setupTestDB(t)
	defer db.Close()

	// Создаём тестового пользователя
	user := &User{
		Username:     "testuser",
		PasswordHash: "hashedpassword",
	}
	err := CreateUser(db, user)
	if err != nil {
		t.Fatalf("Failed to create test user: %v", err)
	}

	// Создаём тестовые заметки
	notes := []*Note{
		{UserID: user.ID, Title: "Note 1", Content: "Content 1"},
		{UserID: user.ID, Title: "Note 2", Content: "Content 2"},
	}

	for _, note := range notes {
		err = CreateNote(db, note)
		if err != nil {
			t.Fatalf("Failed to create test note: %v", err)
		}
	}

	// Тестируем получение заметок пользователя
	foundNotes, err := GetNotesByUser(db, user.ID)
	if err != nil {
		t.Errorf("GetNotesByUser() error = %v", err)
		return
	}

	if len(foundNotes) != 2 {
		t.Errorf("GetNotesByUser() returned %d notes, want %d", len(foundNotes), 2)
	}

	// Проверяем, что заметки принадлежат правильному пользователю
	for _, note := range foundNotes {
		if note.UserID != user.ID {
			t.Errorf("GetNotesByUser() note.UserID = %d, want %d", note.UserID, user.ID)
		}
	}
}

func TestUpdateNote(t *testing.T) {
	db := setupTestDB(t)
	defer db.Close()

	// Создаём тестового пользователя
	user := &User{
		Username:     "testuser",
		PasswordHash: "hashedpassword",
	}
	err := CreateUser(db, user)
	if err != nil {
		t.Fatalf("Failed to create test user: %v", err)
	}

	// Создаём тестовую заметку
	note := &Note{
		UserID:  user.ID,
		Title:   "Original Title",
		Content: "Original content",
	}
	err = CreateNote(db, note)
	if err != nil {
		t.Fatalf("Failed to create test note: %v", err)
	}

	// Обновляем заметку
	updatedNote := &Note{
		Title:   "Updated Title",
		Content: "Updated content",
	}

	ok, err := UpdateNote(db, note.ID, user.ID, updatedNote)
	if err != nil {
		t.Errorf("UpdateNote() error = %v", err)
		return
	}

	if !ok {
		t.Error("UpdateNote() should return true for successful update")
	}

	// Проверяем, что заметка обновилась
	notes, err := GetNotesByUser(db, user.ID)
	if err != nil {
		t.Errorf("Failed to get notes: %v", err)
		return
	}

	if len(notes) == 0 {
		t.Error("Note not found after update")
		return
	}

	if notes[0].Title != "Updated Title" {
		t.Errorf("UpdateNote() title = %s, want %s", notes[0].Title, "Updated Title")
	}
}

func TestDeleteNote(t *testing.T) {
	db := setupTestDB(t)
	defer db.Close()

	// Создаём тестового пользователя
	user := &User{
		Username:     "testuser",
		PasswordHash: "hashedpassword",
	}
	err := CreateUser(db, user)
	if err != nil {
		t.Fatalf("Failed to create test user: %v", err)
	}

	// Создаём тестовую заметку
	note := &Note{
		UserID:  user.ID,
		Title:   "Test Note",
		Content: "Test content",
	}
	err = CreateNote(db, note)
	if err != nil {
		t.Fatalf("Failed to create test note: %v", err)
	}

	// Удаляем заметку
	ok, err := DeleteNote(db, note.ID, user.ID)
	if err != nil {
		t.Errorf("DeleteNote() error = %v", err)
		return
	}

	if !ok {
		t.Error("DeleteNote() should return true for successful deletion")
	}

	// Проверяем, что заметка удалилась
	notes, err := GetNotesByUser(db, user.ID)
	if err != nil {
		t.Errorf("Failed to get notes: %v", err)
		return
	}

	if len(notes) != 0 {
		t.Errorf("DeleteNote() note still exists, want 0 notes, got %d", len(notes))
	}
} 