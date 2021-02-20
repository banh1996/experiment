package arithlang;
import static arithlang.AST.*;
import static arithlang.Value.*;

import java.util.List;

public class Evaluator implements Visitor<Value> {
    //private NumVal record = new NumVal(0);
    Printer.Formatter ts = new Printer.Formatter();
	
    Value valueOf(Program p) {
        // Value of a program in this language is the value of the expression
        return (Value) p.accept(this);
    }

    @Override
    public Value visit(pExp e) {
        return new CharVal(e.v());
    }

    @Override
    public Value visit(nExp e) {
        return new CharVal(e.v());
    }

    @Override
    public Value visit(uExp e) {
        return new CharVal(e.v());
    }

    @Override
    public Value visit(Program p) {
        return (Value) p.e().accept(this);
    }

    @Override
    public Value visit(AddExp e) {
        List<Exp> operands = e.all();
        char result = '\0';
        int count = 0;
        for(Exp exp: operands) {
            CharVal intermediate = (CharVal) exp.accept(this);
            if (count == 0) {
                result = intermediate.v();
            }
            else {
                if (result == 'p' && intermediate.v() == 'p'){
                    result = 'p';
                }
                else if ((result == 'p' && intermediate.v() == 'n') ||
                         (result == 'n' && intermediate.v() == 'p') ||
                         (result == 'u' && intermediate.v() == 'p') ||
                         (result == 'p' && intermediate.v() == 'u') ||
                         (result == 'n' && intermediate.v() == 'u') ||
                         (result == 'u' && intermediate.v() == 'n') ||
                         (result == 'u' && intermediate.v() == 'u')){
                    result = 'u';
                }
                else {
                    result = 'n';
                }
            }
            count++;
            if (count == 3) {
                return new DynamicError("error");
            }
        }
        return new CharVal(result);
    }

    @Override
    public Value visit(SubExp e) {
        List<Exp> operands = e.all();
        char result = '\0';
        int count = 0;
        for(Exp exp: operands) {
            CharVal intermediate = (CharVal) exp.accept(this);
            if (count == 0) {
                result = intermediate.v();
            }
            else {
                if (result == 'p' && intermediate.v() == 'n'){
                    result = 'p';
                }
                else if ((result == 'p' && intermediate.v() == 'p') ||
                         (result == 'p' && intermediate.v() == 'u') ||
                         (result == 'n' && intermediate.v() == 'n') ||
                         (result == 'n' && intermediate.v() == 'u') ||
                         (result == 'u' && intermediate.v() == 'p') ||
                         (result == 'u' && intermediate.v() == 'n') ||
                         (result == 'u' && intermediate.v() == 'u')){
                    result = 'u';
                }
                else {
                    result = 'n';
                }
            }
            count++;
            if (count == 3) {
                return new DynamicError("error");
            }
        }
        return new CharVal(result);
    }
}
