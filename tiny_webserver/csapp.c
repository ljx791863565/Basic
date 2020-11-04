#include "csapp.h"

void unix_error(char *msg)
{
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(0);
}

void posix_error(int code, char *msg)
{
	fprintf(stderr, "%s: %s\n", msg, strerror(code));
	exit(0);
}

void dns_error(char *msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(0);
}

void gai_error(int code, char *msg)
{
	fprintf(stderr, "%s: %s\n", msg, gai_strerror(code));
	exit(0);
}

void app_error(char *msg)
{
	fprintf(stderr, "%s\n", msg);
	exit(0);
}


pid_t Fork()
{
	pid_t pid;
	if ((pid = fork()) < 0) {
		unix_error("Fork error");
	}
	return pid;
}

/*
 * execve()用来执行参数filename字符串所代表的文件路径, 
 * 第二个参数系利用数组指针来传递给执行文件, 
 * 最后一个参数则为传递给执行文件的新环境变量数组.
 * 返回值：如果执行成功则函数不会返回, 执行失败则直接返回-1, 失败原因存于errno 中
 *  exec系列的系统调用是把当前程序替换成要执行的程序，
 *  而fork用来产生一个和当前进程一样的进程（虽然通常执行不同的代码流）。
 *  通常运行另一个程序，而同时保留原程序运行的方法是，fork+exec。
 *  exec系列的系统调用已经是变成别的程序了，已经和本程序无关了
 */
void Execve(const char *filename, char *const argv[], char *const envp[])
{
	if (execve(filename, argv, envp) < 0) {
		unix_error("execve error");
	}
}

/*
 * wait()会暂时停止目前进程的执行, 直到有信号来到或子进程结束. 
 * 如果在调用wait()时子进程已经结束, 则wait()会立即返回子进程结束状态值. 
 * 子进程的结束状态值会保存在参数status 返回, 而子进程的进程识别码也会一快返回. 
 * 如果不在意结束状态值, 则参数 status 可以设成NULL. 子进程的结束状态值请参考waitpid().
 * 返回值：如果执行成功则返回子进程识别码(PID), 如果有错误发生则返回-1. 失败原因存于errno 中.
 *
 * 进程一旦调用了wait，就立即阻塞自己，由wait自动分析是否当前进程的某个子进程已经退出，
 * 如果让它找到了这样一个已经变成僵尸的子进程，wait就会收集这个子进程的信息，
 * 并把它彻底销毁后返回；如果没有找到这样一个子进程，wait就会一直阻塞在这里，直到有一个出现为止。
 * wait()就是得到子进程的返回码，等于就是为子进程“收尸”，否则子进程会变僵尸进程
 */
pid_t Wait(int *status)
{
	pid_t pid;
	if ((pid = wait(status)) < 0) {
		unix_error("wait error");
	}
	return pid;
}

/*
 * waitpid()会暂时停止目前进程的执行, 直到有信号来到或子进程结束. 
 * 如果在调用wait()时子进程已经结束, 则wait()会立即返回子进程结束状态值. 
 * 子进程的结束状态值会由参数status 返回, 而子进程的进程识别码也会一快返回. 
 * 如果不在意结束状态值, 则参数status 可以设成NULL. 参数pid 为欲等待的子进程识别码, 其他数值意义如下：
 * 1、pid<-1 等待一个指定进程组中的任何子进程，这个进程组的ID等于pid的绝对值
 * 2、pid=-1 等待任何子进程, 相当于wait().
 * 3、pid=0  等待同一个进程组中的任何子进程，如果子进程已经加入了别的进程组，waitpid不会对它做任何理睬
 * 4、pid>0  只等待进程ID等于pid的子进程，不管其它已经有多少子进程运行结束退出了，只要指定的子进程还没有结束,waitpid就会一直等下去。
 * 参数option 可以为0 或下面的OR 组合：
 * 目前在Linux中只支持WNOHANG和WUNTRACED两个选项
 * WNOHANG：如果没有任何已经结束的子进程则马上返回, 不予以等待.即使没有子进程退出，它也会立即返回，不会像wait那样永远等下去
 * WUNTRACED：如果子进程进入暂停执行情况则马上返回, 但结束状态不予以理会. 子进程的结束状态返回后存于status, 底下有几个宏可判别结束情况
 * 返回值
 * 当正常返回的时候，waitpid返回收集到的子进程的进程ID；
 * 如果设置了选项WNOHANG，而调用中waitpid发现没有已退出的子进程可收集，则返回0；
 * 如果调用中出错，则返回-1，这时errno会被设置成相应的值以指示错误所在；
 * 当pid所指示的子进程不存在，或此进程存在，但不是调用进程的子进程，waitpid就会出错返回，这时errno被设置为ECHILD 
 */
pid_t Waitpid(pid_t pid, int *status, int options)
{
	pid_t retpid;
	if ((retpid = waitpid(pid, status, options)) < 0) {
		unix_error("waitpid error");
	}
	return retpid;
}

/*
 * kill()可以用来送参数signum 指定的信号给参数pid 指定的进程。
 * 参数pid 有几种情况：
 * 1、pid>0 将信号传给进程识别码为pid 的进程.
 * 2、pid=0 将信号传给和目前进程相同进程组的所有进程
 * 3、pid=-1 将信号广播传送给系统内所有的进程
 * 4、pid<0 将信号传给进程组识别码为pid 绝对值的所有进程参数 
 *
 * 返回值：执行成功则返回0, 如果有错误则返回-1.
 * 错误代码：
 * 1、EINVAL 参数sig 不合法
 * 2、ESRCH 参数pid 所指定的进程或进程组不存在
 * 3、EPERM 权限不够无法传送信号给指定进程
 */
