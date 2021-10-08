/*
 * Avishka Abeywickrama
 * E/18/010
 * Project2
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 100

//crate a node to store name and  participants or duration or meetings in the .csv files
typedef struct node{
	char name[80];
	long long int parameter;
     	struct node *next;
}node_t;

//create a struct to add details according to given flags
typedef struct _{
	char name[80];
	long long int details;
}data_t;

void read_files(char **); //to read .csv files
void sort_array(data_t []); //sort array max to min
void print_chart(data_t []); //printing chart
int max_len(data_t []); //to find max name length in the chart 
int no_digits(long long int); //to find number of digits in the printing value
long long int divider(data_t []); //find the sum and max of the printing values

int file_pos[10]; //store the .csv file positions in the arguments
int pos = 0; 

//flag variables
int flag_l = 0;
int flag_m = 0;
int flag_t = 0;
int flag_p = 0;
int flag_s = 0;
long long int rows = 10; //rows in the bar chart
long long int count = 0; //number of elements in the strcut array
int no_files = 0; //store number of csv files that has given as inputs
long long int total = 0;

int main(int argc, char ** argv){

	int len = 0; 
	int x = 1;
	int invalid_arg = 0;
	int num_len; //variable to get the length of rows argument

	//when no other arguments	
	if(argc == 1){

		printf("No input files were given\n");
		printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n", argv[0]);	
		return 0;

	}

	//go through the arguments
	while(x < argc){

		len = strlen(argv[x]); //take the length of each argument
		char ext[4]; 

		for(int y = 0; y < 4; y++){

                        ext[y] = argv[x][len - 4 + y]; //store last 4 characters of each argument

                }

                //checking for .csv files
                if(strcmp(ext, ".csv") == 0){

                        no_files ++;
			file_pos[pos] = x; //store the file's position
			pos ++;
			
			//if the last argument then break the loop
			if(x == argc - 1){
			
				break;

			}
		
			x ++; //go to next argument

                }
			
		//checking for flags
		else if(argv[x][0] == '-'){
                           
			//invalid argumets
			if((len != 2 && strcmp(argv[x], "--scaled") != 0) || (len == 2 && argv[x][1] != 'l' && argv[x][1] != 'm' && argv[x][1] != 'p' && argv[x][1] != 't')){

				printf("Invalid option [%s]\n", argv[x]);
				printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n", argv[0]);
				return 0;

			}

			//flag -l
			else if(argv[x][1] == 'l'){
		
				num_len = 0; //assign number lenth to zero

				//if it's the last argument
				if(x == argc - 1){

					printf("Not enough options for [-l]\n");
					printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n", argv[0]);				
					return 0;

				}

				else{
					//check length is 0
					if(strcmp(argv[x+1], "0") == 0 || strcmp(argv[x+1], "+0") == 0 || strcmp(argv[x+1], "-0") == 0){
					
						return 0;

					}
					
					len = strlen(argv[x+1]); //get the length of the argument after -l

					//check if it has a sign
					if(argv[x+1][0] == '-' || argv[x+1][0] == '+'){
					
						num_len ++; //increse the length

					}

					//check for decimal values	
					for(int y = 0; y < strlen(argv[x+1]); y++){						
						if(argv[x+1][y] == '.'){
							
							rows = 0;
							break;
														
						}
						
						else{
							
							rows = atoll(argv[x+1]); //get the length in long long int
				
						}
					
					}
					
					num_len += no_digits(rows); //number of digits in the rows

					//length is a negitive number
					if(rows < 0 && len == num_len){

              					printf("Invalid option(negative) for [-l]\n");
              					printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n", argv[0]);
               					return 0;
                       
					}

					//length is positive
					else if(rows > 0 && len == num_len){
				
						//length is the last argument, no files, no two more flags	
						if(x + 1 == argc - 1 && invalid_arg != 1 && no_files == 0 && ((flag_m == 0 && flag_p == 0) ||(flag_p == 0 && flag_t == 0) || (flag_m == 0 && flag_t == 0))){
							
							printf("No input files were given\n");
							printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n", argv[0]);        
							return 0;

                                                }

					}

					//lenth argument is not a number
					else{
						printf("Invalid options for [-l]\n");
						printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n", argv[0]);
						return 0;

					}

				}

				x ++; //going to next argument
			}

			//check other flags
			else if(argv[x][1] == 'm' || argv[x][1] == 'p' || argv[x][1] == 't' || strcmp(argv[x], "--scaled") == 0){			 
				
				//assign values to flags
				if(argv[x][1] == 'm'){
                                              
					flag_m = 1; 
					
				}

				else if(argv[x][1] == 'p'){
                        
					flag_p = 1;
                			
				}
        
				else if(argv[x][1] == 't'){

					flag_t = 1;
					
				}

				else if(strcmp(argv[x], "--scaled") == 0){

					flag_s = 1;
                                       
			       	}
			
				//flag is the last argument
				if(x == argc - 1){
							
					//no files and no teo or more flags		
					if(no_files == 0 && ((flag_m == 0 && flag_p == 0) ||(flag_p == 0 && flag_t == 0) || (flag_m == 0 && flag_t == 0))){

                                                printf("No input files were given\n");
                                                printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n", argv[0]);
                                                return 0;
                                        }

			
				}


			}

			x ++; //going to next argument		
		}

		//argument is not a file and not a flag
		else{
		
			invalid_arg = 1;
			x ++;	
		}

	}

	//when two or more flags are given
	if((flag_m == 1 && flag_p == 1 && flag_t == 1) || (flag_m == 1 && flag_p == 1) || (flag_p == 1 && flag_t == 1) || (flag_m == 1 && flag_t == 1)){
	
		printf("Cannot plot multiple parameters in same graph.\n");
		printf("usage: %s [-l length] [-m | -t | -p] [--scaled] filename1 filename2 ..\n", argv[0]);
		return 0;	
	}
	
	if(invalid_arg == 1){
		
		printf("Only .csv files should be given as inputs.\n");
		return 0;
	
	}

	//check whether all given files are existing
	for(int x = 0; x < pos; x++){
              
                char *file = argv[file_pos[x]];
                FILE * pFile = fopen(file, "r"); //open the file

                if(pFile == NULL){

                        printf("Cannot open one or more given files\n"); //not an existing file
                        return 0;

                }

		fclose(pFile); //close the file

        }

	if(no_files > 0){

		read_files(argv); //read files and put data into a linked list

	}

	return 0;
	
}

//read given files
void read_files(char **argv){
	
	char line[SIZE];
	node_t *head = NULL; //create head node
	long long int hours, min;
        long long int temp_participants, temp_duration, temp_meetings;
	char temp_name[80];
	int duplicate;

	//add name, participants and duration to temperoroy variables according to given flags
	//read all given files 
	for(int x = 0; x < pos; x++){
				
		char *file = argv[file_pos[x]];
		FILE * pFile = fopen(file, "r"); //open the file
		
		while(fgets(line, SIZE, pFile) != NULL){

			duplicate = 0;
			strcpy(temp_name, strtok(line, ",")); //copy name
                       	
                        if(flag_p == 1){

				temp_participants = atoll(strtok(NULL, ",")); //get participants
				
                        }

                        else if(flag_t == 1){

				temp_participants = atoll(strtok(NULL, ","));
                                hours = atoll(strtok(NULL, ":")); //get hours
                                min = atoll(strtok(NULL, ":")); //get minutes
				temp_duration = hours * 60 + min; //calculate duration in minutes		

                        }

			else if(no_files != 0 || flag_m == 1){
			
				temp_meetings = 1; //number of meetings

			}

			//find if there is a node with same name
			node_t *temp = head;

			while(temp != NULL){
			
				if(temp -> name[0] == temp_name[0]){
					
					if(strcmp(temp -> name, temp_name) == 0){
					
						duplicate = 1;		
	
						if(flag_p == 1){
						
							temp -> parameter += temp_participants; //add participants to the node with same name
						}	

						else if(flag_t == 1){
			
							temp -> parameter += temp_duration; //add duration to the node with same name
						}

						else if(no_files != 0 || flag_m == 1){
				
							temp -> parameter += temp_meetings; //add meetings to the node with same name	
						}

						break;

					}

			
				}
				
				
				temp = temp -> next; //go to next node
	
			}
			
			//does not have a node with same name
			if(duplicate == 0){
				
				//craete a node
				node_t *node = (node_t *)malloc(sizeof(node_t));
				
				//add data to it
				strcpy(node -> name, temp_name);

				if(flag_p == 1){
				
					node -> parameter = temp_participants;
				}

				else if(flag_t == 1){
				
					node -> parameter = temp_duration;

				}
				
				else if(no_files != 0 || flag_m == 1){
			
					node -> parameter = temp_meetings;	
				
				}
			
                       		node -> next  = head; //reference to the current head
                       		head = node; //make the new node head of the linked list
				count ++; //nodes count				
			
			}
			
		}
	
		fclose(pFile);	//close file
	}

	node_t *temp1, *temp2;
	temp1 = head;
	temp2 = head;
	data_t data[count]; //craete struct array
	long long int index = count - 1;

	//add data to struct array	
	while(temp1 != NULL && index >= 0){
			
		strcpy(data[index].name, temp1 -> name);

		//according to given flag add data to struct array
		
		data[index].details = temp1 -> parameter;

		total +=  data[index].details; //calculate total
		index --;
		temp2 = temp1;
		temp1 = temp1 -> next;
		free(temp2); //free the node
		
	}
	
	//if there is no data in the file
	if(total == 0){
	
		printf("No data to process\n");
		return;
	}
	
	sort_array(data); //call the function to sort the struct array (max to min)	
}

//sort relevant details (max to min)
void sort_array(data_t data[count]){

        long long int temp_details;
	char temp_name[80];

	//going through each element
	for(int x = 0; x < count - 1; x++){
       
	       	for(int y = 0; y < count - 1 - x; y++){

       			temp_details = data[y].details;       
			strcpy(temp_name, data[y].name);

			//compare adjecent elements
			if(data[y].details < data[y+1].details){

				//swap elements
				data[y].details = data[y+1].details;    
				strcpy(data[y].name, data[y+1].name);
				data[y+1].details = temp_details;
				strcpy(data[y+1].name, temp_name);
			}

		}

	}	

	print_chart(data); //call the function to print chart	
}

//printing the chart
void print_chart(data_t data[count]){

	float len;
	int bar_len, max_namelen, l;

	//when rows are larger than the meetings
	if(rows > count){
	
		rows = count;
	}	
		
	max_namelen = max_len(data);

	printf("\n");
	
	for(int i  = 0; i < rows; i++){

		//calculate the length of a bar
                len = ((80 - max_namelen - 3 - no_digits(data[i].details)) * data[i].details) / divider(data);
		
		bar_len = (int)len; //cast the length to int
		l = max_namelen + 1 - strlen(data[i].name); //number of coloumn cursor want to move after printing the name

		printf("%*s", max_namelen + 2, "");
		printf("\u2502"); 

		//first row of the bar
		for(int m = 0; m < bar_len; m++){

			printf("\u2591");

		}

		printf("\n %s", data[i].name); //print the name
		printf("%*s", l, "");
                printf("\u2502");
		//second row of the bar
		for(int m = 0; m < bar_len; m++){

			printf("\u2591");

		}

		printf("%lli\n", data[i].details); //print the number
		printf("%*s", max_namelen + 2, "");
                printf("\u2502");
		//third row of the bar
		for(int m = 0; m < bar_len; m++){
                        
			printf("\u2591");
                
		}
	
		printf("\n%*s", max_namelen + 2, "");
                printf("\u2502\n");

	}

	printf("%*s", max_namelen + 2, "");
	printf("\u2514");

	//print x axis
	for(int k = 0; k < (80 - max_namelen - 3); k++){
		printf("\u2500");

	}

	printf("\n");

}

//find the maximum name length
int max_len(data_t data[count]){

	int name_len, max_namelen;
	max_namelen = strlen(data[0].name);

	for(int i  = 0; i < rows; i++){
         
		name_len = strlen(data[i].name); //find the legth of each name

 		if(name_len > max_namelen){

			max_namelen = name_len;

		}

	}

	return max_namelen;
}

//find the numebr of digits of the printing number in the chart
int no_digits(long long int val){

	int digits = 0; 
	while(val != 0){

		val = val/10;
		digits++;

	}

	return digits;

}

//find max and sum
long long int divider(data_t data[count]){

	long long int sum = 0;
	long long int max;

	//if scaled flag is given then return the max value among the printing details
	if(flag_s == 1){
                        
		max = data[0].details;
                
		for(int i = 1; i < rows; i++){
        
			if(data[i].details > max){
                                        
				max = data[i].details;
                                
			}
                        
		}

		return max;        
	}
        
	//when scaled flag is not given then return the sum of the printing details
	else{

		sum = total;
		return sum;

	}

}


