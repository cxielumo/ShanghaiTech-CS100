/* CS100 Fall 2026 - HW3 Problem 3: String and character manipulation
 *
 * Implement the hw3_* functions below. Do NOT write a main function here:
 * the autograder compiles this file together with its own test driver.
 * Implementations must conform to the C standard (see cppreference) and
 * must not call any standard library string/character functions.
 * Do not rename this file.
 */
#include <stddef.h>

int hw3_islower(int ch) { return ch >= 'a' && ch <= 'z'; }
int hw3_isupper(int ch) { return ch >= 'A' && ch <= 'Z'; }
int hw3_isalpha(int ch) { return hw3_islower(ch) || hw3_isupper(ch); }
int hw3_isdigit(int ch) { return ch >= '0' && ch <= '9'; }
int hw3_tolower(int ch) { return hw3_isupper(ch) ? ch + ('a' - 'A') : ch; }
int hw3_toupper(int ch) { return hw3_islower(ch) ? ch - ('a' - 'A') : ch; }

size_t hw3_strlen(const char *str)
{
    size_t length = 0;
    while (str[length] != '\0') ++length;
    return length;
}

char *hw3_strchr(const char *str, int ch)
{
    for (;;) {
        if (*str == (char)ch) return (char *)str;
        if (*str == '\0') return NULL;
        ++str;
    }
}

char *hw3_strcpy(char *dest, const char *src)
{
    char *result = dest;
    while ((*dest++ = *src++) != '\0');
    return result;
}

char *hw3_strcat(char *dest, const char *src)
{
    char *result = dest;
    while (*dest != '\0') ++dest;
    while ((*dest++ = *src++) != '\0');
    return result;
}

int hw3_strcmp(const char *lhs, const char *rhs)
{
    while (*lhs != '\0' && *lhs == *rhs) {
        ++lhs;
        ++rhs;
    }
    return (unsigned char)*lhs - (unsigned char)*rhs;
}
