// //Server.c
// #include <stdio.h> 
// #include <arpa/inet.h>
// #include <fcntl.h> 
// #include <unistd.h> 
// #include <string.h>
// int main() 
// { 
//     int welcome, new_soc, fd, n; 
//     char buffer[1024*10], fname[50]; 
//     struct sockaddr_in addr; 

//     welcome = socket(PF_INET, SOCK_STREAM, 0); 

//     addr.sin_family = AF_INET; 
//     addr.sin_port = htons(7891); 
//     addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
//     bind(welcome, (struct sockaddr *) &addr, sizeof(addr)); 
//     printf("\nServer is Online"); 

//     /*  listen for connections from the socket */ 
//     listen(welcome, 5); 
//     /*  accept a connection, we get a file descriptor */ 
//     new_soc = accept(welcome, NULL, NULL); 
//     char response[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length: 1024\r\n\r\n";

//     /*  receive the filename */ 
//     recv(new_soc, fname, 50, 0); 
//     printf("\n\n%s\n\n", fname);
//     strcpy(fname, "index.html");
    
//     send(new_soc, response, strlen(response), 0);

//     fd = open("index.html", O_RDONLY);
//     read(fd, buffer, sizeof(buffer));
//         printf("%s", buffer);
//     send(new_soc, buffer, strlen(buffer), 0);

//     // send(new_soc, h, strlen(h), 0);


//     //repoand to GET request by sending the index.html file
    


//     // printf("\nRequesting for file: %s\n", fname); 
//     // send(new_soc, "HTTP/1.1 404 Not Found", 15, 0);
//     /*  open the file and send its contents */ 
//     // fd = open(fname, O_RDONLY); 
//     // if (fd < 0) 
//     //     send(new_soc, "\nFile not found\n", 15, 0); 
//     // else 
//     //     while ((n = read(fd, buffer, sizeof(buffer))) > 0) 
//     //         send(new_soc, buffer, n, 0); 
//     // printf("\nRequest sent\n"); 
//     // close(fd);

//     return 0;
// }

// //Client.c

// #include <stdio.h> 
// #include <arpa/inet.h> 
// #include <fcntl.h> 
// #include <unistd.h> 
// int main() 
// { 
//     int soc, n; 
//     char buffer[1024], fname[50]; 
//     struct sockaddr_in addr; 

//     /*  socket creates an endpoint for communication and returns a file descriptor */ 
//     soc = socket(PF_INET, SOCK_STREAM, 0); 

//     /* 
//      * sockaddr_in is used for ip manipulation 
//      * we define the port and IP for the connection. 
//      */ 
//     addr.sin_family = AF_INET; 
//     addr.sin_port = htons(7891); 
//     addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

//     /*  keep trying to esatablish connection with server */ 
//     while(connect(soc, (struct sockaddr *) &addr, sizeof(addr))) ; 
//     printf("\nClient is connected to Server"); 
//     printf("\nEnter file name: "); 
//     scanf("%s", fname); 
//     /*  send the filename to the server */ 
//     send(soc, fname, sizeof(fname), 0); 

//     printf("\nRecieved response\n"); 
//     /*  keep printing any data received from the server */ 
//     while ((n = recv(soc, buffer, sizeof(buffer), 0)) > 0) 
//         printf("%s", buffer); 

//     return 0; 
// }

//server.c

#include <stdio.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
    int welcome, new_soc, fd, n;
    char buffer[1024], fname[50];
    struct sockaddr_in addr;
    welcome = socket(PF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(7891);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(welcome, (struct sockaddr *) &addr, sizeof(addr));
    printf("\nServer is Online");
    /*  listen for connections from the socket */
    listen(welcome, 5);
    /*  accept a connection, we get a file descriptor */
    new_soc = accept(welcome, NULL, NULL);
    /*  receive the filename */
    recv(new_soc, fname, 50, 0);
    printf("\nRequesting for file: %s\n", fname);
    /*  open the file and send its contents */
    fd = open(fname, O_RDONLY);
    if (fd < 0)
        send(new_soc, "\nFile not found\n", 15, 0);
    else
        while ((n = read(fd, buffer, sizeof(buffer))) > 0)
            send(new_soc, buffer, n, 0);
    printf("\nRequest sent\n");
    close(fd);
    return 0;
}
