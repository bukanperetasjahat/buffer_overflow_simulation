//coded by -> ig : @hackie.techie
#include <stdlib.h>
#include <stdio.h>

int check(){
	char password[10];
	printf("password address : %p\n", password);
	printf("enter password : ");
	fgets(password, 50, stdin);
	return 1;
}

void granted(){
	printf(\nACCESS GRANTED!!!);
}

void main(){
	if(check()) printf("\nNO ACCESS\n");
	else granted();
}
