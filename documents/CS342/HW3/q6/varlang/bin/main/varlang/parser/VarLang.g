grammar VarLang;

import ArithLang; //Import all rules from Arithlang grammar.
 
 // New elements in the Grammar of this Programming Language
 //  - grammar rules start with lowercase

 exp returns [Exp ast]: 
		v=varexp { $ast = $v.ast; }
		| n=numexp { $ast = $n.ast; }
              | a=addexp { $ast = $a.ast; }
              | s=subexp { $ast = $s.ast; }
              | m=multexp { $ast = $m.ast; }
              | d=divexp { $ast = $d.ast; }
              | l=letexp { $ast = $l.ast; }
              | le=leteexp { $ast = $le.ast; }
              | de=decexp { $ast = $de.ast; }
              ;

 varexp returns [VarExp ast]: 
 		id=Identifier { $ast = new VarExp($id.text); }
 		;

 letexp  returns [LetExp ast] 
        locals [ArrayList<String> names, ArrayList<Exp> value_exps]
 		@init { $names = new ArrayList<String>(); $value_exps = new ArrayList<Exp>(); } :
 		'(' Let 
 			'(' ( '(' id=Identifier e=exp ')' { $names.add($id.text); $value_exps.add($e.ast); } )+  ')'
 			body=exp 
 			')' { $ast = new LetExp($names, $value_exps, $body.ast); }
 		;

 leteexp  returns [LeteExp ast] 
        locals [ArrayList<String> names = new ArrayList<String>(), ArrayList<Exp> value_exps = new ArrayList<Exp>(), ArrayList<NumExp> key_exps = new ArrayList<NumExp>()] :
        '(' Lete
        '(' ( '(' id=Identifier e=exp key=numexp')' { $names.add($id.text); $value_exps.add($e.ast); $key_exps.add($key.ast); } )+ ')'
        body=exp
        ')' { $ast = new LeteExp($names, $value_exps, $body.ast, $key_exps); }
        ;

 decexp returns [DecExp ast]:
        '(' Dec
        key=numexp
        id=Identifier
        ')' { $ast = new DecExp($key.ast, $id.text); }
        ;

 // Lexical Specification of this Programming Language
 //  - lexical specification rules start with uppercase
 
