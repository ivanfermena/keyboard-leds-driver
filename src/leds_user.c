#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void controlOption(int optionPanel, int fd);
void binaryCount(int fd);
void circular(int fd);
void specificOrder(int fd);


int main(int argc, char *argv[]){
	int optionMenu = -1;

	int fd = 0;
	/*if(argc<1) fd = open(argv[1], O_RDWR);
	else fd = open("dev/kb-leds", O_RDWR);*/

	if( (fd = open("/dev/kb-leds", O_RDWR, 0)) == -1){
		printf("open() failed with error [%s]\n", strerror(errno));
		return 1;	
	}
	
	do{
		printf("\nMenu:\n");	
		printf("0: Exit.\n");	
		printf("1: Lineal.\n");		
		printf("2: Circular.\n");
		printf("3: Propio orden.\n\n");

		printf("Ingrese la opcion que desee: ");
		scanf("%d", &optionMenu);

		controlOption(optionMenu, fd);
				
	}while(optionMenu != 0);

	close(fd);
	
	return 0;
}

void controlOption(int optionPanel, int fd){
	
	switch(optionPanel){
		case 1:{
			binaryCount(fd);
		}
			break;
		case 2:{
			circular(fd);
		}
			break;
		case 3:{
			specificOrder(fd);
		}
			break;
		default:{} break;

	}
}

void binaryCount(int fd){
	int maxCount = 8, wr = 0, i;
	char *buffLeds = 0;
	for(i = 0; i < maxCount; i++){
		switch(i){
			case 0: {buffLeds = "0";} break;
			case 1: {buffLeds = "1";} break;
			case 2: {buffLeds = "2";} break;
			case 3: {buffLeds = "3";} break;
			case 4: {buffLeds = "13";} break;
			case 5: {buffLeds = "12";} break;
			case 6: {buffLeds = "23";} break;
			case 7: {buffLeds = "123";} break;
			default:{} break;
		}
		wr = write(fd, buffLeds, strlen(buffLeds));
		if(wr < 0){ //Error
			printf("write() failed with error [%s]\n", strerror(errno));
			return;
		}
		// Dormimos un seg
		usleep(500000);
	}	
	

}

void circular(int fd){
	int maxCount = 0, wr = 0, i;
	char *buffLeds = 0;

	printf("Introduce el numero de ciclos: ");
	scanf("%d", &maxCount);
	
	// Multiplicamos por tres y asi se hacen los tres por el numero del usuario
	maxCount = maxCount * 3;
	
	for(i = 0; i < maxCount; i++){
		switch(i%3){
			case 0: {buffLeds = "1";} break;
			case 1: {buffLeds = "2";} break;
			case 2: {buffLeds = "3";} break;
			default: {} break;
		}
		printf("i= %d, buffLeds= %s", i, buffLeds);
		wr = write(fd, buffLeds, strlen(buffLeds));
		if(wr < 0){ //Error
			printf("write() failed with error [%s]\n", strerror(errno));
			return;
		}
		// Dormimos un seg
		usleep(500000);
	}
}

void specificOrder(int fd){
	char *buffLeds;
	int wr = 0;

	printf("Introduce los leds a encender (ejemplo: 010):");
	scanf("%c", buffLeds);

	printf("%d\n", strlen(buffLeds));

	while(strlen(buffLeds) < 3){
		printf("\nIntroduce los leds a encender (ejemplo: 010):");
		scanf("%c", buffLeds);
	}
	printf("-%s-\n", buffLeds);
	//wr = write(fd, buffLeds, strlen(buffLeds));
	//if(wr < 0){ //Error
	//	printf("write() failed with error [%s]\n", strerror(errno));
	//	return;
	//}
	// Dormimos un seg
	usleep(10000);
}

