/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: FileSysInterface.h                                                 */
/*                                                                           */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2008-07                                                             */
/*                                                                           */
/* Description: Announcement of File System Interface.                               */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date: 2008-09-18                                                          */
/*    Modification: Create this file                                         */
/*                                                                           */
/*****************************************************************************/
#ifndef __FILESYS_INTERFACE_H__
#define __FILESYS_INTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*#if (VOS_NUCLEUS == VOS_OS_VER)*/
#if 0

/*****************************************************************************
 HuaShan协议栈封装的宏定义
*****************************************************************************/

#define DRV_S_IFDIR             0040000          /* directory */
#define DRV_NAME_MAX            28               /* max length of the file name*/
#define DRV_ERROR               (-1)             /* return status values */
#define DRV_FILE_NULL           (-1)                /* empty file*/

#define DRV_O_RDONLY            0x0001          /* +1 == FREAD */
#define DRV_O_WRONLY            0x0002          /* +1 == FWRITE */
#define DRV_O_RDWR              0x0004          /* +1 == FREAD|FWRITE */
#define DRV_O_CREAT             0x0010          /* open with file create */
#define DRV_O_APPEND            0x0008          /* append (writes guaranteed at the end) */
#define DRV_O_TRUNC             0x0040          /* open with truncation */
#define DRV_O_EXCL              0x0020          /* error on open if file exists */

#define DRV_SEEK_SET            2               /* absolute offset, was L_SET */
#define DRV_SEEK_CUR            0               /* relative to current offset, was L_INCR */
#define DRV_SEEK_END            1               /* relative to end of file, was L_XTND */

#define DRV_TIME                unsigned int

/*****************************************************************************
 HuaShan协议栈封装的结构体定义
*****************************************************************************/

/*typedef int DRV_SSIZE_T;
 */
typedef unsigned int DRV_SIZE_T;
typedef long DRV_OFF_T;
typedef unsigned int DRV_MODE_T;

typedef struct stat
{
    unsigned short      st_dev;
    char                padding[2];
    unsigned int        st_ino;
    unsigned int        st_mode;
    unsigned short      st_nlink;
    unsigned short      st_uid;
    unsigned short      st_gid;
    unsigned short      st_rdev;
    unsigned int        st_size;                      /* file size
 */
    DRV_TIME            st_atime;                     /*Time of last access.
 */
    DRV_TIME            st_mtime;                     /*Time of last data modification.
 */
    DRV_TIME            st_ctime;                     /*Time of last status create.
 */
}DRV_STAT_STRU;

typedef struct dstat_struct
{
    char                sfname[9];          /* Null terminated file and extension */
    char                fext[4];
    char                lfname[256];        /* Null terminated long file name */
    unsigned char       fattribute;         /* File attributes */
    unsigned char       fcrcmsec;           /* File create centesimal mili second */
    unsigned short      fcrtime;            /* File create time */
    unsigned short      fcrdate;            /* File create date */
    unsigned short      faccdate;           /* Access date */
    unsigned short      fclusterhigh;       /* High cluster for data file */
    unsigned short      fuptime;            /* File update time */
    unsigned short      fupdate;            /* File update */
    unsigned short      fclusterlow;        /* Low cluster for data file */
    unsigned int        fsize;              /* File size */
    void                *fs_mte;            /* MTE for subsquent calls */
    void                *fs_private;        /*For file system specific data */
    unsigned int        drive_id;           /* Unique ID for determining validity */
    unsigned short      dh;                 /* Disk handle for this object */
} DSTAT;

typedef struct
{
    char        d_name[DRV_NAME_MAX + 1];
}DRV_DIRENT_STRU;

typedef struct
{
    DSTAT           dir;                    /* DSTAT Directory from FILE */
    DRV_DIRENT_STRU dir_ent;                /* Directory entries */
    unsigned        pos;                    /* Directory positions */
    signed short    status;                 /* Directory open/close status */
    signed short    eod;                    /* End of directory */
    char            pathname[256];          /* Directory pathname */ /*以'/'作为结束*/
}DRV_DIR_STRU;

