#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
//#define ART_PARTITION_FILE "/tmp/art"
#define ART_PARTITION_FILE "/home/ljx/sn.txt"


int main(int argc, char *argv[])
{
	int sn_len;
	sn_len = strlen(argv[1]);
	if(sn_len != 32)
	{
		printf("SN lenght is %d,SN lenght must be 16.\n",sn_len);
		return 0;
	}else{
		printf("SN:     [%s]\n", argv[1]);
	}

    unsigned char sn[15];
    int art;
    int i, k;
    art = open(ART_PARTITION_FILE, O_RDWR);

    if(art < 0)
    {
	    perror("open.");
    }

/* write SN */
    for(k = i = 0; i < 16; i++)
    {
		sn[i] = 0;

		//hight bits
		if( isdigit(argv[1][k]) )
		{	
			sn[i] += (argv[1][k] - 48) * 16;
		}else if(isupper(argv[1][k]))
		{
			sn[i] += (argv[1][k] - 55) * 16;
		}else if(islower(argv[1][k]))
		{
			sn[i] += (argv[1][k] -87) * 16;
		}else
		{
			printf("SN error.\n");
		}

		//low bits	
		if( isdigit(argv[1][k+1]) )
		{	
			sn[i] += argv[1][k+1] - 48;
		}else if(isupper(argv[1][k+1]))
		{
			sn[i] += argv[1][k+1] - 55;
		}else if(islower(argv[1][k+1]))
		{
			sn[i] += argv[1][k+1] -87;
		}else
		{
			printf("SN error.\n");
		}
		k += 2;
    }
	
//	lseek(art, 0x88, SEEK_SET);
	lseek(art, 0x20, SEEK_SET);
    for(i = 0; i < 16 ; i++)
    {
		write(art, &sn[i], 1);
	}

    close(art);
}
