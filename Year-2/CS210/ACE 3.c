/**************************************************************************
 *
 * Filename: ace3v1_2.c
 *
 * Synopsis: ace3v1_2
 *
 * Author:
 *      Cameron D G Drennan, Reg no: 201126086
 *
 * Group:
 *      Thu 10-12
 *
 * Promise: I confirm that this submission is all my own work.
 *
 *          (Signed)_____________________________________(Cameron Drennan)
 *
 *
 * Version: See VERSION below
 *
 *********************************************************************/

/********************* R E V I S I O N   H I S T O R Y ********************
 * 
 * v1.0  Renamed Duncan's p4sample.c to ace2v1_0.c. Personalised the code
 *		 by including my own details, version string and revision history.
 *		 I deleted Duncan's sample output and revision history. I also 
 *		 changed the opname for the jump instruction from "J" to "SW". I
 *		 then noticed that the store word instruction is of I-type so I 
 *		 changed the prints from j-type to i-type and I also notice that
 * 		 the instruction for "SW" is identical to the instruction for "LW"
 *		 in Duncan's sample output so i simply copied and pasted the
 *		 "print_" function "void print_i_type_mem" and duplicated the code
 *		 but renamed them "void print_i_type_mem" and "void print_i_type_SW".
 *		 I then realised this was stupid as I could just rename the opname
 *		 for the i-type instruction so this is what I did, and I deleted the
 *		 void print_i_type_SW function. I then deleted everything from the 
 *		 main function that printed out anything from "D.vi:" onwards. I 
 *		 then realised that we do not need the j-type or IEEE instructions
 *		 so I deleted every aspect of them and the FP fields.
 *
 * v1.1	 I created a #define "#define SW 2885681152" in order to help make
 *		 the store word instruction. I also found it necessary to create
 *		 "int  sw;	char *swbits; char *swname;" in the i-type typedef 
 *		 struct to help generate the correct bits in the init_ function. I
 *		 then created the "print_IF_ID" print function which prints the 
 *		 state of the IF/ID stage at the end of the 5th cycle. I wanted to
 *		 keep the r-type and i-type's separate from the pipeline states so
 *		 I created the "void print_pipeline" because I wanted to print the
 *		 pipeline states after the r&i-types without changing too much of 
 *		 the existing code. Therefore I called the pipeline print function
 *		 last in the main function. I changed the value if PC from 0X10000000
 *		 to 0X00000054 as it appears that Duncan has it as 0X00000054 in his
 *		 sample output. I continued to print out the IF/ID states using the 
 *		 sample output as a template as it appeared quite self explanatory.
 *		 I found the MIPS reference data which helped me realise how to 
 *		 encode the "aka $a2" part of the rs Sub-field of IF/ID.I. I was able
 *		 to create multiple if statements which printed out the correct 
 *		 register name and number for each Sub-field of IF/ID.I. I have now
 *		 completed the IF/ID state...now time for a new version.
 *
 * v1.2	 I plan to implement the ID/EX state as the same as the IF/ID state.
 *       I made the sll in the r-type typedef struct in order to generate the
 *		 sll instruction in binary notation. I also realised that with the 
 *		 sll instruction the rs field becomes zero. But instead of changing 
 *		 rs to zero I just selected the bit 0-21, then made it into a 32
 *		 bit number which generated the correct instruction in binary. I then
 *		 created the remaining pipeline registers which was pretty straight
 *		 to be honest. I did come across one problem when trying to create
 *		 a function which returns an array of char (String) as it was really
 *		 messy and complex. So naturally I set up a meeting with Duncan and
 *		 he told me it was shite and he helped me out by directing me to the
 *		 ace2 sample solution which contained an efficient way of returning 
 *		 a String. I called this array "regname_str" and I use it to search 
 *		 the index of a register and get the aka register name for the value.
 *		 Another tricky bit was trying to get the binary string and value for
 *		 the add instruction because in an ADD instruction "Shamt"=0 and 
 *		 "Funct" gets 100000 while the opcode remains 0. Which is a bit of a
 *		 motherfucker if you ask me. It was all very well masking the bits 
 *		 at the beginning and end of the binary string but trying to get rid
 *		 of bits in the middle was a pain in the ass. I managed to do it and
 *		 I wrote a lengthy comment next to the code involved (you'll find it 
 *		 easily in the init_ function). Oh yeah I changed the PC value to 
 *		 0X00000040 as this is what it said in the specification. I was being 
 *		 retarded before and I didn't realise that the PC at the end of the 5th
 *		 cycle in the IF/ID is the PC being incremented by 4 each cycle so it
 *		 became (4*5) + PC, and the ID/EX at that stage had only went 4 cycles,
 *		 so the PC is (4*4) + PC and so on. I decided to #define ten and two,
 *		 just so my code was easy to maintain and is more flexible. The rest
 *		 of the code that I haven't mentioned was easy it was more the hassle 
 *		 of looking up the MIPS reference sheet to see where each number comes
 *		 from that was time consuming but all in all, I only really needed 3 
 *		 versions. Added sample output for marking. Made a function which 
 *		 returns the initial value of the register input called "reg_plus_ten".
 *		 I decided to make functions for the PC calculator and to calculate the
 * 		 registers initial value. 
 *
 **************************************************************************/
