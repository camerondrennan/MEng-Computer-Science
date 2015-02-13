/**************************************************************************
 *
 * Filename: ace2v4_0.c
 *
 * Synopsis: 
 * ace2v4_0 <regno>
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
 * v1.1	 Removed parts of the code so that registration number is not shifted
 *		 by 6 bits to the left. I replaced the variable "regasuint32lslby6"
 *		 to "regashextouint32" as this was the easiest way of dealing with 
 *		 the modification. 
 * v1.2  Deleted all of "B" outputs from the main method as we don't shift the 
 *		 reg no. by 6 bit, so it is not needed. Deleted print outs of A to C. 
 *		 Deleted all print outs of FP representations and various other code 
 *		 related to FP.
 * v2.0	 This was a major revision so I made a new version. I Deleted D.i - D.v 
 *		 from the main method as these are MIPS instructions, so they are not 
 *		 needed. I also deleted the R-type, I-type, and J-type fields. This 
 *		 included deleting the typedef struct for each type, deleting the init
 *		 functions for each type, removing each type from the wrapper function,
 *		 deleting each type's "print_" function, removing each type from 
 *		 "print_all_types" in main, removing each type's declaration in main,
 *		 and removing each type from "init_all_types". I then added the 
 *		 "Arm_add" typedef, added the init_add initialiser function (the bits 
 *		 don't print correctly yet initially I tried to mask the existing 
 *		 #defines but it didn't work so I just put in the bit number I was 
 *		 looking for which works slightly better). I added the add instruction 
 *		 to the wrapper function, added it to the "void print_add", I also 
 *		 added "arm_add_t *add" to void print_all_types. I added "arm_add_t 
 *		 addinstruction" in the main method, and finally added "addinstruction" 
 *		 to "init_all_types" & "print_all_types". I then realise I wasn't using 
 *		 any of the "#defines" so I deleted then all.
 * v2.1  I realise I no longer use the "fp_i_t;" typedef union so I removed it 
 *		 & comments. I then implemented the ARM MOV instruction in the program. 
 *		 To this I used a similar method to how I added the ARM ADD in v2.0. 
 *		 I added the "arm_mov_t;" typedef struct and the "init_mov" initialiser 
 *		 function. I then added the mov instruction to the wrapper function and 
 *		 the "print_mov" function. I also added "arm_mov_t *mov" & 
 *		 "print_mov(mov);" to print_all_types. I then added "arm_mov_t 
 *		 movinstruction" in the main method.
 * v2.2  I added the rimm and imm8 to the add typedef and to "init_add". I added 
 *		 the "address mode 1" to the "print_add" function and also added the 
 *		 "rotate_imm" & "immed_8" to the "arm_add_t addinstruction" in the main 
 *		 method. I also changed the second parameter in each of the IN instructions 
 *		 in the init_ functions. I initially had it at the end of the bits I wanted 
 *		 but it needs to be the beginning. I added the "Data-processing instructions" 
 *		 in the main method to make the output look like Duncan's sample output. I 
 *		 also changed the outputs field names to make it look like the sample output 
 *		 and the syntax printouts for the MOV & ADD instructions.
 * v2.3  I made typedef structures for each addressing mode and called them 
 *		 "arm_SO_1_t", "arm_SO_2_t" and "arm_SO_3_t". I removed the "rimm" and 
 *		 "imm8" from "arm_add_t" because these are now in "arm_SO_1_t". I used 
 *		 the same process for implementing these structures as I did with MOV and 
 *		 ADD. I also removed "regasdectouint32" because it was unused and was throwing
 *		 a warning when the program compiled. I also deleted a lot of the comments 
 *		 throughout the program that were unnecessary.
 * v3.0  I added "print_arm_addimm", "print_arm_addrm", "print_arm_addrm_lsl_si" and
 *		 "print_arm_addrm_lsl_rs" to the print_? functions and print_all_types.
 *		 I also added "print_arm_movimm", "print_arm_movrm", "print_arm_movrm_lsl_si"
 *		 and "print_arm_movrm_lsl_rs" to the print_? functions and print_all_types. 
 * v3.1	 I implemented the branch instruction. I did it the same way as the MOV & ADD
 *		 instructions. I also added the syntax for the branch instructions so the output
 * 		 looks the same as Duncan's sample output. I also added the Example(s) for branch.
 *		 I also implemented the load & store  instructions. I did it the same way as the
 *		 MOV & ADD instructions. I added the syntax for the load & store instructions. I
 *		 also added the Example(s) for the load & store instructions.
 * v3.2	 I implemented the Load & Store multiple instructions, the multiply accumulate
 *		 instruction, and the multiply instruction using the same method as previous 
 *		 instructions. I added the Syntax and Example(s) to the output and added a sample
 *		 output to the end of the program.
 * v3.3  Changed the immed_8 value output in "SO_1" to hexadecimal by changing the printf
 *		 format specifier from "%d" to "#0x%X" in the print.
 * v3.4	 Changed the printf format specifier for the "ADDLSS #<immediate>" & "MOVLSS 
 *		 <immediate>" examples from "%X" to "%07x" so I will get a similar output to Duncan.
 *		 I also changed the printf of PC in the branch examples as before I had the PC value
 *		 hardcoded as "0x40000000" but I changed it to "0x%x" and I passed in the PC. I then
 *		 changed the #define of PC from "#define PC 0X10000000" to "#define PC 0X40000000"
 *		 to get the same output as Duncan's. In the branch I changed the print Example from
 *		 just "-27141808" to a variable using "branch->sinim << 2". I also change "0x3e61d950"
 *		 to "0x%x" and the input to "PC + (branch->sinim << 2)". I added a "#define signed" to
 *		 make a signed_immed_24 number if necessary. I also added "sign" to the branch struct 
 *		 which is the 24th bit (the sign bit). I also added "rsign" to the branch struct which
 *		 is the bits from 0-22, which is used to calculate the signed value. I changed the 
 *		 branch print Example to use my newly created "#define signed". I needed to add an
 *		 if-else statement which looks at the sign bit and determines if it is 1 or 0. If it
 *		 is 1 then it changes the value to signed, if it is 0 then it does unsigned.
 * v4.0	 I added a for loop which determines if the bit in the "register_list" is 1 or 0. If 
 *		 it is 1 then it will print out the register in the example. In order to determine 
 *		 whether or not to print a "+" or "-" in the load & store instructions Example(s) I 
 *		 used an if-else statement with a temporary char variable. So if the U bit is 1 then 
 *	 	 print "+" and vice versa. I also added another if statement to determine to print a 
 *		 "!" in the load & store instructions Example(s). If the W bit is 0 and the P bit is 
 *		 1 then print a "!" and if not, then don't print a "!".
 * v4.1  I re-factored my code so that I only have one typedef struct and init_ function under 
 * 		 the name of "arm". I also concatenated a lot of the print statements to reduce
 *		 the length of the program by about 400 lines. I added comments to the 
 *		 program to allow the code become more understandable. I removed many fields from the
 *		 struct that were simply duplicates of other fields, so I made changes where necessary in
 *		 the init_ functions and print_ functions.
 *       
 *************************************************************************************************/
