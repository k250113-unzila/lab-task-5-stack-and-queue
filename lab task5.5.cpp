#include <iostream>
using namespace std;

#define MAXTOK 200
#define TOKLEN 12


bool isOperator(char token[])
{
    if (token[0] == '+' && token[1] == '\0')
        return true;

    return false;
}


void copyString(char destination[], char source[])
{
    int i = 0;

    while (source[i] != '\0')
    {
        destination[i] = source[i];
        i++;
    }

    destination[i] = '\0';
}


void numberToString(int number, char result[])
{
    int digits[10];
    int count = 0;

    if (number == 0)
    {
        result[0] = '0';
        result[1] = '\0';
        return;
    }

    while (number > 0)
    {
        digits[count] = number % 10;
        number = number / 10;
        count++;
    }

    int j = 0;

    for (int i = count - 1; i >= 0; i--)
    {
        result[j] = digits[i] + '0';
        j++;
    }

    result[j] = '\0';
}


void createSeries(int n, char tokens[][TOKLEN], int &count)
{
    count = 0;

    for (int i = 1; i <= n; i++)
    {
        int term = 3 * i - 2;

        numberToString(term, tokens[count]);
        count++;

        // Add +
        if (i != n)
        {
            tokens[count][0] = '+';
            tokens[count][1] = '\0';

            count++;
        }
    }
}


void infixToPostfix(
    char tokens[][TOKLEN],
    int n,
    char output[][TOKLEN],
    int &outCount)
{
    char stack[MAXTOK][TOKLEN];

    int top = -1;

    outCount = 0;

    for (int i = 0; i < n; i++)
    {
        if (isOperator(tokens[i]))
        {
            while (top >= 0)
            {
                copyString(output[outCount], stack[top]);

                outCount++;
                top--;
            }

            top++;

            copyString(stack[top], tokens[i]);
        }
        else
        {
            copyString(output[outCount], tokens[i]);

            outCount++;
        }
    }

    while (top >= 0)
    {
        copyString(output[outCount], stack[top]);

        outCount++;
        top--;
    }
}


void infixToPrefix(
    char tokens[][TOKLEN],
    int n,
    char output[][TOKLEN],
    int &outCount)
{
    char reversed[MAXTOK][TOKLEN];

    for (int i = 0; i < n; i++)
    {
        copyString(reversed[i], tokens[n - 1 - i]);
    }


    char stack[MAXTOK][TOKLEN];

    int top = -1;

    char temp[MAXTOK][TOKLEN];

    int tempCount = 0;


    for (int i = 0; i < n; i++)
    {
        if (isOperator(reversed[i]))
        {
            while (top >= 0)
            {
                copyString(temp[tempCount], stack[top]);

                tempCount++;
                top--;
            }

            top++;

            copyString(stack[top], reversed[i]);
        }
        else
        {
            copyString(temp[tempCount], reversed[i]);

            tempCount++;
        }
    }


    while (top >= 0)
    {
        copyString(temp[tempCount], stack[top]);

        tempCount++;
        top--;
    }

    outCount = 0;

    for (int i = tempCount - 1; i >= 0; i--)
    {
        copyString(output[outCount], temp[i]);

        outCount++;
    }
}


void printTokens(char tokens[][TOKLEN], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << tokens[i];

        if (i != n - 1)
            cout << " ";
    }

    cout << endl;
}


int main()
{
    int n;

    cout << "Enter number of terms n: ";
    cin >> n;


    char tokens[MAXTOK][TOKLEN];

    int count;


    createSeries(n, tokens, count);


    char postfix[MAXTOK][TOKLEN];
    char prefix[MAXTOK][TOKLEN];

    int postCount;
    int preCount;


    infixToPostfix(
        tokens,
        count,
        postfix,
        postCount
    );


    infixToPrefix(
        tokens,
        count,
        prefix,
        preCount
    );


    cout << "\nSeries: ";
    printTokens(tokens, count);

    cout << "Postfix: ";
    printTokens(postfix, postCount);

    cout << "Prefix: ";
    printTokens(prefix, preCount);


    return 0;
}
