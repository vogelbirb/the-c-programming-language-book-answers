#include <stdio.h>
#include <stdbool.h>

void squeeze(char s[], char char_list[]);
int length(char s[]);

int main() {
    char s[] = "yyymlathlyeusz";
    char chars[] = "lzy";
    
    squeeze(s, chars);
    
    printf("%s\n", s);
}

int length(char s[]) {
    int len = 0;
    while(s[len] != '\0') {
        len++;
    }
    return len;
}

// Removes all letters present in char_list[] from s[]
// Removes up to 10 characters because yes, crashes on more (don't worry about fixing it)
// O(n) + O(n)
void squeeze(char s[], char char_list[]) {

    // Should depend on the size of the char list, but nah cuz yeah
    int to_remove[10] = {0};
    int to_remove_pos = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        for (int j = 0; char_list[j] != '\0'; j++) {
            if (s[i] == char_list[j]) {
                to_remove[to_remove_pos] = i;
                to_remove_pos++;
            }
            break;
        }
    }
      
    int k = 0;
    bool skip = false;
    for(int i = 0; s[i] != '\0'; i++) {
        for (int j = 0; j < 10; j++) {
            if (i == to_remove[j]) {
                skip = true;
                break;
            } 
        }
        if (!skip) {
            s[k] = s[i];
            k++;
        }
        skip = false;
    }

    s[k] = '\0';
}
