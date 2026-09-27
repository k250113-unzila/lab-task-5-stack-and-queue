#include <iostream>
using namespace std;

#define MAX 100

// Operator stack
char operatorStack[MAX];
int operatorTop = -1;

// Value stack
double valueStack[MAX];
int valueTop = -1;


void pushOperator(char op)
{
    operatorTop++;
    operatorStack[operatorTop] = op;
}

char popOperator()
{
    char op = operatorStack[operatorTop];
    operatorTop--;

    return op;
}

char peekOperator()
{
    return operatorStack[operatorTop];
}



void pushValue(double value)
{
    valueTop++;
    valueStack[valueTop] = value;
}

double popValue()
{
    double value = valueStack[valueTop];
    valueTop--;

    return value;
}


// ---------------- PRECEDENCE ----------------

int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;

    if (op == '*' || op == '/')
        return 2;

    if (op == '^')
        return 3;

    return 0;
}

bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}


double power(double base, int exponent)
{
    double answer = 1;

    for (int i = 0; i < exponent; i++)
    {
        answer = answer * base;
    }

    return answer;
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



bool checkCondition(double x, char condition[])
{
    int i = 0;

    // Skip x
    i++;

    // Skip spaces
    while (condition[i] == ' ')
    {
        i++;
    }

    char firstOperator = condition[i];
    i++;

    char secondOperator = '\0';

    // Check for >= or <= or ==
    if (condition[i] == '=')
    {
        secondOperator = '=';
        i++;
    }

    // Skip spaces
    while (condition[i] == ' ')
    {
        i++;
    }

    // Read number
    double number = 0;

    while (isDigit(condition[i]))
    {
        number = number * 10 + (condition[i] - '0');
        i++;
    }


    // Check condition

    if (firstOperator == '>' && secondOperator == '=')
        return x >= number;

    if (firstOperator == '<' && secondOperator == '=')
        return x <= number;

    if (firstOperator == '>')
        return x > number;

    if (firstOperator == '<')
        return x < number;

    if (firstOperator == '=' && secondOperator == '=')
        return x == number;

    return false;
}


// ---------------- INFIX TO POSTFIX ----------------

void infixToPostfix(char infix[], char postfix[])
{
    operatorTop = -1;

    int i = 0;
    int j = 0;

    while (infix[i] != '\0')
    {
        char current = infix[i];


        // Ignore spaces
        if (current == ' ')
        {
            i++;
            continue;
        }


        // Number
        if (isDigit(current))
        {
            while (isDigit(infix[i]))
            {
                postfix[j] = infix[i];

                j++;
                i++;
            }

            postfix[j] = ' ';
            j++;

            continue;
        }


        // x
        if (current == 'x')
        {
            postfix[j] = 'x';
            j++;

            postfix[j] = ' ';
            j++;

            i++;

            continue;
        }


        // Opening bracket
        if (current == '(')
        {
            pushOperator(current);

            i++;
            continue;
        }


        // Closing bracket
        if (current == ')')
        {
            while (operatorTop >= 0 &&
                   peekOperator() != '(')
            {
                postfix[j] = popOperator();
                j++;

                postfix[j] = ' ';
                j++;
            }

            popOperator();

            i++;
            continue;
        }


        // Operator
        while (
            operatorTop >= 0 &&
            peekOperator() != '(' &&
            (
                precedence(peekOperator()) > precedence(current)
                ||
                (
                    precedence(peekOperator()) ==
                    precedence(current)
                    &&
                    current != '^'
                )
            )
        )
        {
            postfix[j] = popOperator();
            j++;

            postfix[j] = ' ';
            j++;
        }

        pushOperator(current);

        i++;
    }

    while (operatorTop >= 0)
    {
        postfix[j] = popOperator();
        j++;

        postfix[j] = ' ';
        j++;
    }

    postfix[j] = '\0';
}



double evaluatePostfix(char postfix[], double x)
{
    valueTop = -1;

    int i = 0;

    while (postfix[i] != '\0')
    {
        char current = postfix[i];


        // Ignore spaces
        if (current == ' ')
        {
            i++;
            continue;
        }


        // Number
        if (isDigit(current))
        {
            double number = 0;

            while (isDigit(postfix[i]))
            {
                number = number * 10
                       + (postfix[i] - '0');

                i++;
            }

            pushValue(number);

            continue;
        }


        // x
        if (current == 'x')
        {
            pushValue(x);

            i++;
            continue;
        }


      

        double second = popValue();
        double first = popValue();

        double answer = 0;


        if (current == '+')
            answer = first + second;

        else if (current == '-')
            answer = first - second;

        else if (current == '*')
            answer = first * second;

        else if (current == '/')
            answer = first / second;

        else if (current == '^')
            answer = power(first, (int)second);


        pushValue(answer);

        i++;
    }

    return popValue();
}



int main()
{
    char expression1[MAX];
    char expression2[MAX];

    char condition1[MAX];
    char condition2[MAX];

    char selectedExpression[MAX];
    char selectedCondition[MAX];

    char postfix[MAX];

    double x;


    // Input
    cout << "Enter Expression 1: ";
    cin.getline(expression1, MAX);

    cout << "Enter Condition 1: ";
    cin.getline(condition1, MAX);

    cout << "Enter Expression 2: ";
    cin.getline(expression2, MAX);

    cout << "Enter Condition 2: ";
    cin.getline(condition2, MAX);

    cout << "Enter x: ";
    cin >> x;



    if (checkCondition(x, condition1))
    {
        copyString(selectedExpression, expression1);
        copyString(selectedCondition, condition1);
    }
    else
    {
        copyString(selectedExpression, expression2);
        copyString(selectedCondition, condition2);
    }


    infixToPostfix(selectedExpression, postfix);


    double result = evaluatePostfix(postfix, x);

    cout << "\nThe program selects:\n";

    cout << "Condition: "
         << selectedCondition << endl;

    cout << "Expression: "
         << selectedExpression << endl;

    cout << "Postfix: "
         << postfix << endl;

    cout << "f(" << x << ") = "
         << result << endl;


    return 0;
}