/*****************************************************************************
 HuaShan协议栈封装的函数声明
*****************************************************************************/
/*****************************************************************************
 函 数 名  : open
 功能描述  : 该函数用于以二进制格式打开文件。创建文件也通过此接口。
 输入参数  : path:  要打开文件的全路径
             oflags:打开标志
 输出参数  : None
 返 回 值  : POSIX_SUCCESS: 操作成功；
             POSIX_ERROR：  操作失败。
 注意事项　：
            1：不支持一个文件打开后未关闭时，又在本任务或其他任务重新打开。
            2：输入的路径字符串长度（含'\0'）不得超过260字节。
            3：支持在同一时刻总共打开30个文件。
*****************************************************************************/
extern int open(const char *path, int oflags);
/*****************************************************************************
 函 数 名  : close
 功能描述  : 该函数用于关闭文件
 输入参数  : filedes:  要关闭文件的描述符
 输出参数  : None
 返 回 值  : POSIX_SUCCESS: 操作成功；
             POSIX_ERROR：  操作失败。
*****************************************************************************/
extern int close(int filedes);
/*****************************************************************************
 函 数 名  : read
 功能描述  : 该函数从文件中读取数据
 输入参数  : filedes:  文件描述符
             buf:      存储数据的缓存
             nbyte:    要读的数据大小（以byte为单位）
 输出参数  : None
 返 回 值  : 成功则返回实际读出的数据大小（ >=0），否则返回POSIX_ERROR
*****************************************************************************/
/*extern DRV_SSIZE_T read(int filedes, void *buf, DRV_SIZE_T nbyte);
 */
/*****************************************************************************
 函 数 名  : write
 功能描述  : 该函数往文件中写入数据
 输入参数  : filedes:  文件描述符
             buf:      存储数据的缓存
             nbyte:    要读的数据大小（以byte为单位）
 输出参数  : None
 返 回 值  : 成功则返回实际写入的数据大小，否则返回POSIX_ERROR
*****************************************************************************/
/*extern DRV_SSIZE_T write(int filedes, const void *buf, DRV_SIZE_T nbyte);
 */
/*****************************************************************************
 函 数 名  : unlink
 功能描述  : 该函数删除文件，该文件必须先已关闭。
 输入参数  : path:  文件全路径
 输出参数  : None
 返 回 值  : 成功则返回POSIX_SUCCESS，否则返回POSIX_ERROR
*****************************************************************************/
extern int unlink(const char* path);
/*****************************************************************************
 函 数 名  : lseek
 功能描述  : 该函数根据参数将文件指针移到特定位置，并返回移动后的文件偏移量。
 输入参数  : fildes:  文件描述符
             offset:  移动的字节数
             whence:  移动方式
 输出参数  : None
 返 回 值  : 移动后相对于文件头的偏移量
*****************************************************************************/
extern DRV_OFF_T lseek(int filedes, DRV_OFF_T offset, int whence);
/*****************************************************************************
 函 数 名  : stat
 功能描述  : 该函数获取路径信息，并将其存入buf中，如果该路径不存在，返回错误.
 输入参数  : path:  文件的全路径名
             buf:   存储路径信息的缓存
 输出参数  : None
 返 回 值  : 如果成功则返回POSIX_SUCCESS，如果失败，则返回POSIX_ERROR
*****************************************************************************/
extern int stat(const char *path, DRV_STAT_STRU*buf);
/*****************************************************************************
 函 数 名  : mkdir
 功能描述  : 该函数依path来创建目录，创建前父目录必须存在.
 输入参数  : path:  要创建目录的全路径
             mode:  创建的模式，未使用
 输出参数  : None
 返 回 值  : 成功则返回POSIX_SUCCESS，如果创建失败，则返回POSIX_ERROR
*****************************************************************************/
#ifdef _WRS_KERNEL
extern int mkdir (const char *path);
#else
extern int mkdir(const char *path, DRV_MODE_T mode);
#endif
/*****************************************************************************
 函 数 名  : opendir
 功能描述  : 该函数打开目录，不支持一个目录打开后未关闭时，又在本任务或其他任务重新打开
 输入参数  : dirname:  要打开目录的全路径名
 输出参数  : None
 返 回 值  : 成功则返回指向目录信息的结构体，否则返回空
*****************************************************************************/
extern DRV_DIR_STRU* opendir(const char *dirname);
/*****************************************************************************
 函 数 名  : closedir
 功能描述  : 该函数打开目录，不支持一个目录打开后未关闭时，又在本任务或其他任务重新打开
 输入参数  : dirp:  指向目录信息的结构体
 输出参数  : None
 返 回 值  : 如果成功则返回POSIX_SUCCESS，如果失败，则返回POSIX_ERROR
*****************************************************************************/
extern int closedir(DRV_DIR_STRU *dirp);
/*****************************************************************************
 函 数 名  : readdir
 功能描述  : 该函数读取目录中的一个入口（包括文件和目录）
 输入参数  : dirp:  指向目录信息的结构体
 输出参数  : None
 返 回 值  : 返回下一个路径的入口，如果已经是最后的路径，返回空
*****************************************************************************/
extern DRV_DIRENT_STRU* readdir(DRV_DIR_STRU *dirp);
/*****************************************************************************
 函 数 名  : rmdir
 功能描述  : 该函数删除目录，该目录只能为空的
 输入参数  : path:  待删除目录全路径名
 输出参数  : None
 返 回 值  : 如果成功则返回POSIX_SUCCESS，如果失败，则返回POSIX_ERROR
*****************************************************************************/
extern int rmdir(const char *path);

