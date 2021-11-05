#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]){
	char option[15];
	for (int i = 0; i<15; i++){
		option[i] = 0;
	}
	if (argc == 1){//there isn't a starting string
		printf("Options: -read_csv, -read_data, -add_data, -update_data\n");
		read(STDIN_FILENO, option, sizeof(option)-1);
		sscanf(option, "%s\n", option);
	}
	else if (argc > 1){//there is a starting string
		if (strcmp(argv[1], "-read_csv") == 0){
			printf("2\n");
			return 0;
		}
		else if (strcmp(argv[1], "-read_data") == 0){
			printf("3\n");
			return 0;
		}
		else if (strcmp(argv[1], "-add_data") == 0){
			printf("4\n");
			return 0;
		}
		else if (strcmp(argv[1], "-update_data") == 0){
			printf("5\n");
			return 0;
		}
		else{
			printf("Options: -read_csv, -read_data, -add_data, -update_data\n");
			read(STDIN_FILENO, option, sizeof(option)-1);
			sscanf(option, "%s\n", option);
		}
	}
	while(1){//there is an option
		if (strcmp(option, "-read_csv") == 0){
			printf("2\n");
			return 0;
		}
		else if (strcmp(option, "-read_data") == 0){
			printf("3\n");
			return 0;
		}
		else if (strcmp(option, "-add_data") == 0){
			printf("4\n");
			return 0;
		}
		else if (strcmp(option, "-update_data") == 0){
			printf("5\n");
			return 0;
		}
		else{
			printf("Options: -read_csv, -read_data, -add_data, -update_data\n");
			read(STDIN_FILENO, option, sizeof(option)-1);
			sscanf(option, "%s\n", option);
		}
	}
}
