// Generated from funclang\parser\FuncLang.g by ANTLR 4.5
package funclang.parser; import static funclang.AST.*;
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class FuncLangLexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.5", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		Define=10, Let=11, Letrec=12, Lambda=13, If=14, Car=15, Cdr=16, Cons=17, 
		List=18, Null=19, Less=20, Equal=21, Greater=22, TrueLiteral=23, FalseLiteral=24, 
		Ref=25, Deref=26, Assign=27, Free=28, Fork=29, Lock=30, UnLock=31, Process=32, 
		Send=33, Stop=34, Self=35, Dot=36, Number=37, Identifier=38, Letter=39, 
		LetterOrDigit=40, StrLiteral=41, AT=42, ELLIPSIS=43, WS=44, Comment=45, 
		Line_Comment=46;
	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	public static final String[] ruleNames = {
		"T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
		"Define", "Let", "Letrec", "Lambda", "If", "Car", "Cdr", "Cons", "List", 
		"Null", "Less", "Equal", "Greater", "TrueLiteral", "FalseLiteral", "Ref", 
		"Deref", "Assign", "Free", "Fork", "Lock", "UnLock", "Process", "Send", 
		"Stop", "Self", "Dot", "Number", "Identifier", "Letter", "LetterOrDigit", 
		"DIGIT", "ESCQUOTE", "StrLiteral", "AT", "ELLIPSIS", "WS", "Comment", 
		"Line_Comment"
	};

	private static final String[] _LITERAL_NAMES = {
		null, "'('", "')'", "'switch'", "'default'", "'case'", "'-'", "'+'", "'*'", 
		"'/'", "'define'", "'let'", "'letrec'", "'lambda'", "'if'", "'car'", "'cdr'", 
		"'cons'", "'list'", "'null?'", "'<'", "'='", "'>'", "'#t'", "'#f'", "'ref'", 
		"'deref'", "'set!'", "'free'", "'fork'", "'lock'", "'unlock'", "'process'", 
		"'send'", "'stop'", "'self'", "'.'", null, null, null, null, null, "'@'", 
		"'...'"
	};
	private static final String[] _SYMBOLIC_NAMES = {
		null, null, null, null, null, null, null, null, null, null, "Define", 
		"Let", "Letrec", "Lambda", "If", "Car", "Cdr", "Cons", "List", "Null", 
		"Less", "Equal", "Greater", "TrueLiteral", "FalseLiteral", "Ref", "Deref", 
		"Assign", "Free", "Fork", "Lock", "UnLock", "Process", "Send", "Stop", 
		"Self", "Dot", "Number", "Identifier", "Letter", "LetterOrDigit", "StrLiteral", 
		"AT", "ELLIPSIS", "WS", "Comment", "Line_Comment"
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


	public FuncLangLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "FuncLang.g"; }

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
		case 38:
			return Letter_sempred((RuleContext)_localctx, predIndex);
		case 39:
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
		"\3\u0430\ud6d1\u8206\uad2d\u4417\uaef1\u8d80\uaadd\2\60\u0152\b\1\4\2"+
		"\t\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4"+
		"\13\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22"+
		"\t\22\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31"+
		"\t\31\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37\4 \t"+
		" \4!\t!\4\"\t\"\4#\t#\4$\t$\4%\t%\4&\t&\4\'\t\'\4(\t(\4)\t)\4*\t*\4+\t"+
		"+\4,\t,\4-\t-\4.\t.\4/\t/\4\60\t\60\4\61\t\61\3\2\3\2\3\3\3\3\3\4\3\4"+
		"\3\4\3\4\3\4\3\4\3\4\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\6\3\6\3\6\3\6\3"+
		"\6\3\7\3\7\3\b\3\b\3\t\3\t\3\n\3\n\3\13\3\13\3\13\3\13\3\13\3\13\3\13"+
		"\3\f\3\f\3\f\3\f\3\r\3\r\3\r\3\r\3\r\3\r\3\r\3\16\3\16\3\16\3\16\3\16"+
		"\3\16\3\16\3\17\3\17\3\17\3\20\3\20\3\20\3\20\3\21\3\21\3\21\3\21\3\22"+
		"\3\22\3\22\3\22\3\22\3\23\3\23\3\23\3\23\3\23\3\24\3\24\3\24\3\24\3\24"+
		"\3\24\3\25\3\25\3\26\3\26\3\27\3\27\3\30\3\30\3\30\3\31\3\31\3\31\3\32"+
		"\3\32\3\32\3\32\3\33\3\33\3\33\3\33\3\33\3\33\3\34\3\34\3\34\3\34\3\34"+
		"\3\35\3\35\3\35\3\35\3\35\3\36\3\36\3\36\3\36\3\36\3\37\3\37\3\37\3\37"+
		"\3\37\3 \3 \3 \3 \3 \3 \3 \3!\3!\3!\3!\3!\3!\3!\3!\3\"\3\"\3\"\3\"\3\""+
		"\3#\3#\3#\3#\3#\3$\3$\3$\3$\3$\3%\3%\3&\6&\u0103\n&\r&\16&\u0104\3\'\3"+
		"\'\7\'\u0109\n\'\f\'\16\'\u010c\13\'\3(\3(\3(\3(\3(\3(\5(\u0114\n(\3)"+
		"\3)\3)\3)\3)\3)\5)\u011c\n)\3*\3*\3+\3+\3+\3,\3,\3,\7,\u0126\n,\f,\16"+
		",\u0129\13,\3,\3,\3-\3-\3.\3.\3.\3.\3/\6/\u0134\n/\r/\16/\u0135\3/\3/"+
		"\3\60\3\60\3\60\3\60\7\60\u013e\n\60\f\60\16\60\u0141\13\60\3\60\3\60"+
		"\3\60\3\60\3\60\3\61\3\61\3\61\3\61\7\61\u014c\n\61\f\61\16\61\u014f\13"+
		"\61\3\61\3\61\4\u0127\u013f\2\62\3\3\5\4\7\5\t\6\13\7\r\b\17\t\21\n\23"+
		"\13\25\f\27\r\31\16\33\17\35\20\37\21!\22#\23%\24\'\25)\26+\27-\30/\31"+
		"\61\32\63\33\65\34\67\359\36;\37= ?!A\"C#E$G%I&K\'M(O)Q*S\2U\2W+Y,[-]"+
		"._/a\60\3\2\t\6\2&&C\\aac|\4\2\2\u0101\ud802\udc01\3\2\ud802\udc01\3\2"+
		"\udc02\ue001\7\2&&\62;C\\aac|\4\2\f\f\17\17\5\2\13\f\16\17\"\"\u015a\2"+
		"\3\3\2\2\2\2\5\3\2\2\2\2\7\3\2\2\2\2\t\3\2\2\2\2\13\3\2\2\2\2\r\3\2\2"+
		"\2\2\17\3\2\2\2\2\21\3\2\2\2\2\23\3\2\2\2\2\25\3\2\2\2\2\27\3\2\2\2\2"+
		"\31\3\2\2\2\2\33\3\2\2\2\2\35\3\2\2\2\2\37\3\2\2\2\2!\3\2\2\2\2#\3\2\2"+
		"\2\2%\3\2\2\2\2\'\3\2\2\2\2)\3\2\2\2\2+\3\2\2\2\2-\3\2\2\2\2/\3\2\2\2"+
		"\2\61\3\2\2\2\2\63\3\2\2\2\2\65\3\2\2\2\2\67\3\2\2\2\29\3\2\2\2\2;\3\2"+
		"\2\2\2=\3\2\2\2\2?\3\2\2\2\2A\3\2\2\2\2C\3\2\2\2\2E\3\2\2\2\2G\3\2\2\2"+
		"\2I\3\2\2\2\2K\3\2\2\2\2M\3\2\2\2\2O\3\2\2\2\2Q\3\2\2\2\2W\3\2\2\2\2Y"+
		"\3\2\2\2\2[\3\2\2\2\2]\3\2\2\2\2_\3\2\2\2\2a\3\2\2\2\3c\3\2\2\2\5e\3\2"+
		"\2\2\7g\3\2\2\2\tn\3\2\2\2\13v\3\2\2\2\r{\3\2\2\2\17}\3\2\2\2\21\177\3"+
		"\2\2\2\23\u0081\3\2\2\2\25\u0083\3\2\2\2\27\u008a\3\2\2\2\31\u008e\3\2"+
		"\2\2\33\u0095\3\2\2\2\35\u009c\3\2\2\2\37\u009f\3\2\2\2!\u00a3\3\2\2\2"+
		"#\u00a7\3\2\2\2%\u00ac\3\2\2\2\'\u00b1\3\2\2\2)\u00b7\3\2\2\2+\u00b9\3"+
		"\2\2\2-\u00bb\3\2\2\2/\u00bd\3\2\2\2\61\u00c0\3\2\2\2\63\u00c3\3\2\2\2"+
		"\65\u00c7\3\2\2\2\67\u00cd\3\2\2\29\u00d2\3\2\2\2;\u00d7\3\2\2\2=\u00dc"+
		"\3\2\2\2?\u00e1\3\2\2\2A\u00e8\3\2\2\2C\u00f0\3\2\2\2E\u00f5\3\2\2\2G"+
		"\u00fa\3\2\2\2I\u00ff\3\2\2\2K\u0102\3\2\2\2M\u0106\3\2\2\2O\u0113\3\2"+
		"\2\2Q\u011b\3\2\2\2S\u011d\3\2\2\2U\u011f\3\2\2\2W\u0122\3\2\2\2Y\u012c"+
		"\3\2\2\2[\u012e\3\2\2\2]\u0133\3\2\2\2_\u0139\3\2\2\2a\u0147\3\2\2\2c"+
		"d\7*\2\2d\4\3\2\2\2ef\7+\2\2f\6\3\2\2\2gh\7u\2\2hi\7y\2\2ij\7k\2\2jk\7"+
		"v\2\2kl\7e\2\2lm\7j\2\2m\b\3\2\2\2no\7f\2\2op\7g\2\2pq\7h\2\2qr\7c\2\2"+
		"rs\7w\2\2st\7n\2\2tu\7v\2\2u\n\3\2\2\2vw\7e\2\2wx\7c\2\2xy\7u\2\2yz\7"+
		"g\2\2z\f\3\2\2\2{|\7/\2\2|\16\3\2\2\2}~\7-\2\2~\20\3\2\2\2\177\u0080\7"+
		",\2\2\u0080\22\3\2\2\2\u0081\u0082\7\61\2\2\u0082\24\3\2\2\2\u0083\u0084"+
		"\7f\2\2\u0084\u0085\7g\2\2\u0085\u0086\7h\2\2\u0086\u0087\7k\2\2\u0087"+
		"\u0088\7p\2\2\u0088\u0089\7g\2\2\u0089\26\3\2\2\2\u008a\u008b\7n\2\2\u008b"+
		"\u008c\7g\2\2\u008c\u008d\7v\2\2\u008d\30\3\2\2\2\u008e\u008f\7n\2\2\u008f"+
		"\u0090\7g\2\2\u0090\u0091\7v\2\2\u0091\u0092\7t\2\2\u0092\u0093\7g\2\2"+
		"\u0093\u0094\7e\2\2\u0094\32\3\2\2\2\u0095\u0096\7n\2\2\u0096\u0097\7"+
		"c\2\2\u0097\u0098\7o\2\2\u0098\u0099\7d\2\2\u0099\u009a\7f\2\2\u009a\u009b"+
		"\7c\2\2\u009b\34\3\2\2\2\u009c\u009d\7k\2\2\u009d\u009e\7h\2\2\u009e\36"+
		"\3\2\2\2\u009f\u00a0\7e\2\2\u00a0\u00a1\7c\2\2\u00a1\u00a2\7t\2\2\u00a2"+
		" \3\2\2\2\u00a3\u00a4\7e\2\2\u00a4\u00a5\7f\2\2\u00a5\u00a6\7t\2\2\u00a6"+
		"\"\3\2\2\2\u00a7\u00a8\7e\2\2\u00a8\u00a9\7q\2\2\u00a9\u00aa\7p\2\2\u00aa"+
		"\u00ab\7u\2\2\u00ab$\3\2\2\2\u00ac\u00ad\7n\2\2\u00ad\u00ae\7k\2\2\u00ae"+
		"\u00af\7u\2\2\u00af\u00b0\7v\2\2\u00b0&\3\2\2\2\u00b1\u00b2\7p\2\2\u00b2"+
		"\u00b3\7w\2\2\u00b3\u00b4\7n\2\2\u00b4\u00b5\7n\2\2\u00b5\u00b6\7A\2\2"+
		"\u00b6(\3\2\2\2\u00b7\u00b8\7>\2\2\u00b8*\3\2\2\2\u00b9\u00ba\7?\2\2\u00ba"+
		",\3\2\2\2\u00bb\u00bc\7@\2\2\u00bc.\3\2\2\2\u00bd\u00be\7%\2\2\u00be\u00bf"+
		"\7v\2\2\u00bf\60\3\2\2\2\u00c0\u00c1\7%\2\2\u00c1\u00c2\7h\2\2\u00c2\62"+
		"\3\2\2\2\u00c3\u00c4\7t\2\2\u00c4\u00c5\7g\2\2\u00c5\u00c6\7h\2\2\u00c6"+
		"\64\3\2\2\2\u00c7\u00c8\7f\2\2\u00c8\u00c9\7g\2\2\u00c9\u00ca\7t\2\2\u00ca"+
		"\u00cb\7g\2\2\u00cb\u00cc\7h\2\2\u00cc\66\3\2\2\2\u00cd\u00ce\7u\2\2\u00ce"+
		"\u00cf\7g\2\2\u00cf\u00d0\7v\2\2\u00d0\u00d1\7#\2\2\u00d18\3\2\2\2\u00d2"+
		"\u00d3\7h\2\2\u00d3\u00d4\7t\2\2\u00d4\u00d5\7g\2\2\u00d5\u00d6\7g\2\2"+
		"\u00d6:\3\2\2\2\u00d7\u00d8\7h\2\2\u00d8\u00d9\7q\2\2\u00d9\u00da\7t\2"+
		"\2\u00da\u00db\7m\2\2\u00db<\3\2\2\2\u00dc\u00dd\7n\2\2\u00dd\u00de\7"+
		"q\2\2\u00de\u00df\7e\2\2\u00df\u00e0\7m\2\2\u00e0>\3\2\2\2\u00e1\u00e2"+
		"\7w\2\2\u00e2\u00e3\7p\2\2\u00e3\u00e4\7n\2\2\u00e4\u00e5\7q\2\2\u00e5"+
		"\u00e6\7e\2\2\u00e6\u00e7\7m\2\2\u00e7@\3\2\2\2\u00e8\u00e9\7r\2\2\u00e9"+
		"\u00ea\7t\2\2\u00ea\u00eb\7q\2\2\u00eb\u00ec\7e\2\2\u00ec\u00ed\7g\2\2"+
		"\u00ed\u00ee\7u\2\2\u00ee\u00ef\7u\2\2\u00efB\3\2\2\2\u00f0\u00f1\7u\2"+
		"\2\u00f1\u00f2\7g\2\2\u00f2\u00f3\7p\2\2\u00f3\u00f4\7f\2\2\u00f4D\3\2"+
		"\2\2\u00f5\u00f6\7u\2\2\u00f6\u00f7\7v\2\2\u00f7\u00f8\7q\2\2\u00f8\u00f9"+
		"\7r\2\2\u00f9F\3\2\2\2\u00fa\u00fb\7u\2\2\u00fb\u00fc\7g\2\2\u00fc\u00fd"+
		"\7n\2\2\u00fd\u00fe\7h\2\2\u00feH\3\2\2\2\u00ff\u0100\7\60\2\2\u0100J"+
		"\3\2\2\2\u0101\u0103\5S*\2\u0102\u0101\3\2\2\2\u0103\u0104\3\2\2\2\u0104"+
		"\u0102\3\2\2\2\u0104\u0105\3\2\2\2\u0105L\3\2\2\2\u0106\u010a\5O(\2\u0107"+
		"\u0109\5Q)\2\u0108\u0107\3\2\2\2\u0109\u010c\3\2\2\2\u010a\u0108\3\2\2"+
		"\2\u010a\u010b\3\2\2\2\u010bN\3\2\2\2\u010c\u010a\3\2\2\2\u010d\u0114"+
		"\t\2\2\2\u010e\u010f\n\3\2\2\u010f\u0114\6(\2\2\u0110\u0111\t\4\2\2\u0111"+
		"\u0112\t\5\2\2\u0112\u0114\6(\3\2\u0113\u010d\3\2\2\2\u0113\u010e\3\2"+
		"\2\2\u0113\u0110\3\2\2\2\u0114P\3\2\2\2\u0115\u011c\t\6\2\2\u0116\u0117"+
		"\n\3\2\2\u0117\u011c\6)\4\2\u0118\u0119\t\4\2\2\u0119\u011a\t\5\2\2\u011a"+
		"\u011c\6)\5\2\u011b\u0115\3\2\2\2\u011b\u0116\3\2\2\2\u011b\u0118\3\2"+
		"\2\2\u011cR\3\2\2\2\u011d\u011e\4\62;\2\u011eT\3\2\2\2\u011f\u0120\7^"+
		"\2\2\u0120\u0121\7$\2\2\u0121V\3\2\2\2\u0122\u0127\7$\2\2\u0123\u0126"+
		"\5U+\2\u0124\u0126\n\7\2\2\u0125\u0123\3\2\2\2\u0125\u0124\3\2\2\2\u0126"+
		"\u0129\3\2\2\2\u0127\u0128\3\2\2\2\u0127\u0125\3\2\2\2\u0128\u012a\3\2"+
		"\2\2\u0129\u0127\3\2\2\2\u012a\u012b\7$\2\2\u012bX\3\2\2\2\u012c\u012d"+
		"\7B\2\2\u012dZ\3\2\2\2\u012e\u012f\7\60\2\2\u012f\u0130\7\60\2\2\u0130"+
		"\u0131\7\60\2\2\u0131\\\3\2\2\2\u0132\u0134\t\b\2\2\u0133\u0132\3\2\2"+
		"\2\u0134\u0135\3\2\2\2\u0135\u0133\3\2\2\2\u0135\u0136\3\2\2\2\u0136\u0137"+
		"\3\2\2\2\u0137\u0138\b/\2\2\u0138^\3\2\2\2\u0139\u013a\7\61\2\2\u013a"+
		"\u013b\7,\2\2\u013b\u013f\3\2\2\2\u013c\u013e\13\2\2\2\u013d\u013c\3\2"+
		"\2\2\u013e\u0141\3\2\2\2\u013f\u0140\3\2\2\2\u013f\u013d\3\2\2\2\u0140"+
		"\u0142\3\2\2\2\u0141\u013f\3\2\2\2\u0142\u0143\7,\2\2\u0143\u0144\7\61"+
		"\2\2\u0144\u0145\3\2\2\2\u0145\u0146\b\60\2\2\u0146`\3\2\2\2\u0147\u0148"+
		"\7\61\2\2\u0148\u0149\7\61\2\2\u0149\u014d\3\2\2\2\u014a\u014c\n\7\2\2"+
		"\u014b\u014a\3\2\2\2\u014c\u014f\3\2\2\2\u014d\u014b\3\2\2\2\u014d\u014e"+
		"\3\2\2\2\u014e\u0150\3\2\2\2\u014f\u014d\3\2\2\2\u0150\u0151\b\61\2\2"+
		"\u0151b\3\2\2\2\f\2\u0104\u010a\u0113\u011b\u0125\u0127\u0135\u013f\u014d"+
		"\3\b\2\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}