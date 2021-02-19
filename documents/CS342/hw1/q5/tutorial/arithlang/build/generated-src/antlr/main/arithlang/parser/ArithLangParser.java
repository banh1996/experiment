// Generated from arithlang/parser/ArithLang.g by ANTLR 4.5
package arithlang.parser; import static arithlang.AST.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class ArithLangParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.5", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, Define=5, Let=6, Dot=7, Number=8, Identifier=9, 
		Letter=10, LetterOrDigit=11, AT=12, ELLIPSIS=13, WS=14, Comment=15, Line_Comment=16;
	public static final int
		RULE_program = 0, RULE_exp = 1, RULE_numexp = 2, RULE_pexp = 3, RULE_addexp = 4, 
		RULE_subexp = 5;
	public static final String[] ruleNames = {
		"program", "exp", "numexp", "pexp", "addexp", "subexp"
	};

	private static final String[] _LITERAL_NAMES = {
		null, "'-'", "'('", "'+'", "')'", "'define'", "'let'", "'.'", null, null, 
		null, null, "'@'", "'...'"
	};
	private static final String[] _SYMBOLIC_NAMES = {
		null, null, null, null, null, "Define", "Let", "Dot", "Number", "Identifier", 
		"Letter", "LetterOrDigit", "AT", "ELLIPSIS", "WS", "Comment", "Line_Comment"
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
	public String getGrammarFileName() { return "ArithLang.g"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public ArithLangParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
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
		enterRule(_localctx, 0, RULE_program);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(12);
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

	public static class ExpContext extends ParserRuleContext {
		public Exp ast;
		public NumexpContext n;
		public PexpContext p;
		public AddexpContext a;
		public SubexpContext s;
		public NumexpContext numexp() {
			return getRuleContext(NumexpContext.class,0);
		}
		public PexpContext pexp() {
			return getRuleContext(PexpContext.class,0);
		}
		public AddexpContext addexp() {
			return getRuleContext(AddexpContext.class,0);
		}
		public SubexpContext subexp() {
			return getRuleContext(SubexpContext.class,0);
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
			setState(27);
			switch ( getInterpreter().adaptivePredict(_input,0,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(15);
				((ExpContext)_localctx).n = numexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).n.ast; 
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(18);
				((ExpContext)_localctx).p = pexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).p.ast; 
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(21);
				((ExpContext)_localctx).a = addexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).a.ast; 
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(24);
				((ExpContext)_localctx).s = subexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).s.ast; 
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
		public List<TerminalNode> Number() { return getTokens(ArithLangParser.Number); }
		public TerminalNode Number(int i) {
			return getToken(ArithLangParser.Number, i);
		}
		public TerminalNode Dot() { return getToken(ArithLangParser.Dot, 0); }
		public NumexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_numexp; }
	}

	public final NumexpContext numexp() throws RecognitionException {
		NumexpContext _localctx = new NumexpContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_numexp);
		try {
			setState(43);
			switch ( getInterpreter().adaptivePredict(_input,1,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(29);
				((NumexpContext)_localctx).n0 = match(Number);
				 ((NumexpContext)_localctx).ast =  new NumExp(Integer.parseInt((((NumexpContext)_localctx).n0!=null?((NumexpContext)_localctx).n0.getText():null))); 
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(31);
				match(T__0);
				setState(32);
				((NumexpContext)_localctx).n0 = match(Number);
				 ((NumexpContext)_localctx).ast =  new NumExp(-Integer.parseInt((((NumexpContext)_localctx).n0!=null?((NumexpContext)_localctx).n0.getText():null))); 
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(34);
				((NumexpContext)_localctx).n0 = match(Number);
				setState(35);
				match(Dot);
				setState(36);
				((NumexpContext)_localctx).n1 = match(Number);
				 ((NumexpContext)_localctx).ast =  new NumExp(Double.parseDouble((((NumexpContext)_localctx).n0!=null?((NumexpContext)_localctx).n0.getText():null)+"."+(((NumexpContext)_localctx).n1!=null?((NumexpContext)_localctx).n1.getText():null))); 
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(38);
				match(T__0);
				setState(39);
				((NumexpContext)_localctx).n0 = match(Number);
				setState(40);
				match(Dot);
				setState(41);
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

	public static class PexpContext extends ParserRuleContext {
		public pExp ast;
		public Token n0;
		public TerminalNode Letter() { return getToken(ArithLangParser.Letter, 0); }
		public PexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_pexp; }
	}

	public final PexpContext pexp() throws RecognitionException {
		PexpContext _localctx = new PexpContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_pexp);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(45);
			((PexpContext)_localctx).n0 = match(Letter);
			 ((PexpContext)_localctx).ast =  new pExp((((PexpContext)_localctx).n0!=null?((PexpContext)_localctx).n0.getText():null)); 
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
		enterRule(_localctx, 8, RULE_addexp);
		 ((AddexpContext)_localctx).list =  new ArrayList<Exp>(); 
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(48);
			match(T__1);
			setState(49);
			match(T__2);
			setState(50);
			((AddexpContext)_localctx).e = exp();
			 _localctx.list.add(((AddexpContext)_localctx).e.ast); 
			setState(55); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(52);
				((AddexpContext)_localctx).e = exp();
				 _localctx.list.add(((AddexpContext)_localctx).e.ast); 
				}
				}
				setState(57); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__0) | (1L << T__1) | (1L << Number) | (1L << Letter))) != 0) );
			setState(59);
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
		enterRule(_localctx, 10, RULE_subexp);
		 ((SubexpContext)_localctx).list =  new ArrayList<Exp>(); 
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(62);
			match(T__1);
			setState(63);
			match(T__0);
			setState(64);
			((SubexpContext)_localctx).e = exp();
			 _localctx.list.add(((SubexpContext)_localctx).e.ast); 
			setState(69); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(66);
				((SubexpContext)_localctx).e = exp();
				 _localctx.list.add(((SubexpContext)_localctx).e.ast); 
				}
				}
				setState(71); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__0) | (1L << T__1) | (1L << Number) | (1L << Letter))) != 0) );
			setState(73);
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

	public static final String _serializedATN =
		"\3\u0430\ud6d1\u8206\uad2d\u4417\uaef1\u8d80\uaadd\3\22O\4\2\t\2\4\3\t"+
		"\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\3\2\3\2\3\2\3\3\3\3\3\3\3\3\3\3\3\3"+
		"\3\3\3\3\3\3\3\3\3\3\3\3\5\3\36\n\3\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3\4\3"+
		"\4\3\4\3\4\3\4\3\4\3\4\5\4.\n\4\3\5\3\5\3\5\3\6\3\6\3\6\3\6\3\6\3\6\3"+
		"\6\6\6:\n\6\r\6\16\6;\3\6\3\6\3\6\3\7\3\7\3\7\3\7\3\7\3\7\3\7\6\7H\n\7"+
		"\r\7\16\7I\3\7\3\7\3\7\3\7\2\2\b\2\4\6\b\n\f\2\2P\2\16\3\2\2\2\4\35\3"+
		"\2\2\2\6-\3\2\2\2\b/\3\2\2\2\n\62\3\2\2\2\f@\3\2\2\2\16\17\5\4\3\2\17"+
		"\20\b\2\1\2\20\3\3\2\2\2\21\22\5\6\4\2\22\23\b\3\1\2\23\36\3\2\2\2\24"+
		"\25\5\b\5\2\25\26\b\3\1\2\26\36\3\2\2\2\27\30\5\n\6\2\30\31\b\3\1\2\31"+
		"\36\3\2\2\2\32\33\5\f\7\2\33\34\b\3\1\2\34\36\3\2\2\2\35\21\3\2\2\2\35"+
		"\24\3\2\2\2\35\27\3\2\2\2\35\32\3\2\2\2\36\5\3\2\2\2\37 \7\n\2\2 .\b\4"+
		"\1\2!\"\7\3\2\2\"#\7\n\2\2#.\b\4\1\2$%\7\n\2\2%&\7\t\2\2&\'\7\n\2\2\'"+
		".\b\4\1\2()\7\3\2\2)*\7\n\2\2*+\7\t\2\2+,\7\n\2\2,.\b\4\1\2-\37\3\2\2"+
		"\2-!\3\2\2\2-$\3\2\2\2-(\3\2\2\2.\7\3\2\2\2/\60\7\f\2\2\60\61\b\5\1\2"+
		"\61\t\3\2\2\2\62\63\7\4\2\2\63\64\7\5\2\2\64\65\5\4\3\2\659\b\6\1\2\66"+
		"\67\5\4\3\2\678\b\6\1\28:\3\2\2\29\66\3\2\2\2:;\3\2\2\2;9\3\2\2\2;<\3"+
		"\2\2\2<=\3\2\2\2=>\7\6\2\2>?\b\6\1\2?\13\3\2\2\2@A\7\4\2\2AB\7\3\2\2B"+
		"C\5\4\3\2CG\b\7\1\2DE\5\4\3\2EF\b\7\1\2FH\3\2\2\2GD\3\2\2\2HI\3\2\2\2"+
		"IG\3\2\2\2IJ\3\2\2\2JK\3\2\2\2KL\7\6\2\2LM\b\7\1\2M\r\3\2\2\2\6\35-;I";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}