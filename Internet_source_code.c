#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>

int main() {
    int mode;
    printf(" ___ ______ |\\______________________________ ______ |\\_____________________\n");
    printf("|   |\\     \\| |__    ___/_   _____/______   \\     \\| |_   _____/__ ___/\n");
    printf("|   |/   |    | |    |   |    __)_ |       _//   |    ||    __)_  |    |   \n");
    printf("|   |    |\\   | |    |   |        \\|    |   \\    |\\   ||        \\|    |   \n");
    printf("___|____| \\  / |____|  /_______  /|____|_  /____| \\  /_______  / |____|   \n");
    printf("            \\/                  \\/        \\/        \\/           \n");
    printf("\n");
    printf("[1] Test if your connection is stable.\n");
    printf("[2] Test if a host is active(using IP address).\n");
    printf("[3] Find the IP to a Domain.\n");
    printf("\n");
    printf("What do you wanna test?: ");
    scanf("%d", &mode);
    char *host = "www.google.com";
    printf("\n");

    if (mode == 1) {
        printf("Press the button 'b' on your keyboard to stop the test.\n");
        printf("\n");
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);

        fd_set set;
        struct timeval timeout;
        int rv;

        int status3 = 0;

        while (1) {
            int status = system("ping -c 1 www.google.com > /dev/null");
            if (status == 0) {
                if (status3 == 5) {
                    status3 = 1;
                }
                if (status3 == 0) {
                    printf("\rConnection is stable.....\\");
                }

                if (status3 == 1) {
                    printf("\rConnection is stable.....\\ ");
                }
                
                if (status3 == 2) {
                    printf("\rConnection is stable.....| ");
                }
                
                if (status3 == 3) {
                    printf("\rConnection is stable...../ ");
                }
                
                if (status3 == 4) {
                    printf("\rConnection is stable.....- ");
                }
                
            } else {
                printf("Connection is unstable.\n");
                break;
            }

            FD_ZERO(&set);
            FD_SET(STDIN_FILENO, &set);
            timeout.tv_sec = 0;
            timeout.tv_usec = 0;

            rv = select(STDIN_FILENO + 1, &set, NULL, NULL, &timeout);
            if (rv == 1) {
                char c;
                read(STDIN_FILENO, &c, 1);
                if (c == 'b') {
                    printf("\rConnection is stable!     ");
                    printf("\n");
                    break;
                }
            }
            status3 = status3 + 1;
            sleep(0.1); //
        }

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    }

    char ipadress[50];
    char command1[50];

    if (mode == 2) {
        printf("Type in the IP address: ");
        scanf("%s", ipadress);
        sprintf(command1, "ping -c 1 %s > /dev/null", ipadress);
        int status2 = system(command1);
        if(status2 == 0){

            printf("Host active!\n");
        }
    }

    char command2[50];

    char host2[50];
    if (mode == 3) {
        printf("Type in the domain:");
        scanf("%s", host2);
        sprintf(command2, "host %s", host2);
        printf("\n");
        system(command2);
    }

    return 0;
}
