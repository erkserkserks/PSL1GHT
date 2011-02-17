#pragma once

#include <psl1ght/types.h>
#include <sys/types.h>

typedef u64	socklen_t;
typedef u8	sa_family_t;

struct sockaddr
{
	u8			sa_len;
	sa_family_t	sa_family;
	char		sa_data[];
};

struct iovec
{
	void*	iov_base;
	size_t	iov_len;
};

struct msghdr
{
	void*			msg_name;
	socklen_t		msg_namelen;
	struct iovec*	msg_iov;
	int				msg_iovlen;
	void*			msg_control;
	socklen_t		msg_controllen;
	int				msg_flags;
};

struct cmsghdr
{
	socklen_t     cmsg_len;
	int           cmsg_level;
	int           cmsg_type;
};

struct linger
{
	int l_onoff;
	int l_linger;
};

#define SOCK_STREAM		0x0001
#define SOCK_DGRAM		0x0002
#define SOCK_RAW		0x0003

#define SOL_SOCKET		0xFFFF

#define SO_REUSEADDR	0x0004
#define SO_KEEPALIVE	0x0008
#define SO_BROADCAST	0x0020
#define SO_LINGER		0x0080
#define SO_OOBINLINE	0x0100
#define SO_REUSEPORT	0x0200
#define SO_SNDBUF		0x1001
#define SO_RCVBUF		0x1002
#define SO_SNDLOWAT		0x1003
#define SO_RCVLOWAT		0x1004
#define SO_SNDTIMEO		0x1005
#define SO_RCVTIMEO		0x1006
#define SO_ERROR		0x1007
#define SO_TYPE			0x1008
#define SO_NBIO			0x1100

#define MSG_OOB			0x0001
#define MSG_PEEK		0x0002
#define MSG_DONTROUTE	0x0004
#define MSG_EOR			0x0008
#define MSG_TRUNC		0x0010
#define MSG_CTRUNC		0x0020
#define MSG_WAITALL		0x0040
#define MSG_DONTWAIT	0x0080
#define MSG_BCAST		0x0100
#define MSG_MCAST		0x0200

#define AF_UNSPEC		0x0000
#define AF_UNIX			0x0001
#define AF_INET			0x0002
#define AF_INET6		0x0018
#define AF_MAX			0x0020

#define SHUT_RD			0x0000
#define SHUT_WR			0x0001
#define SHUT_RDWR		0x0002

#define PF_INET			AF_INET
#define PF_INET6		AF_INET6

#define	NET_EPERM		1
#define	NET_ENOENT		2
#define	NET_ESRCH		3
#define	NET_EINTR		4
#define	NET_EIO			5
#define	NET_ENXIO		6
#define	NET_E2BIG		7
#define	NET_ENOEXEC		8
#define	NET_EBADF		9
#define	NET_ECHILD		10
#define	NET_EDEADLK		11
#define	NET_ENOMEM		12
#define	NET_EACCES		13
#define	NET_EFAULT		14
#define	NET_ENOTBLK		15
#define	NET_EBUSY		16
#define	NET_EEXIST		17
#define	NET_EXDEV		18
#define	NET_ENODEV		19
#define	NET_ENOTDIR		20
#define	NET_EISDIR		21
#define	NET_EINVAL		22
#define	NET_ENFILE		23
#define	NET_EMFILE		24
#define	NET_ENOTTY		25
#define	NET_ETXTBSY		26
#define	NET_EFBIG		27
#define	NET_ENOSPC		28
#define	NET_ESPIPE		29
#define	NET_EROFS		30
#define	NET_EMLINK		31
#define	NET_EPIPE		32
#define	NET_EDOM		33
#define	NET_ERANGE		34
#define	NET_EAGAIN		35
#define	NET_EWOULDBLOCK		NET_EAGAIN
#define	NET_EINPROGRESS		36
#define	NET_EALREADY		37
#define	NET_ENOTSOCK		38
#define	NET_EDESTADDRREQ	39
#define	NET_EMSGSIZE		40
#define	NET_EPROTOTYPE		41
#define	NET_ENOPROTOOPT		42
#define	NET_EPROTONOSUPPORT	43
#define	NET_ESOCKTNOSUPPORT	44
#define	NET_EOPNOTSUPP		45
#define	NET_EPFNOSUPPORT	46
#define	NET_EAFNOSUPPORT	47
#define	NET_EADDRINUSE		48
#define	NET_EADDRNOTAVAIL	49
#define	NET_ENETDOWN		50
#define	NET_ENETUNREACH		51
#define	NET_ENETRESET		52
#define	NET_ECONNABORTED	53
#define	NET_ECONNRESET		54
#define	NET_ENOBUFS		55
#define	NET_EISCONN		56
#define	NET_ENOTCONN		57
#define	NET_ESHUTDOWN		58
#define	NET_ETOOMANYREFS	59
#define	NET_ETIMEDOUT		60
#define	NET_ECONNREFUSED	61
#define	NET_ELOOP		62
#define	NET_ENAMETOOLONG	63
#define	NET_EHOSTDOWN		64
#define	NET_EHOSTUNREACH	65
#define	NET_ENOTEMPTY		66
#define	NET_EPROCLIM		67
#define	NET_EUSERS		68
#define	NET_EDQUOT		69
#define	NET_ESTALE		70
#define	NET_EREMOTE		71
#define	NET_EBADRPC		72
#define	NET_ERPCMISMATCH	73
#define	NET_EPROGUNAVAIL	74
#define	NET_EPROGMISMATCH	75
#define	NET_EPROCUNAVAIL	76
#define	NET_ENOLCK		77
#define	NET_ENOSYS		78
#define	NET_EFTYPE		79
#define	NET_EAUTH		80
#define	NET_ENEEDAUTH		81
#define	NET_EIDRM		82
#define	NET_ENOMSG		83
#define	NET_EOVERFLOW		84
#define	NET_EILSEQ		85
#define	NET_ENOTSUP		86
#define	NET_ECANCELED		87
#define	NET_EBADMSG		88
#define	NET_ENODATA		89
#define	NET_ENOSR		90
#define	NET_ENOSTR		91
#define	NET_ETIME		92
#define	NET_ELAST		92



#define SOCKET_FD_MASK	0x40000000


EXTERN_BEGIN

int accept(int socket, struct sockaddr* address, socklen_t* address_len);
int bind(int socket, const struct sockaddr* address, socklen_t address_len);
int connect(int socket, const struct sockaddr* address, socklen_t address_len);
int getpeername(int socket, struct sockaddr* address, socklen_t* address_len);
int getsockname(int socket, struct sockaddr* address, socklen_t* address_len);
int getsockopt(int socket, int level, int option_name, void* option_value, socklen_t* option_len);
int listen(int socket, int backlog);
ssize_t recv(int socket, void* buffer, size_t length, int flags);
ssize_t recvfrom(int socket, void* buffer, size_t length, int flags,
		struct sockaddr* address, socklen_t* address_len);
ssize_t recvmsg(int socket, struct msghdr* message, int flags);
ssize_t send(int socket, const void* message, size_t length, int flags);
ssize_t sendto(int socket, const void* message, size_t length, int flags,
		const struct sockaddr* dest_addr, socklen_t dest_len);
ssize_t sendmsg(int socket, const struct msghdr* message, int flags);
int setsockopt(int socket, int level, int option_name, const void* option_value,
		socklen_t option_len);
int shutdown(int socket, int how);
int socket(int domain, int type, int protocol);
int socketpair(int domain, int type, int protocol, int socket_vector[2]);
s32 closesocket(int socket);

EXTERN_END