#define VERSION "ace2v4_1 V4.1  by Cameron Drennan. Last Update 05/12/2013\n"
#define USAGE "Usage: %s <regNo>\n",argv[0]

#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

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

/* On some systems an UINT32_MAX is already defined, if not... */
#ifndef UINT32_MAX
#define UINT32_MAX ((uint32_t)-1)
#endif

/* The following if for the signed_immed_24 in branch. This is a #define to calculate the 
signed value of a 24 bit number by calculating the value (excluding the sign bit) and minuses
2^24 from the value. It is used in conjunction with the branch instruction and if statements
in the branch print_ function. */
#define signed ((arm->rsign)-8388608)

/* The following struct represents the instructions in ARM. I tried my best to label the parts
of the struct in reference to how Duncan's output was labelled.
The members of the struct include:
   - the 32-bit representation of the instruction in the .in member
   - the contents of the field as an integer value, e.g. 9 in .cond
   - the (pointer to the) corresponding bit string, e.g. &"1001" in .condbits
   - the (pointer to the) name/label of the field, e.g. &"cond" in .condname */

typedef struct {
  uint32_t in;
  int cond;		char *condbits;		char *condname; 	/*cond - condition*/
  int oo;		char *oobits;		char *ooname;   	/*oo - 00*/
  int I;		char *Ibits;		char *Iname;		/*I - I*/
  int llOl;		char *llOlbits;		char *llOlname;		/*llOl - 1101*/
  int opcode;	char *opbits;		char *opname;		/*opcode - opcode*/
  int s;		char *sbits;		char *sname;		/*s - S*/
  int rn;		char *rnbits;		char *rnname;		/*rn - Rn*/
  int rd;		char *rdbits;		char *rdname;		/*rd - Rd*/
  int so;		char *sobits;		char *soname;		/*so - Shifter Operand*/
  int imm8;		char *imm8bits; 	char *imm8name;		/*imm8 - immediate8*/
  int simm;		char *simmbits;		char *simmname;		/*simm - shift immediate*/
  int shft;		char *shftbits;		char *shftname;		/*shft - shift*/
  int O;		char *Obits;		char *Oname;		/*O - Immediate shift 0*/
  int rm;		char *rmbits;		char *rmname;		/*rm - Rm*/
  int rs;		char *rsbits;		char *rsname;		/*rs - Rs*/
  int o;		char *obits;		char *oname;		/*o - Register shifts 0*/
  int lOO;		char *lOObits;		char *lOOname;		/*lOO - 100*/
  int L;		char *Lbits;		char *Lname;		/*L - L*/
  int sinim;	char *sinimbits;	char *sinimname; 	/*sinim - Signed immediate*/
  int U;		char *Ubits;		char *Uname;		/*U - U*/
  int B;		char *Bbits;		char *Bname;		/*B - B*/
  int W;		char *Wbits;		char *Wname;		/*W - W*/
  int reg;		char *regbits;		char *regname;		/*reg - register list*/
  int OOOOOO1;	char *OOOOOO1bits;	char *OOOOOO1name;	/*OOOOOO1 - 0000001*/
  int OOOOOOO;	char *OOOOOOObits;	char *OOOOOOOname;	/*OOOOOOO - 0000000*/
  int lOOl;		char *lOOlbits;		char *lOOlname;		/*lOOl - 1001*/
  int rsign;	char *rsignbits;	char *rsignname;	/*rsign - Rest of sign number (excluding sign bit)*/
} arm_t;												/*I put rsign at the end because I only use the value*/

