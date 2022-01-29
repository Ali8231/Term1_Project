***This is an overview on Ali Asiaee project ordered by Dr.Taheri Javan Assistant Professor at IKIU University,Engineering Department,CE section.***


--This project is a simple accounting program designed to meet the basic needs of accounting suitable for personal and limited commercial use.
--Also this is a multi user program so it can provide service to thousands of users.
--Unfortunately for developers,This in NOT an open source project as ordered by my Professor.But you still can share your Ideas and criticisms
by sending an email to : aliasiaee304@gmail.com

***WARNING : This program is exclusively developed for use in Islamic Republic of Iran and non-Iranian users may find this program difficult to use.***

***Here is a short description on how this program works***

--Program is developed in one piece of code
--On the first run program only includes Accounting.c,Accounting.exe and two folders named incomes and expenses.you can open program with both .c and .exe files,but .exe file is recommended
--After running on first time,when you sign up for the first user program automatically creates a file named Profile.txt to store users information in the order as followes:

1. Name
2. Last Name
3. User Name
4. Password
5. Melli Number
6. Phone Number
7. Email Address

**CAUTION 1: Users passwords are saved coded.** 

**CAUTION 2 : All usernames are unique to prevent unauthorized access.**

**CAUTION 3 : Every single piece information/data (even Year,Month and Day) is stored line by line for ALL .txt files **

--In the MAIN MENU user can submit incomes and expenses.
--Program saves each user's incomes and expenses seperatly.
--For incomes as mentioned before there's an income folder.Whenever a user submits an income,program will create a .txt file named exactly as username and fills the file with income data.
--if user has an account and has submitted income before new data will be saved at the end of the existing file instead of a new one.
--This is also true for expenses except that they are stored in expenses folder.Incomes/Expenses cases include the following data:

1. Amount of money
2. Source/Subject of income/expense
3. Date of Submit
4. Description

--This programs bans user when he/she enters password incorrectly for 5 consecutive times.Limit is set for 5 minutes and after that user is free to try again.
--To prevent bannes users from cheating by exiting the program and loging in again,after the program's first ban a file named PassLimit.txt is created automatically which saves banned usernames and times of ban
--For each login this file is checked to see if user has active ban statement,if no user may proceed,if yes ban will activate for the remaining ban time.
--As before,when there is an existing PassLimit.txt new ban information will be added to the end of existing file
--Also if any of the .txt files data is completely deleted for any reason,file will be deleted automatically to be created again later on demand.


--Reports section provides users with multiple report statements that you can choose from.They are developed using linked list exclusively.


--In settings user can change their Username,Password,Phone Numbers and Email address.You can also delete your account.Be careful with that as it is not recursable and ALL of
your data will be deleted permanently.
--Please note that you CAN NOT change your Name,Last Name and Melli Number so be very careful when entering them in Signup
--If it is extremely essential to change these data contact me at : aliasiaee304@gmail.com.
--The changes in any data from profile is done by completely deleting profile and filling it again but with the old data replced by new ones.

--This was an overview of my program.Hope it helped you.
--Feel free to contact me at aliasiaee304@gmail.com for any issiue,Idea,Bug,... that you see in the program.
