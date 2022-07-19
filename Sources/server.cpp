/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ablondel <ablondel@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:24:09 by ablondel          #+#    #+#             */
/*   Updated: 2022/06/29 17:48:25 by ablondel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/poll.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <fcntl.h>
#define PORT 8000

int main(void)
{
	//////////////////////////////////////////////////////////////////////////////////////////////SOCKET
	int serverfd;
	int new_socket;
	int ret;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	const char *hello = "HTTP/1.0 200OK\r\n\r\nHello World!";
	serverfd = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(PORT);
	memset(address.sin_zero, 0, sizeof(address.sin_zero));
	bind(serverfd, (struct sockaddr*)&address, sizeof(address));
	listen(serverfd, 10);
	//////////////////////////////////////////////////////////////////////////////////////////////EPOLL
	int event_count;
	struct pollfd event;

	while(1)
    {
        char read_buffer[30000];
		bzero(&read_buffer, sizeof(read_buffer));
        //printf("\n+++++++ Waiting for new connection ++++++++\n");
        if ((new_socket = accept(serverfd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
        {
            std::cerr << "ACCEPT" << std::endl;
            exit(EXIT_FAILURE);
		}
        ret = read(new_socket, read_buffer, 30000);
        //printf("[[[%s]]]\n", read_buffer);
        write(new_socket, hello, strlen(hello));
        close(new_socket);
    }
	return 0;
}
