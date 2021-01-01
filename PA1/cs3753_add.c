#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/uaccess.h>

asmlinkage long sys_cs3753_add(int a, int b, int *result)
{
  printk(KERN_ALERT "b : %d\n" ,b);
  printk(KERN_ALERT "a : %d\n" ,a);
  int sum = a+b;
  copy_to_user(result, &sum, sizeof(int));
  printk(KERN_ALERT "a+b : %d\n",sum);
  return 0;
}
