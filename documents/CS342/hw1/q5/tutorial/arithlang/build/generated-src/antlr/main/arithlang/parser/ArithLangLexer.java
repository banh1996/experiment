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
		T__0=1, T__1=2, T__2=3, T__3=4, Define=5, Let=6, Dot=7, Number=8, Identifier=9, 
		Letter=10, LetterOrDigit=11, AT=12, ELLIPSIS=13, WS=14, Comment=15, Line_Comment=16;
	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	public static final String[] ruleNames = {
		"T__0", "T__1", "T__2", "T__3", "Define", "Let", "Dot", "Number", "Identifier", 
		"Letter", "LetterOrDigit", "DIGIT", "AT", "ELLIPSIS", "WS", "Comment", 
		"Line_Comment"
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
		case 9:
			return Letter_sempred((RuleContext)_localctx, predIndex);
		case 10:
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
		"\3\u0430\ud6d1\u8206\uad2d\u4417\uaef1\u8d80\uaadd\2\22~\b\1\4\2\t\2\4"+
		"\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13\t"+
		"\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\3\2\3\2\3\3\3\3\3\4\3\4\3\5\3\5\3\6\3\6\3\6\3\6\3\6\3\6\3\6\3\7\3\7\3"+
		"\7\3\7\3\b\3\b\3\t\6\t<\n\t\r\t\16\t=\3\n\3\n\7\nB\n\n\f\n\16\nE\13\n"+
		"\3\13\3\13\3\13\3\13\3\13\3\13\5\13M\n\13\3\f\3\f\3\f\3\f\3\f\3\f\5\f"+
		"U\n\f\3\r\3\r\3\16\3\16\3\17\3\17\3\17\3\17\3\20\6\20`\n\20\r\20\16\20"+
		"a\3\20\3\20\3\21\3\21\3\21\3\21\7\21j\n\21\f\21\16\21m\13\21\3\21\3\21"+
		"\3\21\3\21\3\21\3\22\3\22\3\22\3\22\7\22x\n\22\f\22\16\22{\13\22\3\22"+
		"\3\22\3k\2\23\3\3\5\4\7\5\t\6\13\7\r\b\17\t\21\n\23\13\25\f\27\r\31\2"+
		"\33\16\35\17\37\20!\21#\22\3\2\t\6\2&&C\\aac|\4\2\2\u0101\ud802\udc01"+
		"\3\2\ud802\udc01\3\2\udc02\ue001\7\2&&\62;C\\aac|\5\2\13\f\16\17\"\"\4"+
		"\2\f\f\17\17\u0085\2\3\3\2\2\2\2\5\3\2\2\2\2\7\3\2\2\2\2\t\3\2\2\2\2\13"+
		"\3\2\2\2\2\r\3\2\2\2\2\17\3\2\2\2\2\21\3\2\2\2\2\23\3\2\2\2\2\25\3\2\2"+
		"\2\2\27\3\2\2\2\2\33\3\2\2\2\2\35\3\2\2\2\2\37\3\2\2\2\2!\3\2\2\2\2#\3"+
		"\2\2\2\3%\3\2\2\2\5\'\3\2\2\2\7)\3\2\2\2\t+\3\2\2\2\13-\3\2\2\2\r\64\3"+
		"\2\2\2\178\3\2\2\2\21;\3\2\2\2\23?\3\2\2\2\25L\3\2\2\2\27T\3\2\2\2\31"+
		"V\3\2\2\2\33X\3\2\2\2\35Z\3\2\2\2\37_\3\2\2\2!e\3\2\2\2#s\3\2\2\2%&\7"+
		"/\2\2&\4\3\2\2\2\'(\7*\2\2(\6\3\2\2\2)*\7-\2\2*\b\3\2\2\2+,\7+\2\2,\n"+
		"\3\2\2\2-.\7f\2\2./\7g\2\2/\60\7h\2\2\60\61\7k\2\2\61\62\7p\2\2\62\63"+
		"\7g\2\2\63\f\3\2\2\2\64\65\7n\2\2\65\66\7g\2\2\66\67\7v\2\2\67\16\3\2"+
		"\2\289\7\60\2\29\20\3\2\2\2:<\5\31\r\2;:\3\2\2\2<=\3\2\2\2=;\3\2\2\2="+
		">\3\2\2\2>\22\3\2\2\2?C\5\25\13\2@B\5\27\f\2A@\3\2\2\2BE\3\2\2\2CA\3\2"+
		"\2\2CD\3\2\2\2D\24\3\2\2\2EC\3\2\2\2FM\t\2\2\2GH\n\3\2\2HM\6\13\2\2IJ"+
		"\t\4\2\2JK\t\5\2\2KM\6\13\3\2LF\3\2\2\2LG\3\2\2\2LI\3\2\2\2M\26\3\2\2"+
		"\2NU\t\6\2\2OP\n\3\2\2PU\6\f\4\2QR\t\4\2\2RS\t\5\2\2SU\6\f\5\2TN\3\2\2"+
		"\2TO\3\2\2\2TQ\3\2\2\2U\30\3\2\2\2VW\4\62;\2W\32\3\2\2\2XY\7B\2\2Y\34"+
		"\3\2\2\2Z[\7\60\2\2[\\\7\60\2\2\\]\7\60\2\2]\36\3\2\2\2^`\t\7\2\2_^\3"+
		"\2\2\2`a\3\2\2\2a_\3\2\2\2ab\3\2\2\2bc\3\2\2\2cd\b\20\2\2d \3\2\2\2ef"+
		"\7\61\2\2fg\7,\2\2gk\3\2\2\2hj\13\2\2\2ih\3\2\2\2jm\3\2\2\2kl\3\2\2\2"+
		"ki\3\2\2\2ln\3\2\2\2mk\3\2\2\2no\7,\2\2op\7\61\2\2pq\3\2\2\2qr\b\21\2"+
		"\2r\"\3\2\2\2st\7\61\2\2tu\7\61\2\2uy\3\2\2\2vx\n\b\2\2wv\3\2\2\2x{\3"+
		"\2\2\2yw\3\2\2\2yz\3\2\2\2z|\3\2\2\2{y\3\2\2\2|}\b\22\2\2}$\3\2\2\2\n"+
		"\2=CLTaky\3\b\2\2";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}