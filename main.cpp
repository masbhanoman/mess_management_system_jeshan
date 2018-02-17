#include<iostream>
#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include <stdlib.h>
#include<string.h>                  //contains strcmp(),strcpy(),strlen(),etc
#include<ctype.h>                   //contains toupper(), tolower(),etc
#include<dos.h>                     //contains _dos_getdate
#include<time.h>

using namespace std;

// Files pointers

FILE *fp,*ft;

COORD coord = {0, 0};

void gotoxy (int x, int y) {
    coord.X = x; coord.Y = y; // X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int s;
char fmember;
char password[15] = {"tanjim"};

struct CreatedAt{
    char dte[50];
};

struct Meals{
    int meal;
};

struct Costs{
    int pCost;
    int tCosts;
};

struct Members{
    int id;
    char name[30];
    float blnc;
    struct Meals m;
    struct CreatedAt cdt;
    struct Costs c;
    float perMealCost;
};
struct Members mmbr;

//Login function
void login(); //If return 1/true then get access

void showMeals(); // Display all meals
void showMembers(); //Display all members with basic information
void showCosts(); //Display all cost yet
void showMealRate();//Display meal rate yet

//Main menu
void add();
void view();
void edit();
void dlt();

void addMeal();
void addMember();
void addCost();

void updateMeal();
void updateMember();
void updateCost();

void membersView();

void removeMeal();
void removeMember();
void removeCost();

void mainmenu();

//Helper functions
int checked(int); // check member exist or not
int getdata(); // Get or set data

int t(void);

void delay(unsigned int mseconds) { //Ref:: stockoverfollow.com
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void returnfunc();

void userview(int);
void userlogin();

/*===================================================================
|      -----------------
|      | Main function |
|      -----------------
|====================================================================
*/
int main() {
    login();
    return 0;
}

/*===================================================================
|       Login function
|====================================================================
*/

void login() {
    system("cls");
    char d[25]=" Password Protected";
    char ch,pass[10];
    int i=0,j;
    gotoxy(10,4);
    for(j=0;j<20;j++) {
        delay(15);
        printf("\xDB");
    }
    for(j=0;j<20;j++)  {
        delay(50);
        printf("%c",d[j]);
    }

    for(j=0;j<20;j++) {
       delay(15);
       printf("\xDB");
    }

    gotoxy(10,2);
    printf("1. Admin \t2. Member");
    gotoxy(10,7);
    int x;

    printf("Enter your choice: ");
    scanf("%d", &x);
    if(x==1) {
        gotoxy(10,8);
        printf("Enter Password:");


        while(ch!=13) {
            ch=getch();

            if(ch!=13 && ch!=8){
                putch('*');
                pass[i] = ch;
                i++;
            }
        }

        pass[i] = '\0';

        if(strcmp(pass,password)==0) {

            gotoxy(15,9);
            printf("Password match");
            mainmenu();

       } else {

          gotoxy(15,16);
          printf("\aWarning!! Incorrect Password");
          getch();
          login();
       }
    } else {
        userlogin();
    }
}

void userlogin() {
    system("cls");
    int d;
    gotoxy(10, 2);
    printf("Enter your ID: ");
    scanf("%d", &d);
    fp=fopen("tanjim.dat", "rb");
    while(fread(&mmbr, sizeof(mmbr), 1 , fp) == 1) {
        if(mmbr.id == d) {
            userview(d);
        }
    }
    gotoxy(3, 8);
    printf("Press ENTER to close the system or press any key to back login page");
    if(getch() == 13) {
        exit(1);
    } else {
        login();
    }

}
/*===================================================================
|       Main menu functions
|====================================================================
*/
void add() {
    system("cls");
    int i;
    gotoxy(20,3);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 ADD MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    //    show_mouse();
    gotoxy(20,5);
    printf("\xDB\xDB\xDB\xDB\xB2 1. Add Meal");
    gotoxy(20,7);
    printf("\xDB\xDB\xDB\xDB\xB2 2. Add Member");
    gotoxy(20,9);
    printf("\xDB\xDB\xDB\xDB\xB2 3. Add Cost");
    gotoxy(20,11);
    printf("\xDB\xDB\xDB\xDB\xB2 4. Go To Main Menu");
    gotoxy(20,13);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(20,15);
    printf("Enter your choice: ");
    switch(getch()) {
    case '1':
        addMeal();
        break;
    case '2':
        addMember();
        break;
    case '3':
        addCost();
        break;
    case '4':
        mainmenu();
        break;
    default:
        {
            gotoxy(20, 16);
            printf("Wrong entry! Press any key to continue....");
            if(getch()) {
                add();
            }
        }
    }
}

void view() {
    membersView();

}

void edit() {
    updateMember();
}

void dlt(){
    removeMember();
}


/*===================================================================
|       Update functions
|====================================================================
*/
void addMeal() {
    system("cls");
	int c=0, mmeal;
	int d,e;
	gotoxy(20,4);
	printf("=========Edit Member Section============");
	char another='y';
	while(another=='y')
	{
		system("cls");
		gotoxy(15,5);
		printf("List of members with 'Name' => 'ID'");
		fp=fopen("tanjim.dat","rb+");
		int j=6;
		while(fread(&mmbr,sizeof(mmbr),1,fp)==1){
            gotoxy(15,j);
            printf("%s => %d\n", mmbr.name, mmbr.id);
            j++;
		}

		gotoxy(15,j+1);
		printf("Enter Member ID:");
		scanf("%d",&d);
        fp=fopen("tanjim.dat","rb+");
		while(fread(&mmbr,sizeof(mmbr),1,fp)==1)
		{
			if(checked(d)==0)
			{
				gotoxy(15,j+2);
				printf("The Member ID:%d",mmbr.id);
				gotoxy(15,j+3);
				printf("Name: %s",mmbr.name);
				gotoxy(15,j+4);
				printf("Current Meal: %d", mmbr.m.meal);
				gotoxy(15,j+5);

				printf("Add/Sub Meal: ");
				scanf("%d", &mmeal);
				mmbr.m.meal = mmbr.m.meal+(mmeal);
				gotoxy(15,j+6);
				printf("The record is modified");
				fseek(fp,ftell(fp)-sizeof(mmbr),0);
				fwrite(&mmbr,sizeof(mmbr),1,fp);
				fclose(fp);
				c=1;
			}
			if(c==0)
			{
				gotoxy(15,9);
				printf("No member found with %d", d);
			}
		}
		gotoxy(15,16);
		printf("Edit another meal?(Y/N)");
		fflush(stdin);
		another=getch() ;
	}
		returnfunc();
}
void addMember() {
    system("cls");
	int i;

	fp=fopen("tanjim.dat","ab+");

	if(getdata()==1) {


        fseek(fp,0,SEEK_END);
        fwrite(&mmbr,sizeof(mmbr),1,fp);
        fclose(fp);

        gotoxy(20,10);
        printf("The record is successfully saved");
        gotoxy(20,11);
        printf("Save any more?(Y / N):");

        if(getch()=='n')
            mainmenu();
        else
            system("cls");
            addMember();
	}
}
void addCost() {
    system("cls");
	int c=0, cost;
	int d,e;
	gotoxy(20,4);
	printf("========= Update member Cost ============");
	char another='y';
	while(another=='y')
	{
		system("cls");
		gotoxy(15,5);
		printf("List of members with 'Name' => 'ID'");
		fp=fopen("tanjim.dat","rb+");
		int j=6;
		while(fread(&mmbr,sizeof(mmbr),1,fp)==1){
            gotoxy(15,j);
            printf("%s => %d\n", mmbr.name, mmbr.id);
            j++;
		}

		gotoxy(15,j+1);
		printf("Enter Member ID:");
		scanf("%d",&d);
        fp=fopen("tanjim.dat","rb+");
		while(fread(&mmbr,sizeof(mmbr),1,fp)==1)
		{
			if(checked(d)==0)
			{
				gotoxy(15,j+2);
				printf("The Member ID:%d",mmbr.id);
				gotoxy(15,j+3);
				printf("Name: %s",mmbr.name);
				gotoxy(15,j+4);
				printf("Current Cost: %d", mmbr.c.pCost);
				gotoxy(15,j+5);

				printf("Enter Cost: ");
				scanf("%d", &cost);
				mmbr.c.pCost = mmbr.c.pCost+(cost);
				gotoxy(15,j+6);
				printf("The record is modified");
				fseek(fp,ftell(fp)-sizeof(mmbr),0);
				fwrite(&mmbr,sizeof(mmbr),1,fp);
				fclose(fp);
				c=1;
			}
			if(c==0)
			{
				gotoxy(15,9);
				printf("No member found with %d", d);
			}
		}
		gotoxy(15,16);
		printf("Edit another cost?(Y/N)");
		fflush(stdin);
		another=getch() ;
	}
		returnfunc();
}

/*===================================================================
|       Update functions
|====================================================================
*/

void updateMember() {
    system("cls");
	int c=0;
	int d,e;
	gotoxy(20,4);
	printf("=========>> Edit Member <<============");
	char another='y';
	while(another=='y') {
		system("cls");
		fp=fopen("tanjim.dat","rb+");
		int j=6;
		while(fread(&mmbr,sizeof(mmbr),1,fp)==1){
            gotoxy(15,j);
            printf("%s => %d\n", mmbr.name, mmbr.id);
            j++;
		}
		gotoxy(15,j+2);
		printf("Enter Member Id to be edited:");
		scanf("%d",&d);
		fp=fopen("tanjim.dat","rb+");
		while(fread(&mmbr,sizeof(mmbr),1,fp)==1){
			if(checked(d)==0) {
				gotoxy(15,j+3);
				printf("The Member ID:%d, Name: %s, Cost: %d",mmbr.id, mmbr.name, mmbr.c.pCost);

				gotoxy(15,j+4);
				printf("Enter New Name:");
				scanf("%s",mmbr.name);
				gotoxy(15,j+5);
				printf("Cost:");
				scanf("%d",&mmbr.c.pCost);
				gotoxy(15,j+6);
				printf("The record is modified");
				fseek(fp,ftell(fp)-sizeof(mmbr),0);
				fwrite(&mmbr,sizeof(mmbr),1,fp);
				fclose(fp);
				c=1;
			}
			if(c==0)
			{
				gotoxy(15,9);
				printf("No record found");
			}
		}
		gotoxy(15,j+8);
		printf("Modify another Record?(Y/N)");
		fflush(stdin);
		another=getch() ;
	}
		returnfunc();
}


void membersView() {
    int i=0,j;
    int totalCost=0;
    int totalMeal=0;
    float pmc=1;

    system("cls");
    gotoxy(1,1);
    printf("==========================>> Member List <<============================");
    gotoxy(5,2);
    printf("ID");
    gotoxy(20, 2);
    printf("Name");
    gotoxy(35, 2);
    printf("Cost");
    gotoxy(50, 2);
    printf("Meals");
    gotoxy(65, 2);
    printf("Entry date");
    j=4;

    fp = fopen("tanjim.dat", "rb");
    //rewind(fp);
	while(fread(&mmbr,sizeof(mmbr),1,fp)==1) {
        gotoxy(5,j);
        printf("%d",mmbr.id);
        gotoxy(20,j);
        printf("%s", mmbr.name);
        gotoxy(35,j);
        printf("%d", mmbr.c.pCost);
        gotoxy(50,j);
        printf("%d", mmbr.m.meal);
        gotoxy(65,j);
        printf("%s", mmbr.cdt.dte);
        printf("\n\n");
        j++;
        i++;
        totalCost = mmbr.c.pCost+totalCost;
        totalMeal = mmbr.m.meal+totalMeal;
      }

      mmbr.c.tCosts = totalCost;
      pmc = (float) totalCost / (float)totalMeal;

      gotoxy(3,j+4);
      printf("Total Members : %d",i);
      gotoxy(3,j+5);
      printf("Total Total Costs : %d",totalCost);
      gotoxy(3,j+6);
      printf("Total Total Meals : %d",totalMeal);
      gotoxy(3,j+7);
      if(pmc >= 0) {
            printf("Total Meal rate : %.2f",pmc);
      }

        gotoxy(2,j+9);
        printf("=========================Final calculation===============================");
        gotoxy(5, j+10);
        printf("ID");
        gotoxy(20, j+10);
        printf("Name");
        gotoxy(35, j+10);
        printf("Total bill");
        gotoxy(50, j+10);
        printf("Owe");
        gotoxy(65, j+10);
        printf("Get");
        j= j+11+1;
        float tbill, owe, get;
        fp = fopen("tanjim.dat", "rb");
        while(fread(&mmbr,sizeof(mmbr),1,fp)==1) {
            gotoxy(5, j);
            printf("%d", mmbr.id);
            gotoxy(20, j);
            printf("%s", mmbr.name);
            gotoxy(35, j);
            tbill =  mmbr.m.meal * pmc;
            printf("%.2f", tbill);

            owe = tbill - (float) mmbr.c.pCost;
            gotoxy(50, j);
            if(owe > 0) {
                printf("%.2f", owe);
            } else {
                printf("%.2f", 0.00);
            }

            get = (float) mmbr.c.pCost -tbill;
            gotoxy(65, j);
            if(get > 0) {
                printf("%.2f", get);
            } else {
                printf("%.2f", 0.00);
            }

            printf("\n\n");
            j++;
            owe = 0;
            get = 0;
            tbill = 0;
        }


      fclose(fp);




      gotoxy(50,j+2);
      returnfunc();
}

void userview(int d) {
    int i=0,j;
    int totalCost=0;
    int totalMeal=0;
    float pmc=1;

    system("cls");
    gotoxy(1,1);
    printf("==================================>> Member No. %d <<=========================================", d);
    gotoxy(5,2);
    printf("ID");
    gotoxy(20, 2);
    printf("Name");
    gotoxy(35, 2);
    printf("Cost");
    gotoxy(50, 2);
    printf("Meals");
    gotoxy(65, 2);
    printf("Entry date");
    j=4;
    fp = fopen("tanjim.dat", "rb");
    //rewind(fp);
	while(fread(&mmbr,sizeof(mmbr),1,fp)==1) {
        if(mmbr.id == d) {
        gotoxy(5,j);
        printf("%d",mmbr.id);
        gotoxy(20,j);
        printf("%s", mmbr.name);
        gotoxy(35,j);
        printf("%d", mmbr.c.pCost);
        gotoxy(50,j);
        printf("%d", mmbr.m.meal);
        gotoxy(65,j);
        printf("%s", mmbr.cdt.dte);
        printf("\n\n");
        j++;
        i++;
        }
      }


      fclose(fp);
}
/*===================================================================
|       Delete functions
|====================================================================
*/
void removeMember() {
    system("cls");
    int d;
    char another='y';
    while(another=='y')  //infinite loop
    {
	system("cls");
	gotoxy(10,5);
	printf("Enter the Book ID to  delete:");
	scanf("%d",&d);
	fp=fopen("tanjim.dat","rb+");
	rewind(fp);
	while(fread(&mmbr,sizeof(mmbr),1,fp)==1)
	{
	    if(mmbr.id==d)
	    {

		gotoxy(10,7);
		printf("The Member record is available");
		gotoxy(10,8);
		printf("Member name is %s",mmbr.name);
		fmember='t';
	    }
	}
	if(fmember!='t')
	{
	    gotoxy(10,10);
	    printf("No record is found modify the search");
	    if(getch())
	    mainmenu();
	}
	if(fmember=='t' )
	{
	    gotoxy(10,9);
	    printf("Do you want to delete it?(Y/N):");
	    if(getch()=='y')
	    {
		ft=fopen("test.dat","wb+");  //temporary file for delete
		rewind(fp);
		while(fread(&mmbr,sizeof(mmbr),1,fp)==1)
		{
		    if(mmbr.id!=d)
		    {
			fseek(ft,0,SEEK_CUR);
			fwrite(&mmbr,sizeof(mmbr),1,ft); //write all in tempory file except that
		    }                              //we want to delete
		}
		fclose(ft);
		fclose(fp);
		remove("tanjim.dat");
		rename("test.dat","tanjim.dat"); //copy all item from temporary file to fp except that
		fp=fopen("tanjim.dat","rb+");    //we want to delete
		if(fmember=='t')
		{
		    gotoxy(10,10);
		    printf("The record is sucessfully deleted");
		    gotoxy(10,11);
		    printf("Delete another record?(Y/N)");
		}
	    }
	else
	mainmenu();
	fflush(stdin);
	another=getch();
	}
	}
    gotoxy(10,15);
    mainmenu();
}

/*===================================================================
|       Home page functions
|====================================================================
*/

void mainmenu() {
    //loaderanim();
    system("cls");
    //    textbackground(13);
    int i;
    gotoxy(20,3);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2 MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    //    show_mouse();
    gotoxy(20,5);
    printf("\xDB\xDB\xDB\xDB\xB2 1. Add");
    gotoxy(20,7);
    printf("\xDB\xDB\xDB\xDB\xB2 2. View");
    gotoxy(20,9);
    printf("\xDB\xDB\xDB\xDB\xB2 3. Edit");
    gotoxy(20,11);
    printf("\xDB\xDB\xDB\xDB\xB2 4. Delete");
    gotoxy(20,13);
    printf("\xDB\xDB\xDB\xDB\xB2 5. Logout");
    gotoxy(20,15);
    printf("\xDB\xDB\xDB\xDB\xB2 6. Exit");
    gotoxy(20,17);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
    gotoxy(20,19);
    t();
    gotoxy(20,20);
    printf("Enter your choice:");
    switch(getch()) {
    case '1':
        add();
        break;
    case '2':
        view();
        break;
    case '3':
        edit();
        break;
    case '4':
        dlt();
    break;
    case '5':
        login();
        break;
    case '6':
        {
            system("cls");
            gotoxy(20, 10);
            printf("Bye! Exiting");
            int i;
            for(i=0;i<20;i++) {
                printf(".");
                Sleep(60);
            }
            exit(0);
        }
        break;
    default:
        {
            gotoxy(20,20);
            printf("\aWrong Entry!! Press any key to continue.......");
            if(getch())
                mainmenu();
        }

    }

}


int getdata(){
	int t;
	gotoxy(20,3);
    printf("Enter the Information Below");
	gotoxy(20,4);
    printf("\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");

	gotoxy(21,5);
    time_t tg = time(NULL);
    struct tm *tm = localtime(&tg);
//    strftime(&mmbr, sizeof(mmbr), "%c", tm);
    printf("%s\n", mmbr.cdt.dte);

    gotoxy(20,6);
	printf("Member ID:\t");
	scanf("%d",&t);

	if(checked(t) == 0)	{
		gotoxy(20,10);
		printf("\aThe Member id already exists\a");
		getch();
		mainmenu();
		return 0;
	}
	mmbr.id=t;
	gotoxy(20,7);
	printf("Name:");
	scanf("%s",mmbr.name);
	gotoxy(20,8);
	printf("Cost: ");
	scanf("%d",&mmbr.c.pCost);
	return 1;
}
//check whether the user is exist or not
int checked(int t) {
    rewind(fp);
	while(fread(&mmbr,sizeof(mmbr),1,fp)==1)
	if(mmbr.id==t)
	return 0;  //returns 0 if book exits
      return 1; //return 1 if it not
}


void returnfunc(void) {
    printf(" Press ENTER to return to main menu");
    mmbr:
    if(getch()==13) //allow only use of enter
        mainmenu();
    else
        goto mmbr;
}


int t(void) {
    time_t t;
    time(&t);
    printf("Date and time:%s\n",ctime(&t));
    return 0 ;
}
