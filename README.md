# 📘 Docker + VSCode DevContainer 기반 C 개발 환경 구축 가이드 (RBTree)

## 📘 0. 개요 (전체 목적 요약)

이 프로젝트는 Red-Black Tree 자료구조를 C언어로 직접 구현하고, Docker + VSCode DevContainer를 활용하여 OS에 관계없이 일관된 개발/디버깅 환경을 제공하는 것을 목표로 합니다.

---

## 1. Docker란 무엇인가요?

**Docker**는 애플리케이션을 어떤 컴퓨터에서든 **동일한 환경에서 실행**할 수 있게 도와주는 **가상화 플랫폼**입니다.  

Docker는 다음 구성요소로 이루어져 있습니다:

- **Docker Engine**: 컨테이너를 실행하는 핵심 서비스
- **Docker Image**: 컨테이너 생성에 사용되는 템플릿 (레시피 📃)
- **Docker Container**: 이미지를 기반으로 생성된 실제 실행 환경 (요리 🍜)

### ✅ AWS EC2와의 차이점

| 구분 | EC2 같은 VM | Docker 컨테이너 |
|------|-------------|-----------------|
| 실행 단위 | OS 포함 전체 | 애플리케이션 단위 |
| 실행 속도 | 느림 (수십 초 이상) | 매우 빠름 (거의 즉시) |
| 리소스 사용 | 무거움 | 가벼움 |

---

## 2. VSCode DevContainer란 무엇인가요?

**DevContainer**는 VSCode에서 Docker 컨테이너를 **개발 환경**처럼 사용할 수 있게 해주는 기능입니다.

- 코드를 실행하거나 디버깅할 때 **컨테이너 내부 환경에서 동작**
- 팀원 간 **환경 차이 없이 동일한 개발 환경 구성** 가능
- `.devcontainer` 폴더에 정의된 설정을 VSCode가 읽어 자동 구성

---

## 3. Docker Desktop 설치하기