#define VERSION "ace3v1_2 V1.2  by Cameron Drennan. Last Update 02/02/2014\n"
#define USAGE "Usage: %s <regNo>\n",argv[0]

#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/* #include "ace3v1_2.c */

#if SHRT_MAX == 2147483647
typedef unsigned short int uint32_t;
#elif INT_MAX == 2147483647
typedef unsigned int uint32_t;
#elif LONG_MAX == 2147483647
typedef unsigned long uint32_t ;
#elif LLONG_MAX == 2147483647
typedef unsigned long long uint32_t;
#else
#error "Cannot find 32bit integer."
#endif

/* The following #defines are the opcode values for each of the 
   MIPS instructions used in this program. 
   ie. store word (SW) = 43 (decimal) 101011 (binary)
	   But we can't just add 43 to the value of the bits from 0-25
       we need to add (2^26 + 2^27 + 2^29 + 2^31) instead in order 
	   to retrieve the SW instruction in binary notation.
*/
#define SW 2885681152
#define ADDIU 603979776

/*This ADD is different. Because the ADD opcode is 000000 it uses 
the funct field instead which has the binary value 100000. Which is
2^5....32.*/
#define ADD 32
#define LW 2348810240

/*The two is just used when shifting bits by 2. It makes it easy to 
change if for any reason you wanted to shift by another number.*/
#define two 2

/* On some systems an UINT32_MAX is already defined, if not... */
#ifndef UINT32_MAX
#define UINT32_MAX ((uint32_t)-1)
#endif

/* Note on the following #define suffix nomenclature:
   _L = Least significant bit position of the field
   _M = Most significant bit position of the field
   _SZ = Size of the field
*/
/* Fields in the lower 16 bits of the MIPS instruction format: */ 
/* I-type field in lower 16 bits */
#define I_L 0
#define I_M 15
#define I_SZ ((I_M-I_L)+1)

/* R-type fields in lower 16 bits */
/* Function */
#define FN_L 0
#define FN_M 5
#define FN_SZ ((FN_M-FN_L)+1)
/* Shamt - shift amount */
#define SH_L 6
#define SH_M 10
#define SH_SZ ((SH_M-SH_L)+1)
/* Register RD */
#define RD_L 11
#define RD_M 15

/* Fields in the upper 16 bits of the MIPS instruction format: */ 
/* I-type and R-type share a commmon set of fields in the upper 16 bits */
/* Register RT */
#define RT_L 16
#define RT_M 20
/* Register RS */
#define RS_L 21
#define RS_M 25
/* Registers RD, RT and RS are all the same size */
#define R_SZ ((RD_M-RD_L)+1)

/* Opcode is in the top 6 bits for _all_ instructions */
#define OP_L 26
#define OP_M 31
#define OP_SZ ((OP_M-OP_L)+1)

/* This is the function which is used to get the register name. It is an array
   of characters containing all the register name possibilities in order. It is used in
   multiple print statement where I pass in the register number as an index and
   it returns the String (character array) corresponding to that register.
*/
char *regname_str[32] = {
	"zero",
	"at",
	"v0","v1",
	"a0","a1","a2","a3",
	"t0","t1","t2","t3","t4","t5","t6","t7",
	"s0","s1","s2","s3","s4","s5","s6","s7",
	"t8","t9",
	"k0","k1",
	"gp",
	"sp",
	"fp",
	"ra"
};

/* This function works out the initially register value i.e. register + 10.
   When the rs field is 0 then we need not bother adding 10 to it, otherwise 
   add 10 to the register value. This is inorder to comply with the specification 4.2.*/
int reg_plus_ten(int regi) {
  int regiVal = 0;
  if (regi == 0) {
	return regiVal;
  }
  else {
	regiVal = (regi + 10);
	return regiVal;
  }
}

/* The following structs represent the fields in the various MIPS instructions.
   The members of the struct include:
   - the 32-bit representation of the instruction in the .in member
   - the contents of the field as an integer value, e.g. 14 in .rs
   - the (pointer to the) corresponding bit string, e.g. &"01110" in .rsbits
   - the (pointer to the) name/label of the field, e.g. &"RS" in .rsname
*/
     
typedef struct { /*R-TYPE*/
  uint32_t in;
  int  op; char *opbits; char *opname; /*op = opcode*/
  int  rs; char *rsbits; char *rsname; /*rs = RS*/
  int  rt; char *rtbits; char *rtname; /*rt = RT*/
  int  rd; char *rdbits; char *rdname; /*rd = RD*/
  int  sh; char *shbits; char *shname; /*sh = Shamt*/
  int  fn; char *fnbits; char *fnname; /*fn = Funct*/ 
  int  sll;char *sllbits;char *sllname; /*sll = SLL instruction*/
  int  add;char *addbits;char *addname; /*add = ADD instruction*/
  int  addRDM; 							/*addRDM = ADD read data mem*/
} mips_rtype_t; /*R-TYPE*/

