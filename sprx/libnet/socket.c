#include <psl1ght/lv2/net.h>

#include <psl1ght/lv2/errno.h>

#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>

int h_errno = 0;

#define FD(socket) (socket & ~SOCKET_FD_MASK)

void* __netMemory = NULL;
#define LIBNET_INITIALIZED (__netMemory)

const static int neterrno2errno[] = {
	[NET_EPERM] = EPERM,
	[NET_ENOENT] = ENOENT,
	[NET_ESRCH] = ESRCH,
	[NET_EINTR] = EINTR,
	[NET_EIO] = EIO,
	[NET_ENXIO] = ENXIO,
	[NET_E2BIG] = E2BIG,
	[NET_ENOEXEC] = ENOEXEC,
	[NET_EBADF] = EBADF,
	[NET_ECHILD] = ECHILD,
	[NET_EDEADLK] = EDEADLK,
	[NET_ENOMEM] = ENOMEM,
	[NET_EACCES] = EACCES,
	[NET_EFAULT] = EFAULT,
	[NET_ENOTBLK] = ENOTSUP, // no match
	[NET_EBUSY] = EBUSY,
	[NET_EEXIST] = EEXIST,
	[NET_EXDEV] = EXDEV,
	[NET_ENODEV] = ENODEV,
	[NET_ENOTDIR] = ENOTDIR,
	[NET_EISDIR] = EISDIR,
	[NET_EINVAL] = EINVAL,
	[NET_ENFILE] = ENFILE,
	[NET_EMFILE] = EMFILE,
	[NET_ENOTTY] = ENOTTY,
	[NET_ETXTBSY] = ETXTBSY,
	[NET_EFBIG] = EFBIG,
	[NET_ENOSPC] = ENOSPC,
	[NET_ESPIPE] = ESPIPE,
	[NET_EROFS] = EROFS,
	[NET_EMLINK] = EMLINK,
	[NET_EPIPE] = EPIPE,
	[NET_EDOM] = EDOM,
	[NET_ERANGE] = ERANGE,
	[NET_EAGAIN] = EAGAIN,
	[NET_EWOULDBLOCK] = EWOULDBLOCK,
	[NET_EINPROGRESS] = EINPROGRESS,
	[NET_EALREADY] = EALREADY,
	[NET_ENOTSOCK] = ENOTSOCK,
	[NET_EDESTADDRREQ] = EDESTADDRREQ,
	[NET_EMSGSIZE] = EMSGSIZE,
	[NET_EPROTOTYPE] = EPROTOTYPE,
	[NET_ENOPROTOOPT] = ENOPROTOOPT,
	[NET_EPROTONOSUPPORT] = EPROTONOSUPPORT,
	[NET_ESOCKTNOSUPPORT] = EPROTONOSUPPORT, // no match
	[NET_EOPNOTSUPP] = EOPNOTSUPP,
	[NET_EPFNOSUPPORT] = EPFNOSUPPORT,
	[NET_EAFNOSUPPORT] = EAFNOSUPPORT,
	[NET_EADDRINUSE] = EADDRINUSE,
	[NET_EADDRNOTAVAIL] = EADDRNOTAVAIL,
	[NET_ENETDOWN] = ENETDOWN,
	[NET_ENETUNREACH] = ENETUNREACH,
	[NET_ENETRESET] = ENETRESET,
	[NET_ECONNABORTED] = ECONNABORTED,
	[NET_ECONNRESET] = ECONNRESET,
	[NET_ENOBUFS] = ENOBUFS,
	[NET_EISCONN] = EISCONN,
	[NET_ENOTCONN] = ENOTCONN,
	[NET_ESHUTDOWN] = ENOTCONN, // no match
	[NET_ETOOMANYREFS] = ETOOMANYREFS,
	[NET_ETIMEDOUT] = ETIMEDOUT,
	[NET_ECONNREFUSED] = ECONNREFUSED,
	[NET_ELOOP] = ELOOP,
	[NET_ENAMETOOLONG] = ENAMETOOLONG,
	[NET_EHOSTDOWN] = EHOSTDOWN,
	[NET_EHOSTUNREACH] = EHOSTUNREACH,
	[NET_ENOTEMPTY] = ENOTEMPTY,
	[NET_EPROCLIM] = ENOTSUP, // no match
	[NET_EUSERS] = ENOTSUP, // no match
	[NET_EDQUOT] = EDQUOT,
	[NET_ESTALE] = ESTALE,
	[NET_EREMOTE] = ENOTSUP, // no match
	[NET_EBADRPC] = ENOTSUP, // no match
	[NET_ERPCMISMATCH] = ENOTSUP, // no match
	[NET_EPROGUNAVAIL] = ENOTSUP, // no match
	[NET_EPROGMISMATCH] = ENOTSUP, // no match
	[NET_EPROCUNAVAIL] = ENOTSUP, // no match
	[NET_ENOLCK] = ENOLCK,
	[NET_ENOSYS] = ENOSYS,
	[NET_EFTYPE] = EFTYPE,
	[NET_EAUTH] = EPERM, // no match
	[NET_ENEEDAUTH] = EPERM, // no match
	[NET_EIDRM] = EIDRM,
	[NET_ENOMSG] = ENOMSG,
	[NET_EOVERFLOW] = EOVERFLOW,
	[NET_EILSEQ] = EILSEQ,
	[NET_ENOTSUP] = ENOTSUP,
	[NET_ECANCELED] = ECANCELED,
	[NET_EBADMSG] = EBADMSG,
	[NET_ENODATA] = ENODATA,
	[NET_ENOSR] = ENOSR,
	[NET_ENOSTR] = ENOSTR,
	[NET_ETIME] = ETIME
};