/* The following is a macro that 'extracts' from the bits passed in the 
   value of the field of size bit_sz that begins at bit position bit_l.
 */
#define IN(bits,bit_l,bit_sz) ((bits >> bit_l) & ((1 << bit_sz) - 1))

/* The PC value as stipulated in the specification */
#define PC 0X40000000

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
    int result;    
    do                          
        result = isdigit(*s++);  
    while (result && *s) ;       
    return result;  
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
    if (!isnumeric(s))    
      return(UINT32_MAX); 
    while (*s)
        result = (result * base) + ((*s++) - '0'); 
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
    char *bitsPtr;  
    int stringsize, 
        splitter;    
    stringsize = (split)?size+size/split:size; 
    splitter = split; 
    if (NULL == (bitsPtr = calloc(stringsize+1,sizeof(char))))
      return("Calloc Failed"); 
    bitsPtr += stringsize; 
    
    for (  ; size-- ; bits >>= 1) { 
        *--bitsPtr = (bits&1)?'1':'0';    
        if (splitter > 0)          
          if (0 == (--splitter)) { 
            *--bitsPtr = ' ';      
            splitter = split;      
          }
    }
    if (' ' == *bitsPtr) ++bitsPtr; 
    return(bitsPtr);
}

/* 	The following init_? functions initialise the appropriate members of the
	data structure with the values derived from the first parameter - bits.
	The second parameter is the start of the bits that it takes in.
	The third parameter is the size of the bit pattern it takes. eg.
		-arm->cond = IN(bits,28,4);
		-first parameter - bits
		-second - 28 (start looking at bit 28)
		-third - 4 (bit size of 4, so 28-31)
	I put these in order so I could eliminate duplicates easily
*/

void init_arm(uint32_t bits, arm_t *arm) {
  arm->in = bits;
  arm->cond = IN(bits,28,4);
  arm->condbits = bitstostr(arm->cond,4,0);
  arm->oo = IN(bits,26,2);
  arm->oobits = bitstostr(arm->oo,2,0);
  arm->lOO = IN(bits,25,3);
  arm->lOObits = bitstostr(arm->lOO,3,0);
  arm->I = IN(bits,25,1);
  arm->Ibits = bitstostr(arm->I,1,0);
  arm->L = IN(bits,24,1);
  arm->Lbits = bitstostr(arm->L,1,0);
  arm->U = IN(bits,23,1);
  arm->Ubits = bitstostr(arm->U,1,0);
  arm->B = IN(bits,22,1);
  arm->Bbits = bitstostr(arm->B,1,0);
  arm->W = IN(bits,21,1);
  arm->Wbits = bitstostr(arm->W,1,0);
  arm->llOl = IN(bits,21,4);
  arm->llOlbits = bitstostr(arm->llOl,4,0);
  arm->opcode = IN(bits,21,4);
  arm->opbits = bitstostr(arm->opcode,4,0);
  arm->OOOOOO1 = IN(bits,21,7);
  arm->OOOOOO1bits = bitstostr(arm->OOOOOO1,7,0);
  arm->OOOOOOO = IN(bits,21,7);
  arm->OOOOOOObits = bitstostr(arm->OOOOOOO,7,0);
  arm->s = IN(bits,20,1);
  arm->sbits = bitstostr(arm->s,1,0);
  arm->rn = IN(bits,16,4);
  arm->rnbits = bitstostr(arm->rn,4,0);
  arm->rd = IN(bits,12,4);
  arm->rdbits = bitstostr(arm->rd,4,0);
  arm->rs = IN(bits,8,4);
  arm->rsbits = bitstostr(arm->rs,4,0);
  arm->o = IN(bits,7,1);
  arm->obits = bitstostr(arm->o,1,0);
  arm->simm = IN(bits,7,5);
  arm->simmbits = bitstostr(arm->simm,5,0);
  arm->shft = IN(bits,5,2);
  arm->shftbits = bitstostr(arm->shft,2,0);
  arm->O = IN(bits,4,1);
  arm->Obits = bitstostr(arm->O,1,0);
  arm->lOOl = IN(bits,4,4);
  arm->lOOlbits = bitstostr(arm->lOOl,4,0);
  arm->rm = IN(bits,0,4);
  arm->rmbits = bitstostr(arm->rm,4,0);
  arm->imm8 = IN(bits,0,8);
  arm->imm8bits = bitstostr(arm->imm8,8,0);
  arm->so = IN(bits, 0,12);
  arm->sobits = bitstostr(arm->so,12,0);
  arm->reg = IN(bits,0,16);
  arm->regbits = bitstostr(arm->reg,16,0);
  arm->rsign = IN(bits,0,23);
  arm->rsignbits = bitstostr(arm->rsign,23,0);
  arm->sinim = IN(bits,0,24);
  arm->sinimbits = bitstostr(arm->sinim,24,0);

  return;
}

