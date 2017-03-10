#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "errors.h"
#include "exec.h"
#include "ft_printf.h"

static const char	*g_sig_to_str[] = {
     [SIGHUP] = "Hangup",
     [SIGQUIT] = "Quit",
     [SIGILL] = "Illegal instruction",
     [SIGTRAP] = "Trace/BPT trap",
	 [SIGABRT] = "Abort trap",
     [SIGFPE] = "Floating point exception",
     [SIGKILL] = "Killed",
     [SIGBUS] = "Bus error",
     [SIGSEGV] = "Segmentation fault",
     [SIGSYS] = "Bad system call",
     [SIGALRM] = "Alarm clock",
     [SIGTERM] = "Terminated",
     [SIGSTOP] = "Suspended",
     [SIGTSTP] = "Terminal suspended",
     [SIGTTIN] = "Stopped (tty input)",
     [SIGTTOU] = "Stopped (tty ouput)",
     [SIGXCPU] = "Cputime limit exceeded",
     [SIGXFSZ] = "Filesize limit exceeded",
     [SIGVTALRM] = "Virtual timer expired",
     [SIGPROF] = "Profiler timer epxired",
     [SIGUSR1] = "User defined signal 1",
     [SIGUSR2] = "User defined signal 2",
};

static int get_exit_status(int status)
{
	int	sig;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (g_sig_to_str[sig])
			ft_printf("%d, %s\n", sig, g_sig_to_str[sig]);
		return (sig + 128);
	}
	return (-1);
}

int	wait_child_process_group(pid_t last_pid, pid_t pgid)
{
	pid_t		pid;
	int			status;
	int			ret;

	ret = -1;
	while ((pid = waitpid(pgid, &status, 0)) != -1)
	{
		if (pid == last_pid)
			ret = get_exit_status(status);
	}
	if (errno != ECHILD)
	{
		error_set_context("waitpid: %s", strerror(errno));
		error_print("execution");
	}
	return (ret);
}

pid_t	exec_fork(pid_t *pid)
{
	*pid = fork();
	if (*pid < 0)
	{
		error_set_context("fork: %s", strerror(errno));
		return (ERR_EXEC);
	}
	return (NO_ERROR);
}
