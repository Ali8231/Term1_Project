#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include <shlwapi.h>

struct UserProfile
{
    char name[30];
    char family[30];
    char user_name[30];
    char password[30];
    char Melli_Num[20];
    char Phone_Num[20];
    char Email[50];
    struct UserProfile *next;
};


struct UserIncome
{
   char amount[25];
   char source[35];
   char Year[7];
   char Month[5];
   char Day[5];
   char description[110];
   struct UserIncome *next;
};

struct UserExpense
{
   char amount[25];
   char subject[35];
   char Year[7];
   char Month[5];
   char Day[5];
   char description[110];
   struct UserExpense *next;
};


char g_username[20];

int Email_Check(char *Email);
int Phone_Num_Check(char *Phone_Num);
int Melli_Num_Check(char *Melli_Num);
int User_Name_Check(char *username);
int Password_Check(char *password);
void Submit_Income();
void Entrance_Menu();
void Signup();
void Login();
int User_Name_Search();
int Login_Pass_Check(int password[]);
void Main_Menu();
int Profile_Iteration();
void Enter_Pass(char *password);
void Submit_Expense();
void Reports();
void Input_Time_Period(int Begin_Year[],int Begin_Month[],int Begin_Day[],int End_Year[],int End_Month[],int End_Day[]);
int Check_Time_Period(int Year[],int Month[],int Day[],int Begin_Year[],int Begin_Month[],int Begin_Day[],int End_Year[],int End_Month[],int End_Day[]);


void main()
{
    printf("Welcome to Ali Asiaee accounting software");
    sleep(2);
    Entrance_Menu();
}

void Entrance_Menu()
{
    system("cls");
    char Entrance_Menu_Choice;
    int temp;
    printf("-----  ENTRANCE MENU  -----\n\n\n1) Signup\n2) Login\n3) Exit\n");
    do//this part requires user to press only mentioned numbers.Any other character is ignored until a right number is entered
    {
        Entrance_Menu_Choice=getch();
        temp=Entrance_Menu_Choice - '0';//convert char to int
    }while(temp<1 || temp>3);
    if(Entrance_Menu_Choice=='1')
        Signup();
    else if(Entrance_Menu_Choice=='2')
        Login();
         else
             Exit();
}

void Exit()
{
    system("cls");
    printf("Thank you for using this program\nHope to see you again soon!\n\n\n");
    sleep(2);
    exit(1);
}

void Signup()
{
    system("cls");
    char name[20],family[25],user_name[20],password[21],Confirm_Pass[21],Melli_Num[12],Phone_Num[13],Email[40];
    int temp;
    FILE *profile,*UserIncome,*UserExpense;
    profile=fopen("profile.txt","a");
    printf("-----SIGN UP PAGE-----\n\n\nEnter your first name: ");
    rewind(profile);
    gets(name);
    strcat(name,"\n");
    printf("Enter your last name: ");
    gets(family);
    strcat(family,"\n");
    printf("\n\nNotes about user name:\n--Your User name must be between 3 and 15 characters\n");
    printf("--Your User name must be unique.");
    printf("\n\nEnter user name: ");
    gets(user_name);
    do
    {
        temp=User_Name_Check(user_name);
        if(temp==-1)
        {
            printf("\n\nUser name is too short.\nEnter a longer user name: ");
            gets(user_name);
        }
        else if(temp==-2)
        {
            printf("\n\nUser name is too long.\nEnter a shorter user name: ");
            gets(user_name);
        }
        else if(temp==-3)
        {
            printf("\n\nThere's another user with this user name.\nEnter another user name: ");
            gets(user_name);
        }
    }while(temp!=0);
    printf("\n");
    strcat(user_name,"\n");
    printf("\n\nNotes about password:\n--Your password must be between 8 and 20 characters\n--");
    printf("Your password must include uppercase and lowercase letters,at least one\n number and one special character(@,*,#,...)\n\nEnter password: ");
    Enter_Pass(password);
    do
    {
        temp=Password_Check(password);
        if(temp==-1)
        {
            printf("\n\nYour password is too short.\nEnter a longer password: ");
            Enter_Pass(password);
        }
        if(temp==-2)
        {
            printf("\n\nYour password is too long.\nEnter a shorter password: ");
            Enter_Pass(password);
        }
        if(temp==-3)
        {
            printf("\n\nYour password is weak\nEnter a stronger password (according to notes): ");
            Enter_Pass(password);
        }
    }while(temp!=0);
    printf("\n\nEnter the password again: ");
    Enter_Pass(Confirm_Pass);
    do
    {
       if(strcmp(password,Confirm_Pass)!=0)
       {
           printf("\nPassword is not the same.\nPlease Enter the same password: ");
           Enter_Pass(Confirm_Pass);
       }
    }while(strcmp(password,Confirm_Pass)!=0);
    strcat(password,"\n");
    printf("\nEnter your Melli number: ");
    gets(Melli_Num);
    do
      {
        temp=Melli_Num_Check(Melli_Num);
        if(temp==-1)
        {
            printf("\n\nMelli number is not correct.\nEnter a valid Melli number: ");
            gets(Melli_Num);
        }
        if(temp==-2)
        {
            printf("\n\nThis person has signed up before.\nEnter another Melli number: ");
            gets(Melli_Num);
        }
    }while(temp!=0);
    strcat(Melli_Num,"\n");
    printf("Enter your phone number: ");
    gets(Phone_Num);
    do
      {
        temp=Phone_Num_Check(Phone_Num);
        if(temp==-1)
        {
            printf("\n\nPhone number is not correct.\nEnter a valid phone number: ");
            gets(Phone_Num);
        }
        if(temp==-2)
        {
            printf("\n\nThis Phone number is used by another user.\nEnter another phone number: ");
            gets(Phone_Num);
        }
    }while(temp!=0);
    strcat(Phone_Num,"\n");
    printf("Enter your Email address: ");
    gets(Email);
    do
      {
        temp=Email_Check(Email);
        if(temp==-1)
        {
            printf("\n\nEmail address is not correct.\nEnter a valid Email address: ");
            gets(Email);
        }
        if(temp==-2)
        {
            printf("\n\nThis Email address is used by another user.\nEnter another Email address: ");
            gets(Email);
        }
    }while(temp!=0);
    strcat(Email,"\n");
    fputs(name,profile);
    fputs(family,profile);
    fputs(user_name,profile);
    fputs(password,profile);
    fputs(Melli_Num,profile);
    fputs(Phone_Num,profile);
    fputs(Email,profile);
    fclose(profile);
    system("cls");
    printf("  User added Successfully");
    sleep(1);
    Entrance_Menu();
}

int Email_Check(char *Email)
{
    int i=0,At_Sign_Check=0,Dot_Check=0;
    char Temp_Email[42];
    FILE *profile;
    profile=fopen("profile.txt","r");
    struct UserProfile *head,*temp;
    head=(struct UserProfile*)malloc(sizeof(struct UserProfile));
    head=Profile_Iteration();
    temp=head;
    for(i=0;i<strlen(Email);i++)
    {
        if(Email[i]=='@')
            At_Sign_Check++;
        if(Email[i]=='.')
            Dot_Check++;
    }
    if(At_Sign_Check==0 || Dot_Check==0)
        return -1;
    strcpy(Temp_Email,Email);
    strcat(Temp_Email,"\n");
    while(temp!=NULL)
    {
        if(strcmp(temp->Email,Temp_Email)==0)
            return -2;
        temp=temp->next;
    }
    return 0;
}


int Phone_Num_Check(char *Phone_Num)
{
    int i=0,Int_Temp=0;
    char Temp_Phone_Num[12];
    FILE *profile;
    profile=fopen("profile.txt","r");
    struct UserProfile *head,*temp;
    head=(struct UserProfile*)malloc(sizeof(struct UserProfile));
    head=Profile_Iteration();
    temp=head;
    if(strlen(Phone_Num)!=11 || Phone_Num[0]!='0' || Phone_Num[1]!='9')
        return -1;
    for(i=0;i<strlen(Phone_Num);i++)
    {
        Int_Temp=Phone_Num[i];
        if(Int_Temp<48 || Int_Temp>57)
            return -1;
    }
    strcpy(Temp_Phone_Num,Phone_Num);
    strcat(Temp_Phone_Num,"\n");
    while(temp!=NULL)
    {
        if(strcmp(temp->Phone_Num,Temp_Phone_Num)==0)
            return -2;
        temp=temp->next;
    }
    return 0;
}


int Melli_Num_Check(char *Melli_Num)
{
    int i=0,Int_Temp=0;
    char Temp_Melli_Num[13];
    FILE *profile;
    profile=fopen("profile.txt","r");
    struct UserProfile *head,*temp;
    head=(struct UserProfile*)malloc(sizeof(struct UserProfile));
    head=Profile_Iteration();
    temp=head;
    if(strlen(Melli_Num)!=10)
        return -1;
    for(i=0;i<strlen(Melli_Num);i++)
    {
        Int_Temp=Melli_Num[i];
        if(Int_Temp<48 || Int_Temp>57)
            return -1;
    }
    strcpy(Temp_Melli_Num,Melli_Num);
    strcat(Temp_Melli_Num,"\n");
    while(temp!=NULL)
    {
        if(strcmp(temp->Melli_Num,Temp_Melli_Num)==0)
            return -2;
        temp=temp->next;
    }
    return 0;
}


