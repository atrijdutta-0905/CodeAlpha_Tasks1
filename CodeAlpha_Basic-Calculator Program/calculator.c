#include<stdio.h>
#include<math.h>
int main()
{
double num1,num2,result;
int choice;
do {
printf("~~~Basic Calculator Program~~~\n");
printf("Select the mathematical operation you want to perform:\n 1.Addition\n 2.Subtraction\n 3.Multiplication\n 4.Division\n 5.Exit\n");
printf("Enter your choice no.(1,2,3,4,5):");
scanf("%d",&choice);
switch(choice){
case 1:
printf("Enter two numbers for addition:\n");
scanf("%lf %lf",&num1,&num2);
result=num1+num2;
printf("Result of addition is=%.2lf\n",result);
break;
case 2:
printf("Enter two numbers for subtraction:\n");
scanf("%lf %lf",&num1,&num2);
result=num1-num2;
printf("Result of subtraction is=%.2lf\n",result);
break;
case 3:
printf("Enter two numbers for multiplication:\n");
scanf("%lf %lf",&num1,&num2);
result=num1*num2;
printf("Result of multiplication is=%.2lf\n",result);
break;
case 4:
printf("Enter two numbers for division:\n");
scanf("%lf %lf",&num1,&num2);
if(num2!=0){
result=num1/num2;
printf("Result of division is=%.2lf\n",result);
}
else{
printf("Error(Division by zero is undefined)\n");
}
break;
case 5:
printf("Exiting the program.\n");
break;
default:
printf("Invalid choice\n");
break;
}                               
} while (choice != 5);
return 0;
}