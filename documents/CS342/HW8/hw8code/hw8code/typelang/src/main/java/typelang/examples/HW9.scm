Q1. 
a	
————————————————————————————————————————————————
Class Name         |  Atomic or Compound
————————————————————————————————————————————————
BoolT              |    Atomic
————————————————————————————————————————————————
ErrorT             |    Atomic
————————————————————————————————————————————————
FuncT              |    Compund
————————————————————————————————————————————————
ListT              |    Compund
————————————————————————————————————————————————
NumT               |    Atomic
————————————————————————————————————————————————
PairT              |    Compund
————————————————————————————————————————————————
RefT               |    Compund
————————————————————————————————————————————————
StringT            |    Atomic
————————————————————————————————————————————————
UnitT              |    Atomic
————————————————————————————————————————————————


Q1 b. 


Term              |         Condition 
————————————————————————————————————————————————————————————————————————————————————————————————
Program           |    When the declared type of the define decl doesn’t match with expression’s type.
————————————————————————————————————————————————————————————————————————————————————————————————
AssignExp         |    if lhs_exp evaluates to ErrorT |
					   if rhs_exp evaluates to ErrorT |	
					   if rhs_exp's type doesn’t match with lhs_exp's nested type |
 					   if lhs_exp evaluates to type other than RefT
—————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
CallExp           |    if operator evaluates to ErrorT |
					   if operator evaluates to type other than FuncT|
					   if number of actuals does not match with number of formals |	
					   if any of the actual parameters evaluates to ErrorT |
					   if any of the actual parameters is not assignable to declared type of corresponding formal
 					   
—————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
CarExp            |    if expression insided CarExp evaluates to ErrorT |
					   if expression insided CarExp evaluates to type other than PairT					   
—————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
CdrExp            |    if expression insided CdrExp evaluates to ErrorT |
					   if expression insided CdrExp evaluates to type other than PairT					   
—————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
ConsExp           |    if fst expression of ConsExp evaluates to ErrorT |
					   if snd expression of ConsExp evaluates to type other than PairT					   
—————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
DerefExp          |    if location expression of DerefExp evaluates to ErrorT |
					   if location expression of DerefExp evaluates to type other than RefT			   
—————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
FreeExp           |    if location expression of FreeExp evaluates to ErrorT |
					   if location expression of FreeExp evaluates to type other than RefT		
—————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
IfExp             |    if condType expression of IfExp evaluates to ErrorT |
					   if condType expression of IfExp evaluates to type other than BoolT|		
					   if thentype expression of IfExp evaluates to ErrorT |
					   if elsetype expression of IfExp evaluates to ErrorT |
					   if type of thentype expression and type of elsetype expression do not match
—————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
LambdaExp         |    When the number of actuals and the number of formals are not equal	
—————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
LetExp            |    Let a let expression be (let ((e1 : T1 V1) (e2: T2 V2)... (en: Tn Vn)) body)
				 	   where e1, v1, e2, v2 ... en, vn  are expressions
					  -  if type of any expression Vi, where Vi is an expression of value_expression of some variable in 
					  	 (let ((e1 : T1 V1) (e2: T2 V2) ... (en: Tn Vn)) body), is ErrorT  |

					  -  if type of any expression Vi, where Vi is an expression of value_expression of some variable in 
					  	 (let ((e1 : T1 V1) (e2: T2 V2) ... (en: Tn Vn)) body), does not match with type of corresponding ei
—————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
LetrecExp         |    Same as LetExp
—————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
ListExp           |   Let a list expression be (list : T e1 e2 e3 ... en), 
				 	  where T is type of list and e1, e2, e3 ... en are expressions
						-  if type of any expression ei, where ei is an expression of element in list at position i, is ErrorT |
						-  if type of any expression ei, where ei is an expression of an element of list, is not assignable to T |

—————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
NullExp           |    Let a null expression be (null? e1), where e1 is an expression.
						- if e1’s type is ErrorT |
						- if e1’s type is not ListT 
—————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
RefExp            |     Let a ref expression be (ref: T e1), where e1 is an expression.
							- if e1’s type is ErrorT |
							- if e1’s type is not assignable to T 
—————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
VarExp            |    When the variable has not been declared
—————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
BinaryComparator  |    Let a BinaryComparator be (binary operator e1 e2), where e1 and e2 are expressions.
						- if e1’s type is ErrorT |
						- if e2’s type is ErrorT |
						- if e1’s type is not NumT |
						- if e2’s type is not NumT |
—————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
CompoundArithExp  |    Let a CompoundArithExp be (ArithExp e1 e2 e3 ... en), where e1, e2, e3... en are expressions.
						- if type of any expression ei, where ei is an expression of element in list at position 
			   	 			 i, is ErrorT |
						- if type of any expression ei, where ei is an expression of element in list at position 
			   	 			 i, is not NumT |
—————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
VarExp            |    When the variable has not been declared
—————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
AddExp            |    same as CompoundArithExp
—————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
SubExp            |    same as CompoundArithExp
—————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
MultExp           |    same as CompoundArithExp
—————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
DivExp            |    same as CompoundArithExp
—————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
EqualExp          |    When the variable has not been declared
—————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
GreaterExp        |    When the variable has not been declared
—————————————————————————————————————————————————————————————————————————————————————————————————————————————————————


Q1 
c. In checker.java empty environment is extended to map "read" and "eval" with their
   corresponding types while in Evaluator.java empty environment is extended to map
   "read", "eval" and "require" variables with their corresponding values. 