typedef struct { /*I-TYPE*/
  uint32_t in;
  int  op; 			char *opbits; 		char *opname; /*op = opcode*/
  int  rs; 			char *rsbits; 		char *rsname; /*rs = RS*/
  int  rt; 			char *rtbits; 		char *rtname; /*rt = RT*/
  int  immediate; 	char *ibits;  		char *iname; /*immediate = immediate*/
  int  sw;			char *swbits; 		char *swname; /*sw = Store Word instruction*/
  int  swop;		char *swopbits;					 /*swop = Store Word Opcode*/
  int  addiu;		char *addiubits;	char *addiuname; /*addiu = Add Immediate Unsigned instruction*/
  int  lw;			char *lwbits;		char *lwname; /*lw = Load Word instruction*/
} mips_itype_t; /*I-TYPE*/

/* The following is a macro that 'extracts' from the bits passed in the 
   value of the field of size bit_sz that begins at bit position bit_l.
 */
#define IN(bits,bit_l,bit_sz) ((bits >> bit_l) & ((1 << bit_sz) - 1))

/* The PC value as stipulated in the specification */
#define PC 0X00000040

/* PCcalculator Calculates the PC for each instruction at the end of the 5th cycle.
   This function had to be placed after the #define of PC in the program. */
int PCcalculator(int loop) {
  int calculatedPC = PC;
  int i = 0;
  while(i<loop) {
    calculatedPC = calculatedPC + 4;
	i++;
  }
  return calculatedPC;
}

/* Start of the actual code */

/* Synopsis:
 * #include <ctype.h>
 * int isnumeric(char *s)
 *
 * Description:
 * A convenience function similar to isdigit() except that it works for
 * strings rather than single characters.  
 *
 * Returns:
 * The same result as isdigit()
 */
int isnumeric(char *s) {
    int result;    /* Current isdigit() return value */
    do                           /* Check that each character of the...*/
        result = isdigit((int)*s++) ;  /* ...string is a digit and move on...*/
    while (result && *s) ;       /* ...until non-digit found or at EOS */
    return result;  /* Return result of last isdigit() call */
}

/* Synopsis:
 * uint32_t strtouint32(const char * restrict s,int base)
 *
 * Description:
 * Converts a string into an uint32_t (32 bit unsigned) integer value. 
 * A conversion function in the style of strtol(). The character string s is
 * interpreted as a numeral to the base specified by the second parameter base.
 * The string should only contain digits between 0 and 9 even though the
 * the base can be >10. This restriction is allowed since only 9 digit
 * student registration numbers are expected to be converted. If the input
 * string is not a valid numeral then the return value is UINT32_MAX.
 *
 * Returns:
 * The numeric value of the string or UINT32_MAX if string isn't numeric
 */
uint32_t strtouint32(char *s,int base) {
    uint32_t result = 0;
    if (!isnumeric(s))    /* Basic sanity check on input string */
      return(UINT32_MAX); /* UINT32_MAX uses as error indicator */
    while (*s)
        result = (result * base) + ((*s++) - '0'); /* Convert */
    return (result);
}

/* Synopsis:
 * #include <stdlib.h>
 * char* bitstostr (uint32_t bits, int size, int split)
 *
 * Description:
 * Converts the first parameter into a character string that contains the
 * bit pattern equivalent of the internal representation of the integer.
 * The second parameter is the number of bits to be inserted into the string.
 * The third parameter determines the number of bits to be grouped together.
 * A value of 0 for split means that no splitting is to take place. Non-zero
 * values for split cause a space to be inserted into the string after split
 * bits have been inserted.
 *
 * Returns:
 * The return value is a pointer to the (dynamically allocated) string of bits.
 * However, if the string cannot be allocated, it returns a pointer to the
 * "Calloc Failed" error string. This is rather a kludge since calloc is not
 * expected to fail and so the user may assume it succeeds and won't bother
 * checking the return result. Better error reporting/handling is left as an
 * exercise to the reader!
 */
char* bitstostr (uint32_t bits, int size, int split) {
    char *bitsPtr;  /* Pointer to the bit string being built */
    int stringsize, /* (Maximum) Size of the string that's required */
        splitter;   /* Countdown count until a splitting space insertion */ 
    stringsize = (split)?size+size/split:size; /* Calculate size with splits */
    splitter = split; /* Initialise countdown to a splitting space insertion */
    /* Now we know the maximum number of characters needed calloc() them. */  
    if (NULL == (bitsPtr = calloc(stringsize+1,sizeof(char))))
      return("Calloc Failed"); /* Left as an exercise for future improvement */
    /* We now have our array initialised to '\0's so no need to plant an EOS */ 
    bitsPtr += stringsize; /* String is built in reverse so start at the end */
    /* Now perform the conversion. The (bits&1) mask is used to pick off the
     * lowest bit of the number.
     */
    for (  ; size-- ; bits >>= 1) { /* Keep shifting bits down until all done */
        *--bitsPtr = (bits&1)?'1':'0';    /* (Back)Fill string with 1s and 0s */
        if (splitter > 0)          /* Do the bits get split up into groups?   */
          if (0 == (--splitter)) { /* if so do we split them this time round? */ 
            *--bitsPtr = ' ';      /* Yes, so insert a space into the string  */
            splitter = split;      /* ...and reset the split countdown count. */
          }
    }
    if (' ' == *bitsPtr) ++bitsPtr; /* Skip any leading space */
    return(bitsPtr);
}

