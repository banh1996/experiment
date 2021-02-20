package arithlang;

import java.util.ArrayList;
import java.util.List;

/**
 * This class hierarchy represents expressions in the abstract syntax tree
 * manipulated by this interpreter.
 * 
 * @author hridesh
 * 
 */
@SuppressWarnings("rawtypes")
public interface AST {
    public static abstract class ASTNode {
        public abstract Object accept(Visitor visitor);
    }
    public static class Program extends ASTNode {
        Exp _e;

        public Program(Exp e) {
            _e = e;
        }

        public Exp e() {
            return _e;
        }
		
        public Object accept(Visitor visitor) {
            return visitor.visit(this);
        }
    }
    public static abstract class Exp extends ASTNode {

    }

    public static class pExp extends Exp {
        char _val;

        public pExp(char v) {
            _val = 'p';
        }

        public char v() {
            return _val;
        }

        public Object accept(Visitor visitor) {
            return visitor.visit(this);
        }
    }

    public static class nExp extends Exp {
        char _val;

        public nExp(char v) {
            _val = 'n';
        }

        public char v() {
            return _val;
        }

        public Object accept(Visitor visitor) {
            return visitor.visit(this);
        }
    }

    public static class uExp extends Exp {
        char _val;

        public uExp(char v) {
            _val = 'u';
        }

        public char v() {
            return _val;
        }

        public Object accept(Visitor visitor) {
            return visitor.visit(this);
        }
    }

    public static abstract class CompoundArithExp extends Exp {
        List<Exp> _rep;
        public CompoundArithExp(List<Exp> args) {
            _rep = new ArrayList<Exp>();
            _rep.addAll(args);
        }
        public List<Exp> all() {
            return _rep;
        }
    }

    public static class AddExp extends CompoundArithExp {
        public AddExp(List<Exp> args) {
            super(args);
        }
        public Object accept(Visitor visitor) {
            return visitor.visit(this);
        }
    }

    public static class SubExp extends CompoundArithExp {
        public SubExp(List<Exp> args) {
            super(args);
        }
        public Object accept(Visitor visitor) {
            return visitor.visit(this);
        }
    }

    public interface Visitor <T> {
        // This interface should contain a signature for each concrete AST node.
        public T visit(AST.pExp e);
        public T visit(AST.nExp e);
        public T visit(AST.uExp e);
        public T visit(AST.AddExp e);
        public T visit(AST.SubExp e);
        public T visit(AST.Program p);
    }	
}