void Kill(pid_t pid, int signum)
{
	int rc;
	if ((rc = kill(pid, signum)) < 0) {
		unix_error("kill error");
	}
}

/*
 * 调用该函数可以造成进程主动挂起，等待信号唤醒。调用该系统调用的进程将处于阻塞状态(主动放弃cpu) 直到有信号递达将其唤醒
 * 如果信号的默认处理动作是终止进程，则进程终止，pause函数么有机会返回。
 * 如果信号的默认处理动作是忽略，进程继续处于挂起状态，pause函数不返回。
 * 如果信号的处理动作是捕捉，则[调用完信号处理函数之后，pause返回-1] errno设置为EINTR，表示“被信号中断”。
 * pause收到的信号不能被屏蔽，如果被屏蔽，那么pause就不能被唤醒。
 */
void Pause()
{
	(void)pause();
	return;
}

/*
 * sleep()会令目前的进程暂停, 直到达到参数seconds 所指定的时间, 或是被信号所中断.
 * 返回值：若进程暂停到参数seconds 所指定的时间则返回0, 若有信号中断则返回剩余秒数.
 */
unsigned int Sleep(unsigned int secs)
{
	unsigned int rc;
	if ((rc = sleep(secs)) < 0) {
		unix_error("sleep error");
	}
	return rc;
}

/*
 * 闹钟函数
 * alarm()用来设置信号SIGALRM 在经过参数seconds 指定的秒数后传送给目前的进程.
 * 如果参数seconds 为0, 则之前设置的闹钟会被取消, 并将剩下的时间返回.
 * 返回值：返回之前闹钟的剩余秒数, 如果之前未设闹钟则返回0.
 * 每个进程都有且只有唯一个定时器。
 */
unsigned int Alarm(unsigned int secs)
{
	return alarm(secs);
}

/*
 * 将pid进程的进程组ID设置成pgid，创建一个新进程组或加入一个已存在的进程组
 * 一个进程只能为自己或子进程设置进程组ID，不能设置其父进程的进程组ID。
 * if(pid == pgid), 由pid指定的进程变成进程组长;即进程pid的进程组ID pgid=pid.
 * if(pid==0),将当前进程的pid作为进程组ID.
 * if(pgid==0),将pid作为进程组ID.
 */
void Setpgid(pid_t pid, pid_t pgid)
{
	int rc;
	if ((rc = setpgid(pid, pgid)) < 0) {
		unix_error("setpgid error");
	}
	return;
}

/*
 * getpgrp()用来取得目前进程所属的组识别码. 此函数相当于调用getpgid(0);\
 * 返回值：返回目前进程所属的组识别码.
 */
pid_t Getpgrp()
{
	return getpgrp();
}

handler_t *signal(int signum, handler_t *handler)
{
	struct sigaction action, old_action;
	action.sa_handler = handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;
	if (sigaction(signum, &action, &old_action) < 0) {
		unix_error("signal error");
	}
	return old_action.sa_handler;
}

/*
 * #include <signal.h>
 * int sigprocmask( int how, const sigset_t *restrict set, sigset_t *restrict oset );
 * 返回值：若成功则返回0，若出错则返回-1
 * 一个进程的信号屏蔽字规定了当前阻塞而给该进程的信号集。
 * 调用函数sigprocmask可以检测或更改其信号屏蔽字，或者在一个步骤中同时执行这两个操作。
 * 如果set是空指针，则不改变该进程的信号屏蔽字，how的值也无意义。
 * 若oset是非空指针，那么进程的当前信号屏蔽字通过oset返回。
 * 若set是一个非空指针，则参数how指示如何修改当前信号屏蔽字。
 * 下表表明how可选用的值。注意，不能阻塞SIGKILL和SIGSTOP信号。
 * +============+===============================================================+
 * | how		|		说明													|
 * +------------+---------------------------------------------------------------+
 * |SIG_BLOCK	|该进程新的信号屏蔽字是其当前信号屏蔽字和set指向信号集的并集。	|
 * |			|set包含了我们希望阻塞的附加信号								|
 * +------------+---------------------------------------------------------------+
 * |SIG_UNBLOCK |该进程新的信号屏蔽字是其当前信号屏蔽字和set所指向信号集补集的	|
 * |			|交集。set包含了我希望解除阻塞的信号							|
 * +------------+---------------------------------------------------------------+
 * |SIG_SETMASK |该进程新的信号屏蔽字将被set指向的信号集的值代替				|
 * |			|																|
 * +============+===============================================================+
 *
 * sigprocmask()函数只为单线程的进程定义的，在多线程中要使用pthread_sigmask变量，在使用之前需要声明和初始化。
 */
void Sigprocmask(int how, const sigset_t *set, sigset_t *oldset)
{
	if (sigprocmask(how, set, oldset) < 0) {
		unix_error("sigprocmask error");
	}
	return ;
}

/*
 * 该函数的作用是将信号集初始化为空。
 */
void Sigemptyset(sigset_t *set)
{
	if (sigemptyset(set) < 0) {
		unix_error("sigemptyset error");
	}
	return;
}

/*
 * 该函数的作用是把信号集初始化包含所有已定义的信号。
 */
void Sigfillset(sigset_t *set)
{
	if (sigfillset(set) < 0) {
		unix_error("sigfillset error");
	}
	return ;
}

/*
 * 该函数的作用是把信号signo添加到信号集set中，成功时返回0，失败时返回-1。
 */