/* The following init_? functions initialise the appropriate members of the
   data structure with the values derived from the first parameter - bits.
   The second parameter in each function is a pointer to the data structure.
   The semantics of each function should be self-explanatory ;)
*/
 
void init_rtype(uint32_t bits, mips_rtype_t *rtype) { 
  rtype->in = bits;
  rtype->op = IN(bits,OP_L,OP_SZ);
  rtype->opbits = bitstostr(rtype->op,OP_SZ,0);
  rtype->rs = IN(bits,RS_L,R_SZ);
  rtype->rsbits = bitstostr(rtype->rs,R_SZ,0);
  rtype->rt = IN(bits,RT_L,R_SZ);
  rtype->rtbits = bitstostr(rtype->rt,R_SZ,0);
  rtype->rd = IN(bits,RD_L,R_SZ);
  rtype->rdbits = bitstostr(rtype->rd,R_SZ,0);
  rtype->sh = IN(bits,SH_L,SH_SZ);
  rtype->shbits = bitstostr(rtype->sh,SH_SZ,0);
  rtype->fn = IN(bits,FN_L,FN_SZ);
  rtype->fnbits = bitstostr(rtype->fn,FN_SZ,0);
  rtype->sll = IN(bits,0,21);
  rtype->sllbits = ((bitstostr((rtype->sll),32,0)));
  rtype->add = IN((bits-(rtype->sh*64)),0,25); 			
  rtype->addbits = ((bitstostr((ADD+rtype->add),32,0)));
  /*The opcode for ADD is 000000. So we can just not bother reading
    The first 6 bits as this will be come 000000 hence the "0,25" in rtype->add.
    We don't want the bits in the shamt field hence why I take it away from the bits
    input. But we need to multiply the shamt value by 2^6 (64) because the shamt field are
	bits 10-6. The bits 5-0 are the funct so I guess in a way multiplying the rtype->sh
	by 64 is like shifting the bits by 6. Then we can generate the 32 bit number by
	adding the funct value of ADD (100000(2), 32(10)) to the rtype->add value to generate
	the correct instruction in binary. The funct bits are at the end of the binary string,
	so there is no need to shift the funct bits.
  */
  rtype->addRDM = IN((ADD+rtype->add),0,15);
  /*So this addRDM generates the value needed for the add, readDataMem in the MEM/WB stage.
	It does this by casting the bits needed for the add instruction, then masks it to the 
	bits 0-15.
  */
  return; 
  }

void init_itype (uint32_t bits,mips_itype_t *itype) {
  itype->in = bits;
  itype->op = IN(bits,OP_L,OP_SZ);
  itype->opbits = bitstostr(itype->op,OP_SZ,0); 
  itype->rs = IN(bits,RS_L,R_SZ);
  itype->rsbits = bitstostr(itype->rs,R_SZ,0);
  itype->rt = IN(bits,RT_L,R_SZ);
  itype->rtbits = bitstostr(itype->rt,R_SZ,0);
  itype->immediate = IN(bits,I_L,I_SZ);
  itype->ibits = bitstostr(itype->immediate,I_SZ,0);
  itype->sw = IN(bits,0,25);
  itype->swbits = ((bitstostr((SW+itype->sw),32,0)));
  itype->swop = IN(SW,26,6);
  itype->swopbits = bitstostr((SW+itype->swop),6,0);
  itype->addiu = IN(bits,0,25);
  itype->addiubits = ((bitstostr((ADDIU+itype->addiu),32,0)));
  itype->lw = IN(bits,0,25);
  itype->lwbits = ((bitstostr((LW+itype->lw),32,0)));
  return;
}

/* A wrapper function for all the data structures to be initialsed */ 
void init_all_types(uint32_t bits,
                    mips_rtype_t *rtype,
                    mips_itype_t *itype) {
  init_rtype(bits,rtype);
  init_itype(bits,itype);
  return;
}

/* The following print_? functions are really just wrappers round the
   printf()s. This is intended to be a help when (in no particular order):
   - reading the code
   - understanding the code
   - maintaining the code
   - adapting the code
*/

void print_rtype (mips_rtype_t *rtype) {
  printf("R-Type fields:\t+ %6s + %5s + %5s + %5s + %5s + %6s +\n",
                     rtype->opname,
                           rtype->rsname,
                                 rtype->rtname,
                                       rtype->rdname,
                                             rtype->shname,
                                                   rtype->fnname);
  printf("\tBits:\t| %s | %s | %s | %s | %s | %s |\n",
             rtype->opbits,
                  rtype->rsbits,
                       rtype->rtbits,
                            rtype->rdbits,
                                 rtype->shbits,
                                      rtype->fnbits);
  printf("\tValues:\t+ %6d + %5d + %5d + %5d + %5d + %6d +\n",
                rtype->op,
                      rtype->rs,
                            rtype->rt,
                                  rtype->rd,
                                        rtype->sh,
                                              rtype->fn);
}

