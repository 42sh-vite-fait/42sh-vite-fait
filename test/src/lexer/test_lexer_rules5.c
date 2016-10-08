#include "header.h"
#include "criterion/criterion.h"
#include "test_lexer_utils.c"

/*
 * If the current character is an unquoted '$' or '`',
 * the shell shall identify the start of any candidates for:
 *	parameter expansion ${...},
 *	command substitution $(...) `...`,
 *	or arithmetic expansion $((...)),
 * from their introductory unquoted character sequences:
 *	'$' or "${",
 *	"$(" or '`',
 *	and "$((",
 * respectively.
 * The shell shall read sufficient input to determine the end of the unit to
 * be expanded (as explained in the cited sections).
 * While processing the characters, if instances of expansions or
 * quoting are found nested within the substitution,
 * the shell shall recursively process them in the manner specified
 * for the construct that is found.
 * The characters found from the beginning of the substitution to its end,
 * allowing for any recursion necessary to recognize embedded constructs,
 * shall be included unmodified in the result token,
 * including any embedded or enclosing substitution operators or quotes.
 * The token shall not be delimited by the end of the substitution.
 */

TestSuite(LexerRules5, .init = setup, .fini = teardown);

Test(LexerRules5, BadWordExpansion)
{
	test_lexer("$[ $} $)", LEXER_INPUT_COMPLETE, 4);

	test_token(E_TOKEN_WORD, 0, 2, "$[");
	test_token(E_TOKEN_WORD, 3, 2, "$}");
	test_token(E_TOKEN_WORD, 6, 1, "$");
	test_token(E_TOKEN_RPAREN, 7, 1, ")");
}

Test(LexerRules5, SimpleExpansion)
{
	test_lexer("${parameter} 0${a b c d}1 ${a'b'\nc'd'e }", LEXER_INPUT_COMPLETE, 3);

	test_token(E_TOKEN_WORD, 0, 12, "${parameter}");
	test_token(E_TOKEN_WORD, 13, 12, "0${a b c d}1");
	test_token(E_TOKEN_WORD, 26, 14, "${a'b'\nc'd'e }");
}

Test(LexerRules5, ParameterExpansionWithoutCurlyBraces)
{
	test_lexer("$parameter $a/$b $c\n$d", LEXER_INPUT_COMPLETE, 5);

	test_token(E_TOKEN_WORD, 0, 10, "$parameter");
	test_token(E_TOKEN_WORD, 11, 5, "$a/$b");
	test_token(E_TOKEN_WORD, 17, 2, "$c");
	test_token(E_TOKEN_NEWLINE, 19, 1, "\n");
	test_token(E_TOKEN_WORD, 20, 2, "$d");
}

Test(LexerRules5, EscapedCurlyBrace)
{
	test_lexer("${\\}}${'}'}${\"}\"}", LEXER_INPUT_COMPLETE, 1);

	test_token(E_TOKEN_WORD, 0, 17, "${\\}}${'}'}${\"}\"}");
}

Test(LexerRules5, ClosingCurlyBraceInExpansion)
{
	test_lexer("${$(})} ${$((}))} ${`}`} ${${a}}", LEXER_INPUT_COMPLETE, 4);

	test_token(E_TOKEN_WORD, 0, 7, "${$(})}");
	test_token(E_TOKEN_WORD, 8, 9, "${$((}))}");
	test_token(E_TOKEN_WORD, 18, 6, "${`}`}");
	test_token(E_TOKEN_WORD, 25, 7, "${${a}}");
}

Test(LexerRules5, ParameterExpansionDefaultValue)
{
	test_lexer("${p:-word}${p-word}", LEXER_INPUT_COMPLETE, 1);

	test_token(E_TOKEN_WORD, 0, 19, "${p:-word}${p-word}");
}

Test(LexerRules5, ParameterExpansionAssignValue)
{
	test_lexer("${p:=word}${p=word}", LEXER_INPUT_COMPLETE, 1);

	test_token(E_TOKEN_WORD, 0, 19, "${p:=word}${p=word}");
}

Test(LexerRules5, ParameterExpansionPrintError)
{
	test_lexer("${p:?word}${p?word}", LEXER_INPUT_COMPLETE, 1);

	test_token(E_TOKEN_WORD, 0, 19, "${p:?word}${p?word}");
}

Test(LexerRules5, ParameterExpansionAlternateValue)
{
	test_lexer("${p:+word}${p+word}", LEXER_INPUT_COMPLETE, 1);

	test_token(E_TOKEN_WORD, 0, 19, "${p:+word}${p+word}");
}