/*****************************************************************************
 HuaShan协议栈封装的函数宏定义
*****************************************************************************/

#define DRV_FILE_OPEN(name,flags)                 open(name,flags)
#define DRV_FILE_CLOSE(fd)                        close(fd)
#define DRV_FILE_READ(fd,buffer,maxbytes)         read(fd,buffer,maxbytes)
#define DRV_FILE_WRITE(fd,buffer,nbytes)          write(fd,buffer,nbytes)
#define DRV_FILE_LSEEK(fd,offset,whence)          lseek(fd,offset,whence)
#define DRV_FILE_RMFILE(fileName)                 unlink(fileName)
#define DRV_FILE_MKDIR(dirName)                   mkdir(dirName, 0)
#define DRV_FILE_RMDIR(path)                      rmdir(path)
#define DRV_FILE_OPENDIR(dirName)                 opendir(dirName)
#define DRV_FILE_READDIR(pDir)                    readdir(pDir)
#define DRV_FILE_CLOSEDIR(pDir)                   closedir(pDir)
#define DRV_FILE_STAT(name,pStat)                 stat(name,pStat)
#define DRV_FILE_ERRNOGET()                       VOS_ERR

#pragma pack()
#endif
/*#elif (VOS_VXWORKS == VOS_OS_VER)*/

/*****************************************************************************
 Balong协议栈封装的宏定义
*****************************************************************************/

#define DRV_S_IFDIR             0x4000          /* directory */

#define DRV_NAME_MAX            255             /* max length of the file name*/

#define DRV_TIME                unsigned long   /* type for file time fields */

#define DRV_ERROR               (-1)            /* return status values */

#define DRV_FILE_NULL            0              /* empty file*/

#define DRV_O_RDONLY            0               /* +1 == FREAD */
#define DRV_O_WRONLY            1               /* +1 == FWRITE */
#define DRV_O_RDWR              2               /* +1 == FREAD|FWRITE */
#define DRV_O_CREAT             0x0200          /* open with file create */
#define DRV_O_APPEND            0x0008          /* append (writes guaranteed at the end) */
#define DRV_O_TRUNC             0x0400          /* open with truncation */
#define DRV_O_EXCL              0x0800          /* error on open if file exists */
#define DRV_O_NONBLOCK          0x4000          /* non blocking I/O (POSIX style) */
#define DRV_O_NOCTTY            0x8000          /* don't assign a ctty on this open */

#define DRV_SEEK_SET            0               /* absolute offset, was L_SET */
#define DRV_SEEK_CUR            1               /* relative to current offset, was L_INCR */
#define DRV_SEEK_END            2               /* relative to end of file, was L_XTND */

/*****************************************************************************
 Balong协议栈封装的结构体定义
*****************************************************************************/

typedef int                 DRV_STATUS;
typedef unsigned int        DRV_SIZE_T;
typedef long                DRV_OFF_T;
typedef	unsigned long       DRV_INO_T;
/* dirent */
typedef struct dirent
{
    DRV_INO_T           d_ino;                      /* file serial number */
    char                d_name [DRV_NAME_MAX + 1];  /* file name, null-terminated */
}DRV_DIRENT_STRU;

/* Directory descriptor */
typedef struct
{
    int                 dd_fd;                      /* file descriptor for open directory */
    int                 dd_cookie;                  /* filesys-specific marker within dir */
    int                 dd_eof;                     /* readdir EOF flag */
    DRV_DIRENT_STRU     dd_dirent;                  /* obtained directory entry */
}DRV_DIR_STRU;

