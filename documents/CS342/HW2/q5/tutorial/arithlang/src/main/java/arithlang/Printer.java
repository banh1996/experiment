package arithlang;

import static arithlang.AST.*;

public class Printer {
    public void print(Value v) {
        System.out.println(v.toString());
    }
	
    public static class Formatter implements AST.Visitor<String> {
		
        public String visit(Program p) {
            return (String) p.e().accept(this);
        }

        public String visit(pExp e) {
            return "" + e.v();
        }

        public String visit(nExp e) {
            return "" + e.v();
        }

        public String visit(uExp e) {
            return "" + e.v();
        }
		
        public String visit(AddExp e) {
            String result = "(+";
            for(AST.Exp exp : e.all()) 
                result += " " + exp.accept(this);
            return result + ")";
        }		
		
        public String visit(SubExp e) {
            String result = "(-";
            for(AST.Exp exp : e.all()) 
                result += " " + exp.accept(this);
            return result + ")";
        }
    }
}