int Password_Check(char *password)
{
    int i=0,temp=0,Upper_Case_Check=0,Lower_Case_Check=0,Special_Char_Check=0,Number_Check=0;//for checking how many numbers,special chars and letters are in pass
    if(strlen(password)<8)
        return -1;//password is too short
    if(strlen(password)>20)
        return -2;//password is too long
    for(i=0;i<strlen(password);i++)
    {
        temp=password[i];
        if(temp>=33 && temp<=47)//special chars
            Special_Char_Check++;
        else if(temp>=58 && temp<=64)//special chars
            Special_Char_Check++;
        else if(temp>=91 && temp<=96)//special chars
            Special_Char_Check++;
        else if(temp>=123 && temp<=126)//special chars
            Special_Char_Check++;
        else if(temp>=48 && temp<=57)//numbers
            Number_Check++;
        else if(temp>=65 && temp<=90)//upper case letters
            Upper_Case_Check++;
        else if(temp>=97 && temp<=122)//lower case letters
            Lower_Case_Check++;
    }
    if(Special_Char_Check==0 || Number_Check==0 || Upper_Case_Check==0 || Lower_Case_Check==0)
        return -3;
    return 0;
}

int User_Name_Check(char *username)
{
    char Temp_Username[20];
    FILE *profile;
    profile=fopen("profile.txt","r");
    struct UserProfile *head,*temp;
    head=(struct UserProfile*)malloc(sizeof(struct UserProfile));
    head=Profile_Iteration();
    temp=head;
    if(strlen(username)<3)
        return -1;//length of user name is too short
    if(strlen(username)>15)
        return -2;//length of user name is too long
    strcpy(Temp_Username,username);
    strcat(Temp_Username,"\n");
    while(temp!=NULL)
    {
        if(strcasecmp(temp->user_name,Temp_Username)==0)
            return -3;//user name is not unique
        temp=temp->next;
    }
    fclose(profile);
    return 0;//user name is OK
}



void Enter_Pass(char *password)
{
    char temp;
    int i=0;
    while((temp=getch())!=13)//until user presses enter
    {
        if(temp==8)//if user presses backspace
        {
            if(i==0)
                continue;
            printf("\b \b");//destructive /b
            i--;
            continue;
        }
        password[i]=temp;
        putch('*');
        i++;
    }
    password[i]='\0';
}


void Login()
{
    int User_Name_Found,Pass_Found;
    char password[21];
    system("cls");
    printf("-----LOGIN PAGE-----\n\n\nEnter your user name: ");
    gets(g_username);
    do
    {
        User_Name_Found=User_Name_Search();
        if(User_Name_Found==-1)//user was not found in profile
        {
            printf("\nUser name was not found.\nPlease enter your user name again: ");
            gets(g_username);
        }
    }while(User_Name_Found==-1);
    printf("Enter your password: ");
    Enter_Pass(password);
    do
    {
        Pass_Found=Login_Pass_Check(password);
        if(Pass_Found==-1)//password was not found in profile
        {
            printf("\n\nPassword is not correct.\nPlease enter password again: ");
            Enter_Pass(password);
        }
    }while(Pass_Found==-1);
    Main_Menu();
}


int User_Name_Search()
{
    char temp_Username[25];
    struct UserProfile *head,*temp;
    head=(struct UserProfile*)malloc(sizeof(struct UserProfile));
    head=Profile_Iteration();
    temp=head;
    strcpy(temp_Username,g_username);
    strcat(temp_Username,"\n");
    while(temp!=NULL)
    {
        if(strcmp(temp->user_name,temp_Username)==0)
            return 0;//user name found
        temp=temp->next;
    }
    return -1;//user name not found
}


int Login_Pass_Check(int password[])
{
    char temp_Username[25],temp_Password[25];
    struct UserProfile *head,*temp;
    head=(struct UserProfile*)malloc(sizeof(struct UserProfile));
    head=Profile_Iteration();
    temp=head;
    strcpy(temp_Username,g_username);
    strcpy(temp_Password,password);
    strcat(temp_Username,"\n");//in file last character of each element is a \n to go to next line.concatenation of \n is to match two strings for strcmp
    strcat(temp_Password,"\n");
    while(temp!=NULL)
    {
        if((strcmp(temp_Username,temp->user_name)==0) && (strcmp(temp_Password,temp->password)==0))
            return 0;//pass found in profile
        temp=temp->next;
    }
    return -1;//pass not found in profile
}


void Main_Menu()
{
    system("cls");
    char Main_Menu_Choice;
    int temp;
    printf("-----MAIN MENU-----\n\n\n1) Submit Income\n2) Submit Expenses\n3) Reports\n4) Settings\n5) Logout\n6) Exit\n");
    do
    {
        Main_Menu_Choice=getch();
        temp=Main_Menu_Choice - '0';
    }while(temp<1 || temp>6);

    switch(Main_Menu_Choice)
    {
        case '1':
        {
            Submit_Income();
            break;
        }
        case '2':
        {
            Submit_Expense();
            break;
        }
        case '3':
        {
            Reports();
            break;
        }
        case '4':
        {
            Settings();
            break;
        }
        case '5':
        {
            g_username[0]='/0';
            Entrance_Menu();
            break;
        }
        default:
            Exit();
    }
}

void Submit_Income()
{
    system("cls");
    char After_Submit_Choice,Incomes_Directory[50],Income_Amount[20],Choose_Source,Source_Of_Income[30],Year_Of_Income[6],Month_Of_Income[4];
    char Day_Of_Income[4],Income_Description[100];
    int temp;
    FILE *Incomes;
    strcpy(Incomes_Directory,"F:\\\\C_Programs\\\\Final_Project\\\\incomes\\\\");
    strcat(Incomes_Directory,g_username);
    strcat(Incomes_Directory,".txt");
    Incomes=fopen(Incomes_Directory,"a");
    printf("----- INCOME SUBMIT -----\n\n\nEnter amount of income in Iranian RIAL currency: ");
    gets(Income_Amount);
    strcat(Income_Amount,"\n");
    Choose_Source_Of_Income(Source_Of_Income);
    printf("Please enter year of income in YYYY format: ");
    gets(Year_Of_Income);
    strcat(Year_Of_Income,"\n");
    printf("Please enter month of income in MM format(without zero): ");
    gets(Month_Of_Income);
    strcat(Month_Of_Income,"\n");
    printf("Please enter day of income in DD format(without zero): ");
    gets(Day_Of_Income);
    strcat(Day_Of_Income,"\n");
    printf("Please enter a short(one line) description: ");
    gets(Income_Description);
    if(strcmp(Income_Description,"")==0)
        strcpy(Income_Description,"None");
    strcat(Income_Description,"\n");
    fputs(Income_Amount,Incomes);
    fputs(Source_Of_Income,Incomes);
    fputs(Year_Of_Income,Incomes);
    fputs(Month_Of_Income,Incomes);
    fputs(Day_Of_Income,Incomes);
    fputs(Income_Description,Incomes);
    fclose(Incomes);
    system("cls");
    printf("Income submitted successfully");
    sleep(1);
    system("cls");
    printf("\n1) Submit another income\n2) Return to main menu\n");
    do
    {
        After_Submit_Choice=getch();
        temp=After_Submit_Choice-'0';
    }while(temp!=1 && temp!=2);

    if(After_Submit_Choice=='1')
        Submit_Income();
    else
        Main_Menu();
}

void Submit_Expense()
{
    system("cls");
    char After_Submit_Choice,Expenses_Directory[50],Expense_Amount[20],Choose_Subject,Subject_Of_Expense[30],Year_Of_Expenditure[6];
    char Month_Of_Expenditure[4],Day_Of_Expenditure[4],Expense_Description[100];
    int temp;
    FILE *Expenses;
    strcpy(Expenses_Directory,"F:\\\\C_Programs\\\\Final_Project\\\\expenses\\\\");
    strcat(Expenses_Directory,g_username);
    strcat(Expenses_Directory,".txt");
    Expenses=fopen(Expenses_Directory,"a");
    printf("----- EXPENSE SUBMIT -----\n\n\nEnter amount of expenditure in Iranian RIAL currency: ");
    gets(Expense_Amount);
    strcat(Expense_Amount,"\n");
    Choose_Subject_Of_Expense(Subject_Of_Expense);
    printf("Please enter year of expenditure in YYYY format: ");
    gets(Year_Of_Expenditure);
    strcat(Year_Of_Expenditure,"\n");
    printf("Please enter month of expenditure in MM format(without zero): ");
    gets(Month_Of_Expenditure);
    strcat(Month_Of_Expenditure,"\n");
    printf("Please enter day of expenditure in DD format(without zero): ");
    gets(Day_Of_Expenditure);
    strcat(Day_Of_Expenditure,"\n");
    printf("Please enter a short(one line) description: ");
    gets(Expense_Description);
    if(strcmp(Expense_Description,"")==0)//if user enters nothing in description part
        strcpy(Expense_Description,"None");
    strcat(Expense_Description,"\n");
    fputs(Expense_Amount,Expenses);
    fputs(Subject_Of_Expense,Expenses);
    fputs(Year_Of_Expenditure,Expenses);
    fputs(Month_Of_Expenditure,Expenses);
    fputs(Day_Of_Expenditure,Expenses);
    fputs(Expense_Description,Expenses);
    fclose(Expenses);
    system("cls");
    printf("Expense submitted successfully");
    sleep(1);
    system("cls");
    printf("\n1) Submit another expense\n2) Return to main menu\n");
    do
    {
        After_Submit_Choice=getch();
        temp=After_Submit_Choice-'0';
    }while(temp!=1 && temp!=2);

    if(After_Submit_Choice=='1')
        Submit_Expense();
    else
        Main_Menu();
}

void Reports()
{
    system("cls");
    char Report_Type_Choice;
    int temp;
    printf("-----  REPORTS MENU  -----\n\n\n1) Account balance\n2) Incomes Reports\n3) Expenses Reports\n");
    do
    {
        Report_Type_Choice=getch();
        temp=Report_Type_Choice - '0';
    }while(temp<1 || temp>3);
    if(Report_Type_Choice=='1')
        Account_Balance();
    else if(Report_Type_Choice=='2')
        Income_Reports();
    else
        Expense_Reports();
}

