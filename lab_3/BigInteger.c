#include "BigInteger.h"

// Funkcija, kuri sukuria BigInteger
BigInteger *createBigInteger()
{
    BigInteger *num = (BigInteger *)malloc(sizeof(BigInteger));
    (*num).head = NULL;
    return num;
}

void appendDigit(BigInteger *num, int value)
{
    Digit *newDigit = (Digit *)malloc(sizeof(Digit));
    newDigit->value = value;
    newDigit->next = NULL;

    // if tikrina, ar sarasas yra tuscias.
    // jei tuscias, naujas skaitmuo tampa pirmuoju saraso elementu.
    if (num->head == NULL)
    {
        num->head = newDigit;
    }
    // jei sarasas nera tuscias
    // sukurimas current kintamasis, kuris rodo i pirmaji elementa sarase

    else
    {
        Digit *current = num->head;

        // ciklas eina per visa sarasa, kol pasiekia paskutini elementa
        // kai randamas paskutinis, jo next rodykle yra nustatyta i newDigit
        // taip pridedamas skaitmuo prie saraso pabaigos
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = newDigit;
    }
}

BigInteger *createBigIntegerFromString(char *str)
{
    BigInteger *num = createBigInteger();
    // strlen apskaiciuoja eilutes ilgi, kuri buvo ivesta
    int len = strlen(str);

    for (int i = len; i > 0; i -= 2)
    {
        // sis kintamasis saugo 2 skaitmenu segmento reiksme
        int value;

        // if tikrina, ar liko vienas skaitmuo
        // tai yra reikalinga, nes koncertuoja simboli i jo skaitine reiksme
        // bei atima ascii '0' ir priskiria value
        if (i == 1)
        {
            value = str[0] - '0';
        }
        // jei yra 2 skaitmenys tai:
        // konvertuojamos reiksmes i skaitines vertes
        // bei jos yra sujungiamos i viena dvieju skaitmenu skaiciu
        else
        {
            value = (str[i - 2] - '0') * 10 + (str[i - 1] - '0');
        }
        appendDigit(num, value);
    }
    return num;
}

void printBigInteger(BigInteger *num)
{
    // spausdinimas sarasas is galo
    if (num->head == NULL)
    {
        printf("0\n");
        return;
    }

    // apverstas skaiciu spausdinimas
    Digit *current = (*num).head; // Pradeda nuo pirmojo skaitmens
    int values[100];
    int i = 0;

    while (current) // kol yra sk, tol suksis
    {
        values[i++] = current->value;
        current = current->next;
    }

    while (--i >= 0)
    {
        printf("%d", values[i]);
    }
}
BigInteger *addTwoBigIntegers(BigInteger *first, BigInteger *second)
{
    // sukuriamas naujas BigInteger objektas rezultatui saugoti
    BigInteger *result = createBigInteger();
    Digit *a = first->head;  // priskiriama pirmai BigInteger saraso galva
    Digit *b = second->head; // priskiriama antrai BigInteger saraso galva

    int carry = 0;
    int radix = RADIX;

    // kol bet kuri rodykle nera NULL arba yra skola, tol ciklas sukasi
    while (a != NULL || b != NULL || carry != 0)
    {
        int sum = carry;
        // jei pirma rodykle nera NULL
        if (a != NULL)
        {
            sum += a->value;
            a = a->next;
        }
        if (b != NULL)
        {
            sum += b->value;
            b = b->next;
        }

        // apskaiciuojama nauja skolos reiksme
        carry = sum / radix;

        // apskaiciuojama skaitmens reiksme, kai naudojamas radix
        sum %= radix;

        // skaitmuo yra pridedamas prie rezultato
        appendDigit(result, sum);
    }
    return result;
}

int getLength(BigInteger *num)
{
    // tikrina, ar skaicius nera tuscias
    if (num == NULL || num->head == NULL)
    {
        return 0;
    }

    int length = 0;
    Digit *current = num->head;

    // ciklas sukasi tol, kol yra skaitmenu
    while (current != NULL)
    {
        length++;
        current = current->next;
    }

    return length;
}

int compareBigIntegers(BigInteger *first, BigInteger *second)
{
    int ats = 0;

    // pirma palyginame ilgius, nes jei ilgesnis, tai ir didesnis
    int lengthFirst = getLength(first);
    int lengthSecond = getLength(second);

    if (lengthFirst > lengthSecond)
    {
        ats = 1;
        return ats;
    }
    else if (lengthFirst < lengthSecond)
    {
        return ats;
    }

    // jei ilgiai yra vienodi, pereinama prie sios dalies
    Digit *a = first->head;
    Digit *b = second->head;

    while (a != NULL)
    {
        if (a->value > b->value)
        {
            ats = 1;
            return ats;
        }
        else if (a->value < b->value)
        {
            ats = -1;
            return ats;
        }
        // pereinama prie kito skaitmens
        a = a->next;
        b = b->next;
    }

    return ats; // jei skaiciai yra vienodi
}

