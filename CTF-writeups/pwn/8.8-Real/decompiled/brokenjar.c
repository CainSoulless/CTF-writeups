#include <stdio.h>
#include <stdint.h>


void add_user(void)

{
  uint uVar1;
  int iVar2;
  char *pcVar3;
  long in_FS_OFFSET;
  uint idx_candidate;
  uint size;
  long local_20;
  
  local_20 = *(long *)(in_FS_OFFSET + 0x28);
  if (index_space < 5) {
    puts("idx:");
    scanf("%1u",&idx_candidate);
    puts("size: ");
    scanf("%4u",&size);
    uVar1 = idx_candidate;
    if (idx_candidate < 5) {
      if (0x20 < size) {
        puts("size must below or equal to 0x20");
                    /* WARNING: Subroutine does not return */
        exit(0);
      }
      pcVar3 = (char *)malloc((ulong)size);
      buffer[uVar1].username = pcVar3;
      buffer[idx_candidate].size_user = (ulong)size;
      printf("username: ");
      read(0,buffer[idx_candidate].username,buffer[idx_candidate].size_user);
      iVar2 = strcmp(buffer[idx_candidate].username,"root");
      if (iVar2 == 0) {
        puts("hehe not allowed");
                    /* WARNING: Subroutine does not return */
        exit(0);
      }
      index_space = index_space + 1;
      puts("added user");
    }
    else {
      puts("index must be smaller or equal to 4");
    }
  }
  else {
    puts("no more data please");
  }
  if (local_20 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}


void delete_user_and_password(void)

{
  long in_FS_OFFSET;
  uint candidate;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  puts("idx: ");
  scanf("%1u",&candidate);
  if (candidate < 5) {
    buffer[candidate].size_pass = 0;
    buffer[candidate].size_user = 0;
    free(buffer[candidate].username);
    free(buffer[candidate].password);
    puts("user deleted");
    index_space = index_space + -1;
  }
  else {
    puts("index must be smaller or equal to 9");
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}

void superb_admin(void)

{
  long lVar1;
  int iVar2;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  printf("your current user is: %s\n",buffer[0].username);
  iVar2 = strcmp(buffer[0].username,"root");
  if (iVar2 == 0) {
    puts("hello superb admin!");
    system("sh");
  }
  else {
    puts("you are not superb_admin");
  }
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}


void superb_admin(void)

{
  long lVar1;
  int iVar2;
  long in_FS_OFFSET;
  
  lVar1 = *(long *)(in_FS_OFFSET + 0x28);
  printf("your current user is: %s\n",buffer[0].username);
  iVar2 = strcmp(buffer[0].username,"root");
  if (iVar2 == 0) {
    puts("hello superb admin!");
    system("sh");
  }
  else {
    puts("you are not superb_admin");
  }
  if (lVar1 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}

void main(void)

{
  long in_FS_OFFSET;
  int option;
  undefined8 local_10;
  
  local_10 = *(undefined8 *)(in_FS_OFFSET + 0x28);
  setbuf(stdin,(char *)0x0);
  setbuf(stdout,(char *)0x0);
  setbuf(stderr,(char *)0x0);
  do {
    option = 0;
    puts("U-jar");
    puts("1. add user");
    puts("2. add password");
    puts("3. read users and passwords");
    puts("4. delete users and passwords");
    puts("5. superb admin login");
    puts("6. exit");
    printf(">>> ");
    scanf("%d",&option);
    switch(option) {
    case 1:
      add_user();
      break;
    case 2:
      add_password();
      break;
    case 3:
      show_everything();
      break;
    case 4:
      delete_user_and_password();
      break;
    case 5:
      superb_admin();
      break;
    case 6:
      puts("goodbye");
                    /* WARNING: Subroutine does not return */
      exit(0);
    }
  } while( true );
}

