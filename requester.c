#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <custom.h>

int main(void) { 
    void *context = zmq_ctx_new();
    if (context == NULL) {
        perror("Failed to create ZMQ context");
        return 1;
    }

    void *requester = zmq_socket(context, ZMQ_REQ);
    if (requester == NULL) {
        perror("Failed to create socket");
        zmq_ctx_destroy(context);
        return 1;
    }
    
    int rc = zmq_connect(requester, "tcp://localhost:3000");
    if (rc != 0) {
        perror("Failed to connect to server");
        zmq_close(requester);
        zmq_ctx_destroy(context);
        return 1;
    }

    char user_msg[1024];
    char buffer[1024];
    int elapsed = 0;

    printf("Hello, I am AM-1335, a simple AI machine developed on C programming language. \nI use ZMQ library for communication. \nMy serial number: 256983655551 \nMy manufacture date: April 27, 2066 \nPlease ask me what you want to know.\n");
    printf("\n");

    while (1) {

        elapsed +=100;
        CheckActivity(1000, elapsed);

        if (_kbhit()) {
            fgets(user_msg, sizeof(user_msg), stdin);
            user_msg[strcspn(user_msg, "\n")] = 0;
            zmq_send(requester, user_msg, 1024, 0);

            zmq_recv(requester, buffer, 1024, 0);
            printf(buffer);
        } else {
            elapsed +=100;
            CheckActivity(1000, elapsed);
        }
    }

    zmq_close(requester);
    zmq_ctx_destroy(context);

    // Prevent the console window from closing immediately
    printf("Press enter to exit...");
    getchar();  

    return 0;
}