void Income_Reports()
{
    system("cls");
    char Income_Report_Type;
    int temp;
    printf("-----  INCOME REPORTS  -----\n\n\nPlease choose report type from the list: \n\n\n1) Annual income statement\n");
    printf("2) Income statement for a time period\n3) Specific income statement for a time period\n4) Incomes share ratio\n");
    printf("5) Detailed income statement for a time period\n6) Highest income in a time period\n7) Search in descriptions");
    do
    {
        Income_Report_Type=getch();
        temp=Income_Report_Type-'0';
    }while(temp<1 || temp>7);
    switch(Income_Report_Type)
    {
        case '1':
        {
            Annual_Income();
            break;
        }
        case '2':
        {
            Income_In_Time_Period();
            break;
        }
        case '3':
        {
            Specific_Income_In_Time_Period();
            break;
        }
        case '4':
        {
            system("cls");
            printf("\n\n\nPlease choose time period of the report: \n\n\n1) All time\n2) Specific period ");
            do
            {
                Income_Report_Type=getch();
                temp=Income_Report_Type-'0';
            }while(temp!=1 && temp!=2);
            if(Income_Report_Type=='1')
                Incomes_Share_Ratio();
            else
                Incomes_Share_Ratio_In_Time_Period();
            break;
        }
        case '5':
        {
            Detailed_Incomes_In_Time_Period();
            break;
        }
        case '6':
        {
            Highest_Income_In_Time_Period();
            break;
        }
        default:
        {
            Income_Search_In_Description();
        }
    }
}

void Income_Search_In_Description()
{
    system("cls");
    struct UserIncome *head,*Income_Temp;
    head=(struct UserIncome*)malloc(sizeof(struct UserIncome));
    head=Income_Iteration();
    Income_Temp=head;
    char Word_In_Description[100];
    int count=1;
    printf("Please enter a word or phrase: ");
    gets(Word_In_Description);
    system("cls");
    while(Income_Temp->next!=NULL)
    {
        if(StrStrIA(Income_Temp->description,Word_In_Description)!=NULL)
        {
            printf("INCOME #%d\n\n",count);
            Income_Temp->amount[strlen(Income_Temp->amount)-1]='\0';//To delete \n from last character of the string
            printf("Amount = ",Income_Temp->amount);
            puts(Income_Temp->amount);
            Income_Temp->source[strlen(Income_Temp->source)-1]='\0';
            printf("Source : ");
            puts(Income_Temp->source);
            Income_Temp->Year[strlen(Income_Temp->Year)-1]='\0';
            Income_Temp->Month[strlen(Income_Temp->Month)-1]='\0';
            printf("Date : %s/%s/%s",Income_Temp->Year,Income_Temp->Month,Income_Temp->Day);
            Income_Temp->description[strlen(Income_Temp->description)-1]='\0';
            printf("Description : ");
            if(strcmp(Income_Temp->description,"")==0)
                printf("None");
            else
                puts(Income_Temp->description);
            count++;
            printf("\n\n\n\n\n");
        }
        Income_Temp=Income_Temp->next;
    }
    printf("\n\n\nPress any button to continue");
    getch();
    Return_To_Menu_For_Reports();
}

void Highest_Income_In_Time_Period()
{
    system("cls");
    char Begin_Year[6],End_Year[6],Begin_Month[4],End_Month[4],Begin_Day[4],End_Day[4];
    char *end;
    int Income_Date;
    long long int Highest_Income=0;
    struct UserIncome *head,*Income_Temp;
    head=(struct UserIncome*)malloc(sizeof(struct UserIncome));
    head=Income_Iteration();
    Income_Temp=head;
    Input_Time_Period(Begin_Year,Begin_Month,Begin_Day,End_Year,End_Month,End_Day);
    while(Income_Temp->next!=NULL)
    {
        Income_Date=Check_Time_Period(Income_Temp->Year,Income_Temp->Month,Income_Temp->Day,Begin_Year,Begin_Month,Begin_Day,End_Year,End_Month,End_Day);
        if(Income_Date==0)//if income is in time period
        {
            if(Highest_Income==0)
            {
                Highest_Income=strtoull(Income_Temp->amount,&end,10);
                Income_Temp=Income_Temp->next;
                continue;
            }
            if(strtoull(Income_Temp,&end,10)>Highest_Income)
                Highest_Income=strtoull(Income_Temp,&end,10);
        }
        Income_Temp=Income_Temp->next;
    }
    system("cls");
    if(Highest_Income==0)
        printf("\n\n\nYou have not submitted any income in this time period");
    else
        printf("\n\n\nYour highest income between %s/%s/%s and %s/%s/%s\nis %lld",Begin_Year,Begin_Month,Begin_Day,End_Year,End_Month,End_Day,Highest_Income);
    printf(" Iranian RIALS.\n\n\nPress any button to continue");
    getch();//waits for user to press a key
    Return_To_Menu_For_Reports();
}

void Detailed_Incomes_In_Time_Period()
{
    system("cls");
    char Begin_Year[6],End_Year[6],Begin_Month[4],End_Month[4],Begin_Day[4],End_Day[4];
    char *end;
    int Income_Date,count=1;
    struct UserIncome *head,*Income_Temp;
    head=(struct UserIncome*)malloc(sizeof(struct UserIncome));
    head=Income_Iteration();
    Income_Temp=head;
    Input_Time_Period(Begin_Year,Begin_Month,Begin_Day,End_Year,End_Month,End_Day);
    system("cls");
    while(Income_Temp->next!=NULL)
    {
        Income_Date=Check_Time_Period(Income_Temp->Year,Income_Temp->Month,Income_Temp->Day,Begin_Year,Begin_Month,Begin_Day,End_Year,End_Month,End_Day);
        if(Income_Date==0)
        {
            printf("INCOME #%d\n\n",count);
            Income_Temp->amount[strlen(Income_Temp->amount)-1]='\0';
            printf("Amount = ",Income_Temp->amount);
            puts(Income_Temp->amount);
            Income_Temp->source[strlen(Income_Temp->source)-1]='\0';
            printf("Source : ");
            puts(Income_Temp->source);
            Income_Temp->Year[strlen(Income_Temp->Year)-1]='\0';
            Income_Temp->Month[strlen(Income_Temp->Month)-1]='\0';
            printf("Date : %s/%s/%s",Income_Temp->Year,Income_Temp->Month,Income_Temp->Day);
            Income_Temp->description[strlen(Income_Temp->description)-1]='\0';
            printf("Description : ");
            if(strcmp(Income_Temp->description,"")==0)
                printf("None");
            else
                puts(Income_Temp->description);
            count++;
            printf("\n\n\n\n\n");
        }
        Income_Temp=Income_Temp->next;
    }
    printf("\n\n\nPress enter to continue");
    getch();
    Return_To_Menu_For_Reports();
}


void Incomes_Share_Ratio_In_Time_Period()
{
   system("cls");
   char Begin_Year[6],End_Year[6],Begin_Month[4],End_Month[4],Begin_Day[4],End_Day[4];
   char *end;
   long long int Salary_Count=0,Pocket_Count=0,Grant_Count=0,Gov_Aid_Count=0,Loan_Count=0,Interest_Count=0,SUM=0,Others_Count=0;;
   int Income_Date;
   double Salary_Share=0,Pocket_Share=0,Grant_Share=0,Gov_Aid_Share=0,Loan_Share=0,Interest_Share=0,Others_Share=0;
   struct UserIncome *head,*Income_Temp;
   head=(struct UserIncome*)malloc(sizeof(struct UserIncome));
   head=Income_Iteration();
   Income_Temp=head;
   Input_Time_Period(Begin_Year,Begin_Month,Begin_Day,End_Year,End_Month,End_Day);
   while(Income_Temp->next!=NULL)
   {
        Income_Date=Check_Time_Period(Income_Temp->Year,Income_Temp->Month,Income_Temp->Day,Begin_Year,Begin_Month,Begin_Day,End_Year,End_Month,End_Day);
        if(Income_Date==0)
        {
            if(strcasecmp(Income_Temp->source,"Salary\n")==0)
                Salary_Count+=strtoull(Income_Temp->amount,&end,10);
            else if(strcasecmp(Income_Temp->source,"Pocket Money\n")==0)
                Pocket_Count+=strtoull(Income_Temp->amount,&end,10);
            else if(strcasecmp(Income_Temp->source,"University Grant\n")==0)
                Grant_Count+=strtoull(Income_Temp->amount,&end,10);
            else if(strcasecmp(Income_Temp->source,"Government Aid\n")==0)
                Gov_Aid_Count+=strtoull(Income_Temp->amount,&end,10);
            else if(strcasecmp(Income_Temp->source,"Loan\n")==0)
                Loan_Count+=strtoull(Income_Temp->amount,&end,10);
            else if(strcasecmp(Income_Temp->source,"Bank Interest\n")==0)
                Interest_Count+=strtoull(Income_Temp->amount,&end,10);
            else
                Others_Count+=strtoull(Income_Temp->amount,&end,10);
            SUM+=strtoull(Income_Temp->amount,&end,10);
        }
        Income_Temp=Income_Temp->next;
   }
   Salary_Share=((double)Salary_Count/SUM) * 100;
   Pocket_Share=((double)Pocket_Count/SUM) * 100;
   Grant_Share=((double)Grant_Count/SUM) * 100;
   Gov_Aid_Share=((double)Gov_Aid_Count/SUM) * 100;
   Loan_Share=((double)Loan_Count/SUM) * 100;
   Interest_Share=((double)Interest_Count/SUM) * 100;
   Others_Share=((double)Others_Count/SUM) * 100;
   system("cls");
   printf("\n\nYour income share ratio between %s/%s/%s and %s/%s/%s :\n\n\n",Begin_Year,Begin_Month,Begin_Day,End_Year,End_Month,End_Day);
   printf("Salary %20.3Lf%%\nPocket Money %14.3Lf%%\nUniversity Grant %10.3Lf%%\nGovernment Aid %12.3Lf%%\n",Salary_Share,Pocket_Share,Grant_Share,Gov_Aid_Share);
   printf("Loan %22.3Lf%%\nBank Interest %13.3Lf%%\nOther Incomes %13.3Lf%%\n\n\nPress any button to continue",Loan_Share,Interest_Share,Others_Share);
   getch();
   Return_To_Menu_For_Reports();//at the end user can go back to reports menu,main menu or exit
}


