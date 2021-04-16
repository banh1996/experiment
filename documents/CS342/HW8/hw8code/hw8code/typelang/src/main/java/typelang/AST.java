package typelang;

import java.util.ArrayList;
import java.util.List;

import typelang.Type;


/**
 * This class hierarchy represents expressions in the abstract syntax tree
 * manipulated by this interpreter.
 * 
 * @author hridesh
 * 
 */
@SuppressWarnings({"rawtypes", "unchecked"})
public interface AST {
	public static abstract class ASTNode implements AST {
		public abstract Object accept(Visitor visitor, Object env);
	}
	public static class Program extends ASTNode {
		List<DefineDecl> _decls;
		Exp _e;

		public Program(List<DefineDecl>decls, Exp e) {
			_decls = decls;
			_e = e;
		}

		public Exp e() {
			return _e;
		}
		
		public List<DefineDecl> decls() {
			return _decls;
		}
		
		public Object accept(Visitor visitor, Object env) {
			return visitor.visit(this, env);
		}
	}
	public static abstract class Exp extends ASTNode {

	}

	public static class VarExp extends Exp {
		String _name;

		public VarExp(String name) {
			_name = name;
		}

		public String name() {
			return _name;
		}
		
		public Object accept(Visitor visitor, Object env) {
			return visitor.visit(this, env);
		}
	}

	public static class UnitExp extends Exp {
		
		public UnitExp() {}

		public Object accept(Visitor visitor, Object env) {
			return visitor.visit(this, env);
		}

	}

	public static class NumExp extends Exp {
		double _val;

		public NumExp(double v) {
			_val = v;
		}

		public double v() {
			return _val;
		}
		
		public Object accept(Visitor visitor, Object env) {
			return visitor.visit(this, env);
		}
	}

	public static class StrExp extends Exp {
		String _val;

		public StrExp(String v) {
			_val = v;
		}

		public String v() {
			return _val;
		}
		
		public Object accept(Visitor visitor, Object env) {
			return visitor.visit(this, env);
		}
	}

	public static class BoolExp extends Exp {
		boolean _val;

		public BoolExp(boolean v) {
			_val = v;
		}

		public boolean v() {
			return _val;
		}
		
		public Object accept(Visitor visitor, Object env) {
			return visitor.visit(this, env);
		}
	}

	public static abstract class CompoundArithExp extends Exp {
		List<Exp> _rest;

		public CompoundArithExp() {
			_rest = new ArrayList<Exp>();
		}

		public CompoundArithExp(Exp fst) {
			_rest = new ArrayList<Exp>();
			_rest.add(fst);
		}

		public CompoundArithExp(List<Exp> args) {
			_rest = new ArrayList<Exp>();
			for (Exp e : args)
				_rest.add((Exp) e);
		}

		public CompoundArithExp(Exp fst, List<Exp> rest) {
			_rest = new ArrayList<Exp>();
			_rest.add(fst);
			_rest.addAll(rest);
		}

		public CompoundArithExp(Exp fst, Exp second) {
			_rest = new ArrayList<Exp>();
			_rest.add(fst);
			_rest.add(second);
		}

		public Exp fst() {
			return _rest.get(0);
		}

		public Exp snd() {
			return _rest.get(1);
		}

		public List<Exp> all() {
			return _rest;
		}

		public void add(Exp e) {
			_rest.add(e);
		}
		
	}

	public static class AddExp extends CompoundArithExp {
		public AddExp(Exp fst) {
			super(fst);
		}

		public AddExp(List<Exp> args) {
			super(args);
		}

		public AddExp(Exp fst, List<Exp> rest) {
			super(fst, rest);
		}

		public AddExp(Exp left, Exp right) {
			super(left, right);
		}
		
		public Object accept(Visitor visitor, Object env) {
			return visitor.visit(this, env);
		}
	}

	public static class SubExp extends CompoundArithExp {

		public SubExp(Exp fst) {
			super(fst);
		}

		public SubExp(List<Exp> args) {
			super(args);
		}

		public SubExp(Exp fst, List<Exp> rest) {
			super(fst, rest);
		}

		public SubExp(Exp left, Exp right) {
			super(left, right);
		}
		
		public Object accept(Visitor visitor, Object env) {
			return visitor.visit(this, env);
		}
	}

	public static class DivExp extends CompoundArithExp {
		public DivExp(Exp fst) {
			super(fst);
		}

		public DivExp(List<Exp> args) {
			super(args);
		}

		public DivExp(Exp fst, List<Exp> rest) {
			super(fst, rest);
		}

