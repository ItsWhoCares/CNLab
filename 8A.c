#include<stdio.h>
int z, n, m, e, d, c, flag;

void check()
{
    int i;
    for(i = 3; e % i == 0 && z % i == 0; i++)
    {
        flag = 1;
    }
    flag = 0;
}

void encrypt()
{
    int i;
    c = 1;
    for(i = 0; i < e; i++)
        c = c * m % n;
    c = c % n;
    printf("Encrypted keyword:%d", c);
}

void decrypt()
{
    int i;
    m = 1;
    for(i = 0; i < d; i++)
        m = m * c % n;
    m = m % n;
    printf("Decrypted  keyword:%d", m);
}

void main()
{
    int p, q, s;
    printf("Enter two relatively prime  numbers");
    scanf("%d%d", &p, &q);
    n = p * q;
    z = (p - 1) * (q - 1);
    printf("value of z=%d", z);
    printf("Enter the value of e");
    scanf("%d", &e);
    check();
    while(flag == 1)
        d = 1;
    do
    {	
        s = (d * e) % z;
        d++;
    }
    while(s != 1);
    d = d - 1;
    printf("Public key:{%d,%d}", e, n);
    printf("Private key:{%d,%d}", d, z);
    printf("Enter the plain text");
    scanf("%d", &m);
    encrypt();
    printf("Enter the cipher text");
    scanf("%d", &c);
    decrypt();	
}