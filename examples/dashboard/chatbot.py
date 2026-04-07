import streamlit as st


def render_part(part):
    if part.text:
        st.markdown(part.text)
    
    if part.function_call:
        with st.status(f"{part.function_call.name} 함수 호출 요청"):
            st.json(part.function_call.args)

    if part.function_response:
        with st.status(f"{part.function_response.name} 함수 호출 응답"):
            st.json(part.function_response.response)


for content in st.session_state.chat_session.get_history():
    with st.chat_message("ai" if content.role == "model" else "user"):
        for part in content.parts:
            render_part(part)

            
if prompt := st.chat_input("챗봇에게 물어보기"):
    with st.chat_message("user"):
        st.markdown(prompt)
    
    with st.chat_message("ai"):
        response = st.session_state.chat_session.send_message(prompt)
        st.rerun()