		public DivExp(Exp left, Exp right) {
			super(left, right);
		}
		
		public Object accept(Visitor visitor, Object env) {
			return visitor.visit(this, env);
		}
	}

	public static class MultExp extends CompoundArithExp {
		public MultExp(Exp fst) {
			super(fst);
		}

		public MultExp(List<Exp> args) {
			super(args);
		}

		public MultExp(Exp fst, List<Exp> rest) {
			super(fst, rest);
		}

		public MultExp(Exp left, Exp right) {
			super(left, right);
		}
		
		public Object accept(Visitor visitor, Object env) {
			return visitor.visit(this, env);
		}
	}
	
	/**
	 * A let expression has the syntax 
	 * 
	 *  (let ((name expression)* ) expression)
	 *  
	 * @author hridesh
	 *
	 */
	public static class LetExp extends Exp {
		List<String> _names;
		List<Type> _varTypes;
		List<Exp> _value_exps; 
		Exp _body;
		
		public LetExp(List<String> names, List<Type> varTypes,
				List<Exp> value_exps, Exp body) {
			_names = names;
			_varTypes = varTypes;
			_value_exps = value_exps;
			_body = body;
		}
		
		public Object accept(Visitor visitor, Object env) {
			return visitor.visit(this, env);
		}

		public List<String> names() { return _names; }

		public List<Type> varTypes() { return _varTypes; }

		public List<Exp> value_exps() { return _value_exps; }

		public Exp body() { return _body; }
	}
	
	/**
	 * A define declaration has the syntax 
	 * 
	 *  (define name expression)
	 *  
	 * @author hridesh
	 *
	 */
	public static class DefineDecl extends Exp {
		String _name;
		Type _type;
		Exp _value_exp; 
		
		public DefineDecl(String name, Type type, Exp value_exp) {
			_name = name;
			_type = type;
			_value_exp = value_exp;
		}
		
		public Object accept(Visitor visitor, Object env) {
			return visitor.visit(this, env);
		}

		public String name() { return _name; }

		public Type type() { return _type; }

		public Exp value_exp() { return _value_exp; }
	}
	
	/**
	 * An anonymous procedure declaration has the syntax
	 * 
	 * @author hridesh
	 *
	 */
	public static class LambdaExp extends Exp {		
		List<String> _formals;
		List<Type> _types;
		Exp _body;
		
		public LambdaExp(List<String> formals, List<Type> types, Exp body) {
			_formals = formals;
			_types = types;
			_body = body;
		}

		public List<String> formals() { return _formals; }

		public List<Type> types() { return _types; }

		public Exp body() { return _body; }

		public Object accept(Visitor visitor, Object env) {
			return visitor.visit(this, env);
		}
	}
	
	/**
	 * A call expression has the syntax
	 * 
	 * @author hridesh
	 *
	 */
	public static class CallExp extends Exp {
		Exp _operator; 
		List<Exp> _operands;
		
		public CallExp(Exp operator, List<Exp> operands) {
			_operator = operator; 
			_operands = operands;
		}
		
		public Exp operator() { return _operator; }

		public List<Exp> operands() { return _operands; }
		
		public Object accept(Visitor visitor, Object env) {
			return visitor.visit(this, env);
		}
	}

	/**
	 * An if expression has the syntax
	 * 
	 * (if conditional_expression true_expression false_expression)
	 * 
	 * @author hridesh
	 *
	 */
	public static class IfExp extends Exp {
		Exp _conditional; 
		Exp _then_exp; 
		Exp _else_exp; 
		
		public IfExp(Exp conditional, Exp then_exp, Exp else_exp) {
			_conditional = conditional;
			_then_exp = then_exp; 
			_else_exp = else_exp; 
		}
		
		public Exp conditional() { return _conditional; }
		public Exp then_exp() { return _then_exp; }
		public Exp else_exp() { return _else_exp; }
		
		public Object accept(Visitor visitor, Object env) {
			return visitor.visit(this, env);
		}
	}
	
	/**
	 * A less expression has the syntax
	 * 
	 * ( < first_expression second_expression )
	 * 
	 * @author hridesh
	 *
	 */
	public static class LessExp extends BinaryComparator {
		public LessExp(Exp first_exp, Exp second_exp) {
			super(first_exp, second_exp);
		}
				
		public Object accept(Visitor visitor, Object env) {
			return visitor.visit(this, env);
		}
	}
	