int netErrno(int ret)
{
	if (!LIBNET_INITIALIZED)
		return lv2Errno(ret);

	if (ret >= 0)
		return ret;

	if (net_errno < sizeof(neterrno2errno) / sizeof(neterrno2errno[0]))
		errno = neterrno2errno[net_errno] ?: EPERM;

	return -1;
}

int accept(int socket, struct sockaddr* address, socklen_t* address_len)
{
	s32 ret;
	net_socklen_t len;
	net_socklen_t* lenp = (address && address_len) ? &len : NULL;
	if (LIBNET_INITIALIZED)
		ret = netAccept(FD(socket), address, lenp);
	else
		ret = lv2NetAccept(FD(socket), address, lenp);

	if (ret < 0)
		return netErrno(ret);

	if (lenp)
		*address_len = len;

	return ret | SOCKET_FD_MASK;
}

int bind(int socket, const struct sockaddr* address, socklen_t address_len)
{
	s32 ret;
	if (LIBNET_INITIALIZED)
		ret = netBind(FD(socket), address, (net_socklen_t)address_len);
	else
		ret = lv2NetBind(FD(socket), address, (net_socklen_t)address_len);
	return netErrno(ret);
}

int connect(int socket, const struct sockaddr* address, socklen_t address_len)
{
	s32 ret;
	if (LIBNET_INITIALIZED)
		ret = netConnect(FD(socket), address, (net_socklen_t)address_len);
	else
		ret = lv2NetConnect(FD(socket), address, (net_socklen_t)address_len);
	return netErrno(ret);
}

int listen(int socket, int backlog)
{
	s32 ret;
	if (LIBNET_INITIALIZED)
		ret = netListen(FD(socket), backlog);
	else
		ret = lv2NetListen(FD(socket), backlog);
	return netErrno(ret);
}

int socket(int domain, int type, int protocol)
{
	s32 ret;
	if (LIBNET_INITIALIZED)
		ret = netSocket(domain, type, protocol);
	else
		ret = lv2NetSocket(domain, type, protocol);

	if (ret < 0)
		return netErrno(ret);
	
	return ret | SOCKET_FD_MASK;
}

ssize_t send(int socket, const void* message, size_t length, int flags)
{
	s32 ret;
	if (LIBNET_INITIALIZED)
		ret = netSend(FD(socket), message, length, flags);
	else
		return sendto(socket, message, length, flags, NULL, 0);
	return netErrno(ret);
}

ssize_t sendto(int socket, const void* message, size_t length, int flags, const struct sockaddr* dest_addr, socklen_t dest_len)
{
	s32 ret;
	if (LIBNET_INITIALIZED)
		ret = netSendTo(FD(socket), message, length, flags, dest_addr, (net_socklen_t)dest_len);
	else
		ret = lv2NetSendTo(FD(socket), message, length, flags, dest_addr, (net_socklen_t)dest_len);
	return netErrno(ret);
}

ssize_t recv(int s, void *buf, size_t len, int flags)
{
	s32 ret;
	if (LIBNET_INITIALIZED)
		ret = netRecv(FD(s),buf,len,flags);
	else
		return recvfrom(s, buf, len, flags, NULL, NULL);
	return netErrno(ret);
}

ssize_t recvfrom(int s, void *buf, size_t len, int flags, struct sockaddr* from, socklen_t* fromlen)
{
	s32 ret;
	net_socklen_t socklen;
	net_socklen_t* socklenp = (from && fromlen) ? &socklen : NULL;
	if (LIBNET_INITIALIZED)
		ret = netRecvFrom(FD(s), buf, len, flags, from, socklenp);
	else
		ret = lv2NetRecvFrom(FD(s), buf, len, flags, from, socklenp);
	
	if (ret < 0)
		return netErrno(ret);

	if (socklenp)
		*fromlen = socklen;

	return ret;
}

int shutdown(int socket, int how)
{
	s32 ret;
	if (LIBNET_INITIALIZED)
		ret = netShutdown(FD(socket), how);
	else
		ret = lv2NetShutdown(FD(socket), how);
	return netErrno(ret);
}

