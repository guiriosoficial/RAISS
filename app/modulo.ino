// Biblioteca para utilização e determinação dos servos motores.
#include <Servo.h> 
#define DEBUG true
#define NO_DEBUG false
#define L_RED 11
#define L_GREEN 12

bool conectado = false;
bool erro = false;
int momento = 0;
Servo base, avanco, mergulho, garra;
// Define as variáveis dos valores das posições de cada Eixo, sendo Delay a velocidade do movimento.
float baseP, avancoP,mergulhoP, garraP, Delay;

void pisca(int led, const int timeout);
String getString(String padrao, String str);
String RespostaServidor(String str);
String sendData(String command, const int timeout, boolean debug);
void conectaRoteador(String ssid, String senha);
boolean iniciaConexaoTCP(String ip, String porta,boolean debug);
boolean checaConexao(String *conn);
String enviaMensagem(String mensagem);
String recebeMensagem(boolean debug);
void Alive();
void Desconecta(String *conn);
void startServos();
void moveServo(Servo *servo, int posicao);
void posiciona(Servo *motor1, Servo *motor2, Servo *motor3, float np1, float np2, float np3); 

// Inicia porta Serial com as mesmas configurações de velocidade que a plataforma no Visual Studio
void setup() { 
  Serial.begin(9600);
  Serial2.begin(115200);
  pinMode(L_GREEN, OUTPUT);
  pinMode(L_RED, OUTPUT);
  sendData("AT+RST\r\n", 2000, DEBUG); // rst
  conectaRoteador("dlink", "12345678");
  conectado = iniciaConexaoTCP("192.168.0.201","2500",DEBUG);
  if( !conectado ){
  erro = true;
  }
  else{
    digitalWrite(L_GREEN, HIGH);
    startServos();
    Delay = 50;
  }
}