/* A wrapper function for the ARM data structure to be initialsed */
void init_all_types(uint32_t bits,
					arm_t *arm) {
  init_arm(bits,arm);
  return;
}

/* The following print_? functions are really just wrappers round the
   printf()s. 
*/
void print_mov (arm_t *arm) {	/*MOV instruction*/
  printf("\n<opcode1> := MOV | MVN\n");
  printf("DP_1 fields:\t| %4s | %2s | %1s | %4s | %1s |  SBZ | %4s | %12s |\n",
		 arm->condname,
			 arm->ooname,
				 arm->Iname,
					 arm->llOlname,
						 arm->sname,
							 arm->rdname,
								 arm->soname);
  printf("\tBits:\t| %s | %s | %s | %s | %s | %s | %s | %s |\n",
		 arm->condbits,
			 arm->oobits,
				 arm->Ibits,
					 arm->llOlbits,
						 arm->sbits,
							 arm->rnbits,
								 arm->rdbits,
									 arm->sobits);
  printf("\tValues:\t| %4d | %2d | %1d | %4d | %1d | %4d | %4d | %12d |\n",
		 arm->cond,
			 arm->oo,
				 arm->I,
					 arm->llOl,
						 arm->s,
							 arm->rn,
								 arm->rd,
									 arm->so);
  printf("Syntax: <opcode1>{<cond>}{S} <Rd>, <Shftr_Oprand>\n");
}

void print_add (arm_t *arm) {	/*ADD instruction*/
  printf("\n<opcode3> := ADD, etc.\n");
  printf("DP_3 fields:\t| %4s | %2s | %1s | %4s | %1s | %4s | %4s | %12s |\n",
		 arm->condname,
			 arm->ooname,
				 arm->Iname,
					 arm->opname,
						 arm->sname,
							 arm->rnname,
								 arm->rdname,
									 arm->soname);
  printf("\tBits:\t| %s | %s | %s | %s | %s | %s | %s | %s |\n",
		 arm->condbits,
			 arm->oobits,
				 arm->Ibits,
					 arm->opbits,
						 arm->sbits,
							 arm->rnbits,
								 arm->rdbits,
									 arm->sobits);
  printf("\tValues:\t| %4d | %2d | %1d | %4d | %1d | %4d | %4d | %12d |\n",
		 arm->cond,
			 arm->oo,
				 arm->I,
					 arm->opcode,
						 arm->s,
							 arm->rn,
								 arm->rd,
									 arm->so);
  printf("Syntax: <opcode3>{<cond>}{S} <Rd>, <Rn>, <Shftr_Oprand>\n");
}

void print_addressMode (arm_t *arm) {	/*Addressing Modes*/
  printf("\nData-processing operands encoded by <shifter operand> :\n");
  printf("Address Mode 1 - 32-bit immediate\nSO_1 fields:\t| rotate_imm | %8s |\n",
		 arm->imm8name);
  printf("\tBits:\t|       %s | %s |\n",
		 arm->rsbits,
			 arm->imm8bits);
  printf("\tValues:\t|       %4d |     0x%X |\n",
		 arm->rs,
			 arm->imm8);
  printf("Address Mode 1 - Immediate shifts\nSO_2 fields:\t| %5s | %2s | %1s | %4s |\n",
		 arm->simmname,
			 arm->shftname,
				 arm->Oname,
					 arm->rmname);
  printf("\tBits:\t|     %s |    %s | %s | %s |\n",
		 arm->simmbits,
			 arm->shftbits,
				 arm->Obits,
					 arm->rmbits);
  printf("\tValues:\t|     %5d |    %2d | %1d | %4d |\n",
		 arm->simm,
			 arm->shft,
				 arm->O,
					 arm->rm);
  printf("Address Mode 1 - Register shifts\nSO_3 field:\t| %4s | %1s | %2s | 1 | %4s |\n",
		 arm->rsname,
			 arm->oname,
				 arm->shftname,
					 arm->rmname);
  printf("\tBits:\t| %s | %s |    %s | %s | %s |\n",
		 arm->rsbits,
			 arm->obits,
				 arm->shftbits,
					 arm->Obits,
						 arm->rmbits);
  printf("\tValues:\t| %4d | %1d |    %2d | %1d | %4d |\n",
		 arm->rs,
			 arm->o,
				 arm->shft,
					 arm->O,
						 arm->rm);
}