void print_itype (mips_itype_t *itype) {
  printf("I_Type fields:\t+ %6s + %5s + %5s + %16s +\n",
         itype->opname,
			 itype->rsname,
				 itype->rtname,
					 itype->iname);
  printf("\tBits:\t| %s | %s | %s | %s |\n",
         itype->opbits,
			 itype->rsbits,
				 itype->rtbits,
					 itype->ibits);
  printf("\tValues:\t+ %6d + %5d + %5d + %11hd(dec) +\n",
         itype->op,
			 itype->rs,
				 itype->rt,
					 (short)itype->immediate);
}

void print_all_types(mips_rtype_t *rtype,
                     mips_itype_t *itype) {
  print_rtype(rtype);
  print_itype(itype);
  return;
}

/* The following print_? functions just format the instructions as they
   would appear in MIPS assembly language.
*/
void print_i_type_mem(mips_itype_t *itype) { /* Load/Store instructions */
  printf("%s\t$%d,%hd($%d)\n",
          itype->opname,itype->rt,(short)itype->immediate,itype->rs);
  return;
}

void print_i_type_alu(mips_itype_t *itype) { /* I-type ALU instructions */
  printf("%s\t$%d,$%d,%hd\n",
         itype->opname,itype->rt,itype->rs,(short)itype->immediate);
  return;
}

void print_r_type_shift(mips_rtype_t *rtype) { /* R-type shift instructions */
  printf("%s\t$%d,$%d,%d\n",
         rtype->opname,rtype->rd,rtype->rt,rtype->sh);
  return;
}

void print_r_type(mips_rtype_t *rtype) { /* R-type ALU instructions */
  printf("%s\t$%d,$%d,$%d\n",
         rtype->opname,rtype->rd,rtype->rs,rtype->rt);
  return;
}

/* The following print_? functions show the state of the pipeline registers at the
   end of the 5th cycle in the MIPS pipeline.
*/

void print_IF_ID (mips_itype_t *itype, mips_rtype_t *rtype) { /* IF/ID pipeline register */
/* 
   This int IF_ID_PC is the PC for this stage of the pipeline at the end of
   the 5th cycle. PC is incremented by 4 in the IF stage and it is this PC+4 
   value that is passed down the pipeline, so to get the value after the 5th 
   cycle we must add 4 onto the PC 5 times by using the PCcalculator function.
*/
  int IF_ID_PC = PCcalculator(5);
  printf("\nIF/ID\n");
  printf("\nIF/ID state at the end of the 5th cycle:\n");
  printf("Instruction (in assembly language) is : %s $%d,%hd($%d)\n",
		 itype->swname,
			 itype->rt,
				 (short)itype->immediate,
					 itype->rs);
  printf("Instruction (in binary notation) is : %s\nInstruction (in hexadecimal) is : 0x%08X\n\n", 
		 itype->swbits,
			 (int)((itype->sw) + SW));
  printf("IF/ID.PC:32 = %d\nIF/ID.I:32 = 0x%08X\n", 
		 IF_ID_PC,
			 (int)((itype->sw) + SW));
  printf("Sub-fields of IF/ID.I are:\n");
  printf("IF/ID.I:[31-26] (opcode) = %s [%d(ten)]\n",
		 itype->swopbits,
			 itype->swop);
  printf("IF/ID.I:[25-21] (rs) = %s [$%d aka $%s]\n", 
		 itype->rsbits,
			 itype->rs,
				 regname_str[itype->rs]);
/* This here: regname_str[itype->rs]. Refers to the regname_str function. It is an array of characters.
   I have passed in the rs register value as the array index so it looks up the array at that index, finds
   what string in there and returns it so I can then print it out. I use this function another twice below.*/				 
  printf("IF/ID.I:[20-16] (rt) = %s [$%d aka $%s]\n",
		 itype->rtbits,
			 itype->rt,
				 regname_str[itype->rt]);
  printf("IF/ID.I:[15-11] (rd) = %s [$%d aka $%s]\n",
		 rtype->rdbits,
			 rtype->rd,
				 regname_str[rtype->rd]);
  printf("IF/ID.I:[10-6] (shamt) = %s [%d(ten)]\n",
		 rtype->shbits,
			 rtype->sh);
  printf("IF/ID.I:[5-0] (funct) = %s [%d(ten)]\n",
		 rtype->fnbits,
			 rtype->fn);
  printf("IF/ID.I:[15-0] (const) = %s [%d(ten)]\n",
		 itype->ibits,
			 itype->immediate);
}