void Sigaddset(sigset_t *set, int signum)
{
	if (sigaddset(set, signum) < 0) {
		unix_error("sigaddset error");
	}
	return ;
}

/*
 * 该函数的作用是把信号signo从信号集set中删除，成功时返回0，失败时返回-1.
 */
void Sigdelset(sigset_t *set, int signum)
{
	if (sigdelset(set, signum) < 0) {
		unix_error("sigdelset error");
	}
	return;
}

/*
 * 该函数的作用是判断给定的信号signo是否是信号集中的一个成员，如果是返回1，如果不是，返回0，如果给定的信号无效，返回-1；
 */
int Sigismember(const sigset_t *set, int signum)
{
	int rc;
	if ((rc = sigismember(set, signum)) < 0) {
		unix_error("sigismember error");
	}
	return rc;
}

/*
 * 该函数通过将进程的屏蔽字替换为由参数sigmask给出的信号集，然后挂起进程的执行。
 * 先替换再挂起程序的执行
 * 程序将在信号处理函数执行完毕后继续执行。如果接收到信号终止了程序，sigsuspend()就不会返回
 * 如果接收到的信号没有终止程序，sigsuspend()就返回-1，并将errno设置为EINTR。
 */
int Sigsuspend(const sigset_t *set)
{
	int rc = sigsuspend(set);
	if (errno != EINTR) {
		unix_error("sigsuspend error");
	}
	return rc;
}

static void sio_reverse(char s[])
{
	int ch, i, j;
	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		ch = s[i];
		s[i] = s[j];
		s[j] = ch;
	}
}

//将v转换为以b为进制的字符串 保存在s中
static void sio_ltoa(long v, char s[], int b)
{
	int ch;
	int i = 0;
	do {
		s[i++] = ((ch = (v % b)) < 10 ? ch + '0' : ch - 10 + 'a');
	} while ((v/=b) > 0);
	s[i] = '\0';
	sio_reverse(s);
}

static size_t sio_strlen(char s[])
{
	int i = 0;
	while (s[i] != '\0') {
		++i;
	}
	return i;
}

ssize_t sio_puts(char s[])
{
	return write(STDOUT_FILENO, s, sio_strlen(s));
}

ssize_t sio_putl(long v)
{
	char s[128];
	sio_ltoa(v, s, 10);
	return sio_puts(s);
}

void sio_error(char s[])
{
	sio_puts(s);
	_exit(1);
}

ssize_t Sio_puts(char s[])
{
	ssize_t n;
	if ((n = sio_puts(s)) < 0) {
		sio_error("sio_puts error");
	}
	return n;
}

ssize_t Sio_putl(long v)
{
	ssize_t n;
	if ((n = sio_putl(v)) < 0) {
		sio_error("sio_putl error");
	}
	return n;
}

void Sio_error(char s[])
{
	sio_error(s);
}

/*
 * mmap将一个文件或者其它对象映射进内存。
 * 文件被映射到多个页上，如果文件的大小不是所有页的大小之和，最后一个页不被使用的空间将会清零。
 * munmap执行相反的操作，删除特定地址区域的对象映射。
 *
 * 参数：
start：映射区的开始地址。
length：映射区的长度。
prot：期望的内存保护标志，不能与文件的打开模式冲突。是以下的某个值，可以通过or运算合理地组合在一起
PROT_EXEC //页内容可以被执行
PROT_READ  //页内容可以被读取
PROT_WRITE //页可以被写入
PROT_NONE  //页不可访问
flags：指定映射对象的类型，映射选项和映射页是否可以共享。它的值可以是一个或者多个以下位的组合体
MAP_FIXED //使用指定的映射起始地址，如果由start和len参数指定的内存区重叠于现存的映射空间，重叠部分将会被丢弃。如果指定的起始地址不可用，操作将会失败。并且起始地址必须落在页的边界上。
MAP_SHARED //与其它所有映射这个对象的进程共享映射空间。对共享区的写入，相当于输出到文件。直到msync()或者munmap()被调用，文件实际上不会被更新。
MAP_PRIVATE //建立一个写入时拷贝的私有映射。内存区域的写入不会影响到原文件。这个标志和以上标志是互斥的，只能使用其中一个。
MAP_DENYWRITE //这个标志被忽略。
MAP_EXECUTABLE //同上
MAP_NORESERVE //不要为这个映射保留交换空间。当交换空间被保留，对映射区修改的可能会得到保证。当交换空间不被保留，同时内存不足，对映射区的修改会引起段违例信号。
MAP_LOCKED //锁定映射区的页面，从而防止页面被交换出内存。
MAP_GROWSDOWN //用于堆栈，告诉内核VM系统，映射区可以向下扩展。
MAP_ANONYMOUS //匿名映射，映射区不与任何文件关联。
MAP_ANON //MAP_ANONYMOUS的别称，不再被使用。
MAP_FILE //兼容标志，被忽略。
MAP_32BIT //将映射区放在进程地址空间的低2GB，MAP_FIXED指定时会被忽略。当前这个标志只在x86-64平台上得到支持。
MAP_POPULATE //为文件映射通过预读的方式准备好页表。随后对映射区的访问不会被页违例阻塞。
MAP_NONBLOCK //仅和MAP_POPULATE一起使用时才有意义。不执行预读，只为已存在于内存中的页面建立页表入口。
fd：有效的文件描述词。如果MAP_ANONYMOUS被设定，为了兼容问题，其值应为-1。
offset：被映射对象内容的起点。

成功执行时，mmap()返回被映射区的指针，munmap()返回0。失败时，mmap()返回MAP_FAILED[其值为(void *)-1]，munmap返回-1。errno被设为以下的某个值
EACCES：访问出错
EAGAIN：文件已被锁定，或者太多的内存已被锁定
EBADF：fd不是有效的文件描述词
EINVAL：一个或者多个参数无效
ENFILE：已达到系统对打开文件的限制
ENODEV：指定文件所在的文件系统不支持内存映射
ENOMEM：内存不足，或者进程已超出最大内存映射数量
EPERM：权能不足，操作不允许
ETXTBSY：已写的方式打开文件，同时指定MAP_DENYWRITE标志
SIGSEGV：试着向只读区写入
SIGBUS：试着访问不属于进程的内存区
 */
