#ifndef STACKMACHINE_H
#define STACKMACHINE_H

#define STACK_DEPTH 32
#define MEMORY_SIZE 256

#define CHARSET "0123456789" \
                "ABCDEFGHIJ" \
		"KLMNOPQRST" \
		"UVWXYZ.<>!" \
		"?'-+/* \n\0"

#define PSH_CST(x) *(++CSTPTR) = x
#define POP_CST    *(CSTPTR--)
#define INC_CST    ++(*CSTPTR)

#define CINSTR MEMORY[*CSTPTR]      /* Current instruction */
#define IMM    MEMORY[++(*CSTPTR)]  /* Immediate data */

#define PSH_DATA(x) *(++DATAPTR) = x
#define POP_DATA    *(DATAPTR--)
#define DATAHEIGHT  DATAPTR-DATASTACK+1  /* Height of stack */

#define DATATOP *DATAPTR
#define DATABEL *(DATAPTR-1)

typedef int8_t word_t;

static word_t MEMORY[MEMORY_SIZE];

static word_t CALLSTACK[STACK_DEPTH];
static word_t DATASTACK[STACK_DEPTH];

static word_t *DATAPTR = DATASTACK;
static word_t *CSTPTR  = CALLSTACK;

static word_t CODE[MEMORY_SIZE];

enum OP_CODES
{
    nop,
    hlt,
    psh,
    pop,
    dpl,
    swp,
    cyc,
    add,
    cmp,
    out,
    inp,
    cbr,
    ubr,
    crt,
    urt,
    wrt,
    lde
};

void loadIntoMemory(word_t program[], int proglen, word_t origin)
{
    MEMORY[0] = pop;
    if (origin > 0)
	origin--;
    for (int i = origin; i < proglen; i++)
	MEMORY[i+1] = program[i];
}

void printStack(void)
{
    printf("{");
    for (int i = 0; i < DATAHEIGHT; i++)
	printf(" %d ", DATASTACK[i]);
    puts("}");
}

void loadFromFile(FILE* fp)
{
    word_t ch, i;
    while ((ch = getc(fp)) != EOF)
    {
	if (ch == '|')
	    i++;
	else
	{
	    CODE[i]*=10; CODE[i] += ch - '0';
	}
    }
}

#endif
