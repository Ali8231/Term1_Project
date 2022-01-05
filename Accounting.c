#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<conio.h>

void Signup();
char username[15];
void main()
{
    char FirstMenuChoice;
    printf("Welcome to Ali accounting software");
    sleep(2);
    system("cls");
    printf("1) Signup\n2) Login\n3) Exit\n\nPlease enter a number from the list: ");
    FirstMenuChoice=getche();
    if(FirstMenuChoice=='1')
        Signup();


}
void Signup()
{
    system("cls");
    char temp[80],name[20],family[25],password[21],ConfirmPass[21],MelliNum[11],PhoneNum[12],Email[35];
    FILE *profile,*UserIncome,*UserExpense;
    profile=fopen("profile.txt","a");
    printf("-----SIGN UP PAGE-----\n\n\nEnter your first name: ");
    gets(name);
    strcat(name,"\n");
    fputs(name,profile);
    printf("Enter your last name: ");
    gets(family);
    strcat(family,"\n");
    fputs(family,profile);
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
    strcpy(temp,"F:\\\\C_Programs\\\\Final_Project\\\\incomes\\\\");
    strcat(temp,username);
    strcat(temp,".txt");
    UserIncome=fopen(temp,"w");
    strcpy(temp,"F:\\\\C_Programs\\\\Final_Project\\\\expenses\\\\");
    strcat(temp,username);
    strcat(temp,".txt");
    UserExpense=fopen(temp,"w");
    strcat(username,"\n");
    fputs(username,profile);
    printf("\n\nNotes about password:\n---Your password must be between 8 and 20 characters\n---Your password must include uppercase and lowercase letters,at least one\n number and one special character(@,*,#,...)\n\nEnter password: ");
    gets(password);
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
     gets(ConfirmPass);
    do
    {
       if(strcmp(password,ConfirmPass)!=0)
       {
           printf("Password is not the same.\nPlease Enter the same password: ");
           gets(ConfirmPass);
       }
    }while(strcmp(password,ConfirmPass)!=0);
    strcat(password,"\n");
    fputs(password,profile);
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
    fputs(MelliNum,profile);
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
    fputs(PhoneNum,profile);
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
    fputs(Email,profile);
    fclose(UserIncome);
}
