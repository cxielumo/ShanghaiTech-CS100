/* CS100 Fall 2026 - HW2 Problem 5: CPU emulator
 *
 * Emulate a toy CPU with registers x0..x5 (16-bit signed, x0 always 0)
 * executing add/sub/mul/div/let/print instructions read as hex words.
 * Do not use <math.h>. Do not rename this file.
 */
#include <stdio.h>

int main(void)
{
    int n;
    long x[6] = {0};

    scanf("%d", &n);
    for (int i = 0; i < n; i += 1) {
        unsigned int code;
        scanf("%x", &code);
        unsigned int op = (code >> 13) & 7u;
        unsigned int r1 = (code >> 10) & 7u;
        unsigned int r2 = (code >> 7) & 7u;
        unsigned int imm = code & 127u;

        if (op == 5u) {
            printf("x%u = %ld\n", r1, x[r1]);
            continue;
        }
        if (r1 == 0u) {
            continue;
        }

        long ans;
        switch (op) {
        case 0:
            ans = x[r1] + x[r2];
            break;
        case 1:
            ans = x[r1] - x[r2];
            break;
        case 2:
            ans = x[r1] * x[r2];
            break;
        case 3:
            ans = x[r1] / x[r2];
            break;
        case 4:
            ans = (long)imm;
            break;
        default:
            continue;
        }

        /* Keep the low 16 bits and interpret them as a signed value. */
        ans %= 65536L;
        if (ans < 0) {
            ans += 65536L;
        }
        if (ans >= 32768L) {
            ans -= 65536L;
        }
        x[r1] = ans;
    }
    return 0;
}
