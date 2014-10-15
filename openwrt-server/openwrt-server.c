#include <netinet/in.h>    // for sockaddr_in
#include <sys/types.h>    // for socket
#include <sys/socket.h>    // for socket
#include <stdio.h>        // for printf
#include <stdlib.h>        // for exit
#include <string.h>        // for bzero
#include <unistd.h>  
#include <sys/stat.h>
#include <fcntl.h> 
#include <termios.h>
#include <errno.h>

int8_t com_init();
void send_cmd(unsigned char cmd);

#define HELLO_WORLD_SERVER_PORT    3333 
#define LENGTH_OF_LISTEN_QUEUE 20
#define BUFFER_SIZE 1024
#define FILE_NAME_MAX_SIZE 512



int main(int argc, char **argv)
{
        com_init();
        //设置一个socket地址结构server_addr,代表服务器internet地址, 端口
        struct sockaddr_in server_addr;
        bzero(&server_addr,sizeof(server_addr)); //把一段内存区的内容全部设置为0
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = htons(INADDR_ANY);
        server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);

        //创建用于internet的流协议(TCP)socket,用server_socket代表服务器socket
        int server_socket = socket(PF_INET,SOCK_STREAM,0);
        if( server_socket < 0)
        {
                printf("Create Socket Failed!");
                exit(1);
        }
        { 
                int opt =1;
                setsockopt(server_socket,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
        }

        //把socket和socket地址结构联系起来
        if( bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr)))
        {
                printf("Server Bind Port : %d Failed!", HELLO_WORLD_SERVER_PORT); 
                exit(1);
        }

        //server_socket用于监听
        if ( listen(server_socket, LENGTH_OF_LISTEN_QUEUE) )
        {
                printf("Server Listen Failed!"); 
                exit(1);
        }

        printf("Server Start Listen!\n");
        while (1) //服务器端要一直运行
        {
                //定义客户端的socket地址结构client_addr
                struct sockaddr_in client_addr;
                socklen_t length = sizeof(client_addr);
                //接受一个到server_socket代表的socket的一个连接
                //如果没有连接请求,就等待到有连接请求--这是accept函数的特性
                //accept函数返回一个新的socket,这个socket(new_server_socket)用于同连接到的客户的通信
                //new_server_socket代表了服务器和客户端之间的一个通信通道
                //accept函数把连接到的客户端信息填写到客户端的socket地址结构client_addr中
                int new_server_socket = accept(server_socket,(struct sockaddr*)&client_addr,&length);
                if ( new_server_socket < 0)
                {
                        printf("Server Accept Failed!\n");
                        break;
                }
                char buffer[BUFFER_SIZE];
                bzero(buffer, BUFFER_SIZE);
                length = recv(new_server_socket,buffer,BUFFER_SIZE,0);
                if (length < 0)
                {
                        printf("Server Recieve Data Failed!\n");
                        break;
                }
                if(length > 0){
                        printf("the receive string is %s \n", buffer);
                        if(!strcmp("close led",buffer)){
                                send_cmd(0x01);	
                                printf("close led \n");
                        }
                        else if(!strcmp("open led",buffer)){
                                send_cmd(0x02);
                                printf("open led \n");
                        }
                        else if(!strcmp("close fan",buffer)){
                                send_cmd(0x03);
                                printf("close fan \n");
                        }
                        else if(!strcmp("fan 1",buffer)){
                                send_cmd(0x04);
                                printf("fan 1 \n");
                        }
                        else if(!strcmp("fan 2",buffer)){
                                send_cmd(0x05);
                                printf("fan 2 \n");					
                        }
                }
                //关闭与客户端的连接
                //close(new_server_socket);
        }
        //关闭监听用的socket
        close(server_socket);
        return 0;
}
int fd; 
int8_t com_init()
{

        struct termios opt;
        fd = open("/dev/ttyATH0", O_RDWR|O_NOCTTY|O_NDELAY);
        if(fd == -1){
                perror("open serial 0\n");
                exit(0);  
        }

        tcgetattr(fd, &opt);      
        bzero(&opt, sizeof(opt));

        tcflush(fd, TCIOFLUSH);

        cfsetispeed(&opt, B115200);
        cfsetospeed(&opt, B115200);

        opt.c_cflag &= ~CSIZE;  
        opt.c_cflag |= CS8;   
        opt.c_cflag &= ~CSTOPB; 
        opt.c_cflag &= ~PARENB; 
        opt.c_cflag &= ~CRTSCTS;
        opt.c_cflag |= (CLOCAL | CREAD);

        opt.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

        opt.c_oflag &= ~OPOST;

        opt.c_cc[VTIME] = 0;
        opt.c_cc[VMIN] = 0;

        tcflush(fd, TCIOFLUSH);

        printf("configure complete\n");

        if(tcsetattr(fd, TCSANOW, &opt) != 0){
                perror("serial error");
                return -1;
        }

        printf("start send and receive data\n");

        /* while(1)*/
        /*{    */
        /*n = 0;*/
        /*len = 0;*/
        /*bzero(read_buf, sizeof(read_buf)); */
        /*bzero(write_buf, sizeof(write_buf));*/
        /*[>n = read(fd, read_buf, sizeof(read_buf));<]*/
        /*len = sprintf(write_buf,"fuck you");*/
        /*n = write(fd, write_buf, len);*/
        /*printf("write %d chars\n",n);*/
        /*sleep(2);*/

        /*}*/
        return 0;
}
void send_cmd(unsigned char cmd)
{
        int len;
        int n = 0; 
        //	char read_buf[50];
        char write_buf[50];
        n = 0;
        len = 3;
        //	bzero(read_buf, sizeof(read_buf)); 
        bzero(write_buf, sizeof(write_buf));
        //	n = read(fd, read_buf, sizeof(read_buf));
        //	len = sprintf(write_buf,"fuck you");
        write_buf[0]=0xfe;write_buf[1]=0x00;write_buf[2]=cmd;
        n = write(fd, write_buf, len);
        printf("write %d chars\n",n);
}

