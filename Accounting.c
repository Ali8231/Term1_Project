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
    char MelliNum[20];
    char PhoneNum[20];
    char Email[50];
    struct Userprofile *next;
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


char username[20];

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
    EntranceMenu();
}

void EntranceMenu()
{
    system("cls");
    char EntranceMenuChoice;
    int temp;
    printf("-----  ENTRANCE MENU  -----\n\n\n1) Signup\n2) Login\n3) Exit\n");
    do
    {
        EntranceMenuChoice=getch();
        temp=EntranceMenuChoice - '0';
    }while(temp<1 || temp>3);
    if(EntranceMenuChoice=='1')
        Signup();
    else if(EntranceMenuChoice=='2')
        Login();
         else
             Exit();
}

void Exit()
{
    system("cls");
    printf("Thank you for using this program\nHope to see you again soon!");
    sleep(2);
    exit(1);
}

void Signup()
{
    system("cls");
    char name[20],family[25],password[21],ConfirmPass[21],MelliNum[12],PhoneNum[13],Email[40];
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
    gets(username);
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
    strcat(username,"\n");
    printf("\n\nNotes about password:\n---Your password must be between 8 and 20 characters\n---Your password must include uppercase and lowercase letters,at least one\n number and one special character(@,*,#,...)\n\nEnter password: ");
    EnterPass(password);
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
    EnterPass(ConfirmPass);
    do
    {
       if(strcmp(password,ConfirmPass)!=0)
       {
           printf("\nPassword is not the same.\nPlease Enter the same password: ");
           EnterPass(ConfirmPass);
       }
    }while(strcmp(password,ConfirmPass)!=0);
    strcat(password,"\n");
    printf("\nEnter your Melli number: ");
    gets(MelliNum);
    //do
    //  {
    //    MelliNumCheck(MelliNum);
    //    if(MelliNumCheck==0)
    //    {
    //        printf("Melli number is not correct.\nEnter a correct Melli number: ");
    //        gets(MelliNum);
    //    }
    //}while(MelliNumCheck==0);
    strcat(MelliNum,"\n");
    printf("Enter your phone number: ");
    gets(PhoneNum);
    //do
    //  {
    //    PhoneNumCheck(PhoneNum);
    //    if(PhoneNumCheck==0)
    //    {
    //        printf("Phone number is not correct.\nEnter a correct phone number: ");
    //        gets(PhoneNum);
    //    }
    //}while(PhoneNumCheck==0);
    strcat(PhoneNum,"\n");
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
    fputs(username,profile);
    fputs(password,profile);
    fputs(MelliNum,profile);
    fputs(PhoneNum,profile);
    fputs(Email,profile);
    fclose(profile);
    system("cls");
    printf("  User added Successfully");
    sleep(1);
    EntranceMenu();
}

