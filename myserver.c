//Server.c
#include <stdio.h> 
#include <arpa/inet.h>
#include <fcntl.h> 
#include <unistd.h> 
#include <string.h>
#include <stdlib.h>

long int contentSize; 

long int getFileSize(FILE* file){
    fseek(file, 0L, SEEK_END);
    long int fileSize = ftell(file);
    rewind(file);
    
    return fileSize;
} 

char* getFile(char* fileName){
    FILE *file = fopen(fileName, "r");
    if(file == NULL)
        return "404 Not Found";
    long int fileSize = getFileSize(file);
    char* buffer = malloc(fileSize);
    fread(buffer, fileSize, 1, file);
    fclose(file);
    printf("%s\t%li", fileName, fileSize);
    contentSize = fileSize;
    return buffer;
}



char* index_(){
     return getFile("index.html");
}

char* login_(){
     return getFile("login.html");
}

char* register_(){
     return getFile("register.html");
}


int send_response(int new_soc, char *response, char *content_type, char *content, int content_length) {
    char response_header[1024];
    sprintf(response_header, "HTTP/1.1 %s\r\nContent-Type: %s; charset=utf-8\r\nContent-Length: %d\r\n\r\n", response, content_type, content_length);
    send(new_soc, response_header, strlen(response_header), 0);
    // if(strcmp(content, "404 Not Found") != 0)
    send(new_soc, content, content_length, 0);
    

}

char* getRoute(char * route){
    if(route == 0x0){
       char* res = malloc(13);
        strcpy(res, "404 Not Found");
        return res; 
    }
        
    if(strcmp(route, "/") == 0)
        return index_();
    if(strcmp(route, "/login") == 0)
        return login_();
    if(strcmp(route, "/register") == 0)
        return register_();
    
    char* res = malloc(13);
    strcpy(res, "404 Not Found");
    return res;
}


//decode http request and return the content of the file
char *decode_request(char *request) {
    char *res = strtok(request, "\n");
    printf("\n\n%s\n\n", res);
    char *route = strtok(request, " ");
    route = strtok(NULL, " ");
    
    return getRoute(route);
}





int main() 
{ 
    int welcome, new_soc, fd, n; 
    char buffer[1024*10], request[1024]; 
    struct sockaddr_in addr; 
    
    printf("\nServer is Online"); 

    welcome = socket(PF_INET, SOCK_STREAM, 0); 

    addr.sin_family = AF_INET; 
    addr.sin_port = htons(7891); 
    addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    bind(welcome, (struct sockaddr *) &addr, sizeof(addr)); 

    /*  listen for connections from the socket */ 
    listen(welcome, 5); 
    /*  accept a connection, we get a file descriptor */ 
    new_soc = accept(welcome, NULL, NULL); 
    char *content;
    while(1){
        recv(new_soc, request, 1024, 0);
        content = decode_request(request);
        if(strcmp(content, "404 Not Found") == 0) {
            send_response(new_soc, "404 Not Found", "text/html", content, strlen(content));
        }
        else{
            send_response(new_soc, "200 OK", "text/html", content, contentSize);
        }
        free(content); 
    }
    return 0;
}

