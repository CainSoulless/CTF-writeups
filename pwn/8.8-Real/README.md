# 8.8 Real 2022 - Brokenjar

Este challenge tiene tres formas de solucionarse, 
pero solo una es valida en caso de que no tengas acceso al binario, y este esté bajo alguna conexion.

Comenzamos ejecutando el binario para ver de que trata. En este caso ilustra un menu con 6 opcines a elegir: \
![Menu](images/menu.png "Menu")

Al crear un usuario nos pregunta tres cosas, un index, un amaño y un username.
El index es para crear una lista de varios usuarios, cada uno con sus contraseñas pertenecientes, el username no es mas que un string simple, pero pedir el tamaño es algo sospechoso.


Si deduciste bien puedes intuir que el tamaño es la cantidad de bytes que pasaran de tu string username a la memoria, ojo con esto.

Hagamos un poco de ingeneria reversa, veamos que hay en el main:
```
int main(void)

{
  long in_FS_OFFSET;
  int menu;
  undefined8 local_10;
  
  local_10 = *(undefined8 *)(in_FS_OFFSET + 0x28);
  setbuf(stdin,(char *)0x0);
  setbuf(stdout,(char *)0x0);
  setbuf(stderr,(char *)0x0);
  do {
                    /* WARNING: This code block may not be properly labeled as switch case */
    menu = 0;
    puts("U-jar");
    puts("1. add user");
    puts("2. add password");
    puts("3. read users and passwords");
    puts("4. delete users and passwords");
    puts("5. superb admin login");
    puts("6. exit");
    printf(">>> ");
    scanf("%d",&menu);
                    /* WARNING: Could not find normalized switch variable to match jumptable */
  } while( true );
}

```

Muy probablemente no te aparecera al 100% de como aparece ahi, ya que cambié algunas instrucciones para que fuera mas legible.

Nos damos cuenta que tenemos un switch-case que se dirigue a otras funciones, segun la opcion del usuario. Veamos que tiene la función ```add_user()```

## add_user()


```
void add_user(void)

{
  uint uVar1;
  int is_equal;
  char *pcVar2;
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
      pcVar2 = (char *)malloc((ulong)size);
      buffer[uVar1].username = pcVar2;
      buffer[idx_candidate].size_user = (ulong)size;
      printf("username: ");
      read(0,buffer[idx_candidate].username,buffer[idx_candidate].size_user);
      is_equal = strcmp(buffer[idx_candidate].username,"root");
      if (is_equal == 0) {
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
```

Esta funcion pide que el index del username (```idx_cantidate```) no sea mayor a 5 o que tampoco tenga mas de 20 caracteres (20 bytes) de largo. Posterior a eso, guarda el string segun la cantidad de bytes dados por el usuario. \
Mas abajo tenemos algo interesante ya que se la funcion strcmp para comparar el string dado por el usuario con otro que dice "root", en caso de que estos sean iguales se retornaria 0, para luego llamar un syscall de exit en caso de que esto sea asi. \
Podemos deducir que el string "root" es importante para este challenge, pero sigamos viendo que mas hay en el binario. 