void *Mmap(void *start, size_t length, int prot, int flags, int fd, off_t offset)
{
	void *ptr;
	if ((ptr = mmap(start, length, prot, flags, fd, offset)) == (void *)-1) {
		unix_error("mmap error");
	}
	return ptr;
}

void Munmap(void *start, size_t length)
{
	if (munmap(start, length) < 0) {
		unix_error("munmao error");
	}
}
int Open(const char *pathname, int flags, mode_t mode)
{
	int rc;
	if ((rc = open(pathname, flags, mode)) < 0) {
		unix_error("open error");
	}
	return rc;
}

ssize_t Read(int fd, void *buf, size_t n)
{
	ssize_t rc;
	if ((rc = read(fd, buf, n)) < 0) {
		unix_error("read error");
	}
	return rc;
}

ssize_t Write(int fd, void *buf, size_t n)
{
	ssize_t rc;
	if ((rc = write(fd, buf, n)) < 0) {
		unix_error("write error");
	}
	return rc;
}

off_t Lseek(int fildes, off_t offset, int whence)
{
	off_t rc;
	if ((rc = lseek(fildes, offset, whence)) < 0) {
		unix_error("lseek error");
	}
	return rc;
}

void Close(int fd)
{
	int rc;
	if ((rc = close(fd)) < 0) {
		unix_error("close error");
	}
	return;
}

int Select(int fd, fd_set *readfds, fd_set *writefds, fd_set *execptfds, struct timeval *timeout)
{
	int rc;
	if ((rc = select(fd, readfds, writefds, execptfds, timeout)) < 0) {
		unix_error("select error");
	}
	return rc;
}

int Dup2(int fd1, int fd2)
{
	int rc;
	if ((rc = dup2(fd1, fd2)) < 0) {
		unix_error("dup2 error");
	}
	return rc;
}

/*
 * stat()用来将参数file_name 所指的文件状态, 复制到参数buf 所指的结构中。
 */
void Stat(const char *filename, struct stat *buf)
{
	if (stat(filename, buf) < 0) {
		unix_error("stat error");	
	}
}

/*
 * fstat()用来将参数fildes 所指的文件状态, 复制到参数buf 所指的结构中(struct stat). 
 * Fstat()与stat()作用完全相同, 不同处在于传入的参数为已打开的文件描述词. 详细内容请参考stat().
 */
void Fstat(int fd, struct stat *buf)
{
	if (fstat(fd, buf) < 0) {
		unix_error("fstat error");
	}
}

/*
 * opendir()用来打开参数name 指定的目录, 并返回DIR*形态的目录流, 和open()类似, 接下来对目录的读取和搜索都要使用此返回值.
 * 返回值：成功则返回DIR* 型态的目录流, 打开失败则返回NULL.
 */
DIR *Opendir(const char *name)
{
	DIR *pdir = opendir(name);
	if (!pdir) {
		unix_error("opendir error");
	}
	return pdir;
}

/*
 * readdir()返回参数dir 目录流的下个目录进入点
 * struct dirent
{
    ino_t d_ino;					//d_ino 此目录进入点的inode
    ff_t d_off;						//d_off 目录文件开头至此目录进入点的位移
    signed short int d_reclen;		//d_reclen _name 的长度, 不包含NULL 字符
    unsigned char d_type;			//d_type d_name 所指的文件类型 d_name 文件名
    har d_name[256];
};
 * 成功则返回下个目录进入点. 有错误发生或读取到目录文件尾则返回NULL
 */
struct dirent *Readdir(DIR *pdir)
{
	struct dirent *pde;
	errno = 0;
	pde = readdir(pdir);
	if ((pde == NULL) && (errno != 0)) {
		unix_error("readdir pdir");
	}
	return pde;
}

/*
 * closedir()关闭参数dir 所指的目录流。
 * 返回值：关闭成功则返回0,，失败返回-1,，错误原因存于errno 中。
 */
int Closedir(DIR *pdir)
{
	int rc;
	if ((rc = closedir(pdir)) < 0) {
		unix_error("closedir error");
	}
	return rc;
}

/*
 * fdopen()会将参数fildes 的文件描述符, 转换为对应的文件指针后返回.
 * +============+===============================================================+
 * | mode		|	describe													|
 * +------------+---------------------------------------------------------------+
 * |	"r"		| 打开一个用于读取的文件。该文件必须存在。						|
 * +------------+---------------------------------------------------------------+
 * |	"w"		|创建一个用于写入的空文件。如果文件名称与已存在的文件相同，		|
 * |			|则会删除已有文件的内容，文件被视为一个新的空文件。				|
 * +------------+---------------------------------------------------------------+
 * |	"a"		|追加到一个文件,写操作向文件末尾追加数据.如果文件不存在创建文件 |
 * +------------+---------------------------------------------------------------+
 * |	"r+"	|打开一个用于更新的文件，可读取也可写入。该文件必须存在。		|
 * +------------+---------------------------------------------------------------+
 * |	"w+"	|创建一个用于读写的空文件。										|
 * +------------+---------------------------------------------------------------+
 * |	"a+"	|打开一个用于读取和追加的文件。									|
 * +------------+---------------------------------------------------------------+
 * |	"rb+"	| 读写打开一个二进制文件，允许读数据。							|
 * +------------+---------------------------------------------------------------+
 * |	"wb+ "	| 读写打开或建立一个二进制文件，允许读和写。					|
 * +============+===============================================================+
 */
