#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define NAMELEN 10                     // Students'names are no longer than 10 chars.
#define COURSES 4                      // There are four courses in the system.

typedef struct stu_info
{   int id;
	char chStuName[NAMELEN];
    int iScore[COURSES];
	float fAvgScore;
	struct stu_info *pNext;
} STU_INFO;

void ShowMenu();

void ShowList(STU_INFO * pHead);

void Insert(STU_INFO * pHead);

void Search(STU_INFO * pHead);

void Analyze(STU_INFO * pHead);

STU_INFO *Delete(STU_INFO * pHead,STU_INFO * pEnd,STU_INFO * pNode);

void FreeLinkData(STU_INFO * pHead);

STU_INFO *FindStuByNum(STU_INFO * pHead,int id);

int main()
{
    int i,j,k;
    int iMode;
    //initialization
    int id = -1;
	char chStuName[NAMELEN] = {'\0'};
	int iScore[COURSES] = {'\0'};
	float fAvgScore = -1;
    int iFlage = 1;
    STU_INFO *pHead = NULL;
    STU_INFO *pEnd = NULL;

    printf("**********************   Welcome to Student management system   **********************\n\n") ;
	printf("Now  you can type in students' information \n") ;
    printf("if you want to use the current list , please press 1\n");
    printf("if you want to type the information by yourself , please press 2\n");
    scanf("%d",&iMode);
    if(iMode == 1)
    {
        STU_INFO default_info[5] =
        {
            {1,"Alice",{90,80,88,70},82.0,&default_info[1]},
            {2,"Bob",{88,30,78,77},68.3,&default_info[2]},
            {3,"Carol",{90,95,90,100},93.8,&default_info[3]},
            {4,"Geek",{100,98,100,100},99.5,&default_info[4]},
            {5,"Dave",{59,59,59,59},59.0,NULL}
        } ;//Chain on linked list
            pHead = &default_info[0] ;
    }

    if(iMode == 2)
    {
        printf("Please input the Id\n") ;
		scanf("%d", &id);
		printf("Please input the name\n") ;
		scanf("%s", chStuName) ;
        int sum = 0 ;
		//Input information
		for (j = 0; j < COURSES; j++)
		{
		    printf("Please input the iScore of C0%d\n",j+1);
			scanf("%d", &iScore[j]) ;
			sum += iScore[j] ;
		}
		fAvgScore = sum / COURSES ;
        STU_INFO * operation = malloc(sizeof(STU_INFO));
        //Determine whether information is legitimate
		if(id > 0 && iScore[0] > 0 && iScore[1] > 0 && iScore[2] > 0 && iScore[3] > 0 )
        {
            //The node member assigns the initial value
            operation->id = id ;
            strcpy(operation->chStuName,chStuName) ;
            for(i = 0;i < COURSES;i++)
            {
                operation->iScore[i] = iScore[i] ;
            }
            operation->fAvgScore = fAvgScore ;
            operation->pNext = NULL;
        //Put it on the linked list
		if (pHead == NULL)
			{
			    pHead = operation;
			}
		else
           {
                pEnd->pNext = operation;                   //Chain on linked list
           }
		//   Back ward
        pEnd = operation ;
        }
        //Prompts the user to re-enter
        else
        {
            printf("Sorry!you enter the wrong information.Please choose and enter again \n\n\n");
        }
    }
    ShowMenu();
	int choice;

	while (iFlage)
	{

	    printf("\nPlease enter your choice!\n");
        scanf("%d", &choice);
		//Provide users with different options
        switch (choice)
        {
            case 1:
                ShowList(pHead);
                break;
            case 2:
                Insert(pHead);
                break;
            case 3:
                printf("Please enter the id of student you want to delete\n");
                scanf("%d", &id);
                if(NULL != FindStuByNum(pHead,id))
                {
                    pHead = Delete(pHead,pEnd,FindStuByNum(pHead,id));
                }
                break;
            case 4:
                Search(pHead);
                break;
            case 5:
                Analyze(pHead);
                break;
            case 6:
                iFlage = 0;
                break;
            default:
                printf("The command doesn't exit\n");
		}
		if(iFlage)
        {
           ShowMenu();
        }
		//The menu is no longer displayed after exiting
        else
        {
            printf("*********************************************************************************\n") ;
            printf("*********************                Good Bye                 *******************\n") ;
            printf("*********************************************************************************\n") ;
        }
    }
    FreeLinkData(pHead);
	return 0 ;
}
//Print the form of the data
void ShowList(STU_INFO * pHead)
{
	//Create a node
    STU_INFO * ptr = pHead;
	printf("**********************List Into********************\n");
	printf("ID\t  Name\tCO1\tCO2\tCO3\tCO4\tAvg \n");
	//Traverse the list
	while(ptr != NULL)
	{
	    printf("%1d%13s%5d%8d%8d%8d%8.1f\n",ptr->id,ptr->chStuName, ptr->iScore[0], ptr->iScore[1], ptr->iScore[2], ptr->iScore[3], ptr->fAvgScore);
		ptr = ptr->pNext;
	}
	printf("***************************************************\n\n\n");
}

void Insert(STU_INFO * pHead)
{
	//Create a node
	STU_INFO * pEnd,*pTemp;
	int sum = 0;
	int i;
	pEnd = pHead;
	pTemp = (STU_INFO *)malloc(sizeof(STU_INFO));
	//point to the last node
	while (pEnd->pNext!=NULL)
	{
		pEnd = pEnd->pNext;
	}
	printf("ID of the new student:\n");
	scanf("%d", &pTemp->id);
	printf("Name of the new student:\n");
	scanf("%s", pTemp->chStuName);
	for (i = 0; i < COURSES ; i++)
	{
		printf("Please inpt the iScore of CO%d\n",i+1);
		scanf("%d", &pTemp->iScore[i]);
		sum += pTemp->iScore[i];
	}
	pTemp->fAvgScore = sum / COURSES;
	//The final node points to the null
	pTemp->pNext = NULL;
	pEnd->pNext = pTemp;
}

