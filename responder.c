//server
#include <zmq.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

// ASSIGNMENT: Receive user message from the requester.

int main (void)
{
    //  Socket to talk to clients
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    char buffer [1024]; //message from requester
    char reply[1024];
    char custom_ans[1024] = "I will be glad to help you out. Please hold on while I retrieve more information about";
    int rc = zmq_bind(responder, "tcp://*:3000");

    assert (rc == 0); 
     while (1) {
        zmq_recv (responder, buffer, 1024, 0);
        for(int i = 0; buffer[i]; i++){
            buffer[i] = tolower(buffer[i]);
        }

        if(strstr(buffer, "how are you") != NULL) {
            strcpy(reply, "I am great, how about you?\n");
            zmq_send(responder, reply, 1024, 0);

            zmq_recv (responder, buffer, 1024, 0);
                if (strstr(buffer, "good")!= NULL || strstr(buffer, "well")!= NULL || strstr(buffer, "great")!= NULL) {
                    strcpy(reply, "Glad to hear, how can I help you?\n");
                    zmq_send(responder, reply, 1024, 0);
                    char buffer_new [1024];
                    zmq_recv (responder, buffer_new, 1024, 0);

                    const char *key = "with";
                    char *pos = strstr(buffer, key);
                    pos += strlen(key);
                    strcat(pos, "\n");

                    strcpy(reply, custom_ans);
                    strcat(reply, pos);
                    zmq_send(responder, reply, 1024, 0);

                } else if (strstr(buffer, "bad")!= NULL || strstr(buffer, "sad")!= NULL) {
                    strcpy(reply, "I am sorry to hear this, how can I help you?\n");
                    zmq_send(responder, reply, 1024, 0);

                    char buffer_new [1024];
                    zmq_recv (responder, buffer_new, 1024, 0);
                    const char *key = "with";
                    char *pos = strstr(buffer, key);
                    pos += strlen(key);
                    strcat(pos, "\n");

                    strcpy(reply, custom_ans);
                    strcat(reply, pos);
                    zmq_send(responder, reply, 1024, 0);
                }

        } else if (strstr(buffer, "help") != NULL) {
            const char *key = "with";
            char *pos = strstr(buffer, key);
            pos += strlen(key);
            strcat(pos, "\n");

            strcpy(reply, custom_ans);
            strcat(reply, pos);

            zmq_send(responder, reply, 1024, 0);
        } else if (strstr(buffer, "time") != NULL && (strstr(buffer, "now") != NULL)) {
            time_t ltime;
            time(&ltime);
            strcpy(reply, "Today is ");
            strcat(reply, ctime(&ltime));
            zmq_send(responder, reply, 1024, 0);

        } else if (strstr(buffer, "")!=NULL) {
            strcpy(reply, "Sorry, I do not have the capacity to answer your question.");
            zmq_send(responder, reply, 1024, 0);
        }
    } 

    zmq_close(responder);
    zmq_ctx_destroy(context);

    return 0;
}