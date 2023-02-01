#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  int socket_desc;
  struct sockaddr_in server;
  int first_number, second_number, result;

  // Create socket
  socket_desc = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_desc == -1) {
    printf("Could not create socket");
  }

  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  server.sin_family = AF_INET;
  server.sin_port = htons(8888);

  // Connect to remote server
  if (connect(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0) {
    puts("connect error");
    return 1;
  }

  puts("Connected");

  // Send some data
  send(socket_desc, "add", 3, 0);

// Receive the result
  recv(socket_desc, &result, sizeof(result), 0);

  // Receive the first number
  recv(socket_desc, &first_number, sizeof(first_number), 0);

  // Receive the second number
  recv(socket_desc, &second_number, sizeof(second_number), 0);

  

  printf("First number: %d\n", first_number);
  printf("Second number: %d\n", second_number);
  printf("Result of adding two random numbers: %d\n", result);

  return 0;
}
