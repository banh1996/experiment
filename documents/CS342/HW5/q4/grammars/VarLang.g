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
		| sw=switchexp { $ast = $sw.ast; }
		| cs=caseexp { $ast = $cs.ast; }
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

 switchexp returns [SwitchExp ast]:
		'(' 'switch'
		id=Identifier
		e1=exp
		'(' 'default' e2=exp ')'
		')' { $ast = new SwitchExp($id.text, $e1.ast, $e2.ast); }
 		;

 caseexp returns [CaseExp ast]:
		'(' 'case'
		n0=Number
		e=exp
		')' { $ast = new CaseExp(Double.parseDouble($n0.text), $e.ast); }
 		;

 // Lexical Specification of this Programming Language
 //  - lexical specification rules start with uppercase
 