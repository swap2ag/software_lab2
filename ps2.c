#include<stdio.h>	
#include<stdlib.h>	// atoi
#include<string.h>	// strcmp

struct members
{
	char name[100];
	float amt_paid;
	char purpose[100];
	float amt_to_pay;
	float contribution;
	float share;
	float multiplier;
};


void split_equally(struct members m[],int n);
void split_unequally(struct members m[],int n);

void split_by_perc(struct members m[],int n);
void split_by_shares(struct members m[],int n);

void init_default(struct members *m);
int find_mem_idx(struct members mem[],int n,char mem_name[]);
void disp_all_mem(struct members mem[],int n);
void final_calculations(struct members mem[],int n);

int main(int argc, char* argv[])
{

	if(argc != 2)
	{
		printf("Wrong format!!\nPlease enter ./ps2 [no. of members involved in trip]\n");
		return -1;
	}
	int n = atoi(argv[1]);
	struct members mem[n];
	int choice;
	printf("Input the names of Members: \n");

	for(int i=0; i<n; i++)
	{
		scanf("%s",mem[i].name);
		init_default(&mem[i]);
	}
	printf("Members added.\n");

	printf("\nStart adding the expenses: \n");

	int memIdx;
	char mem_name[100];
	int continue_flag = 0;
	scanf("%s",mem_name);
	fflush(stdin);
	
	while(strcmp(mem_name,"done") != 0)	
	{
		float amt_paid;
		char purpose[100];

		scanf("%f ",&amt_paid);
		fflush(stdin);
		scanf("%s", purpose);
//=================================================================
		printf("memname: %s\namt: %0.2f\npurpose: %s\n\n\n",mem_name,amt_paid,purpose);
//=================================================================

		memIdx = find_mem_idx(mem,n,mem_name);
		if(memIdx == -1)
		{
			printf("Invalid member\nEnter again:\n");
			continue_flag = 1;
		}
		else
			continue_flag = 0;

		if(continue_flag == 0)
		{
			mem[memIdx].amt_paid += amt_paid;
			strcpy(mem[memIdx].purpose,"");
			strcpy(mem[memIdx].purpose,purpose);
			printf("Record entered successfully!!!\n");
		}

		scanf("%s",mem_name);
	}

	printf("All Expenses Added!");
//=================================================================
	printf("\nDisplaying mem info: \n");
	disp_all_mem(mem,n);
//=================================================================

	printf("Choose your option:\n");
	printf("1. Split equally\n2. Split unequally\n3. Split by percentages\n4. Split by shares\n");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1: 
				split_equally(mem,n);
				break;
		case 2:
				split_unequally(mem,n);
				break;

		case 3: 
				split_by_perc(mem,n);
				break;

		case 4: 
				split_by_shares(mem,n);
				break;
		default:
				printf("Invalid option!!");
	}
	// disp_all_mem(mem,n);

	printf("\nFinal Calculations are\n");
	final_calculations(mem,n);
	printf("\n");

	return 0;
}

void init_default(struct members *m)
{
	m->amt_paid = 0.0;
	m->amt_to_pay = 0.0;
	strcpy(m->purpose,"");
	m->contribution = 0.0;
}

int find_mem_idx(struct members mem[],int n,char mem_name[])
{
	for(int i=0; i<n; i++)
	{
		if(strcmp(mem[i].name,mem_name) == 0)
			return i;
	}
	return -1;
}
void split_equally(struct members m[],int n)
{
	float total = 0.0;
	for(int i=0; i<n; i++)
	{
		total += m[i].amt_paid;
	}
	float split = total/n;
	// printf("split: %0.2f\n",split);
	for(int i=0; i<n; i++)
	{
		m[i].amt_to_pay = split - m[i].amt_paid;
		// printf("have to pay: %f\n",m[i].amt_to_pay);
	}

	// disp_all_mem(m,n);

}
void split_unequally(struct members m[],int n)
{
	printf("Enter contributions to total amount in terms of amount that has to be paid by ");
	for(int i=0; i<n; i++)
	{
		printf("%s ",m[i].name);
	}
	printf(": ");
	float contri_sum = 0.0;
	for(int i=0; i<n; i++)
	{
		scanf("%f",&m[i].contribution);
		contri_sum += m[i].contribution;
	}

	float total = 0.0;
	for(int i=0; i<n; i++)
	{
		total += m[i].amt_paid;
	}
	if(contri_sum != total)
	{
		printf("Error!!!\nPlease enter the amounts again!!\n");
		split_unequally(m,n);
	}
	else
	{
		for(int i=0; i<n; i++)
		{
			m[i].amt_to_pay = m[i].contribution - m[i].amt_paid;
		}
	}
	// disp_all_mem(m,n);

}
void split_by_perc(struct members m[],int n)
{
	printf("Enter contributions to total amount in terms of percentage that has to be paid by ");
	for(int i=0; i<n; i++)
	{
		printf("%s ",m[i].name);
	}
	printf(": ");

	float total_perc = 0.0;
	for(int i=0; i<n; i++)
	{
		scanf("%f",&m[i].share);
		total_perc += m[i].share;
	}
	if(total_perc != 100)
	{
		printf("Error!!!\nPlease enter the share percentages again!!\n");
		split_by_perc(m,n);
	}

	float total = 0.0;
	for(int i=0; i<n; i++)
	{
		total += m[i].amt_paid;
	}
	for(int i=0; i<n; i++)
	{
		m[i].amt_to_pay = m[i].share * total/100 - m[i].amt_paid;
	}

}
void split_by_shares(struct members m[],int n)
{
	printf("Enter contributions to total amount in terms of share for ");
	for(int i=0; i<n; i++)
	{
		printf("%s ",m[i].name);
	}
	printf(": ");
	for(int i=0; i<n; i++)
	{
		scanf("%f",&m[i].multiplier);
	}
	float total = 0.0;
	for(int i=0; i<n; i++)
	{
		total += m[i].amt_paid;
	}
	float split = total/n;
	for(int i=0; i<n; i++)
	{
		m[i].amt_to_pay = (split*m[i].multiplier - m[i].amt_paid);
		printf("have to pay: %f\n",m[i].amt_to_pay);
	}

}

void disp_all_mem(struct members mem[],int n)
{
	for(int i=0; i<n; i++)
	{
		printf("%s %0.2f %s %0.2f\n",mem[i].name, mem[i].amt_paid, mem[i].purpose,mem[i].amt_to_pay);
	}

}
void final_calculations(struct members mem[],int n)
{
	for(int i=0; i<n; i++)
	{
		if(mem[i].amt_to_pay < 0)
		{
			printf("%s will get back:\tRs. %0.2f\n",mem[i].name,mem[i].amt_to_pay*-1);
		}
		else
		{
			printf("%s has to pay:\tRs. %0.2f\n",mem[i].name,mem[i].amt_to_pay);
		}
	}
}