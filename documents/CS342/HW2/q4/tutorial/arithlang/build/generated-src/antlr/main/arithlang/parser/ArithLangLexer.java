// Generated from arithlang/parser/ArithLang.g by ANTLR 4.5
package arithlang.parser; import static arithlang.AST.*;
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class ArithLangLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.5", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, Define=8, Let=9, 
		Dot=10, Number=11, Identifier=12, Letter=13, LetterOrDigit=14, AT=15, 
		ELLIPSIS=16, WS=17, Comment=18, Line_Comment=19;
	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	public static final String[] ruleNames = {
		"T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "Define", "Let", 
		"Dot", "Number", "Identifier", "Letter", "LetterOrDigit", "DIGIT", "AT", 
		"ELLIPSIS", "WS", "Comment", "Line_Comment"
	};

	private static final String[] _LITERAL_NAMES = {
		null, "'-'", "'('", "'>?'", "')'", "'+'", "'*'", "'/'", "'define'", "'let'", 
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


	public ArithLangLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "ArithLang.g"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	@Override
	public boolean sempred(RuleContext _localctx, int ruleIndex, int predIndex) {
		switch (ruleIndex) {
		case 12:
			return Letter_sempred((RuleContext)_localctx, predIndex);
		case 13:
			return LetterOrDigit_sempred((RuleContext)_localctx, predIndex);
		}
		return true;
	}
	private boolean Letter_sempred(RuleContext _localctx, int predIndex) {
		switch (predIndex) {
		case 0:
			return Character.isJavaIdentifierStart(_input.LA(-1));
		case 1:
			return Character.isJavaIdentifierStart(Character.toCodePoint((char)_input.LA(-2), (char)_input.LA(-1)));
		}
		return true;
	}
	private boolean LetterOrDigit_sempred(RuleContext _localctx, int predIndex) {
		switch (predIndex) {
		case 2:
			return Character.isJavaIdentifierPart(_input.LA(-1));
		case 3:
			return Character.isJavaIdentifierPart(Character.toCodePoint((char)_input.LA(-2), (char)_input.LA(-1)));
		}
		return true;
	}

	public static final String _serializedATN =
		"\3\u0430\ud6d1\u8206\uad2d\u4417\uaef1\u8d80\uaadd\2\25\u008b\b\1\4\2"+
		"\t\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4"+
		"\13\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22"+
		"\t\22\4\23\t\23\4\24\t\24\4\25\t\25\3\2\3\2\3\3\3\3\3\4\3\4\3\4\3\5\3"+
		"\5\3\6\3\6\3\7\3\7\3\b\3\b\3\t\3\t\3\t\3\t\3\t\3\t\3\t\3\n\3\n\3\n\3\n"+
		"\3\13\3\13\3\f\6\fI\n\f\r\f\16\fJ\3\r\3\r\7\rO\n\r\f\r\16\rR\13\r\3\16"+
		"\3\16\3\16\3\16\3\16\3\16\5\16Z\n\16\3\17\3\17\3\17\3\17\3\17\3\17\5\17"+
		"b\n\17\3\20\3\20\3\21\3\21\3\22\3\22\3\22\3\22\3\23\6\23m\n\23\r\23\16"+
		"\23n\3\23\3\23\3\24\3\24\3\24\3\24\7\24w\n\24\f\24\16\24z\13\24\3\24\3"+
		"\24\3\24\3\24\3\24\3\25\3\25\3\25\3\25\7\25\u0085\n\25\f\25\16\25\u0088"+
		"\13\25\3\25\3\25\3x\2\26\3\3\5\4\7\5\t\6\13\7\r\b\17\t\21\n\23\13\25\f"+
		"\27\r\31\16\33\17\35\20\37\2!\21#\22%\23\'\24)\25\3\2\t\6\2&&C\\aac|\4"+
		"\2\2\u0101\ud802\udc01\3\2\ud802\udc01\3\2\udc02\ue001\7\2&&\62;C\\aa"+
		"c|\5\2\13\f\16\17\"\"\4\2\f\f\17\17\u0092\2\3\3\2\2\2\2\5\3\2\2\2\2\7"+
		"\3\2\2\2\2\t\3\2\2\2\2\13\3\2\2\2\2\r\3\2\2\2\2\17\3\2\2\2\2\21\3\2\2"+
		"\2\2\23\3\2\2\2\2\25\3\2\2\2\2\27\3\2\2\2\2\31\3\2\2\2\2\33\3\2\2\2\2"+
		"\35\3\2\2\2\2!\3\2\2\2\2#\3\2\2\2\2%\3\2\2\2\2\'\3\2\2\2\2)\3\2\2\2\3"+
		"+\3\2\2\2\5-\3\2\2\2\7/\3\2\2\2\t\62\3\2\2\2\13\64\3\2\2\2\r\66\3\2\2"+
		"\2\178\3\2\2\2\21:\3\2\2\2\23A\3\2\2\2\25E\3\2\2\2\27H\3\2\2\2\31L\3\2"+
		"\2\2\33Y\3\2\2\2\35a\3\2\2\2\37c\3\2\2\2!e\3\2\2\2#g\3\2\2\2%l\3\2\2\2"+
		"\'r\3\2\2\2)\u0080\3\2\2\2+,\7/\2\2,\4\3\2\2\2-.\7*\2\2.\6\3\2\2\2/\60"+
		"\7@\2\2\60\61\7A\2\2\61\b\3\2\2\2\62\63\7+\2\2\63\n\3\2\2\2\64\65\7-\2"+
		"\2\65\f\3\2\2\2\66\67\7,\2\2\67\16\3\2\2\289\7\61\2\29\20\3\2\2\2:;\7"+
		"f\2\2;<\7g\2\2<=\7h\2\2=>\7k\2\2>?\7p\2\2?@\7g\2\2@\22\3\2\2\2AB\7n\2"+
		"\2BC\7g\2\2CD\7v\2\2D\24\3\2\2\2EF\7\60\2\2F\26\3\2\2\2GI\5\37\20\2HG"+
		"\3\2\2\2IJ\3\2\2\2JH\3\2\2\2JK\3\2\2\2K\30\3\2\2\2LP\5\33\16\2MO\5\35"+
		"\17\2NM\3\2\2\2OR\3\2\2\2PN\3\2\2\2PQ\3\2\2\2Q\32\3\2\2\2RP\3\2\2\2SZ"+
		"\t\2\2\2TU\n\3\2\2UZ\6\16\2\2VW\t\4\2\2WX\t\5\2\2XZ\6\16\3\2YS\3\2\2\2"+
		"YT\3\2\2\2YV\3\2\2\2Z\34\3\2\2\2[b\t\6\2\2\\]\n\3\2\2]b\6\17\4\2^_\t\4"+
		"\2\2_`\t\5\2\2`b\6\17\5\2a[\3\2\2\2a\\\3\2\2\2a^\3\2\2\2b\36\3\2\2\2c"+
		"d\4\62;\2d \3\2\2\2ef\7B\2\2f\"\3\2\2\2gh\7\60\2\2hi\7\60\2\2ij\7\60\2"+
		"\2j$\3\2\2\2km\t\7\2\2lk\3\2\2\2mn\3\2\2\2nl\3\2\2\2no\3\2\2\2op\3\2\2"+
		"\2pq\b\23\2\2q&\3\2\2\2rs\7\61\2\2st\7,\2\2tx\3\2\2\2uw\13\2\2\2vu\3\2"+
		"\2\2wz\3\2\2\2xy\3\2\2\2xv\3\2\2\2y{\3\2\2\2zx\3\2\2\2{|\7,\2\2|}\7\61"+
		"\2\2}~\3\2\2\2~\177\b\24\2\2\177(\3\2\2\2\u0080\u0081\7\61\2\2\u0081\u0082"+
		"\7\61\2\2\u0082\u0086\3\2\2\2\u0083\u0085\n\b\2\2\u0084\u0083\3\2\2\2"+
		"\u0085\u0088\3\2\2\2\u0086\u0084\3\2\2\2\u0086\u0087\3\2\2\2\u0087\u0089"+
		"\3\2\2\2\u0088\u0086\3\2\2\2\u0089\u008a\b\25\2\2\u008a*\3\2\2\2\n\2J"+
		"PYanx\u0086\3\b\2\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}