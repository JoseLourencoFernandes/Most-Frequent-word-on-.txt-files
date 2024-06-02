#include "utilities.h"
#include <ctype.h>

// Adjusts the string s by converting all uppercase letters to lowercase and replacing the first punctuation character by '\0'.
void adjust(char s[]) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (isupper(s[i])) {
            s[i] = tolower(s[i]);
        } else if (ispunct(s[i])) {
            s[i] = '\0';
            return;
        }
    }
}