/* 由于从vxwork6.2换到 vxwork6.8 ，stat结构有所变化 */
typedef struct stat_drv
{
    unsigned long       st_dev;     /* Device ID number */
    unsigned long       st_ino;     /* File serial number */
    int                 st_mode;    /* Mode of file */
    unsigned long       st_nlink;   /* Number of hard links to file */
    unsigned short      st_uid;     /* User ID of file */
    unsigned short      st_gid;     /* Group ID of file */
    unsigned long       st_rdev;    /* Device ID if special file */
    signed long long    st_size;    /* File size in bytes */
    DRV_TIME            st_atime;   /* Time of last access */
    DRV_TIME            st_mtime;   /* Time of last modification */
    DRV_TIME            st_ctime;   /* Time of last status change */
    long                st_blksize; /* File system block size */
    unsigned long       st_blocks;  /* Number of blocks containing file */
    unsigned char       st_attrib;  /* DOSFS only - file attributes */
    int                 st_reserved1;  /* reserved for future use */
    int                 st_reserved2;  /* reserved for future use */
    int                 st_reserved3;  /* reserved for future use */
    int                 st_reserved4;  /* reserved for future use */
}DRV_STAT_STRU;
#if (defined BSP_CORE_APP)
typedef int FILE;
#endif
/*****************************************************************************
 Balong协议栈封装的函数声明
*****************************************************************************/

