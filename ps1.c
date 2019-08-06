#include<stdio.h>	
#include<stdlib.h>	// atoi
#include<string.h>	//strcat

typedef unsigned int ui;
ui* findMinInRow(ui *arr,int n);
ui* findMaxInCol(ui *arr,int n);
ui* combineS1S2(ui* s1, ui* s2, int n);
ui isPrime(ui num);
int findSubStr(char* input_str, char* str);

int main(int argc, char* argv[])
{

	if(argc!=2)
	{
		printf("Wrong format!!\nPlease enter ./ps1 [size]\n");
		return -1;
	}

	
	int n = atoi(argv[1]);
	ui *A;
	char str[1024]={};
	char tmp_str[100];
	char input_str[1024];
	int firstIdx;

	A = (ui*)malloc(sizeof(ui)*n*n);

	for(int i=0; i<n; ++i)
	{
		for(int j=0; j<n; ++j)
		{
			scanf("%u",(A+i*n+j));
		}
	}
	
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

	// create string from set S
	for(int i=0; i<2*n; i++)
	{
		sprintf(tmp_str,"%u",s[i]);
		strcat(str,tmp_str);
	}

	printf("D = \"");
	for(int i=0; str[i]!='\0'; i++)
		printf("%c",str[i]);

	printf("\"\nEnter a Substring: ");
	scanf("%s",input_str);
	printf("You entered: %s\n",input_str);

	firstIdx = findSubStr(input_str, str);
	if(firstIdx != -1)
	{
		printf("First index for occurrence of substring is: %d\n",firstIdx);
	}
	else
	{
		printf("No substring matched\n");
	}

	// find local minima and maxima
	int local_minima_indices[n];
	int local_maxima_indices[n];
	int lmin_idx=0, lmax_idx=0, lmin_flag=0, lmax_flag=0;
	for(int i=1; i<2*n-1; i++)
	{
		if(s[i]<s[i+1] && s[i]<s[i-1])
		{
			local_minima_indices[lmin_idx] = i;
			lmin_flag = 1;
			lmin_idx++;
		}
		else if(s[i]>s[i-1] && s[i]>s[i+1])
		{
			local_maxima_indices[lmax_idx] = i;
			lmax_flag = 1;
			lmax_idx++;
		}
	}

	printf("Local minima indices: ");
	if(lmin_flag == 1)
	{
		for(int i=0; i<lmin_idx; i++)
		{
			printf("%d ",local_minima_indices[i]);
		}
	}
	else
	{
		printf("No local minima found!!\n");
	}

	if(lmax_flag == 1)
	{
		printf("\nLocal maxima indices: ");
		for(int i=0; i<lmax_idx; i++)
		{
			printf("%d ",local_maxima_indices[i]);
		}
	}
	else
	{
		printf("No local maxima found!!\n");
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

int findSubStr(char* input_str, char* str)
{
	int j = 0;
	int idx = -1;
	for(int i=0; i<= (strlen(str) - strlen(input_str)); i++)
	{
		for(j=0; j<strlen(input_str); j++)
		{
			if(str[i+j] != input_str[j])
			{
				break;
			}
		}
		if(j==strlen(input_str))
			idx = i;

	}

	return idx;
}
