#include <Txlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

struct DataTest
{
    int numberTest;
    double a, b, c;
    double x1Expected, x2Expected;
    int numberRootsExpected;
};

const int INFINITEOFNUMBER = -1;

const int NOROOTS  =  0;
const int ONEROOT  =  1;
const int TWOROOTS =  2;
const int EROR     = -5;

const double EPS   =  0.00000000000000001;

int SquareSolver(double a, double b, double c, double* x1, double* x2);
int linearSolver(double b, double c, double* x1);
int AlgorithmSqrtSolver(double a, double b, double c, double* x1, double* x2);  //TODO rename *
int RunTests(struct DataTest);
void DataOutput(double x1, double x2, int numberRoots);
void DataInput(double* a, double* b, double* c);
void UnitTests();
int CompareNumberWithZero(double a);

int main()
{
    UnitTests();

    double a = NAN;
    double b = NAN;
    double c = NAN;

    DataInput(&a, &b, &c);
                                        // TODO: func                                         // TODO: invalid input and repeat input
    double x1 = NAN;
    double x2 = NAN;

    int numberRoots = SquareSolver(a, b, c, &x1, &x2);

    DataOutput(x1, x2, numberRoots);

    return 0;
}
int SquareSolver(double a, double b, double c, double* x1, double* x2)
{                                                                           // char* ptr = NULL;  == double x = NAN;
    assert(x1);
    assert(x2);

    assert(x1 != x2);
                                                                //assert(0)
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));                                          //read isfinite

    if (fabs(a) < EPS)                                          //TODO func
        return linearSolver(b, c, x1);
    else // a != 0
        return AlgorithmSqrtSolver(a, b, c, x1, x2);

 }

int linearSolver(double b, double c, double* x1)                            //TODO
{

    assert(x1);
    assert(isfinite(b));
    assert(isfinite(c));

    if (CompareNumberWithZero(fabs(b)))
    {
        if (CompareNumberWithZero(fabs(c)))
            return INFINITEOFNUMBER;            //TODO rename ***
        else   // c != 0
            return NOROOTS;
    }
    else // b != 0
    {
        if (CompareNumberWithZero(fabs(c)))
        {
            *x1 = 0;
            return ONEROOT;
        }

        else// c != 0
        {
            *x1 = -c/b;
            return 1;
        }
    }
}

int AlgorithmSqrtSolver(double a, double b, double c, double* x1, double* x2)
{
    assert(x1);
    assert(x2);

    assert(x1 != x2);

    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    double discriminant = b*b - 4*a*c;

        if (CompareNumberWithZero(fabs(discriminant)))
        {
            *x1 = *x2 = -b / (2 * a);

            if (CompareNumberWithZero(fabs(*x1)))
                *x1 = fabs(*x1);
                                            //TODO ***
            return ONEROOT;
        }
        else if (!CompareNumberWithZero(discriminant))
        {
            *x1 = (-b - sqrt(discriminant)) / (2 * a);
            *x2 = (-b + sqrt(discriminant)) / (2 * a);

            if (CompareNumberWithZero(fabs(*x1)))
                *x1 = fabs(*x1);

            return TWOROOTS;
        }
        else
            return NOROOTS;

    return NOROOTS;
}

int RunTests(struct DataTest number1)
{
    double x1 = 0;
    double x2 = 0;

    int numberRoots = SquareSolver(number1.a, number1.b, number1.c, &x1, &x2);

    if (fabs(numberRoots - number1.numberRootsExpected) > EPS || fabs(x1 - number1.x1Expected) > EPS || fabs(x2 - number1.x2Expected) > EPS)
        printf("EROR TEST %d, a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg \n"
               "x1Expected = %lg, x2Expected = %lg, numberRoots = %d, numberRootsExpected = %d \n", number1.numberTest, number1.a, number1.b, number1.c, x1, x2, number1.x1Expected, number1.x2Expected, numberRoots, number1.numberRootsExpected);

        return 0;
}

void DataOutput(double x1, double x2, int numberRoots)
{
    switch(numberRoots)
    {
        case NOROOTS: printf("Корней нет\n");
                break;

        case ONEROOT: printf("Один корень: x1 = %lg \n", x1 );
                break;

        case TWOROOTS: printf("Два корня: x1 = %lg и x2 = %lg \n", x1, x2);
                break;

        case INFINITEOFNUMBER: printf("Бесконечное количество корней \n");
                break;
        default: printf("EROR (Нечисловой ввод) \n");
    }
}

void DataInput(double* a, double* b, double* c)
{
    char ch;

    printf("Введите a, b, c: \n");

    while ((scanf("%lg %lg %lg", a, b, c )) != 3)
    {
        while (( ch = getchar()) != '\n')
            putchar(ch);

        printf(" - нечисловой ввод, повторите попытку ввода: \n");
    }
    if (isnan(*a) || isnan(*b) || isnan(*c))         //TODO isfinite
    {
        printf("Error\n");
        int numberRoots = EROR;                                       //assert();       //TODO  K&R буфер ввода и возможность повт ввода (D может гетчар)
    }
}

void UnitTests()
{
    const int AllTest = 4;

    struct DataTest data[AllTest] = {{.numberTest = 1, .a = 1, .b   = 0, .c  = -4, .x1Expected  = -2, .x2Expected = 2, .numberRootsExpected  = 2},
                                     {.numberTest = 2, .a = 1, .b   = -7, .c = 6, .x1Expected   = 1, .x2Expected  = 6, .numberRootsExpected  = 2},
                                     {.numberTest = 3, .a = 0.5, .b = 1, .c  = 0.5, .x1Expected = -1, .x2Expected = -1, .numberRootsExpected = 1},
                                     {.numberTest = 4, .a = 1, .b   = 10, .c = 25, .x1Expected  = -5, .x2Expected = -5, .numberRootsExpected = 1}};

    for (int i = 0; i < AllTest; i++)
        RunTests(data[i]);
}

int CompareNumberWithZero(double a)
{
    if (a < EPS)
        return 1;

    else
        return 0;
}

