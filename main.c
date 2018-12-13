#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movie.h"
#include "linkedList.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	FILE *fp; //FILE pointer for reading movie data 
	char name[200]; //movie name
	char country[10]; //movie country
	int runTime; //movie runtime
	float score; //movie score
	
	int exit_flag = 0; //flag variable for while loop
	int option; //user input option
	void *list, *mvInfo; //pointers for linked list and a specific structure instance for a movie data
	void *ndPtr; //void pointer for linked list node
	
	
	//1. reading the movie.dat-----------------------------
	//1.1 FILE open
	fp = fopen("movie.dat","r"); 
	
	//1.2 list generation (use function list_genList() )
	list = list_genList();
	
	//1.3 read each movie data from the file and add it to the linked list
	printf ("reading data files \n");
	while ( fscanf(fp,"%s %s %i %f",name,country,&runTime,&score) !=EOF) //while 문으로 data읽음  
	{	
		//generate a movie info instance(mvInfo) with function mv_genMvInfo()
		mvInfo = mv_genMvInfo(name,score,runTime,country);
		list_addTail(mvInfo, list);
	}
	printf("Read done! %i read",list_len(list)); // 읽기 완료  
	//1.4 FILE close 
	fclose(fp); 
	//2. program start
	while(exit_flag == 0)  
	{
	//2.1 print menu message and get input option
		printf("---------MENU--------\n");
		printf("1) print all the movies\n");
		printf("2) search for specific country movies\n");
		printf("3) search for specific runtime movies\n");
		printf("4) search for specific score movies\n");
		printf("5) exit\n");
		printf("---------MENU--------\n");
		printf("select an option :\n");
		
		scanf("%i",&option); // 선택된 option을  프로그램에 받음  
		
		switch(option) // switch문으로 옵션별로 실행  
		{
			case 1: //print all the movies
				printf("printing all the movies in the list.....\n\n\n");
				
				ndPtr = list;
				while (list_isEndNode(ndPtr)!=1)/* repeat until the ndPtr points to the end node */
				{
					//2.2 print a movie data : use functions of movie.c and linkedList.c
					ndPtr =list_getNextNd(ndPtr); //ndPtr = the next node of the ndPtr;
					mvInfo = list_getNdObj(ndPtr); //get object of ndPtr to mvInfo void pointer
					mv_print(mvInfo);//print the contents of the mvInfo
						printf("-----------\n");
													
				}
				
				break;
				
			case 2: 
					printf("print movies of specific country\n");//print movies of specific country
					scanf("%s",country);
				//2.3.1 get country name to search for
					ndPtr = list;
					int count =0;
					while (list_isEndNode(ndPtr)!=1)/* repeat until the ndPtr points to the end node */
				{
					//2.3.2 print a movie data : use functions of movie.c and linkedList.c
					ndPtr =list_getNextNd(ndPtr); //ndPtr = the next node of the ndPtr;
					mvInfo = list_getNdObj(ndPtr); //get object of ndPtr to mvInfo void pointer
					
					if(strcmp(country, mv_getCountry(mvInfo))==0 ) 	//if the input country matches to the country of the movie, 문자열 비교함수 사용  
					
					{
						mv_print(mvInfo); 	//then print the contents of the mvInfo
						printf("--------------------\n");
						count++ ; // 목록이 몇개인지 
					}

				
					
				}
					printf("\n"); 
					printf("\n");
					printf("totally %i moives are listed !!! \n", count);
					printf("\n");
					printf("\n");
				break;
				
			case 3:
				//2.4.1 get minimal runtime value to search for
				printf("lowest runtime : \n");
				scanf("%i",&runTime);
				ndPtr = list;
					while (list_isEndNode(ndPtr)!=1)/* repeat until the ndPtr points to the end node */
				{
					//2.4.2 print a movie data : use functions of movie.c and linkedList.c
					ndPtr =list_getNextNd(ndPtr); //ndPtr = the next node of the ndPtr;
					mvInfo = list_getNdObj(ndPtr); //get object of ndPtr to mvInfo void pointer
					//if the input runtime is lower than the runtime of the movie,
					if(runTime <= mv_getRunTime(mvInfo) )
					{	mv_print(mvInfo); 	//then print the contents of the mvInfo
						printf("--------------------\n");
						count++ ; // 목록이 몇개인지	
					}
				
				}
					printf("\n"); 
					printf("\n");
					printf("totally %i moives are listed !!! \n", count);
					printf("\n");
					printf("\n");	
		
				break;
				
			case 4:
				//2.5.1 get minimal score value to search for
					printf("print movies of score\n");//print movies of specific country
					scanf("%s",&score);
				ndPtr = list;
					while (list_isEndNode(ndPtr)!=1)/* repeat until the ndPtr points to the end node */
				{
					//2.5.2 print a movie data : use functions of movie.c and linkedList.c
					ndPtr =list_getNextNd(ndPtr); //ndPtr = the next node of the ndPtr;
					mvInfo = list_getNdObj(ndPtr); //get object of ndPtr to mvInfo void pointer
					
					if (score <=mv_getScore(mvInfo)) //if the input score is lower than the score of the movie,
					{	mv_print(mvInfo); 	//then print the contents of the mvInfo
						printf("--------------------\n");
						count++ ; // 목록이 몇개인지	
			
					}
			
				}
						printf("\n"); 
					printf("\n");
					printf("totally %i moives are listed !!! \n", count);
					printf("\n");
					printf("\n");
				break;
				
			case 5:
				printf("Bye!\n\n");
				exit_flag = 1;
				break;
				
			default:
				printf("wrong command! input again\n");
				break;
		}
	}
	
	return 0;
}
