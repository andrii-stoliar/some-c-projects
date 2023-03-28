#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

#define PORT 7218

sem_t semaphore; 

void* client1(){
	sem_wait(&semaphore);
	int clientSocket;
	int ret;
	struct sockaddr_in serverAddr;
	char buffer[1024];

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0){
		printf("!Error in connection!\n");
		exit(1);
	}
	printf("Client 1 socket was created\n");
	
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
	printf("Hi, you are first clientf, you need to choose your planet\n");
	printf("Planets of solar system:\nM - Mercury\nV - Venus\nE - Earth\nm - Mars\nJ - Jupiter\nS - Saturn\nU - Uranus\nN - Neptune\nWrite key letter of your planet: ");
	int j = 0;
	do{
		scanf("%s", &buffer[0]);
		if(buffer[0] == 'M' || buffer[0] == 'V' || buffer[0] == 'E' || buffer[0] == 'm' || buffer[0] == 'J' || buffer[0] == 'S' || buffer[0] == 'U' || buffer[0] == 'N'){
			j = 1;
		}else{
			printf("\nInvalid key letter, try again: ");
		}
	}while(j == 0);

	printf("\nValuable key letter\nClient:%s\n", buffer);
	send(clientSocket, buffer, strlen(buffer), 0);
	bzero(buffer, sizeof(buffer));
	close(clientSocket);
	sem_post(&semaphore);
}

void* client2(){
	sem_wait(&semaphore);
	int clientSocket;
	int ret;
	struct sockaddr_in serverAddr;
	char buffer[1024];

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0){
		printf("!Error in connection!\n");
		exit(1);
	}
	printf("\nClient 2 socket was created\n");
	
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
	printf("Hi, you are the second clientf, you need to choose your height from 0m to 15000m\nPrint:");
	int i = 0;
	do{
		scanf("%s", &buffer[0]);
		int high;
		sscanf(buffer, "%d", &high);
		if(high >= 0 && high <= 15000){
				i = 1;
		}else{
				printf("\nInvalid high, try again: ");
		}
	}while(i == 0);

	printf("\nValuable high\nClient:%s\n", buffer);
	send(clientSocket, buffer, strlen(buffer), 0);
	bzero(buffer, sizeof(buffer));
	close(clientSocket);
	sem_post(&semaphore);
}

int main(){

	sem_init(&semaphore, 0, 1);
	pthread_t t1, t2;
	pthread_create(&t1, NULL, &client1, NULL);
	sleep(3);
	pthread_create(&t2, NULL, &client2, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	
	sem_destroy(&semaphore);
	return 0;

}
