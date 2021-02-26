// Generated from varlang/parser/VarLang.g by ANTLR 4.5
package varlang.parser; import static varlang.AST.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class VarLangParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.5", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, Define=7, Let=8, Dot=9, 
		Number=10, Identifier=11, Letter=12, LetterOrDigit=13, AT=14, ELLIPSIS=15, 
		WS=16, Comment=17, Line_Comment=18;
	public static final int
		RULE_exp = 0, RULE_varexp = 1, RULE_letexp = 2, RULE_defineexp = 3, RULE_program = 4, 
		RULE_numexp = 5, RULE_addexp = 6, RULE_subexp = 7, RULE_multexp = 8, RULE_divexp = 9;
	public static final String[] ruleNames = {
		"exp", "varexp", "letexp", "defineexp", "program", "numexp", "addexp", 
		"subexp", "multexp", "divexp"
	};

	private static final String[] _LITERAL_NAMES = {
		null, "'('", "')'", "'-'", "'+'", "'*'", "'/'", "'define'", "'let'", "'.'", 
		null, null, null, null, "'@'", "'...'"
	};
	private static final String[] _SYMBOLIC_NAMES = {
		null, null, null, null, null, null, null, "Define", "Let", "Dot", "Number", 
		"Identifier", "Letter", "LetterOrDigit", "AT", "ELLIPSIS", "WS", "Comment", 
		"Line_Comment"
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
	public String getGrammarFileName() { return "VarLang.g"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public VarLangParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}
	public static class ExpContext extends ParserRuleContext {
		public Exp ast;
		public VarexpContext v;
		public NumexpContext n;
		public AddexpContext a;
		public SubexpContext s;
		public MultexpContext m;
		public DivexpContext d;
		public LetexpContext l;
		public DefineexpContext de;
		public VarexpContext varexp() {
			return getRuleContext(VarexpContext.class,0);
		}
		public NumexpContext numexp() {
			return getRuleContext(NumexpContext.class,0);
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
		public DefineexpContext defineexp() {
			return getRuleContext(DefineexpContext.class,0);
		}
		public ExpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_exp; }
	}

	public final ExpContext exp() throws RecognitionException {
		ExpContext _localctx = new ExpContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_exp);
		try {
			setState(44);
			switch ( getInterpreter().adaptivePredict(_input,0,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(20);
				((ExpContext)_localctx).v = varexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).v.ast; 
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(23);
				((ExpContext)_localctx).n = numexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).n.ast; 
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(26);
				((ExpContext)_localctx).a = addexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).a.ast; 
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(29);
				((ExpContext)_localctx).s = subexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).s.ast; 
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(32);
				((ExpContext)_localctx).m = multexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).m.ast; 
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(35);
				((ExpContext)_localctx).d = divexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).d.ast; 
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(38);
				((ExpContext)_localctx).l = letexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).l.ast; 
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(41);
				((ExpContext)_localctx).de = defineexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).de.ast; 
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

	public static class VarexpContext extends ParserRuleContext {
		public VarExp ast;
		public Token id;
		public TerminalNode Identifier() { return getToken(VarLangParser.Identifier, 0); }
		public VarexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_varexp; }
	}

	public final VarexpContext varexp() throws RecognitionException {
		VarexpContext _localctx = new VarexpContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_varexp);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(46);
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
		public ArrayList<Exp> value_exps;
		public Token id;
		public ExpContext e;
		public ExpContext body;
		public TerminalNode Let() { return getToken(VarLangParser.Let, 0); }
		public List<ExpContext> exp() {
			return getRuleContexts(ExpContext.class);
		}
		public ExpContext exp(int i) {
			return getRuleContext(ExpContext.class,i);
		}
		public List<TerminalNode> Identifier() { return getTokens(VarLangParser.Identifier); }
		public TerminalNode Identifier(int i) {
			return getToken(VarLangParser.Identifier, i);
		}
		public LetexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_letexp; }
	}

	public final LetexpContext letexp() throws RecognitionException {
		LetexpContext _localctx = new LetexpContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_letexp);
		 ((LetexpContext)_localctx).names =  new ArrayList<String>(); ((LetexpContext)_localctx).value_exps =  new ArrayList<Exp>(); 
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(49);
			match(T__0);
			setState(50);
			match(Let);
			setState(51);
			match(T__0);
			setState(58); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(52);
				match(T__0);
				setState(53);
				((LetexpContext)_localctx).id = match(Identifier);
				setState(54);
				((LetexpContext)_localctx).e = exp();
				setState(55);
				match(T__1);
				 _localctx.names.add((((LetexpContext)_localctx).id!=null?((LetexpContext)_localctx).id.getText():null)); _localctx.value_exps.add(((LetexpContext)_localctx).e.ast); 
				}
				}
				setState(60); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==T__0 );
			setState(62);
			match(T__1);
			setState(63);
			((LetexpContext)_localctx).body = exp();
			setState(64);
			match(T__1);
			 ((LetexpContext)_localctx).ast =  new LetExp(_localctx.names, _localctx.value_exps, ((LetexpContext)_localctx).body.ast); 
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

	public static class DefineexpContext extends ParserRuleContext {
		public DefineExp ast;
		public ArrayList<String> names;
		public ArrayList<Exp> value_exps;
		public Token id;
		public ExpContext e;
		public ExpContext body;
		public TerminalNode Define() { return getToken(VarLangParser.Define, 0); }
		public List<ExpContext> exp() {
			return getRuleContexts(ExpContext.class);
		}
		public ExpContext exp(int i) {
			return getRuleContext(ExpContext.class,i);
		}
		public List<TerminalNode> Identifier() { return getTokens(VarLangParser.Identifier); }
		public TerminalNode Identifier(int i) {
			return getToken(VarLangParser.Identifier, i);
		}
		public DefineexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_defineexp; }
	}

	public final DefineexpContext defineexp() throws RecognitionException {
		DefineexpContext _localctx = new DefineexpContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_defineexp);
		 ((DefineexpContext)_localctx).names =  new ArrayList<String>(); ((DefineexpContext)_localctx).value_exps =  new ArrayList<Exp>(); 
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(67);
			match(T__0);
			setState(68);
			match(Define);
			setState(69);
			match(T__0);
			setState(76); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(70);
				match(T__0);
				setState(71);
				((DefineexpContext)_localctx).id = match(Identifier);
				setState(72);
				((DefineexpContext)_localctx).e = exp();
				setState(73);
				match(T__1);
				 _localctx.names.add((((DefineexpContext)_localctx).id!=null?((DefineexpContext)_localctx).id.getText():null)); _localctx.value_exps.add(((DefineexpContext)_localctx).e.ast); 
				}
				}
				setState(78); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==T__0 );
			setState(80);
			match(T__1);
			setState(81);
			((DefineexpContext)_localctx).body = exp();
			setState(82);
			match(T__1);
			 ((DefineexpContext)_localctx).ast =  new DefineExp(_localctx.names, _localctx.value_exps, ((DefineexpContext)_localctx).body.ast); 
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

	public static class ProgramContext extends ParserRuleContext {
		public Program ast;
		public ExpContext e;
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
		enterRule(_localctx, 8, RULE_program);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(85);
			((ProgramContext)_localctx).e = exp();
			 ((ProgramContext)_localctx).ast =  new Program(((ProgramContext)_localctx).e.ast); 
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
		public List<TerminalNode> Number() { return getTokens(VarLangParser.Number); }
		public TerminalNode Number(int i) {
			return getToken(VarLangParser.Number, i);
		}
		public TerminalNode Dot() { return getToken(VarLangParser.Dot, 0); }
		public NumexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_numexp; }
	}

	public final NumexpContext numexp() throws RecognitionException {
		NumexpContext _localctx = new NumexpContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_numexp);
		try {
			setState(102);
			switch ( getInterpreter().adaptivePredict(_input,3,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(88);
				((NumexpContext)_localctx).n0 = match(Number);
				 ((NumexpContext)_localctx).ast =  new NumExp(Integer.parseInt((((NumexpContext)_localctx).n0!=null?((NumexpContext)_localctx).n0.getText():null))); 
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(90);
				match(T__2);
				setState(91);
				((NumexpContext)_localctx).n0 = match(Number);
				 ((NumexpContext)_localctx).ast =  new NumExp(-Integer.parseInt((((NumexpContext)_localctx).n0!=null?((NumexpContext)_localctx).n0.getText():null))); 
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(93);
				((NumexpContext)_localctx).n0 = match(Number);
				setState(94);
				match(Dot);
				setState(95);
				((NumexpContext)_localctx).n1 = match(Number);
				 ((NumexpContext)_localctx).ast =  new NumExp(Double.parseDouble((((NumexpContext)_localctx).n0!=null?((NumexpContext)_localctx).n0.getText():null)+"."+(((NumexpContext)_localctx).n1!=null?((NumexpContext)_localctx).n1.getText():null))); 
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(97);
				match(T__2);
				setState(98);
				((NumexpContext)_localctx).n0 = match(Number);
				setState(99);
				match(Dot);
				setState(100);
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
		enterRule(_localctx, 12, RULE_addexp);
		 ((AddexpContext)_localctx).list =  new ArrayList<Exp>(); 
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(104);
			match(T__0);
			setState(105);
			match(T__3);
			setState(106);
			((AddexpContext)_localctx).e = exp();
			 _localctx.list.add(((AddexpContext)_localctx).e.ast); 
			setState(111); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(108);
				((AddexpContext)_localctx).e = exp();
				 _localctx.list.add(((AddexpContext)_localctx).e.ast); 
				}
				}
				setState(113); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__0) | (1L << T__2) | (1L << Number) | (1L << Identifier))) != 0) );
			setState(115);
			match(T__1);
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
		enterRule(_localctx, 14, RULE_subexp);
		 ((SubexpContext)_localctx).list =  new ArrayList<Exp>(); 
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(118);
			match(T__0);
			setState(119);
			match(T__2);
			setState(120);
			((SubexpContext)_localctx).e = exp();
			 _localctx.list.add(((SubexpContext)_localctx).e.ast); 
			setState(125); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(122);
				((SubexpContext)_localctx).e = exp();
				 _localctx.list.add(((SubexpContext)_localctx).e.ast); 
				}
				}
				setState(127); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__0) | (1L << T__2) | (1L << Number) | (1L << Identifier))) != 0) );
			setState(129);
			match(T__1);
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
		enterRule(_localctx, 16, RULE_multexp);
		 ((MultexpContext)_localctx).list =  new ArrayList<Exp>(); 
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(132);
			match(T__0);
			setState(133);
			match(T__4);
			setState(134);
			((MultexpContext)_localctx).e = exp();
			 _localctx.list.add(((MultexpContext)_localctx).e.ast); 
			setState(139); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(136);
				((MultexpContext)_localctx).e = exp();
				 _localctx.list.add(((MultexpContext)_localctx).e.ast); 
				}
				}
				setState(141); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__0) | (1L << T__2) | (1L << Number) | (1L << Identifier))) != 0) );
			setState(143);
			match(T__1);
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
		enterRule(_localctx, 18, RULE_divexp);
		 ((DivexpContext)_localctx).list =  new ArrayList<Exp>(); 
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(146);
			match(T__0);
			setState(147);
			match(T__5);
			setState(148);
			((DivexpContext)_localctx).e = exp();
			 _localctx.list.add(((DivexpContext)_localctx).e.ast); 
			setState(153); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(150);
				((DivexpContext)_localctx).e = exp();
				 _localctx.list.add(((DivexpContext)_localctx).e.ast); 
				}
				}
				setState(155); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__0) | (1L << T__2) | (1L << Number) | (1L << Identifier))) != 0) );
			setState(157);
			match(T__1);
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

	public static final String _serializedATN =
		"\3\u0430\ud6d1\u8206\uad2d\u4417\uaef1\u8d80\uaadd\3\24\u00a3\4\2\t\2"+
		"\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13"+
		"\t\13\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2"+
		"\3\2\3\2\3\2\3\2\3\2\3\2\3\2\3\2\5\2/\n\2\3\3\3\3\3\3\3\4\3\4\3\4\3\4"+
		"\3\4\3\4\3\4\3\4\3\4\6\4=\n\4\r\4\16\4>\3\4\3\4\3\4\3\4\3\4\3\5\3\5\3"+
		"\5\3\5\3\5\3\5\3\5\3\5\3\5\6\5O\n\5\r\5\16\5P\3\5\3\5\3\5\3\5\3\5\3\6"+
		"\3\6\3\6\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\3\7\5\7i"+
		"\n\7\3\b\3\b\3\b\3\b\3\b\3\b\3\b\6\br\n\b\r\b\16\bs\3\b\3\b\3\b\3\t\3"+
		"\t\3\t\3\t\3\t\3\t\3\t\6\t\u0080\n\t\r\t\16\t\u0081\3\t\3\t\3\t\3\n\3"+
		"\n\3\n\3\n\3\n\3\n\3\n\6\n\u008e\n\n\r\n\16\n\u008f\3\n\3\n\3\n\3\13\3"+
		"\13\3\13\3\13\3\13\3\13\3\13\6\13\u009c\n\13\r\13\16\13\u009d\3\13\3\13"+
		"\3\13\3\13\2\2\f\2\4\6\b\n\f\16\20\22\24\2\2\u00a8\2.\3\2\2\2\4\60\3\2"+
		"\2\2\6\63\3\2\2\2\bE\3\2\2\2\nW\3\2\2\2\fh\3\2\2\2\16j\3\2\2\2\20x\3\2"+
		"\2\2\22\u0086\3\2\2\2\24\u0094\3\2\2\2\26\27\5\4\3\2\27\30\b\2\1\2\30"+
		"/\3\2\2\2\31\32\5\f\7\2\32\33\b\2\1\2\33/\3\2\2\2\34\35\5\16\b\2\35\36"+
		"\b\2\1\2\36/\3\2\2\2\37 \5\20\t\2 !\b\2\1\2!/\3\2\2\2\"#\5\22\n\2#$\b"+
		"\2\1\2$/\3\2\2\2%&\5\24\13\2&\'\b\2\1\2\'/\3\2\2\2()\5\6\4\2)*\b\2\1\2"+
		"*/\3\2\2\2+,\5\b\5\2,-\b\2\1\2-/\3\2\2\2.\26\3\2\2\2.\31\3\2\2\2.\34\3"+
		"\2\2\2.\37\3\2\2\2.\"\3\2\2\2.%\3\2\2\2.(\3\2\2\2.+\3\2\2\2/\3\3\2\2\2"+
		"\60\61\7\r\2\2\61\62\b\3\1\2\62\5\3\2\2\2\63\64\7\3\2\2\64\65\7\n\2\2"+
		"\65<\7\3\2\2\66\67\7\3\2\2\678\7\r\2\289\5\2\2\29:\7\4\2\2:;\b\4\1\2;"+
		"=\3\2\2\2<\66\3\2\2\2=>\3\2\2\2><\3\2\2\2>?\3\2\2\2?@\3\2\2\2@A\7\4\2"+
		"\2AB\5\2\2\2BC\7\4\2\2CD\b\4\1\2D\7\3\2\2\2EF\7\3\2\2FG\7\t\2\2GN\7\3"+
		"\2\2HI\7\3\2\2IJ\7\r\2\2JK\5\2\2\2KL\7\4\2\2LM\b\5\1\2MO\3\2\2\2NH\3\2"+
		"\2\2OP\3\2\2\2PN\3\2\2\2PQ\3\2\2\2QR\3\2\2\2RS\7\4\2\2ST\5\2\2\2TU\7\4"+
		"\2\2UV\b\5\1\2V\t\3\2\2\2WX\5\2\2\2XY\b\6\1\2Y\13\3\2\2\2Z[\7\f\2\2[i"+
		"\b\7\1\2\\]\7\5\2\2]^\7\f\2\2^i\b\7\1\2_`\7\f\2\2`a\7\13\2\2ab\7\f\2\2"+
		"bi\b\7\1\2cd\7\5\2\2de\7\f\2\2ef\7\13\2\2fg\7\f\2\2gi\b\7\1\2hZ\3\2\2"+
		"\2h\\\3\2\2\2h_\3\2\2\2hc\3\2\2\2i\r\3\2\2\2jk\7\3\2\2kl\7\6\2\2lm\5\2"+
		"\2\2mq\b\b\1\2no\5\2\2\2op\b\b\1\2pr\3\2\2\2qn\3\2\2\2rs\3\2\2\2sq\3\2"+
		"\2\2st\3\2\2\2tu\3\2\2\2uv\7\4\2\2vw\b\b\1\2w\17\3\2\2\2xy\7\3\2\2yz\7"+
		"\5\2\2z{\5\2\2\2{\177\b\t\1\2|}\5\2\2\2}~\b\t\1\2~\u0080\3\2\2\2\177|"+
		"\3\2\2\2\u0080\u0081\3\2\2\2\u0081\177\3\2\2\2\u0081\u0082\3\2\2\2\u0082"+
		"\u0083\3\2\2\2\u0083\u0084\7\4\2\2\u0084\u0085\b\t\1\2\u0085\21\3\2\2"+
		"\2\u0086\u0087\7\3\2\2\u0087\u0088\7\7\2\2\u0088\u0089\5\2\2\2\u0089\u008d"+
		"\b\n\1\2\u008a\u008b\5\2\2\2\u008b\u008c\b\n\1\2\u008c\u008e\3\2\2\2\u008d"+
		"\u008a\3\2\2\2\u008e\u008f\3\2\2\2\u008f\u008d\3\2\2\2\u008f\u0090\3\2"+
		"\2\2\u0090\u0091\3\2\2\2\u0091\u0092\7\4\2\2\u0092\u0093\b\n\1\2\u0093"+
		"\23\3\2\2\2\u0094\u0095\7\3\2\2\u0095\u0096\7\b\2\2\u0096\u0097\5\2\2"+
		"\2\u0097\u009b\b\13\1\2\u0098\u0099\5\2\2\2\u0099\u009a\b\13\1\2\u009a"+
		"\u009c\3\2\2\2\u009b\u0098\3\2\2\2\u009c\u009d\3\2\2\2\u009d\u009b\3\2"+
		"\2\2\u009d\u009e\3\2\2\2\u009e\u009f\3\2\2\2\u009f\u00a0\7\4\2\2\u00a0"+
		"\u00a1\b\13\1\2\u00a1\25\3\2\2\2\n.>Phs\u0081\u008f\u009d";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}