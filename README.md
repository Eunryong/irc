# IRC

make Internet Relay Chat protocol Server

## 명령어

-   PASS

    서버에 연결할 때 서버의 패스워드와 비교해서 접속한다.

-   NICK

    서버에 연결할 때 또는 닉네임을 변경하고 싶을때 이용한다.

-   USER

    서버에 연결할 때 유저의 정보를 전송한다.

-   QUIT

    서버와 접속을 끊을때 이용한다.

-   JOIN

    채널에 가입할 떄 이용한다.

-   KICK

    채널 관리자가 채널에 접속한 클라이언트를 추방 시킬때 이용한다.

-   PART

    채널에서 나갈때 이용한다.

-   NAMES

    채널에 접속한 클라이언트의 닉네임을 나열한다.

-   PRIVMSG

    개인이나 채널에 메세지를 보낼때 이용한다.

## 소켓

-   socket: 소켓을 생성한다.
-   bind: ip와 port를 지정한다.
-   listen: 클라이언트의 접속을 대기한다.
-   accept: 클라이언트가 접속을 시도하면 연결시켜준다.

## 멀티플렉싱

하나의 통신채널을 통해 둘 이상의 데이터를 전송하는데 사용되는 기술

-   kqueue

커널에 새로운 이벤트 큐를 만들고 fd를 리턴한다. fd는 kevnet에서 이벤트 등록, 모니터링에 사용된다.

```c++
int kqueue(void);
```

-   kevent

kevnet는 시스템 호출은 대기열에 이벤트를 등록하고 보류 중인 모든 이벤트를 반환하는 데 사용됩니다.

```c++
struct kevent {
    uintptr_t ident;        /* identifier for this event */
    int16_t   filter;       /* filter for event */
    uint16_t  flags;        /* action flags for kqueue */
    uint32_t  fflags;       /* filter flag value */
    intptr_t  data;         /* filter data value */
    void      *udata;       /* opaque user data identifier */
};
```

-   ident: event식별자, fd를 사용한다.
-   filter: 이벤트를 처리하는데 사용되는 커널필터를 설정한다.
-   flags: 이벤트에 대해 수행할 작업
-   fflags: filter에 따라 다르게 적용되는 flag
-   data: filter에 따라 다르게 적용되는 data
-   udata: event와 함께 등록하여 event return시 사용할 수 있는 user-data이다. udata 또한 event의 식별자로 사용될 수 있다.

EV_SET을 통해 이벤트를 설정해준다

```c++
// EV_SET(&kev, ident, filter, flags, fflags, data, udata); // kevent 구조체의 주소를 전달
void Multiplex::eventSet(uintptr_t ident, int16_t filter,
						uint16_t flags, uint32_t fflags,
						intptr_t data, void *udata) {
	struct kevent temp_event;

	EV_SET(&temp_event, ident, filter, flags, fflags, data, udata);
	_events.push_back(temp_event);
}
```