int closesocket(int socket)
{
	s32 ret;
	if (LIBNET_INITIALIZED)
		ret = netClose(FD(socket));
	else
		ret = lv2NetClose(FD(socket));
	return netErrno(ret);
}

int select(int nfds, fd_set* readfds, fd_set* writefds, fd_set* errorfds, struct timeval_32* timeout)
{
	s32 ret;
	if (LIBNET_INITIALIZED){
		ret = netSelect(nfds, readfds, writefds, errorfds, timeout);
		printf("netSelect(%d) = %08X\n", nfds, ret);
	}
	else
		ret = lv2NetSelect(nfds, readfds, writefds, errorfds, timeout);

	return netErrno(ret);
}

int poll(struct pollfd fds[], nfds_t nfds, int timeout)
{
	int i, r;
	if (!LIBNET_INITIALIZED) {
		errno = ENOSYS;
		return -1;
	}
	for (i = 0; i < nfds; i++)
		fds[i].fd &= ~SOCKET_FD_MASK;
	r = netErrno(netPoll(fds, nfds, timeout));
	for (i = 0; i < nfds; i++)
		fds[i].fd |= SOCKET_FD_MASK;
	return r;
}

int getsockname(int socket, struct sockaddr* address, socklen_t* address_len)
{
	s32 ret;
	net_socklen_t len;
	net_socklen_t* lenp = (address && address_len) ? &len : NULL;
	if (LIBNET_INITIALIZED)
		ret = netGetSockName(FD(socket), address, lenp);
	else
		ret = lv2NetGetSockName(FD(socket), address, lenp);

	if (ret < 0)
		return netErrno(ret);

	if (lenp)
		*address_len = len;

	return ret;
}

int getpeername(int socket, struct sockaddr* address, socklen_t* address_len)
{
	s32 ret;
	net_socklen_t len;
	net_socklen_t* lenp = (address && address_len) ? &len : NULL;
	if (LIBNET_INITIALIZED)
		ret = netGetPeerName(FD(socket), address, lenp);
	else
		ret = lv2NetGetPeerName(FD(socket), address, lenp);

	if (ret < 0)
		return netErrno(ret);

	if (lenp)
		*address_len = len;

	return ret;
}

#define MAX_HOST_NAMES 0x20
static struct hostent host;
static char* hostaliases[MAX_HOST_NAMES];
static char* hostaddrlist[MAX_HOST_NAMES];
static struct hostent* copyhost(struct net_hostent* nethost)
{
	if (!nethost)
		return NULL;

	memset(&host, 0, sizeof(host));
	host.h_name = (char*)(u64)nethost->h_name;
	host.h_addrtype = nethost->h_addrtype;
	host.h_length = nethost->h_length;
	host.h_aliases = hostaliases;
	host.h_addr_list = hostaddrlist;

	lv2_void* netaddrlist = (lv2_void*)(u64)nethost->h_addr_list;
	lv2_void* netaliases = (lv2_void*)(u64)nethost->h_aliases;
	for (int i = 0; i < MAX_HOST_NAMES; i++) {
		host.h_addr_list[i] = (char*)(u64)netaddrlist[i];
		if (!netaddrlist[i])
			break;
	}
	for (int i = 0; i < MAX_HOST_NAMES; i++) {
		host.h_aliases[i] = (char*)(u64)netaliases[i];
		if (!netaliases[i])
			break;
	}

	return &host;
}
struct hostent* gethostbyaddr(const char* addr, socklen_t len, int type)
{
	if (!LIBNET_INITIALIZED) {
		errno = ENOSYS;
		h_errno = TRY_AGAIN;
		return NULL;
	}

	struct net_hostent* ret = netGetHostByAddr(addr, (net_socklen_t)len, type);
	if (!ret)
		h_errno = net_h_errno;

	return copyhost(ret);
}

struct hostent* gethostbyname(const char* name)
{
	if (!LIBNET_INITIALIZED) {
		errno = ENOSYS;
		h_errno = TRY_AGAIN;
		return NULL;
	}

	struct net_hostent* ret = netGetHostByName(name);
	if (!ret)
		h_errno = net_h_errno;

	return copyhost(ret);
}

int getsockopt(int socket, int level, int option_name, void* option_value, socklen_t* option_len)
{
	if (!LIBNET_INITIALIZED) {
		errno = ENOSYS;
		h_errno = TRY_AGAIN;
		return -1;
	}
	return netErrno(netGetSockOpt(FD(socket), level, option_name, option_value, option_len));
}

int setsockopt(int socket, int level, int option_name, const void* option_value, socklen_t option_len)
{
	if (!LIBNET_INITIALIZED) {
		errno = ENOSYS;
		h_errno = TRY_AGAIN;
		return -1;
	}
	return netErrno(netSetSockOpt(FD(socket), level, option_name, option_value, option_len));
}
