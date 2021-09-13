#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <time.h>
#include <dirent.h>
#include <string.h>
#include <grp.h>

static char *getdayofweek(int n)
{
    switch (n)
    {
    case 0:
        return "Sun";
        break;
    case 1:
        return "Mon";
        break;
    case 2:
        return "Tue";
        break;
    case 3:
        return "Wed";
        break;
    case 4:
        return "Thu";
        break;
    case 5:
        return "Fri";
        break;
    case 6:
        return "Sat";
        break;
    
    default:
        return "unknown";
        break;
    }
}

static char *readlink_malloc (const char *filename)
{
  static char buffer[100];
  char *ptr = buffer;
  memset(buffer, 0, sizeof(buffer));
  while (1)
    {
      long int nchars = readlink (filename, buffer, sizeof(buffer));
      if (nchars < 0)
        {
          return NULL;
        }
      if ((long unsigned int)nchars < sizeof(buffer))
        return ptr;
    }
}

static void print_file_info(char *name)
{
    struct stat file;
    struct tm dt;
    struct passwd *pwd = NULL;
    struct group* gr = NULL;
    if (stat(name, &file) == 0)
    {
        pwd = getpwuid(file.st_uid);
        gr = getgrgid(file.st_gid);
        printf("File: %s\n", name);
        printf("  File type:              %s\n",S_ISDIR(file.st_mode)?"directory":
                                                (S_ISCHR(file.st_mode)?"character device":
                                                (S_ISBLK(file.st_mode)?"block device":
                                                (S_ISREG(file.st_mode)?"regular file":
                                                (S_ISFIFO(file.st_mode)?"FIFO/Pipe":
                                                (S_ISLNK(file.st_mode)?"symbolic link":
                                                (S_ISSOCK(file.st_mode)?"socket":"unknown")))))));
		if(S_ISLNK(file.st_mode))
			printf("%s", (readlink_malloc(name) != NULL)?readlink_malloc(name):"");
        printf("\n");
        printf("Device ID number:         %ld\n", file.st_rdev);
        printf("I-node number:            %ld\n", file.st_ino);
        printf("Mode:                     %c%c%c%c%c%c%c%c%c%c     (%d%d%d in octal)\n", 
                                                                   (S_ISDIR(file.st_mode))?'d':'l',
                                                                   (file.st_mode&S_IRUSR)?'r':'-',
                                                                   (file.st_mode&S_IWUSR)?'w':'-',
                                                                   (file.st_mode&S_IXUSR)?'x':'-',
                                                                   (file.st_mode&S_IRGRP)?'r':'-',
                                                                   (file.st_mode&S_IWGRP)?'w':'-',
                                                                   (file.st_mode&S_IXGRP)?'x':'-',
                                                                   (file.st_mode&S_IROTH)?'r':'-',
                                                                   (file.st_mode&S_IWOTH)?'w':'-',
                                                                   (file.st_mode&S_IXOTH)?'x':'-',
                                                                   ((file.st_mode&S_IRUSR)?4:0) + ((file.st_mode&S_IWUSR)?2:0) + ((file.st_mode&S_IXUSR)?1:0),
                                                                   ((file.st_mode&S_IRGRP)?4:0) + ((file.st_mode&S_IWGRP)?2:0) + ((file.st_mode&S_IXGRP)?1:0),
                                                                   ((file.st_mode&S_IROTH)?4:0) + ((file.st_mode&S_IWOTH)?2:0) + ((file.st_mode&S_IXOTH)?1:0));
        printf("Link Count:               %ld\n", file.st_nlink);
        printf("Owner ID:                 %s   (UID = %d)\n", pwd->pw_name, file.st_uid);
        printf("Group ID:                 %s   (GID = %d)\n", gr->gr_name, file.st_gid);
        printf("Preferred I/O block size: %ld bytes\n", file.st_blksize);
        printf("File size:                %ld bytes\n", file.st_size);
        printf("Blocks allocated:         %ld bytes\n", file.st_blocks);
        dt = *(gmtime(&file.st_atime));
        printf("Last file access:         %d-%d-%d %d:%d:%d %s\n", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900, 
                                             dt.tm_hour, dt.tm_min, dt.tm_sec,
                                             getdayofweek(dt.tm_wday));
        dt = *(gmtime(&file.st_mtime));
        printf("Last file modification:   %d-%d-%d %d:%d:%d %s\n", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900, 
                                             dt.tm_hour, dt.tm_min, dt.tm_sec,
                                             getdayofweek(dt.tm_wday));
        dt = *(gmtime(&file.st_ctime));
        printf("Last file change:         %d-%d-%d %d:%d:%d %s\n", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900, 
                                             dt.tm_hour, dt.tm_min, dt.tm_sec,
                                             getdayofweek(dt.tm_wday));
    }
    else
    {
        printf("Unable to get file properties.\n");
        printf("Please check whether '%s' file exists.\n", name);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    int n = 1;

    if (argc > 0)
        while (argv[n] != NULL)
        {
            print_file_info(argv[n]);
            n++;
        }   

    return 0;
}
