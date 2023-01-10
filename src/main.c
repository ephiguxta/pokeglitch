#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "apply_patch.h"
#include "change_money.h"
#include "change_name.h"
#include "checksum.h"
#include "pokedex_seen_owned.h"

int main(int argc, char *argv[argc + 1]) {
  //  the first generation checksum is an 8 bit value
  unsigned char check;

  //  saving the path, so it doesn't always operate in argv
  char path_size = strlen(argv[1]);
  char save_path[32];

  //  copy argv[1] in the save_path
  strncpy(save_path, argv[1], path_size);

  //  the max letters that a player can have in their
  //  name is 7 bytes
  char test_name[8] = "testing";
  test_name[7] = '\0';

  change_name(argv[1], test_name);

  // max digits for money is 7
  char money[7] = "99999";
  money[6] = '\0';

  change_money(argv[1], money);

  // enabling Blastoise (index is 8) in pokédex seen
  pokedex_seen_owned(argv[1], Blastoise);

  check = checksum(save_path);
  printf("[%x]\n", check);

  //  the checksum value is inserted at the adress 0x3523
  apply_patch(save_path, check);

  // printf("%02hhx\n", check);

  return 0;
}
