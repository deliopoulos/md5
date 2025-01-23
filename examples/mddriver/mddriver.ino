#ifdef __cplusplus
  #include "Arduino.h"
#endif

#define PROTOTYPES 1

#include <md5.h>

static void MDString PROTO_LIST((const char *));
static void MDTestSuite PROTO_LIST((void));
static void MDFilter PROTO_LIST((void));
static void MDPrint PROTO_LIST((unsigned char[16]));

void setup() {
  //initialize serial
  Serial.begin(115200);
  //give it a second
  delay(1000);
  MDTestSuite();
}

void loop() {
}


/* Digests a string and prints the result.
 */
static void MDString (const char *string)
{
  MD5_CTX context;
  unsigned char digest[16];
  unsigned int len = strlen(string);

  MD5Init(&context);
  MD5Update(&context, (unsigned char*)string, len);
  MD5Final(digest, &context);

  printf("MD5 (\"%s\") = ", string);
  MDPrint(digest);
  printf("\n");
}

/* Digests a reference suite of strings and prints the results.
 */
static void MDTestSuite(void)
{
  printf ("MD5 test suite:\n");

  MDString("");
  MDString("a");
  MDString("abc");
  MDString("message digest");
  MDString("abcdefghijklmnopqrstuvwxyz");
  MDString("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
  MDString("12345678901234567890123456789012345678901234567890123456789012345678901234567890");
}

/* Digests the standard input and prints the result.
 */
static void MDFilter(void)
{
  MD5_CTX context;
  int len;
  unsigned char buffer[16], digest[16];

  MD5Init (&context);
  while ((len = fread (buffer, 1, 16, stdin)))
    MD5Update(&context, buffer, len);
  MD5Final(digest, &context);

  MDPrint(digest);
  printf("\n");
}

/* Prints a message digest in hexadecimal.
 */
static void MDPrint(unsigned char digest[16])
{
  unsigned int i;

  for (i = 0; i < 16; i++)
    printf ("%02x", digest[i]);
}