1. Docker 공식 사이트에서 설치 파일 다운로드:  
   👉 [https://www.docker.com/products/docker-desktop](https://www.docker.com/products/docker-desktop)

2. 설치 후 Docker Desktop 실행  
   - Windows: Docker 아이콘이 트레이에 떠야 함  
   - macOS: 상단 메뉴바에 Docker 아이콘 확인

---

## 4. 프로젝트 파일 다운로드 (히스토리 없이)

터미널(CMD, PowerShell, zsh 등)에서 아래 명령어로 프로젝트 폴더만 내려받습니다:

```bash
git clone --depth=1 https://github.com/krafton-jungle/rbtree_lab_docker.git
```

- `--depth=1` 옵션은 git commit 히스토리를 생략하고 **최신 파일만 가져옵니다.**

### 📂 다운로드 후 폴더 구조 설명

```
rbtree_lab_docker/
├── .devcontainer/
│   ├── devcontainer.json      # VSCode에서 컨테이너 환경 설정
│   └── Dockerfile             # C 개발 환경 이미지 정의
│
├── .vscode/
│   ├── launch.json            # 디버깅 설정 (F5 실행용)
│   └── tasks.json             # 컴파일 자동화 설정
│
├── rbtree_lab
│   ├── src/                    # 소스 폴더
│   ├── test/                   # test 폴더
│   ├── Makefile                # 과제를 컴파일하고 테스트하기 위한 파일
│   └── README.md               # rbtree 과제 설명
│
└── README.md  # 설치 및 사용법 설명 문서
```

---

## 5. VSCode에서 해당 프로젝트 폴더 열기

1. VSCode를 실행
2. `파일 → 폴더 열기`로 방금 클론한 `rbtree_lab_docker` 폴더를 선택

---

## 6. 개발 컨테이너: 컨테이너에서 열기

1. VSCode에서 `Ctrl+Shift+P` (Windows/Linux) 또는 `Cmd+Shift+P` (macOS)를 누릅니다.
2. 명령어 팔레트에서 `Dev Containers: Reopen in Container`를 선택합니다.
3. 이후 컨테이너가 자동으로 실행되고 빌드됩니다. 처음 컨테이너를 열면 빌드하는 시간이 오래걸릴 수 있습니다. 빌드 후, 프로젝트가 **컨테이너 안에서 실행됨**.

---

## 7. C 파일에 브레이크포인트 설정 후 디버깅 (F5)

이제 본격적으로 문제를 풀 시간입니다. `rbtree_lab/README.md` 파일을 참조하셔서 rbtree 문제를 풀어보세요.

C 언어로 문제를 풀다가 디버깅이 필요하시면 소스코드에 BreakPoint를 설정한 뒤에 키보드에서 `F5`를 눌러 디버깅을 시작할 수 있습니다.`F5`를 누르면 `rbtree_lab`폴더에서 `make test` 를 실행하여 테스트 코드를 디버깅 모드로 실행합니다.
- 참고로 변수, 메모리, 스택, 출력 등을 VSCode에서 확인할 수도 있습니다.

---

## 8. 새로운 Git 리포지토리에 Commit & Push 하기

금주 프로젝트를 개인 Git 리포와 같은 다른 리포지토리에 업로드하려면, 기존 Git 연결을 제거하고 새롭게 초기화해야 합니다.

### ✅ 완전히 새로운 Git 리포로 업로드하는 방법

아래 명령어를 순서대로 실행하세요:

```bash
rm -rf .git
git init
git remote add origin https://github.com/myusername/my-new-repo.git
git add .
git commit -m "Clean start"
git push -u origin main
```

### 📌 설명

- `rm -rf .git`: 기존 Git 기록과 연결을 완전히 삭제합니다.
- `git init`: 현재 폴더를 새로운 Git 리포지토리로 초기화합니다.
- `git remote add origin ...`: 새로운 리포지토리 주소를 origin으로 등록합니다.
- `git add .` 및 `git commit`: 모든 파일을 커밋합니다.
- `git push`: 새로운 리포에 최초 업로드(Push)합니다.

이 과정을 거치면 기존 리포와의 연결은 완전히 제거되고, **새로운 독립적인 프로젝트로 관리**할 수 있습니다.

## 🎉 끝

이제 Docker와 DevContainer를 활용한 C 개발 환경이 완성되었습니다.

- (주의) 위 내용은 처음 설치하는 사람을 기준으로 작성된 내용입니다. Data-Structures 폴더에서 있는 프로젝트를 반복적으로 개발할 경우 5에서 7장의 내용만 반복하시면 됩니다.
- 어떤 운영체제에서든 동일한 환경으로 개발 가능  
- VSCode 내에서 코드 작성, 컴파일, 디버깅까지 한 번에 가능

---
# 🚀 실행 방법
## DevContainer에서 실행 후, 아래 명령어로 테스트 실행
```bash
cd rbtree_lab
make test
```

make test는 src 디렉토리의 RBTree 구현 코드를 컴파일하고, test 디렉토리의 테스트 케이스를 실행합니다.

VSCode 내에서 F5를 눌러 디버깅도 가능합니다.
### 🌲 구현 기능 요약 (Red-Black Tree)

| 기능 | 설명 |
| --- | --- |
| 트리 초기화 | `new_rbtree()` |
| 노드 삽입 | `rbtree_insert()` + `insert_fixup()` |
| 노드 삭제 | `rbtree_erase()` + `rb_delete_fixup()` |
| 트리 회전 | `left_rotate()`, `right_rotate()` |
| 삭제 보조 | `rb_transplant()` |
| 색상 관리 | `enum color_t { RBTREE_RED, RBTREE_BLACK }` |
| NIL sentinel | 모든 NULL 포인터 대신 사용되는 고정 BLACK 노드 |

### 🔧 주요 함수 설명
`new_rbtree()`

- RBTree 초기화
- NIL 노드 생성 후 root에 연결

`rbtree_insert()`

- BST처럼 삽입 후 `insert_fixup()`으로 색/회전 조정

`insert_fixup()`

- RED-RED 위반 수정 (Case 1~3)
- 회전과 색상 변경으로 트리 균형 유지

`rbtree_erase()`

- 노드 삭제
- 후계자(successor)를 찾아 `rb_transplant()`로 위치 교체
- 삭제된 노드가 BLACK이면 `rb_delete_fixup()` 호출

`rb_delete_fixup()`

- double black 상태 처리 (Case 1~4)
- 형제의 색상/자식 상태에 따라 회전 및 색상 조정

`rb_transplant()`

- `d` 자리에 `a`를 대체 연결

`left_rotate()`, `right_rotate()`

- 부모-자식 포인터 재연결을 통해 트리 구조 회전
