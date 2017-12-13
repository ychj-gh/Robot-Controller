grammar RCdata;

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
 : bool_stat  			# boolStat 
 | char_stat			# charStat
 | int_stat  			# intStat
 | real_stat  			# realStat
 | string_stat			# stringStat
 | jtpose_stat			# jtposeStat
 | trpose_stat			# trposeStat
 | tool_stat			# toolStat
 | coord_stat			# coordStat 
 ;  

bool_stat
 : BOOL ID (ASSIGN boolval)? ';' 	# boolExpr
 ;

boolval
 : TRUE    							# trueExpr
 | FALSE							# falseExpr
 ;

char_stat
 : CHAR ID (ASSIGN CH)? ';' 		# charExpr
 ;

int_stat
 : INT ID (ASSIGN NUM)? ';' 		# intExpr
 ;

real_stat
 : REAL ID (ASSIGN NUM)? ';' 		# realExpr
 ;

string_stat
 : STRING ID (ASSIGN CSTRING)? ';' 	# stringExpr
 ;

jtpose_stat
 : JTPOSE ID ASSIGN NUM (',' NUM)+ ';'       	# jtposeExpr1
 | PID ASSIGN NUM (',' NUM)+ ';'					# jtposeExpr2
 ;

trpose_stat
 : TRPOSE ID ASSIGN NUM ',' NUM ',' NUM ',' NUM ',' NUM ',' NUM';'		# trposeExpr1
 | BPID ASSIGN NUM ',' NUM ',' NUM ',' NUM ',' NUM ',' NUM';'					# trposeExpr2
 | EXID ASSIGN NUM ',' NUM ',' NUM ',' NUM ',' NUM ',' NUM';'					# trposeExpr3
 ;

tool_stat
 : TOOLDATA ID ASSIGN NUM ',' NUM ',' NUM ',' NUM ',' NUM ',' NUM (',' NUM ',' NUM ',' NUM ',' NUM ',' NUM ',' NUM ',' NUM)? ';'  # toolExpr
 ;

coord_stat
 : COORDATA ID ',' op=(COORDO | COORDT) ',' op1=(ID|BPID) ',' op2=(ID|BPID) ',' op3=(ID|BPID) ';'		# coordExpr
 ;

ASSIGN : '=';  

BOOL : 'BOOL';
CHAR : 'CHAR';
INT : 'INT';
REAL : 'REAL';
STRING : 'STRING';
JTPOSE : 'JTPOSE';
TRPOSE : 'TRPOSE';
TOOLDATA : 'TOOLDATA';
COORDATA : 'COORDATA';

COORDO : 'O';
COORDT : 'T';

TRUE : 'TRUE';
FALSE : 'FALSE';


PID 
 : 'P' [0-9] [0-9] [0-9]
 ;

BPID
 : 'BP' [0-9] [0-9] [0-9]
 ;

EXID
 : 'EX' [0-9] [0-9] [0-9]
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
