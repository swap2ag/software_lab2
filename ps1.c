#include<stdio.h>	
#include<stdlib.h>	// atoi


typedef unsigned int ui;
ui* findMinInRow(ui *arr,int n);
ui* findMaxInCol(ui *arr,int n);
ui* combineS1S2(ui* s1, ui* s2, int n);
ui isPrime(ui num);

int main(int argc, char* argv[])
{
	if(argc!=2)
	{
		printf("Wrong format!!\nPlease enter ./ps1 [size]\n");
		return -1;
	}

	int n = atoi(argv[1]);
	
	ui *A;
	A = (ui*)malloc(sizeof(ui)*n*n);


	for(int i=0; i<n; ++i)
	{
		for(int j=0; j<n; ++j)
		{
			scanf("%u",(A+i*n+j));
		}
	}
	
	// for(int i=0; i<n; ++i)
	// {
	// 	for(int j=0; j<n; ++j)
	// 	{
	// 		printf("%u ",*(A+i*n+j));
	// 	}
	// 	printf("\n");
	// }

	// find min in each row
	ui* s1 = findMinInRow((ui*) A,n);
	printf("S1 = ");
	for(int i=0; i<n; i++)
	{
		printf("%u ",s1[i]);
	}

	// find max in each row
	ui* s2 = findMaxInCol((ui*) A,n);

	printf("\nS2 = ");
	for(int i=0; i<n; i++)
	{
		printf("%u ",s2[i]);
	}

	// combine s1 and s2
	ui* s = combineS1S2(s1,s2,n);

	printf("\nS = ");
	for(int i=0; i<2*n; i++)
	{
		printf("%d ",s[i]);
	}

	// find prime numbers
	printf("\nPrime numbers in the set 'S': ");
	for(int i=0; i<2*n; i++)
	{
		if(isPrime(s[i]) == 1)
			printf("%d ",s[i]);
	}




	printf("\n");
	return 0;


}

ui* findMinInRow(ui* A,int n)
{

	ui *s1 = (ui*) malloc(n*sizeof(ui));
	int min;
	for(int i=0; i<n; i++)
	{
		min = *(A+i*n+0);
		for(int j=0; j<n; j++)
		{
			if(*(A+i*n+j) < min)
				min = *(A+i*n+j);
		}
		s1[i] = min;
	}

	return s1;
}

ui* findMaxInCol(ui* A,int n)
{

	ui *s2 = (ui*) malloc(n*sizeof(ui));
	int max;
	for(int j=0; j<n; j++)
	{
		max = *(A+0+j);
		for(int i=0; i<n; i++)
		{
			if(*(A+i*n+j) > max)
				max = *(A+i*n+j);
		}
		s2[j] = max;
	}

	return s2;
}

ui* combineS1S2(ui* s1, ui* s2,int n)
{
	ui* s = (ui*)malloc(n*2*sizeof(ui));
	
	int i;
	for(i=0; i<n; i++)
	{
		s[i] = s1[i];
	}

	int j=0;
	while(i<2*n)
	{
		s[i] = s2[j];
		i++;
		j++;
	}
	return s;
}

ui isPrime(ui num)
{
	if(num <= 1)
		return 0;
	else if(num == 2 || num == 3)
		return 1;
	else
	{
		for(ui i=2; i<num; ++i)
		{
			if(num % i == 0)
				return 0;
		}
	}
	return 1;
}