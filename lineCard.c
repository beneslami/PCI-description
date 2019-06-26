#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){
        /* The file fp is for checking if the package is installed*/
        FILE *fp;
        char command[30];
        char data[512];

        /* The file fp2 is for getting the data from command line output */
        FILE *fp2;
        char command2[10];
        char data2[512];

        sprintf(command, "dpkg -s inxi | grep Status");
        fp = popen(command, "r");
        fgets(data, 512, fp);
        char *buffer, *content;
        int p1, p2, i=0;
        int flag1 = 0;
        int flag2 = 0;
        if (strstr(data, "install ok installed")!= NULL){
                sprintf(command2, "inxi -Fx");
                fp2 = popen(command2, "r");
                while(fgets(data2, 512, fp2) != NULL){
                        if(strstr(data2, "Network:") != NULL){
                                flag1 = 1;
                        }
                        if(strstr(data2, "Drives:") != NULL){
                                flag2 = 1;
                        }
                        if(flag2 == 1){
                                break;
                        }
                        if(flag1 == 1){
                                printf("%s", data2);
                        }
                }
        }
        else{
          system("apt install inxi");
                          fp = popen(command, "r");
        }

        memset(fp, 0, sizeof(fp));
        memset(fp2, 0, sizeof(fp));
        memset(command, '\0', sizeof(command));
        memset(data, '\0', sizeof(command));
        memset(command2, '\0', sizeof(command));
        memset(data2, '\0', sizeof(command));

        printf("-------------------------------------\n");
        sprintf(command, "lspci -m |grep Ethernet | awk '{print $1}'");
        fp = popen(command, "r");
        while(fgets(data, 512, fp) != NULL){
            sprintf(command2, "lspci -vs %s", data);
            fp2 = popen(command2, "r");
            while(fgets(data2, 512, fp2) != NULL){
              printf("%s", data2);
            }
        }

        pclose(fp);
        fclose(fp2);
        return 0;
  }
