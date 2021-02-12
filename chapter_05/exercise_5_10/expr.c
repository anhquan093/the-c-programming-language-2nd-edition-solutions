#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define STACK_SIZE 15

unsigned char stack_pointer = 0;
float stack[STACK_SIZE];

float pop(void);
void push(float element);

int main(int argc, char *argv[])
{
  char error = 0;

  unsigned int i = 1;
  for (i = 1; i < argc; ++i)
  {
    float number = atof(argv[i]);

    // TODO: Check for 0 vs "0" cornercase.
    if (number)
    {
      push(number);
    }
    else if (strlen(argv[i]) == 1)
    {
      float number2 = pop();
      float number1 = pop();

      char op = *argv[i];
      switch (op)
      {
      case '+':
        push(number1 + number2);
        break;

      case '-':
        push(number1 - number2);
        break;

      case '*': // This char might require to be escaped when passed as an argument.
        push(number1 * number2);
        break;

      case '/':
        if (number2 < 0)
        {
          error++;
        }
        else
        {
          push(number1 / number2);
        }
        break;

      default:
        error++;
        break;
      }
    }
    else
    {
      error++;
    }
  }

  if (error)
  {
    printf("ERROR: Arguments should be numbers or one of the following mathematical operations: '+', '-', '*', '/'\n");
  }
  else
  {
    printf("result: %.3f", pop());
  }

  return 0;
}

float pop(void)
{
  if (stack_pointer > 0)
  {
    return stack[stack_pointer--];
  }

  printf("ERROR: The stack is empty.\n");
  return 0;
}

void push(float element)
{
  if (stack_pointer < STACK_SIZE)
  {
    stack[++stack_pointer] = element;
  }
  else
  {
    printf("ERROR: The stack is full.\n");
  }
}