#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/input.h>



#define  NODE_EXP	"/dev/fpga_char_lcd"

#define  LCD_ON              1
#define  LCD_CLEAR           2
#define  LCD_SET_HOME        3
#define  LCD_CURSOR_BLINK    4
#define  LCD_DATA_WRITE      5
#define  LCD_OFF	     6


int main()
{
	


	int fd;
	char buff[256] = "Name";
	int i,rb;
        struct input_event ev;
        struct input_absinfo ab;

	if ((fd = open("/dev/input/touchscreen0", O_RDONLY)) < 0) 
	{
		printf ("Error Opening the Device\n");
                return 1;
    }

	ioctl(fd, EVIOCGNAME(sizeof(buff)), buff);
	printf("Touch Input device name: \"%s\"\n", buff);

        for (i = 0; i < 5; i++)
	{
	   int a,b,ans ;
        	rb=read(fd,&ev,sizeof(struct input_event));

		printf ("After read\n");
		if ((ev.type == 1) && (ev.code == 330))
		{
			printf ("Touch Event = %d\n",ev.code);
		}

		if ((ev.type == 3) && (ev.code == 0))
		{   
                  
			printf ("X Value  = %d\n",ev.value);
			if(ev.value<1500)
				{  a = 1;
				
				}
			if(ev.value>1500)
{a=3;
}
		}
		if ((ev.type == 3) && (ev.code == 1))
		{  
                 
			printf ("Y Value  = %d\n",ev.value);
			if(ev.value<1800)
			{ b = 1;
			}
			if(ev.value>1800)
			{
				b=2;
			}
		}

		if ((ev.type == 3) && (ev.code == 24))
		{  
			printf ("Touch Pressure  = %d\n",ev.value);

		}


if((a==1)&&(b==1))
{
clcd();
}
if((a==1)&&(b==2))
{
clcd();
}

if(ans==3)
{
clcd();
}
}









         
    
	return 0;
}



/******************************************************************************************/

int clcd()
{ 


int exp_dev=0;

    /* open as blocking mode*/
    exp_dev = open(NODE_EXP, O_RDWR);
    if (exp_dev < 0)
    {
        fprintf(stderr, "Open error: %s\n", NODE_EXP);
	return 1;
    }


	   	if (ioctl(exp_dev,LCD_ON, NULL) < 0)
		{
		    printf("Error in Writing the LCD \r\n");
		    close(exp_dev);
		    return 1;
	        }
		if (ioctl(exp_dev,LCD_CLEAR, NULL) < 0)
		{
	   	    printf("Error in Clearing the LCD \r\n");
	     	    close(exp_dev);
	    	    return 1;
		}

                    if (ioctl(exp_dev,LCD_SET_HOME, NULL) < 0 )
                    {
                        printf("Error in setting the cursor in home\
			position \r\n");
                        close(exp_dev);
                        return 1;
                     }

                if (ioctl(exp_dev,LCD_CURSOR_BLINK, NULL) < 0 )
                {
                    printf("Error in Curosr blinking \r\n");
                    close(exp_dev);
                    return 1;
                }

/******************************************************************************/
int a,b,ans;
if((a==1)&&(b==1)){
                if (ioctl(exp_dev,LCD_DATA_WRITE, "wrong answer") < 0 )
                {
                    printf("Error in writing the LCD \r\n");
                    sleep(2);
                    close(exp_dev);
                    return 1;
                }

            }
	if((a==2)&&(b==2)){
               
             if (ioctl(exp_dev,LCD_DATA_WRITE, "wrong answer") < 0 )
                {
                    printf("Error in writing the LCD \r\n");
                    sleep(2);
                    close(exp_dev);
                    return 1;
             }
	}
	if(ans==3){
             if (ioctl(exp_dev,LCD_DATA_WRITE, "correct answer") < 0 )
                {
                    printf("Error in writing the LCD \r\n");
                    sleep(2);
                    close(exp_dev);
                    return 1;
                }
	 }


printf ("Press any key to exit from the program\n");
		getchar();
                if (ioctl(exp_dev,LCD_OFF, NULL) < 0 )
                {
                    printf("Error in Switching OFF the LCD \r\n");
                    close(exp_dev);
                    return 1;
                }
	    
        close(exp_dev);
}


			
	


/*************************************************/
