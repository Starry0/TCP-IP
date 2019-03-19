//
// Created by starry on 19-3-18.
//

#include <stdio.h>
#include <fcntl.h>

int main(void) {
    /**
     * 代码在Ubuntu18.04 上运行出现段错误
     * */
    FILE *fp;
    int fd = open("news.txt",O_WRONLY|O_CREAT|O_TRUNC);
    if(fd == 1) {
        fputs("file open error", stdout);
        return -1;
    }
    fd = fdopen(fd, "w");
    fputs("Network C programming \n",fp);
    fclose(fp);
    return 0;
}