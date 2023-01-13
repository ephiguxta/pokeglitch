#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "open_file.h"

#define begin_bag_addr 0x25c9
#define final_bag_addr 0x25f2

extern char items[255][16];

struct bag {
   int new_item_addr;
   int item_id;
};

int item_exists(char name[16], struct bag *bag_ptr);
int check_bag(FILE *file, struct bag *bag_ptr);
int insert_data(FILE *file, struct bag bag_data, int amount);
int fix_bag(FILE *file, struct bag bag_data);

int
insert_items(const char *save_path,int amount, char name[16]) {
   FILE *file;
   struct bag bag_data;
   struct bag *bag_ptr;

   bag_ptr = &bag_data;

   file = open_file(save_path);
   if(! file)
     return 1;

   // checking if the item exists
   item_exists(name, bag_ptr);

   if(! bag_data.item_id) {
      puts("This item doesn't exists!");
      puts("Skipping this action...");

      return 1;
   }

   if(! check_bag(file, bag_ptr)) {
      insert_data(file, bag_data, amount);
      fix_bag(file, bag_data);

   } else {
      puts("Full Bag!");
   }

   fclose(file);

   return 0;
}

int item_exists(char name[16], struct bag *bag_ptr) {
   for(unsigned char i = 1; i <= 255; i++) {
      if(! strncmp(name, items[i - 1], 16)) {

         // valid id's:
         // 0x01 - 0x53
         // 0xc4 - 0xff
         if(i >= 0x53)
            bag_ptr->item_id = i + 0x71;
         else
            bag_ptr->item_id = i;

         return 0;
      }
   }

   return 1;
}

int check_bag(FILE *file, struct bag *bag_ptr) {
   int data;

   // we sum 1 to the addr to skip the first byte
   fseek(file, begin_bag_addr + 1, SEEK_SET);

   for(int i = begin_bag_addr; i <= final_bag_addr; i++) {
      
      fread(&data, sizeof(char) * 2, 1, file);

      // check if there's an empty space,
      // and return the address

      if((data & 0x00ff) == 0x00ff) {
         bag_ptr->new_item_addr = i;

         return 0;
      }

      // jumping 2 bytes at a time in memory
      i++;
   }

   return 1;
}

int insert_data(FILE *file, struct bag bag_data, int amount) {
   fseek(file, bag_data.new_item_addr + 1, SEEK_SET);

   // item
   fputc(bag_data.item_id, file);
   // amount
   fputc(amount, file);

   return 0;
}

int fix_bag(FILE *file, struct bag bag_data) {
   unsigned char old_total_items;

   // insert new total items
   fseek(file, begin_bag_addr, SEEK_SET);
   old_total_items = fgetc(file);

   fseek(file, begin_bag_addr, SEEK_SET);
   fputc(old_total_items + 1, file);

   // the "limit byte" address (0xff) is two bytes after
   // the last item data
   int last_item_addr = bag_data.new_item_addr + 3;

   // showing what's the final item
   fseek(file, last_item_addr, SEEK_SET);
   fputc(0xff, file);

   return 0;
}