#ifndef _DRV_LLT_
/*******************************************************************************
*
* open - open a file
*
* This routine opens a file for reading, writing, or updating, and returns
* a file descriptor for that file.  The arguments to open() are the filename
* <name> and the type of access set in <flags> and a UNIX chmod-style file mode
* <mode>.
*
* The parameter <flags> is set to one or a combination of the following access
* settings by bitwise OR operation for the duration of time the file is open.
* The following list is just a generic description of supported settings. Their
* availability and effect with or without combination among them change
* from device to device. Check the specific device manual for further details.
*
* \is
* \i O_RDONLY
* Open for reading only.
* \i O_WRONLY
* Open for writing only.
* \i O_RDWR
* Open for reading and writing.
* \i O_CREAT
* Create a file if not existing.
* \i O_EXCL
* Error on open if file exists and O_CREAT is also set.
* \i O_SYNC
* Write on the file descriptor complete as defined by synchronized I/O file
* integrity completion.
* \i O_DSYNC
* Write on the file descriptor complete as defined by synchronized I/O data
* integrity completion.
* \i O_RSYNC
* Read on the file descriptor complete at the same sync level as O_DSYNC and
* O_SYNC flags.
* \i O_APPEND
* If set, the file offset is set to the end of the file prior to each write.
* So writes are guaranteed at the end. It has no effect on devices other than
* the regular file system.
* \i O_NONBLOCK
* Non-blocking I/O if being set.
* \i O_NOCTTY
* Do not assign a ctty on this open, which does not cause the terminal device
* to become the controlling terminal for the process. Effective only on a
* terminal device.
* \i O_TRUNC
* Open with truncation. If the file exists and is a regular file, and the file
* is successfully opened, its length is truncated to 0. It has no effect on
* devices other than the regular file system.
* \ie
*
* In general, open() can only open pre-existing devices and files.  However,
* files can also be created with open() by setting O_CREAT and perhaps some
* other like O_RDWR which depends on the file system implementation.
* In this case, the file is created with a UNIX chmod-style file mode, as
* indicated with the parameter <mode>.  For example:
* \cs
*     fd = open ("/usr/myFile", O_CREAT | O_RDWR, 0644);
* \ce
*
* Files, on dosFs volumes, can be opened with the O_SYNC flag indicating that
* each write should be immediately written to the backing media. This
* synchronizes the FAT and the directory entries.
*
*
* INTERNAL
* A driver's open routine will return FOLLOW_LINK if any part of the file name
* contains a link (directory path or file name).  In this case, it will also
* have changed the name of the file being opened to incorporate the name of
* the link.  The new file name is then repeatedly resubmitted to the driver's
* open routine until all links are resolved.
*
* NOTE
* For more information about situations when there are no file descriptors
* available, see the reference entry for iosInit().
*
* Also note that not all device drivers honor the flags or mode values when
* opening a file.  Most simple devices simply ignore them and return an open
* file descriptor for both reading and writing.  Read the device driver
* manual for information on this.
*
* RETURNS
* A file descriptor number, or ERROR if a file name is not specified, the
* device does not exist, no file descriptors are available, or the driver
* returns ERROR.
*
* ERRNO
* \is
* \i ELOOP
* Circular symbolic link, too many links.
* \i EMFILE
* Maximum number of files already open.
* \i S_iosLib_DEVICE_NOT_FOUND (ENODEV)
* No valid device name found in path.
* \i others
* Other errors reported by device drivers.
* \ie
*
* SEE ALSO: creat()
*/
extern int open (const char *name, int flags, ...);
/*******************************************************************************
*
* close - close a file
*
* This routine closes the specified file and frees the file descriptor.
* It calls the device driver to do the work.
*
* RETURNS
* The status of the driver close routine, or ERROR if the file descriptor
* is invalid.
*
* ERRNO
* \is
* \i EBADF
* Invalid file descriptor.
* \i Others
* Other errors generated by device drivers.
* \ie
*/
extern DRV_STATUS close(int fd);
/*******************************************************************************
*
* read - read bytes from a file or device
*
* This routine reads a number of bytes (less than or equal to <maxbytes>)
* from a specified file descriptor and places them in <buffer>.  It calls
* the device driver to do the work.
*
* RETURNS
* The number of bytes read (between 1 and <maxbytes>, 0 if end of file), or
* ERROR if the file descriptor does not exist, the driver does not have
* a read routines, or the driver returns ERROR. If the driver does not
* have a read routine, errno is set to ENOTSUP.
*
* ERRNO
* \is
* \i EBADF
* Bad file descriptor number.
* \i ENOTSUP
* Device driver does not support the read command.
* \i ENXIO
* Device and its driver are removed. close() should be called to release
* this file descriptor.
* \i Other
* Other errors reported by device driver.
* \ie
*/
extern int read(int fd, char *buffer, DRV_SIZE_T maxbytes);
/*******************************************************************************
*
* write - write bytes to a file
*
* This routine writes <nbytes> bytes from <buffer> to a specified file
* descriptor <fd>.  It calls the device driver to do the work.
*
* RETURNS
* The number of bytes written (if not equal to <nbytes>, an error has
* occurred), or ERROR if the file descriptor does not exist, the driver
* does not have a write routine, or the driver returns ERROR. If the driver
* does not have a write routine, errno is set to ENOTSUP.
*
* ERRNO
* \is
* \i EBADF
* Bad file descriptor number.
* \i ENOTSUP
* Device driver does not support the write command.
* \i ENXIO
* Device and its driver are removed. close() should be called to release
* this file descriptor.
* \i Other
* Other errors reported by device driver.
* \ie
*/
extern int write(int fd, char *buffer, DRV_SIZE_T nbytes);
/*******************************************************************************
*
* lseek - set a file read/write pointer
*
* This routine sets the file read/write pointer of file <fd>
* to <offset>.
* The argument <whence>, which affects the file position pointer,
* has three values:
*
* \ts
* SEEK_SET  (0) | set to <offset>
* SEEK_CUR  (1) | set to current position plus <offset>
* SEEK_END  (2) | set to the size of the file plus <offset>
* \te
*
* This routine calls ioctl() with functions FIOWHERE, FIONREAD, and FIOSEEK.
*
* RETURNS
* The new offset from the beginning of the file, or ERROR.
*
* ERRNO
* See ioctl().
*/
extern DRV_OFF_T lseek(int fd, DRV_OFF_T offset, int whence);
/***************************************************************************
*
* rm - remove a file
*
* This command is provided for UNIX similarity. It simply calls remove().
*
* RETURNS: OK, or ERROR if the file cannot be removed.
*
* SEE ALSO:
* remove(),
* \tb VxWorks Kernel Programmer's Guide: `Kernel Shell'
*/
extern DRV_STATUS rm(const char* fileName);
/***************************************************************************
*
* mkdir - make a directory
*
* \IFSET_START USER
* SYNOPSIS
* \cs
* int mkdir
*     (
*     const char *	dirName,	/@ directory name @/
*     mode_t		mode            /@ mode of dir @/
*     )
* \ce
* \IFSET_END
* \IFSET_START KERNEL
* SYNOPSIS
* \cs
* STATUS mkdir
*        (
*        const char *	dirName		/@ directory name @/
*        )
* \ce
* \IFSET_END
*
* DESCRIPTION
* This command creates a new directory in a hierarchical file system.
* The <dirName> string specifies the name to be used for the
* new directory, and can be either a full or relative pathname.
* \IFSET_START USER
* <mode> sets the initial permission bits of the new directory.
* \IFSET_END
*
* This call is supported by the VxWorks NFS and dosFs file systems.
*
* RETURNS
* OK, or ERROR if the directory cannot be created.
*
* \IFSET_START KERNEL
* SEE ALSO
* rmdir(),
* \tb VxWorks Kernel Programmer's Guide: `Kernel Shell'
* \IFSET_END
*/
extern DRV_STATUS mkdir(const char* dirName);
/***************************************************************************
*
* rmdir - remove a directory
*
* This command removes an existing directory from a hierarchical file
* system.  The <dirName> string specifies the name of the directory to
* be removed, and may be either a full or relative pathname.
*
* This call is supported by the VxWorks NFS and dosFs file systems.
*
* RETURNS: OK, or ERROR if the directory cannot be removed.
*
* SEE ALSO
* mkdir(),
* \tb VxWorks Kernel Programmer's Guide: `Kernel Shell'
*/
extern DRV_STATUS rmdir(const char* dirName);
/*******************************************************************************
*
* opendir - open a directory for searching (POSIX)
*
* This routine opens the directory named by <dirName> and allocates a
* directory descriptor (DIR) for it.  A pointer to the DIR structure is
* returned.  The return of a NULL pointer indicates an error.
*
* After the directory is opened, readdir() is used to extract individual
* directory entries.  Finally, closedir() is used to close the directory.
*
* WARNING: For remote file systems mounted over netDrv, opendir() fails,
* because the netDrv implementation strategy does not provide a way to
* distinguish directories from plain files.  To permit use of opendir()
* on remote files, use NFS rather than netDrv.
*
* RETURNS: A pointer to a directory descriptor, or NULL if there is an error.
*
* ERRNO: N/A.
*
* SEE ALSO:
* closedir(), readdir(), rewinddir(), ls()
*/
extern DRV_DIR_STRU *opendir(const char* dirName);
/*******************************************************************************
*
* readdir - read one entry from a directory (POSIX)
*
* This routine obtains directory entry data for the next file from an
* open directory.  The <pDir> parameter is the pointer to a directory
* descriptor (DIR) which was returned by a previous opendir().
*
* This routine returns a pointer to a `dirent' structure which contains
* the name of the next file.  Empty directory entries and MS-DOS volume
* label entries are not reported.  The name of the file (or subdirectory)
* described by the directory entry is returned in the `d_name' field
* of the `dirent' structure.  The name is a single null-terminated string.
*
* The returned `dirent' pointer will be NULL, if it is at the end of the
* directory or if an error occurred.  Because there are two conditions which
* might cause NULL to be returned, the task's error number (`errno') must be
* used to determine if there was an actual error.  Before calling readdir(),
* set `errno' to OK.  If a NULL pointer is returned, check the new
* value of `errno'.  If `errno' is still OK, the end of the directory was
* reached; if not, `errno' contains the error code for an actual error which
* occurred.
*
* RETURNS: A pointer to a `dirent' structure,
* or NULL if there is an end-of-directory marker or error from the IO system.
*
* ERRNO
* \is
* \i EBADF
* Bad file descriptor number.
* \i S_ioLib_UNKNOWN_REQUEST (ENOSYS)
* Device driver does not support the ioctl command.
* \i Other
* Other errors reported by device driver.
* \ie
*
* SEE ALSO
* opendir(), closedir(), rewinddir(), ls()
*/
extern DRV_DIRENT_STRU* readdir(DRV_DIR_STRU *pDir);
/*******************************************************************************
*
* closedir - close a directory (POSIX)
*
* This routine closes a directory which was previously opened using
* opendir().  The <pDir> parameter is the directory descriptor pointer
* that was returned by opendir().
*
* RETURNS: OK or ERROR, the result of the close() command.
*
* ERRNO
* \is
* \i EBADF
* Invalid file descriptor.
* \i Others
* Other errors generated by device drivers.
* \ie
*
* SEE ALSO
* opendir(), readdir(), rewinddir()
*/
extern DRV_STATUS closedir(DRV_DIR_STRU *pDir);
/*******************************************************************************
*
* stat - get file status information using a pathname (POSIX)
*
* This routine obtains various characteristics of a file (or directory).
* This routine is equivalent to fstat(), except that the <name> of the file
* is specified, rather than an open file descriptor.
*
* The <pStat> parameter is a pointer to a `stat' structure (defined
* in stat.h).  This structure must have already been allocated before
* this routine is called.
*
* NOTE: When used with netDrv devices (FTP or RSH), stat() returns the size
* of the file and always sets the mode to regular; stat() does not distinguish
* between files, directories, links, etc.
*
* Upon return, the fields in the `stat' structure are updated to
* reflect the characteristics of the file.
*
* SYNOPSIS
* STATUS stat
*     (
*     const char * name,                  /@ name of file to check @/
*     struct stat *pStat                  /@ pointer to stat structure @/
*     )
*
* RETURNS: OK or ERROR, from the underlying io commands open(), ioctl(),
* or close().
*
* ERRNO: See open(), ioctl(), and close().
*
* SEE ALSO:
* fstat(), ls()
*/
extern DRV_STATUS stat(const char* name, DRV_STAT_STRU* pStat);
/*******************************************************************************
*
* errnoGet - get the error status value of the calling task
*
* This routine gets the error status value stored in `errno'.
* It is provided for compatibility with previous versions of VxWorks and
* accesses the global variable `errno' directly.
*
* RETURNS:
* The error status value contained in `errno'.
*
* SEE ALSO: errnoSet(), errnoOfTaskGet()
*/
#endif
#ifdef __OS_VXWORKS__
extern int errnoGet (void);
#endif

