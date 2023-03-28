#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <math.h>

#define PORT 7218

int main(){
	int fd[2];
	if(pipe(fd) == -1){
		printf("Error");
		return 1;
	}
	int id = fork();

	if (id == 0){
		//3rd client
		close(fd[0]);
		printf("Hello, you are 3rd client, please choose speed: 1 or 2: ");
		int i = 0;
		int num = 0;
		do{
			scanf("%d", &num);
			if(num == 1 || num == 2){
				i = 1;
			}else{
				printf("\nInvalid value, try again: ");
			}
		}while(i == 0);
		write(fd[1], &num, sizeof(int));
		close(fd[1]);
	}else{
		//4th client
		close(fd[1]);
		int cof;
		read(fd[0], &cof, sizeof(int));
		close(fd[0]);
		printf("\n\nHi, you are 4th client, server is going to send you %d speed", cof);

		//connecting to server
		int clientSocket;
		int ret;
		struct sockaddr_in serverAddr;
		char buffer[1024];

		clientSocket = socket(AF_INET, SOCK_STREAM, 0);
		if(clientSocket < 0){
			printf("!Error in connection!\n");
			exit(1);
		}
		printf("\nClient socket was created");
	
		memset(&serverAddr, '\0', sizeof(serverAddr));
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons(PORT);
		serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
		ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
		if (ret < 0){
			printf("!Error in connection!\n");
			exit(1);
		}
		printf("Connected to server\n");
		float result = 0;
		recv(clientSocket, buffer, 1024, 0);
		sscanf(buffer, "%f", &result);
		bzero(buffer, sizeof(buffer));
		float res = 0;
		res = result * sqrt(cof);
		printf("\nYour speed is: %f km/s\nEnd of the program", res);
		close(clientSocket);
		sleep(5);
	}
	return 0;
}
