#include<stdio.h>
#include<stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include<string.h>
#include<sys/types.h>

#define DEVICE_PATH "/dev/pa2_char_device"
#define BUFFER_SIZE 16

int main()
{
	int num_bytes = 0;
	char* buff;
	int offset;
	int whence;

	int my_file = open(DEVICE_PATH, O_RDWR);
	if (!my_file)
		printf("Could Not open file\n");
	char option = 'c';
	while (option != 'e')
	{
		option = 'c';
		printf("\n\nMENU \n");
		printf("r - to read \n");
		printf("w - to write\n");
		printf("s - to seek\n");
		printf("e - to exit\n");
		printf("Enter command: ");
		fgets(&option, 10, stdin);


		switch (option) {
			case 'r':
				printf("How many bytes you want to read: \n");
				scanf("%d", &num_bytes);
				getchar();
				buff = (char*)malloc(num_bytes);
				if (-1 != read(my_file, buff, num_bytes)) {
					printf("Data read from the device: %s\n", buff);
				}
				else {
					printf("Out of bounds error");
				}
				
				memset(buff, '\0', num_bytes);
				free(buff);
				break;

			case 'w':
				buff = (char*)malloc(BUFFER_SIZE);
				printf("Enter what you want to write: \n");
				fgets(buff, BUFFER_SIZE, stdin);
				int bytes_written = write(my_file, buff, strlen(buff));
				if (-1 != bytes_written ) {
					printf("Data written to the device: %s\n", buff);
					printf("Bytes written: %d\n", bytes_written);
				}
				else {
					printf("Out of bounds error");
				}
				memset(buff, '\0', BUFFER_SIZE);
				free(buff);
				break;

			case 's':
				printf("Enter the offset value: \n");
				scanf("%d", &offset);
				getchar();
				printf("Enter a value for whence: \n");
				scanf("%d", &whence);
				getchar();
				lseek(my_file, offset, whence);
				break;
		}


	}
	close(my_file);


	return 0;
}