/*****************************************************************************
 Balong协议栈封装的函数宏定义
*****************************************************************************/

/*文件系统接口*/
extern FILE *BSP_fopen(const char *path, const char *mode);
extern int BSP_fclose(FILE *fp);
extern int BSP_fread(void* buf,unsigned int size,unsigned int count, FILE *stream) ;
extern int BSP_fwrite(const void* buf,unsigned int size,unsigned int count,FILE *stream);
extern int BSP_fseek(FILE *stream, long offset, int whence);
extern long BSP_ftell(FILE *stream);
extern int BSP_remove(const char *pathname);
extern int BSP_mkdir(const char *dirName);
extern int BSP_rmdir(const char *path);
extern DRV_DIR_STRU* BSP_opendir(const char *dirName);
extern DRV_DIRENT_STRU * BSP_readdir(DRV_DIR_STRU *pDir);
extern int BSP_closedir(DRV_DIR_STRU * pDir);
extern int BSP_stat(const char *path, DRV_STAT_STRU*buf);
extern unsigned long BSP_errnoGet(void);
extern int BSP_xcopy(const char *source,const char *dest);
extern int BSP_xdelete(const char * path);
extern int BSP_access(const char *path, int amode);
extern int BSP_rename(const char *oldname, const char *newname);
extern int BSP_mass_read(const char *partition, unsigned int offset,unsigned int size,void* buf);
extern int BSP_mass_write(const char *partition, unsigned int offset,unsigned int size,void* buf);

