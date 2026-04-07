# 🚀 8일간의 아두이노

![Python](https://img.shields.io/badge/Python-3776AB?style=flat-square&logo=python&logoColor=white)
![Arduino](https://img.shields.io/badge/Arduino-00979D?style=flat-square&logo=arduino&logoColor=white)
![Streamlit](https://img.shields.io/badge/Streamlit-FF4B4B?style=flat-square&logo=streamlit&logoColor=white)
![Gemini API](https://img.shields.io/badge/Gemini_API-8E75B2?style=flat-square&logo=google&logoColor=white)

> *"데이터에 마음을 담다: AI와 대화하는 스마트 홈 시스템"*

**파이썬(Python)과 아두이노(Arduino), 그리고 Gemini AI를 융합한 나만의 스마트 IoT 서비스 개발 프로젝트입니다.**

이 레포지토리는 8일간 진행되는 **[스마트 IoT 서비스]** 실습을 위한 기본 템플릿입니다. 
학생들은 이곳에 준비된 뼈대 코드를 바탕으로 단순한 하드웨어 제어를 넘어, 웹(Web) 화면에서 센서 데이터를 실시간으로 시각화하고 인공지능 챗봇과 대화하며 하드웨어를 제어하는 **풀스택 양방향 IoT 시스템**을 직접 완성하게 됩니다.


## 🛠️ 환경 설정 및 프로그램 설치 (Setup)
본 프로젝트는 하드웨어(Arduino)와 소프트웨어(Python, AI)가 만나는 과정입니다. 원활한 실습을 위해 아래 순서대로 설정을 완료해 주세요.

### 1. 필수 소프트웨어 설치 (Standard Tools)
가장 먼저 코딩을 위한 기본적인 도구들을 설치해야 합니다. 각 링크를 클릭하여 본인의 운영체제(Windows/macOS)에 맞는 버전을 설치하세요.

1. [Arduino IDE](https://www.arduino.cc/en/software/): 아두이노 보드에 회로 제어 코드를 작성하고 업로드하는 도구입니다.

2. [아두이노 드라이버 설치 (USB Driver)](https://www.wch-ic.com/downloads/CH341SER_EXE.html) : 컴퓨터가 아두이노 보드를 올바르게 인식하고 서로 통신할 수 있도록 도와주는 필수 도구입니다.
    
    💡 팁: 보드를 연결했는데 포트(Port)가 뜨지 않는다면 이 드라이버를 반드시 설치해야 합니다.

3. [Python (3.12 이상)](https://www.python.org/downloads/): 데이터 처리와 AI 통신을 담당합니다.

    ⚠️ 주의: 설치 시 [Add Python to PATH] 체크박스를 반드시 선택하세요! (선택 안 하면 터미널에서 실행이 안 됩니다.)

4. [VS Code (Visual Studio Code)](https://code.visualstudio.com/): 우리가 코드를 작성하고 실행할 메인 에디터입니다.

### 3. 파이썬 라이브러리 설치 (Libraries)
VS Code의 터미널(Terminal)창을 열고 아래 명령어를 복사해서 붙여넣으세요. 이 과정에서 필요한 모든 라이브러리가 자동으로 설치됩니다.

```Bash
pip install -r requirements.txt
```
💡 팁: 명령어를 입력한 뒤 **엔터(Enter)**를 누르고, 설치가 완료될 때까지 잠시 기다려 주세요.

⚠️ 주의: 반드시 VS Code에서 프로젝트 폴더가 열려 있는 상태여야 합니다. (왼쪽 파일 목록에 requirements.txt가 보여야 해요!)

📦 포함된 라이브러리 목록
requirements.txt 파일에는 우리가 사용할 아래의 도구들이 들어있습니다.

```
streamlit==1.55.0
pyserial==3.5
google-genai==1.68.0
pandas==2.3.3
python-dotenv==1.2.2
watchdog==6.0.0
```
- `streamlit`: 복잡한 웹 기술 없이도 파이썬만으로 실시간 데이터 대시보드를 만듭니다.

- `pandas`: 아두이노에서 들어온 수많은 데이터를 표(Table) 형식으로 일목요연하게 정리합니다.

- `pyserial`: 아두이노와 파이썬 사이의 대화 통로를 엽니다.

- `google-genai`: 최신 Gemini AI와 연결하여 챗봇 기능을 구현하고 하드웨어를 지능적으로 제어합니다.

- `python-dotenv`: API 키와 같은 민감한 비밀 정보를 코드와 분리하여 안전하게 관리합니다.

- `watchdog`: 코드나 파일의 변화를 감시하여 대시보드에 즉각 반영되도록 돕습니다.

### 4. Gemini API 키 발급 (AI Access)
인공지능과 대화하기 위해 나만의 '열쇠'를 준비해야 합니다.

1. Google AI Studio에 접속합니다.
2. 'Create API key' 버튼을 눌러 본인만의 키를 발급받습니다.
3. 발급받은 키는 메모장에 따로 복사해 두세요. (절대 타인에게 공유하지 마세요!)

⚠️ 주의: 이 키는 여러분의 소중한 개인 정보와 같습니다. 수업 시간에 선생님과 함께 안전하게 등록할 예정이니, 그전까지는 외부(GitHub 등)에 절대 노출되지 않도록 주의하세요!

## ⚡ 프로젝트 실행 방법 (How to Run)

### 🔌 1. 아두이노 연결 및 업로드

- 아두이노 보드를 컴퓨터 USB 포트에 연결하세요.

- 아두이노 IDE에서 작성한 .ino 파일을 보드에 업로드(Upload) 합니다.

### 🖥️ 2. VS Code 터미널 열기

- 단축키 Ctrl + `를 누르거나, 상단 메뉴에서 [터미널] -> [새 터미널]을 클릭하세요.

- 터미널 창에 아래 명령어를 복사해서 붙여넣고 엔터를 누르세요.

```Bash
streamlit run app.py
```

### 3. 🔑 API 키

1. `.env` 파일을 새로 만듭니다.
2. `.env.example` 파일 안의 내용을 `.env` 파일에 붙여 넣습니다.
3. API키를 입력합니다.

## 아두이노

### 사용 라이브러리

- [ArduinoJson 7](https://arduinojson.org/)

### 사용 부품

- 조도 센서: A0
- 서보모터: D9