void EnterPass(char *password)
{
    char temp;
    int i=0;
    while((temp=getch())!=13)
    {
        if(i<0)
            i++;
        if(temp==8)
        {
            printf("\b \b");
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
    int UserNameFound,PassFound;
    char password[21];
    system("cls");
    printf("-----LOGIN PAGE-----\n\n\nEnter your user name: ");
    gets(username);
    do
    {
        UserNameFound=UserNameSearch();
        if(UserNameFound==-1)
        {
            printf("\nUser name was not found.\nPlease enter your user name again: ");
            gets(username);
        }
    }while(UserNameFound==-1);
    printf("Enter your password: ");
    EnterPass(password);
    do
    {
        PassFound=LoginPassCheck(password);
        if(PassFound==-1)
        {
            printf("\n\nPassword is not correct.\nPlease enter password again: ");
            EnterPass(password);
        }
    }while(PassFound==-1);
    MainMenu();
}


int UserNameSearch()
{
    char temp_Username[25];
    struct UserProfile *head,*temp;
    head=(struct UserProfile*)malloc(sizeof(struct UserProfile));
    head=ProfileIteration();
    temp=head;
    strcpy(temp_Username,username);
    strcat(temp_Username,"\n");
    while(temp->next!=NULL)
    {
        if(strcmp(temp->user_name,temp_Username)==0)
            return 0;
        temp=temp->next;
    }
    return -1;
}


int LoginPassCheck(int password[])
{
    char temp_Username[25],temp_Password[25];
    struct UserProfile *head,*temp;
    head=(struct UserProfile*)malloc(sizeof(struct UserProfile));
    head=ProfileIteration();
    temp=head;
    strcpy(temp_Username,username);
    strcpy(temp_Password,password);
    strcat(temp_Username,"\n");
    strcat(temp_Password,"\n");
    while(temp->next!=NULL)
    {
        if((strcmp(temp_Username,temp->user_name)==0) && (strcmp(temp_Password,temp->password)==0))
            return 0;
        temp=temp->next;
    }
    return -1;
}


void MainMenu()
{
    system("cls");
    char MainMenuChoice;
    int temp;
    printf("-----MAIN MENU-----\n\n\n1) Submit Income\n2) Submit Expenses\n3) Reports\n4) Settings\n5) Logout\n6) Exit\n");
    do
    {
        MainMenuChoice=getch();
        temp=MainMenuChoice - '0';
    }while(temp<1 || temp>6);

    switch(MainMenuChoice)
    {
        case '1':
        {
            SubmitIncome();
            break;
        }
        case '2':
        {
            SubmitExpense();
            break;
        }
        case '3':
        {
            Reports();
            break;
        }

    }
}

void SubmitIncome()
{
    system("cls");
    char AfterSubmitChoice,Incomes_Directory[50],IncomeAmount[20],ChooseSource,SourceOfIncome[30],YearOfIncome[6],MonthOfIncome[4],DayOfIncome[4],IncomeDescription[100];
    int temp;
    FILE *Incomes;
    strcpy(Incomes_Directory,"F:\\\\C_Programs\\\\Final_Project\\\\incomes\\\\");
    strcat(Incomes_Directory,username);
    strcat(Incomes_Directory,".txt");
    Incomes=fopen(Incomes_Directory,"a");
    printf("----- INCOME SUBMIT -----\n\n\nEnter amount of income in Iranian RIAL currency: ");
    gets(IncomeAmount);
    strcat(IncomeAmount,"\n");
    ChooseSourceOfIncome(SourceOfIncome);
    printf("Please enter year of income in YYYY format: ");
    gets(YearOfIncome);
    strcat(YearOfIncome,"\n");
    printf("Please enter month of income in MM format(without zero): ");
    gets(MonthOfIncome);
    strcat(MonthOfIncome,"\n");
    printf("Please enter day of income in DD format(without zero): ");
    gets(DayOfIncome);
    strcat(DayOfIncome,"\n");
    printf("Please enter a short(one line) description: ");
    gets(IncomeDescription);
    if(strcmp(IncomeDescription,"")==0)
        strcpy(IncomeDescription,"None");
    strcat(IncomeDescription,"\n");
    fputs(IncomeAmount,Incomes);
    fputs(SourceOfIncome,Incomes);
    fputs(YearOfIncome,Incomes);
    fputs(MonthOfIncome,Incomes);
    fputs(DayOfIncome,Incomes);
    fputs(IncomeDescription,Incomes);
    fclose(Incomes);
    system("cls");
    printf("Income submitted successfully");
    sleep(1);
    system("cls");
    printf("\n1) Submit another income\n2) Return to main menu\n");
    do
    {
        AfterSubmitChoice=getch();
        temp=AfterSubmitChoice-'0';
    }while(temp!=1 && temp!=2);

    if(AfterSubmitChoice=='1')
        SubmitIncome();
    else
        MainMenu();
}

void SubmitExpense()
{
    system("cls");
    char AfterSubmitChoice,Expenses_Directory[50],ExpenseAmount[20],ChooseSubject,SubjectOfExpense[30],YearOfExpenditure[6],MonthOfExpenditure[4],DayOfExpenditure[4],ExpenseDescription[100];
    int temp;
    FILE *Expenses;
    strcpy(Expenses_Directory,"F:\\\\C_Programs\\\\Final_Project\\\\expenses\\\\");
    strcat(Expenses_Directory,username);
    strcat(Expenses_Directory,".txt");
    Expenses=fopen(Expenses_Directory,"a");
    printf("----- EXPENSE SUBMIT -----\n\n\nEnter amount of expenditure in Iranian RIAL currency: ");
    gets(ExpenseAmount);
    strcat(ExpenseAmount,"\n");
    printf("\n\n1) Healthcare\n2) Food\n3) Bills\n4) Education\n5) Transportation\n6) Clothing\n7) Charity\n8) Recreation\n9) Other\n");
    do
    {
        ChooseSubject=getch();
        temp=ChooseSubject - '0';
    }while(temp<1 || temp>9);

    switch(ChooseSubject)
    {
        case '1':
        {
            strcpy(SubjectOfExpense,"Healthcare\n");
            break;
        }
        case '2':
        {
            strcpy(SubjectOfExpense,"Food\n");
            break;
        }
        case '3':
        {
            strcpy(SubjectOfExpense,"Bills\n");
            break;
        }
        case '4':
        {
            strcpy(SubjectOfExpense,"Education\n");
            break;
        }
        case '5':
        {
            strcpy(SubjectOfExpense,"Transportation\n");
            break;
        }
        case '6':
        {
            strcpy(SubjectOfExpense,"Clothing\n");
            break;
        }
        case '7':
        {
            strcpy(SubjectOfExpense,"Charity\n");
            break;
        }
        case '8':
        {
            strcpy(SubjectOfExpense,"Recreation\n");
            break;
        }
        default:
        {
            printf("Please enter subject of expenditure: ");
            gets(SubjectOfExpense);
            strcat(SubjectOfExpense,"\n");
        }
    }
    printf("Please enter year of expenditure in YYYY format: ");
    gets(YearOfExpenditure);
    strcat(YearOfExpenditure,"\n");
    printf("Please enter month of expenditure in MM format(without zero): ");
    gets(MonthOfExpenditure);
    strcat(MonthOfExpenditure,"\n");
    printf("Please enter day of expenditure in DD format(without zero): ");
    gets(DayOfExpenditure);
    strcat(DayOfExpenditure,"\n");
    printf("Please enter a short(one line) description: ");
    gets(ExpenseDescription);
    if(strcmp(ExpenseDescription,"")==0)
        strcpy(ExpenseDescription,"None");
    strcat(ExpenseDescription,"\n");
    fputs(ExpenseAmount,Expenses);
    fputs(SubjectOfExpense,Expenses);
    fputs(YearOfExpenditure,Expenses);
    fputs(MonthOfExpenditure,Expenses);
    fputs(DayOfExpenditure,Expenses);
    fputs(ExpenseDescription,Expenses);
    fclose(Expenses);
    system("cls");
    printf("Expense submitted successfully");
    sleep(1);
    system("cls");
    printf("\n1) Submit another expense\n2) Return to main menu\n");
    do
    {
        AfterSubmitChoice=getch();
        temp=AfterSubmitChoice-'0';
    }while(temp!=1 && temp!=2);

    if(AfterSubmitChoice=='1')
        SubmitExpense();
    else
        MainMenu();
}

void Reports()
{
    system("cls");
    char ReportTypeChoice;
    int temp;
    printf("-----  REPORTS MENU  -----\n\n\n1) Account balance\n2) Incomes Reports\n3) Expenses Reports\n");
    do
    {
        ReportTypeChoice=getch();
        temp=ReportTypeChoice - '0';
    }while(temp<1 || temp>3);
    if(ReportTypeChoice=='1')
        AccountBalance();
    else if(ReportTypeChoice=='2')
        IncomeReports();
}

void IncomeReports()
{
    system("cls");
    char IncomeReportType;
    int temp;
    printf("-----  INCOME REPORTS  -----\n\n\nPlease choose report type from the list: \n\n\n1) Annual income statement\n2) Income statement for a time period\n3) Specific income statement for a time period\n4) Incomes share ratio\n5) Detailed income statement for a time period\n6) Highest income in a time period\n7) Search in descriptions");
    do
    {
        IncomeReportType=getch();
        temp=IncomeReportType-'0';
    }while(temp<1 || temp>7);
    switch(IncomeReportType)
    {
        case '1':
        {
            AnnualIncome();
            break;
        }
        case '2':
        {
            IncomeInTimePeriod();
            break;
        }
        case '3':
        {
            SpecificIncomeInTimePeriod();
            break;
        }
        case '4':
        {
            system("cls");
            printf("\n\n\nPlease choose timespan of the report: \n\n\n1) All time\n2) Specific timespan ");
            do
            {
                IncomeReportType=getch();
                temp=IncomeReportType-'0';
            }while(temp!=1 && temp!=2);
            if(IncomeReportType=='1')
                IncomesShareRatio();
            else
                IncomesShareRatioInTimePeriod();
            break;
        }
        case '5':
        {
            DetailedIncomesInTimePeriod();
            break;
        }
        case '6':
        {
            HighestIncomeInTimePeriod();
            break;
        }
        default:
        {
            IncomeSearchInDescription();
        }
    }
}

void IncomeSearchInDescription()
{
    system("cls");
    struct UserIncome *head,*IncomeTemp;
    head=(struct UserIncome*)malloc(sizeof(struct UserIncome));
    head=IncomeIteration();
    IncomeTemp=head;
    char WordInDescription[100];
    int count=1;
    printf("Please enter a word or phrase: ");
    gets(WordInDescription);
    system("cls");
    while(IncomeTemp->next!=NULL)
    {
        if(StrStrIA(IncomeTemp->description,WordInDescription)!=NULL)
        {
            printf("INCOME #%d\n\n",count);
            IncomeTemp->amount[strlen(IncomeTemp->amount)-1]='\0';
            printf("Amount = ",IncomeTemp->amount);
            puts(IncomeTemp->amount);
            IncomeTemp->source[strlen(IncomeTemp->source)-1]='\0';
            printf("Source : ");
            puts(IncomeTemp->source);
            IncomeTemp->Year[strlen(IncomeTemp->Year)-1]='\0';
            IncomeTemp->Month[strlen(IncomeTemp->Month)-1]='\0';
            printf("Date : %s/%s/%s",IncomeTemp->Year,IncomeTemp->Month,IncomeTemp->Day);
            IncomeTemp->description[strlen(IncomeTemp->description)-1]='\0';
            printf("Description : ");
            if(strcmp(IncomeTemp->description,"")==0)
                printf("None");
            else
                puts(IncomeTemp->description);
            count++;
            printf("\n\n\n\n\n");
        }
        IncomeTemp=IncomeTemp->next;
    }
}

void HighestIncomeInTimePeriod()
{
    system("cls");
    char BeginYear[6],EndYear[6],BeginMonth[4],EndMonth[4],BeginDay[4],EndDay[4];
    char *end;
    int IncomeDate;
    long long int HighestIncome=0;
    struct UserIncome *head,*IncomeTemp;
    head=(struct UserIncome*)malloc(sizeof(struct UserIncome));
    head=IncomeIteration();
    IncomeTemp=head;
    InputTimePeriod(BeginYear,BeginMonth,BeginDay,EndYear,EndMonth,EndDay);
    while(IncomeTemp->next!=NULL)
    {
        IncomeDate=CheckTimePeriod(IncomeTemp->Year,IncomeTemp->Month,IncomeTemp->Day,BeginYear,BeginMonth,BeginDay,EndYear,EndMonth,EndDay);
        if(IncomeDate==0)//if income is in time period
        {
            if(HighestIncome==0)
            {
                HighestIncome=strtoull(IncomeTemp->amount,&end,10);
                IncomeTemp=IncomeTemp->next;
                continue;
            }
            if(strtoull(IncomeTemp,&end,10)>HighestIncome)
                HighestIncome=strtoull(IncomeTemp,&end,10);
        }
        IncomeTemp=IncomeTemp->next;
    }
    system("cls");
    if(HighestIncome==0)
        printf("\n\n\nYou have not submitted any income in this time period");
    else
        printf("\n\n\nYour highest income between %s/%s/%s and %s/%s/%s\nis %lld",BeginYear,BeginMonth,BeginDay,EndYear,EndMonth,EndDay,HighestIncome);
    printf("\n\n\nPress any button to continue");
    getch();
    ReturnToMenu();
}

void DetailedIncomesInTimePeriod()
{
    system("cls");
    char BeginYear[6],EndYear[6],BeginMonth[4],EndMonth[4],BeginDay[4],EndDay[4];
    char *end;
    int IncomeDate,count=1;
    struct UserIncome *head,*IncomeTemp;
    head=(struct UserIncome*)malloc(sizeof(struct UserIncome));
    head=IncomeIteration();
    IncomeTemp=head;
    InputTimePeriod(BeginYear,BeginMonth,BeginDay,EndYear,EndMonth,EndDay);
    system("cls");
    while(IncomeTemp->next!=NULL)
    {
        IncomeDate=CheckTimePeriod(IncomeTemp->Year,IncomeTemp->Month,IncomeTemp->Day,BeginYear,BeginMonth,BeginDay,EndYear,EndMonth,EndDay);
        if(IncomeDate==0)
        {
            printf("INCOME #%d\n\n",count);
            IncomeTemp->amount[strlen(IncomeTemp->amount)-1]='\0';
            printf("Amount = ",IncomeTemp->amount);
            puts(IncomeTemp->amount);
            IncomeTemp->source[strlen(IncomeTemp->source)-1]='\0';
            printf("Source : ");
            puts(IncomeTemp->source);
            IncomeTemp->Year[strlen(IncomeTemp->Year)-1]='\0';
            IncomeTemp->Month[strlen(IncomeTemp->Month)-1]='\0';
            printf("Date : %s/%s/%s",IncomeTemp->Year,IncomeTemp->Month,IncomeTemp->Day);
            IncomeTemp->description[strlen(IncomeTemp->description)-1]='\0';
            printf("Description : ");
            if(strcmp(IncomeTemp->description,"")==0)
                printf("None");
            else
                puts(IncomeTemp->description);
            count++;
            printf("\n\n\n\n\n");
        }
        IncomeTemp=IncomeTemp->next;
    }
    printf("\n\n\nPress enter to continue");
    getch();
    ReturnToMenu();
}


void IncomesShareRatioInTimePeriod()
{
   system("cls");
   char BeginYear[6],EndYear[6],BeginMonth[4],EndMonth[4],BeginDay[4],EndDay[4];
   char *end;
   long long int SalaryCount=0,PocketCount=0,GrantCount=0,GovAidCount=0,LoanCount=0,InterestCount=0,SUM=0,OthersCount=0;;
   int IncomeDate;
   double SalaryShare=0,PocketShare=0,GrantShare=0,GovAidShare=0,LoanShare=0,InterestShare=0,OthersShare=0;
   struct UserIncome *head,*IncomeTemp;
   head=(struct UserIncome*)malloc(sizeof(struct UserIncome));
   head=IncomeIteration();
   IncomeTemp=head;
   InputTimePeriod(BeginYear,BeginMonth,BeginDay,EndYear,EndMonth,EndDay);
   while(IncomeTemp->next!=NULL)
   {
        IncomeDate=CheckTimePeriod(IncomeTemp->Year,IncomeTemp->Month,IncomeTemp->Day,BeginYear,BeginMonth,BeginDay,EndYear,EndMonth,EndDay);
        if(IncomeDate==0)
        {
            if(strcasecmp(IncomeTemp->source,"Salary\n")==0)
                SalaryCount+=strtoull(IncomeTemp->amount,&end,10);
            else if(strcasecmp(IncomeTemp->source,"Pocket Money\n")==0)
                PocketCount+=strtoull(IncomeTemp->amount,&end,10);
            else if(strcasecmp(IncomeTemp->source,"University Grant\n")==0)
                GrantCount+=strtoull(IncomeTemp->amount,&end,10);
            else if(strcasecmp(IncomeTemp->source,"Government Aid\n")==0)
                GovAidCount+=strtoull(IncomeTemp->amount,&end,10);
            else if(strcasecmp(IncomeTemp->source,"Loan\n")==0)
                LoanCount+=strtoull(IncomeTemp->amount,&end,10);
            else if(strcasecmp(IncomeTemp->source,"Bank Interest\n")==0)
                InterestCount+=strtoull(IncomeTemp->amount,&end,10);
            else
                OthersCount+=strtoull(IncomeTemp->amount,&end,10);
            SUM+=strtoull(IncomeTemp->amount,&end,10);
        }
        IncomeTemp=IncomeTemp->next;
   }
   SalaryShare=((double)SalaryCount/SUM) * 100;
   PocketShare=((double)PocketCount/SUM) * 100;
   GrantShare=((double)GrantCount/SUM) * 100;
   GovAidShare=((double)GovAidCount/SUM) * 100;
   LoanShare=((double)LoanCount/SUM) * 100;
   InterestShare=((double)InterestCount/SUM) * 100;
   OthersShare=((double)OthersCount/SUM) * 100;
   system("cls");
   printf("\n\nYour income share ratio between %s/%s/%s and %s/%s/%s :\n\n\nSalary %20.3Lf%%\nPocket Money %14.3Lf%%\nUniversity Grant %10.3Lf%%\nGovernment Aid %12.3Lf%%\nLoan %22.3Lf%%\nBank Interest %13.3Lf%%\nOther Incomes %13.3Lf%%\n\n\nPress any button to continue",BeginYear,BeginMonth,BeginDay,EndYear,EndMonth,EndDay,SalaryShare,PocketShare,GrantShare,GovAidShare,LoanShare,InterestShare,OthersShare);
   getch();
   ReturnToMenu();
}


void IncomesShareRatio()
{
   system("cls");
   char *end;
   long long int SalaryCount=0,PocketCount=0,GrantCount=0,GovAidCount=0,LoanCount=0,InterestCount=0,SUM=0,OthersCount=0;;
   double SalaryShare=0,PocketShare=0,GrantShare=0,GovAidShare=0,LoanShare=0,InterestShare=0,OthersShare=0;
   struct UserIncome *head,*IncomeTemp;
   head=(struct UserIncome*)malloc(sizeof(struct UserIncome));
   head=IncomeIteration();
   IncomeTemp=head;
   while(IncomeTemp->next!=NULL)
   {
       if(strcasecmp(IncomeTemp->source,"Salary\n")==0)
           SalaryCount+=strtoull(IncomeTemp->amount,&end,10);
       else if(strcasecmp(IncomeTemp->source,"Pocket Money\n")==0)
           PocketCount+=strtoull(IncomeTemp->amount,&end,10);
       else if(strcasecmp(IncomeTemp->source,"University Grant\n")==0)
           GrantCount+=strtoull(IncomeTemp->amount,&end,10);
       else if(strcasecmp(IncomeTemp->source,"Government Aid\n")==0)
           GovAidCount+=strtoull(IncomeTemp->amount,&end,10);
       else if(strcasecmp(IncomeTemp->source,"Loan\n")==0)
           LoanCount+=strtoull(IncomeTemp->amount,&end,10);
       else if(strcasecmp(IncomeTemp->source,"Bank Interest\n")==0)
           InterestCount+=strtoull(IncomeTemp->amount,&end,10);
       else
           OthersCount+=strtoull(IncomeTemp->amount,&end,10);
       SUM+=strtoull(IncomeTemp->amount,&end,10);
       IncomeTemp=IncomeTemp->next;
   }
   SalaryShare=((double)SalaryCount/SUM) * 100;
   PocketShare=((double)PocketCount/SUM) * 100;
   GrantShare=((double)GrantCount/SUM) * 100;
   GovAidShare=((double)GovAidCount/SUM) * 100;
   LoanShare=((double)LoanCount/SUM) * 100;
   InterestShare=((double)InterestCount/SUM) * 100;
   OthersShare=((double)OthersCount/SUM) * 100;
   system("cls");
   printf("\n\nYour All time income share ratio :\n\n\nSalary %20.3Lf%%\nPocket Money %14.3Lf%%\nUniversity Grant %10.3Lf%%\nGovernment Aid %12.3Lf%%\nLoan %22.3Lf%%\nBank Interest %13.3Lf%%\nOther Incomes %13.3Lf%%\n\n\nPress any button to continue",SalaryShare,PocketShare,GrantShare,GovAidShare,LoanShare,InterestShare,OthersShare);
   getch();
   ReturnToMenu();
}


void SpecificIncomeInTimePeriod()
{
   system("cls");
   struct UserIncome *head,*IncomeTemp;
   char SourceOfIncome[30],BeginYear[6],EndYear[6],BeginMonth[4],EndMonth[4],BeginDay[4],EndDay[4],ChooseSource;
   char *end;
   long long int IncomeCount=0;
   int temp,IncomeDate;
   head=(struct UserIncome*)malloc(sizeof(struct UserIncome));
   head=IncomeIteration();
   IncomeTemp=head;
   ChooseSourceOfIncome(SourceOfIncome);
   InputTimePeriod(BeginYear,BeginMonth,BeginDay,EndYear,EndMonth,EndDay);
   while(IncomeTemp->next!=NULL)
   {
       if(strcasecmp(IncomeTemp->source,SourceOfIncome)==0)
       {
           IncomeDate=CheckTimePeriod(IncomeTemp->Year,IncomeTemp->Month,IncomeTemp->Day,BeginYear,BeginMonth,BeginDay,EndYear,EndMonth,EndDay);
           if(IncomeDate==0)
               IncomeCount+=strtoull(IncomeTemp->amount,&end,10);
       }
       IncomeTemp=IncomeTemp->next;
   }
   SourceOfIncome[strlen(SourceOfIncome)-1]='\0';
   system("cls");
   printf("\n\n\nYour total income from %s between %s/%s/%s and %s/%s/%s\nis %lld Iranian RIALS.\n\n\nPress any button to continue",SourceOfIncome,BeginYear,BeginMonth,BeginDay,EndYear,EndMonth,EndDay,IncomeCount);
   getch();
   ReturnToMenu();
}


void IncomeInTimePeriod()
{
   system("cls");
   struct UserIncome *head,*IncomeTemp;
   char BeginYear[6],EndYear[6],BeginMonth[4],EndMonth[4],BeginDay[4],EndDay[4];
   char *end;
   long long int IncomeCount=0;
   int IncomeDate;
   head=(struct UserIncome*)malloc(sizeof(struct UserIncome));
   head=IncomeIteration();
   IncomeTemp=head;
   InputTimePeriod(BeginYear,BeginMonth,BeginDay,EndYear,EndMonth,EndDay);
   while(IncomeTemp->next!=NULL)
   {
       IncomeDate=CheckTimePeriod(IncomeTemp->Year,IncomeTemp->Month,IncomeTemp->Day,BeginYear,BeginMonth,BeginDay,EndYear,EndMonth,EndDay);
       if(IncomeDate==0)
           IncomeCount+=strtoull(IncomeTemp->amount,&end,10);
       IncomeTemp=IncomeTemp->next;
   }
   system("cls");
   printf("\n\n\nYour total income between %s/%s/%s and %s/%s/%s\nis %lld Iranian RIALS.\n\n\nPress any button to continue",BeginYear,BeginMonth,BeginDay,EndYear,EndMonth,EndDay,IncomeCount);
   getch();
   ReturnToMenu();
}


void AnnualIncome()
{
    system("cls");
    struct UserIncome *head,*IncomeTemp;
    char Year[6];
    char *end;
    long long int IncomeCount=0;
    head=(struct UserIncome*)malloc(sizeof(struct UserIncome));
    head=IncomeIteration();
    IncomeTemp=head;
    printf("Please enter a year: ");
    gets(Year);
    while(IncomeTemp->next!=NULL)
    {
        if(atoi(IncomeTemp->Year)==atoi(Year))
            IncomeCount+=strtoull(IncomeTemp->amount,&end,10);
        IncomeTemp=IncomeTemp->next;
    }
    printf("Your income in %s is %lld\n\nPress any button to continue",Year,IncomeCount);
    getch();
    ReturnToMenu();
}


void AccountBalance()
{
    system("cls");
    long long int IncomeCount=0,ExpenseCount=0,Balance=0;
    char *end;
    struct UserIncome *IncomeHead,*IncomeTemp;
    struct UserExpense *ExpenseHead, *ExpenseTemp;
    IncomeHead=(struct UserIncome*)malloc(sizeof(struct UserIncome));
    ExpenseHead=(struct UserExpense*)malloc(sizeof(struct UserExpense));
    IncomeHead=IncomeIteration();
    ExpenseHead=ExpenseIteration();
    IncomeTemp=IncomeHead;
    ExpenseTemp=ExpenseHead;
    while(IncomeTemp->next!=NULL)
    {
        IncomeCount+=strtoull(IncomeTemp->amount,&end,10);
        IncomeTemp=IncomeTemp->next;
    }
    while(ExpenseTemp->next!=NULL)
    {
        ExpenseCount+=strtoull(ExpenseTemp->amount,&end,10);
        ExpenseTemp=ExpenseTemp->next;
    }
    Balance=IncomeCount-ExpenseCount;
    printf("\n\nYour account balance is %lld Iranian RIALS\n\nPlease press any button to continue",Balance);
    getch();
    ReturnToMenu();
}


 int ProfileIteration()
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
    fgets(head->MelliNum,sizeof head->MelliNum,profile);
    fgets(head->PhoneNum,sizeof head->PhoneNum ,profile);
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
        fgets(user->MelliNum,sizeof head->MelliNum,profile);
        fgets(user->PhoneNum,sizeof user->PhoneNum,profile);
        fgets(user->Email,sizeof head->Email,profile);
        user->next=NULL;
        temp->next=user;
        temp=user;
    }
    fclose(profile);
    return head;
}

