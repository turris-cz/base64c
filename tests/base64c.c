/* Copyright (c) 2020 CZ.NIC z.s.p.o. (http://www.nic.cz/)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <base64c.h>


const char *b64_valid[] = {
	"", // Empty string is valid in sense of empty output
	"abcd",
	"z4a=",
	"ZX8==",
	"==",
};

START_TEST(valid_valids) {
	ck_assert(!base64_str_verify(b64_valid[_i]));
}
END_TEST


struct b64_invalid {
	const char *str;
	size_t error;
} b64_invalid[] = {
	{"=", 1},
	{"a", 1},
	{"z", 1},
	{"/", 1},
	{"aa+\\aa", 4},
};

START_TEST(valid_invalids) {
	const char *str = b64_invalid[_i].str;
	ck_assert_int_eq(b64_invalid[_i].error, base64_verify(str, strlen(str)));
}
END_TEST


struct decode_length_d {
	const char *str;
	size_t len;
} decode_length_d[] = {
	{"aaaa", 3},
	{"aaaaxxxx", 6},
	{"aaaaxx==", 4},
	{"aaaaxxx=", 5},
	{"aaaaxx", 4},
	{"aaaaxxx", 5},
};

START_TEST(decode_len_f) {
	ck_assert_int_eq(decode_length_d[_i].len, base64_str_decode_len(decode_length_d[_i].str));
}
END_TEST


struct decode_d {
	const char *str;
	const uint8_t *data;
	size_t len;
} decode_d[] = {
	{"SGVsbG8K", (uint8_t*)"Hello\n", 6},
	{"SGVsbG8gV29ybGQhCg==", (uint8_t*)"Hello World!\n", 13},
	{"SGVsbG8gV29ybGQhCg", (uint8_t*)"Hello World!\n", 13},
};

START_TEST(decode_f) {
	uint8_t *data;
	size_t len = base64_str_mdecode(decode_d[_i].str, &data);
	ck_assert_int_eq(decode_d[_i].len, len);
	ck_assert_mem_eq(decode_d[_i].data, data, len);
	free(data);
}
END_TEST


struct d_encode_length {
	size_t in_len;
	size_t out_len;
} d_encode_length[] = {
	{0, 1},
	{1, 5},
	{3, 5},
	{4, 9},
	{6, 9},
	{7, 13},
	{8, 13},
	{9, 13},
	{10, 17},
};

START_TEST(encode_len_f) {
	ck_assert_int_eq(d_encode_length[_i].out_len, base64_encode_len(d_encode_length[_i].in_len));
}
END_TEST


struct encode_d {
	const uint8_t *data;
	size_t len;
	const char *str;
	size_t str_len;
} encode_d[] = {
	{(uint8_t*)"Hello\n", 6, "SGVsbG8K", 8},
	//{(uint8_t*)"Hello World!\n", 13, "jGVsbG8gV29ybGQhCg==", 20},
};


START_TEST(encode_f) {
	char *str;
	size_t len = base64_mencode(encode_d[_i].data, encode_d[_i].len, &str);
	ck_assert_int_eq(encode_d[_i].str_len, len);
	ck_assert_str_eq(encode_d[_i].str, str);
	free(str);
}
END_TEST


void base64c_tests(Suite *suite) {
	TCase *valid = tcase_create("base64_valid");
	tcase_add_loop_test(valid, valid_valids, 0, sizeof(b64_valid) / sizeof(char*));
	tcase_add_loop_test(valid, valid_invalids, 0, sizeof(b64_invalid) / sizeof(struct b64_invalid));
	suite_add_tcase(suite, valid);

	TCase *decode_len = tcase_create("base64_decode_len");
	tcase_add_loop_test(decode_len, decode_len_f, 0, sizeof(decode_length_d) / sizeof(struct decode_length_d));
	suite_add_tcase(suite, decode_len);

	TCase *decode = tcase_create("base64_decode");
	tcase_add_loop_test(decode, decode_f, 0, sizeof(decode_d) / sizeof(struct decode_d));
	suite_add_tcase(suite, decode);

	TCase *encode_len = tcase_create("base64_encode_len");
	tcase_add_loop_test(encode_len, encode_len_f, 0, sizeof(d_encode_length) / sizeof(struct d_encode_length));
	suite_add_tcase(suite, encode_len);

	TCase *encode = tcase_create("base64_encode");
	tcase_add_loop_test(encode, encode_f, 0, sizeof(encode_d) / sizeof(struct encode_d));
	suite_add_tcase(suite, encode);
}