FILE *Fdopen(int fd, const char *type)
{
	FILE *fp;
	if ((fp = fdopen(fd, type)) == NULL) {
		unix_error("fdopen error");
	}
	return fp;
}

/*
 * fclose()用来关闭先前fopen()打开的文件. 此动作会让缓冲区内的数据写入文件中, 并释放系统所提供的文件资源.
 */
void Fclose(FILE *fp)
{
	if (fclose(fp) != 0) {
		unix_error("fclose error");
	}
	return;
}

/*
 *  使用给定的模式 mode 打开 filename 所指向的文件
 */
FILE *Fopen(const char *filename, const char *mode)
{
	FILE *fp;
	if ((fp = fopen(filename, mode)) == NULL) {
		unix_error("fopen error");
	}
	return fp;
}

/*
 * fputs()用来将参数s 所指的字符串写入到参数stream 所指的文件内.
 */
void Fputs(const char *ptr, FILE *stream)
{
	if (fputs(ptr, stream) == EOF) {
		unix_error("fputs error");
	}
}

/*
 * fgets()用来从参数stream 所指的文件内读入字符并存到参数s 所指的内存空间
 * 直到出现换行字符、读到文件尾或是已读了size-1 个字符为止, 最后会加上NULL 作为字符串结束.
 * gets()若成功则返回s 指针, 返回NULL 则表示有错误发生.
 *
 * ferror()用来检测文件流是否发生了错误
 * 若文件流出错则返回非0，否则返回0
 * ferror()一般是为增强代码强健性加入的检验性程序，避免在文件操作时出现程序锁死或错误
 */
char *Fgets(char *ptr, int n, FILE *stream)
{
	char *rptr;
	if (((rptr = fgets(ptr, n, stream)) == NULL) && ferror(stream)) {
		app_error("fgets error");
	}
	return rptr;
}

/*
 * fread()用来从文件流中读取数据.
 * 参数stream 为已打开的文件指针, 参数ptr 指向欲存放读取进来的数据空间, 
 * 读取的字符数以参数size*nmemb 来决定. 
 * Fread()会返回实际读取到的nmemb 数目,
 * 如果此值比参数nmemb 来得小, 则代表可能读到了文件的尾或有错误发生, 
 * 这时必须用feof()或ferror()来决定发生什么情况.
 * 返回实际读取到的nmemb 数目
 */
size_t Fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	size_t n;
	if (((n = fread(ptr, size, nmemb, stream)) < nmemb) &&ferror(stream)) {
		unix_error("fread error");
	}
	return n;
}

/*
 * fwrite()用来将数据写入文件流中. 参数stream 为已打开的文件指针, 
 * 参数ptr 指向欲写入的数据地址, 总共写入的字符数以参数size*nmemb 来决定. 
 * fwrite()会返回实际写入的nmemb 数目.
 */
void Fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	if (fwrite(ptr, size, nmemb, stream) < nmemb) {
		unix_error("fwrite error");
	}
}

void *Malloc(size_t size)
{
	void *p;
	if ((p = malloc(size)) == NULL) {
		unix_error("malloc error");
	}
	return p;
}

void *Realloc(void *ptr, size_t size)
{
	void *p;
	if ((p = realloc(ptr, size)) == NULL) {
		unix_error("realloc error");
	}
	return p;
}

void *Calloc(size_t nmemb, size_t size)
{
	void *p;
	if ((p = calloc(nmemb, size)) == NULL) {
		unix_error("calloc error");
	}
	return p;
}

void Free(void *ptr)
{
	free(ptr);
}

int Socket(int domain, int type, int protocol)
{
	int fd;
	if ((fd = socket(domain, type, protocol)) < 0) {
		unix_error("socket error");
	}
	return fd;
}

void Setsockopt(int fd, int level, int optname, const void *optval, int optlen)
{
	int rc;
	if ((rc = setsockopt(fd, level, optname, optval, optlen)) < 0) {
		unix_error("setsockopt error");
	}
	return;
}

void Bind(int sockfd, struct sockaddr *addr, int addrlen)
{
	int rc;
	if ((rc = bind(sockfd, addr, addrlen)) < 0) {
		unix_error("bind error");
	}
	return;
}

void Listen(int sockfd, int backlog)
{
	int rc;
	if ((rc = listen(sockfd, backlog)) < 0) {
		unix_error("listen error");
	}
	return;
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
	int fd;
	if ((fd = accept(sockfd, addr, addrlen)) < 0) {
		unix_error("accept error");
	}
	return fd;
}

void Connect(int sockfd, struct sockaddr *addr, int addrlen)
{
	int rc;
	if ((rc = connect(sockfd, addr, addrlen)) < 0) {
		unix_error("connect error");
	}
	return;
}

