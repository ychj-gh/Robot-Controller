grammar RSI;

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
 : assignment  			# assignStat 
 | if_stat  			# ifStat
 | while_stat  			# whileStat
 | loop_stat			# loopStat
 | call_stat			# callStat 
 ;  
  
assignment  
 : ID ASSIGN expr   # assignExpr 
 ;  
  
if_stat  
 : IF expr THEN block (elseif_stat)* (else_stat)? END_IF	# ifExpr
 ;  
  
elseif_stat
 : ELSE IF expr THEN block 				# elseifExpr
 ;

else_stat
 : ELSE block   						# elseExpr
 ;

while_stat  
 : WHILE expr DO block END_WHILE		# whileExpr
 ;  

loop_stat
 : LOOP var DO block END_LOOP 			# loopExpr
 ;

call_stat
 : ID '(' params ')'			# callExpr
 ;
  
expr  
 : var 						# variable
 | call_stat				# call
 ;  

params
 : var? (',' var)*			# paramlist
 ;

var
 : NUM 						# num
 | ID 						# id
 ;

ASSIGN : '=';  
IF : 'IF';  
THEN : 'THEN';
ELSE : 'ELSE';  
END_IF : 'END_IF';
WHILE : 'WHILE';  
DO : 'DO';
END_WHILE : 'END_WHILE';
LOOP : 'LOOP';
END_LOOP : 'END_LOOP';
  
ID  
 : [a-zA-Z_] [a-zA-Z_0-9]*  
 ;  
    
  
NUM  
 : '-'? [0-9]+ '.' [0-9]*   
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