void Incomes_Share_Ratio()
{
   system("cls");
   char *end;
   long long int Salary_Count=0,Pocket_Count=0,Grant_Count=0,Gov_Aid_Count=0,Loan_Count=0,Interest_Count=0,SUM=0,Others_Count=0;;
   double Salary_Share=0,Pocket_Share=0,Grant_Share=0,Gov_Aid_Share=0,Loan_Share=0,Interest_Share=0,Others_Share=0;
   struct UserIncome *head,*Income_Temp;
   head=(struct UserIncome*)malloc(sizeof(struct UserIncome));
   head=Income_Iteration();
   Income_Temp=head;
   while(Income_Temp->next!=NULL)
   {
       if(strcasecmp(Income_Temp->source,"Salary\n")==0)
           Salary_Count+=strtoull(Income_Temp->amount,&end,10);
       else if(strcasecmp(Income_Temp->source,"Pocket Money\n")==0)
           Pocket_Count+=strtoull(Income_Temp->amount,&end,10);
       else if(strcasecmp(Income_Temp->source,"University Grant\n")==0)
           Grant_Count+=strtoull(Income_Temp->amount,&end,10);
       else if(strcasecmp(Income_Temp->source,"Government Aid\n")==0)
           Gov_Aid_Count+=strtoull(Income_Temp->amount,&end,10);
       else if(strcasecmp(Income_Temp->source,"Loan\n")==0)
           Loan_Count+=strtoull(Income_Temp->amount,&end,10);
       else if(strcasecmp(Income_Temp->source,"Bank Interest\n")==0)
           Interest_Count+=strtoull(Income_Temp->amount,&end,10);
       else
           Others_Count+=strtoull(Income_Temp->amount,&end,10);
       SUM+=strtoull(Income_Temp->amount,&end,10);
       Income_Temp=Income_Temp->next;
   }
   Salary_Share=((double)Salary_Count/SUM) * 100;
   Pocket_Share=((double)Pocket_Count/SUM) * 100;
   Grant_Share=((double)Grant_Count/SUM) * 100;
   Gov_Aid_Share=((double)Gov_Aid_Count/SUM) * 100;
   Loan_Share=((double)Loan_Count/SUM) * 100;
   Interest_Share=((double)Interest_Count/SUM) * 100;
   Others_Share=((double)Others_Count/SUM) * 100;
   system("cls");
   printf("\n\nYour All time income share ratio :\n\n\nSalary %20.3Lf%%\nPocket Money %14.3Lf%%\n",Salary_Share,Pocket_Share);
   printf("University Grant %10.3Lf%%\nGovernment Aid %12.3Lf%%\nLoan %22.3Lf%%\n",Grant_Share,Gov_Aid_Share,Loan_Share);
   printf("Bank Interest %13.3Lf%%\nOther Incomes %13.3Lf%%\n\n\nPress any button to continue",Interest_Share,Others_Share);
   getch();
   Return_To_Menu_For_Reports();
}


void Specific_Income_In_Time_Period()
{
   system("cls");
   struct UserIncome *head,*Income_Temp;
   char Source_Of_Income[30],Begin_Year[6],End_Year[6],Begin_Month[4],End_Month[4],Begin_Day[4],End_Day[4];
   char *end;
   long long int Income_Count=0;
   int temp,Income_Date;
   head=(struct UserIncome*)malloc(sizeof(struct UserIncome));
   head=Income_Iteration();
   Income_Temp=head;
   Choose_Source_Of_Income(Source_Of_Income);
   Input_Time_Period(Begin_Year,Begin_Month,Begin_Day,End_Year,End_Month,End_Day);
   while(Income_Temp->next!=NULL)
   {
       if(strcasecmp(Income_Temp->source,Source_Of_Income)==0)
       {
           Income_Date=Check_Time_Period(Income_Temp->Year,Income_Temp->Month,Income_Temp->Day,Begin_Year,Begin_Month,Begin_Day,End_Year,End_Month,End_Day);
           if(Income_Date==0)
               Income_Count+=strtoull(Income_Temp->amount,&end,10);
       }
       Income_Temp=Income_Temp->next;
   }
   Source_Of_Income[strlen(Source_Of_Income)-1]='\0';
   system("cls");
   printf("\n\n\nYour total income from %s between %s/%s/%s and %s/%s/%s\n",Source_Of_Income,Begin_Year,Begin_Month,Begin_Day,End_Year,End_Month,End_Day);
   printf("is %lld Iranian RIALS.\n\n\nPress any button to continue",Income_Count);
   getch();
   Return_To_Menu_For_Reports();
}


void Income_In_Time_Period()
{
   system("cls");
   struct UserIncome *head,*Income_Temp;
   char Begin_Year[6],End_Year[6],Begin_Month[4],End_Month[4],Begin_Day[4],End_Day[4];
   char *end;
   long long int Income_Count=0;
   int Income_Date;
   head=(struct UserIncome*)malloc(sizeof(struct UserIncome));
   head=Income_Iteration();
   Income_Temp=head;
   Input_Time_Period(Begin_Year,Begin_Month,Begin_Day,End_Year,End_Month,End_Day);
   while(Income_Temp->next!=NULL)
   {
       Income_Date=Check_Time_Period(Income_Temp->Year,Income_Temp->Month,Income_Temp->Day,Begin_Year,Begin_Month,Begin_Day,End_Year,End_Month,End_Day);
       if(Income_Date==0)
           Income_Count+=strtoull(Income_Temp->amount,&end,10);
       Income_Temp=Income_Temp->next;
   }
   system("cls");
   printf("\n\n\nYour total income between %s/%s/%s and %s/%s/%s\n",Begin_Year,Begin_Month,Begin_Day,End_Year,End_Month,End_Day);
   printf("is %lld Iranian RIALS.\n\n\nPress any button to continue",Income_Count);
   getch();
   Return_To_Menu_For_Reports();
}


void Annual_Income()
{
    system("cls");
    struct UserIncome *head,*Income_Temp;
    char Year[6];
    char *end;
    long long int Income_Count=0;
    head=(struct UserIncome*)malloc(sizeof(struct UserIncome));
    head=Income_Iteration();
    Income_Temp=head;
    printf("Please enter a year: ");
    gets(Year);
    while(Income_Temp->next!=NULL)
    {
        if(strtol(Income_Temp->Year,&end,10)==strtol(Year,&end,10))
            Income_Count+=strtoull(Income_Temp->amount,&end,10);
        Income_Temp=Income_Temp->next;
    }
    printf("Your income in %s is %lld Iranian RIALS.\n\nPress any button to continue",Year,Income_Count);
    getch();
    Return_To_Menu_For_Reports();
}


void Account_Balance()
{
    system("cls");
    long long int Income_Count=0,Expense_Count=0,Balance=0;
    char *end;
    struct UserIncome *Income_Head,*Income_Temp;
    struct UserExpense *Expense_Head, *Expense_Temp;
    Income_Head=(struct UserIncome*)malloc(sizeof(struct UserIncome));
    Expense_Head=(struct UserExpense*)malloc(sizeof(struct UserExpense));
    Income_Head=Income_Iteration();
    Expense_Head=Expense_Iteration();
    Income_Temp=Income_Head;
    Expense_Temp=Expense_Head;
    while(Income_Temp->next!=NULL)
    {
        Income_Count+=strtoull(Income_Temp->amount,&end,10);
        Income_Temp=Income_Temp->next;
    }
    while(Expense_Temp->next!=NULL)
    {
        Expense_Count+=strtoull(Expense_Temp->amount,&end,10);
        Expense_Temp=Expense_Temp->next;
    }
    Balance=Income_Count-Expense_Count;
    printf("\n\nYour account balance is %lld Iranian RIALS\n\nPlease press any button to continue",Balance);
    getch();
    Return_To_Menu_For_Reports();
}

void Expense_Reports()
{
    system("cls");
    char Expense_Report_Type;
    int temp;
    printf("-----  EXPENSE REPORTS  -----\n\n\nPlease choose report type from the list: \n\n\n1) Annual expense statement\n");
    printf("2) Expense statement for a time period\n3) Specific expense statement for a time period\n4) Expense share ratio\n");
    printf("5) Detailed expense statement for a time period\n6) Highest expense in a time period\n7) Search in descriptions");
    do
    {
        Expense_Report_Type=getch();
        temp=Expense_Report_Type-'0';
    }while(temp<1 || temp>7);
    switch(Expense_Report_Type)
    {
        case '1':
        {
            Annual_Expense();
            break;
        }
        case '2':
        {
            Expense_In_Time_Period();
            break;
        }
        case '3':
        {
            Specific_Expense_In_Time_Period();
            break;
        }
        case '4':
        {
            system("cls");
            printf("\n\n\nPlease choose time period of the report: \n\n\n1) All time\n2) Specific period ");
            do
            {
                Expense_Report_Type=getch();
                temp=Expense_Report_Type-'0';
            }while(temp!=1 && temp!=2);
            if(Expense_Report_Type=='1')
                Expense_Share_Ratio();
            else
                Expense_Share_Ratio_In_Time_Period();
            break;
        }
        case '5':
        {
            Detailed_Expense_In_Time_Period();
            break;
        }
        case '6':
        {
            Highest_Expense_In_Time_Period();
            break;
        }
        default:
        {
            Expense_Search_In_Description();
        }
    }
}

