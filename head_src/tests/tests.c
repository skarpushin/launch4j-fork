/*
 Launch4j (http://launch4j.sourceforge.net/)
 Cross-platform Java application wrapper for creating Windows native executables.

 Copyright (c) 2004, 2015 Grzegorz Kowal
 Sergey Karpushin (java9+ version schema)

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 Except as contained in this notice, the name(s) of the above copyright holders
 shall not be used in advertising or otherwise to promote the sale, use or other
 dealings in this Software without prior written authorization.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

/*
 INSTRUCTIONS:
 - Make sure to run eclipse as an administrator, otherwise you'll see error:
 "munit unable to create buffer for stderr: Permission denied (13)"
 */

#include "../resource.h"
#include "../head.h"
#include "tests.h"
#include "munit.h"

static MunitResult expectJava8VerWithoutUpdatePartParseCorrectly(
		const MunitParameter params[], void* data) {
	char result[20];
	formatJavaVersion(result, "1.8.0");

	munit_assert_string_equal("1.008.000", result);
	return MUNIT_OK;
}

static MunitResult expectJava8VerWithUpdatePart2digitsParsedCorrectly(
		const MunitParameter params[], void* data) {
	char result[20];
	formatJavaVersion(result, "1.8.0_45");

	munit_assert_string_equal("1.008.000_045", result);
	return MUNIT_OK;
}

static MunitResult expectJava8VerWithUpdatePart3digitsParsedCorrectly(
		const MunitParameter params[], void* data) {
	char result[20];
	formatJavaVersion(result, "1.8.0_151");

	munit_assert_string_equal("1.008.000_151", result);
	return MUNIT_OK;
}

static MunitResult expectEmptyVersionStringWillStayEmpty(
		const MunitParameter params[], void* data) {
	char result[20];
	formatJavaVersion(result, "");

	munit_assert_string_equal("", result);
	return MUNIT_OK;
}

static MunitResult expectJava9Ver1PartParseCorrectly(
		const MunitParameter params[], void* data) {
	char result[20];
	formatJavaVersion(result, "9");

	munit_assert_string_equal("1.009.000", result);
	return MUNIT_OK;
}

static MunitResult expectJava9Ver2PartsParseCorrectly(
		const MunitParameter params[], void* data) {
	char result[20];
	formatJavaVersion(result, "9.34");

	munit_assert_string_equal("1.009.034", result);
	return MUNIT_OK;
}

static MunitResult expectJava9Ver4PlusPartsIgnored(
		const MunitParameter params[], void* data) {
	char result[20];
	formatJavaVersion(result, "9.34.123.43.23.43");

	munit_assert_string_equal("1.009.034_123", result);
	return MUNIT_OK;
}

static MunitResult expectJava9Ver3Parts3digitsParseCorrectly(
		const MunitParameter params[], void* data) {
	char result[20];
	formatJavaVersion(result, "9.34.123");

	munit_assert_string_equal("1.009.034_123", result);
	return MUNIT_OK;
}

static MunitResult expectJava9Ver3Parts2digitsParseCorrectly(
		const MunitParameter params[], void* data) {
	char result[20];
	formatJavaVersion(result, "9.34.54");

	munit_assert_string_equal("1.009.034_054", result);
	return MUNIT_OK;
}

static MunitResult expectJava10CanBeParsedCorrectly(
		const MunitParameter params[], void* data) {
	char result[20];
	formatJavaVersion(result, "10.0.1");

	munit_assert_string_equal("1.010.000_001", result);
	return MUNIT_OK;
}

static MunitResult expectJava10CouldBeFoundInRegistry(
		const MunitParameter params[], void* data) {

	char javaMinVer[STR];
	search.runtimeBits = USE_32_AND_64_BIT_RUNTIME;
	BOOL result = findJavaHome(javaMinVer, PREFER_JRE);

	munit_assert_int(TRUE, ==, result);
	return MUNIT_OK;
}

static MunitTest test_suite_tests[] = { {
		(char*) "/regression/expectJava8VerWithoutUpdatePartParseCorrectly",
		expectJava8VerWithoutUpdatePartParseCorrectly,
		NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

{ (char*) "/regression/expectJava8VerWithUpdatePartParsedCorrectly",
		expectJava8VerWithUpdatePart2digitsParsedCorrectly,
		NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

{ (char*) "/regression/expectJava8VerWithUpdatePart3digitsParsedCorrectly",
		expectJava8VerWithUpdatePart3digitsParsedCorrectly,
		NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

{ (char*) "/regression/expectEmptyVersionStringWillStayEmpty",
		expectEmptyVersionStringWillStayEmpty,
		NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

{ (char*) "/java9/expectJava9Ver1PartParseCorrectly",
		expectJava9Ver1PartParseCorrectly,
		NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

{ (char*) "/java9/expectJava9Ver2PartsParseCorrectly",
		expectJava9Ver2PartsParseCorrectly,
		NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

{ (char*) "/java9/expectJava9Ver3Parts2digitsParseCorrectly",
		expectJava9Ver3Parts2digitsParseCorrectly,
		NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

{ (char*) "/java9/expectJava9Ver3Parts3digitsParseCorrectly",
		expectJava9Ver3Parts3digitsParseCorrectly,
		NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

{ (char*) "/java9/expectJava9Ver4PlusPartsIgnored",
		expectJava9Ver4PlusPartsIgnored,
		NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

{ (char*) "/java9/expectJava10CanBeParsedCorrectly",
		expectJava10CanBeParsedCorrectly,
		NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

{ (char*) "/registry/expectJava10CouldBeFoundInRegistry",
		expectJava10CouldBeFoundInRegistry,
		NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },

{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL } };

static const MunitSuite test_suite = { (char*) "", test_suite_tests,
NULL, 1, MUNIT_SUITE_OPTION_NONE };

int APIENTRY
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,
		int nCmdShow) {

	return munit_suite_main(&test_suite, (void*) "µnit", 0, NULL);
}