void print_addmov(arm_t *arm) {		/*ADD & MOV Examples*/
  printf("Example(s):\nMode:\t#<immediate>\n\tADDLSS R%d, R%d, #0x%x\n",
		 arm->rd,
			 arm->rn,
				 arm->imm8);
  printf("Mode:\t<Rm>\n\tADDLSS R%d, R%d, R%d\n",
		 arm->rd,
			 arm->rn,
				 arm->rm);
  printf("Mode:\t<Rm>, LSL #<shift_imm>\n\tADDLSS R%d, R%d, R%d LSL #%d\n",
		 arm->rd,
			 arm->rn,
				 arm->rm,
					 arm->simm);
  printf("Mode:\t<Rm>, LSL <Rs>\n\tADDLSS R%d, R%d, R%d LSL R%d\n",
		 arm->rd,
			 arm->rn,
				 arm->rm,
					 arm->rs);
  printf("Mode:\t#<immediate>\n\tMOVLSS R%d, #0x%x\n",
		 arm->rd,
			 arm->imm8);
  printf("Mode:\t<Rm>\n\tMOVLSS R%d, R%d\n",
		 arm->rd,
			 arm->rm);
  printf("Mode:\t<Rm>, LSL #<shift_imm>\n\tMOVLSS R%d, R%d LSL #%d\n",
		 arm->rd,
			 arm->rm,
				 arm->simm);
  printf("Mode:\t<Rm>, LSL <Rs>\n\tMOVLSS R%d, R%d LSL R%d\n",
		 arm->rd,
			 arm->rm,
				 arm->rs);
}

void print_branch (arm_t *arm) {	/*Branch instruction and Examples*/
  int signed_imm24;
  if(arm->U == 1) {		/*its arm->U because the U bit is the same as the sign bit.*/
	 signed_imm24 = signed;
  }
  else {
	 signed_imm24 = arm->sinim;
  }
  printf("\nBranch instruction\n");
  printf("Branch fields:\t| %4s | %3s | %1s | %24s |\n",
		 arm->condname,
			 arm->lOOname,
					 arm->Lname,
						 arm->sinimname);
  printf("\tBits:\t| %s | %s | %s | %s |\n",
		 arm->condbits,
			 arm->lOObits,
				 arm->Lbits,
					 arm->sinimbits);
  printf("\tValues:\t| %4d | %3d | %1d | %24d |\n", 
		 arm->cond,
			 arm->lOO,
				 arm->L,
					 signed_imm24);
  printf("Syntax: B{L}{<cond>} <target_address>\n");

  printf("Example(s) (with PC as 0x%x):\n\tBLLS\t0x%x <PC + %d (%d << %d)>\n",		/*Branch Examples*/
		 PC,
			 PC + (signed_imm24 << arm->shft),
				 signed_imm24 << arm->shft,
					 signed_imm24,
						 arm->shft);
}

void print_ls (arm_t *arm) {	/*Load & Store Instructions*/
  char plusORminus;
  char exclamation;
  printf("\nLoad & Store instructions\n");
  printf("LS fields:| %4s | 01 | %1s | P | %1s | %1s | %1s | %1s | %4s | %4s |    addr_mode |\n",
		 arm->condname,
			 arm->Iname,
				 arm->Uname,
					 arm->Bname,
						 arm->Wname,
							 arm->Lname,
								 arm->rnname,
									 arm->rdname);
  printf("Bits:\t  | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s |\n",
		 arm->condbits,
			 arm->oobits,
				 arm->Ibits,
					 arm->Lbits,
						 arm->Ubits,
							 arm->Bbits,
								 arm->Wbits,
									 arm->sbits,
										 arm->rnbits,
											 arm->rdbits,
												 arm->sobits);
  printf("Values:\t  | %4d | %2d | %1d | %1d | %1d | %1d | %1d | %1d | %4d | %4d | %12d |\n",
		 arm->cond,
			 arm->oo,
				 arm->I,
					 arm->L,
						 arm->U,
							 arm->B,
								 arm->W,
									 arm->s,
										 arm->rn,
											 arm->rd,
												 arm->so);
  printf("Syntax: LDR|STR{<cond>}{B}{T} Rd, <addressing_mode>\n");
  
  if(arm->U == 1) {		/*Decides whether to print a plus or minus depending on the U bit*/
	 plusORminus = '+';
  }
  else {
	 plusORminus = '-';
  }
  printf("Examples(s):\nMode:\t[<Rn>, #+/-<offset_12>]\n\tLDRLS R%d, [R%d, #%c%d]\n",	/*Load & Store Examples*/
		 arm->rd,
			 arm->rn,
				 plusORminus,
					 arm->so);
					 
  printf("Mode:\t[<Rn>, +/-<Rm>]\n\tLDRLS R%d, [R%d, %cR%d]\n",
		 arm->rd,
			 arm->rn,
				 plusORminus,
					 arm->rm);

  printf("Mode:\t[<Rn>, +/-<Rm>, <shift> #<shift_imm>]\n\tLDRLS R%d, [R%d, %cR%d, %d #%d]\n",
		 arm->rd,
			 arm->rn,
				 plusORminus,
					 arm->rm,
						 arm->shft,
							 arm->simm);
							 
  if(arm->W == 0 && arm->L == 1) {		/*Decides whether to print an exclamation mark depending on the W & L bits*/
	 exclamation = '!';
  }
  else {
	 exclamation = ' ';
  }
  
  printf("Mode:\t[<Rn>, #+/-<offset_12>]!\n\tLDRLS R%d, [R%d, #%c%d]%c\n",
		 arm->rd,
			 arm->rn,
				 plusORminus,
					 arm->so,
						 exclamation);

  printf("Mode:\t[<Rn>, +/-<Rm>]!\n\tLDRLS R%d, [R%d, %cR%d]%c\n",
		 arm->rd,
			 arm->rn,
				 plusORminus,
					 arm->rm,
						 exclamation);

  printf("Mode:\t[<Rn>, +/-<Rm>, <shift> #<shift_imm>]!\n\tLDRLS R%d, [R%d, %cR%d, %d #%d]%c\n",
		 arm->rd,
			 arm->rn,
				 plusORminus,
					 arm->rm,
						 arm->shft,
							 arm->simm,
								 exclamation);

  printf("Mode:\t[<Rn>], #+/-<offset_12>\n\tLDRLS R%d, [R%d], #%c%d\n",
		 arm->rd,
			 arm->rn,
				 plusORminus,
					 arm->so);

  printf("Mode:\t[<Rn>], +/-<Rm>\n\tLDRLS R%d, [R%d], %cR%d\n",
		 arm->rd,
			 arm->rn,
				 plusORminus,
					 arm->rm);

  printf("Mode:\t[<Rn>], +/-<Rm>, <shift> #<shift_imm>\n\tLDRLS R%d, [R%d], %cR%d, %d #%d\n",
		 arm->rd,
			 arm->rn,
				 plusORminus,
					 arm->rm,
						 arm->shft,
							 arm->simm);
}

