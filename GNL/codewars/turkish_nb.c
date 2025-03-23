// char* getTurkishNumber(unsigned int n)
// {
// 	if (n / 10 > 1 && n / 10 < 2)
// 	{
// printf("on");
// 	}

// 	23 / 10 = 
// 	5 / 10 = 0
// 	10 / 10 = 1
// 	24 /10 = 2

// }
// write (1, &[123456789])



// 0 = sıfır
// 1 = bir
// 2 = iki
// 3 = üç
// 4 = dört
// 5 = beş
// 6 = altı
// 7 = yedi
// 8 = sekiz
// 9 = dokuz

// 10 = on
// 20 = yirmi
// 30 = otuz
// 40 = kırk
// 50 = elli
// 60 = altmış
// 70 = yetmiş
// 80 = seksen
// 90 = doksan
#include <unistd.h>

void putnbr(int n)
{
	int unit = n;

	char *array[] = {"sıfır", "bir", "iki", "üç", "dört", "beş", "altı", "yedi", "sekiz", "dokuz"};

	if (n < 9)
		write(1, &array[unit % 10], 1);
}

int main()
{
	int n = 5;
	putnbr(n);
	return 0;
}