void print_ID_EX (mips_itype_t *itype, mips_rtype_t *rtype) { /* ID/EX pipeline register */
/* To get the value after the 5th 
   cycle we must add 4 onto the PC 4 times.
*/
  int ID_EX_PC = PCcalculator(4);
  printf("\nID/EX\n");
  printf("\nID/EX state at the end of the 5th cycle:\n");
  printf("Instruction (in assembly language) is : %s $%d,$%d,%d\n",
		 rtype->sllname,
			 rtype->rd,
				 rtype->rt,
					 rtype->sh);
  printf("Instruction (in binary notation) is : %s # Note: rs defaults to $0\nInstruction (in hexadecimal) is : 0x%08X\n\n", 
		 rtype->sllbits,
			 (int)(rtype->sll));
  printf("ID/EX.PC:32 = %d\n", ID_EX_PC);
  printf("ID/EX.readData1:32 = %d (or 0 (zero)) ($%d contains %d (or $0 contains 0))\n", 
		 reg_plus_ten(rtype->rs),
			 rtype->rs,
				 reg_plus_ten(rtype->rs));
  printf("ID/EX.readData2:32 = %d ($%d contains %d)\n",
		 reg_plus_ten(rtype->rt),
			 rtype->rt,
				 reg_plus_ten(rtype->rt));
  printf("ID/EX.SEConstant:32 = %d (0x%08X) (sign extended IF/ID.I:[15-0])\n",
		 itype->immediate,
			 itype->immediate);
  printf("Note: SEConstant:[15-11] = %d [rd]\n", rtype->rd);
  printf("Note: SEConstant:[10-6] = %d [shamt]\n", rtype->sh);
  printf("Note: SEConstant:[5-0] = %d [funct]\n", rtype->fn);
  printf("ID/EX.rtIndex:5 = %d (from IF/ID.I:[20-16])\n", itype->rt);
}

void print_EX_MEM (mips_itype_t *itype) { /* EX/MEM pipeline register */
/* zeroBit is used for the if statement for ALUzero. */
  int zeroBit;
/* To get the value after the 5th 
   cycle we must add 4 onto the PC 3 times.
*/
  int EX_MEM_PC = PCcalculator(3);
  printf("\nEX/MEM\n");
  printf("\nEX/MEM state at the end of the 5th cycle:\n");
  printf("Instruction (in assembly language) is : %s $%d,$%d,%d\n",
		 itype->addiuname,
			 itype->rt,
				 itype->rs,
					 itype->immediate);
  printf("Instruction (in binary notation) is : %s\nInstruction (in hexadecimal) is : 0x%08X\n\n", 
		 itype->addiubits,
			 (int)((itype->addiu) + ADDIU));
  printf("EX/MEM.BTA:32 = %d ((%d << 2) + %d) [0x%08X]\n", /* We shift left by 2 because we want to x4 */
		 (int)(((itype->immediate) << two) + EX_MEM_PC),
			 itype->immediate,
				 EX_MEM_PC,
					 (((itype->immediate) << two) + EX_MEM_PC));
  printf("EX/MEM.ALUResult:32 = %d (%d + %d) [0x%08X]\n",
		 (itype->immediate) + (reg_plus_ten(itype->rs)),
			 itype->immediate,
				 reg_plus_ten(itype->rs),
					 ((itype->immediate) + (reg_plus_ten(itype->rs))));
/* Below is the condition to whether the ALUZero bit equals 0 or 1.*/
  if (((itype->immediate) + (reg_plus_ten(itype->rs))) == 0) {
	zeroBit = 1;
  }
  else {
	zeroBit = 0;
  }
  printf("EX/MEM.ALUZero:1 = %d\n", zeroBit);
  printf("EX/MEM.writeDataMem:32 = %d ($%d contains %d)\n",
		 reg_plus_ten(itype->rt),
			 itype->rt,
				 reg_plus_ten(itype->rt));
  printf("EX/MEM.writeRegister:5 = %d\n", itype->rt);
}

void print_MEM_WB (mips_itype_t *itype, mips_rtype_t *rtype) { /* MEM/WB pipeline register */
  printf("\nMEM/WB\n");
  printf("\nMEM/WB state at the end of the 5th cycle:\n");
  printf("Instruction (in assembly language) is : %s $%d,$%d,$%d\n",
		 rtype->addname,
			 rtype->rd,
				 rtype->rs,
					 rtype->rt);
  printf("Instruction (in binary notation) is : %s\nInstruction (in hexadecimal) is : 0x%08X\n\n", 
		 rtype->addbits,		
			 (int)((rtype->add) + ADD));
  printf("MEM/WB.ALUResult:32 = %d (%d + %d) [0x%08X]\n",
		 ((reg_plus_ten(rtype->rs)) + (reg_plus_ten(rtype->rt))),
			 reg_plus_ten(rtype->rs),
				 reg_plus_ten(rtype->rt),
					 ((reg_plus_ten(rtype->rs)) + (reg_plus_ten(rtype->rt))));
  printf("MEM/WB.readDataMem:32 = %d (%d * 4) [0x%08X]\n",
		 (int)((rtype->addRDM) << two),
			 (int)(rtype->addRDM),
				 ((int)(rtype->addRDM) << two));
  printf("MEM/WB.writeRegister:5 = %d\n", rtype->rd);
}

