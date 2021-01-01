# Simple Character Device Driver and LKM
Created by: Michael Brown - michael.g.brown@colorado.edu

## Files:
| PATH | DESCRIPTION |
| ------ | ------ |
| "modules/pa2_char_driver.c"| Device driver file, includes read, write, lseek, open, and close definitions |
| "modules/Makefile"| Makefile for device driver. Creates a module object |
| "test/char_device_test.c"| User-space test program. Includes functionality for all defined file operations in "modules/pa2_char_driver.c" |

## How to use
1) Build LKM
```sh
kernel/modules/$ sudo make -C /lib/modules/$(uname -r)/build M=$PWD modules
```
2) Insert LKM
```sh
kernel/modules/$ sudo insmod pa2-char-driver.ko
```

3) Add device file
```sh
kernel/modules/$sudo mknod –m 777 /dev/pa2_char_device c 60 0
```
Check for the device file with the command  ```ls /dev```

4) Build test program
```sh
kernel/modules/$ gcc ../test/char_device_test.c -o test
```

5) Run test program
```sh
kernel/modules/$ ./test
```
### Useful commands
1) Adding and removing the LKM
sudo insmod pa2_char_driver.ko
sudo rmmod pa2_char_driver.ko

3) Building the LKM
make -C /lib/modules/$(uname -r)/build M=$PWD

2) Adding a the device file
sudo mknod -m 777 /dev/pa2_char_device c 60 0
