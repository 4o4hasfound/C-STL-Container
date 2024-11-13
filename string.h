#include <string.h>
#include <stdlib.h>

#ifndef max
#define max(a, b) (a>b?a:b)
#endif

#ifndef min
#define min(a, b) (a<b?a:b)
#endif

#define STRING_INITIALIZE_SIZE 8

typedef struct String {
	char* data;
	int size;
	int capacity;
} String;

extern inline String* string_create();
extern inline String* string_from_char(char c);
extern inline String* string_from_chararr(char* c);
extern inline void string_initialize(String* string);
extern inline void string_copy(String* dest, String* from);
extern inline void string_clear(String* string);
extern inline void string_destroy(String* string);
extern inline void string_destroy_ptr(String* string);
extern inline void string_reserve(String* string, int size);
extern inline void string_resize(String* string, int size);
extern inline void string_append(String* string, char* c);
extern inline void string_append_char(String* string, char c);
extern inline void string_append_string(String* string, String* s);
extern inline void string_append_n(String* string, char* c, int n);
extern inline void string_append_string_n(String* string, String* s, int n);
extern inline void string_insert(String* string, char* c, int index);
extern inline void string_insert_char(String* string, char c, int index);
extern inline void string_insert_string(String* string, String* s, int index);
extern inline void string_insert_n(String* string, char* c, int index, int n);
extern inline void string_insert_string_n(String* string, String* s, int index, int n);
extern inline void string_replace(String* string, char* c, int index);
extern inline void string_replace_char(String* string, char c, int index);
extern inline void string_replace_string(String* string, String* s, int index);
extern inline void string_replace_n(String* string, char* c, int index, int n);
extern inline void string_replace_string_n(String* string, String* s, int index, int n);
extern inline void string_reallocate(String* string, int size);

