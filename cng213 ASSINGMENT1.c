#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<ctype.h>

#define SIZE 50

//f b a//

struct Node//this is my node and its variables//
{
    int ID;
	char teamName[SIZE];
	char teamStatu;
	int matchPoint;
	int teamScore;
	int goalNumber;
	int teamDay;
	int teamMonth;
	int teamYear;
	int teamHour;
	int teamMinute;
    struct Node *next;
};

struct ListRecord//this is simply a listRecord structure, which contains head, tail and size of my list//
{
    struct Node *head;
    struct  Node *tail;
    int size;
    int IDsize;//Here, this IDsize will hold the next added team's ID
};

typedef struct ListRecord *List;

//Those are my function prototypes//
List InitializeTeams();
void addTeam(List);
int isEmpty(List);
void deleteTeam(List,int);
void printTeams(List);
void searchTeams(List);
void printffav(List);
List createFavouriteList(List,List);
void Overwrite(List);
void OverwriteFavourite(List);
void menu();


int main()
{

//I declared List myList and assign it to InitializeTeams to get my list//
List myList;
myList=InitializeTeams();
//myFavList will contain the favourite teams list//

List myFavList;

//Here, I am declaring memory for my favourite team list, and make it empty//
myFavList=(struct ListRecord*)malloc(sizeof(struct ListRecord));

if(myFavList==NULL)
{
    printf("Out of memory for myFavList!!\n");
    exit(1);
}
myFavList->head=(struct Node *) malloc(sizeof(struct Node));

if(myFavList->head==NULL)
{
    printf("Out of memory for myFavList->head!!\n");
    exit(2);
}
myFavList->head->next=NULL;
myFavList->tail=myFavList->head;
myFavList->size=0;

int op,deletedID;

do//this is my loop in the main, runs until the user enters 6, which is the exit condition//
{

menu();
scanf("%d",&op);

if(op==1)
{
    addTeam(myList);
}
else if(op==2)
{
    printf("\nEnter the ID of the team you want to delete:");
    scanf("%d",&deletedID);
    deleteTeam(myList,deletedID);
}
else if(op==3)
{
    printTeams(myList);
}
else if(op==4)
{
    searchTeams(myList);
}
else if(op==5)
{
    myFavList=createFavouriteList(myList,myFavList);

}
else if(op==6)
{
    Overwrite(myList);
    OverwriteFavourite(myFavList);
}
else
    printf("Please enter options between 1-6!!\n");


}while(op != 6);

printf("The favouriteTeams.txt file has been updated successfully!!\n");

    return 0;
}

                      //This function creates a list, which is empty at the beginning
List InitializeTeams()//Then function reads the data from my Teams.txt file with fscanf, then it assign these values to my variables//
{                     //After assigning, I populate my tmp node with these variables, then I fix the position of l->tail->next, l->tail and l->size//

    FILE *outFile; //I opened my file as read mode to get the data in it//
    outFile=fopen("Teams.txt","r");
    if(outFile==NULL)
        printf("File could not opened for read mode!!\n\n");
    else
        printf("The Teams.txt file has been loaded successfully\n\n");

    List l;// I create my list, and make it empty//

    l=(struct ListRecord*)malloc(sizeof(struct ListRecord));
    if(l==NULL)
    {
        printf("Out of memory for l!!\n");
        exit(3);
    }

    l->head=(struct Node*)malloc(sizeof(struct Node));
    if(l->head==NULL)
    {
        printf("Out of memory for l->head!!\n");
        exit(4);
    }
    l->head->next=NULL;
    l->tail=l->head;
    l->size=0;

    //this is my temporary node//
    struct Node *tmp;

    //these are my variables to populate the tmp node//
    int id,i;
	char name[50]; char statu;
	int point,score,goal;
	int day,month,year,hour,minute;


    for(i=0;((fscanf(outFile,"%d; %[^;]; %c; %d; %d; %d; %d/%d/%d %d:%d\n",&id,name,&statu,&point,&score,&goal,&day,&month,&year,&hour,&minute)!=EOF));i++)//this loop takes data until it reaches EOF//
	{
        tmp = (struct Node *) malloc(sizeof(struct Node));// this temporary node carries the information taken by Teams.txt file//
        if(tmp==NULL)
        {
            printf("Out of memory for tmp!!\n");
            exit(4);
        }
	  	tmp->ID=id;
	  	strcpy(tmp->teamName,name);
	  	tmp->teamStatu=statu;
	  	tmp->matchPoint=point;
	  	tmp->teamScore=score;
	  	tmp->goalNumber=goal;
	  	tmp->teamDay=day;
	  	tmp->teamMonth=month;
	  	tmp->teamYear=year;
	  	tmp->teamHour=hour;
	  	tmp->teamMinute=minute;

        tmp->next = NULL;

	  	l->tail->next=tmp;
        l->tail=tmp;
        l->size++;
    }

    l->IDsize=l->size;//I assigned l->IDsize to list size,If user adds a new team,it's ID is equal to one more of l->IDsize//

    fclose(outFile);
    return l;//after execution, I am returning my list l//

}