void print_lsm (arm_t *arm) {		/*Load & Store Multiple Instructions*/
  int i;
  int first = 0;
  printf("\nLoad & Store Multiple instructions\n");
  printf("LSM fields:| %4s | %3s | P | %1s | %1s | %1s | %1s | %4s | %16s |\n",
		 arm->condname,
			 arm->lOOname,
				 arm->Uname,
					 arm->sname,
						 arm->Wname,
							 arm->Lname,
								 arm->rnname,
									 arm->regname);
  printf("Bits:\t   | %s | %s | %s | %s | %s | %s | %s | %s | %s |\n",
		 arm->condbits,
			 arm->lOObits,
				 arm->Lbits,
					 arm->Ubits,
						 arm->Bbits,
							 arm->Wbits,
								 arm->sbits,
									 arm->rnbits,
										 arm->regbits);
  printf("Values:\t   | %4d | %3d | %1d | %1d | %1d | %1d | %1d | %4d | %16d |\n",
		 arm->cond,
			 arm->lOO,
				 arm->L,
					 arm->U,
						 arm->B,
							 arm->W,
								 arm->s,
									 arm->rn,
										 arm->reg);
  printf("Syntax:	LDM|STM{<cond>}<addressing_mode> <Rn>{!}, <registers>{^}\n");

  printf("Example(s):\n\tLDMLS R%d, {",		/*Load & Store Multiple Examples*/
		 arm->rn);

  for(i=0; i<16; i++) {		/*Identifies when the register list has a 1 in the bit string*/
	 if(first == 1) {		/*and prints out the register of each bit that is a 1*/
		 if(IN(arm->reg,i,1) == 1) {
			 printf(",R%d",i);		 
		 }
	 } else {		/*For the first register, it doesn't put a comma in front of the register*/
		 if(IN(arm->reg,i,1) == 1) {
			 printf("R%d",i);
			 first = 1;
		 }
	 }
  }
  first = 0;
  printf("}\n");
  printf("\tPOPLS {");
  for(i=0; i<16; i++) {		/*This is the same for loop as above*/
	 if(first == 1) {
		 if(IN(arm->reg,i,1) == 1) {
			 printf(",R%d",i);		 
		 }
	 } else {
		 if(IN(arm->reg,i,1) == 1) {
			 printf("R%d",i);
			 first = 1;
		 }
	 }
  }
  printf("}\n");
}

