#include <stdio.h>

#define MAX_SIZE 32

#define passSetupSize 9
#define nameSetupSize 5
#define surnameSetupSize 8
#define ageSetupSize 4

FILE *fpt;

const char passSetup[passSetupSize] = "password:";
const char nameSetup[nameSetupSize] = "name:";
const char surnameSetup[surnameSetupSize] = "surname:";
const char ageSetup[ageSetupSize] = "age:";

char userInput[MAX_SIZE];


void setupPrint(const char setupArray[MAX_SIZE], int setupArraySize)
{
    for (int i = 0; i < setupArraySize; i++)
    {
        fputc(setupArray[i], fpt);
    }
}

int flag = 0;

void inputPrint(char userInput[MAX_SIZE], int correctnessCheck)
{
    flag = 0;
    int invalidInput = 0;
    if (correctnessCheck == 1)
    {
        for (int i = 0; i < MAX_SIZE; i++)
        {
            if (userInput[i] != '\n')
            {
                if (!((userInput[i] >= 'A' && userInput[i] <= 'Z') ||
                (userInput[i] >= 'a' && userInput[i] <= 'z')))
                {
                    invalidInput = 1;
                }
            }
            else
            {
                break;
            }
            
        }
        if (invalidInput == 0)
        {
            for (int i = 0; i < MAX_SIZE; i++)
            {
                fputc(userInput[i], fpt);
            }
            flag = 1;
        }
        else
        {
            printf("Invalid input! Try again!\n");
        }
    }
    else if (correctnessCheck == 2)
    {   
        for (int i = 0; i < MAX_SIZE; i++)
        {
            if (userInput[i] != '\n')
            {
                if (!(userInput[i] >= '0' && userInput[i] <= '9'))
                {
                    invalidInput = 1;
                }
            }
            else
            {
                break;
            }
        }
        if (invalidInput == 0)
        {
            for (int i = 0; i < MAX_SIZE; i++)
            {
                fputc(userInput[i], fpt);
            }
            flag = 1;
        }
        else
        {
            printf("Invalid input! Try again!\n");
        }   
    }
    else
    {
        for (int i = 0; i < MAX_SIZE; i++)
        {
            fputc(userInput[i], fpt);
        }
        
        flag = 1;
    }
    
}












void choiceOne()
{
    printf("you chose 1");
}














void choiceTwo()
{
    //getting the user's password
	printf("Enter the password you want to use (max 32 characters) > ");
    do
    {
        fgets(userInput, MAX_SIZE, stdin);
        setupPrint(passSetup, passSetupSize);
        inputPrint(userInput, 0);
    } while (flag != 1);
    

    //getting the user's name
    printf("Enter your name (max 32 characters) > ");
    do
    {
        fgets(userInput, MAX_SIZE, stdin);
        setupPrint(nameSetup, nameSetupSize);
        inputPrint(userInput, 1);
    } while (flag != 1);
    

    //getting the user's surname
    printf("Enter your surname (max 32 characters) > ");
    do
    {
        fgets(userInput, MAX_SIZE, stdin);
        setupPrint(surnameSetup, surnameSetupSize);
        inputPrint(userInput, 1);
    } while (flag != 1);


    //getting the user's age
    printf("Enter your age > ");
    do
    {
        fgets(userInput, MAX_SIZE, stdin);
        setupPrint(ageSetup, ageSetupSize);
        inputPrint(userInput, 2);
    } while (flag != 1);
    
}










int main()
{
    fpt = fopen("database.txt", "a+");
    int loginOrCreate;
    int loginOrCreate_correctInput = 0;

    printf("Do you want to login or create an account? (1/2) > ");
    do
    {
        scanf("%d", &loginOrCreate);
        if (loginOrCreate != 1 && loginOrCreate != 2)
        {
            printf("Invalid input, try again!\n");
        }
        else
        {
            loginOrCreate_correctInput = 1;
        }
    } while (loginOrCreate_correctInput != 1);

    fflush(stdin);

    if (loginOrCreate == 1)
    {
        choiceOne();
    }
    else if (loginOrCreate == 2)
    {
        choiceTwo();
    }

    fclose(fpt);

    return 0;
}