Test(LexerRules5, ParameterExpansionLength)
{
	test_lexer("${#p}", LEXER_INPUT_COMPLETE, 1);

	test_token(E_TOKEN_WORD, 0, 5, "${#p}");
}

Test(LexerRules5, ParameterExpansionRemovePattern)
{
	test_lexer("${p%%word} ${p%word} ${p#word} ${p##word}", LEXER_INPUT_COMPLETE, 4);

	test_token(E_TOKEN_WORD, 0, 10, "${p%%word}");
	test_token(E_TOKEN_WORD, 11, 9, "${p%word}");
	test_token(E_TOKEN_WORD, 21, 9, "${p#ord}");
	test_token(E_TOKEN_WORD, 31, 10, "${p##word}");
}

Test(LexerRules5, ParameterExpansionNested)
{
	test_lexer("echo ${a:?$(echo 'merde'$(($1 + 1)))}", LEXER_INPUT_COMPLETE, 2);

	test_token(E_TOKEN_WORD, 0, 4, "echo");
	test_token(E_TOKEN_WORD, 5, 32, "${a:?$(echo 'merde'$(($1 + 1)))}");
}

Test(LexerRules5, SimpleCommandSubstitution)
{
	test_lexer("$( ls -a )`a>2` 0$(a\nb)c", LEXER_INPUT_COMPLETE, 2);

	test_token(E_TOKEN_WORD, 0, 15, "$( ls -a )`a>2`");
	test_token(E_TOKEN_WORD, 16, 8, "0$(a\nb)c");
}

Test(LexerRules5, CommandSubstitutionBackquoteQuoted)
{
	test_lexer("`a\\`b` `\\$` `\\\\`", LEXER_INPUT_COMPLETE, 3);
	// [a`b] [$] [\]

	test_token(E_TOKEN_WORD, 0, 6, "`a\\`b`");
	test_token(E_TOKEN_WORD, 7, 4, "`\\$`");
	test_token(E_TOKEN_WORD, 12, 4, "`\\\\`");
}

Test(LexerRules5, CommandSubstitutionNestedParen)
{
	test_lexer("b$(`012`$(${zzz}$($(a)\\)')'\")\")b))", LEXER_INPUT_COMPLETE, 1);

	test_token(E_TOKEN_WORD, 0, 34, "b$(`012`$(${zzz}$($(a)\\)')'\")\")b))");
}

Test(LexerRules5, CommandSubstitutionNestedBackquote)
{
	test_lexer("a `ls \\`echo ${a}\\`>/dev/null` b", LEXER_INPUT_COMPLETE, 3);

	test_token(E_TOKEN_WORD, 0, 1, "a");
	test_token(E_TOKEN_WORD, 2, 28, "`ls \\`echo ${a}\\`>/dev/null`");
	test_token(E_TOKEN_WORD, 31, 1, "b");
}

/*
 * The syntax of the shell command language has an ambiguity for expansions beginning with "$((",
 * which can introduce an arithmetic expansion or a command substitution that starts with a subshell.
 * Arithmetic expansion has precedence; that is,
 * the shell shall first determine whether it can parse the expansion as an arithmetic expansion
 * and shall only parse the expansion as a command substitution if it determines that it cannot
 * parse the expansion as an arithmetic expansion.
 * The shell need not evaluate nested expansions when performing this determination.
 * If it encounters the end of input without already having determined that it cannot parse the expansion as an arithmetic expansion,
 * the shell shall treat the expansion as an incomplete arithmetic expansion and report a syntax error.
 * A conforming application shall ensure that it separates the "$(" and '(' into two tokens (that is,
 * separate them with white space) in a command substitution that starts with a subshell.
 * For example, a command substitution containing a single subshell could be written as: $( (command) )
 */

Test(LexerRules5, ArithmeticExpansion)
{
	test_lexer("$((1 + 1)) $(( \\) 2 + 2)) $( ( 3+3 ))", LEXER_INPUT_COMPLETE, 3);

	test_token(E_TOKEN_WORD, 0, 10, "$((1 + 1))");
	test_token(E_TOKEN_WORD, 11, 14, "$(( \\) 2 + 2))");
	test_token(E_TOKEN_WORD, 26, 11, "$( ( 3+3 ))");
}

Test(LexerRules5, ArithmeticExpansionNewline)
{
	test_lexer("$((1+\n", LEXER_INPUT_INCOMPLETE, 0);
	/* test_token(E_TOKEN_WORD, 0, 7, "$((1+\n"); */

	test_lexer("1))", LEXER_INPUT_COMPLETE, 1);
	test_token(E_TOKEN_WORD, 0, 9, "$((1+\n1))");
}
