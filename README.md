이씨
- MessageHandler 의 _parse 채우기
- _tok 가져다가 pair 로 채우기

천씨
- MessageHandler 의 _fdTo, _sendMsg 채우기

Server
- kqueue, kevent 관리
- Channel list, fd list 보유

FileDescriptor
- 서버와 각 클라이언트 관리
- 클라이언트의 이름, 닉, 호스트이름, 가입한 채널, 현재 채널 등 각각의 클라이언트의 정보 관리

Channel
- 채널 객체
- 채널에 있는 사람들을 관리
- 서버에서 channel 벡터로 관리됨

Event Handler
- 들어온 이벤트를 관리
- 이벤트에서 recv 한 내용을 토대로 구현된 명령어 실행, 반환할 문자열 생성, 반환할 클라이언트 선별
- 서버에서 해당 객체를 보고 값 전송

``` default error 
ERR_NEEDMOREPARAMS
```

Pass
- 본인에게 반환
- fd 의 pass 변경
- server 의 pass 와 비교
```
ERR_PASSWDMISMATCH 464
```

Nick
- 본인에게 반환
- fd 의 nick 변경
- fd list 전부와 비교
```

```

User
- 본인에게 반환
- fd 의 name 변경
- 비교사항 없음

Quit
- 본인에게 반환
- 클라이언트가 들어가있는 모든 channel 에서 삭제
- 비교사항 없음

Join
- 본인, join 한 channel 의 클라이언트에게 반환
- 본인의 join list 와 join 한 channel 의 리스트 변경
- 비교사항 없음

Kick
- kick 대상이 join 되어있던 channel 의 모두에게 반환 ......??????
- kick 대상의 join list 와 join 되어있던 channel 의 리스트 변경
- 비교사항 없음

Part
- 본인이 join 되어있던 channel 의 모두에게 반환 ......??????
- 본인의 join list 와 join 되어있던 channel 의 리스트 변경
- 비교사항 없음
- 여러 채널 입력 가능 ',' 구분

Names
- 본인에게 반환
- 변경사항 없음
- 현재 본인이 있는 channel 의 유저목록과 각각 유저들의 권한 정보
- 여러 채널 입력 가능 ',' 구분

Privmsg
- 해당 닉네임의 상대 유저에게 반환
- 변경사항 없음
- 해당 닉네임의 상대 유저의 존대 유무 확인
- target ','로 구분해서 여러개 입력가능, 입력시 한줄씩 들어옴

Oper
- recv = OPER nick pass


Dcc
- cmd : /dcc send <path>
- cmd : /dcc get <nick> <file> //

names, join : operFd로 수정함 닉네임 맞춰서 넣어야됨