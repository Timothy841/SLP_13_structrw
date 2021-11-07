#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

struct pop_entry{
	int year;
  int population;
  char boro[15];
};

void read_csv(){
	struct stat file;
	int rfile = open("nyc_pop.csv", O_RDONLY);
	if (errno){
		printf("Error: No file to read from. Create file with data.");
		return;
	}
	stat("nyc_pop.csv", &file);
	int wfile = open("pop.txt", O_WRONLY | O_TRUNC | O_CREAT, 0644);
	char size[file.st_size], line[100];
	char place[5][15] = {"Manhattan", "Brooklyn", "Queens", "Bronx", "Staten Island"};
	int y[6];
	struct pop_entry entry;
	for (int i = 0; i<100; i++){
		line[i] = 0;
	}
	for (int i = 0; i<6; i++){
		y[i] = 0;
	}
	read(rfile, size, sizeof(size));
	int nline = 0;
	nline = (int)(strchr(size, '\n') - size);
	strncpy(size, size+nline+1, strlen(size));
	while (strlen(size)){
		nline = (int)(strchr(size, '\n') - size);
		if (strchr(size, '\n') == 0){
			nline = strlen(size);
		}
		strncpy(line, size, nline);
		sscanf(line, "%d,%d,%d,%d,%d,%d", &y[5], &y[0], &y[1], &y[2], &y[3], &y[4]);
		for (int i = 0; i<5; i++){
			entry.year = y[5];
			entry.population = y[i];
			strcpy(entry.boro, place[i]);
			write(wfile, &entry, sizeof(struct pop_entry));
		}
		strncpy(size, size+nline+1, strlen(size));
	}
	close(rfile);
	close(wfile);
	printf("Wrote %d bytes to file\n", file.st_size);
}

void read_data(){
	struct stat file;
	int rfile = open("pop.txt", O_RDONLY);
	if (errno){
		printf("No file to read from. Use -read_csv first.\n");
		return;
	}
	stat("pop.txt", &file);
	int size = file.st_size/sizeof(struct pop_entry);
	struct pop_entry entries[size];
	for (int i = 0; i < size; i++){
		read(rfile, &entries[i], sizeof(struct pop_entry));
	}
	for (int i = 0; i < size; i++){
		printf("%d: year: %d borough: %s pop: %d\n", i, entries[i].year, entries[i].boro, entries[i].population);
	}
	close(rfile);
}

void add_data(){
	int ye = 0;
	int pop = 0;
	char y[15], p[15], b[15];
	for (int i = 0; i < 15; i++){
		y[i] = 0;
		p[i] = 0;
		b[i] = 0;
	}
	printf("Year?\n");
	read(STDIN_FILENO, &y, sizeof(y));
	sscanf(y, "%d", &ye);
	printf("Population?\n");
	read(STDIN_FILENO, &p, sizeof(p));
	sscanf(p, "%d\n", &pop);
	printf("Borough?\n");
	read(STDIN_FILENO, &b, sizeof(b));
	sscanf(b, "%s\n", &b);
	struct pop_entry entry;
	entry.year = ye;
	entry.population = pop;
	strcpy(entry.boro, b);
	int wfile = open("pop.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
	write(wfile, &entry, sizeof(entry));
	close(wfile);
	printf("Appended entry to file: year: %d borough: %s pop: %d\n", entry.year, entry.boro, entry.population);
}

void update_data(){
	struct stat file;
	int rfile = open("pop.txt", O_RDONLY);
	if (errno){
		printf("Error: No file to read from. Create file with data.");
		return;
	}
	stat("pop.txt", &file);
	printf("Which entry do you want to modify\n");
	int e = 0;
	char entry[5];
	for (int i = 0; i < 5; i++){
		entry[i] = 0;
	}
	read(STDIN_FILENO, &entry, sizeof(entry));
	sscanf(entry, "%d\n", &e);
	if (e>file.st_size/sizeof(struct pop_entry)){
		printf("There is no entry %d\n", e);
		return;
	}
	struct pop_entry entries[e+1];
	for (int i = 0; i <= e; i++){
		read(rfile, &entries[i], sizeof(struct pop_entry));
	}
	close(rfile);
	int wfile = open("pop.txt", O_WRONLY);
	int ye = 0;
	int pop = 0;
	char y[15], p[15], b[15];
	for (int i = 0; i < 15; i++){
		y[i] = 0;
		p[i] = 0;
		b[i] = 0;
	}
	printf("Year?\n");
	read(STDIN_FILENO, &y, sizeof(y));
	sscanf(y, "%d", &ye);
	printf("Population?\n");
	read(STDIN_FILENO, &p, sizeof(p));
	sscanf(p, "%d\n", &pop);
	printf("Borough?\n");
	read(STDIN_FILENO, &b, sizeof(b));
	sscanf(b, "%s\n", &b);
	entries[e].year = ye;
	entries[e].population = pop;
	strcpy(entries[e].boro, b);
	for (int i = 0; i <= e; i++){
		write(wfile, &entries[i], sizeof(struct pop_entry));
	}
	close(wfile);
	printf("Modified entry %d\n", e);
}

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
			read_csv();
			return 0;
		}
		else if (strcmp(argv[1], "-read_data") == 0){
			read_data();
			return 0;
		}
		else if (strcmp(argv[1], "-add_data") == 0){
			add_data();
			return 0;
		}
		else if (strcmp(argv[1], "-update_data") == 0){
			update_data();
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
			read_csv();
			return 0;
		}
		else if (strcmp(option, "-read_data") == 0){
			read_data();
			return 0;
		}
		else if (strcmp(option, "-add_data") == 0){
			add_data();
			return 0;
		}
		else if (strcmp(option, "-update_data") == 0){
			update_data();
			return 0;
		}
		else{
			printf("Options: -read_csv, -read_data, -add_data, -update_data\n");
			read(STDIN_FILENO, option, sizeof(option)-1);
			sscanf(option, "%s\n", option);
		}
	}
}
