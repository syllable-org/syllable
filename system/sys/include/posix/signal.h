#ifndef	_POSIX_SIGNALS_H_
#define	_POSIX_SIGNALS_H_

#include <posix/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define _NSIG             32
#define NSIG		_NSIG

#define SIGHUP		 1
#define SIGINT		 2
#define SIGQUIT		 3
#define SIGILL		 4
#define SIGTRAP		 5
#define SIGABRT		 6
#define SIGIOT		 6
#define SIGBUS		 7
#define SIGFPE		 8
#define SIGKILL		 9
#define SIGUSR1		10
#define SIGSEGV		11
#define SIGUSR2		12
#define SIGPIPE		13
#define SIGALRM		14
#define SIGTERM		15
#define SIGSTKFLT	16
#define SIGCHLD		17
#define SIGCONT		18
#define SIGSTOP		19
#define SIGTSTP		20
#define SIGTTIN		21
#define SIGTTOU		22
#define SIGURG		23
#define SIGXCPU		24
#define SIGXFSZ		25
#define SIGVTALRM	26
#define SIGPROF		27
#define SIGWINCH	28
#define SIGPWR		30
#define	SIGUNUSED	31

#ifdef __KERNEL__

/*
 * sa_flags values: SA_STACK is not currently supported, but will allow the
 * usage of signal stacks by using the (now obsolete) sa_restorer field in
 * the sigaction structure as a stack pointer. This is now possible due to
 * the changes in signal handling. LBT 010493.
 * SA_INTERRUPT is a no-op, but left due to historical reasons. Use the
 * SA_RESTART flag to get restarting signals (which were the default long ago)
 * SA_SHIRQ flag is for shared interrupt support on PCI and EISA.
 */

#define SA_NOCLDSTOP	1
#define SA_SHIRQ	0x04000000
#define SA_STACK	0x08000000
#define SA_RESTART	0x10000000
#define SA_INTERRUPT	0x20000000
#define SA_NOMASK	0x40000000
#define SA_NODEFER	SA_NOMASK
#define SA_ONESHOT	0x80000000

/*
 * These values of sa_flags are used only by the kernel as part of the
 * irq handling routines.
 *
 * SA_INTERRUPT is also used by the irq handling routines.
 */
#define SA_PROBE SA_ONESHOT
#define SA_SAMPLE_RANDOM SA_RESTART


#define SIG_BLOCK          0	/* for blocking signals */
#define SIG_UNBLOCK        1	/* for unblocking signals */
#define SIG_SETMASK        2	/* for setting the signal mask */

typedef	unsigned long sigset_t;

/* Type of a signal handler.  */
typedef void (*__sighandler_t)(int);

typedef struct sigaction
{
  sighandler_t sa_handler;
  sigset_t 	sa_mask;
  unsigned long sa_flags;
  void 		(*sa_restorer)(void);
} SigAction_s;

/* Values returned from GetSignalMode() */

#define	SIG_HANDLED	1
#define SIG_IGNORED	2
#define	SIG_DEFAULT 3
#define SIG_BLOCKED 4

int get_signal_mode( int nSigNum );

int	sys_kill( const thread_id hThread, const int nSigNum );
int	sys_sigaction( const int nSigNum, const struct sigaction * const psAction, struct sigaction * const psOldAct );
int	is_signal_pending( void );
void	send_alarm_signals( bigtime_t nCurTime );

int	raise(int _sig);
void	(*signal(int nSig, void (*pFunc)(int)))(int);

int	kill( pid_t nPid, int nSig );
int	sigaction( int nSig, const struct sigaction *psAct, struct sigaction *psOldAct );
int	sigaddset( sigset_t *pSet, int nSigNo );
int	sigdelset( sigset_t *pSet, int nSigNo );
int	sigemptyset( sigset_t *pSet );
int	sigfillset( sigset_t *pSet );
int	sigismember( const sigset_t *pSet, int nSigNo );
int	sigpending( sigset_t *pSet );
int	sigprocmask( int nHow, const sigset_t *pSet, sigset_t *pOldSet );
int	sigsuspend( const sigset_t *pSet );

#endif /* __KERNEL__ */

#define SIG_DFL	((__sighandler_t)0)	/* default signal handling */
#define SIG_IGN	((__sighandler_t)1)	/* ignore signal */
#define SIG_ERR	((__sighandler_t)-1)	/* error return from signal */

#include <atheos/pthreadsignal.h>

#ifdef __cplusplus
}
#endif


#endif	/*	_POSIX_SIGNALS_H_ */
