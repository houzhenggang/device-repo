#define C_LOGGER_ADDR  (0x400E1000)
#define PY_LOGGER_ADDR (0x400E1200)
#define RS_LOGGER_ADDR (0x400E1400)

void setup() 
{
  Serial.begin(9600);
  Serial.println("start");
}

void say_hello_logger(int addr, const char * msg)
{
    int cnt = 0;
    while (cnt < strlen(msg))
    {
        *(int*)addr = msg[cnt++];
    }
    *(int*)addr = '\n';
}

void loop() 
{
  while (1)
  {
    Serial.println("-------------------LOOP START-------------------");
    
    say_hello_logger(C_LOGGER_ADDR, "Hello C logger!");
    say_hello_logger(PY_LOGGER_ADDR, "Hello PY logger!");
    say_hello_logger(RS_LOGGER_ADDR, "Hello RUST logger!");
    
    Serial.println("===================loop end===================");
  }
}
