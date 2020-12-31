#include <stdio.h>

#define maxSize 32

#define passSetupSize 9
#define nameSetupSize 5
#define surnameSetupSize 8
#define ageSetupSize 4
#define allSetupSize 26 //passSetupSize + nameSetupSize + surnameSetupSize + ageSetupSize

#define skipToPassword 154 //maxSize*4 + allSetupSize

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

int counter = 0; //counter for Database password size
int c; // used for fgetc(fpt)
int skipToNextPass_counter = 0; //counts the amount of times it needs to do the sequence, depends on the amount of accounts



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


int passCheckingIncorrect(char passInDatabase[maxSize], char passForCheck[maxSize], int counter)  
{
    int passIncorrect = 0;
    for (int i = 0; i < counter; i++)
    {
        if (passInDatabase[i] != passForCheck[i])
        {
            passIncorrect = 1;
            break;
        }
        
    }
    return passIncorrect;
}


void skipToNextPass()
{
    int i;
    skipToNextPass_counter++;
    for (i = 0; i < skipToPassword*skipToNextPass_counter; i++)
    {
        c = fgetc(fpt);
    }
}


void displayInfo()
{
    int displayInfoCounter = 0;
    int i ;
    for (i = 0; i < maxSize - counter; i++)
    {
        c = fgetc(fpt);
        printf("%c", c);
    }

    //printing the name

    for (i = 0; i < nameSetupSize; i++)
    {
        c = fgetc(fpt);
        printf("%c", c);
    }
    for (i = 0; i < maxSize; i++)
    {
        c = fgetc(fpt);
        printf("%c", c);
        if (c == '\n')
        {
            break;
        }
        else
        {
            printf("Your name is: %c", c);
        }
    }
    printf("\n");
    displayInfoCounter = i;
    for (i = 0; i < maxSize - displayInfoCounter; i++)
    {
        c = fgetc(fpt);
        printf("%c", c);
    }

    //printing the surname


    for (i = 0; i < surnameSetupSize; i++)
    {
        c = fgetc(fpt);
        printf("%c", c);
    }
    for (i = 0; i < maxSize; i++)
    {
        c = fgetc(fpt);
        printf("%c", c);
        if (c == '\n')
        {
            break;
        }
        else
        {
            printf("Your surname is: %c", c);
        }
    }
    printf("\n");
    displayInfoCounter = i;
    for (i = 0; i < maxSize - displayInfoCounter; i++)
    {
        c = fgetc(fpt);
        printf("%c", c);
    }

    //printing the age

    for (i = 0; i < ageSetupSize; i++)
    {
        c = fgetc(fpt);
        printf("%c", c);
    }
    for (i = 0; i < maxSize; i++)
    {
        c = fgetc(fpt);
        printf("%c", c);
        if (c == '\n')
        {
            break;
        }
        else
        {
            printf("Your age is: %c", c);
        }
    }
    printf("\n");
    displayInfoCounter = i;
    for (i = 0; i < maxSize - displayInfoCounter; i++)
    {
        c = fgetc(fpt);
        printf("%c", c);
    }
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

        rewind(fpt);
        while (1)
        {
            //end of file
            if (feof(fpt))
            {
                printf("No account with this password found.");
                break;
            }


            //for loop for skipping the whole "password:" thing
            for (int i = 0; i < passSetupSize; i++)
            {
                c = fgetc(fpt);
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
            if (passCheckingIncorrect(passInDatabase, passForCheck, counter) == 1)
            {
                rewind(fpt);
                skipToNextPass();
            }
            else
            {
                printf("You have entered the correct password!");
                displayInfo();
                break;
            }
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
