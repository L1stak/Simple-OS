#include "../std.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>




unsigned long simple_hash(char* str) {
    unsigned long i = 0;
    for (int j=0; str[j]; j++)
        i += str[j];
    return i % 50000;
}

typedef struct dict     /* L1stak*/
{
    char* key;
    uint8_t value;
}dict;

// hash table :3

typedef struct HashTable
{
    
    dict** items;
    int size;
    int count;
} HashTable;

dict* create_item(char* key, uint8_t value){

    dict* dict_ptr = (dict*)malloc(sizeof(dict));
    dict_ptr->key = (char*)malloc(strlen(key) +1);
    dict_ptr->value = (uint8_t*)malloc(sizeof(unsigned char));
    dict_ptr->key = key;
    dict_ptr->value = value;
    
}

HashTable* create_table(int size)
{
     
    HashTable* table = (HashTable*) malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (dict**) calloc(table->size, sizeof(dict*));

    for (int i = 0; i < table->size; i++)
        table->items[i] = NULL;

    return table;
}

void free_item(dict* item)
{
    free(item->key);
    free(item->value);
    free(item);
}

void free_table(HashTable* table)
{
  for (int i = 0; i < table->size; i++)
    {
        dict* item = table->items[i];

        if (item != NULL)
            free_item(item);
    }

    free(table->items);
    free(table);
}
void ht_insert(HashTable* table, char* key, uint8_t value)
{

    dict* item = create_item(key,value);
     if (table->count == table->size)
    {
        terminalSetColor(VGA_COLOR_RED,VGA_COLOR_BLACK);
        print("Insert Error: Hash Table is full\n");
        free_item(item);
        return;
    }

     
    if (table->count == 0){

        table->items[simple_hash(key)] = item;
        table->count++;
    }
    else {
        
    table->items[simple_hash(key)] = item;
    table->count++;
    }
}

char* ht_search(HashTable* table, char* key)
{
    int index = simple_hash(key);
    dict* item = table->items[index];

     
    if (item != NULL)
    {
        if (strcmp(item->key, key) == 0)
            return item->value;
    }

    return NULL;
}
static uint32_t farpeekl(uint16_t sel, void* off)
{
    uint32_t ret;
    asm ( "push %%fs\n\t"
          "mov %1, %%fs\n\t"
          "mov %%fs:(%2), %0\n\t"
          "pop %%fs"
          : "=r"(ret) : "g"(sel), "r"(off) );
    return ret;

}

static void farpokeb(uint16_t sel, void* off, uint8_t v)
{
    asm ( "push %%fs\n\t"
          "mov %0, %%fs\n\t"
          "movb %2, %%fs:(%1)\n\t"
          "pop %%fs"
          : : "g"(sel), "r"(off), "r"(v) );
   
}

static void outb(uint16_t port, uint8_t val) // out asm
{
    __asm__ volatile ( "outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
    /* Существует кодировка outb %al, $ imm8, для постоянных номеров портов во время компиляции, которые помещаются в 8b. (Ограничение N).
 * Более широкие непосредственные константы будут усекаться во время сборки (например, ограничение «i»).
 * Кодировка outb %al, %dx является единственным вариантом для всех остальных случаев.
 * %1 расширяется до %dx, потому что порт является uint16_t. %w1 можно было бы использовать, если бы номер порта был более широким типом C */
}

static uint8_t inb(uint16_t port) // in  asm
{
    uint8_t ret;
    __asm__ volatile ( "inb %w1, %b0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}

static void io_wait(void) // sleep на пару микросекунд
{
    outb(0x80, 0);
}

static bool are_interrupts_enabled()
{
    unsigned long flags;
    asm volatile ( "pushf\n\t"
                   "pop %0"
                   : "=g"(flags) );
    return flags & (1 << 9);
}

// включение / отключение прерываний
static unsigned long save_irqdisable(void)
{
    unsigned long flags;
    asm volatile ("pushf\n\tcli\n\tpop %0" : "=r"(flags) : : "memory");
    return flags;
}

static void irqrestore(unsigned long flags)
{
    asm ("push %0\n\tpopf" : : "rm"(flags) : "memory","cc");
}

static void intended_usage(void)
{
    unsigned long f = save_irqdisable();
    do_whatever_without_irqs();
    irqrestore(f);
}

static uint64_t rdtsc() // считывает текущее значение счётчика временных меток процессора и сохранит его в EDX:EAX. 
{
    uint64_t ret;
    asm volatile ( "rdtsc" : "=A"(ret) );
    return ret;
}
