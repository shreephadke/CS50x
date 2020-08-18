#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    //initialization of variable for input
    long x = get_long("Number: ");
    long length = 0;
    long checksum = 0;
    long num = 0;

    for (long i = x; i > 0; i /= 10)
    {
        length++;
    }

    //printf("The number is %ld digits long\n", length);

    // if the number x is an even digits long
    if (length % 2 == 0)
    {
        // leftmost digit is multiplied by 2 and added to num; every other digit is then also multiplied and added
        for (long i = length; i > 0; i -= 2)
        {
            // example: x = 198, mod = 10^length(x) = 10^3 = 1000
            // div = mod/10 = 100
            // therefore, (198 % 1000)/100 = 1
            // num = 2 * 1
            long mod = powl(10, i);
            long div = mod / 10;
            num = 2 * ((x % mod) / div);

            // case for if the product of 2 and the digit is greater than or equal to 10
            // (separation and summation of digits is required)
            if (num >= 10)
            {
                long first = num / 10;
                long sec = num % 10;
                checksum += first + sec;
            }
            else
            {
                checksum += num;
            }
        }
    }


    // if the number x is an odd digits long
    else
    {
        /* the second to leftmost digit is multiplied by 2 and added to num; every other digit is then
        also multiplied and added */

        for (long i = length - 1; i > 0; i -= 2)
        {
            long mod = powl(10, i);
            long div = mod / 10;

            num = 2 * ((x % mod) / div);
            if (num >= 10)
            {
                long first = num / 10;
                long sec = num % 10;
                checksum += first + sec;
            }
            else
            {
                checksum += num;
            }

        }
    }

    // above is correct (debugging comment)

    // if and for statements for accumulating the un-multiplied digits for an even digit number
    if (length % 2 == 0)
    {
        for(long i = length - 1; i >= 0; i -= 2)
        {
            long mod = powl(10, i);
            long div = mod / 10;

            num = ((x % mod)/div);
            checksum += num;

        }
    }

    // if and for statements for accumulating the un-multiplied digits for an odd digit number
    else
    {
        for (long i = length; i > 0; i -= 2)
        {
            long mod = powl(10, i);
            long div = mod / 10;

            num = ((x % mod) / div);
            checksum += num;
        }

    }


    //printf("Checksum is %ld\n", checksum);

    // if the checksum is divisible by 10

    if (checksum % 10 == 0)
    {
        // if the length of the number is 15 digits

        if (length == 15)
        {

            // following statments are used to extract the first and second digits of each number
            // same method was used in extracting digits from before

            long mod1 = powl(10, length);
            long div1 = powl(10, length - 1);
            long div2 = powl(10, length - 2);
            long first = (x % mod1) / div1;
            long second = (x % div1) / div2;

            //printf("%ld", first);
            //printf("%ld", second);

            // AMEX cases: starts with 34 or 37

            if ((first == 3) && ((second == 4) || (second == 7)))
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }

        // if the length of the number is 16 digits

        else if (length == 16)
        {

            //printf("%ld\n", length);

            // following statments are used to extract the first and second digits of each number
            // same method was used in extracting digits from before
            long mod1 = powl(10, length);
            long div1 = powl(10, length - 1);
            long div2 = powl(10, length - 2);
            long first = (x % mod1) / div1;
            long second = (x % div1) / div2;

            //printf("%ld\n", first);
            //printf("%ld\n", second);

            // MASTERCARD cases: starts with 51, 52, 53, 54, or 55
            // VISA case1: starts with 4

            if ((first == 5) && ((second == 1) || (second == 2) || (second == 3) || (second == 4) || (second == 5)))
            {
                printf("MASTERCARD\n");
            }
            else if (first == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }

        // if the length of the number is 13 digits

        else if (length == 13)
        {

            // following statments are used to extract the first digit of each number
            // same method was used in extracting digits from before
            long mod1 = powl(10, length);
            long div1 = powl(10, length - 1);
            long first = (x % mod1) / div1;

            //printf("%ld", first);
            // VISA case2: starts with 4

            if (first == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }


}