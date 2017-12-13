grammar RCcode;

options{
	language = Cpp;
}
  
prog 
 : block EOF  			# program	
 ;  
  
block  
 : stat*  				# statBlock
 ;  
  
stat 
 : robot_stat  				
 | data_stat				
 | signal_stat  			
 | math_stat				
 | oneinst_stat				
 | assign_stat 				
 | goto_stat				
 | if_stat 					
 | for_stat 				
 | while_stat 				
 | libcall_stat 			
 | call_stat				
 ;  

robot_stat
 : MOVJ ID ',' ID ',' ID ';'			# movjExpr
 | MOVL ID ',' ID ',' ID ';' 			# movlExpr
 | MOVC ID ',' ID ',' ID ',' ID ';' 	# movcExpr
 | MOVS ID ',' ID ',' ID ',' ID ';'		# movsExpr
 | SHIFTON ID ',' ID ';'				# shiftonExpr
 | SHIFTOFF';' 							# shiftoffExpr
 ;

data_stat
 : SET ID ',' ID ';'		# setExpr
 | SETE ELEM ',' ID	';'		# seteExpr
 | GETE ID ',' ELEM ';'  	# geteExpr
 ;

signal_stat
 : WAIT ID op=(EQ|GE|LE|LT|GT|NE) numorid (',' TIME)? ';'  	# waitExpr
 | DELAY TIME ';' 							# delayExpr
 | SETOUT ID ',' numorid ';'				# setoutExpr
 | DIN ID ',' ID ';' 						# dinExpr
 ;

math_stat
 : INCR ID ';'  								# incExpr
 | DECR ID ';' 									# decExpr
 | FUNC op1=(ELEM | ID) ',' op2=(ELEM | ID | NUM)';' 	# funcExpr
 ;

call_stat
 : CALL ID ';'			# callExpr
 ;

assign_stat
 : ID ASSIGN numorid op=(ADD|SUB|MUL|DIV|EQ|GE|LE|GT|LT|NE) numorid ';' # assignExpr1
 | ID ASSIGN funcallexpr ';'  	# assignExpr2
 | ID ASSIGN numorid ';'		# assignExpr3
 | ID ASSIGN CSTRING ';' 		# assignExpr4
 ;

goto_stat
 : GOTO LABEL ';'			# gotoExpr
 ;

if_stat  
 : IF numorid op=(EQ|GE|LE|LT|GT|NE) numorid THEN block (elseif_stat)* (else_stat)? ENDIF ';' 	# ifExpr1
 | IF ID THEN block (elseif_stat)* (else_stat)? ENDIF ';'				 		# ifExpr2
 ;  
  
elseif_stat
 : ELSEIF numorid op=(EQ|GE|LE|LT|GT|NE) numorid THEN block 				# elseifExpr1
 | ELSEIF ID THEN block 									# elseifExpr2
 ;

else_stat
 : ELSE block   							# elseExpr
 ;

for_stat
 : FOR ID ASSIGN NUM TO NUM BY NUM block ENDFOR ';' 		# forExpr
 ;

while_stat
 : WHILE numorid op=(EQ|GE|LE|LT|GT|NE) numorid DO block ENDWL ';'   		# whileExpr1
 | WHILE ID DO block ENDWL ';' 								# whileExpr2 
 ;



libcall_stat
 :  funcallexpr ';'			# libcallExpr
 ;

funcallexpr
 : ID '(' params ')'        # funcallExpr
 ;

params
 : numorid? (',' numorid)* 			# paramlist
 ;
 

numorid
 : NUM 						# numExpr
 | ID 						# idExpr
 | CSTRING 					# cstrExpr
 ;

oneinst_stat
 : LABEL ';'	 	# labelExpr
 | RET 	';'	 		# retExpr
 | NOP 	';'			# nopExpr
 | PAUSE ';'		# pauseExpr
 | HALT ';'			# haltExpr
 | BREAK ';'		# breakExpr
 ;

GOTO : 'GOTO';

IF : 'IF' ;
THEN : 'THEN';
ELSEIF : 'ELSEIF';
ELSE : 'ELSE';
ENDIF : 'ENDIF';

ASSIGN : '=';  

WHILE : 'WHILE';
DO : 'DO';
ENDWL : 'ENDWL';

FOR : 'FOR';
TO : 'TO';
BY : 'BY';
ENDFOR : 'ENDFOR';


MOVJ : 'MOVJ';
MOVL : 'MOVL';
MOVC : 'MOVC';
MOVS : 'MOVS';
SHIFTON : 'SHIFTON';
SHIFTOFF : 'SHIFTOFF';

SET : 'SET';
SETE : 'SETE';
GETE : 'GETE';

WAIT : 'WAIT';
DELAY : 'DELAY';
SETOUT : 'SETOUT';
DIN : 'DIN';

LABEL 
 : 'L' [0-9]+
 ;

RET : 'RET';
NOP : 'NOP';
PAUSE : 'PAUSE';
HALT : 'HALT';
BREAK : 'BREAK';

INCR : 'INCR';
DECR : 'DECR';

CALL : 'CALL';

EQ : '==';
GT : '>';
GE : '>=';
LT : '<';
LE : '<=';
NE : '<>';

ADD : '+';
SUB : '-';
MUL : '*';
DIV : '/';

FUNC 
 : 'ADD'
 | 'SUB'
 | 'MUL'
 | 'DIV'
 | 'SIN'
 | 'COS'
 | 'ATAN'
 | 'SQRT'
 | 'AND'
 | 'OR'
 | 'NOT'
 | 'XOR'
 ;

TIME 
 : 'T' [0-9]+ '.' [0-9]* 
 | 'T' '.' [0-9]+
 | 'T' [0-9]+
 ; 

ELEM 
 : ID '(' [0-6] ')' 
 ;

CSTRING
 : '"' [a-zA-Z_0-9]* '"'
 ;

CH 
 : '\'' [0-9A-Za-z_] '\''
 ;

ID  
 : [a-zA-Z_] [a-zA-Z_0-9]*  
 ;  
    
  
NUM  
 : '^B' '-'? [01]+
 | '^H' '-'? [0-9A-F]+ 
 | '-'? [0-9]+ '.' [0-9]*   
 | '-'? '.' [0-9]+  
 | '-'? [0-9]+
 ;  
  
COMMENT  
 : '#' ~[\r\n]* -> skip  
 ;  
  
SPACE  
 : [ \t\r\n] -> skip  
 ;  
  
OTHER  
 : .   
 ;  