void print_WB (mips_itype_t *itype) { /* WB pipeline register */
  printf("\nWB\n");
  printf("\nWB state at the end of the 5th cycle:\n");
  printf("Instruction (in assembly language) is : %s $%d,%d($%d)\n",
		 itype->lwname,
			 itype->rt,
				 itype->immediate,
					 itype->rs);
  printf("Instruction (in binary notation) is : %s\nInstruction (in hexadecimal) is : 0x%08X\n\n", 
		 itype->lwbits,		
			 (int)((itype->lw) + LW));
  printf("WB.ALUResult:32 = %d (%d + %d) [0x%08X]\n",
		 ((itype->immediate) + (reg_plus_ten(itype->rs))),
			 itype->immediate,
				 reg_plus_ten(itype->rs),
					 ((itype->immediate) + (reg_plus_ten(itype->rs))));
  printf("WB.readDataMem:32 = %d (%d * 4) (contents of Memory[0x%08X])\n",
		 ((itype->immediate) << two),
			 itype->immediate,
				 ((itype->immediate) + (reg_plus_ten(itype->rs)))); 
  printf("WB.writeRegister:5 = %d\n\n", itype->rt);
  printf("So, by the end of the 5th cycle:\n$%d = %d",
		 itype->rt,
			 ((itype->immediate) << two));
}

void print_pipeline(mips_rtype_t *rtype,
					mips_itype_t *itype)	{
  print_IF_ID(itype,rtype);
  print_ID_EX(itype,rtype);
  print_EX_MEM(itype);
  print_MEM_WB(itype,rtype);
  print_WB(itype);
  return;
}

int main(int argc, char *argv[]) {
  uint32_t regashextouint32, regasuint32lslby6, regasdectouint32;
  /* Declare & (partially) initialise vars for each type of instruction/data */
  mips_rtype_t rtypeinstruction = {0,
                                   0,NULL,"Opcode",
                                   0,NULL,"RS",
                                   0,NULL,"RT",
                                   0,NULL,"RD",
                                   0,NULL,"Shamt",
                                   0,NULL,"Funct",
								   0,NULL,"SLL",
								   0,NULL,"ADD"
                                   };
  mips_itype_t itypeinstruction = {0,
                                   0,NULL,"Opcode",
                                   0,NULL,"RS",
                                   0,NULL,"RT",
                                   0,NULL,"Immediate",
								   0,NULL,"SW",
								   0,NULL,/* no need for a swop name */
								   0,NULL,"ADDIU",
								   0,NULL,"LW"
                                   };
  printf(VERSION); 
  
  /* Now perform some basic sanity checks on the command line input string... */ 
  if ( argc != 2 || /* if there's an input string carry on & check its length */
       strlen(argv[1]) != 9 || /* if OK then convert it and check the result: */
       (UINT32_MAX==(regashextouint32=strtouint32(&argv[1][1],16))) ){ /* OK? */
    printf(USAGE);  /* Failed at least one of the above checks so alert user  */
    exit(1);        /* ...and exit. */
  }
  /* All of the above tests passed so continue on with the rest of the code. */
  
  regasuint32lslby6 = regashextouint32 << 6; /* Calculate the LSL by 6 value */
  regasdectouint32 = strtouint32(&argv[1][0],10); /* Treat reg no as base 10 */

  printf("A.\targv[1] command line input was: %s\n", argv[1]);
  printf("B.\tIgnoring the first digit gives: %s\n", &argv[1][1]);
  printf("B.i\tTreated as 0x%08X & printed in groups of 4 bits:\n\t%s\n",
         regashextouint32,bitstostr(regashextouint32,32,4));
  printf("B.ii\tLogical shift left by 6 is 0x%08X & grouped in 4 bits:\n\t%s\n",
         regasuint32lslby6,bitstostr(regasuint32lslby6,32,4));
  printf("B.iii\t0x%08X as 2's complement number & printed in base 10:\n\t%d\n",
         regasuint32lslby6,(int)regasuint32lslby6);
  printf("C.\t%s treated as a 32-bit number & printed as 0x%%08X:\n\t0x%08X\n",
         argv[1],regasdectouint32);

  init_all_types(regasuint32lslby6,
                 &rtypeinstruction,
                 &itypeinstruction);

  puts("Answers for Part D given the following representations:");
  print_all_types(&rtypeinstruction,
               &itypeinstruction);
  printf("D.i:\t");
  itypeinstruction.opname="LW";     print_i_type_mem(&itypeinstruction);
  printf("D.ii:\t");
  rtypeinstruction.opname="ADD";    print_r_type(&rtypeinstruction);
  printf("D.iii:\t");
  itypeinstruction.opname="ADDIU";  print_i_type_alu(&itypeinstruction);
  printf("D.iv:\t");
  rtypeinstruction.opname="SLL";    print_r_type_shift(&rtypeinstruction);
  printf("D.v:\t");
  itypeinstruction.opname="SW";     print_i_type_mem(&itypeinstruction);	/*Updates the opname for itype to SW so we don't need duplicate code.*/
  
/* This below, prints out the pipeline through the use of pointers. */
  print_pipeline(&rtypeinstruction,
				 &itypeinstruction);
  return(0);
}

