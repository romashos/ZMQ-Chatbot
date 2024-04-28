
#include <string.h>
#include <stdio.h>
    #ifdef _WIN32
    #include <Windows.h>  // Include Windows.h for Windows
    #else
    #include <unistd.h>   // Include unistd.h for Unix-like systems
    #endif

void CheckActivity (int timeout, int elapsed) {

    #ifdef _WIN32
    Sleep(1000);
    #else
    sleep(1)
    #endif;

    if (elapsed > timeout) {
        printf("No activity for 10 seconds. Signing out.");
        #ifdef _WIN32
        Sleep(1000);
        #else
        sleep(1)
        #endif;

        printf("Closing...");

        #ifdef _WIN32
        Sleep(3000);
        #else
        sleep(1)
        #endif;

        exit(0);
    }

}