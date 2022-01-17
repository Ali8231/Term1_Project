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
   char source[35];
   char Year[7];
   char Month[5];
   char Day[5];
   char description[110];
   struct UserExpense *next;
};


char g_username[20];

void SubmitIncome();
void EntranceMenu();
void Signup();
void Login();
int UserNameSearch();
int LoginPassCheck(int password[]);
void MainMenu();
int ProfileIteration();
void EnterPass(char *password);
void SubmitExpense();
void Reports();
void InputTimePeriod(int BeginYear[],int BeginMonth[],int BeginDay[],int EndYear[],int EndMonth[],int EndDay[]);
int CheckTimePeriod(int Year[],int Month[],int Day[],int BeginYear[],int BeginMonth[],int BeginDay[],int EndYear[],int EndMonth[],int EndDay[]);


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
    FILE *profile,*UserIncome,*UserExpense;
    profile=fopen("profile.txt","a");
    printf("-----SIGN UP PAGE-----\n\n\nEnter your first name: ");
    rewind(profile);
    gets(name);
    strcat(name,"\n");
    printf("Enter your last name: ");
    gets(family);
    strcat(family,"\n");
    printf("Enter user name: ");
    gets(user_name);
    //do
    //{
    //    UserNameCheck(username);
    //    if(UserNameCheck==0)
    //    {
    //        printf("There is a user with this username.\nEnter another user name: ");
    //        gets(username);
    //    }
    //}while(UserNameCheck==0);
    printf("\n");
    strcat(user_name,"\n");
    printf("\n\nNotes about password:\n---Your password must be between 8 and 20 characters\n---");
    printf("Your password must include uppercase and lowercase letters,at least one\n number and one special character(@,*,#,...)\n\nEnter password: ");
    Enter_Pass(password);
    //do
    //{
    //    PassCheck(password);
    //    if(PassCheck==0)
    //    {
    //        printf("Your password isn't strong.\nPlease read the notes again and enter an strong password: ");
    //        gets(password);
    //    }
    //}while(PassCheck==0);
    printf("\nEnter the password again: ");
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
    //do
    //  {
    //    MelliNumCheck(MelliNum);
    //    if(MelliNumCheck==0)
    //    {
    //        printf("Melli number is not correct.\nEnter a correct Melli number: ");
    //        gets(MelliNum);
    //    }
    //}while(MelliNumCheck==0);
    strcat(Melli_Num,"\n");
    printf("Enter your phone number: ");
    gets(Phone_Num);
    //do
    //  {
    //    PhoneNumCheck(PhoneNum);
    //    if(PhoneNumCheck==0)
    //    {
    //        printf("Phone number is not correct.\nEnter a correct phone number: ");
    //        gets(PhoneNum);
    //    }
    //}while(PhoneNumCheck==0);
    strcat(Phone_Num,"\n");
    printf("Enter your Email address: ");
    gets(Email);
    //do
    //  {
    //    EmailCheck(Email);
    //    if(EmailCheck==0)
    //    {
    //        printf("Email address is not correct.\nEnter a correct Email address: ");
    //        gets(Email);
    //    }
    //}while(EmailCheck==0);
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

void Enter_Pass(char *password)
{
    char temp;
    int i=0;
    while((temp=getch())!=13)//until user presses enter
    {
        if(i<0)
            i++;
        if(temp==8)//if user presses backspace
        {
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
    while(temp->next!=NULL)
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
    strcat(temp_Username,"\n");//in file last character of each element there is a \n to go to next line.concatenation is to match two strings for strcmp
    strcat(temp_Password,"\n");
    while(temp->next!=NULL)//This is because all of my linked lists last nodes are always empty for unknown reasons.so I do not read the last nodes
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
    printf("\n\n1) Healthcare\n2) Food\n3) Bills\n4) Education\n5) Transportation\n6) Clothing\n7) Charity\n8) Recreation\n9) Other\n");
    do
    {
        Choose_Subject=getch();
        temp=Choose_Subject - '0';
    }while(temp<1 || temp>9);

    switch(Choose_Subject)
    {
        case '1':
        {
            strcpy(Subject_Of_Expense,"Healthcare\n");
            break;
        }
        case '2':
        {
            strcpy(Subject_Of_Expense,"Food\n");
            break;
        }
        case '3':
        {
            strcpy(Subject_Of_Expense,"Bills\n");
            break;
        }
        case '4':
        {
            strcpy(Subject_Of_Expense,"Education\n");
            break;
        }
        case '5':
        {
            strcpy(Subject_Of_Expense,"Transportation\n");
            break;
        }
        case '6':
        {
            strcpy(Subject_Of_Expense,"Clothing\n");
            break;
        }
        case '7':
        {
            strcpy(Subject_Of_Expense,"Charity\n");
            break;
        }
        case '8':
        {
            strcpy(Subject_Of_Expense,"Recreation\n");
            break;
        }
        default:
        {
            printf("Please enter subject of expenditure: ");
            gets(Subject_Of_Expense);
            strcat(Subject_Of_Expense,"\n");
        }
    }
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
    printf("\n\n\nPress any button to continue");
    getch();//waits for user to press a key
    Return_To_Menu();
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
    Return_To_Menu();
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
   Return_To_Menu();//at the end user can go back to reports or main menu or exit
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
   printf("\n\nYour All time income share ratio :\n\n\nSalary %20.3Lf%%\nPocket Money %14.3Lf%%\nUniversity Grant %10.3Lf%%\n",Salary_Share,Pocket_Share,Grant_Share);
   printf("Government Aid %12.3Lf%%\nLoan %22.3Lf%%\nBank Interest %13.3Lf%%\nOther Incomes %13.3Lf%%",Gov_Aid_Share,Loan_Share,Interest_Share,Others_Share);
   printf("\n\n\nPress any button to continue");
   getch();
   Return_To_Menu();
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
   printf("\n\n\nYour total income from %s between %s/%s/%s and %s/%s/%s\nis %lld Iranian RIALS.",Source_Of_Income,Begin_Year,Begin_Month,Begin_Day,End_Year,End_Month,End_Day,Income_Count);
   printf("\n\n\nPress any button to continue");
   getch();
   Return_To_Menu();
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
   printf("\n\n\nYour total income between %s/%s/%s and %s/%s/%s\nis %lld Iranian RIALS.",Begin_Year,Begin_Month,Begin_Day,End_Year,End_Month,End_Day,Income_Count);
   printf("\n\n\nPress any button to continue");
   getch();
   Return_To_Menu();
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
        if(atoi(Income_Temp->Year)==atoi(Year))
            Income_Count+=strtoull(Income_Temp->amount,&end,10);
        Income_Temp=Income_Temp->next;
    }
    printf("Your income in %s is %lld\n\nPress any button to continue",Year,Income_Count);
    getch();
    Return_To_Menu();
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
    Return_To_Menu();
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
    fgets(head->source,sizeof head->source,Expenses);
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
        fgets(expense->source,sizeof expense->source,Expenses);
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

void Return_To_Menu()
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
    printf("\n\nPlease choose source of income :\n\n1) Salary\n2) Pocket Money\n3) Government Aid\n4) University Grant\n5) Bank Interest\n6) Loan\n7) Other\n");
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