/* Compile and Run Results

Cameron@CameronXPS /cygdrive/c/Users/Cameron/Documents/CS210/ace3
$ gcc ace3v1_2.c -Wall -pedantic -o ace3v1_2

Cameron@CameronXPS /cygdrive/c/Users/Cameron/Documents/CS210/ace3
$ ./ace3v1_2 201234567
ace3v1_2 V1.2  by Cameron Drennan. Last Update 02/02/2014
A.      argv[1] command line input was: 201234567
B.      Ignoring the first digit gives: 01234567
B.i     Treated as 0x01234567 & printed in groups of 4 bits:
        0000 0001 0010 0011 0100 0101 0110 0111
B.ii    Logical shift left by 6 is 0x48D159C0 & grouped in 4 bits:
        0100 1000 1101 0001 0101 1001 1100 0000
B.iii   0x48D159C0 as 2's complement number & printed in base 10:
        1221679552
C.      201234567 treated as a 32-bit number & printed as 0x%08X:
        0x0BFE9887
Answers for Part D given the following representations:
R-Type fields:  + Opcode +    RS +    RT +    RD + Shamt +  Funct +
        Bits:   | 010010 | 00110 | 10001 | 01011 | 00111 | 000000 |
        Values: +     18 +     6 +    17 +    11 +     7 +      0 +
I_Type fields:  + Opcode +    RS +    RT +        Immediate +
        Bits:   | 010010 | 00110 | 10001 | 0101100111000000 |
        Values: +     18 +     6 +    17 +       22976(dec) +
D.i:    LW      $17,22976($6)
D.ii:   ADD     $11,$6,$17
D.iii:  ADDIU   $17,$6,22976
D.iv:   SLL     $11,$17,7
D.v:    SW      $17,22976($6)

IF/ID

IF/ID state at the end of the 5th cycle:
Instruction (in assembly language) is : SW $17,22976($6)
Instruction (in binary notation) is : 10101100110100010101100111000000
Instruction (in hexadecimal) is : 0xACD159C0

IF/ID.PC:32 = 84
IF/ID.I:32 = 0xACD159C0
Sub-fields of IF/ID.I are:
IF/ID.I:[31-26] (opcode) = 101011 [43(ten)]
IF/ID.I:[25-21] (rs) = 00110 [$6 aka $a2]
IF/ID.I:[20-16] (rt) = 10001 [$17 aka $s1]
IF/ID.I:[15-11] (rd) = 01011 [$11 aka $t3]
IF/ID.I:[10-6] (shamt) = 00111 [7(ten)]
IF/ID.I:[5-0] (funct) = 000000 [0(ten)]
IF/ID.I:[15-0] (const) = 0101100111000000 [22976(ten)]

ID/EX

ID/EX state at the end of the 5th cycle:
Instruction (in assembly language) is : SLL $11,$17,7
Instruction (in binary notation) is : 00000000000100010101100111000000 # Note: r
s defaults to $0
Instruction (in hexadecimal) is : 0x001159C0

ID/EX.PC:32 = 80
ID/EX.readData1:32 = 16 (or 0 (zero)) ($6 contains 16 (or $0 contains 0))
ID/EX.readData2:32 = 27 ($17 contains 27)
ID/EX.SEConstant:32 = 22976 (0x000059C0) (sign extended IF/ID.I:[15-0])
Note: SEConstant:[15-11] = 11 [rd]
Note: SEConstant:[10-6] = 7 [shamt]
Note: SEConstant:[5-0] = 0 [funct]
ID/EX.rtIndex:5 = 17 (from IF/ID.I:[20-16])

EX/MEM

EX/MEM state at the end of the 5th cycle:
Instruction (in assembly language) is : ADDIU $17,$6,22976
Instruction (in binary notation) is : 00100100110100010101100111000000
Instruction (in hexadecimal) is : 0x24D159C0

EX/MEM.BTA:32 = 91980 ((22976 << 2) + 76) [0x0001674C]
EX/MEM.ALUResult:32 = 22992 (22976 + 16) [0x000059D0]
EX/MEM.ALUZero:1 = 0
EX/MEM.writeDataMem:32 = 27 ($17 contains 27)
EX/MEM.writeRegister:5 = 17

MEM/WB

MEM/WB state at the end of the 5th cycle:
Instruction (in assembly language) is : ADD $11,$6,$17
Instruction (in binary notation) is : 00000000110100010101100000100000
Instruction (in hexadecimal) is : 0x00D15820

MEM/WB.ALUResult:32 = 43 (16 + 27) [0x0000002B]
MEM/WB.readDataMem:32 = 90240 (22560 * 4) [0x00016080]
MEM/WB.writeRegister:5 = 11

WB

WB state at the end of the 5th cycle:
Instruction (in assembly language) is : LW $17,22976($6)
Instruction (in binary notation) is : 10001100110100010101100111000000
Instruction (in hexadecimal) is : 0x8CD159C0

WB.ALUResult:32 = 22992 (22976 + 16) [0x000059D0]
WB.readDataMem:32 = 91904 (22976 * 4) (contents of Memory[0x000059D0])
WB.writeRegister:5 = 17

So, by the end of the 5th cycle:
$17 = 91904
*/