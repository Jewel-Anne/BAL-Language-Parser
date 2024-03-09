/*
* Parser or Syntax Analyzer
* 
* BSCS 3-1N GROUP 4 
*
* Members:
* Balmadrid, Vince
* Campo, Jeslen
* Gero, Michaella
* Pagcanlungan, Evitha
* Reyes, Jewel Anne 
* Velarde, Mia Jamille
*
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include<ctype.h>

struct node {
   char statement[50];
   char tokentype[50];
   struct node *next;
};
enum tokenTypes {
	Void_Key, 
	Integer_dt, String_dt, integerLiteral, StringLiteral, Operator, Relational_Operator, add_Operator, mul_Operator, Boolean, ifKey, elseKey, moreIfKey, Keyword,
	Noiseword, Terminator, Comment, Comma, Delimiter_OpenBrack, Delimiter_CloseBrack, Delimiter_OpenParen, Delimiter_CloseParen, Delimiter_Quote, Delimiter_SingQuote, 
	Print_Key, Scan_Key, SLoop_Key, ELoop_Key, Char_dt, charLiteral, Float_dt, floatLiteral, Double_dt, doubleLiteral, Bool_dt, boolLiteral, Delimiter_Colon,
	switchKey, caseKey, defaultKey, stopKey
};

char tokenTypes [10000][150];

char errormessage[150];
void printList();
void insertTokens(char statement[], char tokens[]);

int isAssignmentOperator(int mark);

int isInt(int mark);
int isFloat(int mark);
int isDouble(int mark);
int isBool(int mark);

int isComma(int mark);
int isTerminator(int mark);
int isIdentifier(int mark);
int isOBrack(int mark);
int declarationChar (char tokenTypes[][150]);
int declarationBool (char tokenTypes[][150]);
int expressionStatement(char tokenTypes[][150]);
int parser(char tokenTypes[][150]);
int declaration(char tokenTypes[][150]);
int declarationString(char tokenTypes[][150]);
int scanStatement(char tokenTypes[][150]);
int printStatement(char tokenTypes[][150]);
int StartStatement(char tokenTypes[][150]);
int assignmentStatement(char tokenTypes[][150]);
int ifStatement(char tokenTypes[][150]);

int isArithmetic(int mark);


int isQuote(int mark);
struct node *head2 = NULL;
struct node *current2 = NULL;

int i =0, ctr =0, line =0, checker = 1, pass = 0, x = 0;
int saveTokenMark;

int main(){
	char strFilename[50];
	char statement[1000], token[1000];
	struct node ptr; 
	FILE * ptrs;
	
	

    printf("*NOTE: Our Lexer output filename is \"SymbolTable.teks\"\n");
	printf("Enter Filename: ");
	scanf("%s", &strFilename);
	ptrs = fopen(strFilename,"rw+");
	
	
	while(fscanf(ptrs, "%s %s", statement, token)!= EOF)	
	{
		insertTokens(statement,token);
		strcpy(tokenTypes[i],token);
		i++;
	}
			
	while(ctr<=i-1)
	{
		checker = parser(tokenTypes);
		if(checker == 1)
		{
			printf("Valid statement on line %d.\n",++line);
		}
		else if (checker == 2)
		{
			printf("Delimiter Close Bracket in line %d.\n",++line);
		}
		else if(checker == 3)
		{
			++line;
		}
		else if (checker == 0)
		{
			printf("Invalid statement on line %d.\n",++line);
		}
	}
}

void insertTokens(char statement[], char tokens[]) {
    struct node *link = (struct node*) malloc(sizeof(struct node));
	
    strcpy(link->statement,statement);
	strcpy(link->tokentype,tokens);

    link->next = head2;
	
    head2 = link;
}

int parser(char tokenTypes[][150]){
	if(strcmp(tokenTypes[ctr],"Integer_dt")==0){
		ctr++;
		return declaration(tokenTypes);
	}
	else if(strcmp(tokenTypes[ctr],"Float_dt")==0){
		ctr++;
		return declaration(tokenTypes);
	}
	else if(strcmp(tokenTypes[ctr],"Double_dt")==0){
		ctr++;
		return declaration(tokenTypes);
	}
	else if(strcmp(tokenTypes[ctr],"Bool_dt")==0){
		ctr++;
		return declaration(tokenTypes);
	}
	else if(strcmp(tokenTypes[ctr],"Char_dt")==0){
		ctr++;
		return declarationChar(tokenTypes);
	}
	else if(strcmp(tokenTypes[ctr],"String_dt")==0){
		ctr++;
		return declarationString(tokenTypes);
	}
	else if(strcmp(tokenTypes[ctr],"Scan_Key")==0){
		ctr++;
		return scanStatement(tokenTypes);
	}
	else if(strcmp(tokenTypes[ctr],"Print_Key")==0){
		ctr++;
		return printStatement(tokenTypes);
	}
	else if(strcmp(tokenTypes[ctr],"Void_Key")==0){
		ctr++;
		return StartStatement(tokenTypes);
	}
	else if(strcmp(tokenTypes[ctr],"ifKey")==0){
		ctr++;
		return ifStatement(tokenTypes);
	}
	else if(strcmp(tokenTypes[ctr],"elseKey")==0){
		ctr++;
		return elseStatement(tokenTypes);
	}
	else if(strcmp(tokenTypes[ctr],"SLoop_Key")==0){
		ctr++;
		return doStatement(tokenTypes);
	}
	else if(strcmp(tokenTypes[ctr],"ELoop_Key")==0){
		ctr++;
		return whileStatement(tokenTypes);
	}
	else if(strcmp(tokenTypes[ctr],"switchKey")==0){
		ctr++;
		return switchStatement(tokenTypes);
	}
	else if(strcmp(tokenTypes[ctr],"caseKey")==0){
		ctr++;
		return caseStatement(tokenTypes);
	}
	else if(strcmp(tokenTypes[ctr],"defaultKey")==0){
		ctr++;
		return defaultStatement(tokenTypes);
	}
	else if(strcmp(tokenTypes[ctr],"stopKey")==0){
		ctr++;
		return stopStatement(tokenTypes);
	}
	else if(strcmp(tokenTypes[ctr],"Identifier")==0){
		ctr++;
		return assignmentStatement(tokenTypes);
	}
	else if(strcmp(tokenTypes[ctr],"Delimiter_CloseBrack")==0){
		ctr++;
		if(strcmp(tokenTypes[ctr],"ELoop_Key")==0){
			ctr++;
			return whileStatement(tokenTypes);
		}
		else
		{
			return 2;
		}
	}
	else if(strcmp(tokenTypes[ctr],"Comment")==0){
		ctr++;
		return 3;
	}
	
	return 0;
}

int StartStatement(char tokenTypes[][150]){
	int dataType = ctr;
	if(isIdentifier(ctr)==1)
	{
		if(isOparen(ctr)==1)
		{
			if(isCparen(ctr)==1)
			{
				if(isOBrack(ctr)==1)
				{
					return 1;
				}
				else
				{
					ctr++;
					return 0;
				}
			}
			else
			{
				ctr++;
				return 0;
			}
		}
		else
		{
			ctr++;
			return 0;
		}
	}
	else
	{
		ctr++;
		return 0;
	}
	
}

int printStatement(char tokenTypes[][150]){
	int dataType = ctr; 
	if(isOparen(ctr)==1)
	{
		label:
		if(isIdentifier(ctr)==1)
		{
				if(isCparen(ctr)==1)
				{
					if(isTerminator(ctr)==1)
					{
						return 1;
					}
				
					else 
					{
						ctr++;
						return 0;
					}
					
				}	
				else if(isAddOpr(ctr)==1)
				{
					goto label;
				}
				else if(isMulOpr(ctr)==1)
				{
					goto label;
				}
				else 
				{
					ctr++;
					return 0;
				}

		}
		else if(isQuote(ctr)==1)
		{
			 if(isString(ctr)==1)
			 {
				 if(isQuote(ctr)==1)
				 {
					if(isCparen(ctr)==1)
					{
						if(isTerminator(ctr)==1)
						{
							return 1;
						}
						else 
						{
							ctr++;
							return 0;
						}
					
					}
					else if(isAddOpr(ctr)==1)
					{
						goto label;
						
					}
					else if(isMulOpr(ctr)==1)
					{
						goto label;
						
					}
				}
				else
				{
					ctr++;
					return 0;
				}
	
			 }
		}
		else 
		{
			ctr++;
			return 0;
		}	
	}
	else 
	{
		ctr++;
		return 0;
	}	
}

int ifStatement(char tokenTypes[][150]){
	int dataType = ctr; 
	if(isOparen(ctr)==1)
	{
		if(isIdentifier(ctr)==1)
		{
			if(isConditionExp(ctr)==1)
			{
				if(isInt(ctr)==1 || isFloat(ctr)== 1)
				{
					if(isCparen(ctr)==1)
					{
						if(isOBrack(ctr)==1)
						{
							return 1;
							
						}
						else
						{
							ctr++;
							return 0;
						}
					}
					else
					{
						ctr++;
						return 0;
					}
				}
				else if(isIdentifier(ctr)==1)
				{
					if(isCparen(ctr)==1)
					{
						if(isOBrack(ctr)==1)
						{
							return 1;
							
						}
						else
						{
							ctr++;
							return 0;
						}
					}
				}
				else if(isString(ctr)==1)
				{
					if(isCparen(ctr)==1)
					{
						if(isOBrack(ctr)==1)
						{
							return 1;
							
						}
						else
						{
							ctr++;
							return 0;
						}
					}
				}
				else
				{
					ctr++;
					return 0;
				}
				
			}
			else
			{
				ctr++;ctr++;ctr++;ctr++;
				return 0;
			}
		}
		else if(isInt(ctr)==1)
		{
			if(isConditionExp(ctr)==1)
			{
				if(isInt(ctr)==1)
				{
					if(isCparen(ctr)==1)
					{
						if(isOBrack(ctr)==1)
						{
							return 1;
							
						}
						else
						{
							ctr++;
							return 0;
						}
					}
					else
					{
						ctr++;
						return 0;
					}
				}
				else if(isIdentifier(ctr)==1)
				{
					if(isCparen(ctr)==1)
					{
						if(isOBrack(ctr)==1)
						{
							return 1;
							
						}
						else
						{
							ctr++;
							return 0;
						}
					}
				}
				else if(isString(ctr)==1)
				{
					if(isCparen(ctr)==1)
					{
						if(isOBrack(ctr)==1)
						{
							return 1;
							
						}
						else
						{
							ctr++;
							return 0;
						}
					}
				}
			}
			else
			{
				ctr++;
				return 0;
			}
		}
		else if(isString(ctr)==1)
		{
			if(isConditionExp(ctr)==1)
			{
				if(isInt(ctr)==1)
				{
					if(isCparen(ctr)==1)
					{
						if(isOBrack(ctr)==1)
						{
							return 1;
							
						}
						else
						{
							ctr++;
							return 0;
						}
					}
					else
					{
						ctr++;
						return 0;
					}
				}
				else if(isIdentifier(ctr)==1)
				{
					if(isCparen(ctr)==1)
					{
						if(isOBrack(ctr)==1)
						{
							return 1;
							
						}
						else
						{
							ctr++;
							return 0;
						}
					}
				}
				else if(isString(ctr)==1)
				{
					if(isCparen(ctr)==1)
					{
						if(isOBrack(ctr)==1)
						{
							return 1;
							
						}
						else
						{
							ctr++;
							return 0;
						}
					}
				}
			}
			else
			{
				ctr++;
				return 0;
			}
		}
		else
		{
			ctr++;
			return 0;
		}
	}
	else
	{
		ctr++;
		return 0;
	}
}

int elseStatement(char tokenTypes[][150]){
	int dataType = ctr;
	if(isOBrack(ctr)==1)
	{
		return 1;
	}
}

int declaration(char tokenTypes[][150]){
	int dataType = ctr; 
	if(isIdentifier(ctr)==1)
	{
		pass = 1;
		if(isAssignmentOperator(ctr)==1)
		{
			if(isIdentifier(ctr)==1)
			{
		
				if(isComma(ctr)==1)
				{
					return declaration(tokenTypes);
				}
				else if(isTerminator(ctr)==1)
				{
					return 1;
				}
				else
				{
					ctr--;
					return 0;
				}
				
			}
			else if(isInt(ctr)==1)
			{

				if(isTerminator(ctr)==1)
				{
					return 1;
				}
				else if(isComma(ctr)==1)
				{
					return declaration(tokenTypes);
				}
				else
				{
					ctr--;
					return 0;
				}
			}
			else if(isFloat(ctr)==1)
			{
				if(isTerminator(ctr)==1)
				{
					return 1;
				}
				else if(isComma(ctr)==1)
				{
					return declaration(tokenTypes);
				}
				else
				{
					ctr--;
					return 0;
				}
			}
			else if(isDouble(ctr)==1)
			{
				if(isTerminator(ctr)==1)
				{
					return 1;
				}
				else if(isComma(ctr)==1)
				{
					return declaration(tokenTypes);
				}
				else
				{
					ctr--;
					return 0;
				}
			}
			else if(isBool(ctr)==1)
			{
				if(isTerminator(ctr)==1)
				{
					return 1;
				}
				else
				{
					ctr++;
					return 0;
				}
				
			}
			else
			{
				ctr++;
				return 0;
			}
			
		}
		else if(isTerminator(ctr)==1)
		{
			return 1;
		}
		else if(isComma(ctr)==1)
		{
			return 	declaration(tokenTypes);
		}
		else 
		{
			ctr++;
			return 0;
		}

	}
	else if(strcmp(tokenTypes[ctr],"Wrong_Input")==0)
	{
		ctr++;ctr++;ctr++;ctr++;
		return 0;
	}
}

int assignmentStatement(char tokenTypes[][150]){
	int dataType = ctr; 
	if(isAssignmentOperator(ctr) == 1)
	{
			if(isIdentifier(ctr) == 1 || isInt(ctr) == 1 || isFloat(ctr) == 1)
			{
				if(isComma(ctr)==1)
				{
					return declaration(tokenTypes);
				}
				else if(isMulOpr(ctr)==1)
				{
					return expressionStatement(tokenTypes);
				}
				else if(isAddOpr(ctr)==1)
				{
					return expressionStatement(tokenTypes);
				}
				else if(isLogical(ctr)==1)
				{
					return expressionStatement(tokenTypes);
				}
				else if(isTerminator(ctr)==1)
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
			else
			{
				ctr++;
				return 0;
			}
	}
	else if(isOperator(ctr)==1)
	{
		if(isTerminator(ctr)==1)
		{
			return 1;
		}
	}
	else if(isComma(ctr)==1){
		return assignmentStatement(tokenTypes);
	}
	else
	{
		ctr++;
		return 0;
	}
}

int expressionStatement(char tokenTypes[][150]){
	int dataType = ctr; 
	if(isIdentifier(ctr)==1 || isInt(ctr)==1)
	{
		if(isTerminator(ctr)==1)
		{
			return 1;
		}
		else if(isMulOpr(ctr)==1)
		{
			return expressionStatement(tokenTypes);
		}
		else if (isAddOpr(ctr)==1)
		{
			return expressionStatement(tokenTypes);
		}
		else if(isLogical(ctr)==1)
		{
			return expressionStatement(tokenTypes);
		}
		else
		{
			ctr++;
			return 0;
		}
	}
}

int declarationString(char tokenTypes[][150]){
	int dataType = ctr; 
	if(isIdentifier(ctr)==1)
	{
		if(isAssignmentOperator(ctr)==1)
		{
			if(isIdentifier(ctr)==1)
			{
				if(isComma(ctr)==1)
				{
					declaration(tokenTypes);
				}
				else if(isTerminator(ctr)==1)
				{
					return 1;
				}
			}
			else if(isQuote(ctr)==1)
			{
				 if(isString(ctr)==1)
				 {
					 if(isQuote(ctr)==1)
					 {
						if(isTerminator(ctr)==1)
						{
							return 1;
						}
						else if(isComma(ctr)==1)
						{
							return 	declarationString(tokenTypes);
						}
					 }
				 }
			 }
			 else
			 {
			 	ctr++;ctr++;
			 	return 0;
			 }
			
		}
		else if(isTerminator(ctr)==1)
		{
			return 1;
		}
		else if(isComma(ctr)==1)
		{
			return 	declaration(tokenTypes);
		}
		else {
			ctr++;
			return 0;
		}

	}
	 

	else 
	return 0;
}

int declarationChar(char tokenTypes[][150]){ 
	int dataType = ctr; 
	if(isIdentifier(ctr)==1)
	{
		if(isAssignmentOperator(ctr)==1)
		{
			if(isIdentifier(ctr)==1)
			{
				if(isComma(ctr)==1)
				{
					declaration(tokenTypes);
				}
				else if(isTerminator(ctr)==1)
				{
					return 1;
				}
			}
			else if(isSingQuote(ctr)==1)
			{
				 if(isChar(ctr)==1)
				 {
					 if(isSingQuote(ctr)==1)
					 {
						if(isTerminator(ctr)==1)
						{
							return 1;
						}
						else if(isComma(ctr)==1)
						{
							return 	declarationChar(tokenTypes);
						}
					 }
					 else
					 {
					 	ctr++;
					 	return 0;
					 }
				 }
				 else
				 {
				 	ctr++;
				 	return 0;
				 }
			 }
			 else
			 {
			 	ctr++;
			 	return 0;
			 }
			
		}
		else if(isTerminator(ctr)==1)
		{
			return 1;
		}
		else if(isComma(ctr)==1)
		{
			return 	declaration(tokenTypes);
		}
		else 
		{
			ctr++;
			return 0;
		}

	}
	else 
	{
	ctr++;
	return 0;
	}
}

int scanStatement(char tokenTypes[][150]){
	int dataType = ctr; 
	if(isOparen(ctr)==1)
	{
		if(isIdentifier(ctr)==1)
		{
				if(isCparen(ctr)==1)
				{
					if(isTerminator(ctr)==1)
					{
						return 1;
					}
				
					else 
					{
						ctr++;
						return 0;
					}
				}	
				else 
				{
					ctr++;
					return 0;
				}
		}
		else 
		{
			ctr++;
			return 0;
		}	
	}

	else 
	{
		ctr++;
		return 0;
	}

}

int doStatement(char tokenTypes[][150]){
	int dataType = ctr;
	if(isOBrack(ctr)==1)
	{
		return 1;
	}
	else
	{
		ctr++;
		return 0;
	}
}

int whileStatement(char tokenTypes[][150]){
	int dataType = ctr;
	if(isOparen(ctr)==1)
	{
		if(isIdentifier(ctr)==1)
		{
			if(isConditionExp(ctr)==1)
			{
				if(isInt(ctr)==1  || isFloat(ctr)== 1)
				{
					if(isCparen(ctr)==1)
					{
						if(isTerminator(ctr)==1)
						{
							return 1;
						}
					}
					else
					{
						ctr++;
						return 0;
					}
				}
				else if(isIdentifier(ctr)==1)
				{
					if(isCparen(ctr)==1)
					{
						if(isTerminator(ctr)==1)
						{
							return 1;
						}
					}
				}
				else if(isString(ctr)==1)
				{
					if(isCparen(ctr)==1)
					{
						if(isTerminator(ctr)==1)
						{
							return 1;
						}
					}
				}
				else
				{
					ctr++;ctr++;ctr++;ctr++;
					return 0;
				}
				
				
			}
			else
			{
				ctr++;ctr++;ctr++;ctr++;
				return 0;
			}
		}
		else if(isInt(ctr)==1)
		{
			if(isConditionExp(ctr)==1)
			{
				if(isInt(ctr)==1)
				{
					if(isCparen(ctr)==1)
					{
						return 1;
					}
					else
					{
						ctr++;
						return 0;
					}
				}
				else if(isIdentifier(ctr)==1)
				{
					if(isCparen(ctr)==1)
					{
						return 1;
					}
				}
				else if(isString(ctr)==1)
				{
					if(isCparen(ctr)==1)
					{
						return 1;
					}
				}
			}
			else
			{
				ctr++;
				return 0;
			}
		}
		else if(isString(ctr)==1)
		{
			if(isConditionExp(ctr)==1)
			{
				if(isInt(ctr)==1)
				{
					if(isCparen(ctr)==1)
					{
						return 1;
					}
					else
					{
						ctr++;
						return 0;
					}
				}
				else if(isIdentifier(ctr)==1)
				{
					if(isCparen(ctr)==1)
					{
						return 1;
					}
				}
				else if(isString(ctr)==1)
				{
					if(isCparen(ctr)==1)
					{
						return 1;
					}
				}
			}
			else
			{
				ctr++;
				return 0;
			}
		}
		else
		{
			ctr++;
			return 0;
		}
	}
	else
	{
		ctr++;
		return 0;
	}
}

int switchStatement(char tokenTypes[][150]){
	int dataType = ctr;
	if(isOparen(ctr)==1)
	{
		if(isIdentifier(ctr)==1 || isInt(ctr)==1)
		{
			if(isCparen(ctr)==1)
			{
				if(isOBrack(ctr)==1)
				{
					return 1;
				}
				else
				{
					return 1;
				}
			}
			else
			{
				ctr++;
				return 0;
			}
		}
		else if(isSingQuote(ctr)==1)
		{
			if(isChar(ctr)==1)
			{
				if(isSingQuote(ctr)==1)
				{
					if(isCparen(ctr)==1)
					{
						if(isOBrack(ctr)==1)
						{
							return 1;
						}
						else
						{
							ctr++;
							return 0;
						}
					}
					else
					{
						ctr++;
						return 0;
					}
				}
				else
				{
					ctr++;
					return 0;
				}
			}
			else
			{
				ctr++;
				return 0;
			}
		}
		else
		{
			ctr++;
			return 0;
		}
	}
	else
	{
		ctr++;
		return 0;
	}
}

int caseStatement(char tokenTypes[][150]){
	int dataType = ctr;
	if(isInt(ctr)==1)
	{
		if(isColon(ctr)==1)
		{
			return 1;
		}
		
	}
	else if(isSingQuote(ctr)==1)
	{
		if(isChar(ctr)==1)
		{
			if(isSingQuote(ctr)==1)
			{
				if(isColon(ctr)==1)
				{
					return 1;
				}
				
			}
			else
			{
				ctr++;
				return 0;
			}
		}
		else
		{
			ctr++;
			return 0;
		}
	}
	else
	{
		ctr++;
		return 0;
	}
}


int stopStatement(char tokenTypes[][150]){
	int dataType = ctr;
	if(isTerminator(ctr)==1)
	{
		return 1;
	}
}


int defaultStatement(char tokenTypes[][150]){
	int dataType = ctr;
	if(isColon(ctr)==1)
	{
		return 1;
	}
	else if(isTerminator(ctr)==1)
	{
		if(isOBrack(ctr)==1)
		{
			return 1;
		}
		else
		{
			ctr++;
			return 0;
		}
	}
}

int isAddOpr(int mark){
	
	if(strcmp(tokenTypes[mark],"add_Operator")==0){
		ctr++;	
		return 1;
	}

	return 0;
}

int isMulOpr(int mark){
	
	if(strcmp(tokenTypes[mark],"mul_Operator")==0){
		ctr++;	
		return 1;
	}

	return 0;
}

int isLogical(int mark){
	
		if(strcmp(tokenTypes[mark],"Log_Operator")==0){
		ctr++;	
		return 1;
	}

	return 0;
}

int isConditionExp(int mark){
	
		if(strcmp(tokenTypes[mark],"Relational_Operator")==0){
		ctr++;	
		return 1;
	}

	return 0;
	
}

int isQuote(int mark){
		if(strcmp(tokenTypes[mark],"Delimiter_Quote")==0){
		ctr++;	
		return 1;
	}

	return 0;
}

int isSingQuote(int mark){
		if(strcmp(tokenTypes[mark],"Delimiter_SingQuote")==0){
		ctr++;	
		return 1;
	}

	return 0;
}

int isOparen(int mark){
	if(strcmp(tokenTypes[mark],"Delimiter_OpenParen")==0){
		ctr++;	
		return 1;
	}
	return 0;
}

int isCparen(int mark){
	if(strcmp(tokenTypes[mark],"Delimiter_CloseParen")==0){
		ctr++;	
		return 1;
	}
	return 0;
}

int isString(int mark){
		if(strcmp(tokenTypes[mark],"StringLiteral")==0){
		ctr++;	
		pass=1;
		return isString(ctr);
	}
	else if(strcmp(tokenTypes[mark],"StringLiteral")!=0&&pass>0){
		pass =0;
		return 1;
	}
	return 0;
}

int isChar(int mark){
		if(strcmp(tokenTypes[mark],"charLiteral")==0){
		ctr++;	
		pass=1;
		return isString(ctr);
	}
	else if(strcmp(tokenTypes[mark],"charLiteral")!=0&&pass>0){
		pass =0;
		return 1;
	}
	return 0;
}

int isIdentifier(int mark){
		if(strcmp(tokenTypes[mark],"Identifier")==0){
	ctr++;	
		return 1;
	}
	return 0;
}

int isAssignmentOperator(int mark){
		if(strcmp(tokenTypes[mark],"Assign_Operator")==0){
	ctr++;	
		return 1;
	}
	return 0;
}


int isTerminator(int mark){
	if(strcmp(tokenTypes[mark],"Terminator")==0){
		ctr++;	
		return 1;
	}
	return 0;
	
}

int isInt(int mark){
	if(strcmp(tokenTypes[mark],"integerLiteral")==0){
	ctr++;	
		return 1;
	}
	return 0;
}

int isFloat(int mark){
	if(strcmp(tokenTypes[mark],"floatLiteral")==0){
	ctr++;	
		return 1;
	}
	return 0;
}

int isDouble(int mark){
	if(strcmp(tokenTypes[mark],"doubleLiteral")==0){
	ctr++;	
		return 1;
	}
	return 0;
}

int isBool(int mark){
	if(strcmp(tokenTypes[mark],"boolLiteral")==0){
	ctr++;	
		return 1;
	}
	return 0;
}


int isComma(int mark){
	if(strcmp(tokenTypes[mark],"Comma")==0){
	ctr++;	
		return 1;
	}
	return 0;
}

int isColon(int mark)
{
	if(strcmp(tokenTypes[mark],"Delimiter_Colon")==0)
	{
		ctr++;
		return 1;
	}
	return 0;
}

int isOBrack(int mark){
	if(strcmp(tokenTypes[mark],"Delimiter_OpenBrack")==0){
	ctr++;	
		return 1;
	}
	return 0;
}

int isOperator(int mark){
	if(strcmp(tokenTypes[mark],"Operator")==0){
	ctr++;	
		return 1;
	}
	return 0;
}
