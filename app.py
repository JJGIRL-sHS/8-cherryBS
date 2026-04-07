import streamlit as st
import serial

from google import genai
from google.genai import types

from datetime import datetime
import time
import json

import os
from dotenv import load_dotenv


# =========================================================
# [구역 1] 환경 설정
# =========================================================

load_dotenv()
GEMINI_API_KEY = os.getenv("GEMINI_API_KEY")
MODEL_NAME = "gemini-2.5-flash"

st.set_page_config(page_title="8일간의 아두이노", layout="wide")


# =========================================================
# [구역 2] 리소스 및 외부 연결 관리
# =========================================================

@st.cache_resource
def get_client():
    load_dotenv()
    api_key = os.getenv("GEMINI_API_KEY")

    if not api_key:
        st.error("🔑API 키가 설정되지 않았습니다.")
        st.stop()

    return genai.Client(api_key=api_key)

client = get_client()

@st.cache_resource
def get_ser(port):
    try:
        return serial.Serial(port, 115200, timeout=1)
    except:
        return None

port = st.sidebar.text_input("시리얼 포트", value="COM3")

st.session_state.ser = get_ser(port)

if st.session_state.ser is not None:
    st.sidebar.success(f"{port} 연결 성공!")
else:
    st.sidebar.error(f"{port}를 찾을 수 없습니다.")

# =========================================================
# [구역 2] 리소스 및 외부 연결 관리
# =========================================================


# =========================================================
# [구역 3] 상태 초기화
# =========================================================


# =========================================================
# [구역 4] AI 에이전트 및 도구(Tools) 정의
# =========================================================

def load_system_prompt(file_name):
    file_dir = os.path.dirname(os.path.abspath(__file__))
    file_path = os.path.join(file_dir, file_name)
    try:
        with open(file_path, "r", encoding="utf-8") as f:
            return f.read()
    except FileNotFoundError:
        st.error(f"{file_path}를 찾을 수 없습니다.")
        st.stop()

if "chat_session" not in st.session_state:
    system_prompt = load_system_prompt("system_prompt.md")
    tool_list = []
    st.session_state.chat_session = client.chats.create(
        model=MODEL_NAME,
        config= types.GenerateContentConfig(
            system_instruction=system_prompt,
            tools= tool_list,
            automatic_function_calling=types.AutomaticFunctionCallingConfig(
                disable=False,
                maximum_remote_calls=7,
            )
        ),
    )

# =========================================================
# [구역 5] 데이터 수집
# =========================================================


# =========================================================
# [구역 6] 페이지 내비게이션 및 앱 실행
# =========================================================

pages = [
    st.Page("dashboard.py", title="대시보드", icon=":material/dashboard:", default=True),
    st.Page("chatbot.py", title="챗봇", icon=":material/smart_toy:"),
    st.Page("control.py", title="수동 제어", icon=":material/adjust:"),
]

page = st.navigation(pages=pages)

st.title(f"{page.icon} {page.title}")

page.run()