void Search(STU_INFO * pHead)
{
    int k;
	char name[NAMELEN];
	printf("Please enter the name of the student to search!\nName = ");
	scanf("%s", name);
	//Create a node
	STU_INFO *pSearch = pHead;
	while (pSearch->pNext != NULL)
	{
		k = 1;
		//determin if the student name = the student in the pSearch
		int i=0;
		//Traverse the name array
		while (name[i] != '\0')
		{
			if (name[i] != pSearch->chStuName[i])
				k = 0;
			else;
			i++;
		}
		if (k)
		{
            printf("Found the Student !\n");
			printf("Student Indo:\n");
			printf("ID\tName\tCO1\tCO2\tCO3\tCO4\tAvg\n");
			printf("%d\t%s\t%d\t%d\t%d\t%d\t%.1f\n",pSearch->id, pSearch->chStuName, pSearch->iScore[0], pSearch->iScore[1], pSearch->iScore[2], pSearch->iScore[3], pSearch->fAvgScore);
		}
		//Traverse the list
        pSearch = pSearch->pNext;

	}	//Determine the validity of the input
		if(k == 0)
        {
            printf("Sorry ,There is no person you want to search!\n");
		}

}

void Analyze(STU_INFO * pHead)
{
	int id ;
	int Max=0, Min=400, Sum=0;
	float Avg;
	//Create a node
	STU_INFO *pAnalyze = pHead;
	printf("Please input the course id you want to analyze\n");
	scanf("%d", &id);
    if(id < 0)
    {
        printf("Sorry, you enter a wrong number\n");
        return ;
    }
	while (pAnalyze->pNext != NULL)
	{
		Max = (Max > pAnalyze->iScore[id - 1]) ? Max : pAnalyze->iScore[id - 1];
		Min = (Min < pAnalyze->iScore[id - 1]) ? Min : pAnalyze->iScore[id - 1];
		Sum += pAnalyze->iScore[id - 1];
		pAnalyze = pAnalyze->pNext;

	}
	Avg = Sum / COURSES;
	printf("Course Info of CO%d :\n",id);
	printf("Max = %d.0\n", Max);
	printf("Min = %d.0\n", Min);
	printf("Avg = %.1f\n", Avg);
}

void ShowMenu()
{

	printf("**************************Main Menu**************************\n");
	printf("**********             1. Show Current List        **********\n");
    printf("**********             2. Insert Student           **********\n");
	printf("**********             3. Delete Student           **********\n");
	printf("**********             4. Search Student           **********\n");
	printf("**********             5. Analyze Course           **********\n");
	printf("**********             6. Exit the program         **********\n");
	printf("*************************************************************\n");

}

STU_INFO *Delete(STU_INFO * pHead,STU_INFO * pEnd,STU_INFO * pNode)
{
        //Only one node
        if(pHead == pEnd)
        {
            free(pHead);
            pHead = NULL;
            pEnd = NULL;
            printf("Delete successfully ! try to display the new system !\n");
        }
        //Only two nodes
        else if(pHead->pNext == pEnd)
        {
            if(pHead == pNode)
            {
                free(pHead);
                pHead = NULL;
                pHead = pEnd ;
            }
            else
            {
                free(pEnd);
                pEnd = NULL;
                pEnd = pHead ;
                pHead->pNext = NULL;
            }
            printf("Delete successfully ! try to display the new system !\n");
        }
        //Three nodes or more
        else
        {
        STU_INFO *pTemp = pHead ;
        //Determine head
        if(pHead == pNode)
        {
            pTemp = pHead;
            //Remember head
            pHead = pHead->pNext;
            free(pTemp);
            pTemp = NULL;
            printf("Delete successfully ! try to display the new system !\n");
            return pHead;
        }
        while (pTemp != NULL)
        {
        if(pTemp->pNext == pNode)
        {
            if(pNode == pEnd)
            {
                free(pNode);
                pNode = NULL;
                pEnd = pTemp;
                printf("Delete successfully ! try to display the new system !\n");
                return ;
            }
            //Intermediate nodes
            else
            {
                //Remember the node
                STU_INFO *p = pTemp->pNext;
                //connect
                pTemp->pNext = pTemp->pNext->pNext;
                free(p);
                p = NULL;
                printf("Delete successfully ! try to display the new system !\n");
                return ;
            }
        }
        pTemp = pTemp->pNext;
    }
    }

}

void FreeLinkData(STU_INFO * pHead)
{
    STU_INFO * pTemp = pHead ;
	//release completely or not
	while (pHead != NULL)
	{
		//Record the node
		pTemp = pHead ;
		//move backward
		pHead = pHead->pNext ;
		//Remove nodes
		free(pTemp);

 	}
}

STU_INFO *FindStuByNum(STU_INFO * pHead,int id)
{
    STU_INFO * pTemp = pHead ;
    //Verify the validity of the parameters
    if(id < 0)
    {
        printf("Sorry, you enter a wrong number\n\n\n");
        return NULL;
    }
    //Determine if the list is empty
    if(NULL == pHead)
    {
        printf("The list is empty\n\n\n");
        return NULL;
    }
    while (pTemp != NULL)
    {
        if(pTemp->id == id)
        {
            return pTemp ;
        }
        pTemp = pTemp->pNext;

    }
    printf("There is no id you entered \n\n\n");
    return NULL;
}
