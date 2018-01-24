
#include "adafruitss.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <iostream>
#include <string.h>

upm::adafruitss* servos = new upm::adafruitss(1, 0x40);

int sockfd, newsockfd;
char buffer[6];
struct sockaddr_in serv_addr;

void cl()
{
	close(newsockfd);
	close(sockfd);
}

int main( int argc, char *argv[] ) 
{
	//cl();
	atexit(cl);
	int port = atoi(argv[1]);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0)
	{
		perror("ERROR opening socket");
		exit(1);
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);


	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		perror("ERROR on binding");
		exit(1);
	}

	listen(sockfd,5);

	while(true)
	{
		newsockfd = accept(sockfd, (struct sockaddr *)NULL, NULL);

		if (newsockfd < 0)
		{
			perror("ERROR on accept");
			exit(1);
		}

		bzero(buffer, 6);
		while (read(newsockfd, buffer, 6) >= 0)
		{
			std::cout << "Read:" << buffer << "\n";
			std::string ServoNum; ServoNum += buffer[0]; ServoNum += buffer[1];
			std::string Val; Val += buffer[2]; Val += buffer[3]; Val += buffer[4]; Val += buffer[5];
			servos->servo(atoi(ServoNum.c_str()), 1, atoi(Val.c_str()));
			bzero(buffer, 6);
		}
	}

	return 0;
}
