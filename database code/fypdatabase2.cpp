#include "stdio.h"
#include "string.h"
#include "conio.h"
//#define PATH "E://FYPcode//users2.dat"

struct record
{
	//char first_name[15];
	//char last_name[20];
	//char email_id[30];
	//char national_id[10];
   int travelid;
	int balance;
	int pos;
}user,test;
void main(){
	FILE *people;
	people = fopen("E://FYPcode//users2.dat", "r+b");
   if(people==NULL){
      printf("Creating new file\n");
      people = fopen("E://FYPcode//users2.dat", "w+b");
   	}
	fseek(people, -1*sizeof(user), SEEK_END);
   fread(&user, sizeof(user), 1, people);
   int i=user.travelid, j=1, k;

   while(j){
   	//clrscr();
   	//i=0;
   	printf("\nPress 1 for making an account\nPress 2 for viewing an account\nPress 3 to recharge\nPress 4 to view total users\nPress 0 to exit\nYour Input is :");
   	scanf("%d",&j);
   	/*while(j!= 1){
      printf(" Invalid input\nPress 1 for making an account\n Press 2 for viewing an account\n Press 0 to recharge");
   	scanf("%d",&j);
   	}*/
		//FILE *people;
   	switch(j){
      case 1:
   		/*people = fopen(PATH, "r+b");
   		while(feof(people)==NULL){
   			fread(&test, sizeof(test), 1, people);
   			i++;
   			}*/
      	/*printf("Enter First Name: ");
			scanf("%s",&user.first_name);
      	printf("Enter Last Name: ");
			scanf("%s",&user.last_name);
      	printf("Enter Email ID: ");
   		scanf("%s",&user.email_id);
      	printf("Enter National ID: ");
			scanf("%s",&user.national_id);*/
      	user.travelid = ++i;
   		user.balance = 100;
   		user.pos = 0;
			fseek(people, 0, SEEK_END);
   		fwrite(&user, sizeof(user), 1, people);
   		//fclose(people);
      	printf("Congratulations your account is made and your travel id is %d\n",i);
      	//getch();
         break;

   	case 2:
      	//people = fopen(PATH, "rb");
   		printf("Enter travel id: ");
   		scanf("%d",&k);
         if(k<1||k>i){
         	printf("Invalid travel id\n");
            break;
            }
   		fseek(people, (k-1)*sizeof(user), SEEK_SET);
      	fread(&user, sizeof(user), 1, people);
      	/*printf("First Name: %s\nLast Name: %s\nEmail ID: %s\n National ID: %s\n ",&user.first_name,&user.last_name,&user.email_id,&user.national_id);*/
      	printf("Travel Id: %d\nBalance: %d\nPosition %d\n",user.travelid,user.balance,user.pos);
      	//fclose(people);
      	//getch();
         break;

   	case 3:
   		int payment;
   		//people = fopen(PATH, "r+b");
   		printf("Enter travel id: ");
   		scanf("%d",&k);
      	if(k<1||k>i){
         	printf("Invalid travel id\n");
            break;
            }
   		fseek(people, (k-1)*sizeof(user), SEEK_SET);
      	fread(&user, sizeof(user), 1, people);
      	printf("Enter Recharge Amount :");
      	scanf("%d",&payment);
      	user.balance += payment;
         fseek(people, (k-1)*sizeof(user), SEEK_SET);
         fwrite(&user, sizeof(user), 1, people);
         //fseek(people, (k-1)*sizeof(user), SEEK_SET);
      	//fread(&user, sizeof(user), 1, people);
         printf("Recharge Successful!!!\nNew account Info:\n");
      	/*printf("First Name: %s\nLast Name: %s\nEmail ID: %s\nNational ID: %s\n",&user.first_name,&user.last_name,&user.email_id,&user.national_id);*/
      	printf("Travel Id: %d\nBalance: %d\nPosition %d\n",user.travelid,user.balance,user.pos);
      	//fclose(people);
      	//getch();
         break;

      case 4:
      	printf("Total users: %d\n",i);
         break;

      default:
      	printf("Invalid input\n");
      }
   }
   fclose(people);
}
