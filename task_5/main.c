#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int LOGIN_MAX_LEN = 256;
const int LINE_MAX_LEN = 1024;
const char *PATTERN = "^([^:]*):[^:]*:[^:]*:[^:]*:([^,:]*)";

int main() {
  char login[LOGIN_MAX_LEN];

  if (scanf("%s", login) != 1) {
    printf("failed to read login");
    return 0;
  }

  regex_t regex;
  if (regcomp(&regex, PATTERN, REG_EXTENDED) != 0) {
    printf("failed to compile regex");
    return 0;
  }

  FILE *file = fopen("/etc/passwd", "r");
  if (file == NULL) {
    printf("failed to open /etc/passwd file");
    return 0;
  }

  char line[LINE_MAX_LEN];
  while (fgets(line, LINE_MAX_LEN, file) != NULL) {
    regmatch_t matches[3];
    if (regexec(&regex, line, 3, matches, 0) != 0) {
      printf("failed to execute regex matching");
      return 0;
    }

    char login_from_file[matches[1].rm_eo - matches[1].rm_so + 1];
    memcpy(login_from_file, line + matches[1].rm_so,
           matches[1].rm_eo - matches[1].rm_so);
    login_from_file[matches[1].rm_eo - matches[1].rm_so] = '\0';

    char name[matches[2].rm_eo - matches[2].rm_so + 1];
    memcpy(name, line + matches[2].rm_so, matches[2].rm_eo - matches[2].rm_so);
    name[matches[2].rm_eo - matches[2].rm_so] = '\0';

    if (strcmp(login, login_from_file) == 0) {
      printf("%s", name);
      return 0;
    }
  }

  return 0;
}
