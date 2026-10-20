/* CS100 Fall 2026 - HW2 Problem 4: GCC argument descriptor
 *
 * Read GCC-style command-line arguments (argv) and print a description
 * for each of them, in order. No standard input in this problem.
 * Do not rename this file.
 */
#include <stdio.h>
#include <string.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
    struct option options[] = {
        {"Wall", no_argument, NULL, 'a'},
        {"Wpedantic", no_argument, NULL, 'p'},
        {"Wextra", no_argument, NULL, 'e'},
        {"Werror", no_argument, NULL, 'w'},
        {"std", required_argument, NULL, 's'},
        {NULL, 0, NULL, 0}
    };
    int opt;

    /* Return input files in order along with the options. */
    while ((opt = getopt_long_only(argc, argv, "-o:I:", options, NULL)) != -1) {
        switch (opt) {
        case 'a':
            printf("-Wall: Enable all the warnings about constructions that some users consider questionable, and that are easy to avoid (or modify to prevent the warning).\n");
            break;
        case 'p':
            printf("-Wpedantic: Issue all the warnings demanded by strict ISO C and ISO C++ and reject all programs that use forbidden extensions.\n");
            break;
        case 'e':
            printf("-Wextra: Enable some extra warning flags that are not enabled by -Wall.\n");
            break;
        case 'w':
            printf("-Werror: Make all warnings into errors.\n");
            break;
        case 'o':
            printf("-o %s: Place the primary output in file %s.\n", optarg, optarg);
            break;
        case 'I':
            printf("-I %s: Add the directory %s to the list of directories to be searched for header files during preprocessing.\n", optarg, optarg);
            break;
        case 's':
            if (strncmp(optarg, "gnu++", 5) == 0) {
                printf("-std=%s: Set the language standard to GNU dialect of C++%s.\n", optarg, optarg + 5);
            } else if (strncmp(optarg, "gnu", 3) == 0) {
                printf("-std=%s: Set the language standard to GNU dialect of C%s.\n", optarg, optarg + 3);
            } else if (strncmp(optarg, "c++", 3) == 0) {
                printf("-std=%s: Set the language standard to ISO C++%s.\n", optarg, optarg + 3);
            } else if (strncmp(optarg, "c", 1) == 0) {
                printf("-std=%s: Set the language standard to ISO C%s.\n", optarg, optarg + 1);
            }
            break;
        case 1:
            char *ext = strrchr(optarg, '.');
            if (strcmp(ext, ".c") == 0) {
                printf("%s: C source code as input file.\n", optarg);
            } else if (strcmp(ext, ".h") == 0) {
                printf("%s: C/C++ header file as input file.\n", optarg);
            } else if (strcmp(ext, ".hpp") == 0 || strcmp(ext, ".hxx") == 0) {
                printf("%s: C++ header file as input file.\n", optarg);
            } else {
                printf("%s: C++ source code as input file.\n", optarg);
            }
            break;
        default:
            return 0;
        }
    }
    return 0;
}
