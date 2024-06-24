#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearBuffer()
{
    int tmp;
    do {
        tmp = getchar();
    } while (tmp != EOF && tmp != '\n');
}

int main(int argc,char *argv[]){
		
		if(argc == 1){
				printf("Not enough arguments provided, use 'mounter help' for help.\n");
				return 1;
		}else if(argc == 2 && strcmp(argv[1], "help") == 0){
				printf("\nIf you want to mount an exFat drive with permissions for your user, run the command: \n'mounter 1 [device] [directory]'");
				printf("\n\nIf you want to mount a btrfs drive with zstd compression, noatime and a subvolume, run the command: \n'mounter 2 [subvol] [zstd level] [device] [directory]'");
				printf("\n\nIf none of the options above suits you, this program won't have any advantages over the normal mount command.\n");
				printf("If you have a mount process in mind with a lot of arguments, feel free to contribute or hit me up.\n");
				return 0;
		}

		char command[256];
		char device[128];
		char directory[128];
		char subvolume[128];
		int zstd = 0;
		char confirm;

		if(argc == 4 && strcmp(argv[1], "1") == 0){
				strncpy(device, argv[2],127);
				strncpy(directory, argv[3],127);
				snprintf(command, 256, "sudo mount -o uid=%d,gid=%d %s %s",getuid(),getgid(),device,directory);
				printf("COMMAND: %s\n",command);
				printf("The above command will be executed, do you confirm? (y/n)\n");
				scanf("%c",&confirm);
				clearBuffer();
				if(confirm == 'y'){
						system(command);
						return 0;
				}else{
						printf("Canceled by user, exiting.\n");
						return 0;
				}
		}else if(argc == 6 && strcmp(argv[1] , "2") == 0){
				strncpy(subvolume, argv[2], 127);
				strncpy(device, argv[4], 127);
				strncpy(directory, argv[5], 127);
				zstd = atoi(argv[3]);
				snprintf(command, 256, "sudo mount -o subvol=%s,noatime,compress=zstd:%d %s %s",subvolume,zstd,device,directory);
				printf("COMMAND: %s\n",command);
				printf("The above command will be executed, do you confirm? (y/n)\n");
				scanf("%c",&confirm);
				clearBuffer();
				if(confirm == 'y'){
						system(command);
						return 0;
				}else{
						printf("Canceled by user, exiting.\n");
						return 0;
				}
				return 0;
		}else{
				printf("Operation not supported! Exiting.");
				return 1;
		}
		return 0;
}

