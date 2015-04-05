#include "card.h"
#include <stdio.h>

const char* Card::DATABASE = "cards.db";
static int func(void* priv, int i, char** a, char** b) {
    printf("Hello from callback\n");
    printf("%s\n%s\n", a[0], b[0]);
    return 0;
}


Card::Card(int id)
{
    int ret;
    sqlite3_open(Card::DATABASE, &conn);
    printf("Hi from card.\n");
    ret = sqlite3_exec(conn, "select * from Cards where Id = 1;", func, NULL, NULL);
    if (ret < 0)
        printf("shit's fucked yo.\n");
    if (ret >= 0)
        printf("where mah callback at?\n");
}

Card::~Card()
{

}

