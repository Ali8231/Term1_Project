#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#include<time.h>

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
         {
             printf("Thank you for using this program\nHope to see you again!");
             sleep(2);
             exit(1);
         }
}

void Signup()
{
    system("cls");
    char File_Directoy[80],name[20],family[25],password[21],ConfirmPass[21],MelliNum[11],PhoneNum[12],Email[35];
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
    strcpy(File_Directoy,"F:\\\\C_Programs\\\\Final_Project\\\\incomes\\\\");
    strcat(File_Directoy,username);
    strcat(File_Directoy,".txt");
    UserIncome=fopen(File_Directoy,"w");
    strcpy(File_Directoy,"F:\\\\C_Programs\\\\Final_Project\\\\expenses\\\\");
    strcat(File_Directoy,username);
    strcat(File_Directoy,".txt");
    UserExpense=fopen(File_Directoy,"w");
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
    printf("Enter the password again: ");
    EnterPass(ConfirmPass);
    do
    {
       if(strcmp(password,ConfirmPass)!=0)
       {
           printf("Password is not the same.\nPlease Enter the same password: ");
           EnterPass(ConfirmPass);
       }
    }while(strcmp(password,ConfirmPass)!=0);
    strcat(password,"\n");
    printf("Enter your Melli number: ");
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
    fclose(UserIncome);
    system("cls");
    printf("  User added Successfully");
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
            printf("User name was not found.\nPlease enter your user name again: ");
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
            printf("Password is not correct.\nPlease enter password again: ");
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
    while(temp!=NULL)
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
    while(temp!=NULL)
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
    printf("\n\n1) Salary\n2) Pocket Money\n3)Government Aid\n4)University Grant\n5) Bank Interest\n6) Loan\n7)Other\n");
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
            printf("Please enter source of Income: ");
            gets(SourceOfIncome);
            strcat(SourceOfIncome,"\n");
        }

    }
    printf("Please enter year of income in YYYY format: ");
    gets(YearOfIncome);
    strcat(YearOfIncome,"/");
    printf("Please enter month of income in MM format: ");
    gets(MonthOfIncome);
    strcat(MonthOfIncome,"/");
    printf("Please enter day of income in DD format: ");
    gets(DayOfIncome);
    strcat(DayOfIncome,"\n");
    printf("Please enter a short(one line) description: ");
    gets(IncomeDescription);
    strcat(IncomeDescription,"\n");
    fputs(IncomeAmount,Incomes);
    fputs(SourceOfIncome,Incomes);
    fputs(YearOfIncome,Incomes);
    fputs(MonthOfIncome,Incomes);
    fputs(DayOfIncome,Incomes);
    fputs(IncomeDescription,Incomes);
    fclose(Incomes);
    printf("\n\nEnter 1 to submit another income or any other button to return to main menu: ");
    AfterSubmitChoice=getche();
    if(AfterSubmitChoice=='1')
        SubmitExpense();
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
    strcat(YearOfExpenditure,"/");
    printf("Please enter month of expenditure in MM format: ");
    gets(MonthOfExpenditure);
    strcat(MonthOfExpenditure,"/");
    printf("Please enter day of expenditure in DD format: ");
    gets(DayOfExpenditure);
    strcat(DayOfExpenditure,"\n");
    printf("Please enter a short(one line) description: ");
    gets(ExpenseDescription);
    strcat(ExpenseDescription,"\n");
    fputs(ExpenseAmount,Expenses);
    fputs(SubjectOfExpense,Expenses);
    fputs(YearOfExpenditure,Expenses);
    fputs(MonthOfExpenditure,Expenses);
    fputs(DayOfExpenditure,Expenses);
    fputs(ExpenseDescription,Expenses);
    fclose(Expenses);
    printf("\n\nEnter 1 to submit another expense or any other button to return to main menu: ");
    AfterSubmitChoice=getche();
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

