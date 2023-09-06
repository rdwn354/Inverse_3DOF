#define DXL_BUS_SERIAL1 1  //Dynamixel on Serial1(USART1)  <-OpenCM9.04
#define DXL_BUS_SERIAL2 2  //Dynamixel on Serial2(USART2)  <-LN101,BT210
#define DXL_BUS_SERIAL3 3  //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#define SpeedDxl 300   //400

#define ID_NUM1 4      //coxa
#define ID_NUM2 10      //femur
#define ID_NUM3 16     //tibia

#define ID_NUM4 3      //coxa
#define ID_NUM5 9      //femur
#define ID_NUM6 15     //tibia

const float cx=3.1;     //coxa length
const float fm=6.2;     //femur length
const float tb=5.2;     //tibia length

float x0,coxa,coxaNormal_1,coxaNormal_2;
float femur1,femur2,femur,femurNormal_1,femurNormal_2,x0c,a;
float tibia,convertTibia_1,convertTibia_2,tibiaNormal_1,tibiaNormal_2;
int convertCoxa_1,convertCoxa_2,convertFemur_1,convertFemur_2;

Dynamixel Dxl(DXL_BUS_SERIAL3);

void setup() {
  SerialUSB.begin();
  Dxl.begin(3);
  Dxl.jointMode(ID_NUM1); //jointMode() is to use position mode
  Dxl.jointMode(ID_NUM2);
  Dxl.jointMode(ID_NUM3);
  Dxl.jointMode(ID_NUM4);
  Dxl.jointMode(ID_NUM5);
  Dxl.jointMode(ID_NUM6);
}

void loop() {
  inverse3D(10,0,-5);

}

void inverse3D(float x, float y, float z){
  //coxa
  x0 = sqrt(sq(x)+sq(y));//Panjang kaki coxa
  coxa = atan(y/x)/(PI/180);//convert rad to deg
  coxaNormal_1 = 270-coxa;
  coxaNormal_2 = 90-coxa;
  convertCoxa_1 = map(coxaNormal_1,180,360,0,1024);
  convertCoxa_2 = map(coxaNormal_2 ,0,180,0,1024);

  Dxl.setPosition(ID_NUM4,convertCoxa_1,SpeedDxl);
  Dxl.setPosition(ID_NUM1,convertCoxa_2,SpeedDxl);

  
  //femur
  x0c = x0-cx;
  femur1 = atan(z/x0c)/(PI/180);
  a = sqrt((sq(z)+sq(x0c))); 
  femur2 = acos( (sq(fm)+sq(a)-sq(tb))/(2*a*fm) )/(PI/180);  
  femur = femur1+femur2;
  femurNormal_1 = 90+femur;
  femurNormal_2 = 90-femur;
  convertFemur_1 = abs(map(femurNormal_1,180,360,0,1024));
  convertFemur_2 = map(femurNormal_2,0,180,0,1024);

  Dxl.setPosition(ID_NUM5,convertFemur_1,SpeedDxl);
  Dxl.setPosition(ID_NUM2,convertFemur_2,SpeedDxl);

  
  //tibia
  tibia = (acos( (sq(fm)+sq(tb)-sq(a))/(2*fm*tb) )-1.5708)/(PI/180);
  tibiaNormal_1 = 90-tibia;
  tibiaNormal_2 = 90+tibia;
  convertTibia_1 = abs(map(tibiaNormal_1,180,360,0,1024));
  convertTibia_2 = map(tibiaNormal_2,0,180,0,1024);

  Dxl.setPosition(ID_NUM6,convertTibia_1,SpeedDxl);
  Dxl.setPosition(ID_NUM3,convertTibia_2,SpeedDxl);
  
  SerialUSB.print("coxa : ");
  SerialUSB.print(coxaNormal_1);
  SerialUSB.print(", convertCoxa : ");
  SerialUSB.print(convertCoxa_1);
  
  SerialUSB.print(", femur : ");
  SerialUSB.print(femurNormal_1);
  SerialUSB.print(", convertFemur : ");
  SerialUSB.print(convertFemur_1);
  
  SerialUSB.print(", tibia : ");
  SerialUSB.print(tibiaNormal_1);
  SerialUSB.print(", convertTibia : ");
  SerialUSB.print(convertTibia_1);
  SerialUSB.println();
  delay(500);

}