/*
 * getaddrinfo解决了把主机名和服务名转换成套接口地址结构的问题。
 * getaddrinfo函数能够处理名字到地址以及服务到端口这两种转换，返回的是一个addrinfo的结构（列表）指针而不是一个地址清单。
 * 这些addrinfo结构随后可由套接口函数直接使用。如此以来，getaddrinfo函数把协议相关性安全隐藏在这个库函数内部。
 * 应用程序只要处理由getaddrinfo函数填写的套接口地址结构
 * #include <netdb.h>
 *
 * struct addrinfo {
 *	int ai_flags;
 *	int ai_family;
 *	int ai_socktype;
 *	int ai_protocol;
 *	socklen_t ai_addrlen;
 *	struct sockaddr *ai_addr;
 *	char *ai_canonname;
 *	struct addrinfo *ai_next;
 *	};
 *
 *	ai_flags: 用来指定如何处理地址和名字，可取得值如下 各值可|相或
 *	+===================+=======================================================+
 *	|	标志			|		描述											|
 *	+===================+=======================================================+
 *	|	AI_ADDRCONFIG	|	查询配置地址类型(IPV4, IPV6)						|
 *	+-------------------+-------------------------------------------------------+
 *	|	AI_ALL			|	查找IPV4和IPV6地址 (仅用于AI_V4MAPPED)				|
 *	+-------------------+-------------------------------------------------------+
 *	|	AI_CANONNAME	|	需要一个规范名(而不是别名)							|
 *	+-------------------+-------------------------------------------------------+
 *	|	AI_NUMERICHOST	|	以数字格式返回主机地址								|
 *	+-------------------+-------------------------------------------------------+
 *	|	AI_NUMERICSERV	|	以端口号返回服务									|
 *	+-------------------+-------------------------------------------------------+
 *	|	AI_PASSIVE		|	套接字地址用于监听绑定								|
 *	+-------------------+-------------------------------------------------------+
 *	|	AI_V4MAPPED		|	如果没有找到IPV6地址 则返回映射到IPV6格式的IPV4地址	|
 *	+===================+=======================================================+
 *
 *	ai_family: 地址族，可取的值有AF_INET(IPv4) AF_INET6(IPv6) AF_UNIX(UNIX域) AF_UNSPEC(未指定)
 *	
 *	ai_socktype: socket的类型，主要有SOCK_STREAM(流)和SOCK_DGRAM(数据报)两种
 *	SOCK_SEQPACLKET (长度固定 有序 可靠的面向连接报文传递)
 *	SOCK_RAW(IP协议的数据报接口)
 *
 *	ai_protocol：socket协议参数
 *	IPPROTO_IP		0	IP协议
 *	IPPROTO_IPV4	4	IPV4
 *	IPPROTO_TPV6	41	IPV6
 *	IPPROTO_TCP		6	TCP
 *	IPPROTO_UDP		17	UDP
 *
 *	可以使用hint来过滤上面的结构体，仅使用ai_family、ai_flags、ai_protocol和ai_socktype字段
 *	剩余的整数字段必须设置为零，并且指针字段为空。
 *
 * hostname:一个主机名或者地址串(IPv4的点分十进制串或者IPv6的16进制串)
 * service：服务名可以是十进制的端口号，也可以是已定义的服务名称，如ftp、http等
 * hints：可以是一个空指针，也可以是一个指向某个addrinfo结构体的指针，调用者在这个结构中填入关于期望返回的信息类型的暗示。
 * 举例来说：如果指定的服务既支持TCP也支持UDP
 * 那么调用者可以把hints结构中的ai_socktype成员设置成SOCK_DGRAM使得返回的仅仅是适用于数据报套接口的信息。
 * result：本函数通过result指针参数返回一个指向addrinfo结构体链表的指针。
 * 
 * 在getaddrinfo函数之前通常需要对以下6个参数进行以下设置：hostname、service、hints的ai_flags、ai_family、ai_socktype、ai_protocol。
 * 在6项参数中，对函数影响最大的是nodename，sername和hints.ai_flag，而ai_family只是有地址为v4地址或v6地址的区别。ai_protocol一般是为0不作改动。 
 * 一般情况下，client/server编程中，server端调用bind（如果面向连接的还需要listen）
 * client则不用调用bind函数，解析地址后直接connect（面向连接）或直接发送数据（无连接）
 *	- 通常服务器端在调用getaddrinfo之前，ai_flags设置AI_PASSIVE，用于bind；主机名hostname通常会设置为NULL，返回通配地址[::]
 *	- 客户端调用getaddrinfo时，ai_flags一般不设置AI_PASSIVE，但是主机名hostname和服务名service(更愿意称之为端口)则应该不为空
 *	- 使不设置AI_PASSIVE，取出的地址也并非不可以被bind，很多程序中ai_flags直接设置为0
 *	  即3个标志位都不设置，这种情况下只要hostname和service设置的没有问题就可以正确bind。
 * 
 * 由getaddrinfo返回的所有存储空间都是动态获取的，这些存储空间必须通过调用freeaddrinfo返回给系统。
 * gai_strerror用来获取getaddrinfo接口返回的错误码对应的错误信息，注意getaddrinfo不是设置errno
 * 
 * 返回值：0——成功，非0——出错
 * 果本函数返回成功，那么由result参数指向的变量已被填入一个指针.它指向的是由其中的ai_next成员串联起来的addrinfo结构链表
 * 可以导致返回多个addrinfo结构的情形有以下2个：
 *	- 如果与hostname参数关联的地址有多个，那么适用于所请求地址簇的每个地址都返回一个对应的结构
 *	- 如果service参数指定的服务支持多个套接口类型，那么每个套接口类型都可能返回一个对应的结构，具体取决于hints结构的ai_socktype成员
 * 我们必须先分配一个hints结构，把它清零后填写需要的字段，再调用getaddrinfo，然后遍历一个链表逐个尝试每个返回地址
 */