	public static abstract class BinaryComparator extends Exp {
		private Exp _first_exp; 
		private Exp _second_exp; 
		BinaryComparator(Exp first_exp, Exp second_exp) {
			_first_exp = first_exp;
			_second_exp = second_exp; 
		}
		public Exp first_exp() { return _first_exp; }
		public Exp second_exp() { return _second_exp; }
	}

	/**
	 * An equal expression has the syntax
	 * 
	 * ( == first_expression second_expression )
	 * 
	 * @author hridesh
	 *
	 */
	public static class EqualExp extends BinaryComparator {
		public EqualExp(Exp first_exp, Exp second_exp) {
			super(first_exp, second_exp);
		}
		
		public Object accept(Visitor visitor, Object env) {
			return visitor.visit(this, env);
		}
	}

	/**
	 * A greater expression has the syntax
	 * 
	 * ( > first_expression second_expression )
	 * 
	 * @author hridesh
	 *
	 */
	public static class GreaterExp extends BinaryComparator {
		public GreaterExp(Exp first_exp, Exp second_exp) {
			super(first_exp, second_exp);
		}
				
		public Object accept(Visitor visitor, Object env) {
			return visitor.visit(this, env);
		}
	}

	/**
	 * A car expression has the syntax
	 * 
	 * ( car expression )
	 * 
	 * @author hridesh
	 *
	 */
	public static class CarExp extends Exp {
		private Exp _arg; 
		public CarExp(Exp arg){
			_arg = arg;
		}
		public Exp arg() { return _arg; }
		public Object accept(Visitor visitor, Object env) {
			return visitor.visit(this, env);
		}
	}
	
	/**
	 * A cdr expression has the syntax
	 * 
	 * ( car expression )
	 * 
	 * @author hridesh
	 *
	 */
	public static class CdrExp extends Exp {
		private Exp _arg; 
		public CdrExp(Exp arg){
			_arg = arg;
		}
		public Exp arg() { return _arg; }
		public Object accept(Visitor visitor, Object env) {
			return visitor.visit(this, env);
		}
	}
	
	/**
	 * A cons expression has the syntax
	 * 
	 * ( cons expression expression )
	 * 
	 * @author hridesh
	 *
	 */
	public static class ConsExp extends Exp {
		private Exp _fst; 
		private Exp _snd; 
		public ConsExp(Exp fst, Exp snd){
			_fst = fst;
			_snd = snd;
		}
		public Exp fst() { return _fst; }
		public Exp snd() { return _snd; }
		public Object accept(Visitor visitor, Object env) {
			return visitor.visit(this, env);
		}
	}

	/**
	 * A list expression has the syntax
	 * 
	 * ( list expression* )
	 * 
	 * @author hridesh
	 *
	 */
	public static class ListExp extends Exp {
		private List<Exp> _elems;
		private Type _type;

		public ListExp(Type type, List<Exp> elems) {
			_type = type;
			_elems = elems;
		}

		public Type type() { return _type; }

		public List<Exp> elems() { return _elems; }
		public Object accept(Visitor visitor, Object env) {
			return visitor.visit(this, env);
		}
	}
	
	/**
	 * A null expression has the syntax
	 * 
	 * ( null? expression )
	 * 
	 * @author hridesh
	 *
	 */
	public static class NullExp extends Exp {
		private Exp _arg; 
		public NullExp(Exp arg){
			_arg = arg;
		}
		public Exp arg() { return _arg; }
		public Object accept(Visitor visitor, Object env) {
			return visitor.visit(this, env);
		}
	}

	/**
	 * Eval expression: evaluate the program that is _val
	 * @author hridesh
	 *
	 */
	public static class EvalExp extends Exp {
		private Exp _code; 
		public EvalExp(Exp code){
			_code = code;
		}
		public Exp code() { return _code; }
		public Object accept(Visitor visitor, Object env) {
			return visitor.visit(this, env);
		}
	}

	/**
	 * Read expression: reads the file that is _file
	 * @author hridesh
	 *
	 */
	public static class ReadExp extends Exp {
		private Exp _file; 
		public ReadExp(Exp file){
			_file = file;
		}
		public Exp file() { return _file; }
		public Object accept(Visitor visitor, Object env) {
			return visitor.visit(this, env);
		}
	}

	/**
	 * A letrec expression has the syntax 
	 * 
	 *  (letrec ((name expression)* ) expression)
	 *  
	 * @author hridesh
	 *
	 */
	public static class LetrecExp extends Exp {
		List<String> _names;
		List<Type> _types;
		List<Exp> _fun_exps; 
		Exp _body;
		
