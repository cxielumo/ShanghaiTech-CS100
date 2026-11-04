/* CS100 Fall 2026 - HW3 Problem 2: Palindrome
 *
 * Read n strings and test whether each of them is a palindrome.
 * Print "Yes" / "No" on one line per string.
 * Use dynamic memory to store each input string (no fixed-size arrays).
 * Do not rename this file.
 */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        int length;
        scanf("%d", &length);
        char *str = malloc(length + 1);

        scanf("%s", str);
        int palindrome = 1;
        for (int j = 0; j < length / 2; ++j) {
            if (str[j] != str[length - 1 - j]) {
                palindrome = 0;
                break;
            }
        }
        puts(palindrome ? "Yes" : "No");
        free(str);
    }
    return 0;
}
