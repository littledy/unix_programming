#include <string.h>
#include <stdio.h>

// strtok的行为
// char *strtok(char *s1, const char *s2);
// 从 s1 头开始搜索，首先找到 s1 中不包含 s2 中字符的字符，未找到返回空指针
// 找到则标记这个字符，记为 ret_char，接着在 s1 中查找 s2 中包含的字符，未找到则返回空指针
// 找到则将找到的这个字符设为空字符 '\0'，返回 ret_char，并保存指向这个空字符的下一个字符的指针，下一次搜索从这个字符开始
int main() {
    static char str[] = "?a???b,,,#c";
    char *t;

    t = strtok(str, "?");   // "a"
    printf("t: %s\n", t);
    // t = strtok(NULL, "?");
    // printf("t: %s\n", t);
    t = strtok(NULL, ",");  // "??b"
    printf("t: %s\n", t);
    t = strtok(NULL, "#,"); // c
    printf("t: %s\n", t);
    t = strtok(NULL, "?");  // NULL
    if (t != NULL)
        printf("t: %s\n", t);
    else
        printf("t is NULL\n");
}


