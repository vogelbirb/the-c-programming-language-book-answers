#include <stdio.h>

#define STRING_LEN 100

void escape(char s[], char t[], int len);
void unescape(char s[], char t[], int len);

int main() {
    char unescaped[STRING_LEN] = "Hello\nWorld!\nOne\tTwo\n";
    char escaped[STRING_LEN] = "Hello\\nWorld!\\nOne\\tTwo\\n";
    char s[STRING_LEN + 2] = "";
    
    escape(s, unescaped, STRING_LEN);
    printf("%s\n", s);

    unescape(s, escaped, STRING_LEN);
    printf("%s", s);
    
    return 0;
}

// Writes t[] into s[] with newlines and tabs replaced with "\n" and "\t" respectively, with bounds checking for s[]
void escape(char s[], const char t[], int len) {
    // k = s[] pointer, i = t[] pointer
    int c, i = 0, k = 0;
    
    while (t[i] != '\0' && k < len - 1) {
        switch (t[i]) {
            case '\n':
                if (k < len - 2) {
                    s[k] = '\\';
                    s[++k] = 'n';
                }
                break;
            case '\t':
                if (k < len - 2) {
                    s[k] = '\\';
                    s[++k] = 't';
                }
                break;
            default:
                s[k] = t[i];
                break;
        }
        k++;
        i++;
    }
    s[k] = '\0';
}

// Writes t[] into s[] with character sequences "\n" and "\t" replaced with their actual characters, with bounds checking for s[]
void unescape(char s[], const char t[], int len) {
    // k = s[] pointer, i = t[] pointer
    int c, i = 0, k = 0;
    
    while (t[i] != '\0' && i < len - 1) {
        switch (t[i]) {
            case 'n':
                if (s[k - 1] == '\\') {
                    s[--k] = '\n';
                    break;
                } 
            case 't':
                if (s[k - 1] == '\\') {
                    s[--k] = '\t';
                    break;
                }
            default:
                s[k] = t[i];
                break;
        }
        k++;
        i++;
    }
    s[k] = '\0';
}