extern inline String* string_create() {
	String* string = (String*)malloc(sizeof(String));
	string_initialize(string);
	return string;
}
extern inline String* string_from_char(char c) {
	String* string = (String*)malloc(sizeof(String));
	string_initialize(string);
	string_append_char(string, c);
	return string;
}
extern inline String* string_from_chararr(char* c) {
	String* string = (String*)malloc(sizeof(String));
	string_initialize(string);
	string_append(string, c);
	return string;
}
extern inline void string_initialize(String* string) {
	string->data = (char*)malloc(sizeof(char) * (STRING_INITIALIZE_SIZE + 1));
	memset(string->data, 0, sizeof(char) * (STRING_INITIALIZE_SIZE + 1));
	string->size = 0;
	string->capacity = STRING_INITIALIZE_SIZE;
}
extern inline void string_copy(String* dest, String* from) {
	string_initialize(dest);
	string_reallocate(dest, from->capacity);
	memcpy(dest->data, from->data, from->size * sizeof(char));
	dest->size = from->size;
}
extern inline void string_clear(String* string) {
	memset(string->data, 0, string->size * sizeof(char));
	string->size = 0;
}
extern inline void string_destroy(String* string) {
	free(string->data);
}
extern inline void string_destroy_ptr(String* string) {
	free(string->data);
	free(string);
}
extern inline void string_reserve(String* string, int size) {
	if (string->capacity >= size) {
		return;
	}
	char* tmp = (char*)realloc(string->data, size * sizeof(char));
	if (!tmp) {

	}
	memcpy(tmp, string->data, string->size * sizeof(char));
	free(string->data);
	string->data = tmp;
}
extern inline void string_resize(String* string, int size) {
	if (string->capacity < size) {
		string_reallocate(string, size);
	}
	memset(string->data + size, 0, (string->capacity - size) * sizeof(char));
	string->size = size;
}
extern inline void string_append(String* string, char* c) {
	int len = strlen(c);
	if (string->size + len - 1 >= string->capacity) {
		string_reallocate(string, max(string->capacity + len, string->capacity * 2));
	}
	memcpy(string->data + string->size, c, len);
	string->size += len;
}
extern inline void string_append_char(String* string, char c) {
	if (string->size >= string->capacity) {
		string_reallocate(string, string->capacity * 2);
	}
	string->data[string->size++] = c;
}
extern inline void string_append_string(String* string, String* s) {
	if (string->size + s->size - 1 >= string->capacity) {
		string_reallocate(string, max(string->capacity + s->size, string->capacity * 2));
	}
	memcpy(string->data + string->size, s->data, s->size);
	string->size += s->size;
}
extern inline void string_append_n(String* string, char* c, int n) {
	if (string->size + n - 1 >= string->capacity) {
		string_reallocate(string, max(string->capacity + n, string->capacity * 2));
	}
	memcpy(string->data + string->size, c, n);
	string->size += n;
}
extern inline void string_append_string_n(String* string, String* s, int n) {
	if (string->size + n - 1 >= string->capacity) {
		string_reallocate(string, max(string->capacity + n, string->capacity * 2));
	}
	memcpy(string->data + string->size, s->data, n);
	string->size += n;
}
extern inline void string_insert(String* string, char* c, int index) {
	int len = strlen(c);
	if (string->size + len - 1 >= string->capacity) {
		string_reallocate(string, max(string->capacity + len, string->capacity * 2));
	}
	for (int i = string->size + len - 1; i - len >= index; --i) {
		string->data[i] = string->data[i - len];
	}
	memcpy(string->data + index, c, len);
	string->size += len;
}
extern inline void string_insert_char(String* string, char c, int index) {
	if (string->size >= string->capacity) {
		string_reallocate(string, string->capacity * 2);
	}
	for (int i = string->size; i - 1 >= index; --i) {
		string->data[i] = string->data[i - 1];
	}
	string->data[index] = c;
	++string->size;
}
extern inline void string_insert_string(String* string, String* s, int index) {
	if (string->size + s->size - 1 >= string->capacity) {
		string_reallocate(string, max(string->capacity + s->size, string->capacity * 2));
	}
	for (int i = string->size + s->size - 1; i - s->size >= index; --i) {
		string->data[i] = string->data[i - s->size];
	}
	memcpy(string->data + index, s->data, s->size);
	string->size += s->size;
}
extern inline void string_insert_n(String* string, char* c, int index, int n) {
	if (string->size + n - 1 >= string->capacity) {
		string_reallocate(string, max(string->capacity + n, string->capacity * 2));
	}
	for (int i = string->size + n - 1; i - n >= index; --i) {
		string->data[i] = string->data[i - n];
	}
	memcpy(string->data + string->size, c, n);
	string->size += n;
}
extern inline void string_insert_string_n(String* string, String* s, int index, int n) {
	if (string->size + n - 1 >= string->capacity) {
		string_reallocate(string, max(string->capacity + n, string->capacity * 2));
	}
	for (int i = string->size + n - 1; i - n >= index; --i) {
		string->data[i] = string->data[i - n];
	}
	memcpy(string->data + string->size, s->data, n);
	string->size += n;
}
extern inline void string_replace(String* string, char* c, int index) {
	int len = strlen(c);
	if (string->size + len - 1 >= string->capacity) {
		string_reallocate(string, max(string->capacity + len, string->capacity * 2));
	}
	memcpy(string->data + index, c, len);
	string->size = max(string->size, index + len);
}
extern inline void string_replace_char(String* string, char c, int index) {
	if (string->size >= string->capacity) {
		string_reallocate(string, string->capacity * 2);
	}
	string->data[index] = c;
	string->size = max(string->size, index + 1);
}
extern inline void string_replace_string(String* string, String* s, int index) {
	if (string->size + s->size - 1 >= string->capacity) {
		string_reallocate(string, max(string->capacity + s->size, string->capacity * 2));
	}
	memcpy(string->data + index, s->data, s->size);
	string->size = max(string->size, index + s->size);
}
extern inline void string_replace_n(String* string, char* c, int index, int n) {
	if (string->size + n - 1 >= string->capacity) {
		string_reallocate(string, max(string->capacity + n, string->capacity * 2));
	}
	memcpy(string->data + string->size, c, n);
	string->size = max(string->size, index + 1);
}
extern inline void string_replace_string_n(String* string, String* s, int index, int n) {
	if (string->size + n - 1 >= string->capacity) {
		string_reallocate(string, max(string->capacity + n, string->capacity * 2));
	}
	memcpy(string->data + string->size, s->data, n);
	string->size = max(string->size, index + n);
}
extern inline void string_reallocate(String* string, int size) {
	if (string->capacity >= size) {
		return;
	}
	char* tmp = (char*)realloc(string->data, (size + 1) * sizeof(char));
	if (!tmp) {

	}
	memset(tmp + string->capacity, 0, (size - string->capacity + 1) * sizeof(char));
	string->data = tmp;
	string->capacity = size;
}