BigInteger *copyBigInteger(BigInteger *original)
{
    if (original == NULL)
    {
        return NULL;
    }

    BigInteger *copy = createBigInteger();
    Digit *current = original->head;

    while (current != NULL)
    {
        appendDigit(copy, current->value);
        current = current->next;
    }

    return copy;
}

BigInteger *subtractTwoBigIntegers(BigInteger *first, BigInteger *second)
{
    // sukuriamas naujas objektas, kuriame bus saugomas rezultatas
    BigInteger *result = createBigInteger();

    // rodo i pirmaji objekto skaitmeni
    Digit *a = first->head;
    Digit *b = second->head;

    // kintamasis skirtas skolai
    int borrow = 0;
    int radix = RADIX;

    while (a != NULL || b != NULL)
    {
        int valueA;
        if (a != NULL)
        {
            valueA = a->value;
        }
        else
        {
            valueA = 0;
        }

        int valueB;
        if (b != NULL)
        {
            valueB = b->value;
        }
        else
        {
            valueB = 0;
        }

        int diff = valueA - valueB - borrow;

        if (diff < 0)
        {
            diff += radix;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        appendDigit(result, diff);

        // jei nelygu NULL, pereina prie kito skaitmens
        if (a != NULL)
        {
            a = a->next; // Pereinama prie kito pirmojo BigInteger skaitmens
        }
        if (b != NULL)
        {
            b = b->next; // Pereinama prie kito antrojo BigInteger skaitmens
        }
    }

    return result;
}

int isZero(BigInteger *num)
{
    return (num->head == NULL || (num->head->value == 0 && num->head->next == NULL));
}

BigInteger *createBigIntegerFromInt(int value)
{
    BigInteger *num = createBigInteger();

    if (value < 0)
    {
        // jei reiksme neigiama, pavercia ja teigiama
        num->isNegative = 1;
        value = -value;
    }

    // jei reiksme yra nulis
    if (value == 0)
    {
        appendDigit(num, 0);
        return num;
    }

    while (value > 0)
    {
        // prideda paskutini skaitmeni prie objekto
        appendDigit(num, value % RADIX);
        value /= RADIX;
    }

    return num;
}

BigInteger *multiplyTwoBigIntegers(BigInteger *first, BigInteger *second)
{
    // tikrina, ar kuris nors is skaiciu yra nulis
    if (isZero(first) || isZero(second))
    {
        return createBigIntegerFromInt(0);
    }

    BigInteger *result = createBigInteger();

    Digit *a = first->head;

    // pozicijos polinkiui saugoti
    int shift = 0;

    while (a != NULL)
    {
        Digit *b = second->head;
        BigInteger *temp = createBigInteger();
        int carry = 0;

        for (int i = 0; i < shift; i++)
        {
            appendDigit(temp, 0);
        }

        // pereina prie sekancio skaitmens
        while (b != NULL)
        {
            int product = (a->value * b->value) + carry;
            // saugojimui likucio
            appendDigit(temp, product % RADIX);
            carry = product / RADIX;

            b = b->next;
        }

        // jei po ciklo dar lieka
        if (carry > 0)
        {
            appendDigit(temp, carry);
        }

        // prideda tarpinius rezultatus prie bendro
        result = addTwoBigIntegers(result, temp);

        shift++;
        a = a->next;
    }

    return result;
}

void freeBigInteger(BigInteger *num)
{
    // tikrina, ar jau iskart nera tuscias
    if (num == NULL)
    {
        return;
    }

    // pradeda nuo pradzios
    Digit *current = num->head;
    while (current != NULL)
    {
        Digit *next = current->next;
        free(current);
        // pereina prie kito
        current = next;
    }

    free(num);
}

double bigIntegerToDouble(BigInteger *bigInt)
{
    double result = 0.0;
    Digit *current = bigInt->head;
    int power = 0;

    while (current != NULL)
    {
        result += current->value * pow(10, power);
        power++;
        current = current->next;
    }

    return result;
}

double divideBigIntegers(BigInteger *dividend, BigInteger *divisor)
{
    // skaiciu konvertacija
    double dividendDouble = bigIntegerToDouble(dividend);
    double divisorDouble = bigIntegerToDouble(divisor);

    if (divisorDouble == 0.0)
    {
        printf("Error: Division by zero\n");
        return 0.0;
    }

    return dividendDouble / divisorDouble;
}
