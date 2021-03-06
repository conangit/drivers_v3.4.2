#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int fd;
    int ret;
    unsigned char val;
    unsigned char wr_data[3];
    unsigned char rd_data[3];
    
    if (1 == argc)
        val = 0;
    else
        val = (unsigned char)strtoul(argv[1], NULL, 0);
    
    wr_data[0] = 0x10;
    wr_data[1] = 0x10;
    wr_data[2] = val;
    rd_data[0] = 0x10;
    rd_data[1] = 0x10;
    rd_data[2] = 0;
    
    
    fd = open("/dev/at24c256-0", O_RDWR);
    if(fd < 0)
    {
        printf("Open device at24c256-0 failed!\n");
        return -1;
    }
    printf("Open device at24c256-0\n");
    
    ret = write(fd, wr_data, 3);
    if (3 != ret)
    {
        printf("Write error!\n");
        return ret;
    }
    printf("write data: 0x%x\n", wr_data[2]);
    
    // 必须存在!!
    usleep(150);
    
    ret = read(fd, rd_data, 3);
    if (3 == ret)
    {
        printf("read data:  0x%x\n", rd_data[2]);
    }
    else
    {
        printf("Read error!\n");
    }
    
    close(fd);
    return 0;
}