void Annual_Expense()
{
    system("cls");
    struct UserExpense *head,*Expense_Temp;
    char Year[6];
    char *end;
    long long int Expense_Count=0;
    head=(struct UserExpense*)malloc(sizeof(struct UserExpense));
    head=Expense_Iteration();
    Expense_Temp=head;
    printf("Please enter a year: ");
    gets(Year);
    while(Expense_Temp->next!=NULL)
    {
        if(strtol(Expense_Temp->Year,&end,10)==strtol(Year,&end,10))
            Expense_Count+=strtoull(Expense_Temp->amount,&end,10);
        Expense_Temp=Expense_Temp->next;
    }
    printf("Your expense amount in %s is %lld Iranian RIALS.\n\nPress any button to continue",Year,Expense_Count);
    getch();
    Return_To_Menu_For_Reports();
}


void Expense_In_Time_Period()
{
   system("cls");
   struct UserExpense *head,*Expense_Temp;
   char Begin_Year[6],End_Year[6],Begin_Month[4],End_Month[4],Begin_Day[4],End_Day[4];
   char *end;
   long long int Expense_Count=0;
   int Expense_Date;
   head=(struct UserExpense*)malloc(sizeof(struct UserExpense));
   head=Expense_Iteration();
   Expense_Temp=head;
   Input_Time_Period(Begin_Year,Begin_Month,Begin_Day,End_Year,End_Month,End_Day);
   while(Expense_Temp->next!=NULL)
   {
       Expense_Date=Check_Time_Period(Expense_Temp->Year,Expense_Temp->Month,Expense_Temp->Day,Begin_Year,Begin_Month,Begin_Day,End_Year,End_Month,End_Day);
       if(Expense_Date==0)
           Expense_Count+=strtoull(Expense_Temp->amount,&end,10);
       Expense_Temp=Expense_Temp->next;
   }
   system("cls");
   printf("\n\n\nYour total expense between %s/%s/%s and %s/%s/%s\n",Begin_Year,Begin_Month,Begin_Day,End_Year,End_Month,End_Day);
   printf("is %lld Iranian RIALS.\n\n\nPress any button to continue",Expense_Count);
   getch();
   Return_To_Menu_For_Reports();
}

void Specific_Expense_In_Time_Period()
{
   system("cls");
   struct UserExpense *head,*Expense_Temp;
   char Subject_Of_Expense[30],Begin_Year[6],End_Year[6],Begin_Month[4],End_Month[4],Begin_Day[4],End_Day[4];
   char *end;
   long long int Expense_Count=0;
   int temp,Expense_Date;
   head=(struct UserExpense*)malloc(sizeof(struct UserExpense));
   head=Expense_Iteration();
   Expense_Temp=head;
   Choose_Subject_Of_Expense(Subject_Of_Expense);
   Input_Time_Period(Begin_Year,Begin_Month,Begin_Day,End_Year,End_Month,End_Day);
   while(Expense_Temp->next!=NULL)
   {
       if(strcasecmp(Expense_Temp->subject,Subject_Of_Expense)==0)
       {
           Expense_Date=Check_Time_Period(Expense_Temp->Year,Expense_Temp->Month,Expense_Temp->Day,Begin_Year,Begin_Month,Begin_Day,End_Year,End_Month,End_Day);
           if(Expense_Date==0)
               Expense_Count+=strtoull(Expense_Temp->amount,&end,10);
       }
       Expense_Temp=Expense_Temp->next;
   }
   Subject_Of_Expense[strlen(Subject_Of_Expense)-1]='\0';
   system("cls");
   printf("\n\n\nYour total expense from %s between %s/%s/%s and %s/%s/%s\n",Subject_Of_Expense,Begin_Year,Begin_Month,Begin_Day,End_Year,End_Month,End_Day);
   printf("is %lld Iranian RIALS.\n\n\nPress any button to continue",Expense_Count);
   getch();
   Return_To_Menu_For_Reports();
}

void Expense_Share_Ratio()
{
   system("cls");
   char *end;
   long long int Healthcare_Count=0,Food_Count=0,Care_Cleaning_Count=0,Bills_Count=0,Rent_Mortgage_Count=0,Loan_Payment_Count=0,Education_Count=0;
   long long int Transportation_Count=0,Clothing_Count=0,Recreation_Count=0,Charity_Count=0,Others_Count=0,SUM=0;
   double Healthcare_Share=0,Food_Share=0,Care_Cleaning_Share=0,Bills_Share=0,Rent_Mortgage_Share=0,Loan_Payment_Share=0,Education_Share=0;
   double Transportation_Share=0,Clothing_Share=0,Recreation_Share=0,Charity_Share=0,Others_Share=0;
   struct UserExpense *head,*Expense_Temp;
   head=(struct UserExpense*)malloc(sizeof(struct UserExpense));
   head=Expense_Iteration();
   Expense_Temp=head;
   while(Expense_Temp->next!=NULL)
   {
       if(strcasecmp(Expense_Temp->subject,"Healthcare\n")==0)
           Healthcare_Count+=strtoull(Expense_Temp->amount,&end,10);
       else if(strcasecmp(Expense_Temp->subject,"Food\n")==0)
            Food_Count+=strtoull(Expense_Temp->amount,&end,10);
       else if(strcasecmp(Expense_Temp->subject,"Personal Care & Cleaning\n")==0)
           Care_Cleaning_Count+=strtoull(Expense_Temp->amount,&end,10);
       else if(strcasecmp(Expense_Temp->subject,"Bills\n")==0)
           Bills_Count+=strtoull(Expense_Temp->amount,&end,10);
       else if(strcasecmp(Expense_Temp->subject,"Rent & Mortgage\n")==0)
           Rent_Mortgage_Count+=strtoull(Expense_Temp->amount,&end,10);
       else if(strcasecmp(Expense_Temp->subject,"Loan Payment\n")==0)
           Loan_Payment_Count+=strtoull(Expense_Temp->amount,&end,10);
       else if(strcasecmp(Expense_Temp->subject,"Education\n")==0)
           Education_Count+=strtoull(Expense_Temp->amount,&end,10);
       else if(strcasecmp(Expense_Temp->subject,"Transportation\n")==0)
           Transportation_Count+=strtoull(Expense_Temp->amount,&end,10);
       else if(strcasecmp(Expense_Temp->subject,"Clothing\n")==0)
           Clothing_Count+=strtoull(Expense_Temp->amount,&end,10);
       else if(strcasecmp(Expense_Temp->subject,"Recreation\n")==0)
           Recreation_Count+=strtoull(Expense_Temp->amount,&end,10);
       else if(strcasecmp(Expense_Temp->subject,"Charity\n")==0)
           Charity_Count+=strtoull(Expense_Temp->amount,&end,10);
       else
           Others_Count+=strtoull(Expense_Temp->amount,&end,10);
       SUM+=strtoull(Expense_Temp->amount,&end,10);
       Expense_Temp=Expense_Temp->next;
   }
   Healthcare_Share=((double)Healthcare_Count/SUM) * 100;
   Food_Share=((double)Food_Count/SUM) * 100;
   Care_Cleaning_Share=((double)Care_Cleaning_Count/SUM) * 100;
   Bills_Share=((double)Bills_Count/SUM) * 100;
   Rent_Mortgage_Share=((double)Rent_Mortgage_Count/SUM) * 100;
   Loan_Payment_Share=((double)Loan_Payment_Count/SUM) * 100;
   Education_Share=((double)Education_Count/SUM) * 100;
   Transportation_Share=((double)Transportation_Count/SUM) * 100;
   Clothing_Share=((double)Clothing_Count/SUM) * 100;
   Recreation_Share=((double)Recreation_Count/SUM) * 100;
   Charity_Share=((double)Charity_Count/SUM) * 100;
   Others_Share=((double)Others_Count/SUM) * 100;
   system("cls");
   printf("\n\n\nYour All time expense share ratio :\n\n\n-->Healthcare %24.3lf%%\n-->Food %30.3lf%%\n",Healthcare_Share,Food_Share);
   printf("-->Personal Care & Cleaning %10.3lf%%\n-->Bills %29.3lf%%\n-->Rent & Mortgage %19.3lf%%\n",Care_Cleaning_Share,Bills_Share,Rent_Mortgage_Share);
   printf("-->Loan Payment %22.3lf%%\n-->Education %25.3lf%%\n-->Transportation %20.3lf%%\n",Loan_Payment_Share,Education_Share,Transportation_Share);
   printf("-->Clothing %26.3lf%%\n-->Recreation %24.3lf%%\n-->Charity %27.3lf%%\n-->Others %28.3lf%%",Clothing_Share,Recreation_Share,Charity_Share,Others_Share);
   printf("\n\n\nPress any button to continue");
   getch();
   Return_To_Menu_For_Reports();
}