		public LetrecExp(List<String> names, List<Type> types,
				List<Exp> fun_exps, Exp body) {
			_names = names;
			_types = types;
			_fun_exps = fun_exps;
			_body = body;
		}

		public Object accept(Visitor visitor, Object env) {
			return visitor.visit(this, env);
		}

		public List<String> names() { return _names; }

		public List<Type> types() { return _types; }

		public List<Exp> fun_exps() { return _fun_exps; }

		public Exp body() { return _body; }
	}

    /**
     * A ref expression has the syntax 
     * 
     *  (ref expression)
     *  
     * @author hridesh
     *
     */
    public static class RefExp extends Exp {
        private Exp _value_exp;
        Type _type;

        public RefExp(Exp value_exp, Type type) {
        	_value_exp = value_exp;
        	_type = type;
        }

        public Object accept(Visitor visitor, Object env) {
                return visitor.visit(this, env);
        }

        public Exp value_exp() { return _value_exp; }

        public Type type() { return _type; }
}

    /**
     * A deref expression has the syntax 
     * 
     *  (deref expression)
     *  
     * @author hridesh
     *
     */
    public static class DerefExp extends Exp {
            private Exp _loc_exp;

            public DerefExp(Exp loc_exp) {
                    _loc_exp = loc_exp;
            }

            public Object accept(Visitor visitor, Object env) {
                    return visitor.visit(this, env);
            }

            public Exp loc_exp() { return _loc_exp; }

    }

    /**
     * An assign expression has the syntax 
     * 
     *  (set! expression expression)
     *  
     * @author hridesh
     *
     */
    public static class AssignExp extends Exp {
            private Exp _lhs_exp;
            private Exp _rhs_exp;

            public AssignExp(Exp lhs_exp, Exp rhs_exp) {
                    _lhs_exp = lhs_exp;
                    _rhs_exp = rhs_exp;
            }

            public Object accept(Visitor visitor, Object env) {
                    return visitor.visit(this, env);
            }

            public Exp lhs_exp() { return _lhs_exp; }
            public Exp rhs_exp() { return _rhs_exp; }

    }

    /**
     * A free expression has the syntax 
     * 
     *  (free expression)
     *  
     * @author hridesh
     *
     */
    public static class FreeExp extends Exp {
            private Exp _value_exp;

            public FreeExp(Exp value_exp) {
                    _value_exp = value_exp;
            }

            public Object accept(Visitor visitor, Object env) {
                    return visitor.visit(this, env);
            }

            public Exp value_exp() { return _value_exp; }

    }
	
	public interface Visitor <T,U> {
		// This interface should contain a signature for each concrete AST node.
		public T visit(AST.AddExp e, U env);
		public T visit(AST.UnitExp e, U env);
		public T visit(AST.NumExp e, U env);
		public T visit(AST.StrExp e, U env);
		public T visit(AST.BoolExp e, U env);
		public T visit(AST.DivExp e, U env);
		public T visit(AST.MultExp e, U env);
		public T visit(AST.Program p, U env);
		public T visit(AST.SubExp e, U env);
		public T visit(AST.VarExp e, U env);
		public T visit(AST.LetExp e, U env); // New for the varlang
		public T visit(AST.DefineDecl d, U env); // New for the definelang
		public T visit(AST.ReadExp e, U env); // New for the funclang
		public T visit(AST.EvalExp e, U env); // New for the funclang
		public T visit(AST.LambdaExp e, U env); // New for the funclang
		public T visit(AST.CallExp e, U env); // New for the funclang
		public T visit(AST.LetrecExp e, U env); // New for the funclang
		public T visit(AST.IfExp e, U env); // Additional expressions for convenience
		public T visit(AST.LessExp e, U env); // Additional expressions for convenience
		public T visit(AST.EqualExp e, U env); // Additional expressions for convenience
		public T visit(AST.GreaterExp e, U env); // Additional expressions for convenience
		public T visit(AST.CarExp e, U env); // Additional expressions for convenience
		public T visit(AST.CdrExp e, U env); // Additional expressions for convenience
		public T visit(AST.ConsExp e, U env); // Additional expressions for convenience
		public T visit(AST.ListExp e, U env); // Additional expressions for convenience
		public T visit(AST.NullExp e, U env); // Additional expressions for convenience
		public T visit(AST.RefExp e, U env); // New for the Reflang
		public T visit(AST.DerefExp e, U env); // New for the Reflang
		public T visit(AST.AssignExp e, U env); // New for the Reflang
		public T visit(AST.FreeExp e, U env); // New for the Reflang
	}	
}