int IncomeIteration()
{
    struct UserIncome *head,*income,*temp;
    char Incomes_Directory[70];
    FILE *Incomes;
    strcpy(Incomes_Directory,"F:\\\\C_Programs\\\\Final_Project\\\\incomes\\\\");
    strcat(Incomes_Directory,username);
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


int ExpenseIteration()
{
    struct UserExpense *head,*expense,*temp;
    char Expense_Directory[70];
    FILE *Expenses;
    strcpy(Expense_Directory,"F:\\\\C_Programs\\\\Final_Project\\\\expenses\\\\");
    strcat(Expense_Directory,username);
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


int CheckTimePeriod(int Year[],int Month[],int Day[],int BeginYear[],int BeginMonth[],int BeginDay[],int EndYear[],int EndMonth[],int EndDay[])
{
    char *end;
    if(strtoul(Year,&end,10)>=strtoul(BeginYear,&end,10)  &&   strtoul(Year,&end,10)<=strtoul(EndYear,&end,10))
       {
            if(strtoul(Year,&end,10)==strtoul(BeginYear,&end,10))
            {
                if(strtoul(Month,&end,10)<strtoul(BeginMonth,&end,10))
                    return -1;
                if(strtoul(Month,&end,10)==strtoul(BeginMonth,&end,10))
                    if(strtoul(Day,&end,10)<strtoul(BeginDay,&end,10))
                        return -1;
            }
            if(strtoul(Year,&end,10)==strtoul(EndYear,&end,10))
            {
                if(strtoul(Month,&end,10)>strtoul(EndMonth,&end,10))
                    return -1;
                if(strtoul(Month,&end,10)==strtoul(EndMonth,&end,10))
                    if(strtoul(Day,&end,10)>strtoul(EndDay,&end,10))
                        return -1;
            }
        }
    else
        return -1;
    return 0;
}

void InputTimePeriod(int BeginYear[],int BeginMonth[],int BeginDay[],int EndYear[],int EndMonth[],int EndDay[])
{
   printf("Enter beginning year in YYYY format: ");
   gets(BeginYear);
   printf("Enter beginning month in MM format (without zero): ");
   gets(BeginMonth);
   printf("Enter beginning day in DD format (without zero): ");
   gets(BeginDay);
   printf("\n\n\nEnter ending year in YYYY format: ");
   gets(EndYear);
   printf("Enter ending month in MM format (without zero): ");
   gets(EndMonth);
   printf("Enter ending day in DD format (without zero): ");
   gets(EndDay);
}

void ReturnToMenu()
{
    int temp;
    char MenuChoose;
    system("cls");
    printf("\n\n1) Return to main menu\n2) Return to reports menu\n3) Exit");
    do
    {
        MenuChoose=getch();
        temp=MenuChoose-'0';
    }while(temp<1 || temp>3);
    if(MenuChoose=='1')
        MainMenu();
    else if(MenuChoose=='2')
        Reports();
         else
             Exit();
}

void ChooseSourceOfIncome(int SourceOfIncome[])
{
    char ChooseSource;
    int temp;
    printf("\n\nPlease choose source of income :\n\n1) Salary\n2) Pocket Money\n3) Government Aid\n4) University Grant\n5) Bank Interest\n6) Loan\n7) Other\n");
    do
    {
        ChooseSource=getch();
        temp=ChooseSource - '0';
    }while(temp<1 || temp>7);

    switch(ChooseSource)
    {
        case '1':
        {
            strcpy(SourceOfIncome,"Salary\n");
            break;
        }
        case '2':
        {
            strcpy(SourceOfIncome,"Pocket Money\n");
            break;
        }
        case '3':
        {
            strcpy(SourceOfIncome,"Government Aid\n");
            break;
        }
        case '4':
        {
            strcpy(SourceOfIncome,"University Grant\n");
            break;
        }
        case '5':
        {
            strcpy(SourceOfIncome,"Bank Interest\n");
            break;
        }
        case '6':
        {
            strcpy(SourceOfIncome,"Loan\n");
            break;
        }
        default:
        {
            printf("\n\nPlease enter source of Income: ");
            gets(SourceOfIncome);
            strcat(SourceOfIncome,"\n");
        }
   }
}