void Expense_Share_Ratio_In_Time_Period()
{
   system("cls");
   char Begin_Year[6],End_Year[6],Begin_Month[4],End_Month[4],Begin_Day[4],End_Day[4];
   char *end;
   int Expense_Date;
   long long int Healthcare_Count=0,Food_Count=0,Care_Cleaning_Count=0,Bills_Count=0,Rent_Mortgage_Count=0,Loan_Payment_Count=0,Education_Count=0;
   long long int Transportation_Count=0,Clothing_Count=0,Recreation_Count=0,Charity_Count=0,Others_Count=0,SUM=0;
   double Healthcare_Share=0,Food_Share=0,Care_Cleaning_Share=0,Bills_Share=0,Rent_Mortgage_Share=0,Loan_Payment_Share=0,Education_Share=0;
   double Transportation_Share=0,Clothing_Share=0,Recreation_Share=0,Charity_Share=0,Others_Share=0;
   struct UserExpense *head,*Expense_Temp;
   head=(struct UserExpense*)malloc(sizeof(struct UserExpense));
   head=Expense_Iteration();
   Expense_Temp=head;
   Input_Time_Period(Begin_Year,Begin_Month,Begin_Day,End_Year,End_Month,End_Day);
   while(Expense_Temp->next!=NULL)
   {
       Expense_Date=Check_Time_Period(Expense_Temp->Year,Expense_Temp->Month,Expense_Temp->Day,Begin_Year,Begin_Month,Begin_Day,End_Year,End_Month,End_Day);
       if(Expense_Date==0)
       {
           if(strcasecmp(Expense_Temp->subject,"Healthcare\n")==0)
                Healthcare_Count+=strtoull(Expense_Temp->amount,&end,10);
           else if(strcasecmp(Expense_Temp->subject,"Food\n")==0)
                Food_Count+=strtoull(Expense_Temp->amount,&end,10);
           else if(strcasecmp(Expense_Temp->subject,"Personal Care & Cleaning\n")==0)
                Care_Cleaning_Count+=strtoull(Expense_Temp->amount,&end,10);
           else if(strcasecmp(Expense_Temp->subject,"Bills\n")==0)
                Bills_Count+=strtoull(Expense_Temp->amount,&end,10);
           else if(strcasecmp(Expense_Temp->subject,"Rent & Mortgage\n")==0)
                Rent_Mortgage_Count+=strtoull(Expense_Temp->amount,&end,10);
           else if(strcasecmp(Expense_Temp->subject,"Loan Payment\n")==0)
                Loan_Payment_Count+=strtoull(Expense_Temp->amount,&end,10);
           else if(strcasecmp(Expense_Temp->subject,"Education\n")==0)
                Education_Count+=strtoull(Expense_Temp->amount,&end,10);
           else if(strcasecmp(Expense_Temp->subject,"Transportation\n")==0)
                Transportation_Count+=strtoull(Expense_Temp->amount,&end,10);
           else if(strcasecmp(Expense_Temp->subject,"Clothing\n")==0)
                Clothing_Count+=strtoull(Expense_Temp->amount,&end,10);
           else if(strcasecmp(Expense_Temp->subject,"Recreation\n")==0)
                Recreation_Count+=strtoull(Expense_Temp->amount,&end,10);
           else if(strcasecmp(Expense_Temp->subject,"Charity\n")==0)
                Charity_Count+=strtoull(Expense_Temp->amount,&end,10);
           else
                Others_Count+=strtoull(Expense_Temp->amount,&end,10);
           SUM+=strtoull(Expense_Temp->amount,&end,10);
       }
       Expense_Temp=Expense_Temp->next;
   }
   Healthcare_Share=((double)Healthcare_Count/SUM) * 100;
   Food_Share=((double)Food_Count/SUM) * 100;
   Care_Cleaning_Share=((double)Care_Cleaning_Count/SUM) * 100;
   Bills_Share=((double)Bills_Count/SUM) * 100;
   Rent_Mortgage_Share=((double)Rent_Mortgage_Count/SUM) * 100;
   Loan_Payment_Share=((double)Loan_Payment_Count/SUM) * 100;
   Education_Share=((double)Education_Count/SUM) * 100;
   Transportation_Share=((double)Transportation_Count/SUM) * 100;
   Clothing_Share=((double)Clothing_Count/SUM) * 100;
   Recreation_Share=((double)Recreation_Count/SUM) * 100;
   Charity_Share=((double)Charity_Count/SUM) * 100;
   Others_Share=((double)Others_Count/SUM) * 100;
   system("cls");
   printf("\n\n\nYour expense share ratio between %s/%s/%s and %s/%s/%s is :",Begin_Year,Begin_Month,Begin_Day,End_Year,End_Month,End_Day);
   printf("\n\n\n-->Healthcare %24.3lf%%\n-->Food %30.3lf%%\n",Healthcare_Share,Food_Share);
   printf("-->Personal Care & Cleaning %10.3lf%%\n-->Bills %29.3lf%%\n-->Rent & Mortgage %19.3lf%%\n",Care_Cleaning_Share,Bills_Share,Rent_Mortgage_Share);
   printf("-->Loan Payment %22.3lf%%\n-->Education %25.3lf%%\n-->Transportation %20.3lf%%\n",Loan_Payment_Share,Education_Share,Transportation_Share);
   printf("-->Clothing %26.3lf%%\n-->Recreation %24.3lf%%\n-->Charity %27.3lf%%\n-->Others %28.3lf%%",Clothing_Share,Recreation_Share,Charity_Share,Others_Share);
   printf("\n\n\nPress any button to continue");
   getch();
   Return_To_Menu_For_Reports();
}

void Detailed_Expense_In_Time_Period()
{
    system("cls");
    char Begin_Year[6],End_Year[6],Begin_Month[4],End_Month[4],Begin_Day[4],End_Day[4];
    char *end;
    int Expense_Date,count=1;
    struct UserExpense *head,*Expense_Temp;
    head=(struct UserExpense*)malloc(sizeof(struct UserExpense));
    head=Expense_Iteration();
    Expense_Temp=head;
    Input_Time_Period(Begin_Year,Begin_Month,Begin_Day,End_Year,End_Month,End_Day);
    system("cls");
    while(Expense_Temp->next!=NULL)
    {
        Expense_Date=Check_Time_Period(Expense_Temp->Year,Expense_Temp->Month,Expense_Temp->Day,Begin_Year,Begin_Month,Begin_Day,End_Year,End_Month,End_Day);
        if(Expense_Date==0)
        {
            printf("EXPENSE #%d\n\n",count);
            Expense_Temp->amount[strlen(Expense_Temp->amount)-1]='\0';
            printf("Amount = ",Expense_Temp->amount);
            puts(Expense_Temp->amount);
            Expense_Temp->subject[strlen(Expense_Temp->subject)-1]='\0';
            printf("Subject : ");
            puts(Expense_Temp->subject);
            Expense_Temp->Year[strlen(Expense_Temp->Year)-1]='\0';
            Expense_Temp->Month[strlen(Expense_Temp->Month)-1]='\0';
            printf("Date : %s/%s/%s",Expense_Temp->Year,Expense_Temp->Month,Expense_Temp->Day);
            Expense_Temp->description[strlen(Expense_Temp->description)-1]='\0';
            printf("Description : ");
            if(strcmp(Expense_Temp->description,"")==0)
                printf("None");
            else
                puts(Expense_Temp->description);
            count++;
            printf("\n\n\n\n\n");
        }
        Expense_Temp=Expense_Temp->next;
    }
    printf("\n\n\nPress enter to continue");
    getch();
    Return_To_Menu_For_Reports();
}

void Highest_Expense_In_Time_Period()
{
    system("cls");
    char Begin_Year[6],End_Year[6],Begin_Month[4],End_Month[4],Begin_Day[4],End_Day[4];
    char *end;
    int Expense_Date;
    long long int Highest_Expense=0;
    struct UserExpense *head,*Expense_Temp;
    head=(struct UserExpense*)malloc(sizeof(struct UserExpense));
    head=Expense_Iteration();
    Expense_Temp=head;
    Input_Time_Period(Begin_Year,Begin_Month,Begin_Day,End_Year,End_Month,End_Day);
    while(Expense_Temp->next!=NULL)
    {
        Expense_Date=Check_Time_Period(Expense_Temp->Year,Expense_Temp->Month,Expense_Temp->Day,Begin_Year,Begin_Month,Begin_Day,End_Year,End_Month,End_Day);
        if(Expense_Date==0)
        {
            if(Highest_Expense==0)
            {
                Highest_Expense=strtoull(Expense_Temp->amount,&end,10);
                Expense_Temp=Expense_Temp->next;
                continue;
            }
            if(strtoull(Expense_Temp,&end,10)>Highest_Expense)
                Highest_Expense=strtoull(Expense_Temp,&end,10);
        }
        Expense_Temp=Expense_Temp->next;
    }
    system("cls");
    if(Highest_Expense==0)
        printf("\n\n\nYou have not submitted any expense in this time period");
    else
        printf("\n\n\nYour highest expense between %s/%s/%s and %s/%s/%s\nis %lld",Begin_Year,Begin_Month,Begin_Day,End_Year,End_Month,End_Day,Highest_Expense);
    printf(" Iranian RIALS.\n\n\nPress any button to continue");
    getch();
    Return_To_Menu_For_Reports();
}

void Expense_Search_In_Description()
{
    system("cls");
    struct UserExpense *head,*Expense_Temp;
    head=(struct UserExpense*)malloc(sizeof(struct UserExpense));
    head=Expense_Iteration();
    Expense_Temp=head;
    char Word_In_Description[100];
    int count=1;
    printf("Please enter a word or phrase: ");
    gets(Word_In_Description);
    system("cls");
    while(Expense_Temp->next!=NULL)
    {
        if(StrStrIA(Expense_Temp->description,Word_In_Description)!=NULL)
        {
            printf("EXPENSE #%d\n\n",count);
            Expense_Temp->amount[strlen(Expense_Temp->amount)-1]='\0';
            printf("Amount = ",Expense_Temp->amount);
            puts(Expense_Temp->amount);
            Expense_Temp->subject[strlen(Expense_Temp->subject)-1]='\0';
            printf("Subject : ");
            puts(Expense_Temp->subject);
            Expense_Temp->Year[strlen(Expense_Temp->Year)-1]='\0';
            Expense_Temp->Month[strlen(Expense_Temp->Month)-1]='\0';
            printf("Date : %s/%s/%s",Expense_Temp->Year,Expense_Temp->Month,Expense_Temp->Day);
            Expense_Temp->description[strlen(Expense_Temp->description)-1]='\0';
            printf("Description : ");
            if(strcmp(Expense_Temp->description,"")==0)
                printf("None");
            else
                puts(Expense_Temp->description);
            count++;
            printf("\n\n\n\n\n");
        }
        Expense_Temp=Expense_Temp->next;
    }
    printf("\n\n\nPress any button to continue");
    getch();
    Return_To_Menu_For_Reports();
}

void Settings()
{
    system("cls");
    char Choose_Menu;
    int temp;
    printf("----- SETTINGS MENU -----\n\n\n1) Change user name\n2) Change password\n3) Change phone number\n4) Change Email address\n\n\n");
    do
    {
        Choose_Menu=getch();
        temp=Choose_Menu-'0';
    }while(temp<1 || temp>4);
    switch(temp)
    {
        case 1:
        {
            Change_Username();
            break;
        }
        case 2:
        {
            Change_Password();
            break;
        }
        case 3:
        {
            Change_Phone_Number();
            break;
        }
        default:
            Change_Email();
    }
}

