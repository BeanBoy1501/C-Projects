#include <stdio.h>

#define maxSize 32

#define passSetupSize 9
#define nameSetupSize 5
#define surnameSetupSize 8
#define ageSetupSize 4

FILE *fpt;
void choiceOne();
void choiceTwo();

const char passSetup[passSetupSize] = "password:";
const char nameSetup[nameSetupSize] = "name:";
const char surnameSetup[surnameSetupSize] = "surname:";
const char ageSetup[ageSetupSize] = "age:";
char useless[4];

char userInput[maxSize];
char passForCheck[maxSize];
char passInDatabase[maxSize];



void setupPrint(const char setupArray[maxSize], int setupArraySize)
{
    for (int i = 0; i < setupArraySize; i++)
    {
        fputc(setupArray[i], fpt);
    }
}

int flag = 0;

void inputPrint(char userInput[maxSize], int correctnessCheck)
{
    flag = 0;
    int invalidInput = 0;
    if (correctnessCheck == 1)
    {
        for (int i = 0; i < maxSize; i++)
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
            for (int i = 0; i < maxSize; i++)
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
        for (int i = 0; i < maxSize; i++)
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
            for (int i = 0; i < maxSize; i++)
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
        for (int i = 0; i < maxSize; i++)
        {
            fputc(userInput[i], fpt);
        }
        
        flag = 1;
    }
    
}


void passChecking(char passInDatabase[maxSize], char passForCheck[maxSize], int counter)  
{
    for (int i = 0; i < counter; i++)
    {
        if (passInDatabase[i] != passForCheck[i])
        {
            printf("they not same!");
        }
        
    }
    
}


void skipToNextPass()
{

}









void choiceOne()
{
    char *s = fgets(useless, 4, fpt);
    if (s == NULL)
    {
        printf("There are no accounts registered, creating a new account now.\n");
        choiceTwo();  
    }

    else
    {
        printf("Enter your password > ");
        fgets(passForCheck, maxSize, stdin);

        int passSetupSkip = 0;
        int c;
        int counter = 0;

        rewind(fpt);
        while (1)
        {
            //for loop for skipping the whole "password:" thing
            if (passSetupSkip == 0)
            {
                for (int i = 0; i < passSetupSize; i++)
                {
                    c = fgetc(fpt);
                }
                passSetupSkip = 1;
            }


            for (int i = 0; i < maxSize; i++)
            {
                c = fgetc(fpt);
                if (c == '\n')
                {
                    counter = i;
                    break;
                }
                else
                {
                    passInDatabase[i] = c;
                }
            }
            passChecking(passInDatabase, passForCheck, counter);

        }
    }
}














void choiceTwo()
{

    //getting the user's password
	printf("Enter the password you want to use for future logins (max 32 characters) > ");
    setupPrint(passSetup, passSetupSize);
    do
    {
        fgets(userInput, maxSize, stdin);
        inputPrint(userInput, 0);
    } while (flag != 1);
    

    //getting the user's name
    printf("Enter your name (max 32 characters) > ");
    setupPrint(nameSetup, nameSetupSize);
    do
    {
        fgets(userInput, maxSize, stdin);
        inputPrint(userInput, 1);
    } while (flag != 1);
    

    //getting the user's surname
    printf("Enter your surname (max 32 characters) > ");
    setupPrint(surnameSetup, surnameSetupSize);
    do
    {
        fgets(userInput, maxSize, stdin);
        inputPrint(userInput, 1);
    } while (flag != 1);


    //getting the user's age
    printf("Enter your age > ");
    setupPrint(ageSetup, ageSetupSize);
    do
    {
        fgets(userInput, maxSize, stdin);
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
