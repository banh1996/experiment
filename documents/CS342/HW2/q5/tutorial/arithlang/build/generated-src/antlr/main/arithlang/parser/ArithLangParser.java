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
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, Define=8, Let=9, 
		Dot=10, Number=11, Identifier=12, Letter=13, LetterOrDigit=14, AT=15, 
		ELLIPSIS=16, WS=17, Comment=18, Line_Comment=19;
	public static final int
		RULE_program = 0, RULE_exp = 1, RULE_pexp = 2, RULE_nexp = 3, RULE_uexp = 4, 
		RULE_addexp = 5, RULE_subexp = 6, RULE_pp = 7, RULE_nn = 8, RULE_uu = 9;
	public static final String[] ruleNames = {
		"program", "exp", "pexp", "nexp", "uexp", "addexp", "subexp", "pp", "nn", 
		"uu"
	};

	private static final String[] _LITERAL_NAMES = {
		null, "'('", "'+'", "')'", "'-'", "'p'", "'n'", "'u'", "'define'", "'let'", 
		"'.'", null, null, null, null, "'@'", "'...'"
	};
	private static final String[] _SYMBOLIC_NAMES = {
		null, null, null, null, null, null, null, null, "Define", "Let", "Dot", 
		"Number", "Identifier", "Letter", "LetterOrDigit", "AT", "ELLIPSIS", "WS", 
		"Comment", "Line_Comment"
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
			setState(20);
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
		public PexpContext p;
		public NexpContext n;
		public UexpContext u;
		public AddexpContext a;
		public SubexpContext s;
		public PexpContext pexp() {
			return getRuleContext(PexpContext.class,0);
		}
		public NexpContext nexp() {
			return getRuleContext(NexpContext.class,0);
		}
		public UexpContext uexp() {
			return getRuleContext(UexpContext.class,0);
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
			setState(38);
			switch ( getInterpreter().adaptivePredict(_input,0,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(23);
				((ExpContext)_localctx).p = pexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).p.ast; 
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(26);
				((ExpContext)_localctx).n = nexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).n.ast; 
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(29);
				((ExpContext)_localctx).u = uexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).u.ast; 
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(32);
				((ExpContext)_localctx).a = addexp();
				 ((ExpContext)_localctx).ast =  ((ExpContext)_localctx).a.ast; 
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(35);
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

	public static class PexpContext extends ParserRuleContext {
		public pExp ast;
		public PpContext n0;
		public PpContext pp() {
			return getRuleContext(PpContext.class,0);
		}
		public PexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_pexp; }
	}

	public final PexpContext pexp() throws RecognitionException {
		PexpContext _localctx = new PexpContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_pexp);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(40);
			((PexpContext)_localctx).n0 = pp();
			 ((PexpContext)_localctx).ast =  new pExp(((((PexpContext)_localctx).n0!=null?_input.getText(((PexpContext)_localctx).n0.start,((PexpContext)_localctx).n0.stop):null)).charAt(0)); 
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

	public static class NexpContext extends ParserRuleContext {
		public nExp ast;
		public NnContext n0;
		public NnContext nn() {
			return getRuleContext(NnContext.class,0);
		}
		public NexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_nexp; }
	}

	public final NexpContext nexp() throws RecognitionException {
		NexpContext _localctx = new NexpContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_nexp);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(43);
			((NexpContext)_localctx).n0 = nn();
			 ((NexpContext)_localctx).ast =  new nExp(((((NexpContext)_localctx).n0!=null?_input.getText(((NexpContext)_localctx).n0.start,((NexpContext)_localctx).n0.stop):null)).charAt(0)); 
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

	public static class UexpContext extends ParserRuleContext {
		public uExp ast;
		public UuContext n0;
		public UuContext uu() {
			return getRuleContext(UuContext.class,0);
		}
		public UexpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_uexp; }
	}

	public final UexpContext uexp() throws RecognitionException {
		UexpContext _localctx = new UexpContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_uexp);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(46);
			((UexpContext)_localctx).n0 = uu();
			 ((UexpContext)_localctx).ast =  new uExp(((((UexpContext)_localctx).n0!=null?_input.getText(((UexpContext)_localctx).n0.start,((UexpContext)_localctx).n0.stop):null)).charAt(0)); 
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
		enterRule(_localctx, 10, RULE_addexp);
		 ((AddexpContext)_localctx).list =  new ArrayList<Exp>(); 
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(49);
			match(T__0);
			setState(50);
			match(T__1);
			setState(51);
			((AddexpContext)_localctx).e = exp();
			 _localctx.list.add(((AddexpContext)_localctx).e.ast); 
			setState(56); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(53);
				((AddexpContext)_localctx).e = exp();
				 _localctx.list.add(((AddexpContext)_localctx).e.ast); 
				}
				}
				setState(58); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__0) | (1L << T__4) | (1L << T__5) | (1L << T__6))) != 0) );
			setState(60);
			match(T__2);
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
		enterRule(_localctx, 12, RULE_subexp);
		 ((SubexpContext)_localctx).list =  new ArrayList<Exp>(); 
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(63);
			match(T__0);
			setState(64);
			match(T__3);
			setState(65);
			((SubexpContext)_localctx).e = exp();
			 _localctx.list.add(((SubexpContext)_localctx).e.ast); 
			setState(70); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(67);
				((SubexpContext)_localctx).e = exp();
				 _localctx.list.add(((SubexpContext)_localctx).e.ast); 
				}
				}
				setState(72); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << T__0) | (1L << T__4) | (1L << T__5) | (1L << T__6))) != 0) );
			setState(74);
			match(T__2);
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

	public static class PpContext extends ParserRuleContext {
		public PpContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_pp; }
	}

	public final PpContext pp() throws RecognitionException {
		PpContext _localctx = new PpContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_pp);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(77);
			match(T__4);
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

	public static class NnContext extends ParserRuleContext {
		public NnContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_nn; }
	}

	public final NnContext nn() throws RecognitionException {
		NnContext _localctx = new NnContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_nn);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(79);
			match(T__5);
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

	public static class UuContext extends ParserRuleContext {
		public UuContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_uu; }
	}

	public final UuContext uu() throws RecognitionException {
		UuContext _localctx = new UuContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_uu);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(81);
			match(T__6);
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
		"\3\u0430\ud6d1\u8206\uad2d\u4417\uaef1\u8d80\uaadd\3\25V\4\2\t\2\4\3\t"+
		"\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13\t\13\3"+
		"\2\3\2\3\2\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3\3"+
		"\5\3)\n\3\3\4\3\4\3\4\3\5\3\5\3\5\3\6\3\6\3\6\3\7\3\7\3\7\3\7\3\7\3\7"+
		"\3\7\6\7;\n\7\r\7\16\7<\3\7\3\7\3\7\3\b\3\b\3\b\3\b\3\b\3\b\3\b\6\bI\n"+
		"\b\r\b\16\bJ\3\b\3\b\3\b\3\t\3\t\3\n\3\n\3\13\3\13\3\13\2\2\f\2\4\6\b"+
		"\n\f\16\20\22\24\2\2Q\2\26\3\2\2\2\4(\3\2\2\2\6*\3\2\2\2\b-\3\2\2\2\n"+
		"\60\3\2\2\2\f\63\3\2\2\2\16A\3\2\2\2\20O\3\2\2\2\22Q\3\2\2\2\24S\3\2\2"+
		"\2\26\27\5\4\3\2\27\30\b\2\1\2\30\3\3\2\2\2\31\32\5\6\4\2\32\33\b\3\1"+
		"\2\33)\3\2\2\2\34\35\5\b\5\2\35\36\b\3\1\2\36)\3\2\2\2\37 \5\n\6\2 !\b"+
		"\3\1\2!)\3\2\2\2\"#\5\f\7\2#$\b\3\1\2$)\3\2\2\2%&\5\16\b\2&\'\b\3\1\2"+
		"\')\3\2\2\2(\31\3\2\2\2(\34\3\2\2\2(\37\3\2\2\2(\"\3\2\2\2(%\3\2\2\2)"+
		"\5\3\2\2\2*+\5\20\t\2+,\b\4\1\2,\7\3\2\2\2-.\5\22\n\2./\b\5\1\2/\t\3\2"+
		"\2\2\60\61\5\24\13\2\61\62\b\6\1\2\62\13\3\2\2\2\63\64\7\3\2\2\64\65\7"+
		"\4\2\2\65\66\5\4\3\2\66:\b\7\1\2\678\5\4\3\289\b\7\1\29;\3\2\2\2:\67\3"+
		"\2\2\2;<\3\2\2\2<:\3\2\2\2<=\3\2\2\2=>\3\2\2\2>?\7\5\2\2?@\b\7\1\2@\r"+
		"\3\2\2\2AB\7\3\2\2BC\7\6\2\2CD\5\4\3\2DH\b\b\1\2EF\5\4\3\2FG\b\b\1\2G"+
		"I\3\2\2\2HE\3\2\2\2IJ\3\2\2\2JH\3\2\2\2JK\3\2\2\2KL\3\2\2\2LM\7\5\2\2"+
		"MN\b\b\1\2N\17\3\2\2\2OP\7\7\2\2P\21\3\2\2\2QR\7\b\2\2R\23\3\2\2\2ST\7"+
		"\t\2\2T\25\3\2\2\2\5(<J";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}