void Change_Email()
{
    system("cls");
    int Int_Temp=0;
    char New_Email[50],Temp_Username[30];
    struct UserProfile *head,*temp;
    head=(struct UserProfile*)malloc(sizeof(struct UserProfile));
    head=Profile_Iteration();
    temp=head;
    FILE *profile;
    printf("\n\n\nEnter new Email address: ");
    gets(New_Email);
    do
      {
        Int_Temp=Email_Check(New_Email);
        if(Int_Temp==-1)
        {
            printf("\n\nEmail address is not correct.\nEnter a valid Email address: ");
            gets(New_Email);
        }
        if(Int_Temp==-2)
        {
            printf("\n\nThis Email address is used by another user.\nEnter another Email address: ");
            gets(New_Email);
        }
    }while(Int_Temp!=0);
    strcat(New_Email,"\n");
    strcpy(Temp_Username,g_username);
    strcat(Temp_Username,"\n");
    profile=fopen("profile.txt","w");
    while(temp!=NULL)
    {
        fputs(temp->name,profile);
        fputs(temp->family,profile);
        fputs(temp->user_name,profile);
        fputs(temp->password,profile);
        fputs(temp->Melli_Num,profile);
        fputs(temp->Phone_Num,profile);
        if(strcmp(Temp_Username,temp->user_name)==0)
            fputs(New_Email,profile);
        else
            fputs(temp->Email,profile);
        temp=temp->next;
    }
    fclose(profile);
    Return_To_Menu_For_Settings();
}



void Change_Phone_Number()
{
    system("cls");
    int Int_Temp=0;
    char New_Phone_Num[20],Temp_Username[30];
    struct UserProfile *head,*temp;
    head=(struct UserProfile*)malloc(sizeof(struct UserProfile));
    head=Profile_Iteration();
    temp=head;
    FILE *profile;
    printf("\n\n\nEnter new phone number: ");
    gets(New_Phone_Num);
    do
      {
        Int_Temp=Phone_Num_Check(New_Phone_Num);
        if(Int_Temp==-1)
        {
            printf("\n\nPhone number is not correct.\nEnter a valid phone number: ");
            gets(New_Phone_Num);
        }
        if(Int_Temp==-2)
        {
            printf("\n\nThis Phone number is used by another user.\nEnter another phone number: ");
            gets(New_Phone_Num);
        }
    }while(Int_Temp!=0);
    strcat(New_Phone_Num,"\n");
    strcpy(Temp_Username,g_username);
    strcat(Temp_Username,"\n");
    profile=fopen("profile.txt","w");
    while(temp!=NULL)
    {
        fputs(temp->name,profile);
        fputs(temp->family,profile);
        fputs(temp->user_name,profile);
        fputs(temp->password,profile);
        fputs(temp->Melli_Num,profile);
        if(strcmp(Temp_Username,temp->user_name)==0)
            fputs(New_Phone_Num,profile);
        else
            fputs(temp->Phone_Num,profile);
        fputs(temp->Email,profile);
        temp=temp->next;
    }
    fclose(profile);
    Return_To_Menu_For_Settings();
}


void Change_Password()
{
    system("cls");
    int Int_Temp=0;
    char New_Password[30],Old_Password[30],Confirm_Old_Password[30],Repeat_New_Password[30],Temp_Username[30],Temp_Password[30];
    struct UserProfile *head,*temp;
    head=(struct UserProfile*)malloc(sizeof(struct UserProfile));
    head=Profile_Iteration();
    temp=head;
    FILE *profile;
    printf("\n\n\nEnter old password: ");
    Enter_Pass(Old_Password);
    strcat(Old_Password,"\n");
    strcpy(Temp_Username,g_username);
    strcat(Temp_Username,"\n");
    do
    {
        while(temp->next!=NULL)
        {
            if(strcmp(Temp_Username,temp->user_name)==0)
                strcpy(Confirm_Old_Password,temp->password);
            temp=temp->next;
        }
        temp=head;
        if(strcmp(Old_Password,Confirm_Old_Password)!=0)
        {
            printf("\nPassword is not correct.\nPlease Enter the old password: ");
            Enter_Pass(Old_Password);
            strcat(Old_Password,"\n");
        }
    }while(strcmp(Old_Password,Confirm_Old_Password)!=0);
    printf("\n\nEnter new password: ");
    Enter_Pass(New_Password);
    do
    {
        Int_Temp=Password_Check(New_Password);
        if(Int_Temp==-1)
        {
            printf("\n\nYour password is too short.\nEnter a longer password: ");
            Enter_Pass(New_Password);
        }
        if(Int_Temp==-2)
        {
            printf("\n\nYour password is too long.\nEnter a shorter password: ");
            Enter_Pass(New_Password);
        }
        if(Int_Temp==-3)
        {
            printf("\n\nYour password is weak\nEnter a stronger password (according to notes): ");
            Enter_Pass(New_Password);
        }
    }while(Int_Temp!=0);
    printf("\nRepeat new password: ");
    Enter_Pass(Repeat_New_Password);
    do
    {
       if(strcmp(New_Password,Repeat_New_Password)!=0)
       {
           printf("\nPassword is not the same.\nPlease Enter the same password: ");
           Enter_Pass(Repeat_New_Password);
       }
    }while(strcmp(New_Password,Repeat_New_Password)!=0);
    strcat(New_Password,"\n");
    strcpy(Temp_Username,g_username);
    strcat(Temp_Username,"\n");
    profile=fopen("profile.txt","w");
    while(temp!=NULL)
    {
        fputs(temp->name,profile);
        fputs(temp->family,profile);
        fputs(temp->user_name,profile);
        if(strcmp(Temp_Username,temp->user_name)==0)
            fputs(New_Password,profile);
        else
            fputs(temp->password,profile);
        fputs(temp->Melli_Num,profile);
        fputs(temp->Phone_Num,profile);
        fputs(temp->Email,profile);
        temp=temp->next;
    }
    fclose(profile);
    Return_To_Menu_For_Settings();
}


void Change_Username()
{
    system("cls");
    char New_Username[30],Temp_Username[30],Old_Directory[80],New_Directory[80],Int_Temp=0;
    struct UserProfile *head,*temp;
    head=(struct UserProfile*)malloc(sizeof(struct UserProfile));
    head=Profile_Iteration();
    temp=head;
    FILE *profile;
    printf("\n\n\nEnter new user name: ");
    gets(New_Username);
    do
    {
        Int_Temp=User_Name_Check(New_Username);
        if(Int_Temp==-1)
        {
            printf("\n\nUser name is too short.\nEnter a longer user name: ");
            gets(New_Username);
        }
        else if(Int_Temp==-2)
        {
            printf("\n\nUser name is too long.\nEnter a shorter user name: ");
            gets(New_Username);
        }
        else if(Int_Temp==-3)
        {
            printf("\n\nThere's another user with this user name.\nEnter another user name: ");
            gets(New_Username);
        }
    }while(Int_Temp!=0);
    strcpy(Old_Directory,"F:\\\\C_Programs\\\\Final_Project\\\\incomes\\\\");
    strcat(Old_Directory,g_username);
    strcat(Old_Directory,".txt");
    strcpy(New_Directory,"F:\\\\C_Programs\\\\Final_Project\\\\incomes\\\\");
    strcat(New_Directory,New_Username);
    strcat(New_Directory,".txt");
    rename(Old_Directory,New_Directory);
    strcpy(Old_Directory,"F:\\\\C_Programs\\\\Final_Project\\\\expenses\\\\");
    strcat(Old_Directory,g_username);
    strcat(Old_Directory,".txt");
    strcpy(New_Directory,"F:\\\\C_Programs\\\\Final_Project\\\\expenses\\\\");
    strcat(New_Directory,New_Username);
    strcat(New_Directory,".txt");
    rename(Old_Directory,New_Directory);
    strcat(New_Username,"\n");
    strcpy(Temp_Username,g_username);
    strcat(Temp_Username,"\n");
    profile=fopen("profile.txt","w");
    while(temp!=NULL)
    {
        fputs(temp->name,profile);
        fputs(temp->family,profile);
        if(strcmp(Temp_Username,temp->user_name)==0)
            fputs(New_Username,profile);
        else
            fputs(temp->user_name,profile);
        fputs(temp->password,profile);
        fputs(temp->Melli_Num,profile);
        fputs(temp->Phone_Num,profile);
        fputs(temp->Email,profile);
        temp=temp->next;
    }
    fclose(profile);
    Return_To_Menu_For_Settings();
}


 int Profile_Iteration()
{
    struct UserProfile *head,*user,*temp;
    FILE *profile;
    profile=fopen("profile.txt","r");
    do
    {
        head=(struct UserProfile*)malloc(sizeof(struct UserProfile));
    }while(head==NULL);
    fgets(head->name,sizeof head->name,profile);
    fgets(head->family,sizeof head->family,profile);
    fgets(head->user_name,sizeof head->user_name,profile);
    fgets(head->password,sizeof head->password,profile);
    fgets(head->Melli_Num,sizeof head->Melli_Num,profile);
    fgets(head->Phone_Num,sizeof head->Phone_Num ,profile);
    fgets(head->Email,sizeof head->Email,profile);
    head->next=NULL;
    temp=head;
    while(feof(profile)==0)
    {
        do
        {
            user=(struct UserProfile*)malloc(sizeof(struct UserProfile));
        }while(user==NULL);
        fgets(user->name,sizeof user->name,profile);
        fgets(user->family,sizeof user->family,profile);
        fgets(user->user_name,sizeof user->user_name,profile);
        fgets(user->password,sizeof user->password,profile);
        fgets(user->Melli_Num,sizeof head->Melli_Num,profile);
        fgets(user->Phone_Num,sizeof user->Phone_Num,profile);
        fgets(user->Email,sizeof head->Email,profile);
        user->next=NULL;
        temp->next=user;
        temp=user;
    }
    fclose(profile);
    return head;
}

