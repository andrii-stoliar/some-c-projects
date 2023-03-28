#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <math.h>
#include <signal.h>
#include <time.h>

#define PORT 7218

timer_t vytvorCasovac(int);
void spustiCasovac(timer_t, int);
int main(void){

	//spustim casovac

	timer_t casovac;
  	casovac=vytvorCasovac(SIGKILL);
  	spustiCasovac(casovac,60);
  	printf("After 1 minute programm will stop automatically\n");

	// values for speed counting

	char plist[8] = {'M', 'V', 'E', 'm', 'J', 'S', 'U', 'N'};
	float pvalue[8] = {2.43, 6.06, 6.38, 3.37, 6.99, 5.85, 2.33, 2.21};
	float pcoff[8] = {6, 6, 6, 6, 7, 7, 7, 7};
	float pgrav[8] = {3.59, 8.87, 9.81, 3.77, 25.95, 11.08, 10.67, 14.07};
	


	int high = 0;
	char planet = '\0';

	//creating server socket
	
	int sockfd;
	int ret;
	struct sockaddr_in serverAddr;
	
	int newSocket;
	struct sockaddr_in newAddr;
	
	socklen_t addr_size;
	
	char buffer[1024];
	bzero(buffer, sizeof(buffer));

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		printf("!Error in connection!\n");
		exit(1);
	}
	printf("Server socket was created\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	ret = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0){
		printf("!Error in binding!\n");
		close(newSocket);
		close(sockfd);
		exit(1);
	}
	printf("Bind to port %d\n", 7218);

	if(listen(sockfd, 10) == 0){
		printf("Listening...\n");
	}else{
		close(newSocket);
		close(sockfd);
		printf("!Error in binding!\n");
	}

	//connecting to first client and working with them

	newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
	if(newSocket < 0){
		printf("Error, try again later\n");
		close(newSocket);
		close(sockfd);
		exit(1);
	}
	printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
	recv(newSocket, buffer, 1024, 0);
	printf("Clients planet key word: %s\n", buffer);
	planet = buffer[0];
	bzero(buffer, sizeof(buffer));

	//connecting to second client and working with them

	newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
	if(newSocket < 0){
		exit(1);
	}
	printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
	recv(newSocket, buffer, 1024, 0);
	sscanf(buffer, "%d", &high);
	printf("Clients high: %s\n", buffer);
	bzero(buffer, sizeof(buffer));
	//count speed

	int pn = 0;
	for(int j = 0; j<8; j++){
		if(plist[j] == planet){
			pn = j;	
		}
	}

	float result;
	float res;
	result = pgrav[pn]*((pvalue[pn]*pow(10, pcoff[pn]))+high);
	res = sqrt(result);
	//printf("%f", res);
	
	//working with 4th client

	newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);
	if(newSocket < 0){
		exit(1);
	}
	printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
	sprintf(buffer, "%f", res);
	send(newSocket, buffer, strlen(buffer), 0);
	printf("Speed was send to 4th client\nEnd of the program");
	bzero(buffer, sizeof(buffer));

	//closing socket

	sleep(5);
	close(newSocket);
	close(sockfd);
	return 0;
}

timer_t vytvorCasovac(int signal)
{
  struct sigevent kam;
  kam.sigev_notify=SIGEV_SIGNAL;
  kam.sigev_signo=signal;
  
  timer_t casovac;
  timer_create(CLOCK_REALTIME, &kam, &casovac);
  return(casovac); 
}

void spustiCasovac(timer_t casovac, int sekundy)
{
  struct itimerspec casik;
  casik.it_value.tv_sec=sekundy;
  casik.it_value.tv_nsec=0;
  casik.it_interval.tv_sec=0;
  casik.it_interval.tv_nsec=0;
  timer_settime(casovac,CLOCK_REALTIME,&casik,NULL);
}
