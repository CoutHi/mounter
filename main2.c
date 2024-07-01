#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void clearBuffer() {
    char *buffer = NULL;
    size_t bufsize = 0;
    getline(&buffer, &bufsize, stdin); // Read input into dynamically allocated buffer
    free(buffer); // Free dynamically allocated memory
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Not enough arguments provided, use 'mounter help' for help.\n");
        return 1;
    } else if (argc == 2 && strcmp(argv[1], "help") == 0) {
        printf("\nIf you want to mount an exFat drive with permissions for your user, run the command: \n'mounter 1 [device] [directory]'");
        printf("\n\nIf you want to mount a btrfs drive with zstd compression, noatime and a subvolume, run the command: \n'mounter 2 [subvol] [zstd level] [device] [directory]'");
        printf("\n\nIf none of the options above suits you, this program won't have any advantages over the normal mount command.\n");
        printf("If you have a mount process in mind with a lot of arguments, feel free to contribute or hit me up.\n");
        return 0;
    }

    char *command = malloc(256 * sizeof(char));
    if (command == NULL) {
        perror("malloc");
        return 1;
    }
    char *device = NULL;
    char *directory = NULL;
    char *subvolume = NULL;
    int zstd = 0;
    char confirm;

    if (argc == 4 && strcmp(argv[1], "1") == 0) {
        device = strdup(argv[2]);
        directory = strdup(argv[3]);
        snprintf(command, 256, "sudo");
        char *args[] = {"sudo", "mount", "-o", "uid=your_uid,gid=your_gid", device, directory, NULL};
        printf("COMMAND: %s %s %s %s %s %s\n", args[0], args[1], args[2], args[3], args[4], args[5]);
        printf("The above command will be executed, do you confirm? (y/n)\n");
        scanf(" %c", &confirm);
        clearBuffer();
        if (confirm == 'y' || confirm == 'Y') {
            if (execve("/usr/bin/sudo", args, NULL) == -1) {
                perror("execve");
                free(command);
                return 1;
            }
        } else {
            printf("Canceled by user, exiting.\n");
            free(command);
            free(device);
            free(directory);
            return 0;
        }
    } else if (argc == 6 && strcmp(argv[1], "2") == 0) {
        subvolume = strdup(argv[2]);
        device = strdup(argv[4]);
        directory = strdup(argv[5]);
        zstd = (int)strtol(argv[3], NULL, 10);
        if (errno == ERANGE) {
            perror("strtol");
            free(command);
            return 1;
        }
        snprintf(command, 256, "sudo");
        char *args[] = {"sudo", "mount", "-o", "subvol=subvolume,noatime,compress=zstd:zstd_level", device, directory, NULL};
        printf("COMMAND: %s %s %s %s %s %s\n", args[0], args[1], args[2], args[3], args[4], args[5]);
        printf("The above command will be executed, do you confirm? (y/n)\n");
        scanf(" %c", &confirm);
        clearBuffer();
        if (confirm == 'y' || confirm == 'Y') {
            if (execve("/usr/bin/sudo", args, NULL) == -1) {
                perror("execve");
                free(command);
                return 1;
            }
        } else {
            printf("Canceled by user, exiting.\n");
            free(command);
            free(subvolume);
            free(device);
            free(directory);
            return 0;
        }
    } else {
        printf("Operation not supported! Exiting.\n");
        free(command);
        return 1;
    }

    free(subvolume);
    free(device);
    free(directory);
    free(command);
    return 0;
}
