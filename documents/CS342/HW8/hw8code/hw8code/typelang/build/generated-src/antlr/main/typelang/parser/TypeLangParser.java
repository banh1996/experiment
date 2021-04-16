// Generated from typelang/parser/TypeLang.g by ANTLR 4.5
package typelang.parser; import static typelang.AST.*; import typelang.*; import typelang.Type.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class TypeLangParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.5", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, T__11=12, T__12=13, T__13=14, T__14=15, Define=16, 
		Let=17, Letrec=18, Lambda=19, If=20, Car=21, Cdr=22, Cons=23, List=24, 
		Null=25, Less=26, Equal=27, Greater=28, TrueLiteral=29, FalseLiteral=30, 
		Ref=31, Deref=32, Assign=33, Free=34, Fork=35, Lock=36, UnLock=37, Process=38, 
		Send=39, Stop=40, Self=41, Dot=42, Number=43, Identifier=44, Letter=45, 
		LetterOrDigit=46, StrLiteral=47, AT=48, ELLIPSIS=49, WS=50, Comment=51, 
		Line_Comment=52;
	public static final int
		RULE_program = 0, RULE_exp = 1, RULE_numexp = 2, RULE_addexp = 3, RULE_subexp = 4, 
		RULE_multexp = 5, RULE_divexp = 6, RULE_varexp = 7, RULE_letexp = 8, RULE_definedecl = 9, 
		RULE_carexp = 10, RULE_cdrexp = 11, RULE_consexp = 12, RULE_listexp = 13, 
		RULE_nullexp = 14, RULE_strexp = 15, RULE_boolexp = 16, RULE_lambdaexp = 17, 
		RULE_callexp = 18, RULE_ifexp = 19, RULE_lessexp = 20, RULE_equalexp = 21, 
		RULE_greaterexp = 22, RULE_letrecexp = 23, RULE_refexp = 24, RULE_derefexp = 25, 
		RULE_assignexp = 26, RULE_freeexp = 27, RULE_type = 28, RULE_booleantype = 29, 
		RULE_unittype = 30, RULE_numtype = 31, RULE_listtype = 32, RULE_pairtype = 33, 
		RULE_reft = 34, RULE_stringt = 35, RULE_funct = 36;
	public static final String[] ruleNames = {
		"program", "exp", "numexp", "addexp", "subexp", "multexp", "divexp", "varexp", 
		"letexp", "definedecl", "carexp", "cdrexp", "consexp", "listexp", "nullexp", 
		"strexp", "boolexp", "lambdaexp", "callexp", "ifexp", "lessexp", "equalexp", 
		"greaterexp", "letrecexp", "refexp", "derefexp", "assignexp", "freeexp", 
		"type", "booleantype", "unittype", "numtype", "listtype", "pairtype", 
		"reft", "stringt", "funct"
	};

	private static final String[] _LITERAL_NAMES = {
		null, "'-'", "'('", "'+'", "')'", "'*'", "'/'", "':'", "'bool'", "'unit'", 
		"'num'", "'List<'", "','", "'Ref'", "'Str'", "'->'", "'define'", "'let'", 
		"'letrec'", "'lambda'", "'if'", "'car'", "'cdr'", "'cons'", "'list'", 
		"'null?'", "'<'", "'='", "'>'", "'#t'", "'#f'", "'ref'", "'deref'", "'set!'", 
		"'free'", "'fork'", "'lock'", "'unlock'", "'process'", "'send'", "'stop'", 
		"'self'", "'.'", null, null, null, null, null, "'@'", "'...'"
	};
	private static final String[] _SYMBOLIC_NAMES = {
		null, null, null, null, null, null, null, null, null, null, null, null, 
		null, null, null, null, "Define", "Let", "Letrec", "Lambda", "If", "Car", 
		"Cdr", "Cons", "List", "Null", "Less", "Equal", "Greater", "TrueLiteral", 
		"FalseLiteral", "Ref", "Deref", "Assign", "Free", "Fork", "Lock", "UnLock", 
		"Process", "Send", "Stop", "Self", "Dot", "Number", "Identifier", "Letter", 
		"LetterOrDigit", "StrLiteral", "AT", "ELLIPSIS", "WS", "Comment", "Line_Comment"
	};
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "TypeLang.g"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public TypeLangParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}
	public static class ProgramContext extends ParserRuleContext {
		public Program ast;
		public ArrayList<DefineDecl> defs;
		public Exp expr;
		public DefinedeclContext def;
		public ExpContext e;
		public List<DefinedeclContext> definedecl() {
			return getRuleContexts(DefinedeclContext.class);
		}
		public DefinedeclContext definedecl(int i) {
			return getRuleContext(DefinedeclContext.class,i);
		}
		public ExpContext exp() {
			return getRuleContext(ExpContext.class,0);
		}
		public ProgramContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_program; }
	}

	public final ProgramContext program() throws RecognitionException {
		ProgramContext _localctx = new ProgramContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_program);
		 ((ProgramContext)_localctx).defs =  new ArrayList<DefineDecl>(); ((ProgramContext)_localctx).expr =  new UnitExp(); 
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(79);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,0,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(74);
					((ProgramContext)_localctx).def = definedecl();
					 _localctx.defs.add(((ProgramContext)_localctx).def.ast); 
					}
					} 
				}
				setState(81);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,0,_ctx);
			}
			setState(85);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__0) | (1L << T__1) | (1L << TrueLiteral) | (1L << FalseLiteral) | (1L << Number) | (1L << Identifier) | (1L << StrLiteral))) != 0)) {
				{
				setState(82);
				((ProgramContext)_localctx).e = exp();
				 ((ProgramContext)_localctx).expr =  ((ProgramContext)_localctx).e.ast; 
				}
			}

			 ((ProgramContext)_localctx).ast =  new Program(_localctx.defs, _localctx.expr); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ExpContext extends ParserRuleContext {
		public Exp ast;
		public VarexpContext va;
		public NumexpContext num;
		public StrexpContext str;
		public BoolexpContext bl;
		public AddexpContext add;
		public SubexpContext sub;
		public MultexpContext mul;
		public DivexpContext div;
		public LetexpContext let;
		public LambdaexpContext lam;
		public CallexpContext call;
		public IfexpContext i;
		public LessexpContext less;
		public EqualexpContext eq;
		public GreaterexpContext gt;
		public CarexpContext car;
		public CdrexpContext cdr;
		public ConsexpContext cons;
		public ListexpContext list;
		public NullexpContext nl;
		public LetrecexpContext lrec;
		public RefexpContext ref;
		public DerefexpContext deref;
		public AssignexpContext assign;
		public FreeexpContext free;
		public VarexpContext varexp() {
			return getRuleContext(VarexpContext.class,0);
		}
		public NumexpContext numexp() {
			return getRuleContext(NumexpContext.class,0);
		}
		public StrexpContext strexp() {
			return getRuleContext(StrexpContext.class,0);
		}
		public BoolexpContext boolexp() {
			return getRuleContext(BoolexpContext.class,0);
		}
		public AddexpContext addexp() {
			return getRuleContext(AddexpContext.class,0);
		}
		public SubexpContext subexp() {
			return getRuleContext(SubexpContext.class,0);
		}
		public MultexpContext multexp() {
			return getRuleContext(MultexpContext.class,0);
		}
		public DivexpContext divexp() {
			return getRuleContext(DivexpContext.class,0);
		}
		public LetexpContext letexp() {
			return getRuleContext(LetexpContext.class,0);
		}
		public LambdaexpContext lambdaexp() {
			return getRuleContext(LambdaexpContext.class,0);
		}
		public CallexpContext callexp() {
			return getRuleContext(CallexpContext.class,0);
		}
		public IfexpContext ifexp() {
			return getRuleContext(IfexpContext.class,0);
		}
		public LessexpContext lessexp() {
			return getRuleContext(LessexpContext.class,0);
		}
		public EqualexpContext equalexp() {
			return getRuleContext(EqualexpContext.class,0);
		}
		public GreaterexpContext greaterexp() {
			return getRuleContext(GreaterexpContext.class,0);
		}
		public CarexpContext carexp() {
			return getRuleContext(CarexpContext.class,0);
		}
		public CdrexpContext cdrexp() {
			return getRuleContext(CdrexpContext.class,0);
		}
		public ConsexpContext consexp() {
			return getRuleContext(ConsexpContext.class,0);
		}
		public ListexpContext listexp() {
			return getRuleContext(ListexpContext.class,0);
		}
		public NullexpContext nullexp() {
			return getRuleContext(NullexpContext.class,0);
		}
		public LetrecexpContext letrecexp() {
			return getRuleContext(LetrecexpContext.class,0);
		}
		public RefexpContext refexp() {
			return getRuleContext(RefexpContext.class,0);
		}
		public DerefexpContext derefexp() {
			return getRuleContext(DerefexpContext.class,0);
		}
		public AssignexpContext assignexp() {
			return getRuleContext(AssignexpContext.class,0);
		}
		public FreeexpContext freeexp() {
			return getRuleContext(FreeexpContext.class,0);
		}
		public ExpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_exp; }
	}

	public final ExpContext exp() throws RecognitionException {
		ExpContext _localctx = new ExpContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_exp);
		try {
			setState(164);
			switch ( getInterpreter().adaptivePredict(_input,2,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(89);
				((ExpContext)_localctx).va = varexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).va.ast; 
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(92);
				((ExpContext)_localctx).num = numexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).num.ast; 
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(95);
				((ExpContext)_localctx).str = strexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).str.ast; 
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(98);
				((ExpContext)_localctx).bl = boolexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).bl.ast; 
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(101);
				((ExpContext)_localctx).add = addexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).add.ast; 
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(104);
				((ExpContext)_localctx).sub = subexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).sub.ast; 
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(107);
				((ExpContext)_localctx).mul = multexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).mul.ast; 
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(110);
				((ExpContext)_localctx).div = divexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).div.ast; 
				}
				break;
			case 9:
				enterOuterAlt(_localctx, 9);
				{
				setState(113);
				((ExpContext)_localctx).let = letexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).let.ast; 
				}
				break;
			case 10:
				enterOuterAlt(_localctx, 10);
				{
				setState(116);
				((ExpContext)_localctx).lam = lambdaexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).lam.ast; 
				}
				break;
			case 11:
				enterOuterAlt(_localctx, 11);
				{
				setState(119);
				((ExpContext)_localctx).call = callexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).call.ast; 
				}
				break;
			case 12:
				enterOuterAlt(_localctx, 12);
				{
				setState(122);
				((ExpContext)_localctx).i = ifexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).i.ast; 
				}
				break;
			case 13:
				enterOuterAlt(_localctx, 13);
				{
				setState(125);
				((ExpContext)_localctx).less = lessexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).less.ast; 
				}
				break;
			case 14:
				enterOuterAlt(_localctx, 14);
				{
				setState(128);
				((ExpContext)_localctx).eq = equalexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).eq.ast; 
				}
				break;
			case 15:
				enterOuterAlt(_localctx, 15);
				{
				setState(131);
				((ExpContext)_localctx).gt = greaterexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).gt.ast; 
				}
				break;
			case 16:
				enterOuterAlt(_localctx, 16);
				{
				setState(134);
				((ExpContext)_localctx).car = carexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).car.ast; 
				}
				break;
			case 17:
				enterOuterAlt(_localctx, 17);
				{
				setState(137);
				((ExpContext)_localctx).cdr = cdrexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).cdr.ast; 
				}
				break;
			case 18:
				enterOuterAlt(_localctx, 18);
				{
				setState(140);
				((ExpContext)_localctx).cons = consexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).cons.ast; 
				}
				break;
			case 19:
				enterOuterAlt(_localctx, 19);
				{
				setState(143);
				((ExpContext)_localctx).list = listexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).list.ast; 
				}
				break;
			case 20:
				enterOuterAlt(_localctx, 20);
				{
				setState(146);
				((ExpContext)_localctx).nl = nullexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).nl.ast; 
				}
				break;
			case 21:
				enterOuterAlt(_localctx, 21);
				{
				setState(149);
				((ExpContext)_localctx).lrec = letrecexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).lrec.ast; 
				}
				break;
			case 22:
				enterOuterAlt(_localctx, 22);
				{
				setState(152);
				((ExpContext)_localctx).ref = refexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).ref.ast; 
				}
				break;
			case 23:
				enterOuterAlt(_localctx, 23);
				{
				setState(155);
				((ExpContext)_localctx).deref = derefexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).deref.ast; 
				}
				break;
			case 24:
				enterOuterAlt(_localctx, 24);
				{
				setState(158);
				((ExpContext)_localctx).assign = assignexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).assign.ast; 
				}
				break;
			case 25:
				enterOuterAlt(_localctx, 25);
				{
				setState(161);
				((ExpContext)_localctx).free = freeexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).free.ast; 
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class NumexpContext extends ParserRuleContext {
		public NumExp ast;
		public Token n0;
		public Token n1;
		public List<TerminalNode> Number() { return getTokens(TypeLangParser.Number); }
		public TerminalNode Number(int i) {
			return getToken(TypeLangParser.Number, i);
		}
		public TerminalNode Dot() { return getToken(TypeLangParser.Dot, 0); }
		public NumexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_numexp; }
	}

	public final NumexpContext numexp() throws RecognitionException {
		NumexpContext _localctx = new NumexpContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_numexp);
		try {
			setState(180);
			switch ( getInterpreter().adaptivePredict(_input,3,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(166);
				((NumexpContext)_localctx).n0 = match(Number);
				 ((NumexpContext)_localctx).ast =  new NumExp(Integer.parseInt((((NumexpContext)_localctx).n0!=null?((NumexpContext)_localctx).n0.getText():null))); 
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(168);
				match(T__0);
				setState(169);
				((NumexpContext)_localctx).n0 = match(Number);
				 ((NumexpContext)_localctx).ast =  new NumExp(-Integer.parseInt((((NumexpContext)_localctx).n0!=null?((NumexpContext)_localctx).n0.getText():null))); 
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(171);
				((NumexpContext)_localctx).n0 = match(Number);
				setState(172);
				match(Dot);
				setState(173);
				((NumexpContext)_localctx).n1 = match(Number);
				 ((NumexpContext)_localctx).ast =  new NumExp(Double.parseDouble((((NumexpContext)_localctx).n0!=null?((NumexpContext)_localctx).n0.getText():null)+"."+(((NumexpContext)_localctx).n1!=null?((NumexpContext)_localctx).n1.getText():null))); 
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(175);
				match(T__0);
				setState(176);
				((NumexpContext)_localctx).n0 = match(Number);
				setState(177);
				match(Dot);
				setState(178);
				((NumexpContext)_localctx).n1 = match(Number);
				 ((NumexpContext)_localctx).ast =  new NumExp(Double.parseDouble("-" + (((NumexpContext)_localctx).n0!=null?((NumexpContext)_localctx).n0.getText():null)+"."+(((NumexpContext)_localctx).n1!=null?((NumexpContext)_localctx).n1.getText():null))); 
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class AddexpContext extends ParserRuleContext {
		public AddExp ast;
		public ArrayList<Exp> list;
		public ExpContext e;
		public List<ExpContext> exp() {
			return getRuleContexts(ExpContext.class);
		}
		public ExpContext exp(int i) {
			return getRuleContext(ExpContext.class,i);
		}
		public AddexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_addexp; }
	}

	public final AddexpContext addexp() throws RecognitionException {
		AddexpContext _localctx = new AddexpContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_addexp);
		 ((AddexpContext)_localctx).list =  new ArrayList<Exp>(); 
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(182);
			match(T__1);
			setState(183);
			match(T__2);
			setState(184);
			((AddexpContext)_localctx).e = exp();
			 _localctx.list.add(((AddexpContext)_localctx).e.ast); 
			setState(189); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(186);
				((AddexpContext)_localctx).e = exp();
				 _localctx.list.add(((AddexpContext)_localctx).e.ast); 
				}
				}
				setState(191); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__0) | (1L << T__1) | (1L << TrueLiteral) | (1L << FalseLiteral) | (1L << Number) | (1L << Identifier) | (1L << StrLiteral))) != 0) );
			setState(193);
			match(T__3);
			 ((AddexpContext)_localctx).ast =  new AddExp(_localctx.list); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class SubexpContext extends ParserRuleContext {
		public SubExp ast;
		public ArrayList<Exp> list;
		public ExpContext e;
		public List<ExpContext> exp() {
			return getRuleContexts(ExpContext.class);
		}
		public ExpContext exp(int i) {
			return getRuleContext(ExpContext.class,i);
		}
		public SubexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_subexp; }
	}

	public final SubexpContext subexp() throws RecognitionException {
		SubexpContext _localctx = new SubexpContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_subexp);
		 ((SubexpContext)_localctx).list =  new ArrayList<Exp>(); 
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(196);
			match(T__1);
			setState(197);
			match(T__0);
			setState(198);
			((SubexpContext)_localctx).e = exp();
			 _localctx.list.add(((SubexpContext)_localctx).e.ast); 
			setState(203); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(200);
				((SubexpContext)_localctx).e = exp();
				 _localctx.list.add(((SubexpContext)_localctx).e.ast); 
				}
				}
				setState(205); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__0) | (1L << T__1) | (1L << TrueLiteral) | (1L << FalseLiteral) | (1L << Number) | (1L << Identifier) | (1L << StrLiteral))) != 0) );
			setState(207);
			match(T__3);
			 ((SubexpContext)_localctx).ast =  new SubExp(_localctx.list); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class MultexpContext extends ParserRuleContext {
		public MultExp ast;
		public ArrayList<Exp> list;
		public ExpContext e;
		public List<ExpContext> exp() {
			return getRuleContexts(ExpContext.class);
		}
		public ExpContext exp(int i) {
			return getRuleContext(ExpContext.class,i);
		}
		public MultexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_multexp; }
	}

	public final MultexpContext multexp() throws RecognitionException {
		MultexpContext _localctx = new MultexpContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_multexp);
		 ((MultexpContext)_localctx).list =  new ArrayList<Exp>(); 
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(210);
			match(T__1);
			setState(211);
			match(T__4);
			setState(212);
			((MultexpContext)_localctx).e = exp();
			 _localctx.list.add(((MultexpContext)_localctx).e.ast); 
			setState(217); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(214);
				((MultexpContext)_localctx).e = exp();
				 _localctx.list.add(((MultexpContext)_localctx).e.ast); 
				}
				}
				setState(219); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__0) | (1L << T__1) | (1L << TrueLiteral) | (1L << FalseLiteral) | (1L << Number) | (1L << Identifier) | (1L << StrLiteral))) != 0) );
			setState(221);
			match(T__3);
			 ((MultexpContext)_localctx).ast =  new MultExp(_localctx.list); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class DivexpContext extends ParserRuleContext {
		public DivExp ast;
		public ArrayList<Exp> list;
		public ExpContext e;
		public List<ExpContext> exp() {
			return getRuleContexts(ExpContext.class);
		}
		public ExpContext exp(int i) {
			return getRuleContext(ExpContext.class,i);
		}
		public DivexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_divexp; }
	}

	public final DivexpContext divexp() throws RecognitionException {
		DivexpContext _localctx = new DivexpContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_divexp);
		 ((DivexpContext)_localctx).list =  new ArrayList<Exp>(); 
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(224);
			match(T__1);
			setState(225);
			match(T__5);
			setState(226);
			((DivexpContext)_localctx).e = exp();
			 _localctx.list.add(((DivexpContext)_localctx).e.ast); 
			setState(231); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(228);
				((DivexpContext)_localctx).e = exp();
				 _localctx.list.add(((DivexpContext)_localctx).e.ast); 
				}
				}
				setState(233); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__0) | (1L << T__1) | (1L << TrueLiteral) | (1L << FalseLiteral) | (1L << Number) | (1L << Identifier) | (1L << StrLiteral))) != 0) );
			setState(235);
			match(T__3);
			 ((DivexpContext)_localctx).ast =  new DivExp(_localctx.list); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class VarexpContext extends ParserRuleContext {
		public VarExp ast;
		public Token id;
		public TerminalNode Identifier() { return getToken(TypeLangParser.Identifier, 0); }
		public VarexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_varexp; }
	}

	public final VarexpContext varexp() throws RecognitionException {
		VarexpContext _localctx = new VarexpContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_varexp);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(238);
			((VarexpContext)_localctx).id = match(Identifier);
			 ((VarexpContext)_localctx).ast =  new VarExp((((VarexpContext)_localctx).id!=null?((VarexpContext)_localctx).id.getText():null)); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class LetexpContext extends ParserRuleContext {
		public LetExp ast;
		public ArrayList<String> names;
		public ArrayList<Type> types;
		public ArrayList<Exp> value_exps;
		public Token id;
		public TypeContext t;
		public ExpContext e;
		public ExpContext body;
		public TerminalNode Let() { return getToken(TypeLangParser.Let, 0); }
		public List<ExpContext> exp() {
			return getRuleContexts(ExpContext.class);
		}
		public ExpContext exp(int i) {
			return getRuleContext(ExpContext.class,i);
		}
		public List<TerminalNode> Identifier() { return getTokens(TypeLangParser.Identifier); }
		public TerminalNode Identifier(int i) {
			return getToken(TypeLangParser.Identifier, i);
		}
		public List<TypeContext> type() {
			return getRuleContexts(TypeContext.class);
		}
		public TypeContext type(int i) {
			return getRuleContext(TypeContext.class,i);
		}
		public LetexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_letexp; }
	}

	public final LetexpContext letexp() throws RecognitionException {
		LetexpContext _localctx = new LetexpContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_letexp);
		 ((LetexpContext)_localctx).names =  new ArrayList<String>(); ((LetexpContext)_localctx).types = new ArrayList<Type>(); ((LetexpContext)_localctx).value_exps =  new ArrayList<Exp>(); 
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(241);
			match(T__1);
			setState(242);
			match(Let);
			setState(243);
			match(T__1);
			setState(252); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(244);
				match(T__1);
				setState(245);
				((LetexpContext)_localctx).id = match(Identifier);
				setState(246);
				match(T__6);
				setState(247);
				((LetexpContext)_localctx).t = type();
				setState(248);
				((LetexpContext)_localctx).e = exp();
				setState(249);
				match(T__3);
				 _localctx.names.add((((LetexpContext)_localctx).id!=null?((LetexpContext)_localctx).id.getText():null));_localctx.types.add(((LetexpContext)_localctx).t.ast); _localctx.value_exps.add(((LetexpContext)_localctx).e.ast); 
				}
				}
				setState(254); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==T__1 );
			setState(256);
			match(T__3);
			setState(257);
			((LetexpContext)_localctx).body = exp();
			setState(258);
			match(T__3);
			 ((LetexpContext)_localctx).ast =  new LetExp(_localctx.names, _localctx.types, _localctx.value_exps, ((LetexpContext)_localctx).body.ast); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class DefinedeclContext extends ParserRuleContext {
		public DefineDecl ast;
		public Token id;
		public TypeContext t;
		public ExpContext e;
		public TerminalNode Define() { return getToken(TypeLangParser.Define, 0); }
		public TerminalNode Identifier() { return getToken(TypeLangParser.Identifier, 0); }
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public ExpContext exp() {
			return getRuleContext(ExpContext.class,0);
		}
		public DefinedeclContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_definedecl; }
	}

	public final DefinedeclContext definedecl() throws RecognitionException {
		DefinedeclContext _localctx = new DefinedeclContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_definedecl);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(261);
			match(T__1);
			setState(262);
			match(Define);
			setState(263);
			((DefinedeclContext)_localctx).id = match(Identifier);
			setState(264);
			match(T__6);
			setState(265);
			((DefinedeclContext)_localctx).t = type();
			setState(266);
			((DefinedeclContext)_localctx).e = exp();
			setState(267);
			match(T__3);
			 ((DefinedeclContext)_localctx).ast =  new DefineDecl((((DefinedeclContext)_localctx).id!=null?((DefinedeclContext)_localctx).id.getText():null), ((DefinedeclContext)_localctx).t.ast, ((DefinedeclContext)_localctx).e.ast); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class CarexpContext extends ParserRuleContext {
		public CarExp ast;
		public ExpContext e;
		public TerminalNode Car() { return getToken(TypeLangParser.Car, 0); }
		public ExpContext exp() {
			return getRuleContext(ExpContext.class,0);
		}
		public CarexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_carexp; }
	}

	public final CarexpContext carexp() throws RecognitionException {
		CarexpContext _localctx = new CarexpContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_carexp);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(270);
			match(T__1);
			setState(271);
			match(Car);
			setState(272);
			((CarexpContext)_localctx).e = exp();
			setState(273);
			match(T__3);
			 ((CarexpContext)_localctx).ast =  new CarExp(((CarexpContext)_localctx).e.ast); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class CdrexpContext extends ParserRuleContext {
		public CdrExp ast;
		public ExpContext e;
		public TerminalNode Cdr() { return getToken(TypeLangParser.Cdr, 0); }
		public ExpContext exp() {
			return getRuleContext(ExpContext.class,0);
		}
		public CdrexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_cdrexp; }
	}

	public final CdrexpContext cdrexp() throws RecognitionException {
		CdrexpContext _localctx = new CdrexpContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_cdrexp);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(276);
			match(T__1);
			setState(277);
			match(Cdr);
			setState(278);
			((CdrexpContext)_localctx).e = exp();
			setState(279);
			match(T__3);
			 ((CdrexpContext)_localctx).ast =  new CdrExp(((CdrexpContext)_localctx).e.ast); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ConsexpContext extends ParserRuleContext {
		public ConsExp ast;
		public ExpContext e1;
		public ExpContext e2;
		public TerminalNode Cons() { return getToken(TypeLangParser.Cons, 0); }
		public List<ExpContext> exp() {
			return getRuleContexts(ExpContext.class);
		}
		public ExpContext exp(int i) {
			return getRuleContext(ExpContext.class,i);
		}
		public ConsexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_consexp; }
	}

	public final ConsexpContext consexp() throws RecognitionException {
		ConsexpContext _localctx = new ConsexpContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_consexp);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(282);
			match(T__1);
			setState(283);
			match(Cons);
			setState(284);
			((ConsexpContext)_localctx).e1 = exp();
			setState(285);
			((ConsexpContext)_localctx).e2 = exp();
			setState(286);
			match(T__3);
			 ((ConsexpContext)_localctx).ast =  new ConsExp(((ConsexpContext)_localctx).e1.ast,((ConsexpContext)_localctx).e2.ast); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ListexpContext extends ParserRuleContext {
		public ListExp ast;
		public ArrayList<Exp> list;
		public TypeContext t;
		public ExpContext e;
		public TerminalNode List() { return getToken(TypeLangParser.List, 0); }
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public List<ExpContext> exp() {
			return getRuleContexts(ExpContext.class);
		}
		public ExpContext exp(int i) {
			return getRuleContext(ExpContext.class,i);
		}
		public ListexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_listexp; }
	}

	public final ListexpContext listexp() throws RecognitionException {
		ListexpContext _localctx = new ListexpContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_listexp);
		 ((ListexpContext)_localctx).list =  new ArrayList<Exp>(); 
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(289);
			match(T__1);
			setState(290);
			match(List);
			setState(291);
			match(T__6);
			setState(292);
			((ListexpContext)_localctx).t = type();
			setState(298);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__0) | (1L << T__1) | (1L << TrueLiteral) | (1L << FalseLiteral) | (1L << Number) | (1L << Identifier) | (1L << StrLiteral))) != 0)) {
				{
				{
				setState(293);
				((ListexpContext)_localctx).e = exp();
				 _localctx.list.add(((ListexpContext)_localctx).e.ast); 
				}
				}
				setState(300);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(301);
			match(T__3);
			 ((ListexpContext)_localctx).ast =  new ListExp(((ListexpContext)_localctx).t.ast ,_localctx.list); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class NullexpContext extends ParserRuleContext {
		public NullExp ast;
		public ExpContext e;
		public TerminalNode Null() { return getToken(TypeLangParser.Null, 0); }
		public ExpContext exp() {
			return getRuleContext(ExpContext.class,0);
		}
		public NullexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_nullexp; }
	}

	public final NullexpContext nullexp() throws RecognitionException {
		NullexpContext _localctx = new NullexpContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_nullexp);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(304);
			match(T__1);
			setState(305);
			match(Null);
			setState(306);
			((NullexpContext)_localctx).e = exp();
			setState(307);
			match(T__3);
			 ((NullexpContext)_localctx).ast =  new NullExp(((NullexpContext)_localctx).e.ast); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class StrexpContext extends ParserRuleContext {
		public StrExp ast;
		public Token s;
		public TerminalNode StrLiteral() { return getToken(TypeLangParser.StrLiteral, 0); }
		public StrexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_strexp; }
	}

	public final StrexpContext strexp() throws RecognitionException {
		StrexpContext _localctx = new StrexpContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_strexp);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(310);
			((StrexpContext)_localctx).s = match(StrLiteral);
			 ((StrexpContext)_localctx).ast =  new StrExp((((StrexpContext)_localctx).s!=null?((StrexpContext)_localctx).s.getText():null)); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class BoolexpContext extends ParserRuleContext {
		public BoolExp ast;
		public TerminalNode TrueLiteral() { return getToken(TypeLangParser.TrueLiteral, 0); }
		public TerminalNode FalseLiteral() { return getToken(TypeLangParser.FalseLiteral, 0); }
		public BoolexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_boolexp; }
	}

	public final BoolexpContext boolexp() throws RecognitionException {
		BoolexpContext _localctx = new BoolexpContext(_ctx, getState());
		enterRule(_localctx, 32, RULE_boolexp);
		try {
			setState(317);
			switch (_input.LA(1)) {
			case TrueLiteral:
				enterOuterAlt(_localctx, 1);
				{
				setState(313);
				match(TrueLiteral);
				 ((BoolexpContext)_localctx).ast =  new BoolExp(true); 
				}
				break;
			case FalseLiteral:
				enterOuterAlt(_localctx, 2);
				{
				setState(315);
				match(FalseLiteral);
				 ((BoolexpContext)_localctx).ast =  new BoolExp(false); 
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class LambdaexpContext extends ParserRuleContext {
		public LambdaExp ast;
		public ArrayList<String> formals;
		public ArrayList<Type> types;
		public Token id;
		public TypeContext ty;
		public ExpContext body;
		public TerminalNode Lambda() { return getToken(TypeLangParser.Lambda, 0); }
		public ExpContext exp() {
			return getRuleContext(ExpContext.class,0);
		}
		public List<TerminalNode> Identifier() { return getTokens(TypeLangParser.Identifier); }
		public TerminalNode Identifier(int i) {
			return getToken(TypeLangParser.Identifier, i);
		}
		public List<TypeContext> type() {
			return getRuleContexts(TypeContext.class);
		}
		public TypeContext type(int i) {
			return getRuleContext(TypeContext.class,i);
		}
		public LambdaexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_lambdaexp; }
	}

	public final LambdaexpContext lambdaexp() throws RecognitionException {
		LambdaexpContext _localctx = new LambdaexpContext(_ctx, getState());
		enterRule(_localctx, 34, RULE_lambdaexp);
		 ((LambdaexpContext)_localctx).formals =  new ArrayList<String>(); ((LambdaexpContext)_localctx).types =  new ArrayList<Type>(); 
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(319);
			match(T__1);
			setState(320);
			match(Lambda);
			setState(321);
			match(T__1);
			setState(329);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==Identifier) {
				{
				{
				setState(322);
				((LambdaexpContext)_localctx).id = match(Identifier);
				setState(323);
				match(T__6);
				setState(324);
				((LambdaexpContext)_localctx).ty = type();
				 _localctx.formals.add((((LambdaexpContext)_localctx).id!=null?((LambdaexpContext)_localctx).id.getText():null)); _localctx.types.add(((LambdaexpContext)_localctx).ty.ast); 
				}
				}
				setState(331);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(332);
			match(T__3);
			setState(333);
			((LambdaexpContext)_localctx).body = exp();
			setState(334);
			match(T__3);
			((LambdaexpContext)_localctx).ast =  new LambdaExp(_localctx.formals, _localctx.types, ((LambdaexpContext)_localctx).body.ast); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class CallexpContext extends ParserRuleContext {
		public CallExp ast;
		public ArrayList<Exp> arguments =  new ArrayList<Exp>();;
		public ExpContext f;
		public ExpContext e;
		public List<ExpContext> exp() {
			return getRuleContexts(ExpContext.class);
		}
		public ExpContext exp(int i) {
			return getRuleContext(ExpContext.class,i);
		}
		public CallexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_callexp; }
	}

	public final CallexpContext callexp() throws RecognitionException {
		CallexpContext _localctx = new CallexpContext(_ctx, getState());
		enterRule(_localctx, 36, RULE_callexp);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(337);
			match(T__1);
			setState(338);
			((CallexpContext)_localctx).f = exp();
			setState(344);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__0) | (1L << T__1) | (1L << TrueLiteral) | (1L << FalseLiteral) | (1L << Number) | (1L << Identifier) | (1L << StrLiteral))) != 0)) {
				{
				{
				setState(339);
				((CallexpContext)_localctx).e = exp();
				 _localctx.arguments.add(((CallexpContext)_localctx).e.ast); 
				}
				}
				setState(346);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(347);
			match(T__3);
			 ((CallexpContext)_localctx).ast =  new CallExp(((CallexpContext)_localctx).f.ast,_localctx.arguments); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class IfexpContext extends ParserRuleContext {
		public IfExp ast;
		public ExpContext e1;
		public ExpContext e2;
		public ExpContext e3;
		public TerminalNode If() { return getToken(TypeLangParser.If, 0); }
		public List<ExpContext> exp() {
			return getRuleContexts(ExpContext.class);
		}
		public ExpContext exp(int i) {
			return getRuleContext(ExpContext.class,i);
		}
		public IfexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_ifexp; }
	}

	public final IfexpContext ifexp() throws RecognitionException {
		IfexpContext _localctx = new IfexpContext(_ctx, getState());
		enterRule(_localctx, 38, RULE_ifexp);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(350);
			match(T__1);
			setState(351);
			match(If);
			setState(352);
			((IfexpContext)_localctx).e1 = exp();
			setState(353);
			((IfexpContext)_localctx).e2 = exp();
			setState(354);
			((IfexpContext)_localctx).e3 = exp();
			setState(355);
			match(T__3);
			 ((IfexpContext)_localctx).ast =  new IfExp(((IfexpContext)_localctx).e1.ast,((IfexpContext)_localctx).e2.ast,((IfexpContext)_localctx).e3.ast); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class LessexpContext extends ParserRuleContext {
		public LessExp ast;
		public ExpContext e1;
		public ExpContext e2;
		public TerminalNode Less() { return getToken(TypeLangParser.Less, 0); }
		public List<ExpContext> exp() {
			return getRuleContexts(ExpContext.class);
		}
		public ExpContext exp(int i) {
			return getRuleContext(ExpContext.class,i);
		}
		public LessexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_lessexp; }
	}

	public final LessexpContext lessexp() throws RecognitionException {
		LessexpContext _localctx = new LessexpContext(_ctx, getState());
		enterRule(_localctx, 40, RULE_lessexp);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(358);
			match(T__1);
			setState(359);
			match(Less);
			setState(360);
			((LessexpContext)_localctx).e1 = exp();
			setState(361);
			((LessexpContext)_localctx).e2 = exp();
			setState(362);
			match(T__3);
			 ((LessexpContext)_localctx).ast =  new LessExp(((LessexpContext)_localctx).e1.ast,((LessexpContext)_localctx).e2.ast); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class EqualexpContext extends ParserRuleContext {
		public EqualExp ast;
		public ExpContext e1;
		public ExpContext e2;
		public TerminalNode Equal() { return getToken(TypeLangParser.Equal, 0); }
		public List<ExpContext> exp() {
			return getRuleContexts(ExpContext.class);
		}
		public ExpContext exp(int i) {
			return getRuleContext(ExpContext.class,i);
		}
		public EqualexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_equalexp; }
	}

	public final EqualexpContext equalexp() throws RecognitionException {
		EqualexpContext _localctx = new EqualexpContext(_ctx, getState());
		enterRule(_localctx, 42, RULE_equalexp);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(365);
			match(T__1);
			setState(366);
			match(Equal);
			setState(367);
			((EqualexpContext)_localctx).e1 = exp();
			setState(368);
			((EqualexpContext)_localctx).e2 = exp();
			setState(369);
			match(T__3);
			 ((EqualexpContext)_localctx).ast =  new EqualExp(((EqualexpContext)_localctx).e1.ast,((EqualexpContext)_localctx).e2.ast); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class GreaterexpContext extends ParserRuleContext {
		public GreaterExp ast;
		public ExpContext e1;
		public ExpContext e2;
		public TerminalNode Greater() { return getToken(TypeLangParser.Greater, 0); }
		public List<ExpContext> exp() {
			return getRuleContexts(ExpContext.class);
		}
		public ExpContext exp(int i) {
			return getRuleContext(ExpContext.class,i);
		}
		public GreaterexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_greaterexp; }
	}

	public final GreaterexpContext greaterexp() throws RecognitionException {
		GreaterexpContext _localctx = new GreaterexpContext(_ctx, getState());
		enterRule(_localctx, 44, RULE_greaterexp);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(372);
			match(T__1);
			setState(373);
			match(Greater);
			setState(374);
			((GreaterexpContext)_localctx).e1 = exp();
			setState(375);
			((GreaterexpContext)_localctx).e2 = exp();
			setState(376);
			match(T__3);
			 ((GreaterexpContext)_localctx).ast =  new GreaterExp(((GreaterexpContext)_localctx).e1.ast,((GreaterexpContext)_localctx).e2.ast); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class LetrecexpContext extends ParserRuleContext {
		public LetrecExp ast;
		public ArrayList<String> ids =  new ArrayList<String>();
		public ArrayList<Type> types =  new ArrayList<Type>();
		public ArrayList<Exp> funs =  new ArrayList<Exp>();;
		public Token id;
		public TypeContext t;
		public ExpContext fun;
		public ExpContext body;
		public TerminalNode Letrec() { return getToken(TypeLangParser.Letrec, 0); }
		public List<ExpContext> exp() {
			return getRuleContexts(ExpContext.class);
		}
		public ExpContext exp(int i) {
			return getRuleContext(ExpContext.class,i);
		}
		public List<TerminalNode> Identifier() { return getTokens(TypeLangParser.Identifier); }
		public TerminalNode Identifier(int i) {
			return getToken(TypeLangParser.Identifier, i);
		}
		public List<TypeContext> type() {
			return getRuleContexts(TypeContext.class);
		}
		public TypeContext type(int i) {
			return getRuleContext(TypeContext.class,i);
		}
		public LetrecexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_letrecexp; }
	}

	public final LetrecexpContext letrecexp() throws RecognitionException {
		LetrecexpContext _localctx = new LetrecexpContext(_ctx, getState());
		enterRule(_localctx, 46, RULE_letrecexp);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(379);
			match(T__1);
			setState(380);
			match(Letrec);
			setState(381);
			match(T__1);
			setState(390); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(382);
				match(T__1);
				setState(383);
				((LetrecexpContext)_localctx).id = match(Identifier);
				setState(384);
				match(T__6);
				setState(385);
				((LetrecexpContext)_localctx).t = type();
				setState(386);
				((LetrecexpContext)_localctx).fun = exp();
				setState(387);
				match(T__3);
				 _localctx.ids.add((((LetrecexpContext)_localctx).id!=null?((LetrecexpContext)_localctx).id.getText():null)); _localctx.types.add(((LetrecexpContext)_localctx).t.ast);_localctx.funs.add(((LetrecexpContext)_localctx).fun.ast); 
				}
				}
				setState(392); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==T__1 );
			setState(394);
			match(T__3);
			setState(395);
			((LetrecexpContext)_localctx).body = exp();
			setState(396);
			match(T__3);
			 ((LetrecexpContext)_localctx).ast =  new LetrecExp(_localctx.ids, _localctx.types, _localctx.funs, ((LetrecexpContext)_localctx).body.ast); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class RefexpContext extends ParserRuleContext {
		public RefExp ast;
		public TypeContext t;
		public ExpContext e;
		public TerminalNode Ref() { return getToken(TypeLangParser.Ref, 0); }
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public ExpContext exp() {
			return getRuleContext(ExpContext.class,0);
		}
		public RefexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_refexp; }
	}

	public final RefexpContext refexp() throws RecognitionException {
		RefexpContext _localctx = new RefexpContext(_ctx, getState());
		enterRule(_localctx, 48, RULE_refexp);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(399);
			match(T__1);
			setState(400);
			match(Ref);
			setState(401);
			match(T__6);
			setState(402);
			((RefexpContext)_localctx).t = type();
			setState(403);
			((RefexpContext)_localctx).e = exp();
			setState(404);
			match(T__3);
			 ((RefexpContext)_localctx).ast =  new RefExp(((RefexpContext)_localctx).e.ast, ((RefexpContext)_localctx).t.ast); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class DerefexpContext extends ParserRuleContext {
		public DerefExp ast;
		public ExpContext e;
		public TerminalNode Deref() { return getToken(TypeLangParser.Deref, 0); }
		public ExpContext exp() {
			return getRuleContext(ExpContext.class,0);
		}
		public DerefexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_derefexp; }
	}

	public final DerefexpContext derefexp() throws RecognitionException {
		DerefexpContext _localctx = new DerefexpContext(_ctx, getState());
		enterRule(_localctx, 50, RULE_derefexp);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(407);
			match(T__1);
			setState(408);
			match(Deref);
			setState(409);
			((DerefexpContext)_localctx).e = exp();
			setState(410);
			match(T__3);
			 ((DerefexpContext)_localctx).ast =  new DerefExp(((DerefexpContext)_localctx).e.ast); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class AssignexpContext extends ParserRuleContext {
		public AssignExp ast;
		public ExpContext e1;
		public ExpContext e2;
		public TerminalNode Assign() { return getToken(TypeLangParser.Assign, 0); }
		public List<ExpContext> exp() {
			return getRuleContexts(ExpContext.class);
		}
		public ExpContext exp(int i) {
			return getRuleContext(ExpContext.class,i);
		}
		public AssignexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_assignexp; }
	}

	public final AssignexpContext assignexp() throws RecognitionException {
		AssignexpContext _localctx = new AssignexpContext(_ctx, getState());
		enterRule(_localctx, 52, RULE_assignexp);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(413);
			match(T__1);
			setState(414);
			match(Assign);
			setState(415);
			((AssignexpContext)_localctx).e1 = exp();
			setState(416);
			((AssignexpContext)_localctx).e2 = exp();
			setState(417);
			match(T__3);
			 ((AssignexpContext)_localctx).ast =  new AssignExp(((AssignexpContext)_localctx).e1.ast, ((AssignexpContext)_localctx).e2.ast); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class FreeexpContext extends ParserRuleContext {
		public FreeExp ast;
		public ExpContext e;
		public TerminalNode Free() { return getToken(TypeLangParser.Free, 0); }
		public ExpContext exp() {
			return getRuleContext(ExpContext.class,0);
		}
		public FreeexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_freeexp; }
	}

	public final FreeexpContext freeexp() throws RecognitionException {
		FreeexpContext _localctx = new FreeexpContext(_ctx, getState());
		enterRule(_localctx, 54, RULE_freeexp);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(420);
			match(T__1);
			setState(421);
			match(Free);
			setState(422);
			((FreeexpContext)_localctx).e = exp();
			setState(423);
			match(T__3);
			 ((FreeexpContext)_localctx).ast =  new FreeExp(((FreeexpContext)_localctx).e.ast); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class TypeContext extends ParserRuleContext {
		public Type ast;
		public BooleantypeContext b;
		public FunctContext f;
		public NumtypeContext n;
		public ListtypeContext l;
		public PairtypeContext p;
		public StringtContext s;
		public ReftContext r;
		public UnittypeContext u;
		public BooleantypeContext booleantype() {
			return getRuleContext(BooleantypeContext.class,0);
		}
		public FunctContext funct() {
			return getRuleContext(FunctContext.class,0);
		}
		public NumtypeContext numtype() {
			return getRuleContext(NumtypeContext.class,0);
		}
		public ListtypeContext listtype() {
			return getRuleContext(ListtypeContext.class,0);
		}
		public PairtypeContext pairtype() {
			return getRuleContext(PairtypeContext.class,0);
		}
		public StringtContext stringt() {
			return getRuleContext(StringtContext.class,0);
		}
		public ReftContext reft() {
			return getRuleContext(ReftContext.class,0);
		}
		public UnittypeContext unittype() {
			return getRuleContext(UnittypeContext.class,0);
		}
		public TypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_type; }
	}

	public final TypeContext type() throws RecognitionException {
		TypeContext _localctx = new TypeContext(_ctx, getState());
		enterRule(_localctx, 56, RULE_type);
		try {
			setState(450);
			switch ( getInterpreter().adaptivePredict(_input,14,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(426);
				((TypeContext)_localctx).b = booleantype();
				 ((TypeContext)_localctx).ast =  ((TypeContext)_localctx).b.ast; 
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(429);
				((TypeContext)_localctx).f = funct();
				 ((TypeContext)_localctx).ast =  ((TypeContext)_localctx).f.ast; 
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(432);
				((TypeContext)_localctx).n = numtype();
				 ((TypeContext)_localctx).ast =  ((TypeContext)_localctx).n.ast; 
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(435);
				((TypeContext)_localctx).l = listtype();
				 ((TypeContext)_localctx).ast =  ((TypeContext)_localctx).l.ast; 
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(438);
				((TypeContext)_localctx).p = pairtype();
				 ((TypeContext)_localctx).ast =  ((TypeContext)_localctx).p.ast; 
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(441);
				((TypeContext)_localctx).s = stringt();
				 ((TypeContext)_localctx).ast =  ((TypeContext)_localctx).s.ast; 
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(444);
				((TypeContext)_localctx).r = reft();
				 ((TypeContext)_localctx).ast =  ((TypeContext)_localctx).r.ast; 
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(447);
				((TypeContext)_localctx).u = unittype();
				 ((TypeContext)_localctx).ast =  ((TypeContext)_localctx).u.ast; 
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class BooleantypeContext extends ParserRuleContext {
		public BoolT ast;
		public BooleantypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_booleantype; }
	}

	public final BooleantypeContext booleantype() throws RecognitionException {
		BooleantypeContext _localctx = new BooleantypeContext(_ctx, getState());
		enterRule(_localctx, 58, RULE_booleantype);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(452);
			match(T__7);
			 ((BooleantypeContext)_localctx).ast =  new BoolT(); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class UnittypeContext extends ParserRuleContext {
		public UnitT ast;
		public UnittypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_unittype; }
	}

	public final UnittypeContext unittype() throws RecognitionException {
		UnittypeContext _localctx = new UnittypeContext(_ctx, getState());
		enterRule(_localctx, 60, RULE_unittype);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(455);
			match(T__8);
			 ((UnittypeContext)_localctx).ast =  new UnitT(); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class NumtypeContext extends ParserRuleContext {
		public NumT ast;
		public NumtypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_numtype; }
	}

	public final NumtypeContext numtype() throws RecognitionException {
		NumtypeContext _localctx = new NumtypeContext(_ctx, getState());
		enterRule(_localctx, 62, RULE_numtype);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(458);
			match(T__9);
			 ((NumtypeContext)_localctx).ast =  new NumT(); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ListtypeContext extends ParserRuleContext {
		public ListT ast;
		public TypeContext ret;
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public ListtypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_listtype; }
	}

	public final ListtypeContext listtype() throws RecognitionException {
		ListtypeContext _localctx = new ListtypeContext(_ctx, getState());
		enterRule(_localctx, 64, RULE_listtype);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(461);
			match(T__10);
			setState(462);
			((ListtypeContext)_localctx).ret = type();
			setState(463);
			match(Greater);
			 ((ListtypeContext)_localctx).ast =  new ListT(((ListtypeContext)_localctx).ret.ast); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class PairtypeContext extends ParserRuleContext {
		public PairT ast;
		public TypeContext fst;
		public TypeContext snd;
		public List<TypeContext> type() {
			return getRuleContexts(TypeContext.class);
		}
		public TypeContext type(int i) {
			return getRuleContext(TypeContext.class,i);
		}
		public PairtypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_pairtype; }
	}

	public final PairtypeContext pairtype() throws RecognitionException {
		PairtypeContext _localctx = new PairtypeContext(_ctx, getState());
		enterRule(_localctx, 66, RULE_pairtype);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(466);
			match(T__1);
			setState(467);
			((PairtypeContext)_localctx).fst = type();
			setState(468);
			match(T__11);
			setState(469);
			((PairtypeContext)_localctx).snd = type();
			setState(470);
			match(T__3);
			 ((PairtypeContext)_localctx).ast =  new PairT(((PairtypeContext)_localctx).fst.ast, ((PairtypeContext)_localctx).snd.ast); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ReftContext extends ParserRuleContext {
		public RefT ast;
		public TypeContext ret;
		public TypeContext type() {
			return getRuleContext(TypeContext.class,0);
		}
		public ReftContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_reft; }
	}

	public final ReftContext reft() throws RecognitionException {
		ReftContext _localctx = new ReftContext(_ctx, getState());
		enterRule(_localctx, 68, RULE_reft);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(473);
			match(T__12);
			setState(474);
			((ReftContext)_localctx).ret = type();
			 ((ReftContext)_localctx).ast =  new RefT(((ReftContext)_localctx).ret.ast); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class StringtContext extends ParserRuleContext {
		public StringT ast;
		public StringtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stringt; }
	}

	public final StringtContext stringt() throws RecognitionException {
		StringtContext _localctx = new StringtContext(_ctx, getState());
		enterRule(_localctx, 70, RULE_stringt);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(477);
			match(T__13);
			  ((StringtContext)_localctx).ast =  new StringT(); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class FunctContext extends ParserRuleContext {
		public FuncT ast;
		public ArrayList<Type> formals;
		public TypeContext e;
		public TypeContext ret;
		public List<TypeContext> type() {
			return getRuleContexts(TypeContext.class);
		}
		public TypeContext type(int i) {
			return getRuleContext(TypeContext.class,i);
		}
		public FunctContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_funct; }
	}

	public final FunctContext funct() throws RecognitionException {
		FunctContext _localctx = new FunctContext(_ctx, getState());
		enterRule(_localctx, 72, RULE_funct);
		 ((FunctContext)_localctx).formals =  new ArrayList<Type>(); 
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(480);
			match(T__1);
			setState(486);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__1) | (1L << T__7) | (1L << T__8) | (1L << T__9) | (1L << T__10) | (1L << T__12) | (1L << T__13))) != 0)) {
				{
				{
				setState(481);
				((FunctContext)_localctx).e = type();
				 _localctx.formals.add(((FunctContext)_localctx).e.ast);
				}
				}
				setState(488);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(489);
			match(T__14);
			setState(490);
			((FunctContext)_localctx).ret = type();
			setState(491);
			match(T__3);
			 ((FunctContext)_localctx).ast =  new FuncT(_localctx.formals, ((FunctContext)_localctx).ret.ast); 
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static final String _serializedATN =
		"\3\u0430\ud6d1\u8206\uad2d\u4417\uaef1\u8d80\uaadd\3\66\u01f1\4\2\t\2"+
		"\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13"+
		"\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31\t\31"+
		"\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37\4 \t \4!"+
		"\t!\4\"\t\"\4#\t#\4$\t$\4%\t%\4&\t&\3\2\3\2\3\2\7\2P\n\2\f\2\16\2S\13"+
		"\2\3\2\3\2\3\2\5\2X\n\2\3\2\3\2\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3"+
		"\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3"+
		"\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3"+
		"\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3"+
		"\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\5\3\u00a7\n\3\3\4"+
		"\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\5\4\u00b7\n\4\3\5"+
		"\3\5\3\5\3\5\3\5\3\5\3\5\6\5\u00c0\n\5\r\5\16\5\u00c1\3\5\3\5\3\5\3\6"+
		"\3\6\3\6\3\6\3\6\3\6\3\6\6\6\u00ce\n\6\r\6\16\6\u00cf\3\6\3\6\3\6\3\7"+
		"\3\7\3\7\3\7\3\7\3\7\3\7\6\7\u00dc\n\7\r\7\16\7\u00dd\3\7\3\7\3\7\3\b"+
		"\3\b\3\b\3\b\3\b\3\b\3\b\6\b\u00ea\n\b\r\b\16\b\u00eb\3\b\3\b\3\b\3\t"+
		"\3\t\3\t\3\n\3\n\3\n\3\n\3\n\3\n\3\n\3\n\3\n\3\n\3\n\6\n\u00ff\n\n\r\n"+
		"\16\n\u0100\3\n\3\n\3\n\3\n\3\n\3\13\3\13\3\13\3\13\3\13\3\13\3\13\3\13"+
		"\3\13\3\f\3\f\3\f\3\f\3\f\3\f\3\r\3\r\3\r\3\r\3\r\3\r\3\16\3\16\3\16\3"+
		"\16\3\16\3\16\3\16\3\17\3\17\3\17\3\17\3\17\3\17\3\17\7\17\u012b\n\17"+
		"\f\17\16\17\u012e\13\17\3\17\3\17\3\17\3\20\3\20\3\20\3\20\3\20\3\20\3"+
		"\21\3\21\3\21\3\22\3\22\3\22\3\22\5\22\u0140\n\22\3\23\3\23\3\23\3\23"+
		"\3\23\3\23\3\23\3\23\7\23\u014a\n\23\f\23\16\23\u014d\13\23\3\23\3\23"+
		"\3\23\3\23\3\23\3\24\3\24\3\24\3\24\3\24\7\24\u0159\n\24\f\24\16\24\u015c"+
		"\13\24\3\24\3\24\3\24\3\25\3\25\3\25\3\25\3\25\3\25\3\25\3\25\3\26\3\26"+
		"\3\26\3\26\3\26\3\26\3\26\3\27\3\27\3\27\3\27\3\27\3\27\3\27\3\30\3\30"+
		"\3\30\3\30\3\30\3\30\3\30\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31\3\31"+
		"\3\31\3\31\6\31\u0189\n\31\r\31\16\31\u018a\3\31\3\31\3\31\3\31\3\31\3"+
		"\32\3\32\3\32\3\32\3\32\3\32\3\32\3\32\3\33\3\33\3\33\3\33\3\33\3\33\3"+
		"\34\3\34\3\34\3\34\3\34\3\34\3\34\3\35\3\35\3\35\3\35\3\35\3\35\3\36\3"+
		"\36\3\36\3\36\3\36\3\36\3\36\3\36\3\36\3\36\3\36\3\36\3\36\3\36\3\36\3"+
		"\36\3\36\3\36\3\36\3\36\3\36\3\36\3\36\3\36\5\36\u01c5\n\36\3\37\3\37"+
		"\3\37\3 \3 \3 \3!\3!\3!\3\"\3\"\3\"\3\"\3\"\3#\3#\3#\3#\3#\3#\3#\3$\3"+
		"$\3$\3$\3%\3%\3%\3&\3&\3&\3&\7&\u01e7\n&\f&\16&\u01ea\13&\3&\3&\3&\3&"+
		"\3&\3&\2\2\'\2\4\6\b\n\f\16\20\22\24\26\30\32\34\36 \"$&(*,.\60\62\64"+
		"\668:<>@BDFHJ\2\2\u01fa\2Q\3\2\2\2\4\u00a6\3\2\2\2\6\u00b6\3\2\2\2\b\u00b8"+
		"\3\2\2\2\n\u00c6\3\2\2\2\f\u00d4\3\2\2\2\16\u00e2\3\2\2\2\20\u00f0\3\2"+
		"\2\2\22\u00f3\3\2\2\2\24\u0107\3\2\2\2\26\u0110\3\2\2\2\30\u0116\3\2\2"+
		"\2\32\u011c\3\2\2\2\34\u0123\3\2\2\2\36\u0132\3\2\2\2 \u0138\3\2\2\2\""+
		"\u013f\3\2\2\2$\u0141\3\2\2\2&\u0153\3\2\2\2(\u0160\3\2\2\2*\u0168\3\2"+
		"\2\2,\u016f\3\2\2\2.\u0176\3\2\2\2\60\u017d\3\2\2\2\62\u0191\3\2\2\2\64"+
		"\u0199\3\2\2\2\66\u019f\3\2\2\28\u01a6\3\2\2\2:\u01c4\3\2\2\2<\u01c6\3"+
		"\2\2\2>\u01c9\3\2\2\2@\u01cc\3\2\2\2B\u01cf\3\2\2\2D\u01d4\3\2\2\2F\u01db"+
		"\3\2\2\2H\u01df\3\2\2\2J\u01e2\3\2\2\2LM\5\24\13\2MN\b\2\1\2NP\3\2\2\2"+
		"OL\3\2\2\2PS\3\2\2\2QO\3\2\2\2QR\3\2\2\2RW\3\2\2\2SQ\3\2\2\2TU\5\4\3\2"+
		"UV\b\2\1\2VX\3\2\2\2WT\3\2\2\2WX\3\2\2\2XY\3\2\2\2YZ\b\2\1\2Z\3\3\2\2"+
		"\2[\\\5\20\t\2\\]\b\3\1\2]\u00a7\3\2\2\2^_\5\6\4\2_`\b\3\1\2`\u00a7\3"+
		"\2\2\2ab\5 \21\2bc\b\3\1\2c\u00a7\3\2\2\2de\5\"\22\2ef\b\3\1\2f\u00a7"+
		"\3\2\2\2gh\5\b\5\2hi\b\3\1\2i\u00a7\3\2\2\2jk\5\n\6\2kl\b\3\1\2l\u00a7"+
		"\3\2\2\2mn\5\f\7\2no\b\3\1\2o\u00a7\3\2\2\2pq\5\16\b\2qr\b\3\1\2r\u00a7"+
		"\3\2\2\2st\5\22\n\2tu\b\3\1\2u\u00a7\3\2\2\2vw\5$\23\2wx\b\3\1\2x\u00a7"+
		"\3\2\2\2yz\5&\24\2z{\b\3\1\2{\u00a7\3\2\2\2|}\5(\25\2}~\b\3\1\2~\u00a7"+
		"\3\2\2\2\177\u0080\5*\26\2\u0080\u0081\b\3\1\2\u0081\u00a7\3\2\2\2\u0082"+
		"\u0083\5,\27\2\u0083\u0084\b\3\1\2\u0084\u00a7\3\2\2\2\u0085\u0086\5."+
		"\30\2\u0086\u0087\b\3\1\2\u0087\u00a7\3\2\2\2\u0088\u0089\5\26\f\2\u0089"+
		"\u008a\b\3\1\2\u008a\u00a7\3\2\2\2\u008b\u008c\5\30\r\2\u008c\u008d\b"+
		"\3\1\2\u008d\u00a7\3\2\2\2\u008e\u008f\5\32\16\2\u008f\u0090\b\3\1\2\u0090"+
		"\u00a7\3\2\2\2\u0091\u0092\5\34\17\2\u0092\u0093\b\3\1\2\u0093\u00a7\3"+
		"\2\2\2\u0094\u0095\5\36\20\2\u0095\u0096\b\3\1\2\u0096\u00a7\3\2\2\2\u0097"+
		"\u0098\5\60\31\2\u0098\u0099\b\3\1\2\u0099\u00a7\3\2\2\2\u009a\u009b\5"+
		"\62\32\2\u009b\u009c\b\3\1\2\u009c\u00a7\3\2\2\2\u009d\u009e\5\64\33\2"+
		"\u009e\u009f\b\3\1\2\u009f\u00a7\3\2\2\2\u00a0\u00a1\5\66\34\2\u00a1\u00a2"+
		"\b\3\1\2\u00a2\u00a7\3\2\2\2\u00a3\u00a4\58\35\2\u00a4\u00a5\b\3\1\2\u00a5"+
		"\u00a7\3\2\2\2\u00a6[\3\2\2\2\u00a6^\3\2\2\2\u00a6a\3\2\2\2\u00a6d\3\2"+
		"\2\2\u00a6g\3\2\2\2\u00a6j\3\2\2\2\u00a6m\3\2\2\2\u00a6p\3\2\2\2\u00a6"+
		"s\3\2\2\2\u00a6v\3\2\2\2\u00a6y\3\2\2\2\u00a6|\3\2\2\2\u00a6\177\3\2\2"+
		"\2\u00a6\u0082\3\2\2\2\u00a6\u0085\3\2\2\2\u00a6\u0088\3\2\2\2\u00a6\u008b"+
		"\3\2\2\2\u00a6\u008e\3\2\2\2\u00a6\u0091\3\2\2\2\u00a6\u0094\3\2\2\2\u00a6"+
		"\u0097\3\2\2\2\u00a6\u009a\3\2\2\2\u00a6\u009d\3\2\2\2\u00a6\u00a0\3\2"+
		"\2\2\u00a6\u00a3\3\2\2\2\u00a7\5\3\2\2\2\u00a8\u00a9\7-\2\2\u00a9\u00b7"+
		"\b\4\1\2\u00aa\u00ab\7\3\2\2\u00ab\u00ac\7-\2\2\u00ac\u00b7\b\4\1\2\u00ad"+
		"\u00ae\7-\2\2\u00ae\u00af\7,\2\2\u00af\u00b0\7-\2\2\u00b0\u00b7\b\4\1"+
		"\2\u00b1\u00b2\7\3\2\2\u00b2\u00b3\7-\2\2\u00b3\u00b4\7,\2\2\u00b4\u00b5"+
		"\7-\2\2\u00b5\u00b7\b\4\1\2\u00b6\u00a8\3\2\2\2\u00b6\u00aa\3\2\2\2\u00b6"+
		"\u00ad\3\2\2\2\u00b6\u00b1\3\2\2\2\u00b7\7\3\2\2\2\u00b8\u00b9\7\4\2\2"+
		"\u00b9\u00ba\7\5\2\2\u00ba\u00bb\5\4\3\2\u00bb\u00bf\b\5\1\2\u00bc\u00bd"+
		"\5\4\3\2\u00bd\u00be\b\5\1\2\u00be\u00c0\3\2\2\2\u00bf\u00bc\3\2\2\2\u00c0"+
		"\u00c1\3\2\2\2\u00c1\u00bf\3\2\2\2\u00c1\u00c2\3\2\2\2\u00c2\u00c3\3\2"+
		"\2\2\u00c3\u00c4\7\6\2\2\u00c4\u00c5\b\5\1\2\u00c5\t\3\2\2\2\u00c6\u00c7"+
		"\7\4\2\2\u00c7\u00c8\7\3\2\2\u00c8\u00c9\5\4\3\2\u00c9\u00cd\b\6\1\2\u00ca"+
		"\u00cb\5\4\3\2\u00cb\u00cc\b\6\1\2\u00cc\u00ce\3\2\2\2\u00cd\u00ca\3\2"+
		"\2\2\u00ce\u00cf\3\2\2\2\u00cf\u00cd\3\2\2\2\u00cf\u00d0\3\2\2\2\u00d0"+
		"\u00d1\3\2\2\2\u00d1\u00d2\7\6\2\2\u00d2\u00d3\b\6\1\2\u00d3\13\3\2\2"+
		"\2\u00d4\u00d5\7\4\2\2\u00d5\u00d6\7\7\2\2\u00d6\u00d7\5\4\3\2\u00d7\u00db"+
		"\b\7\1\2\u00d8\u00d9\5\4\3\2\u00d9\u00da\b\7\1\2\u00da\u00dc\3\2\2\2\u00db"+
		"\u00d8\3\2\2\2\u00dc\u00dd\3\2\2\2\u00dd\u00db\3\2\2\2\u00dd\u00de\3\2"+
		"\2\2\u00de\u00df\3\2\2\2\u00df\u00e0\7\6\2\2\u00e0\u00e1\b\7\1\2\u00e1"+
		"\r\3\2\2\2\u00e2\u00e3\7\4\2\2\u00e3\u00e4\7\b\2\2\u00e4\u00e5\5\4\3\2"+
		"\u00e5\u00e9\b\b\1\2\u00e6\u00e7\5\4\3\2\u00e7\u00e8\b\b\1\2\u00e8\u00ea"+
		"\3\2\2\2\u00e9\u00e6\3\2\2\2\u00ea\u00eb\3\2\2\2\u00eb\u00e9\3\2\2\2\u00eb"+
		"\u00ec\3\2\2\2\u00ec\u00ed\3\2\2\2\u00ed\u00ee\7\6\2\2\u00ee\u00ef\b\b"+
		"\1\2\u00ef\17\3\2\2\2\u00f0\u00f1\7.\2\2\u00f1\u00f2\b\t\1\2\u00f2\21"+
		"\3\2\2\2\u00f3\u00f4\7\4\2\2\u00f4\u00f5\7\23\2\2\u00f5\u00fe\7\4\2\2"+
		"\u00f6\u00f7\7\4\2\2\u00f7\u00f8\7.\2\2\u00f8\u00f9\7\t\2\2\u00f9\u00fa"+
		"\5:\36\2\u00fa\u00fb\5\4\3\2\u00fb\u00fc\7\6\2\2\u00fc\u00fd\b\n\1\2\u00fd"+
		"\u00ff\3\2\2\2\u00fe\u00f6\3\2\2\2\u00ff\u0100\3\2\2\2\u0100\u00fe\3\2"+
		"\2\2\u0100\u0101\3\2\2\2\u0101\u0102\3\2\2\2\u0102\u0103\7\6\2\2\u0103"+
		"\u0104\5\4\3\2\u0104\u0105\7\6\2\2\u0105\u0106\b\n\1\2\u0106\23\3\2\2"+
		"\2\u0107\u0108\7\4\2\2\u0108\u0109\7\22\2\2\u0109\u010a\7.\2\2\u010a\u010b"+
		"\7\t\2\2\u010b\u010c\5:\36\2\u010c\u010d\5\4\3\2\u010d\u010e\7\6\2\2\u010e"+
		"\u010f\b\13\1\2\u010f\25\3\2\2\2\u0110\u0111\7\4\2\2\u0111\u0112\7\27"+
		"\2\2\u0112\u0113\5\4\3\2\u0113\u0114\7\6\2\2\u0114\u0115\b\f\1\2\u0115"+
		"\27\3\2\2\2\u0116\u0117\7\4\2\2\u0117\u0118\7\30\2\2\u0118\u0119\5\4\3"+
		"\2\u0119\u011a\7\6\2\2\u011a\u011b\b\r\1\2\u011b\31\3\2\2\2\u011c\u011d"+
		"\7\4\2\2\u011d\u011e\7\31\2\2\u011e\u011f\5\4\3\2\u011f\u0120\5\4\3\2"+
		"\u0120\u0121\7\6\2\2\u0121\u0122\b\16\1\2\u0122\33\3\2\2\2\u0123\u0124"+
		"\7\4\2\2\u0124\u0125\7\32\2\2\u0125\u0126\7\t\2\2\u0126\u012c\5:\36\2"+
		"\u0127\u0128\5\4\3\2\u0128\u0129\b\17\1\2\u0129\u012b\3\2\2\2\u012a\u0127"+
		"\3\2\2\2\u012b\u012e\3\2\2\2\u012c\u012a\3\2\2\2\u012c\u012d\3\2\2\2\u012d"+
		"\u012f\3\2\2\2\u012e\u012c\3\2\2\2\u012f\u0130\7\6\2\2\u0130\u0131\b\17"+
		"\1\2\u0131\35\3\2\2\2\u0132\u0133\7\4\2\2\u0133\u0134\7\33\2\2\u0134\u0135"+
		"\5\4\3\2\u0135\u0136\7\6\2\2\u0136\u0137\b\20\1\2\u0137\37\3\2\2\2\u0138"+
		"\u0139\7\61\2\2\u0139\u013a\b\21\1\2\u013a!\3\2\2\2\u013b\u013c\7\37\2"+
		"\2\u013c\u0140\b\22\1\2\u013d\u013e\7 \2\2\u013e\u0140\b\22\1\2\u013f"+
		"\u013b\3\2\2\2\u013f\u013d\3\2\2\2\u0140#\3\2\2\2\u0141\u0142\7\4\2\2"+
		"\u0142\u0143\7\25\2\2\u0143\u014b\7\4\2\2\u0144\u0145\7.\2\2\u0145\u0146"+
		"\7\t\2\2\u0146\u0147\5:\36\2\u0147\u0148\b\23\1\2\u0148\u014a\3\2\2\2"+
		"\u0149\u0144\3\2\2\2\u014a\u014d\3\2\2\2\u014b\u0149\3\2\2\2\u014b\u014c"+
		"\3\2\2\2\u014c\u014e\3\2\2\2\u014d\u014b\3\2\2\2\u014e\u014f\7\6\2\2\u014f"+
		"\u0150\5\4\3\2\u0150\u0151\7\6\2\2\u0151\u0152\b\23\1\2\u0152%\3\2\2\2"+
		"\u0153\u0154\7\4\2\2\u0154\u015a\5\4\3\2\u0155\u0156\5\4\3\2\u0156\u0157"+
		"\b\24\1\2\u0157\u0159\3\2\2\2\u0158\u0155\3\2\2\2\u0159\u015c\3\2\2\2"+
		"\u015a\u0158\3\2\2\2\u015a\u015b\3\2\2\2\u015b\u015d\3\2\2\2\u015c\u015a"+
		"\3\2\2\2\u015d\u015e\7\6\2\2\u015e\u015f\b\24\1\2\u015f\'\3\2\2\2\u0160"+
		"\u0161\7\4\2\2\u0161\u0162\7\26\2\2\u0162\u0163\5\4\3\2\u0163\u0164\5"+
		"\4\3\2\u0164\u0165\5\4\3\2\u0165\u0166\7\6\2\2\u0166\u0167\b\25\1\2\u0167"+
		")\3\2\2\2\u0168\u0169\7\4\2\2\u0169\u016a\7\34\2\2\u016a\u016b\5\4\3\2"+
		"\u016b\u016c\5\4\3\2\u016c\u016d\7\6\2\2\u016d\u016e\b\26\1\2\u016e+\3"+
		"\2\2\2\u016f\u0170\7\4\2\2\u0170\u0171\7\35\2\2\u0171\u0172\5\4\3\2\u0172"+
		"\u0173\5\4\3\2\u0173\u0174\7\6\2\2\u0174\u0175\b\27\1\2\u0175-\3\2\2\2"+
		"\u0176\u0177\7\4\2\2\u0177\u0178\7\36\2\2\u0178\u0179\5\4\3\2\u0179\u017a"+
		"\5\4\3\2\u017a\u017b\7\6\2\2\u017b\u017c\b\30\1\2\u017c/\3\2\2\2\u017d"+
		"\u017e\7\4\2\2\u017e\u017f\7\24\2\2\u017f\u0188\7\4\2\2\u0180\u0181\7"+
		"\4\2\2\u0181\u0182\7.\2\2\u0182\u0183\7\t\2\2\u0183\u0184\5:\36\2\u0184"+
		"\u0185\5\4\3\2\u0185\u0186\7\6\2\2\u0186\u0187\b\31\1\2\u0187\u0189\3"+
		"\2\2\2\u0188\u0180\3\2\2\2\u0189\u018a\3\2\2\2\u018a\u0188\3\2\2\2\u018a"+
		"\u018b\3\2\2\2\u018b\u018c\3\2\2\2\u018c\u018d\7\6\2\2\u018d\u018e\5\4"+
		"\3\2\u018e\u018f\7\6\2\2\u018f\u0190\b\31\1\2\u0190\61\3\2\2\2\u0191\u0192"+
		"\7\4\2\2\u0192\u0193\7!\2\2\u0193\u0194\7\t\2\2\u0194\u0195\5:\36\2\u0195"+
		"\u0196\5\4\3\2\u0196\u0197\7\6\2\2\u0197\u0198\b\32\1\2\u0198\63\3\2\2"+
		"\2\u0199\u019a\7\4\2\2\u019a\u019b\7\"\2\2\u019b\u019c\5\4\3\2\u019c\u019d"+
		"\7\6\2\2\u019d\u019e\b\33\1\2\u019e\65\3\2\2\2\u019f\u01a0\7\4\2\2\u01a0"+
		"\u01a1\7#\2\2\u01a1\u01a2\5\4\3\2\u01a2\u01a3\5\4\3\2\u01a3\u01a4\7\6"+
		"\2\2\u01a4\u01a5\b\34\1\2\u01a5\67\3\2\2\2\u01a6\u01a7\7\4\2\2\u01a7\u01a8"+
		"\7$\2\2\u01a8\u01a9\5\4\3\2\u01a9\u01aa\7\6\2\2\u01aa\u01ab\b\35\1\2\u01ab"+
		"9\3\2\2\2\u01ac\u01ad\5<\37\2\u01ad\u01ae\b\36\1\2\u01ae\u01c5\3\2\2\2"+
		"\u01af\u01b0\5J&\2\u01b0\u01b1\b\36\1\2\u01b1\u01c5\3\2\2\2\u01b2\u01b3"+
		"\5@!\2\u01b3\u01b4\b\36\1\2\u01b4\u01c5\3\2\2\2\u01b5\u01b6\5B\"\2\u01b6"+
		"\u01b7\b\36\1\2\u01b7\u01c5\3\2\2\2\u01b8\u01b9\5D#\2\u01b9\u01ba\b\36"+
		"\1\2\u01ba\u01c5\3\2\2\2\u01bb\u01bc\5H%\2\u01bc\u01bd\b\36\1\2\u01bd"+
		"\u01c5\3\2\2\2\u01be\u01bf\5F$\2\u01bf\u01c0\b\36\1\2\u01c0\u01c5\3\2"+
		"\2\2\u01c1\u01c2\5> \2\u01c2\u01c3\b\36\1\2\u01c3\u01c5\3\2\2\2\u01c4"+
		"\u01ac\3\2\2\2\u01c4\u01af\3\2\2\2\u01c4\u01b2\3\2\2\2\u01c4\u01b5\3\2"+
		"\2\2\u01c4\u01b8\3\2\2\2\u01c4\u01bb\3\2\2\2\u01c4\u01be\3\2\2\2\u01c4"+
		"\u01c1\3\2\2\2\u01c5;\3\2\2\2\u01c6\u01c7\7\n\2\2\u01c7\u01c8\b\37\1\2"+
		"\u01c8=\3\2\2\2\u01c9\u01ca\7\13\2\2\u01ca\u01cb\b \1\2\u01cb?\3\2\2\2"+
		"\u01cc\u01cd\7\f\2\2\u01cd\u01ce\b!\1\2\u01ceA\3\2\2\2\u01cf\u01d0\7\r"+
		"\2\2\u01d0\u01d1\5:\36\2\u01d1\u01d2\7\36\2\2\u01d2\u01d3\b\"\1\2\u01d3"+
		"C\3\2\2\2\u01d4\u01d5\7\4\2\2\u01d5\u01d6\5:\36\2\u01d6\u01d7\7\16\2\2"+
		"\u01d7\u01d8\5:\36\2\u01d8\u01d9\7\6\2\2\u01d9\u01da\b#\1\2\u01daE\3\2"+
		"\2\2\u01db\u01dc\7\17\2\2\u01dc\u01dd\5:\36\2\u01dd\u01de\b$\1\2\u01de"+
		"G\3\2\2\2\u01df\u01e0\7\20\2\2\u01e0\u01e1\b%\1\2\u01e1I\3\2\2\2\u01e2"+
		"\u01e8\7\4\2\2\u01e3\u01e4\5:\36\2\u01e4\u01e5\b&\1\2\u01e5\u01e7\3\2"+
		"\2\2\u01e6\u01e3\3\2\2\2\u01e7\u01ea\3\2\2\2\u01e8\u01e6\3\2\2\2\u01e8"+
		"\u01e9\3\2\2\2\u01e9\u01eb\3\2\2\2\u01ea\u01e8\3\2\2\2\u01eb\u01ec\7\21"+
		"\2\2\u01ec\u01ed\5:\36\2\u01ed\u01ee\7\6\2\2\u01ee\u01ef\b&\1\2\u01ef"+
		"K\3\2\2\2\22QW\u00a6\u00b6\u00c1\u00cf\u00dd\u00eb\u0100\u012c\u013f\u014b"+
		"\u015a\u018a\u01c4\u01e8";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}