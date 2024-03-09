/*
* Lexer or Lexical Analysis
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

#include<stdio.h>
#include<conio.h> 
#include<stdlib.h> 
#include<ctype.h> 
#include<malloc.h> 
#include<string.h>
#include<stdbool.h>


struct list
{
    char character;
    struct list *next, *prev;
}*head, *tail, *current, *checker;

struct tokenTable
{
	char ch;
    struct tokenTable *next, *p;
}*head1, *tail1, *curr, *chkr;

FILE *source, *output, *display, *table;
int flag = 0, line = 0;

void readSourceFile();
void lexicalAnalysis();
void outputFile(int ln);
void printChar(char c);
void displayOutput();
void readTable();

 int main(){
	readSourceFile();
	readTable();
	output = fopen("SymbolTable.txt","w+");
    fclose(output);
	lexicalAnalysis();
	displayOutput();
	getch();
	return 0;
	
 }
 
 void lexicalAnalysis(){
 	checker = head;
 	
 	while(checker!=NULL){
 		
 		if(checker->character == '\n'){
 			checker = checker->next;
		 }//for the lines
		 
		else if(checker->character == ' ' || checker->character == '\t'){
			checker = checker->next;
		}//ignores spaces
		
 		else if(checker->character == '{'){
 			printChar(checker->character);  checker = checker->next; outputFile(2);
		}//left brace
		
		else if(checker->character == '}'){
 			printChar(checker->character);  checker = checker->next; outputFile(3);
		}//right brace
		
		else if(checker->character == '('){
 			printChar(checker->character);  checker = checker->next; outputFile(5);
		}//left parenthesis
		
		else if(checker->character == ')'){
 			printChar(checker->character);  checker = checker->next; outputFile(6);
		}//right parenthesis
		
		else if(checker->character == ';'){
 			printChar(checker->character);  checker = checker->next; outputFile(4);
		}//semicolon or separator
		
		else if(checker->character == ','){
 			printChar(checker->character);  checker = checker->next; outputFile(56);
		}//comma
		
		else if(checker->character == ':'){
 			printChar(checker->character);  checker = checker->next; outputFile(59);
		}//for case
		
		else if(checker->character == '+'){
 			printChar(checker->character);  checker = checker->next;
 			if(checker->character == '='){
 				printChar(checker->character); checker = checker->next; outputFile(14);
 			}
			else if(checker->character == '+'){
 				printChar(checker->character); checker = checker->next; outputFile(18);
			}
			else
				outputFile(7);
		}//add operator, shorthand, increment
		
		else if(checker->character == '-'){
 			printChar(checker->character);  checker = checker->next; 
 			if(checker->character == '='){
 				printChar(checker->character); checker = checker->next; outputFile(15);
 			}
			else if(checker->character == '-'){
 				printChar(checker->character); checker = checker->next; outputFile(19);
			}
			else
				outputFile(8);
		}//subtract opr, shorthand, decrement
		
		else if(checker->character == '*'){
 			printChar(checker->character);  checker = checker->next; 
 			if(checker->character == '='){
 				printChar(checker->character); checker = checker->next; outputFile(16);
 			}
 			else
 				outputFile(9);
		}//mult operator, shorthand,
		
		else if(checker->character == '%'){
 			printChar(checker->character);  checker = checker->next; 
 			outputFile(11);
		}//mod operator, shorthand
		
		else if(checker->character == '/'){
 			printChar(checker->character);  checker = checker->next; 
 			if(checker->character == '='){
 				printChar(checker->character); checker = checker->next; outputFile(17);
 			}
			 else
			 	outputFile(10);
		}//division opr, shorthand
		
		else if(checker->character == '~'){
 			printChar(checker->character);  checker = checker->next; 
 			while(checker->character != '\n'){
 					if(checker->character ==' '){
					checker = checker->next;
					}
					else{	
					printChar(checker->character); checker = checker->next;
					}
				 }
				 
 			if(checker->character == '~'){
 				printChar(checker->character); checker = checker->next;
 				while(checker->character != '\n'){
 					if(checker->character ==' '){
					checker = checker->next;
					}
					else{	
					printChar(checker->character); checker = checker->next;
					}
				 }
				 outputFile(31);
			 }
			 else
			 	outputFile(30);
		}//singlelinecomment, blockcomment
		
		else if(checker->character == '?'){
 			printChar(checker->character);  checker = checker->next; 
 			outputFile(12);
		}//integer division
		
		else if(checker->character == '^'){
 			printChar(checker->character);  checker = checker->next; 
 			outputFile(13);
		}//exponentialization
		
		else if(checker->character == '='){
 			printChar(checker->character);  checker = checker->next;
 			if(checker->character == '='){
 					printChar(checker->character); checker = checker->next; outputFile(24);
			 }
			else
 				outputFile(20);
		}//assign operator, conditional opr
		
		else if(checker->character == '!'){
 			printChar(checker->character);  checker = checker->next;
 			if(checker->character == '='){
 					printChar(checker->character); checker = checker->next; outputFile(27);
			 }
			else
 				outputFile(23);
		}//not operator, cond operator
		
		else if(checker->character == '<'){
 			printChar(checker->character);  checker = checker->next;
 			if(checker->character == '='){
 					printChar(checker->character); checker = checker->next; outputFile(29);
			 }
			 else
				outputFile(26);
		}//less than cond opr
		
		else if(checker->character == '>'){
 			printChar(checker->character);  checker = checker->next;
 			if(checker->character == '='){
 					printChar(checker->character); checker = checker->next; outputFile(28);
			 }else
				outputFile(25);
		}//greater than cond opr
		
		else if(checker->character == '&'){
 			if(checker->next->character == '&'){
 				printChar(checker->character);
				printChar(checker->next->character);
				checker = checker->next->next;
				outputFile(21);
			 }	
		}//and opr
		
		else if(checker->character == '|'){
 			if(checker->next->character == '|'){
 				printChar(checker->character);
				printChar(checker->next->character);
				checker = checker->next->next;
				outputFile(22);
			 }	
		}//or opr	
		
		else if(checker->character == '"'){
			printChar(checker->character); checker = checker->next; outputFile(57);
			while(checker->character!='"'){
				if(checker->character ==' '){
					checker = checker->next;
				}
				else{	
				printChar(checker->character); checker = checker->next;
				}
				if(checker->character =='"') {
					outputFile(47); 
				}
			}
			printChar(checker->character); checker = checker->next; outputFile(57);
		}//for string constant
		
		else if(checker->character == '\''){
			printChar(checker->character); checker = checker->next; outputFile(58);
			while(checker->character!='\''){
				printChar(checker->character); checker = checker->next; 
				if(checker->character =='\'')
					outputFile(48);
			}
			printChar(checker->character); checker = checker->next; outputFile(58);
		}//for character constant
		
		else if(isdigit(checker->character)){
			bool x = true;
			while(isdigit(checker->character)){
				printChar(checker->character);
				checker = checker->next;
					if(checker->character == '.') 
					{
						printChar(checker->character);
						checker = checker->next;
							while(isdigit(checker->character))
							{
								printChar(checker->character);
								checker = checker->next;
							}
						outputFile(50);
						x = false;
					}
				}
				if(x)
				{	
				outputFile(49);
				}
			}//int or float const
		
 		else if(isalpha(checker->character)){
 			switch(checker->character){
 				
 				case 'b': //booly & bounce
 				{
 						printChar(checker->character);  checker = checker->next;
 						if(checker->character == 'o')
 						{
 							printChar(checker->character);  checker = checker->next;
 							if(checker->character == 'o')
 							{
 								printChar(checker->character);  checker = checker->next;
 								if(checker->character == 'l')
 								{
 									printChar(checker->character);  checker = checker->next;
 									if(checker->character == 'y')
 									{
 									    printChar(checker->character);  checker = checker->next;
 								       	if(checker->character == ' ' || checker->character == '\t' || checker->character == '\n' )
 								       	{
 									       outputFile(40);
    									}
    									else 
    									{
     									    goto identify;
    									}
    								 }
    								 else
    								 {
    								    goto identify;
    								 }
    							 }
    							 else
    							 {
    								goto identify;
    							 }
    					  	 }
							else if(checker -> character == 'u')
							{
								printChar(checker -> character); checker = checker -> next;
								if(checker -> character == 'n'){
									printChar(checker -> character); checker = checker -> next;
									if(checker -> character == 'c'){
									    printChar(checker -> character); checker = checker -> next;
									    if(checker -> character == 'e'){
										    printChar(checker -> character); checker = checker -> next;
        										if(checker -> character == ' ' || checker -> character == '\t' || checker -> character == '\n' || checker -> character == '(')
        										{
        											outputFile(33);
        										}
												else{
        									    	goto identify;
        								    	}
        								}
        								else{
        							    	goto identify;
        						    	}
							    	}
							    	else{
								    	goto identify;
							    	}
								}
						    	else{
							    	goto identify;
						    	}
							}
    					  	else
    					  	{
    							goto identify;
    					  	}
 						 }
 						 else
 			             {
    						goto identify;
 			             }    	
					break;
				 } //case b

 				case 'c': //char
				{
 							printChar(checker -> character); checker = checker -> next;
 							if(checker -> character == 'h')
 							{
 								printChar(checker -> character); checker = checker -> next;
 								if(checker -> character == 'a')
 								{
 									printChar(checker -> character); checker = checker -> next;
 									if(checker -> character =='r')
 									{
 										printChar(checker -> character); checker = checker -> next;
 										if(checker -> character == ' ' || checker -> character == '\t' || checker -> character == '\n' || checker -> character == '(')
 										{
 											outputFile(44);
										}
										else
										{
											goto identify;
										}
									}
									else
									{
										goto identify;
									}
								}
								else
								{
									goto identify;
								}
							}
							else
							{
								goto identify;
							}
						break;
					 }//case c
					 
				case 'd': //dobol
				{
					 	printChar(checker -> character); checker = checker -> next;
					 	if(checker -> character == 'o')
					 	{
					 		if(checker -> character == 'b')
					 			{
					 				printChar(checker -> character); checker = checker -> next;
					 				if(checker -> character == 'o')
					 					{
					 						printChar(checker -> character); checker = checker -> next;
        					 				if(checker -> character == 'l')
        					 				{
        					 				    	printChar(checker -> character); checker = checker -> next;
        					 						if(checker -> character == ' ' || checker -> character == '\t' || checker -> character == '\n' || checker -> character == '(')
        					 						{
        					 							outputFile(42);
        											}
        											else
        											{
        												goto identify;
        											}
        										}
        										else
        										{
        											goto identify;
        										}
        									}
        									else
        									{
        										goto identify;
        									}
        								}
        								else
        								{
        									goto identify;
        								}
        							}
        							else
        							{
        								goto identify;
        							}
						}//case d
					 
				case 'e': //elsa_paano_kung
				{
					printChar(checker -> character); checker = checker -> next;
					if(checker -> character == 'l')
					{
						printChar(checker -> character); checker = checker -> next;
						if(checker -> character == 's')
						{
							printChar(checker -> character); checker = checker -> next;
							if(checker -> character == 'a')
							{
								printChar(checker -> character); checker = checker -> next;
								if(checker -> character == ' ' || checker -> character == '\t' || checker -> character == '\n' || checker -> character == '(')
								{
									outputFile(38);
								}
								else if(checker -> character == '_')
    							{
    					 			printChar(checker -> character); checker = checker -> next;
    					 			if(checker -> character == 'p')
    					 			{
    					 				printChar(checker -> character); checker = checker -> next;
    					 				if(checker -> character == 'a')
    					 				{
    					 					printChar(checker -> character); checker = checker -> next;
    					 					if(checker -> character == 'a')
    					 					{
    					 					    printChar(checker -> character); checker = checker -> next;
    					 					    if(checker -> character == 'n')
    					 					    {
    					 					        printChar(checker -> character); checker = checker -> next;
    					 					        if(checker -> character == 'o')
    					 				        	{
    					 				        	    printChar(checker -> character); checker = checker -> next;
    					 					            if(checker -> character == '_')
    					 				            	{
    					 				            	    printChar(checker -> character); checker = checker -> next;
            					 					        if(checker -> character == 'k')
            					 				        	{
            					 				        	    printChar(checker -> character); checker = checker -> next;
                					 					        if(checker -> character == 'u')
                					 				        	{
                					 				        	    printChar(checker -> character); checker = checker -> next;
                    					 					        if(checker -> character == 'n')
                    					 				        	{
                    					 				        	    printChar(checker -> character); checker = checker -> next;
                        					 					        if(checker -> character == 'g')
                        					 				        	{
                                					 						printChar(checker -> character); checker = checker -> next;
                                					 						if(checker -> character == ' ' || checker -> character == '\t' || checker -> character == '\n' || checker -> character == '(')
                                					 						{
                                					 							outputFile(37);
                                											}
                                            								else
                                            								{
                                            									goto identify;
                                            								}
                                            							}
                                            							else
                                            							{
                                            								goto identify;
                                            							}
                                            						}
                                            						else
                                            						{
                                            							goto identify;
                                            						}
                                            					}
                                            					else
                                            					{
                                            						goto identify;
                                            					}
            					 				        	}
                                            				else
                                            				{
                                            					goto identify;
                                            				}
    					 				            	}
                                            			else
                                            			{
                                            				goto identify;
                                            			}
    					 				        	}
                                            		else
                                            		{
                                            			goto identify;
                                            		}
    					 					    }
                                            	else
                                            	{
                                            		goto identify;
                                            	}
    					 					}
                                            else
                                            {
                                            	goto identify;
                                            }
    					 				}
                                        else
                                        {
                                            goto identify;
                                        }
    					 			}
                                    else
                                	{
                                        goto identify;
                					}
    							}
                                else
                            	{
                                    goto identify;
                            	}
							}
                            else
                            {
                                goto identify;
                            }
						}
                        else
                        {
                            goto identify;
                        }
					}
                    else
                    {
                        goto identify;
                    }
                                            			
					break;
				} //case e
				
				case 'g': //giginteger & getchi
				{
					printChar(checker -> character); checker = checker -> next;
					if(checker -> character == 'i')
					{
						printChar(checker -> character); checker = checker -> next;
						if(checker -> character == 'g')
						{
							printChar(checker -> character); checker = checker -> next;
							if(checker -> character == 'i')
							{
								printChar(checker -> character); checker = checker -> next;
								if(checker -> character == 'n')
								{
								    printChar(checker -> character); checker = checker -> next;
    								if(checker -> character == 't')
    								{
    								    printChar(checker -> character); checker = checker -> next;
        								if(checker -> character == 'e')
        								{
        								    printChar(checker -> character); checker = checker -> next;
            								if(checker -> character == 'g')
            								{
            								    printChar(checker -> character); checker = checker -> next;
                								if(checker -> character == 'e')
                								{
                								    printChar(checker -> character); checker = checker -> next;
                    								if(checker -> character == 'r')
                    								{
                    									printChar(checker -> character); checker = checker -> next;
                    									if(checker -> character == ' ' || checker -> character == '\t' || checker -> character == '\n' || checker -> character == '(')
                    									{
                    										outputFile(41);
                    									}
                    									else
                    									{
                    										goto identify;
                    									}
                    								}
                    								else
                    								{
                    									goto identify;
                    								}
                    							}
                    							else
                    							{
                    								goto identify;
                    							}
                    						}
                    						else
                    						{
                    							goto identify;
                    						}
                    					}
                    					else
                    					{
                    						goto identify;
                    					}
    								}
                    				else
                    				{
                    					goto identify;
                    				}
								}
                    			else
                    			{
                    				goto identify;
                    			}
							}
                    		else
                    		{
                    			goto identify;
                    		}
						}
                    	else
                    	{
                    		goto identify;
                    	}
					}				
                    else if(checker -> character == 'e')
							{
							printChar(checker -> character); checker = checker -> next;
							if(checker -> character == 't')
							{
							    printChar(checker -> character); checker = checker -> next;
								if(checker -> character == 'c')
								{
								    printChar(checker -> character); checker = checker -> next;
    								if(checker -> character == 'h')
    								{
    								    printChar(checker -> character); checker = checker -> next;
        								if(checker -> character == 'i')
        								{
        									printChar(checker -> character); checker = checker -> next;
        									if(checker -> character == ' ' || checker -> character == '\t' || checker -> character == '\n' || checker -> character == '(')
        									{
        										outputFile(32);
        									}
                                        	else
                                        	{
                                        		goto identify;
                                        	}
        								}
                                    	else
                                    	{
                                    		goto identify;
                                    	}
    								}
                                	else
                                	{
                                		goto identify;
                                	}
								}
                            	else
                            	{
                            		goto identify;
                            	}
							}
                        	else
                        	{
                        		goto identify;
                        	}
						}
                    	else
                    	{
                    		goto identify;
                    	}
					break;
				} //case g
				
				case 'i': //istring
				{
					printChar(checker -> character); checker = checker -> next;
					if(checker -> character == 's')
					{	
						printChar(checker -> character); checker = checker -> next;
						if(checker -> character == 't')
						{
						    printChar(checker -> character); checker = checker -> next;
    						if(checker -> character == 'r')
    						{
    						    printChar(checker -> character); checker = checker -> next;
        						if(checker -> character == 'i')
        						{
        						    printChar(checker -> character); checker = checker -> next;
            						if(checker -> character == 'n')
            						{
            						    printChar(checker -> character); checker = checker -> next;
                						if(checker -> character == 'g')
                						{
                            				printChar(checker -> character); checker = checker -> next;
                            				if(checker -> character == ' ' || checker -> character == '\t' || checker -> character == '\n' || checker -> character == '(')
                            				{
                            					outputFile(45);
                            				}			
            								else
            								{
            									goto identify;
            								}
                						}			
            							else
            							{
            								goto identify;
            							}
            						}			
            						else
            						{
            							goto identify;
            						}
        						}			
            					else
            					{
            						goto identify;
            					}
    						}			
            				else
            				{
            					goto identify;
            				}
						}			
            			else
            			{
            				goto identify;
            			}
					}			
            		else
            		{
            			goto identify;
            		}
					break;
				} //case i
				
				case 'm': //mcfloat
				{
					printChar(checker -> character); checker = checker -> next;
					if(checker -> character == 'c')
					{
						printChar(checker -> character); checker = checker -> next;
						if(checker -> character == 'f')
						{
							printChar(checker -> character); checker = checker -> next;
							if(checker -> character == 'l')
							
								printChar(checker -> character); checker = checker -> next;
								if(checker -> character == 'o')
								{
									printChar(checker -> character); checker = checker -> next;
									if(checker -> character == 'a')
									{
									    printChar(checker -> character); checker = checker -> next;
    									if(checker -> character == 't')
    									{
    										printChar(checker -> character); checker = checker -> next;
    										if(checker -> character == ' ' || checker -> character == '\t' || checker -> character == '\n' || checker -> character == '(')
    										{
    											outputFile(43);
    										}
    										else
    										{
    											goto identify;
    										}
    									}
    									else
    									{
    										goto identify;
    									}
    								}
    								else
    								{
    									goto identify;
    								}
    							}
    							else
    							{
    								goto identify;
    							}
    						}
    						else
    						{
    							goto identify;
    						}
    					}
    					else
    					{
    						goto identify;
    					}
			    	} // case m
				
				case 'n': //nugagawen
				{
					printChar(checker -> character); checker = checker -> next;
					if(checker -> character == 'u')
					{
						printChar(checker -> character); checker = checker -> next;
						if(checker -> character == 'g')
						{
							printChar(checker -> character); checker = checker -> next;
							if(checker -> character == 'a')
							{
								printChar(checker -> character); checker = checker -> next;
								if(checker -> character == 'g')
								{
									printChar(checker -> character); checker = checker -> next;
									if(checker -> character == 'a')
									{
									    printChar(checker -> character); checker = checker -> next;
    									if(checker -> character == 'w')
    									{
    									    printChar(checker -> character); checker = checker -> next;
        									if(checker -> character == 'e')
        									{
        									    printChar(checker -> character); checker = checker -> next;
            									if(checker -> character == 'n')
            									{
            										printChar(checker -> character); checker = checker -> next;
            										if(checker -> character == ' ' || checker -> character == '\t' || checker -> character == '\n' || checker -> character == '(' || checker -> character == '{')
            										{
            											outputFile(51);
            										}
            										else
            										{
            											goto identify;
            										}
                								}
                								else
                								{
                									goto identify;
                								}
                							}
                							else
                							{
                								goto identify;
                							}
                						}
                						else
                						{
                							goto identify;
                						}
                					}
                					else
                					{
                						goto identify;
                					}
								}
                				else
                				{
                					goto identify;
                				}
							}
                			else
                			{
                				goto identify;
                			}
						}
                		else
                		{
                			goto identify;
                		}
					}
                	else
                	{
                		goto identify;
                	}
					break;
				} // case n
 				
 				case 'p': //paano_kung & pano
				{
 					printChar(checker -> character); checker = checker -> next;
 					if(checker -> character == 'a')
 					{
 						printChar(checker -> character); checker = checker -> next;
 						if(checker -> character == 'a')
 						{
 							printChar(checker -> character); checker = checker -> next;
 							if(checker -> character == 'n')
 							{
 								printChar(checker -> character); checker = checker -> next;
 								if(checker -> character == 'o')
 								{
 									printChar(checker -> character); checker = checker -> next;
 									if(checker -> character == '_')
 									{
 									    printChar(checker -> character); checker = checker -> next;
                     					if(checker -> character == 'k')
                     					{
                     						printChar(checker -> character); checker = checker -> next;
                     						if(checker -> character == 'u')
                     						{
                     							printChar(checker -> character); checker = checker -> next;
                     							if(checker -> character == 'n')
                     							{
                     								printChar(checker -> character); checker = checker -> next;
                     								if(checker -> character == 'g')
                     								{
                 										printChar(checker -> character); checker = checker -> next;
                										if(checker -> character == ' ' || checker -> character == '\t' || checker -> character == '\n' || checker -> character == '(')
                										{
                											outputFile(36);
                										}
                										else
                										{
                											goto identify;
                										}
                									}
                									else
                									{
                										goto identify;
                									}
                								}
                								else
                								{
                									goto identify;
                								}
                							}
                							else
                							{
                								goto identify;
                							}
                						}
                						else 
                						{
                							goto identify;
                						}
                					}
                					else
                					{
                					 goto identify;
                					}
 								}
                				else
                				{
                				    goto identify;
                				}
 							}
                			else
                			{
                				goto identify;
                			}
 						}
                		else
                		{
                			goto identify;
                		}
 					}
                	else if(checker -> character == 'a')
 					{
     						printChar(checker -> character); checker = checker -> next;
     						if(checker -> character == 'n')
     						{
     							printChar(checker -> character); checker = checker -> next;
     							if(checker -> character == 'o')
     							{
     	                           printChar(checker -> character); checker = checker -> next;
    							   if(checker -> character == ' ' || checker -> character == '\t' || checker -> character == '\n' || checker -> character == '(')
    							   {
    								    outputFile(35);
    							   }
    							   else
                            	   {
                                	    goto identify;
                            	   }
     							}
    							else
                            	{
                                	goto identify;
                            	}
     						}
    						else
                            {
                                goto identify;
                            }
 					}
    				else
                    {
                        goto identify;
                    }
					break;
				 } //case p
				
				case 'v': //void
				{
 					printChar(checker -> character); checker = checker -> next;
 					if(checker -> character == 'o')
 					{
 						printChar(checker -> character); checker = checker -> next;
 						if(checker -> character == 'i')
 						{
 							printChar(checker -> character); checker = checker -> next;
 							if(checker -> character == 'd')
 							{	
 								printChar(checker -> character); checker = checker -> next;
								if(checker -> character == ' ' || checker -> character == '\t' || checker -> character == '\n' || checker -> character == '(')
								{
									outputFile(46);
								}
									else
								{
									goto identify;
								}
									
							}
							else
							{
								goto identify;
							}
						}
						else
						{
							goto identify;
						}
					}
					else
					{
						goto identify;
					}
					
					break;
				 } //case v
				 
				case 'w': //waylalu
				{
                     printChar(checker->character);  checker = checker->next;
                    if(checker->character == 'a'){
                         printChar(checker->character);  checker = checker->next;
                        if(checker->character == 'y'){
                             printChar(checker->character);  checker = checker->next;
                                if(checker->character == 'l'){
                                     printChar(checker->character);  checker = checker->next;
                                    if(checker->character == 'a'){
                                         printChar(checker->character);  checker = checker->next;
                                        if(checker->character == 'l'){
                                             printChar(checker->character);  checker = checker->next;
                                            if(checker->character == 'u'){
                                                printChar(checker->character);  checker = checker->next;
                                                if(checker->character == ' ' || checker->character == '\t' || checker->character == '\n' || checker->character == '(' ){
                                                    outputFile(39);
                                                }else
                                                    goto identify;
                                            }else
                                                goto identify;
                                        }else
                                            goto identify;
                                    }else
                                        goto identify;
                                }else
                                    goto identify;
                        }else
                            goto identify;
                    }else
                        goto identify;
                    break;
                 } //case w
				 
				default:
					goto identify;
			 }
		}//else if isalpha
		 
		else{
		 	identify:
		 		while(checker->character!= ' ' && checker->character != '\t' && checker->character != '\n' && 
				      checker->character!= '+' && checker->character != '-' && checker->character != '*' && 
					  checker->character!= '/' && checker->character != '%' && checker->character != '=' &&
					  checker->character!= ';' && checker->character != '{' && checker->character != '}' &&
					  checker->character!= '(' && checker->character != ')' && checker->character != '<' &&
					  checker->character != '>' && checker->character != '&' && checker->character != '$' &&
					  checker->character != '!' && checker->character != '^' && checker->character != '?' && checker->character != ','){
					  	if(!isalpha(checker->character)&&!isdigit(checker->character)&&checker->character!='_'){
					  		while(checker->character!= ' ' && checker->character != '\t' && checker->character != '\n' && 
				     			  checker->character!= '+' && checker->character != '-' && checker->character != '*' && 
					  			  checker->character!= '/' && checker->character != '%' && checker->character != '=' &&
					  			  checker->character!= ';' && checker->character != '{' && checker->character != '}' &&
					  			  checker->character!= '(' && checker->character != ')' && checker->character != '<' &&
					  			  checker->character != '>' && checker->character != '&' && checker->character != '$' &&
					  			  checker->character != '!' && checker->character != '^' && checker->character != '?' && checker->character != ','){
					  			printChar(checker->character); 
								checker = checker->next;
							  }
							  flag = 1;
							  break;
						  }
		 				printChar(checker->character);
						checker = checker->next;
				 }
				 if(flag == 1){
					 outputFile(53); flag = 0;
				}
				else
				 	outputFile(52);
		 }//end of else
	 }//end of while
 }//end of lexicalAnalysis
 
 void readSourceFile(){
 	char strFilename[50], c;
 	char file[5] = ".teks"; //for the accepting .teks
 	int i, j, Flag; //for the accepting .teks
 	
 	printf("Enter Source File: ");
 	scanf("%s", &strFilename);
 	source = fopen(strFilename,"rw+");
 	
 
 	for(i = 0; strFilename[i] != '\0'; i++){ //for loop for accepting .teks only
		if(strFilename[i] == file[0]){
			Flag = 1;
			for(j = 0; file[j] != '\0'; j++){
				if(strFilename[i + j] != file[j]){
					Flag = 0;
					break;
				}
			}	
		}
		if(Flag == 1)
			break;
	}//end of for
 	
 	if(source==NULL || Flag ==0){
		if(source==NULL)
			 printf("File not found");
		if(Flag == 0)
			printf("Invalid File Extension (.teks file only)");
		 exit(0);
 	}

    while(fscanf(source,"%c",&c) != EOF){
        current = (struct list*) malloc(sizeof(struct list));
        current -> next = current -> prev = NULL;

        if (head == NULL){
            head = tail = current;
            current->character = c;
        }
        else{
            tail -> next = current;
            current -> prev = tail;
            tail = current;
            current->character = c;
        }//
    }// end of while
    
    fclose(source);
    tail -> next = NULL;
 }//end of void read/sourceFile
 
 void outputFile(int ln){
 	
	int i = 1;
	chkr = head1;
	
	while(chkr!=NULL){
		chkr = chkr->next;
		
		if(chkr->ch == '\n'){
			i++;
		}
		if(i == ln){
			while(chkr->ch != '\t'){
				chkr = chkr->next;
			}
			while(chkr->ch != '\n'){
				printChar(chkr->ch);
				chkr = chkr->next;
			}
			break;
		}
	}
	output = fopen("SymbolTable.txt", "aw+");
 	fprintf(output,"\n");
 	fclose(output);
 }
 
 void printChar(char c){
 	output = fopen("SymbolTable.txt", "aw+");
 	fprintf(output,"%c", c);
 	fclose(output);
 }

 void displayOutput(){
	char pt;
	display = fopen("SymbolTable.txt", "r");
	 while(fscanf(source,"%c",&pt) != EOF){
		 printf("%c", pt);
	 }
	 fclose(display);
 }
 
 void readTable(){
    char temp;
    table = fopen("TABLE.txt","rw+");

    while(fscanf(table,"%c",&temp) != EOF){
        curr = (struct tokenTable*) malloc(sizeof(struct tokenTable));
        curr -> next = curr -> p = NULL;

        if (head1 == NULL){
            head1 = tail1 = curr;
            curr->ch = temp;
        }//if
        else{
            tail1 -> next = curr;
            curr -> p = tail;
            tail1 = curr;
            curr->ch = temp;
        }//else
    }//while

    fclose(table);
    tail1 -> next = NULL;
}

