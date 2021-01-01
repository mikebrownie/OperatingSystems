#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/slab.h>
#include<linux/uaccess.h>

MODULE_AUTHOR("Michael Brown");
MODULE_LICENSE("GPL");

#define BUFFER_SIZE 1024
/* Define device_buffer and other global data structures you will need here */
#define MAJOR_NUMBER 60
#define DEVICE_NAME "pa2_char_driver"

char* device_buffer;
int opens = 0;
int closes = 0;


ssize_t pa2_char_driver_read (struct file *pfile, char __user *buffer, size_t length, loff_t *offset) /*0 if fails, bytes copied otherwise*/
{
	/* *buffer is the userspace buffer to where you are writing the data you want to be read from the device file*/
	/* length is the length of the userspace buffer*/
	/* offset will be set to current position of the opened file after read*/
	/* copy_to_user function: source is device_buffer and destination is the userspace buffer *buffer */	
	if ((BUFFER_SIZE - *offset) < length ) { //Don't overflow user buffer
		
		return -1;
	}
	/* 1st check if user tries to read outstide of allocated buffer
		2n check if user attempts to read past written memory
	*/
	if (copy_to_user(buffer, device_buffer + *offset, length)) {
		printk(KERN_ALERT "NO bytes copied\n");
	}
	else {
		printk(KERN_ALERT "%ld bytes copied\n", length);
	}
	
	*offset = *offset + (length-1);
	return length;
}



ssize_t pa2_char_driver_write (struct file *pfile, const char __user *buffer, size_t length, loff_t *offset)
{
	/* *buffer is the userspace buffer where you are writing the data you want to be written in the device file*/
	/* length is the length of the userspace buffer*/
	/* current position of the opened file*/
	/* copy_from_user function: destination is device_buffer and source is the userspace buffer *buffer */
	if (BUFFER_SIZE < *offset + length) { //Stop out of bounds seg fault
		return -1;
	}
	copy_from_user(device_buffer+*offset, buffer, length); //copy_to_user returns number of bytes not copied
	*offset = *offset + (length-1);
	printk(KERN_ALERT "%ld bytes written\n", length);
	return length;
}


int pa2_char_driver_open (struct inode *pinode, struct file *pfile)
{
	/* print to the log file that the device is opened and also print the number of times this device has been opened until now*/
	printk(KERN_ALERT "%s function is opening file\n", __FUNCTION__);
	opens++;
	printk(KERN_ALERT "%u times opened\n", opens);
	return 0;
}

int pa2_char_driver_close (struct inode *pinode, struct file *pfile)
{
	/* print to the log file that the device is closed and also print the number of times this device has been closed until now*/
	printk(KERN_ALERT "%s function is closing file\n", __FUNCTION__);
	closes++;
	printk(KERN_ALERT "%u times closed\n", closes);
	return 0;
}

loff_t pa2_char_driver_seek (struct file *pfile, loff_t offset, int whence)
{
	/* Update open file position according to the values of offset and whence */
	if (whence == 0) {
		pfile->f_pos = offset;
	}
	else if (whence == 1) {
		if ( (pfile->f_pos + offset) > sizeof(*pfile) || (pfile->f_pos + offset) < 0) {
			return -1;
			} //Don't let user write out of bounds
			pfile->f_pos += offset;
	}
	else if (whence == 2) {
		if ((sizeof(*pfile) + offset) > sizeof(*pfile) || (sizeof(*pfile) + offset < 0)) {
			return -1;
		} //Don't let user write out of bounds
		pfile->f_pos = (BUFFER_SIZE - offset);
	}
	return 0;
}

struct file_operations my_file_operations = {
	.owner = THIS_MODULE,
	.open = pa2_char_driver_open,       // int my_open  (struct inode *, struct file *);
	.release = pa2_char_driver_close,      // int my_close (struct inode *, struct file *);
	.read = pa2_char_driver_read,       // ssize_t my_read  (struct file *, char __user *, size_t, loff_t *);
	.write = pa2_char_driver_write,      // ssize_t my_write (struct file *, const char __user *, size_t, loff_t *);
	.llseek = pa2_char_driver_seek       // loff_t  my_seek  (struct file *, loff_t, int);
};



static int pa2_char_driver_init(void)
{
	/* print to the log file that the init function is called.*/
	/* register the device */
	printk(KERN_ALERT "inside %s function\n", __FUNCTION__);
	device_buffer = kmalloc(BUFFER_SIZE, GFP_KERNEL);
	if(0!=register_chrdev(MAJOR_NUMBER, DEVICE_NAME, &my_file_operations)){
		printk(KERN_ALERT "Failed to register char_driver");
	}
	else {
		printk(KERN_ALERT "registered char_driver");
	}
 // IF ERROR CHECK PTR	
	
	
	return 0;
}

static void pa2_char_driver_exit(void)
{
	/* print to the log file that the exit function is called.*/
	/* unregister  the device using the register_chrdev() function. */
	printk(KERN_ALERT "inside %s function\n", __FUNCTION__);
	unregister_chrdev(MAJOR_NUMBER, DEVICE_NAME);
	memset(device_buffer, '\0', BUFFER_SIZE);
	kfree(device_buffer);
}

/* add module_init and module_exit to point to the corresponding init and exit function*/
module_init(pa2_char_driver_init);
module_exit(pa2_char_driver_exit);