void Getaddrinfo(const char *hostname, const char *service, const struct addrinfo *hints, struct addrinfo **result)
{
	int rc;
	if ((rc = getaddrinfo(hostname, service, hints, result)) != 0) {
		gai_error(rc, "getaddrinfo error");
	}
}

/*
 * 是getaddrinfo的互补函数，以一个套接字地址为参数，返回描述其中的主机的一个字符串和描述其中的服务的另一个字符串
 * 它以与协议无关的方式将套接字地址转换为相应的主机和服务。
 * getnameinfo()是可重入的，允许程序消除IPv4-vs-IPv6依赖关系
 *
 *  sa参数是指向保存输入IP地址和端口号的salen大小的通用套接字地址结构(类型为sockaddr_in或sockaddr_in6)的指针
 *  参数host和serv是指向调用者分配的缓冲区(分别为hostlen和servlen大小)的指针，其中getnameinfo()分别放置包含主机和服务名称的以空结尾的字符串。
 *  调用方可以通过提供NULL的host(或serv)参数或0的hostlen(或servlen)参数来指定不需要主机名(或服务名)。
 *  但是，必须请求至少一个主机名或服务名称。
 *  flags参数修改getnameinfo的行为
 *  +=======================+===========================================+
 *  |	NI_DGRAM			|	数据报服务								|					
 *  +-----------------------+-------------------------------------------+
 *  |	NI_NAMEREQD			|	若不能从地址解析出名字则返回错误		|					
 *  +-----------------------+-------------------------------------------+
 *  |	NI_NIFQDN			|	只能返回NQDN的主机字符串				|					
 *  +-----------------------+-------------------------------------------+
 *  |	NI_NUMERICHOST		|	以数串格式返回主机字符串				|					
 *  +-----------------------+-------------------------------------------+
 *  |	NI_NUMERICSCOPE		|	以数串格式返回范围标识字符串			|					
 *  +-----------------------+-------------------------------------------+
 *  |	NI_NUMERICSERV		|	以数串格式返回服务字符串				|
 *  +-----------------------+-------------------------------------------+
 *  在成功时返回0，如果请求，节点和服务名称将填充以空结尾的字符串，可能会截断以适应指定的缓冲区长度
 */
void Getnameinfo(const struct sockaddr *sa, socklen_t salen, char *host, size_t hostlen, char *serv, size_t servlen, int flags)
{
	int rc;
	if ((rc = getnameinfo(sa, salen, host, hostlen, serv, servlen, flags)) != 0) {
		gai_error(rc, "getnameinfo error");
	}
}

/*
 * freeaddrinfo接口用来释放getaddrinfo接口返回的res指向的链表
 * 如果调用getaddrinfo接口后没有释放内存，会造成内存泄露，所以一定要记得调用这个接口来释放内存
 * void freeaddrinfo( struct addrinfo *result );
 * result参数应指向由getaddrinfo返回的第一个addrinfo结构。这个连表中的所有结构以及它们指向的任何动态存储空间都被释放掉
 */
void Freeaddrinfo(struct addrinfo *result)
{
	freeaddrinfo(result);
}

/*
 * 这两个函数是随IPv6出现的函数，对于IPv4地址和IPv6地址都适用
 * 函数中p和n分别代表表达（presentation)和数值（numeric)。地址的表达格式通常是ASCII字符串，数值格式则是存放到套接字地址结构的二进制值。
 * 这两个函数的family参数既可以是AF_INET（ipv4）也可以是AF_INET6（ipv6）
 * 如果，以不被支持的地址族作为family参数，这两个函数都返回一个错误，并将errno置为EAFNOSUPPORT.
 *
 * inet_pton()函数尝试转换由strptr指针所指向的字符串，并通过addrptr指针存放二进制结果
 * 若成功则返回值为1，否则如果所指定的family而言输入字符串不是有效的表达式格式，那么返回值为0.
 */
void Inet_pton(int family, const char *strptr, void *addrptr)
{
	int rc = inet_pton(family, strptr, addrptr);
	if (rc == 0) {
		app_error("inet_pton error: invalid dotted-decimal address");
	}else if (rc < 0) {
		unix_error("inet_pton error");
	}
}

/*
 * 实现 inet_ntoa()对ipv6的支持
 * inet_ntop()进行相反的转换，从数值格式（addrptr）转换到表达式（strptr)。
 * inet_ntop函数的strptr参数不可以是一个空指针。调用者必须为目标存储单元分配内存并指定其大小，调用成功时，这个指针就是该函数的返回值。
 * len参数是目标存储单元的大小，以免该函数溢出其调用者的缓冲区。如果len太小，不足以容纳表达式结果，那么返回一个空指针，并置为errno为ENOSPC。
 */
void Inet_ntop(int family, const void *addrptr, char *strptr, socklen_t len)
{
	if (!inet_ntop(family, src, dst, len)) {
		unix_error("inet_ntop error");
	}
}


/*
 * 将域名或者主机名转换为ip地址保存在hostent结构体中
 * 客户端中直接使用 IP 地址会有很大的弊端，一旦 IP 地址变化(IP 地址会经常变动)，客户端软件就会出现错误。
 * 而使用域名会方便很多，注册后的域名只要每年续费就永远属于自己的，更换 IP 地址时修改域名解析即可，不会影响软件的正常使用
 * 域名仅仅是 IP 地址的一个助记符，目的是方便记忆，通过域名并不能找到目标计算机，通信之前必须要将域名转换成 IP 地址
 *
 *	struct hostent{
 *		char *h_name;    //正式主机名
 *		char **h_aliases;  //主机别名
 *		int h_addrtype;  //主机ip地址类型 AF_INET AF_INET6
 *		int h_length;    //主机ip地址长度，对应的IPV4 是 4， 即32位 IPV6是16
 *		char **h_addr_list;  //主机ip地址列表
 *	};
 *
 */ 