int Income_Iteration()
{
    struct UserIncome *head,*income,*temp;
    char Incomes_Directory[70];
    FILE *Incomes;
    strcpy(Incomes_Directory,"F:\\\\C_Programs\\\\Final_Project\\\\incomes\\\\");
    strcat(Incomes_Directory,g_username);
    strcat(Incomes_Directory,".txt");
    Incomes=fopen(Incomes_Directory,"r");
    do
    {
        head=(struct UserIncome*)malloc(sizeof(struct UserIncome));
    }while(head==NULL);
    fgets(head->amount,sizeof head->amount,Incomes);
    fgets(head->source,sizeof head->source,Incomes);
    fgets(head->Year,sizeof head->Year,Incomes);
    fgets(head->Month,sizeof head->Month,Incomes);
    fgets(head->Day,sizeof head->Day,Incomes);
    fgets(head->description,sizeof head->description,Incomes);
    head->next=NULL;
    temp=head;
    while(feof(Incomes)==0)
    {
        do
        {
            income=(struct UserIncome*)malloc(sizeof(struct UserIncome));
        }while(income==NULL);
        fgets(income->amount,sizeof income->amount,Incomes);
        fgets(income->source,sizeof income->source,Incomes);
        fgets(income->Year,sizeof income->Year,Incomes);
        fgets(income->Month,sizeof income->Month,Incomes);
        fgets(income->Day,sizeof income->Day,Incomes);
        fgets(income->description,sizeof income->description,Incomes);
        income->next=NULL;
        temp->next=income;
        temp=income;
    }
    fclose(Incomes);
    return head;
}


int Expense_Iteration()
{
    struct UserExpense *head,*expense,*temp;
    char Expense_Directory[70];
    FILE *Expenses;
    strcpy(Expense_Directory,"F:\\\\C_Programs\\\\Final_Project\\\\expenses\\\\");
    strcat(Expense_Directory,g_username);
    strcat(Expense_Directory,".txt");
    Expenses=fopen(Expense_Directory,"r");
    do
    {
        head=(struct UserExpense*)malloc(sizeof(struct UserExpense));
    }while(head==NULL);
    fgets(head->amount,sizeof head->amount,Expenses);
    fgets(head->subject,sizeof head->subject,Expenses);
    fgets(head->Year,sizeof head->Year,Expenses);
    fgets(head->Month,sizeof head->Month,Expenses);
    fgets(head->Day,sizeof head->Day,Expenses);
    fgets(head->description,sizeof head->description,Expenses);
    head->next=NULL;
    temp=head;
    while(feof(Expenses)==0)
    {
        do
        {
            expense=(struct UserIncome*)malloc(sizeof(struct UserIncome));
        }while(expense==NULL);
        fgets(expense->amount,sizeof expense->amount,Expenses);
        fgets(expense->subject,sizeof expense->subject,Expenses);
        fgets(expense->Year,sizeof expense->Year,Expenses);
        fgets(expense->Month,sizeof expense->Month,Expenses);
        fgets(expense->Day,sizeof expense->Day,Expenses);
        fgets(expense->description,sizeof expense->description,Expenses);
        expense->next=NULL;
        temp->next=expense;
        temp=expense;
    }
    fclose(Expenses);
    return head;
}


int Check_Time_Period(int Year[],int Month[],int Day[],int Begin_Year[],int Begin_Month[],int Begin_Day[],int End_Year[],int End_Month[],int End_Day[])
{
    char *end;
    if(strtoul(Year,&end,10)>=strtoul(Begin_Year,&end,10)  &&   strtoul(Year,&end,10)<=strtoul(End_Year,&end,10))
       {
            if(strtoul(Year,&end,10)==strtoul(Begin_Year,&end,10))
            {
                if(strtoul(Month,&end,10)<strtoul(Begin_Month,&end,10))
                    return -1;//Income not in time period
                if(strtoul(Month,&end,10)==strtoul(Begin_Month,&end,10))
                    if(strtoul(Day,&end,10)<strtoul(Begin_Day,&end,10))
                        return -1;
            }
            if(strtoul(Year,&end,10)==strtoul(End_Year,&end,10))
            {
                if(strtoul(Month,&end,10)>strtoul(End_Month,&end,10))
                    return -1;
                if(strtoul(Month,&end,10)==strtoul(End_Month,&end,10))
                    if(strtoul(Day,&end,10)>strtoul(End_Day,&end,10))
                        return -1;
            }
        }
    else
        return -1;
    return 0;//income in time period
}

void Input_Time_Period(int Begin_Year[],int Begin_Month[],int Begin_Day[],int End_Year[],int End_Month[],int End_Day[])
{
   printf("Enter beginning year in YYYY format: ");
   gets(Begin_Year);
   printf("Enter beginning month in MM format (without zero): ");
   gets(Begin_Month);
   printf("Enter beginning day in DD format (without zero): ");
   gets(Begin_Day);
   printf("\n\n\nEnter ending year in YYYY format: ");
   gets(End_Year);
   printf("Enter ending month in MM format (without zero): ");
   gets(End_Month);
   printf("Enter ending day in DD format (without zero): ");
   gets(End_Day);
}

void Return_To_Menu_For_Settings()
{
    int temp;
    char Menu_Choose;
    system("cls");
    printf("\n\n1) Return to main menu\n2) Return to settings\n3) Exit");
    do
    {
        Menu_Choose=getch();
        temp=Menu_Choose-'0';
    }while(temp<1 || temp>3);
    if(Menu_Choose=='1')
        Main_Menu();
    else if(Menu_Choose=='2')
        Settings();
         else
             Exit();
}

void Return_To_Menu_For_Reports()
{
    int temp;
    char Menu_Choose;
    system("cls");
    printf("\n\n1) Return to main menu\n2) Return to reports menu\n3) Exit");
    do
    {
        Menu_Choose=getch();
        temp=Menu_Choose-'0';
    }while(temp<1 || temp>3);
    if(Menu_Choose=='1')
        Main_Menu();
    else if(Menu_Choose=='2')
        Reports();
         else
             Exit();
}

void Choose_Source_Of_Income(int Source_Of_Income[])
{
    char Choose_Source;
    int temp;
    printf("\n\nPlease choose source of income :\n\n1) Salary\n2) Pocket Money\n3) Government Aid\n4) University Grant\n5) Bank Interest\n6) Loan\n7) Other\n\n\n");
    do
    {
        Choose_Source=getch();
        temp=Choose_Source - '0';
    }while(temp<1 || temp>7);

    switch(Choose_Source)
    {
        case '1':
        {
            strcpy(Source_Of_Income,"Salary\n");
            break;
        }
        case '2':
        {
            strcpy(Source_Of_Income,"Pocket Money\n");
            break;
        }
        case '3':
        {
            strcpy(Source_Of_Income,"Government Aid\n");
            break;
        }
        case '4':
        {
            strcpy(Source_Of_Income,"University Grant\n");
            break;
        }
        case '5':
        {
            strcpy(Source_Of_Income,"Bank Interest\n");
            break;
        }
        case '6':
        {
            strcpy(Source_Of_Income,"Loan\n");
            break;
        }
        default:
        {
            printf("\n\nPlease enter source of Income: ");
            gets(Source_Of_Income);
            strcat(Source_Of_Income,"\n");
        }
   }
}

void Choose_Subject_Of_Expense(int Subject_Of_Expense[])
{
    char Choose_Subject;
    int temp;
    char *end;
    printf("\n\nPlease choose subject of expense:\n\n1) Healthcare\n2) Daily expenses\n3) Monthly expenses\n");
    printf("4) Education\n5) Clothing\n6) Recreation\n7) Charity\n8) Others\n\n\n");
    do
    {
        Choose_Subject=getch();
        temp=Choose_Subject - '0';
    }while(temp<1 || temp>8);

    switch(temp)
    {
        case 1:
        {
            strcpy(Subject_Of_Expense,"Healthcare\n");
            break;
        }
        case 2:
        {
            system("cls");
            printf("\n\n\n1) Food\n2) Personal Care & Cleaning\n3) Transportation\n\n\n");
            do
            {
                Choose_Subject=getch();
                temp=Choose_Subject - '0';
            }while(temp<1 || temp>3);
            if(temp==1)
                strcpy(Subject_Of_Expense,"Food\n");
            else if(temp==2)
                strcpy(Subject_Of_Expense,"Personal Care & Cleaning\n");
            else
                strcpy(Subject_Of_Expense,"Transportation\n");
            break;
        }
        case 3:
        {
            system("cls");
            printf("\n\n\n1) Bills\n2) Rent & Mortgage\n3) Loan Payment\n\n\n");
            do
            {
                Choose_Subject=getch();
                temp=Choose_Subject - '0';
            }while(temp<1 || temp>3);
            if(temp==1)
                strcpy(Subject_Of_Expense,"Bills\n");
            else if(temp==2)
                strcpy(Subject_Of_Expense,"Rent & Mortgage\n");
            else
                strcpy(Subject_Of_Expense,"Loan Payment\n");
            break;
        }
        case 4:
        {
            strcpy(Subject_Of_Expense,"Education\n");
            break;
        }
        case 5:
        {
            strcpy(Subject_Of_Expense,"Clothing\n");
            break;
        }
        case 6:
        {
            strcpy(Subject_Of_Expense,"Recreation\n");
            break;
        }
        case 7:
        {
            strcpy(Subject_Of_Expense,"Charity\n");
            break;
        }
        default:
        {
            printf("Please enter subject of expense: ");
            gets(Subject_Of_Expense);
            strcat(Subject_Of_Expense,"\n");
        }
    }
}


