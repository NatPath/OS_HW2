#include <linux/kernel.h>
#include <linux/errno.h>
#include <asm/current.h>
#include <linux/sched.h>
#include <linux/list.h>

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
int get_children_sum_wrap(struct task_struct& task){
    struct list_head *list;
    struct task_struct *itt_task;        
    int sum= task->_weight;
    list_for_each(list,&task->children){
        itt_task = list_entry(list,struct task_struct,sibling);
        sum+= get_children_sum_wrap(*itt_task);
    }
    return sum;
    
}
asmlinkage int sys_get_children_sum(void){
    int res = get_children_sum_wrap(current);
    struct list_head *list;
    struct task_struct *itt_task;        
    int sum=0;
    int i=0;
    list_for_each(list,&task->children){
        itt_task = list_entry(list,struct task_struct,sibling);
        sum+= get_children_sum_wrap(*itt_task)
        i++;
    }
    if (i==0){
        return -ECHILD;
    }
    return sum;
}
asmlinkage pid_t sys_get_heaviest_ancestor(void){
    pid_t max_pid = current->pid;
    int max_weight = current->_weight;
    struct task_struct* itt=current;
    while (itt->pid!=1){
       if (itt->_weight > max_weight){
           max_pid= itt->pid;
           max_weight= itt->_weight;
       } 
       itt = itt->real_parent;
    }
    return max_pid;
}