struct hostent *Gethostbyname(const char *name)
{
	struct hostent *he;
	if ((he = Gethostbyname(name)) == NULL) {
		dns_error("Gethostbyname error");
	}
	return he;
}

/*
 * 通过一个IPv4的地址来获取主机信息，并放在hostent结构体中
 * addr是ip地址，但需要通过inet_aton()转换为网络字节序的32位二进制数
 * len是ip地址长度 4 / 6
 * type 族 AF_INET / AF_INET6
 */
struct hostent *Gethostbyaddr(const char *addr, int len, int type)
{
	struct hostent *he;
	if ((he = gethostbyaddr(addr, len, type)) == NULL) {
		dns_error("gethostbyaddr error");
	}
	return he;
}



void Pthread_create(pthread_t *pid, pthread_attr_t *pattr, void *(*handler)(void *), void *arg)
{
	int rc;
	if ((rc = pthread_create(pid, pattr, handler, arg)) != 0) {
		posix_error(rc, "Pthread_create error");
	}
}

void Pthread_cancel(pthread_t pid)
{
	int rc;
	if ((rc = pthread_cancel(pid)) != 0) {
		posix_error(rc, "pthread_cancel error");
	}
}
void Pthread_join(pthread_t pid, void **thread_return)
{
	int rc;
	if ((rc = pthread_join(pid, thread_return)) != 0) {
		posix_error(rc, "pthread_join error");
	}
}

void Pthread_detach(pthread_t pid)
{
	int rc;
	if ((rc = pthread_detach(pid)) != 0) {
		posix_error(rc, "pthread_detach error");
	}
}

void Pthread_exit(void *retval)
{
	pthread_exit(retval);
}

pthread_t Pthread_self()
{
	return pthread_self();
}

void Pthread_once(pthread_once_t *once_control, void(*init_fanction)())
{
	pthread_once(once_control, init_fanction);
}

/*
 * 信号量和互斥锁(mutex)的区别：互斥锁只允许一个线程进入临界区，而信号量允许多个线程同时进入临界区。
 * 其中sem是要初始化的信号量，pshared表示此信号量是在进程间共享还是线程间共享，value是信号量的初始值。
 * pshared不为０时此信号量在进程间共享，否则只能为当前进程的所有线程共享
 */
void Sem_init(sem_t *sem, int pshared, unsigned int value)
{
	if (sem_init(sem, pshared, value) < 0) {
		unix_error("sem_init error");
	}
}

/*
 * int sem_wait(sem_t *sem);等待信号量，如果信号量的值大于0,将信号量的值减1,立即返回。
 * 如果信号量的值为0,则线程阻塞。相当于P操作。成功返回0,失败返回-1。
 */
void P(sem_t *sem)
{
	if (sem_wait(sem) < 0) {
		unix_error("p error");
	}
}

/*
 * int sem_post(sem_t *sem); 释放信号量，让信号量的值加1。相当于V操作。
 */
void V(sem_t *sem)
{
	if (sem_post(sem) < 0) {
		unix_error("v error");
	}
}

/*
 * 传入一个主机名和端口号 返回相应的可用sockfd
 */

int open_client(char *hostname, char *port)
{
	int clientfd;
	struct addrinfo hints, *plist, *p;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_NUMERICSERV;
	hints.ai_flags |= AI_ADDRCONFIG;
	Getaddrinfo(hostname, port, &hints, &plist);

	for (p = plist; p != NULL; p = p->ai_next) {
		if ((clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) {
			continue;
		}
		if (connect(clientfd, p->ai_addr, p->ai_addrlen) != -1) {
			break;
		}
		Close(clientfd);
	}
	Freeaddrinfo(plist);
	if (!p) {
		return -1;
	}
	return clientfd;
}

/*
 * 通过传入参数port返回一个可以监听的sock套接字
 * 
 * 调用getaddrinfo()函数获得对应端口的返回地址
 * ai_flags设置AI_PASSIVE，(套接字地址用于监听绑定) 用于bind；主机名hostname通常会设置为NULL，返回通配地址[::]
 * ai_flags配置 AI_NUMERICSERV 以服务器返回端口号 配置AI_ADDRCONFIG查询配置地址类型
 * 将对应获得的每一个返回的地址和端口调用socket()获取套接字
 * setsockopt()通知内核，重用端口
 * bind() bind对应的addr在套接字上
 * listen() 进入listen状态
 *
 */
int open_listenfd(const char *port)
{
	struct addrinfo hints, *plist, *p;
	int listenfd, optval = 1;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_flags |= AI_NUMERICSERV;
	hints.ai_flags |= AI_ADDRCONFIG;
	Getaddrinfo(NULL, port, &hints, &plist);

	for (p = plist; p != NULL; p = p->ai_next) {
		if ((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) {
			continue;
		}
		Setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void*)&optval, sizeof(int));
		if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0) {
			break;
		}
		Close(listenfd);
	}

	Freeaddrinfo(plist);
	if (!p) {
		return -1;
	}
	if (listen(listenfd, LISTENQ) < 0) {
		return -1;
	}
	return listenfd;

}

int Open_clientfd(char *hostname, char *port)
{
	int rc;
	if ((rc = open_client(hostname, port)) < 0) {
		unix_error("open_clientfd error");
	}
	return rc;
}

int Open_listenfd(const char *port)
{
	int rc;
	if ((rc = open_listenfd(port)) < 0) {
		unix_error("open_listenfd error");
	}
	return rc;
}
