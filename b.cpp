// print
extern "C" int write(int fd, const void *buf, unsigned int count);
void print(const char* str){
  while(*str){
    write(1, str, 1);
    str++;
  }
}

// scan
extern "C" int read(int fd, void *buf, unsigned int count);
void scan(char* buffer){
  int bytesRead = read(0, buffer, sizeof(buffer));
  if(bytesRead) buffer[bytesRead] = '\0';
}

// time
extern "C" long int time(long int *loc);

// random number
unsigned int seed = 64;
unsigned int random(){
  seed = seed * 110315245 + 12345;
  return (seed / 65536) % 32768;
}

// cast int -> const char[]
void intToChar(int num, char* buffer){
  int i = 0;
  bool isNegative = false;
  if(num < 0){
    isNegative = true;
    num = -num;
  }
  do{
    buffer[i++] = (num%10) + '0';
    num /= 10;
  } while(num > 0);
  if(isNegative) buffer[i++] = '-';
  buffer[i] = '\0';
  for(int j = 0; j < i/2; j++){
    char tmp = buffer[j];
    buffer[j] = buffer[i-j-1];
    buffer[i-j-1] = tmp;
  }
}

// cast char[] -> int
int charToInt(char* str){
  int result = 0;
  bool isNegative = false;
  if(*str == '-'){
    isNegative = true;
    str++;
  }
  int cnt = 0;
  while(*str){
    if(*str < '0' || *str > '9') break;
    result = result*10 + int(*str-'0');
    str++;
  }
  return isNegative ? -result : result;
}


int main(){
  long int currentTime;
  time(&currentTime);
  seed = (unsigned int)currentTime;
  char buffer[10];
  // 0: draw  1: win  2: lose
  // player is x. cpu is y
  int resultTable[3][3] = {
    {0, 2, 1},
    {1, 0, 2},
    {2, 1, 0}
  };
  print("Choose your hand. (0:g, 1:c, 2:p): ");
  scan(buffer);
  int hand = charToInt(buffer);
  print("CPU hands is ");
  int cpuHand = random()%3;
  char cpuHandBuffer[10];
  intToChar(cpuHand, cpuHandBuffer);
  print(cpuHandBuffer);
  print("\nresult: ");
  int result = resultTable[cpuHand][hand%3];
  if(result == 0) print("Draw\n");
  else if(result == 1) print("You win\n");
  else print("You lose\n");
}
