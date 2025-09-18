#include <stdio.h>

int main(int argc, char *argv[])
{
  FILE *fp;
  long nc;  // character count
  long nl;  // newline count
  long nw;  // word count
  int c;    // current character
  int in_word = 0; // Flag to track if we're in a word

  // Check if filename was provided as command line argument
  if (argc != 2) {
    printf("Error: Invalid number of arguments\n");
    printf("Usage: %s <filename>\n", argv[0]);
    return 1;
  }

  // Try to open the file
  fp = fopen(argv[1], "r");
  if (fp == NULL) {
    printf("Error: Cannot open file '%s'\n", argv[1]);
    return 1;
  }

  nc = nl = nw = 0;
  while ((c = fgetc(fp)) != EOF) {
    ++nc; // Count each character
    
    if (c == '\n')
      ++nl; // Count newlines
    
    // Word counting logic
    if (c == ' ' || c == '\n' || c == '\t') {
      // If we were in a word and hit whitespace, we're at the end of a word
      if (in_word) {
        in_word = 0;
        ++nw;
      }
    } else if (!in_word) {
      // If we weren't in a word and hit a non-whitespace, we're at the start of a word
      in_word = 1;
    }
  }
  
  // If the file doesn't end with whitespace and we were in a word, count the last word
  if (in_word)
    ++nw;
    
  printf("Characters: %ld\nLines: %ld\nWords: %ld\n", nc, nl, nw);

  // Close the file
  fclose(fp);

  return 0;
}