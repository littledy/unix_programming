#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main()
{
    DIR *dirp;
    struct dirent *dp;

    dirp = opendir(".");
    if (dirp == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    // 获取当前位置
    long pos = telldir(dirp);
    printf("Current position in directory: %ld\n", pos);

    // 读取并输出目录下的文件名
    while ((dp = readdir(dirp)) != NULL) {
        printf("%s\n", dp->d_name);
    }

    // 回到之前的位置
    seekdir(dirp, pos);
    printf("Back to position %ld\n", pos);

    // 读取并输出剩下的文件名
    while ((dp = readdir(dirp)) != NULL) {
        printf("%s\n", dp->d_name);
    }

    closedir(dirp);
    return 0;
}