void addTeam(List l)//In the addTeam function, it takes the information from the user, and takes the date and time from localtime function//
{
     struct Node *compare;//this is my temporary pointer, I assigned it to next of my beginning of my list, which is l->head->next//
     compare=l->head->next;

     //these are my variables assigned by user.Then I populate my insertNode with these variables//
     int id,i,flag=1;
	 char name[50]; char statu;
	 int point,score,goal;
	 int day,month,year,hour,minute;
     char makeFirstUpperName[SIZE];//The purpose of this array is that it stores the entered name with some changes made below//

     time_t ti = time(NULL);//this function helps me to get the exact date and time//
     struct tm t = *localtime(&ti);

     struct Node *insertNode;//this is my temporary node//
     insertNode=(struct Node*)malloc(sizeof(struct Node));



     getchar();
     printf("\n\nEnter name of the Team:");//user enters the new team name
     gets(name);

     //here, I convert my new team name's first letter capital, and rest is lowercase//
     for(i=0;name[i]!='\0';i++)//this is because when user entered a  team, which is all capitals, all lowercase or first letter is upper and rest is lowercase, if that team exist,program should give error//
     {
        if(i==0)
            makeFirstUpperName[i]=toupper(name[i]);
        else
            makeFirstUpperName[i]=tolower(name[i]);
     }
     makeFirstUpperName[i]='\0';

     while(compare != NULL)//here I traverse my list, and compare with all the team names and my new entered team name//
     {
        int firstUpperCompare=strcmp(compare->teamName,makeFirstUpperName);

        if(firstUpperCompare == 0 )//if entered team is already exist, flag will be 0 and error message will be given//
        {
            printf("Team %s could not added!\n",name);
            printf("\nPlease enter a team which has a different name!\n\n");
            flag=0;


        }
        if(flag==0)//when flag is 0, this loop will not be executed anymore//
          break;

         compare=compare->next;
     }

    if(flag==1)//If the entered new team name does not exist in my list, as flag should not be changed, it will take other informations from user to add a new team//
    {
     l->IDsize++;//here, as l->IDsize=8 at the beginning, i will increase it here and equal it to my new team's ID
     insertNode->ID=l->IDsize;//In this way, even user deletes a team,my list size will change,but as my ID size don't change when I did not call this function,it will assign one more of a last team's ID//
     strcpy(insertNode->teamName,name);
     printf("Enter status of the Team:");
     scanf("%c",&insertNode->teamStatu);
     printf("Enter points of the Team:");
     scanf("%d",&insertNode->matchPoint);
     printf("Enter score of the Team:");
     scanf("%d",&insertNode->teamScore);
     printf("Enter number of Team goals:");
     scanf("%d",&insertNode->goalNumber);
     insertNode->teamDay=t.tm_mday;
     insertNode->teamMonth=t.tm_mon+1;
     insertNode->teamYear=t.tm_year+1900;
     insertNode->teamHour=t.tm_hour;
     insertNode->teamMinute=t.tm_min;
     insertNode->next=NULL;

     l->tail->next=insertNode;
     l->tail=insertNode;
     l->size++;
     printf("The team has been added!\n\n");
    }


}
void printTeams(List l)//this function simply traverses my linked list and prints the information//
{
    struct Node *p;//I defined *p, not printing the list with l, as I dont want to lose my data//
    p=l->head->next;

    while(p != NULL)
    {
        printf("ID: %d\nTeam Name: %s\nTeam Status: %c\nTeam Points: %d\nTeam Score: %d\nNumber of team goals: %d\nDate: %02d/%02d/%04d\nTime: %02d:%02d\n\n",p->ID,p->teamName,p->teamStatu,p->matchPoint,p->teamScore,p->goalNumber,p->teamDay,p->teamMonth,p->teamYear,p->teamHour,p->teamMinute);
        p=p->next;
    }
}
int isEmpty(List l)//this is a helper function, it  checks whether my list is empty or not//
{
    if(l->size==0)
        return 1;
    else
        return 0;
}
void deleteTeam(List l, int id)//this function deletes a team by its unique identification number//
{
    if(!isEmpty(l))//here, I execute the function if the list is not empty//
    {
        struct Node *tmp;//the purpose of tmp pointer is that it holds the address ,which is the previous of the node,which we want to delete//
        if(tmp==NULL)
        {
            printf("Out of memory for tmp!!\n");
            exit(5);
        }
        tmp=l->head;

        while(tmp->next != NULL && tmp->next->ID != id)//here, I set the tmp before the deleted node//
        {
            tmp=tmp->next;
        }
        if(tmp->next==NULL)//If we entered a not existed ID, program should give error//
            printf("element with  ID %d could not found!\n\n",id);
        else
        {
            struct Node *remove;//remove is pointing to deleted node,I made connections with tmp and remove->next//
            remove=tmp->next;
            tmp->next=tmp->next->next;
            free(remove);//after making connections, I free the memory of remove//
            printf("Team with ID %d has been deleted from your list!!!\n\n",id);

        }
    l->size--;//I decrement the size as I deleted a team//

    }
    else
    {
        printf("List is empty!");
    }
}
void searchTeams(List l)//this function search a team information with using team's name//
{
    char name[SIZE]; char makeFirstUpperName[SIZE];
    int i,flag=1;

    getchar();
    printf("Enter Team name:");
    gets(name);

    for(i=0;name[i]!='\0';i++)//this loop's function is  when user entered a  team, which is all capital, all lowercase or first letter is upper and rest is lowercase, if that team exist,program should give error//
     {
        if(i==0)
            makeFirstUpperName[i]=toupper(name[i]);
        else
            makeFirstUpperName[i]=tolower(name[i]);
     }
     makeFirstUpperName[i]='\0';


    struct Node *p;
    p=l->head->next;

    while(p != NULL)
    {
        int compare=strcmp(p->teamName,makeFirstUpperName);//here, If the compare result is 0, the searched team name exist in my list, so I print the team information and break the loop//
        if(compare==0)
        {
            printf("Results:\n");
            printf("---------------------\n\n");
            printf("ID: %d\nTeam Name: %s\nTeam Status: %c\nTeam Points: %d\nTeam Score: %d\nNumber of team goals: %d\nDate: %02d/%02d/%04d\nTime: %02d:%02d\n\n",p->ID,p->teamName,p->teamStatu,p->matchPoint,p->teamScore,p->goalNumber,p->teamDay,p->teamMonth,p->teamYear,p->teamHour,p->teamMinute);
            flag=0;
        }
        if(flag==0)
            break;

        p=p->next;
    }
    if(flag==1)//As I assigned flag=1 at the beginning, if the searched team does not exist, flag will be remains 1, and error message will be given//
        printf("\nTeam with the name %s does not exist in team list!!!!\n\n",name);


}
List createFavouriteList(List l,List lFav)//as I can call this function until the user types exit, I declared my favourite list int the main and make it empty//
{                                         //When I declared my fav list in this function,as I called it many times, I could not manage to store the data//

    int favID,flag=1;

    printf("Enter team ID you want to add to your favorite list:");
    scanf("%d",&favID);

    struct Node *p;
    p=l->head->next;

    struct Node *tmp;

    while(p != NULL)
    {
        if(favID==p->ID)//Here I check whether entered ID is equal to any of my favourite team ID or not. If not, the error will be given//
        {

            tmp=(struct Node*)malloc(sizeof(struct Node));
            tmp->ID=p->ID;
            strcpy(tmp->teamName,p->teamName);
            tmp->teamStatu=p->teamStatu;
            tmp->matchPoint=p->matchPoint;
            tmp->teamScore=p->teamScore;
            tmp->goalNumber=p->goalNumber;
            tmp->teamDay=p->teamDay;
            tmp->teamMonth=p->teamMonth;
            tmp->teamYear=p->teamYear;
            tmp->teamHour=p->teamHour;
            tmp->teamMinute=p->teamMinute;

            tmp->next = NULL;

            lFav->tail->next=tmp;

            lFav->tail=tmp;
            lFav->size++;

            flag=0;//I assigned flag to 0, if entered ID is equal to  ID of any team//

        }

        p=p->next;
    }

if(flag==0)
{
    printf("%d has been added to your list!!\n\n",favID);

}
else
    printf("Team with ID %d does not exist in team list!!\n\n",favID);

return lFav;



}
void Overwrite(List l)//this function  overwrites the latest version of the list to Teams.txt file//
{
    FILE *inFile;//Here, I declared inFile and open it with writing mode//
    inFile=fopen("Teams.txt","w");//as I want to overwrite the latest version of my list, opening the file with "w" mode will be enough//
    if(inFile==NULL)
        printf("File could not be opened for write mode!!\n\n");
    else
    {
        printf("\nThe Teams.txt file has been updated successfully!!\n");

    }

struct Node *p;
p=l->head->next;


while(p != NULL)//In this loop, I write my list content to my Teams.txt file by using fprintf //
{
    fprintf(inFile,"%d;%s;%c;%d;%d;%d;%02d/%02d/%04d %02d:%02d\n",p->ID,p->teamName,p->teamStatu,p->matchPoint,p->teamScore,p->goalNumber,p->teamDay,p->teamMonth,p->teamYear,p->teamHour,p->teamMinute);
    p=p->next;
}

fclose(inFile);

}
void OverwriteFavourite(List lFav)//this function writes the data of the favourite teams to favouriteTeams.txt file//
{
    FILE *favFile;//Here, I declared favFile and open it with writing mode//
    favFile=fopen("favouriteTeams.txt","w");
    if(favFile==NULL)
        printf("File could not be opened for write mode!!\n\n");


struct Node *p;
p=lFav->head->next;



while(p != NULL)//In this loop, I write my list content to my favouriteTeams.txt file by using fprintf //
{
    fprintf(favFile,"%d;%s;%c;%d;%d;%d;%02d/%02d/%04d %02d:%02d\n",p->ID,p->teamName,p->teamStatu,p->matchPoint,p->teamScore,p->goalNumber,p->teamDay,p->teamMonth,p->teamYear,p->teamHour,p->teamMinute);
    p=p->next;
}

fclose(favFile);
}
void menu()//this is my menu function//
{

    printf("-------MENU-------\n\n");
    printf("1.Add Team\n");
    printf("2.Delete Team\n");
    printf("3.Print Teams\n");
    printf("4.Search Teams\n");
    printf("5.Create Favourite Team List\n");
    printf("6.Exit\n\n");
    printf("Enter your option:");

}














