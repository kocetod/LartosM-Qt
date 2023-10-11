# include "Uart.h"



static void Error(const char *Msg)
{
    fprintf (stderr, "%s\n", Msg);
    fprintf (stderr, "strerror() is %s\n", strerror(errno));
    exit(1);
}
static void Warning(const char *Msg)
{
     fprintf (stderr, "Warning: %s\n", Msg);
}


static int SerialSpeed(int argInSpeed /*const char *SpeedString*/)
{
    //int SpeedNumber = atoi(SpeedString);
#   define TestSpeed(Speed) if (argInSpeed == Speed) return B##Speed
    TestSpeed(1200);
    TestSpeed(2400);
    TestSpeed(4800);
    TestSpeed(9600);
    TestSpeed(19200);
    TestSpeed(38400);
    TestSpeed(57600);
    TestSpeed(115200);
    TestSpeed(230400);
    Error("Bad speed");
    return -1;
}

static void PrintUsage(void)
{

   fprintf(stderr, "comtest - interactive program of comm port\n");
   fprintf(stderr, "press [ESC] 3 times to quit\n\n");

   fprintf(stderr, "Usage: comtest [-d device] [-t tty] [-s speed] [-7] [-c] [-x] [-o] [-h]\n");
   fprintf(stderr, "         -7 7 bit\n");
   fprintf(stderr, "         -x hex mode\n");
   fprintf(stderr, "         -o output to stdout too\n");
   fprintf(stderr, "         -c stdout output use color\n");
   fprintf(stderr, "         -h print this help\n");
   exit(-1);
}

static inline void WaitFdWriteable(int Fd)
{
    fd_set WriteSetFD;
    FD_ZERO(&WriteSetFD);
    FD_SET(Fd, &WriteSetFD);
    if (select(Fd + 1, NULL, &WriteSetFD, NULL, NULL) < 0) {
      Error(strerror(errno));
    }

}

bool isInititalised = false;
int CommFd/*, TtyFd*/;

struct termios TtyAttr;
struct termios BackupTtyAttr;

int DeviceSpeed = B115200;
int TtySpeed = B115200;
int ByteBits = CS8;
const char *DeviceName = "/dev/ttyS4";
const char *TtyName = "/dev/tty";
int OutputHex = 0;
int OutputToStdout = 0;
int UseColor = 0;

void ComInit(int argInSpeed)
{
    opterr = 0;

    if(isInititalised==false)
    {
        DeviceSpeed = SerialSpeed(argInSpeed);
        CommFd = open(DeviceName, O_RDWR, 0);
        if (CommFd < 0)
        {
            Error("Unable to open device");
        }
        if (fcntl(CommFd, F_SETFL, O_NONBLOCK) < 0)
        {
            Error("Unable set to NONBLOCK mode");
        }

        memset(&TtyAttr, 0, sizeof(struct termios));

        TtyAttr.c_iflag = IGNPAR;
        TtyAttr.c_cflag = DeviceSpeed | HUPCL | ByteBits | CREAD | CLOCAL;
        TtyAttr.c_cc[VMIN] = 1;

        if (tcsetattr(CommFd, TCSANOW, &TtyAttr) < 0)
        {
            Warning("Unable to set comm port");
        }

        /*TtyFd = open(TtyName, O_RDWR | O_NDELAY, 0);
        if (TtyFd < 0)
        {
            Error("Unable to open tty");
        }*/
        /*
        TtyAttr.c_cflag = TtySpeed | HUPCL | ByteBits | CREAD | CLOCAL;
        if (tcgetattr(TtyFd, &BackupTtyAttr) < 0)
        {
            Error("Unable to get tty");
        }*/
        /*
        if (tcsetattr(TtyFd, TCSANOW, &TtyAttr) < 0)
        {
            Error("Unable to set tty");
        }*/
        isInititalised = true;
    }
    else
    {
        Error("Already Initialised");
    }
}

void ComSetSpeed(int argInSpeed)
{
    if(isInititalised==true)
    {
        opterr = 0;

        if(argInSpeed==9600)
        {
            //digitalWrite(3,0);
        }
        else
        {
            //digitalWrite(3,1);
        }

        DeviceSpeed = SerialSpeed(argInSpeed);
        if (CommFd < 0)
        {
            Error("Device Not Oppened");
        }
        if (fcntl(CommFd, F_SETFL, O_NONBLOCK) < 0)
        {
            Error("Unable set to NONBLOCK mode");
        }

        memset(&TtyAttr, 0, sizeof(struct termios));

        TtyAttr.c_iflag = IGNPAR;
        TtyAttr.c_cflag = DeviceSpeed | HUPCL | ByteBits | CREAD | CLOCAL;
        TtyAttr.c_cc[VMIN] = 1;

        if (tcsetattr(CommFd, TCSANOW, &TtyAttr) < 0)
        {
            Warning("Unable to set comm port Speed");
        }

        /*if (TtyFd < 0)
        {
            Error("Tty not oppened");
        }

        TtyAttr.c_cflag = TtySpeed | HUPCL | ByteBits | CREAD | CLOCAL;
        if (tcgetattr(TtyFd, &BackupTtyAttr) < 0)
        {
            Error("Unable to get tty");
        }

        if (tcsetattr(TtyFd, TCSANOW, &TtyAttr) < 0)
        {
            Error("Unable to set tty");
        }*/
    }
    else
    {
        Error("Not Inititalised");
    }
}

void OutputStdChar(FILE *File, unsigned char argInChar)
{
    char Buffer[10];
    int Len = sprintf(Buffer, OutputHex ? "%.2X  " : "%c", argInChar);
    fwrite(Buffer, 1, Len, File);
}

int Max(int argInX, int argInY)
{
    if(argInX>=argInY)
    {
        return argInX;
    }
    else
    {
        return argInY;
    }
}



/*void Receive()
{
    unsigned char Char = 0;
    while (read(CommFd, &Char, 1) == 1)
    {
        ProcessChar(Char);
    }
}*/

void ComSend(void* argInData, int argInSize)
{
    //if(sendFrameout==0)
    //{
        WaitFdWriteable(CommFd);
        if (write(CommFd, argInData, argInSize) < 0)
        {
            Error(strerror(errno));
        }
    //    sendFrameout = 50;
    //}
    //else
    //{
    //    sendFrameout--;
    //}
}

void (*OnReceive)(char);

void ComAddOnReceive(void* argInOnReceive)
{
    OnReceive = argInOnReceive;
}

int cur = 0;
char Recevied[10000];

int ComRoutine()
{
    fd_set ReadSetFD;
    FD_ZERO(&ReadSetFD);
    FD_SET(CommFd, &ReadSetFD);

    unsigned char Char = 0;
    while (read(CommFd, &Char, 1) == 1)
    {
        if(cur<10000)
        {
          Recevied[cur] = Char;
          cur++;
        }
        if(OnReceive!=NULL)
        {
            (*OnReceive)(Char);
        }
    }
    //Receive();
    //Send();

    return 1;
}

void ComExit()
{
    /*if (tcsetattr(TtyFd, TCSANOW, &BackupTtyAttr) < 0)
    Error("Unable to set tty");*/
}
