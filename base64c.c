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
#include <base64c.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


static bool is_valid_char(const char c) {
	return \
		(c >= '0' && c <= '9') || \
		(c >= 'A' && c <= 'Z') || \
		(c >= 'a' && c <= 'z') || \
		(c == '+' || c == '/');
}

static size_t padding(const char *input, size_t len) {
	return input[len - 1] == '=' ? (input[len - 2] == '=' ? 2 : 1) : 0;
}

size_t base64_valid(const char *input, size_t len) {
	if (len == 1)
		return 0; // One character is invalid not matter what character it is

	for (size_t i = 0; i < (len - padding(input, len)); i++)
		if (!is_valid_char(input[i]))
			return i;

	return len;
}

bool base64_str_valid(const char *input) {
	size_t len = strlen(input);
	if (len == 0) // Special case that is valid
		return true;
	return base64_valid(input, len);
}

size_t base64_decode_len(const char *input, size_t len) {
	return (len * 3 / 4) - padding(input, len);
}

size_t base64_str_decode_len(const char *input) {
	return base64_decode_len(input, strlen(input));
}

static uint32_t char2data(const char chr) {
	if (chr >= 'A' && chr <= 'Z')
		return chr - 'A';
	if (chr >= 'a' && chr <= 'z')
		return chr - 'a' + 26;
	if (chr >= '0' && chr <= '9')
		return chr + 4;
	if (chr == '+')
		return 62;
	if (chr == '/')
		return 63;
	// Anything else we consider for now as zero
	return 0;

}

size_t base64_decode(const char *input, size_t len, uint8_t *output) {
	uint32_t dt = 0;
	size_t j = 0;
	size_t real_len = len - padding(input, len);

	for (size_t i = 0; i < real_len; i++) {
		dt |= char2data(input[i]) << (6 * (3 - (i % 4)));
		if ((i + 1) % 4 == 0) {
			for (int f = 16; f >= 0; f -= 8)
				output[j++] = (dt >> f) & 0xff;
			dt = 0;
		}
	}

	int rem = real_len % 4;
	if (rem != 0)
		for (int f = 16; f >= (8 * (4 - rem)); f -= 8)
			output[j++] = (dt >> f) & 0xff;

	return j;
}

size_t base64_str_decode(const char *input, uint8_t *output) {
	return base64_decode(input, strlen(input), output);
}

size_t base64_mdecode(const char *input, size_t len, uint8_t **output) {
	*output = malloc(base64_decode_len(input, len));
	return base64_decode(input, len, *output);
}

size_t base64_str_mdecode(const char *input, uint8_t **output) {
	return base64_mdecode(input, strlen(input), output);
}

size_t base64_encode_len(size_t len) {
	return len / 3 * 4 + ((len % 3) ? 4 : 0) + 1;
}

const char b64char[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

size_t base64_encode(const uint8_t *input, size_t len, char *output) {
	uint32_t dt = 0;
	size_t j = 0;

	for (size_t i = 0; i < len; i++) {
		dt |= input[i] << (8 * (2 - (i % 3)));
		if ((i + 1) % 3 == 0) {
			for (int f = 18; f >= 0; f -= 6)
				output[j++] = b64char[(dt >> f) & 0x3f];
			dt = 0;
		}
	}

	int rem = len % 3;
	if (rem != 0)
		for (int f = 3; f >= 0; f--) {
			if (f >= (3 - rem))
				output[j++] = (dt >> (f * 6)) & 0x3f;
			else
				output[j++] = '=';
		}

	output[j] = '\0';
	return j;
}

size_t base64_mencode(const uint8_t *input, size_t len, char **output) {
	*output = malloc(base64_encode_len(len));
	return base64_encode(input, len, *output);
}
