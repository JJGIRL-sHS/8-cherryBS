// 스마트 신호등 — 4상태 비차단 상태 머신
// 차량 신호등(적·황·녹) + 보행자 신호등(적·녹) + 보행자 호출 버튼

// ===== 핀 할당 =====
const int CAR_R = 2;   // 빨강
const int CAR_Y = 3;   // 황색
const int CAR_G = 4;   // 초록

const int PED_R = 13;  // 빨강
const int PED_Y = 12;  // 황색 (미사용)
const int PED_G = 11;  // 초록

const int BUTTON = 9;

// ===== 타이밍 (ms) =====
const unsigned long VEHICLE_PASS_MIN_MS    = 10000;
const unsigned long VEHICLE_WARNING_MS     = 3000;
const unsigned long PEDESTRIAN_PASS_MS     = 7000;
const unsigned long PEDESTRIAN_WARNING_MS  = 3000;
const unsigned long BLINK_INTERVAL_MS      = 500;

// ===== 상태 =====
enum State {
  VEHICLE_PASS,
  VEHICLE_WARNING,
  PEDESTRIAN_PASS,
  PEDESTRIAN_WARNING
};

State currentState;
unsigned long stateEnteredAt;
bool pedestrianRequest = false;   // 보행자 호출 래치 (VEHICLE_PASS 중 버튼 눌림을 기억)

// ===== LED 출력 =====
void setCarLed(bool r, bool y, bool g) {
  digitalWrite(CAR_R, r ? HIGH : LOW);
  digitalWrite(CAR_Y, y ? HIGH : LOW);
  digitalWrite(CAR_G, g ? HIGH : LOW);
}

void setPedLed(bool r, bool g) {
  digitalWrite(PED_R, r ? HIGH : LOW);
  digitalWrite(PED_G, g ? HIGH : LOW);
  digitalWrite(PED_Y, LOW);
}

void applyLeds(State s) {
  switch (s) {
    case VEHICLE_PASS:        setCarLed(false, false, true);  setPedLed(true, false); break;
    case VEHICLE_WARNING:     setCarLed(false, true,  false); setPedLed(true, false); break;
    case PEDESTRIAN_PASS:     setCarLed(true,  false, false); setPedLed(false, true); break;
    case PEDESTRIAN_WARNING:  setCarLed(true,  false, false); setPedLed(false, true); /* 점멸 첫 프레임; 이후 loop에서 깜빡임 */ break;
    default:                  setCarLed(true,  false, false); setPedLed(true,  false); break;  // 안전: 전면 정지
  }
}

void enterState(State s) {
  currentState = s;
  stateEnteredAt = millis();
  applyLeds(s);

  Serial.print("-> ");
  switch (s) {
    case VEHICLE_PASS:       Serial.println("VEHICLE_PASS"); break;
    case VEHICLE_WARNING:    Serial.println("VEHICLE_WARNING"); break;
    case PEDESTRIAN_PASS:    Serial.println("PEDESTRIAN_PASS"); break;
    case PEDESTRIAN_WARNING: Serial.println("PEDESTRIAN_WARNING"); break;
    default:                 Serial.println("UNKNOWN"); break;
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(CAR_R, OUTPUT);
  pinMode(CAR_Y, OUTPUT);
  pinMode(CAR_G, OUTPUT);
  pinMode(PED_R, OUTPUT);
  pinMode(PED_Y, OUTPUT);
  pinMode(PED_G, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);

  Serial.println("스마트 신호등 시작");
  enterState(VEHICLE_PASS);
}

void loop() {
  unsigned long elapsed = millis() - stateEnteredAt;
  bool buttonPressed = (digitalRead(BUTTON) == LOW);

  switch (currentState) {
    case VEHICLE_PASS:
      // 버튼이 한 번이라도 눌리면 요청을 래치(짧게 눌렀다 떼도 기억)
      if (buttonPressed && !pedestrianRequest) {
        pedestrianRequest = true;
        Serial.println("보행자 요청 접수");
      }
      // 최소 통행 시간이 지나고 요청이 있으면 전환하며 래치 소비
      if (elapsed >= VEHICLE_PASS_MIN_MS && pedestrianRequest) {
        pedestrianRequest = false;
        enterState(VEHICLE_WARNING);
      }
      break;

    case VEHICLE_WARNING:
      if (elapsed >= VEHICLE_WARNING_MS) {
        enterState(PEDESTRIAN_PASS);
      }
      break;

    case PEDESTRIAN_PASS:
      if (elapsed >= PEDESTRIAN_PASS_MS) {
        enterState(PEDESTRIAN_WARNING);
      }
      break;

    case PEDESTRIAN_WARNING: {
      bool blinkOn = ((elapsed / BLINK_INTERVAL_MS) % 2) == 0;
      setPedLed(false, blinkOn);
      if (elapsed >= PEDESTRIAN_WARNING_MS) {
        enterState(VEHICLE_PASS);
      }
      break;
    }

    default:
      enterState(VEHICLE_PASS);  // 안전: 알 수 없는 상태면 차량 통행으로 복구
      break;
  }
}
