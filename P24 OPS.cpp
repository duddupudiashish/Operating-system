#include <stdio.h>
#include <fcntl.h>   
#include <unistd.h>  
#include <string.h>
#include <stdlib.h>

int main() {
    int fd;
    char buffer[100];
    char data[] = "Hello, this is a system call demo.\n";

    
    fd = open("demo.txt", O_CREAT | O_RDWR, 0644);
    if (fd < 0) {
        perror("Error opening file");
        exit(1);
    }
    printf("File 'demo.txt' opened successfully with fd = %d\n", fd);


    if (write(fd, data, strlen(data)) < 0) {
        perror("Error writing to file");
        close(fd);
        exit(1);
    }
    printf("Data written to file.\n");

    
    lseek(fd, 0, SEEK_SET);

    
    int n = read(fd, buffer, sizeof(buffer) - 1);
    if (n < 0) {
        perror("Error reading file");
        close(fd);
        exit(1);
    }
    buffer[n] = '\0';  
    printf("Data read from file:\n%s", buffer);

    close(fd);
    printf("\nFile closed.\n");

    return 0;
}

