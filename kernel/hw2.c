#include <linux/kernel.h>
#include <linux/errno.h>
#include <asm/current.h>
#include <linux/sched.h>

asmlinkage long sys_hello(void){
    printk("Hello, World!\n");
    return 0;
}
asmlinkage long sys_set_weight(int weight){
    if (weight < 0){
        return -EINVAL;
    }
    current->_weight = weight;
    return 0;
}
asmlinkage long sys_get_weight(void){
    return current->_weight;
}
asmlinkage int sys_get_children_sum(void){

}