#define DRV_FILE_OPEN(name,flags)                 BSP_fopen(name,flags)
#define DRV_FILE_CLOSE(fp)                        BSP_fclose(fp)
#define DRV_FILE_READ(buf,u32size,u32count,fp)          BSP_fread(buf,u32size,u32count,fp)
#define DRV_FILE_WRITE(buf,u32size,u32count,fp)       BSP_fwrite(buf,u32size,u32count,fp)
#define DRV_FILE_LSEEK(fp,offset,whence)          BSP_fseek(fp,offset,whence)
#define DRV_FILE_TELL(fp)                         BSP_ftell(fp)
#define DRV_FILE_RMFILE(fileName)                 BSP_remove(fileName)
#define DRV_FILE_MKDIR(dirName)                   BSP_mkdir(dirName)
#define DRV_FILE_RMDIR(path)                      BSP_rmdir(path)
#define DRV_FILE_OPENDIR(dirName)                 BSP_opendir(dirName)
#define DRV_FILE_READDIR(pDir)                    BSP_readdir(pDir)
#define DRV_FILE_CLOSEDIR(pDir)                   BSP_closedir(pDir)
#define DRV_FILE_STAT(name,pStat)                 BSP_stat(name,pStat)
#define DRV_FILE_ERRNOGET()                       (unsigned long)BSP_errnoGet()
#define DRV_FILE_ACCESS(name,flags)               BSP_access(name,flags)
#define DRV_FILE_XCOPY(src, dest)                 BSP_xcopy(src, dest)
#define DRV_FILE_XDELETE(name)                    BSP_xdelete(name)
#define DRV_FILE_RENAME(oldname,newname)          BSP_rename(oldname,newname)

#pragma pack(0)

/*#elif (VOS_WIN32 == VOS_OS_VER)*/
#if 0

#include <io.h>
#include <fcntl.h>
#include <direct.h>

/*****************************************************************************
 PC工程的宏定义
*****************************************************************************/

#define DRV_S_IFDIR             0x4000          /* directory */

#define DRV_NAME_MAX            255             /* max length of the file name*/

#define DRV_TIME                unsigned long   /* type for file time fields */

#define DRV_ERROR               (-1)            /* return status values */

#define DRV_FILE_NULL            0              /* empty file*/

