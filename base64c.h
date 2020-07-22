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
#ifndef _BASE64C_H_
#define _BASE64C_H_
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// Verifies that provided input string is validly encoded in base64 format
// input: string to be verified
// len: size of string (validating at most given number of bytes)
// Returns len if valid or index of first invalid character.
size_t base64_valid(const char *input, size_t len);

// Verify that provided input string is validly encoded in base64 format
// input: null terminated string to be verified
// Returns true if valid and false otherwise
bool base64_str_valid(const char *input);

// This function provides you with exact size of decoded output. Use this function
// to allocate memory for output of base64c_decode.
// input: string encoded in base64
// len: size of string (using at most given number of bytes)
// Returns required buffer size to fit decoded result.
size_t base64_decode_len(const char *input, size_t len);

// base64_decode_len variant that uses strlen to get size of input.
size_t base64_str_decode_len(const char *input);

// Decode base64 encoded string.
// input: string encoded in base64 to be decoded
// len: length of input string
// output: point to allocated memory with enough space to store decoded output.
//   You can use base64_decode_len function to get appropriate size.
// Returns number of bytes actually decoded from string.
size_t base64_decode(const char *input, size_t len, uint8_t *output);

// base64_decode variant that uses strlen to get size of input.
size_t base64_str_decode(const char *input, uint8_t *output);

// base64_decode variant that allocates appropriately sized buffer with malloc.
// output: where pointer to output is going to be stored. It is caller's
//   responsibility to free *output. *output can be set to NULL if no output is
//   produced (decode of zero sized input), this depends on malloc implementation.
size_t base64_mdecode(const char *input, size_t len, uint8_t **output);

// base64_str_decode and base64_mdecode variant of base64_decode combining both to
// convenient single function.
size_t base64_str_mdecode(const char *input, uint8_t **output);

// This function provides you with exact size of encoded output. Use this function
// to allocate memory for output of base64c_encode.
// len: size of expected input in bytes
// Returns required buffer size to fit encoded result (including terminating null
// byte).
size_t base64_encode_len(size_t len);

// Encode data to base64 encoded string
// input: input data to be encoded
// len: size of input data in bytes
// output: pointer to allocated memory with enough space to store encoded string
//   plus one byte for terminating null byte. You can use base64_encode_len to get
//   appropriate size.
// Returns number of characters actually written to output (that is without null
// byte).
size_t base64_encode(const uint8_t *input, size_t len, char *output);

// base64_encode variant that allocates appropriately sized buffer with malloc.
// output: where pointer to output is going to be stored. It is caller's
//   responsibility to free *output.
size_t base64_mencode(const uint8_t *input, size_t len, char **output);

#endif