void loop() {
  String resp = "";
  if(erro){
  Serial.println("Erro na Conexão com o servidor.");
  digitalWrite(L_GREEN, LOW);
  digitalWrite(L_RED, HIGH);
  while(true);
  }
  if(!conectado){
    Serial.println("Fim da Conexão.");
    digitalWrite(L_GREEN, LOW);
    digitalWrite(L_RED, HIGH);
    while(true);
  }
  // if(conectado && momento > 15) Alive();
  resp = recebeMensagem(NO_DEBUG);
  resp = RespostaServidor(resp);
  Serial.print(resp);
  if(resp == "0" || resp == "0\r") {
    posiciona(&base,&avanco,&mergulho,100,0,0);
    moveServo(&garra,0);
  }
  else if(resp == "G-1" || resp == "G-1\r") {
    moveServo(&garra,0);
  }
  else if(resp == "G-2" || resp == "G-2\r") {
    moveServo(&garra,100); 
  }
  else if(resp == "B-1" || resp == "B-1\r") {
    moveServo(&base,0);  
  }
  else if(resp == "B-2" || resp == "B-2\r") {
    moveServo(&base,100);  
  }
  else if(resp == "B-3" || resp == "B-3\r") {
    moveServo(&base,200);  
  }
  else if(resp == "A-1" || resp == "A-1\r") {
    moveServo(&avanco,0);  
  }
  else if(resp == "A-2" || resp == "A-2\r") {
    moveServo(&avanco,100);  
  }
  else if(resp == "A-3" || resp == "A-3\r") {
    moveServo(&avanco,200);  
  }
  else if(resp == "M-1" || resp == "M-1\r") {
    moveServo(&mergulho,0);  
  }
  else if(resp == "M-2" || resp == "M-2\r") {
    moveServo(&mergulho,100);  
  }
  else if(resp == "M-3" || resp == "M-3\r") {
    moveServo(&mergulho,200);  
  }
  momento++;
} 

    /*----------------------------------------------------------------------*/
   /*----------------------------------------------------------------------*/
  /*--------------------------Funções do programa-------------------------*/
 /*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
  void startServos() {
    base.attach(4);  
    avanco.attach(5);  
    mergulho.attach(6);  
    garra.attach(7);
    garra.write(40);  
  }

  // Definição do void de movimentação dos servos
  void moveServo(Servo *servo, int posicao) {
    int p=servo->read();
    //  Serial.print("Posição: ");
    //  Serial.println(p);
      if(p < posicao) {
      for(int i=p;i<=posicao;i++) {
        servo->write(i);
        delay(Delay);
      }
    }
    else {
      for(int i=p;i>=posicao;i--) {
        servo->write(i);
        delay(Delay);
      }
    }
  }

  // Void para posicionamento sincronizado dos eixos
  void posiciona(Servo *motor1, Servo *motor2, Servo *motor3, float np1, float np2, float np3) {
  float s1,s2,s3;
  float p1=motor1->read();
  float p2=motor2->read();
  float p3=motor3->read();
  // Em seguida, calculamos a distância, em graus, entre as posições atuais e as novas.
  // Variáveis float, para diminuir os erros de arredondamento.
  float d1=np1-p1;
  float d2=np2-p2;
  float d3=np3-p3;
  // pc1 , pc2 e pc3 são as posições correntes, que serão incrementadas durante o movimento.
  float pc1=p1;
  float pc2=p2;
  float pc3=p3;

  if((d1 == 0) && (d2 == 0) && (d3 == 0)) {
    Serial.println("OK");
    return;
  }
  
  if(d1 != 0) {
    s1=d1/abs(d1);
    s2=d2/abs(d1);
    s3=d3/abs(d1);
  }
  else
  if(d2 != 0) {
    s1=d1/abs(d2);
    s2=d2/abs(d2);
    s3=d3/abs(d2);
  }
  else
  if(d3 != 0) {
    s1=d1/abs(d3);
    s2=d2/abs(d3);
    s3=d3/abs(d3);
  }

  // Imprime os valores calculados, para debug, mostrando na tela os valores calculados
  Serial.print(np1);
  Serial.print(' ');
  Serial.print(np2);
  Serial.print(' ');
  Serial.print(np3);
  Serial.print(' ');
  Serial.print(p1);
  Serial.print(' ');
  Serial.print(p2);
  Serial.print(' ');
  Serial.print(p3);
  Serial.print(' ');
  Serial.print(d1);
  Serial.print(' ');
  Serial.print(d2);
  Serial.print(' ');
  Serial.print(d3);
  Serial.print(' ');
  Serial.print(pc1);
  Serial.print(' ');
  Serial.print(pc2);
  Serial.print(' ');
  Serial.print(pc3);
  Serial.print(' ');
  Serial.print(s1);
  Serial.print(' ');
  Serial.print(s2);
  Serial.print(' ');
  Serial.print(s3);
  Serial.println();

  while((abs(pc1-np1) > 1) || (abs(pc2-np2) > 1) || (abs(pc3-np3) > 1)) {
    // Somo o incremento à posição corrente de cada motor
    pc1=pc1+s1;
    pc2=pc2+s2;
    pc3=pc3+s3;
    // Mostro os valores na tela
    Serial.print(pc1);
    Serial.print(' ');
    Serial.print(pc2);
    Serial.print(' ');
    Serial.println(pc3);
    // Giro os motores para suas novas posições
    motor1->write(pc1);
    motor2->write(pc2);
    motor3->write(pc3);

    delay(Delay);
  }
  Serial.println("OK");
}

//-------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------//

void pisca(int led,const int timeout) {
  long int tempo = millis();
  while ( (tempo + timeout) > millis()) {
    digitalWrite(led, HIGH);
    delay(400);
    digitalWrite(led, LOW);
    delay(400);
  }
}

String getString(String padrao, String str) {
  int tam = padrao.length();
  int index = str.indexOf(padrao);
  if( index == -1)return "";
  str.remove(index+tam);
  str.remove(0,index);
  return str;
}

String RespostaServidor(String str) {
  String padrao = "+IPD,"; 
  int tam = padrao.length();
  int index = str.indexOf(padrao);
  if( index == -1)return "";
  str.remove(0,index);
  index = str.indexOf(":");
  str.remove(0,index+1);
  index = str.indexOf('\n');
  if(index == -1)return str;
  str.remove(index);
  return str;
}

String sendData(String command, const int timeout, boolean debug) {
  // Envio dos comandos AT para o modulo
  String response = "";
  Serial2.print(command);
  long int time = millis();
  while ( (time + timeout) > millis()) {
    while (Serial2.available()){
      // O esp possui dados para exibir sua saída na janela serial
      char c = Serial2.read(); // Le o proximo carácter.
      response += c;
    }
  }
  if (debug) {
    Serial.print(response);
  }
  return response;
}

void conectaRoteador(String ssid, String senha) {
  String connAP = "AT+CWJAP=";
  connAP += "\""+ssid+"\",\""+senha+"\"\r\n";
  sendData(connAP, 3000, DEBUG); // Conecta Roteador
  delay(5000);
  sendData("AT+CWMODE=1\r\n", 1000, DEBUG); // Modo WiFi
  sendData("AT+CIFSR\r\n", 1000, DEBUG); // Mostra IP do modulo
  sendData("AT+CIPMUX=0\r\n", 1000, DEBUG); // Configura para somente uma conexão
  sendData("AT+CIPMODE=0\r\n", 1000, DEBUG); // Configura para transmissão para o modo normal
}

boolean iniciaConexaoTCP(String ip, String porta,boolean debug) {
  bool con = false;
  String servidor = "\"TCP\",\""+ip+"\","+porta;
  String Resposta = sendData("AT+CIPSTART="+servidor+"\r\n", 1000, debug);
  String OK = getString("OK", Resposta);
  Resposta = RespostaServidor(Resposta);
  String UM = getString("1", Resposta);
  String ZERO = getString("0", Resposta);
  if(OK == "OK") {
    Serial.println("Conexao feita com sucesso.");
    Serial.println(Resposta);
    if(UM == "1") return true;
  }
  if(ZERO == "0") {
    pisca(L_RED, 3500);
    sendData("AT+CIPSEND=10\r\n", 500, NO_DEBUG);
    sendData("!!Alive!!\n", 500, NO_DEBUG);
    con = iniciaConexaoTCP("192.168.0.201","2500",DEBUG);
  }
  return con;
}

void checaConexao(boolean *conn) {
  String estado = getString("STATUS:3",sendData("AT+CIPSTATUS\r\n", 1000, NO_DEBUG));
  if(estado == "STATUS:3") {
    *conn = true;
  }
  else *conn = false;
}

String recebeMensagem(boolean debug) {
  String response = "";
  char c;
  long int tempo = millis();
  while(tempo + 1000 > millis()) { 
    while (Serial2.available()) {
      c = Serial2.read();
      response += c;
      if(c == '\n')break;
    }
    if( c == '\n' ) break;
  }
  if(debug) {
    Serial.print(response);
  }
  return response;
}

String enviaMensagem(String mensagem) {
  Serial.print(mensagem);
  String cipSend = "AT+CIPSEND=";
  cipSend += mensagem.length();
  cipSend += "\r\n";
  sendData(cipSend, 1000, NO_DEBUG);
  String resposta = RespostaServidor(sendData(mensagem, 1000, NO_DEBUG));
  Serial.print(resposta);
  resposta = recebeMensagem(NO_DEBUG);
  Serial.print(resposta);
  return resposta;
}

void Alive() {
  checaConexao(&conectado);
  if(conectado) {
    sendData("AT+CIPSEND=10\r\n", 1000, NO_DEBUG);
    sendData("!!Alive!!\n", 1000, NO_DEBUG);
  }
  momento = 0;
}

void Desconecta(boolean *conn) {
  if(*conn) {
    //Serial.println("Desconectando...");
    sendData("AT+CIPSEND=6\r\n", 500, NO_DEBUG);
    RespostaServidor(sendData("quit\r\n", 500, NO_DEBUG));
    *conn = false;
  }
}
    /*----------------------------------------------------------------------*/
   /*----------------------------------------------------------------------*/
  /*----------------------------------FIM---------------------------------*/
 /*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/