void print_mul (arm_t *arm) {		/*Multiply Accumulate instruction*/
  printf("\nMultiply Accumulate instruction\n");
  printf("MLA fields:| %4s | %7s | %1s | %4s | %4s | %4s | %4s | %4s |\n",
		 arm->condname,
			 arm->OOOOOO1name,
				 arm->sname,
					 arm->rdname,
						 arm->rnname,
							 arm->rsname,
								 arm->lOOlname,
									 arm->rmname);
  printf("Bits:\t   | %s | %s | %s | %s | %s | %s | %s | %s |\n",
		 arm->condbits,
			 arm->OOOOOO1bits,
				 arm->sbits,
					 arm->rnbits,
						 arm->rdbits,
							 arm->rsbits,
								 arm->lOOlbits,
									 arm->rmbits);
  printf("Values:\t   | %4d | %7d | %1d | %4d | %4d | %4d | %4d | %4d |\n",
		 arm->cond,
			 arm->OOOOOO1,
				 arm->s,
					 arm->rn,
						 arm->rd,
							 arm->rs,
								 arm->lOOl,
									 arm->rm);
  printf("Syntax:	MLA{<cond>}{S} <Rd>, <Rm>, <Rs>, <Rn>\n");

  printf("Examples(s):\n\tMLALSS R%d, R%d, R%d, R%d\n",		/*Multiply Accumulate Example*/
		 arm->rn,
			 arm->rm,
				 arm->rs,
					 arm->rd);

  printf("\nMultiply instruction\n");		/*Multiply instruction*/
  printf("MUL fields:| %4s | %7s | %1s | %4s |  SBZ | %4s | %4s | %4s |\n",
		 arm->condname,
			 arm->OOOOOOOname,
				 arm->sname,
					 arm->rdname,
						 arm->rsname,
							 arm->lOOlname,
								 arm->rmname);
  printf("Bits:\t   | %s | %s | %s | %s | %s | %s | %s | %s |\n",
		 arm->condbits,
			 arm->OOOOOOObits,
				 arm->sbits,
					 arm->rnbits,
						 arm->rdbits,
							 arm->rsbits,
								 arm->lOOlbits,
									 arm->rmbits);
  printf("Values:\t   | %4d | %7d | %1d | %4d | %4d | %4d | %4d | %4d |\n",
		 arm->cond,
			 arm->OOOOOOO,
				 arm->s,
					 arm->rn,
						 arm->rd,
							 arm->rs,
								 arm->lOOl,
									 arm->rm);
  printf("Syntax:	MUL{<cond>}{S} <Rd>, <Rm>, <Rs>\n");

  printf("Examples(s):\n\tMULLSS R%d, R%d, R%d",		/*Multiply Example*/
		 arm->rn,
			 arm->rm,
				 arm->rs);
}

void print_all_types(arm_t *arm) {
  print_mov(arm);
  print_add(arm);
  print_addressMode(arm);
  print_addmov(arm);
  print_branch(arm);
  print_ls(arm);
  print_lsm(arm);
  print_mul(arm);
  return;
}

int main(int argc, char *argv[]) {
  uint32_t regashextouint32;
  /* Declare & (partially) initialise variables for each ARM Instruction. */
  arm_t arminstruction = {0,
						  0,NULL,"cond",
						  0,NULL,"00",
						  0,NULL,"I",
						  0,NULL,"1101",
						  0,NULL,"Opco",
						  0,NULL,"S",
						  0,NULL,"Rn",
						  0,NULL,"Rd",
						  0,NULL,"Shftr_Oprand",
						  0,NULL,"immed_8",
						  0,NULL,"shift_imm",
						  0,NULL,"shift",
						  0,NULL,"0",
					  	  0,NULL,"Rm",
						  0,NULL,"Rs",
						  0,NULL,"0",
						  0,NULL,"100",
						  0,NULL,"L",
						  0,NULL,"signed_immed_24",
						  0,NULL,"U",
						  0,NULL,"B",
						  0,NULL,"W",
						  0,NULL,"register_list",
						  0,NULL,"0000001",
						  0,NULL,"0000000",
						  0,NULL,"1001"
						  };
  printf(VERSION);
 
  /* This is a basic sanity checks on the command line input string taken from p4sample.c */
  if ( argc != 2 || 
       strlen(argv[1]) != 9 || 
       (UINT32_MAX==(regashextouint32=strtouint32(&argv[1][1],16))) ){ 
    printf(USAGE);  
    exit(1);        
  }
  
  /*The following initializes and prints the ARM instructions & Examples.*/
  init_all_types(regashextouint32,
				 &arminstruction);
				 
  puts("\nACE 2:\n\nData-processing instructions");
  print_all_types(&arminstruction);
  
  return(0);
}

