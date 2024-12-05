#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

struct birthday {
    int day;
    int month;
    int year;
    struct list_head list;
};

static LIST_HEAD(birthday_list);

int simple_init(void) {
    struct birthday *person;
    int i;

    printk(KERN_INFO "Loading Module\n");

    for (i = 1; i <= 5; i++) {
        person = kmalloc(sizeof(*person), GFP_KERNEL);
        person->day = i;
        person->month = i + 1;
        person->year = 2000 + i;
        INIT_LIST_HEAD(&person->list);
        list_add_tail(&person->list, &birthday_list);
    }

    list_for_each_entry(person, &birthday_list, list) {
        printk(KERN_INFO "Birthday: %d/%d/%d\n", person->day, person->month, person->year);
    }
    return 0;
}

void simple_exit(void) {
    struct birthday *ptr, *next;

    list_for_each_entry_safe(ptr, next, &birthday_list, list) {
        list_del(&ptr->list);
        kfree(ptr);
    }

    printk(KERN_INFO "Removing Module and Freeing Memory\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Linked List Kernel Module");
MODULE_AUTHOR("SGG");
