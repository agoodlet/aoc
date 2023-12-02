#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int part1(char *string) {
  int first = -1;
  int last;
  
  for (char character = *string; character != '\0'; character = *++string) {
    if (isdigit(character)) {       
      if (first == -1) {
        first = character;
        last = character;
      } else {
        last = character;
      }
    }
  }

  char final[2] = {first, last};
  char *end;
  // idk why but some of my string here were 3 chars long so if it's longer than 2 chars just kill it 
  if (strlen(final) > 2) {
    final[2] = '\0';
  }
  int finalNum = strtol(final, &end, 10);

  return finalNum;
}

int findIndex(char search, char *string) {
  char *e;
  int index;

  e = strchr(string, search);
  index = (int)(e - string);

  return index;
}

int part2(char *string1, char *string2) {

  char origString1[strlen(string1)];
  char origString2[strlen(string2)];

  strcpy(origString1, string1);
  strcpy(origString2, string2);

  int test = part1(string1);
  int test2 = part1(string2);


  int firstIndex1 = findIndex((test/10) + '0', origString1);
  int firstIndex2 = findIndex((test2/10) + '0', origString2);

  int lastIndex1 = findIndex((test%10) + '0', origString1);
  int lastIndex2 = findIndex((test2%10) + '0', origString2);

  int finalFirst;
  if (firstIndex1 < firstIndex2) {
    finalFirst = test/10;
  } else {
    finalFirst = test2/10;
  }

  int finalLast;
  if (lastIndex1 < lastIndex2) {
    finalLast = test2%10;
  } else {
    finalLast = test%10;
  }

  char final[2] = {(finalFirst + '0'), (finalLast + '0')};
  char *end;

  int finalNum = strtol(final, &end, 10);
 

  return finalNum;
}

void replaceSubstring(char *str, char *oldSubstr, char *newSubstr) {
    char *pos = strstr(str, oldSubstr);
    int oldLen = strlen(oldSubstr);
    int newLen = strlen(newSubstr);

    while (pos != NULL) {
        memmove(pos + newLen, pos + oldLen, strlen(pos + oldLen) + 1);
        memcpy(pos, newSubstr, newLen);
        pos = strstr(pos + newLen, oldSubstr);
    }
}

int parse(char *string) {
  char checks[9][6] = {
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
  };

  char string1[strlen(string) + 1];
  char string2[strlen(string) + 1]; 
  strcpy(string1, string);
  strcpy(string2, string);

  for (int i = 0; i < 9; i++) {
    char buffer[2];  
    buffer[0] = (char)(i + 1) + '0';
    buffer[1] = '\0';  
    char *new = buffer;
    replaceSubstring(string1, checks[i], new);
  }

  for (int i = 8; i >= 0; i--) {
    char buffer[2];  
    buffer[0] = (char)(i + 1) + '0';
    buffer[1] = '\0';  
    char *new = buffer;
    // printf("%s -- %s\n", new, checks[i]);
    replaceSubstring(string2, checks[i], new);
  }
  return part2(string1, string2);
}


int main() {
  
  FILE *fp;
  char input[255];
  int total = 0;

  fp = fopen("input.txt", "r");

  while (fgets(input, sizeof(input), fp)) {
    // PART 2
    int num = parse(input);
    // PART 1
    // int num = part1(input);  
    printf("%d\n", num);
    total += num;
  }

  printf("%d\n", total);

  fclose(fp);

}