/*Compile and Run Results
Cameron@CameronXPS /cygdrive/c/Users/Cameron/Documents/CS210/ace2
$ gcc ace2v4_1.c -Wall -pedantic -o ace2v4_1
ace2v4_1.c: In function 'isnumeric':
ace2v4_1.c:213:9: warning: array subscript has type 'char' [-Wchar-subscripts]
         result = isdigit(*s++);
         ^

Cameron@CameronXPS /cygdrive/c/Users/Cameron/Documents/CS210/ace2
$ ./ace2v4_1 199987654
ace2v4_1 V4.1  by Cameron Drennan. Last Update 05/12/2013

ACE 2:

Data-processing instructions

<opcode1> := MOV | MVN
DP_1 fields:    | cond | 00 | I | 1101 | S |  SBZ |   Rd | Shftr_Oprand |
        Bits:   | 1001 | 10 | 0 | 1100 | 1 | 1000 | 0111 | 011001010100 |
        Values: |    9 |  2 | 0 |   12 | 1 |    8 |    7 |         1620 |
Syntax: <opcode1>{<cond>}{S} <Rd>, <Shftr_Oprand>

<opcode3> := ADD, etc.
DP_3 fields:    | cond | 00 | I | Opco | S |   Rn |   Rd | Shftr_Oprand |
        Bits:   | 1001 | 10 | 0 | 1100 | 1 | 1000 | 0111 | 011001010100 |
        Values: |    9 |  2 | 0 |   12 | 1 |    8 |    7 |         1620 |
Syntax: <opcode3>{<cond>}{S} <Rd>, <Rn>, <Shftr_Oprand>

Data-processing operands encoded by <shifter operand> :
Address Mode 1 - 32-bit immediate
SO_1 fields:    | rotate_imm |  immed_8 |
        Bits:   |       0110 | 01010100 |
        Values: |          6 |     0x54 |
Address Mode 1 - Immediate shifts
SO_2 fields:    | shift_imm | shift | 0 |   Rm |
        Bits:   |     01100 |    10 | 1 | 0100 |
        Values: |        12 |     2 | 1 |    4 |
Address Mode 1 - Register shifts
SO_3 field:     |   Rs | 0 | shift | 1 |   Rm |
        Bits:   | 0110 | 0 |    10 | 1 | 0100 |
        Values: |    6 | 0 |     2 | 1 |    4 |
Example(s):
Mode:   #<immediate>
        ADDLSS R7, R8, #0x54
Mode:   <Rm>
        ADDLSS R7, R8, R4
Mode:   <Rm>, LSL #<shift_imm>
        ADDLSS R7, R8, R4 LSL #12
Mode:   <Rm>, LSL <Rs>
        ADDLSS R7, R8, R4 LSL R6
Mode:   #<immediate>
        MOVLSS R7, #0x54
Mode:   <Rm>
        MOVLSS R7, R4
Mode:   <Rm>, LSL #<shift_imm>
        MOVLSS R7, R4 LSL #12
Mode:   <Rm>, LSL <rs>
        MOVLSS R7, R4 LSL R6

Branch instruction
Branch fields:  | cond | 100 | L |          signed_immed_24 |
        Bits:   | 1001 | 100 | 1 | 100110000111011001010100 |
        Values: |    9 |   4 | 1 |                 -6785452 |
Syntax: B{L}{<cond>} <target_address>
Example(s) (with PC as 0x40000000):
        BLLS    0x3e61d950 <PC + -27141808 (-6785452 << 2)>

Load & Store instructions
LS fields:| cond | 01 | I | P | U | B | W | L |   Rn |   Rd |    addr_mode |
Bits:     | 1001 | 10 | 0 | 1 | 1 | 0 | 0 | 1 | 1000 | 0111 | 011001010100 |
Values:   |    9 |  2 | 0 | 1 | 1 | 0 | 0 | 1 |    8 |    7 |         1620 |
Syntax: LDR|STR{<cond>}{B}{T} Rd, <addressing_mode>
Examples(s):
Mode:   [<Rn>, #+/-<offset_12>]
        LDRLS R7, [R8, #+1620]
Mode:   [<Rn>, +/-<Rm>]
        LDRLS R7, [R8, +R4]
Mode:   [<Rn>, +/-<Rm>, <shift> #<shift_imm>]
        LDRLS R7, [R8, +R4, 2 #12]
Mode:   [<Rn>, #+/-<offset_12>]!
        LDRLS R7, [R8, #+1620]!
Mode:   [<Rn>, +/-<Rm>]!
        LDRLS R7, [R8, +R4]!
Mode:   [<Rn>, +/-<Rm>, <shift> #<shift_imm>]!
        LDRLS R7, [R8, +R4, 2 #12]!
Mode:   [<Rn>], #+/-<offset_12>
        LDRLS R7, [R8], #+1620
Mode:   [<Rn>], +/-<Rm>
        LDRLS R7, [R8], +R4
Mode:   [<Rn>], +/-<Rm>, <shift> #<shift_imm>
        LDRLS R7, [R8], +R4, 2 #12

Load & Store Multiple instructions
LSM fields:| cond | 100 | P | U | S | W | L |   Rn |    register_list |
Bits:      | 1001 | 100 | 1 | 1 | 0 | 0 | 1 | 1000 | 0111011001010100 |
Values:    |    9 |   4 | 1 | 1 | 0 | 0 | 1 |    8 |            30292 |
Syntax: LDM|STM{<cond>}<addressing_mode> <Rn>{!}, <registers>{^}
Example(s):
        LDMLS R8, {R2,R4,R6,R9,R10,R12,R13,R14}
        POPLS {R2,R4,R6,R9,R10,R12,R13,R14}

Multiply Accumulate instruction
MLA fields:| cond | 0000001 | S |   Rd |   Rn |   Rs | 1001 |   Rm |
Bits:      | 1001 | 1001100 | 1 | 1000 | 0111 | 0110 | 0101 | 0100 |
Values:    |    9 |      76 | 1 |    8 |    7 |    6 |    5 |    4 |
Syntax: MLA{<cond>}{S} <Rd>, <Rm>, <Rs>, <Rn>
Examples(s):
        MLALSS R8, R4, R6, R7

Multiply instruction
MUL fields:| cond | 0000000 | S |   Rd |  SBZ |   Rs | 1001 |   Rm |
Bits:      | 1001 | 1001100 | 1 | 1000 | 0111 | 0110 | 0101 | 0100 |
Values:    |    9 |      76 | 1 |    8 |    7 |    6 |    5 |    4 |
Syntax: MUL{<cond>}{S} <Rd>, <Rm>, <Rs>
Examples(s):
        MULLSS R8, R4, R6
*/
