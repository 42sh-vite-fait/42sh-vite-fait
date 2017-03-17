#include <unistd.h>
#include <signal.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>

void block_all_signals(void)
{
	sigset_t	all;
	int			ret;

	ret = sigfillset(&all);
	assert(ret == 0);

	ret = sigprocmask(SIG_SETMASK, &all, NULL);
	assert(ret == 0);
}

void what_signals_is_blocked_by_default(void)
{
	sigset_t	blocked_sigs;
	int			ret;

	ret = sigprocmask(SIG_SETMASK, NULL, &blocked_sigs);
	assert(ret == 0);

	for (size_t i = 0; i < NSIG; ++i)
	{
		if (sigismember(&blocked_sigs, i))
			printf("%zu is blocked by default\n", i);
	}
}

void add_sig_to_mask(int sig)
{
	int			ret;
	sigset_t	set;

	ret = sigemptyset(&set);
	assert(ret == 0);

	ret = sigaddset(&set, sig);
	assert(ret == 0);

	if (sigismember(&set, sig))
		printf("Is a member of the set\n");

	ret = sigprocmask(SIG_BLOCK, &set, NULL);
	assert(ret == 0);
}

void pending_sigint(void)
{
	int			ret;
	sigset_t	set;

	ret = sigemptyset(&set);
	/* ret = sigfillset(&set); */
	assert(ret == 0);

	ret = sigaddset(&set, SIGINT);
	assert(ret == 0);

	// blocking SIGINT
	ret = sigprocmask(SIG_BLOCK, &set, NULL);
	assert(ret == 0);

	sleep(3);

	// is SIGINT pending ?
	sigset_t	pending;
	ret = sigpending(&pending);
	assert(ret == 0);
	if (sigismember(&pending, SIGINT))
		printf("SIGINT bien reçu\n");

	// sigaction
	struct sigaction	act;
	sigset_t			blocked_signals_during_handler;
	sigfillset(&blocked_signals_during_handler);
	act.sa_handler = SIG_IGN;
	act.sa_mask = blocked_signals_during_handler;
	ret = sigaction(SIGINT, &act, NULL);
	assert(ret == 0);

	// unblocking the signal
	sigprocmask(SIG_UNBLOCK, &pending, NULL);
	printf("post sigprocmask\n");
}

void handler_sigint(int sig)
{
	printf("%s\n", __func__);
}

void ignore_sig_before_block(void)
{
	struct sigaction	act;
	sigset_t			set;

	// ignore SIGINT
	act.sa_handler = SIG_IGN;
	/* act.sa_handler = &handler_sigint; */
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT, &act, NULL);

	// block SIGINT
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigprocmask(SIG_BLOCK, &set, NULL);

	// raise SIGINT
	raise(SIGINT);
	printf("post raise()\n");

	sigset_t	pending;
	sigpending(&pending);
	if (sigismember(&pending, SIGINT))
		printf("SIGINT is pending\n");

	sigprocmask(SIG_UNBLOCK, &set, NULL);
	printf("post unblock\n");
}

void read_sigint(void)
{
	struct sigaction act;
	act.sa_handler = &handler_sigint;
	sigaction(SIGINT, &act, NULL);

	char c;
	if (read(0, &c, 1) == -1 && errno == EINTR)
		printf("failed");
	else
		printf("char %c\n", c);
}

int main(void)
{
	/* add_sig_to_mask(SIGQUIT); */
	/* pause(); */

	/* block_all_signals(); */
	/* pending_sigint(); */
	/* ignore_sig_before_block(); */
	read_sigint();
}