#define DRV_O_RDONLY            _O_RDONLY           /* +1 == FREAD */
#define DRV_O_WRONLY            _O_WRONLY           /* +1 == FWRITE */
#define DRV_O_RDWR              _O_RDWR             /* +1 == FREAD|FWRITE */
#define DRV_O_CREAT             _O_CREAT              /* open with file create */
#define DRV_O_APPEND            _O_APPEND             /* append (writes guaranteed at the end) */
#define DRV_O_TRUNC             _O_TRUNC              /* open with truncation */
#define DRV_O_EXCL              _O_EXCL             /* error on open if file exists */
#define DRV_O_NONBLOCK          _O_NONBLOCK         /* non blocking I/O (POSIX style) */
#define DRV_O_NOCTTY            _O_NOCTTY           /* don't assign a ctty on this open */

#define DRV_SEEK_SET            SEEK_SET              /* absolute offset, was L_SET */
#define DRV_SEEK_CUR            SEEK_CUR              /* relative to current offset, was L_INCR */
#define DRV_SEEK_END            SEEK_END              /* relative to end of file, was L_XTND */

/*****************************************************************************
 PC工程的结构体定义
*****************************************************************************/
typedef int                 DRV_STATUS;
typedef unsigned int        DRV_SIZE_T;
typedef long                DRV_OFF_T;
typedef unsigned long       DRV_INO_T;

/* dirent */
typedef struct dirent
{
    DRV_INO_T           d_ino;                      /* file serial number */
    char                d_name [DRV_NAME_MAX + 1];	/* file name, null-terminated */
}DRV_DIRENT_STRU;

/* Directory descriptor */
typedef struct
{
    int                 dd_fd;                      /* file descriptor for open directory */
    int                 dd_cookie;                  /* filesys-specific marker within dir */
    int                 dd_eof;                     /* readdir EOF flag */
    DRV_DIRENT_STRU     dd_dirent;                  /* obtained directory entry */
}DRV_DIR_STRU;

typedef struct stat
{
    unsigned long       st_dev;                 /* device ID number */
    unsigned long       st_ino;                 /* file serial number */
    unsigned short      st_mode;                /* file mode (see below) */
    short               st_nlink;               /* number of links to file */
    short               st_uid;                 /* user ID of file's owner */
    short               st_gid;                 /* group ID of file's group */
    unsigned long       st_rdev;                /* device ID, only if special file */
    unsigned long       st_size;                /* size of file, in bytes */
    DRV_TIME            st_atime;               /* time of last access */
    DRV_TIME            st_mtime;               /* time of last modification */
    DRV_TIME            st_ctime;               /* time of last change of file status */
    long                st_blksize;
    long                st_blocks;
    unsigned long       st_attrib;              /* file attribute byte (dosFs only) */
    int                 reserved1;              /* reserved for future use */
    int                 reserved2;              /* reserved for future use */
    int                 reserved3;              /* reserved for future use */
    int                 reserved4;              /* reserved for future use */
    int                 reserved5;              /* reserved for future use */
    int                 reserved6;              /* reserved for future use */
}DRV_STAT_STRU;

extern DRV_STATUS _rm(const char* fileName);
extern DRV_DIR_STRU* _opendir(const char* dirName);
extern DRV_DIRENT_STRU* _readdir(DRV_DIR_STRU *pDir);
extern DRV_STATUS _closedir(DRV_DIR_STRU *pDir);
extern DRV_STATUS _stat(const char* name, DRV_STAT_STRU* pStat);


#define DRV_FILE_OPEN(name,flags)                 _open(name,flags)
#define DRV_FILE_CLOSE(fd)                        _close(fd)
#define DRV_FILE_READ(fd,buffer,maxbytes)         _read(fd,buffer,maxbytes)
#define DRV_FILE_WRITE(fd,buffer,nbytes)          _write(fd,buffer,nbytes)
#define DRV_FILE_LSEEK(fd,offset,whence)          _lseek(fd,offset,whence)
#define DRV_FILE_RMFILE(fileName)                 _rm(fileName)
#define DRV_FILE_MKDIR(dirName)                   _mkdir(dirName)
#define DRV_FILE_RMDIR(path)                      _rmdir(path)
#define DRV_FILE_OPENDIR(dirName)                 _opendir(dirName)
#define DRV_FILE_READDIR(pDir)                    _readdir(pDir)
#define DRV_FILE_CLOSEDIR(pDir)                   _closedir(pDir)
#define DRV_FILE_STAT(name,pStat)                 _stat(name,pStat)
#define DRV_FILE_ERRNOGET()                       (unsigned long)_doserrno

#pragma pack()

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif


