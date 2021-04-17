// Generated from typelang\parser\TypeLang.g by ANTLR 4.5
package typelang.parser; import static typelang.AST.*; import typelang.*; import typelang.Type.*;
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class TypeLangLexer extends Lexer {
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
	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	public static final String[] ruleNames = {
		"T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
		"T__9", "T__10", "T__11", "T__12", "T__13", "T__14", "Define", "Let", 
		"Letrec", "Lambda", "If", "Car", "Cdr", "Cons", "List", "Null", "Less", 
		"Equal", "Greater", "TrueLiteral", "FalseLiteral", "Ref", "Deref", "Assign", 
		"Free", "Fork", "Lock", "UnLock", "Process", "Send", "Stop", "Self", "Dot", 
		"Number", "Identifier", "Letter", "LetterOrDigit", "DIGIT", "ESCQUOTE", 
		"StrLiteral", "AT", "ELLIPSIS", "WS", "Comment", "Line_Comment"
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


	public TypeLangLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "TypeLang.g"; }

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
		case 44:
			return Letter_sempred((RuleContext)_localctx, predIndex);
		case 45:
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
		"\3\u0430\ud6d1\u8206\uad2d\u4417\uaef1\u8d80\uaadd\2\66\u016d\b\1\4\2"+
		"\t\2\4\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4"+
		"\13\t\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22"+
		"\t\22\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31"+
		"\t\31\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37\4 \t"+
		" \4!\t!\4\"\t\"\4#\t#\4$\t$\4%\t%\4&\t&\4\'\t\'\4(\t(\4)\t)\4*\t*\4+\t"+
		"+\4,\t,\4-\t-\4.\t.\4/\t/\4\60\t\60\4\61\t\61\4\62\t\62\4\63\t\63\4\64"+
		"\t\64\4\65\t\65\4\66\t\66\4\67\t\67\3\2\3\2\3\3\3\3\3\4\3\4\3\5\3\5\3"+
		"\6\3\6\3\7\3\7\3\b\3\b\3\t\3\t\3\t\3\t\3\t\3\n\3\n\3\n\3\n\3\n\3\13\3"+
		"\13\3\13\3\13\3\f\3\f\3\f\3\f\3\f\3\f\3\r\3\r\3\16\3\16\3\16\3\16\3\17"+
		"\3\17\3\17\3\17\3\20\3\20\3\20\3\21\3\21\3\21\3\21\3\21\3\21\3\21\3\22"+
		"\3\22\3\22\3\22\3\23\3\23\3\23\3\23\3\23\3\23\3\23\3\24\3\24\3\24\3\24"+
		"\3\24\3\24\3\24\3\25\3\25\3\25\3\26\3\26\3\26\3\26\3\27\3\27\3\27\3\27"+
		"\3\30\3\30\3\30\3\30\3\30\3\31\3\31\3\31\3\31\3\31\3\32\3\32\3\32\3\32"+
		"\3\32\3\32\3\33\3\33\3\34\3\34\3\35\3\35\3\36\3\36\3\36\3\37\3\37\3\37"+
		"\3 \3 \3 \3 \3!\3!\3!\3!\3!\3!\3\"\3\"\3\"\3\"\3\"\3#\3#\3#\3#\3#\3$\3"+
		"$\3$\3$\3$\3%\3%\3%\3%\3%\3&\3&\3&\3&\3&\3&\3&\3\'\3\'\3\'\3\'\3\'\3\'"+
		"\3\'\3\'\3(\3(\3(\3(\3(\3)\3)\3)\3)\3)\3*\3*\3*\3*\3*\3+\3+\3,\6,\u011e"+
		"\n,\r,\16,\u011f\3-\3-\7-\u0124\n-\f-\16-\u0127\13-\3.\3.\3.\3.\3.\3."+
		"\5.\u012f\n.\3/\3/\3/\3/\3/\3/\5/\u0137\n/\3\60\3\60\3\61\3\61\3\61\3"+
		"\62\3\62\3\62\7\62\u0141\n\62\f\62\16\62\u0144\13\62\3\62\3\62\3\63\3"+
		"\63\3\64\3\64\3\64\3\64\3\65\6\65\u014f\n\65\r\65\16\65\u0150\3\65\3\65"+
		"\3\66\3\66\3\66\3\66\7\66\u0159\n\66\f\66\16\66\u015c\13\66\3\66\3\66"+
		"\3\66\3\66\3\66\3\67\3\67\3\67\3\67\7\67\u0167\n\67\f\67\16\67\u016a\13"+
		"\67\3\67\3\67\4\u0142\u015a\28\3\3\5\4\7\5\t\6\13\7\r\b\17\t\21\n\23\13"+
		"\25\f\27\r\31\16\33\17\35\20\37\21!\22#\23%\24\'\25)\26+\27-\30/\31\61"+
		"\32\63\33\65\34\67\359\36;\37= ?!A\"C#E$G%I&K\'M(O)Q*S+U,W-Y.[/]\60_\2"+
		"a\2c\61e\62g\63i\64k\65m\66\3\2\t\6\2&&C\\aac|\4\2\2\u0101\ud802\udc01"+
		"\3\2\ud802\udc01\3\2\udc02\ue001\7\2&&\62;C\\aac|\4\2\f\f\17\17\5\2\13"+
		"\f\16\17\"\"\u0175\2\3\3\2\2\2\2\5\3\2\2\2\2\7\3\2\2\2\2\t\3\2\2\2\2\13"+
		"\3\2\2\2\2\r\3\2\2\2\2\17\3\2\2\2\2\21\3\2\2\2\2\23\3\2\2\2\2\25\3\2\2"+
		"\2\2\27\3\2\2\2\2\31\3\2\2\2\2\33\3\2\2\2\2\35\3\2\2\2\2\37\3\2\2\2\2"+
		"!\3\2\2\2\2#\3\2\2\2\2%\3\2\2\2\2\'\3\2\2\2\2)\3\2\2\2\2+\3\2\2\2\2-\3"+
		"\2\2\2\2/\3\2\2\2\2\61\3\2\2\2\2\63\3\2\2\2\2\65\3\2\2\2\2\67\3\2\2\2"+
		"\29\3\2\2\2\2;\3\2\2\2\2=\3\2\2\2\2?\3\2\2\2\2A\3\2\2\2\2C\3\2\2\2\2E"+
		"\3\2\2\2\2G\3\2\2\2\2I\3\2\2\2\2K\3\2\2\2\2M\3\2\2\2\2O\3\2\2\2\2Q\3\2"+
		"\2\2\2S\3\2\2\2\2U\3\2\2\2\2W\3\2\2\2\2Y\3\2\2\2\2[\3\2\2\2\2]\3\2\2\2"+
		"\2c\3\2\2\2\2e\3\2\2\2\2g\3\2\2\2\2i\3\2\2\2\2k\3\2\2\2\2m\3\2\2\2\3o"+
		"\3\2\2\2\5q\3\2\2\2\7s\3\2\2\2\tu\3\2\2\2\13w\3\2\2\2\ry\3\2\2\2\17{\3"+
		"\2\2\2\21}\3\2\2\2\23\u0082\3\2\2\2\25\u0087\3\2\2\2\27\u008b\3\2\2\2"+
		"\31\u0091\3\2\2\2\33\u0093\3\2\2\2\35\u0097\3\2\2\2\37\u009b\3\2\2\2!"+
		"\u009e\3\2\2\2#\u00a5\3\2\2\2%\u00a9\3\2\2\2\'\u00b0\3\2\2\2)\u00b7\3"+
		"\2\2\2+\u00ba\3\2\2\2-\u00be\3\2\2\2/\u00c2\3\2\2\2\61\u00c7\3\2\2\2\63"+
		"\u00cc\3\2\2\2\65\u00d2\3\2\2\2\67\u00d4\3\2\2\29\u00d6\3\2\2\2;\u00d8"+
		"\3\2\2\2=\u00db\3\2\2\2?\u00de\3\2\2\2A\u00e2\3\2\2\2C\u00e8\3\2\2\2E"+
		"\u00ed\3\2\2\2G\u00f2\3\2\2\2I\u00f7\3\2\2\2K\u00fc\3\2\2\2M\u0103\3\2"+
		"\2\2O\u010b\3\2\2\2Q\u0110\3\2\2\2S\u0115\3\2\2\2U\u011a\3\2\2\2W\u011d"+
		"\3\2\2\2Y\u0121\3\2\2\2[\u012e\3\2\2\2]\u0136\3\2\2\2_\u0138\3\2\2\2a"+
		"\u013a\3\2\2\2c\u013d\3\2\2\2e\u0147\3\2\2\2g\u0149\3\2\2\2i\u014e\3\2"+
		"\2\2k\u0154\3\2\2\2m\u0162\3\2\2\2op\7/\2\2p\4\3\2\2\2qr\7*\2\2r\6\3\2"+
		"\2\2st\7-\2\2t\b\3\2\2\2uv\7+\2\2v\n\3\2\2\2wx\7,\2\2x\f\3\2\2\2yz\7\61"+
		"\2\2z\16\3\2\2\2{|\7<\2\2|\20\3\2\2\2}~\7d\2\2~\177\7q\2\2\177\u0080\7"+
		"q\2\2\u0080\u0081\7n\2\2\u0081\22\3\2\2\2\u0082\u0083\7w\2\2\u0083\u0084"+
		"\7p\2\2\u0084\u0085\7k\2\2\u0085\u0086\7v\2\2\u0086\24\3\2\2\2\u0087\u0088"+
		"\7p\2\2\u0088\u0089\7w\2\2\u0089\u008a\7o\2\2\u008a\26\3\2\2\2\u008b\u008c"+
		"\7N\2\2\u008c\u008d\7k\2\2\u008d\u008e\7u\2\2\u008e\u008f\7v\2\2\u008f"+
		"\u0090\7>\2\2\u0090\30\3\2\2\2\u0091\u0092\7.\2\2\u0092\32\3\2\2\2\u0093"+
		"\u0094\7T\2\2\u0094\u0095\7g\2\2\u0095\u0096\7h\2\2\u0096\34\3\2\2\2\u0097"+
		"\u0098\7U\2\2\u0098\u0099\7v\2\2\u0099\u009a\7t\2\2\u009a\36\3\2\2\2\u009b"+
		"\u009c\7/\2\2\u009c\u009d\7@\2\2\u009d \3\2\2\2\u009e\u009f\7f\2\2\u009f"+
		"\u00a0\7g\2\2\u00a0\u00a1\7h\2\2\u00a1\u00a2\7k\2\2\u00a2\u00a3\7p\2\2"+
		"\u00a3\u00a4\7g\2\2\u00a4\"\3\2\2\2\u00a5\u00a6\7n\2\2\u00a6\u00a7\7g"+
		"\2\2\u00a7\u00a8\7v\2\2\u00a8$\3\2\2\2\u00a9\u00aa\7n\2\2\u00aa\u00ab"+
		"\7g\2\2\u00ab\u00ac\7v\2\2\u00ac\u00ad\7t\2\2\u00ad\u00ae\7g\2\2\u00ae"+
		"\u00af\7e\2\2\u00af&\3\2\2\2\u00b0\u00b1\7n\2\2\u00b1\u00b2\7c\2\2\u00b2"+
		"\u00b3\7o\2\2\u00b3\u00b4\7d\2\2\u00b4\u00b5\7f\2\2\u00b5\u00b6\7c\2\2"+
		"\u00b6(\3\2\2\2\u00b7\u00b8\7k\2\2\u00b8\u00b9\7h\2\2\u00b9*\3\2\2\2\u00ba"+
		"\u00bb\7e\2\2\u00bb\u00bc\7c\2\2\u00bc\u00bd\7t\2\2\u00bd,\3\2\2\2\u00be"+
		"\u00bf\7e\2\2\u00bf\u00c0\7f\2\2\u00c0\u00c1\7t\2\2\u00c1.\3\2\2\2\u00c2"+
		"\u00c3\7e\2\2\u00c3\u00c4\7q\2\2\u00c4\u00c5\7p\2\2\u00c5\u00c6\7u\2\2"+
		"\u00c6\60\3\2\2\2\u00c7\u00c8\7n\2\2\u00c8\u00c9\7k\2\2\u00c9\u00ca\7"+
		"u\2\2\u00ca\u00cb\7v\2\2\u00cb\62\3\2\2\2\u00cc\u00cd\7p\2\2\u00cd\u00ce"+
		"\7w\2\2\u00ce\u00cf\7n\2\2\u00cf\u00d0\7n\2\2\u00d0\u00d1\7A\2\2\u00d1"+
		"\64\3\2\2\2\u00d2\u00d3\7>\2\2\u00d3\66\3\2\2\2\u00d4\u00d5\7?\2\2\u00d5"+
		"8\3\2\2\2\u00d6\u00d7\7@\2\2\u00d7:\3\2\2\2\u00d8\u00d9\7%\2\2\u00d9\u00da"+
		"\7v\2\2\u00da<\3\2\2\2\u00db\u00dc\7%\2\2\u00dc\u00dd\7h\2\2\u00dd>\3"+
		"\2\2\2\u00de\u00df\7t\2\2\u00df\u00e0\7g\2\2\u00e0\u00e1\7h\2\2\u00e1"+
		"@\3\2\2\2\u00e2\u00e3\7f\2\2\u00e3\u00e4\7g\2\2\u00e4\u00e5\7t\2\2\u00e5"+
		"\u00e6\7g\2\2\u00e6\u00e7\7h\2\2\u00e7B\3\2\2\2\u00e8\u00e9\7u\2\2\u00e9"+
		"\u00ea\7g\2\2\u00ea\u00eb\7v\2\2\u00eb\u00ec\7#\2\2\u00ecD\3\2\2\2\u00ed"+
		"\u00ee\7h\2\2\u00ee\u00ef\7t\2\2\u00ef\u00f0\7g\2\2\u00f0\u00f1\7g\2\2"+
		"\u00f1F\3\2\2\2\u00f2\u00f3\7h\2\2\u00f3\u00f4\7q\2\2\u00f4\u00f5\7t\2"+
		"\2\u00f5\u00f6\7m\2\2\u00f6H\3\2\2\2\u00f7\u00f8\7n\2\2\u00f8\u00f9\7"+
		"q\2\2\u00f9\u00fa\7e\2\2\u00fa\u00fb\7m\2\2\u00fbJ\3\2\2\2\u00fc\u00fd"+
		"\7w\2\2\u00fd\u00fe\7p\2\2\u00fe\u00ff\7n\2\2\u00ff\u0100\7q\2\2\u0100"+
		"\u0101\7e\2\2\u0101\u0102\7m\2\2\u0102L\3\2\2\2\u0103\u0104\7r\2\2\u0104"+
		"\u0105\7t\2\2\u0105\u0106\7q\2\2\u0106\u0107\7e\2\2\u0107\u0108\7g\2\2"+
		"\u0108\u0109\7u\2\2\u0109\u010a\7u\2\2\u010aN\3\2\2\2\u010b\u010c\7u\2"+
		"\2\u010c\u010d\7g\2\2\u010d\u010e\7p\2\2\u010e\u010f\7f\2\2\u010fP\3\2"+
		"\2\2\u0110\u0111\7u\2\2\u0111\u0112\7v\2\2\u0112\u0113\7q\2\2\u0113\u0114"+
		"\7r\2\2\u0114R\3\2\2\2\u0115\u0116\7u\2\2\u0116\u0117\7g\2\2\u0117\u0118"+
		"\7n\2\2\u0118\u0119\7h\2\2\u0119T\3\2\2\2\u011a\u011b\7\60\2\2\u011bV"+
		"\3\2\2\2\u011c\u011e\5_\60\2\u011d\u011c\3\2\2\2\u011e\u011f\3\2\2\2\u011f"+
		"\u011d\3\2\2\2\u011f\u0120\3\2\2\2\u0120X\3\2\2\2\u0121\u0125\5[.\2\u0122"+
		"\u0124\5]/\2\u0123\u0122\3\2\2\2\u0124\u0127\3\2\2\2\u0125\u0123\3\2\2"+
		"\2\u0125\u0126\3\2\2\2\u0126Z\3\2\2\2\u0127\u0125\3\2\2\2\u0128\u012f"+
		"\t\2\2\2\u0129\u012a\n\3\2\2\u012a\u012f\6.\2\2\u012b\u012c\t\4\2\2\u012c"+
		"\u012d\t\5\2\2\u012d\u012f\6.\3\2\u012e\u0128\3\2\2\2\u012e\u0129\3\2"+
		"\2\2\u012e\u012b\3\2\2\2\u012f\\\3\2\2\2\u0130\u0137\t\6\2\2\u0131\u0132"+
		"\n\3\2\2\u0132\u0137\6/\4\2\u0133\u0134\t\4\2\2\u0134\u0135\t\5\2\2\u0135"+
		"\u0137\6/\5\2\u0136\u0130\3\2\2\2\u0136\u0131\3\2\2\2\u0136\u0133\3\2"+
		"\2\2\u0137^\3\2\2\2\u0138\u0139\4\62;\2\u0139`\3\2\2\2\u013a\u013b\7^"+
		"\2\2\u013b\u013c\7$\2\2\u013cb\3\2\2\2\u013d\u0142\7$\2\2\u013e\u0141"+
		"\5a\61\2\u013f\u0141\n\7\2\2\u0140\u013e\3\2\2\2\u0140\u013f\3\2\2\2\u0141"+
		"\u0144\3\2\2\2\u0142\u0143\3\2\2\2\u0142\u0140\3\2\2\2\u0143\u0145\3\2"+
		"\2\2\u0144\u0142\3\2\2\2\u0145\u0146\7$\2\2\u0146d\3\2\2\2\u0147\u0148"+
		"\7B\2\2\u0148f\3\2\2\2\u0149\u014a\7\60\2\2\u014a\u014b\7\60\2\2\u014b"+
		"\u014c\7\60\2\2\u014ch\3\2\2\2\u014d\u014f\t\b\2\2\u014e\u014d\3\2\2\2"+
		"\u014f\u0150\3\2\2\2\u0150\u014e\3\2\2\2\u0150\u0151\3\2\2\2\u0151\u0152"+
		"\3\2\2\2\u0152\u0153\b\65\2\2\u0153j\3\2\2\2\u0154\u0155\7\61\2\2\u0155"+
		"\u0156\7,\2\2\u0156\u015a\3\2\2\2\u0157\u0159\13\2\2\2\u0158\u0157\3\2"+
		"\2\2\u0159\u015c\3\2\2\2\u015a\u015b\3\2\2\2\u015a\u0158\3\2\2\2\u015b"+
		"\u015d\3\2\2\2\u015c\u015a\3\2\2\2\u015d\u015e\7,\2\2\u015e\u015f\7\61"+
		"\2\2\u015f\u0160\3\2\2\2\u0160\u0161\b\66\2\2\u0161l\3\2\2\2\u0162\u0163"+
		"\7\61\2\2\u0163\u0164\7\61\2\2\u0164\u0168\3\2\2\2\u0165\u0167\n\7\2\2"+
		"\u0166\u0165\3\2\2\2\u0167\u016a\3\2\2\2\u0168\u0166\3\2\2\2\u0168\u0169"+
		"\3\2\2\2\u0169\u016b\3\2\2\2\u016a\u0168\3\2\2\2\u016b\u016c\b\67\2\2"+
		"\u016cn\3\2\2\2\f\2\u011f\u0125\u012e\u0136\u0140\u0142\u0150\u015a\u0168"+
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