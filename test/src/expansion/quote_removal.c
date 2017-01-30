#include "expansion.h"
#include "criterion/criterion.h"

TestSuite(QuoteRemoval);

//#define CHECK(A, B) check_exp(A, B, sizeof(A))

#define CHECK(A, B) {											\
		char const *out = expand_quote_removal(A, sizeof(A));	\
		cr_assert_str_eq(out, B);								\
		free((void *)out);}

Test(QuoteRemoval, BackslashedBackslash) {
/* in  : \ \\ \\\
** out :  \ \
*/ CHECK("\\ \\\\ \\\\\\", " \\ \\"); }

Test(QuoteRemoval, EmptyQuotes) {
/* in  : '' ""
** out : 
*/ CHECK("\'\' \"\"", " "); }

Test(QuoteRemoval, SingleBackslash) {
/* in  : \
** out : 
*/ CHECK("\\", ""); }

Test(QuoteRemoval, UnterminatedQuotes) {
/* in  : "
** out : 
*/ CHECK("\"", "");
/* in  : '
** out : 
*/ CHECK("\'", ""); }

Test(QuoteRemoval, QuotedBackslashes) {
/* in  : '\'
** out : \
*/ CHECK("'\\'", "\\");
/* in  : "\"
** out : "
*/ CHECK("\"\\\"", "\"");
/* in  : "\\"
** out : \
*/ CHECK("\"\\\\\"", "\\"); }

Test(QuoteRemoval, QuotedQuotes) {
/* in  : "'"
** out : '
*/ CHECK("\"'\"", "'");
/* in  : '"'
** out : "
*/ CHECK("'\"'", "\""); }

Test(QuoteRemoval, QuotedBackslashedQuotesAndBacklashedQuotedBackslashes) {
/* in  : """"''''\'\"'"\'"\""\\\
** out : '""\"\
*/ CHECK("\"\"\"\"''''\\'\\\"'\"\\'\"\\\"\"\\\\\\",
		 "'\"\"\\\"\\"); }

Test(QuoteRemoval, RealisticTest) {
/* in  : Enlarged you\'re penis for '$'100\\month with "$SOMEBRAND's" new product \!
** out : Enlarged you're penis for $100\month with $SOMEBRAND's new product !
*/ CHECK("Enlarged you\\'re penis for '$'100\\\\month with \"$SOMEBRAND's\" new product \\!",
		 "Enlarged you're penis for $100\\month with $SOMEBRAND's new product !"); }
