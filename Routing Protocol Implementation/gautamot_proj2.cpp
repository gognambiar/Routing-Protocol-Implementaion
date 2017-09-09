#include <fstream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <netdb.h> 
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <stdio.h> 
#include <iostream>
#include <time.h>

using namespace std;

#define STDIN 1
#define TRUE 1


char clipad[50],tpl[40],ctrr[20];
int interval,lofn[30],ctr = 0,connectfs[10],max_sd,numserv,numedge,i,j,count = 1,newc = 1,newc1 = 1,packets = 0;

struct timeval tv; //Data structure to store time interval
time_t st[10]; 

void storeip()
{

struct ifaddrs *ifap, *ifa;
struct sockaddr_in *sa;
char *addr;

getifaddrs (&ifap);
for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
if (ifa->ifa_addr->sa_family==AF_INET) {
sa = (struct sockaddr_in *) ifa->ifa_addr;
addr = inet_ntoa(sa->sin_addr);
if(strcmp(ifa->ifa_name,"eth0") == 0 || strcmp(ifa->ifa_name,"em2") == 0) 
{
strcpy(clipad,addr);
}
}
}

freeifaddrs(ifap);
}

class topology//Class Object to store IPs and Port numbers of various servers ids
{
public :
uint16_t serverid,port,isneigh;
char htnm[40],ipad[32];
topology()
{
isneigh = 0;
if(strcmp(ipad,"128.205.36.8") == 0)
strcpy(htnm,"timberlake.cse.buffalo.edu");
else if(strcmp(ipad,"128.205.36.33") == 0)
strcpy(htnm,"highgate.cse.buffalo.edu");
else if(strcmp(ipad,"128.205.36.34"))
strcpy(htnm,"euston.cse.buffalo.edu");
else if(strcmp(ipad,"128.205.36.35"))
strcpy(htnm,"embankment.cse.buffalo.edu");
else if(strcmp(ipad,"128.205.36.36"))
strcpy(htnm,"underground.cse.buffalo.edu");
else
strcpy(htnm,"sample");
}
}tpf[30],crs;//tpf stores details pertaining to all servers. crs stores details pertaining to the server running the program.

class retdet//functions like a dictionary when a server id is passed as index of rtdd (rtdd[serverid]) it gives the corresponding serverid and port.
{
public :
char ipd[32];
uint16_t port;
}rtdd[15];

class costnd
{
public : 
uint16_t servid, neighid,costb,port;
char ipts[32];
}cost[30];

class costs//functions like a dictionary when a server id is passed as index of ct (ct[serverid]) it gives the cost between serverid and the server running the program.
{
public :
uint16_t cta,nhn;
}ct[30];


void StartupServer()
{
char buf[100],line[500];
char buf1[40],buf2[40],buf3[40];
fd_set readfds;
int up1,up2,up3;


FILE *in_file = fopen(tpl, "r");
//reading topology file starts
for (count = 1; fgets(line, 500, in_file) != NULL; count++)
{

if(count == 1)
{
numserv = strtol(line, NULL, 10);
for(int jk = 1;jk<=numserv;jk++)
{
ct[jk].cta = 10000;
ct[jk].nhn = jk;
}
}

else if(count == 2)
{
numedge = strtol(line, NULL, 10);
}

else if(count > 2 && (count <= 2 + numserv))
{
tpf[newc1-1].serverid = strtol(line, NULL, 10);
for(i=0; line[2+i] != ' '; i++)
{
tpf[newc1-1].ipad[i] = line[2+i];
}
tpf[newc-1].ipad[i] = '\0';

for(j=0; line[i+j+2] != '\0'; j++)
{
buf1[j] = line[i+j+3];
}
buf1[j] = '\0';
tpf[newc1-1].port = atoi(buf1);

//change
strcpy(rtdd[tpf[newc1-1].serverid].ipd ,tpf[newc1-1].ipad);
rtdd[tpf[newc1-1].serverid].port = tpf[newc1-1].port;
//change
//if(tpf[newc1-1].ipad == clipad && tpf[newc1-1].port == 7891)//Here!
if(strcmp(tpf[newc1-1].ipad,clipad) == 0)
{
crs = tpf[newc1-1];
}
//cout<<"clipad is "<<clipad<<" Server Id is "<<tpf[newc1-1].serverid<<" IP is "<<tpf[newc1-1].ipad<<" Port is "<<tpf[newc1-1].port<<"\n";//Comment
newc1++;
}

else if(count > 2 + numserv)
{
cost[newc-1].servid = strtol(line, NULL, 10);
for(i=0; line[2+i] != ' '; i++)
{
buf2[i] = line[2+i];
}
buf2[i] = '\0';
cost[newc-1].neighid = atoi(buf2);
for(j=0; line[i+j+2] != '\0'; j++)
{
buf3[j] = line[i+j+3];
}
buf3[j] = '\0';
cost[newc-1].costb = atoi(buf3);
ct[cost[newc-1].neighid].cta = cost[newc-1].costb;
ct[cost[newc-1].neighid].nhn = cost[newc-1].neighid;
if(crs.serverid == cost[newc-1].servid)
{
lofn[ctr] = cost[newc-1].neighid;
ctr++;
}

else if(crs.serverid == cost[newc-1].neighid)
{
lofn[ctr] = cost[newc-1].servid;
ctr++;
}
//cout<<"Cost of neigbour server "<<cost[newc-1].neighid<<"of IP "<<rtdd[cost[newc-1].neighid].ipd<<"is\t"<<ct[cost[newc-1].neighid].cta<<"\n";
newc++ ;
}

//count++ ;
}

if(ctr > 0)
{
lofn[ctr] = '\0';
}


for(int ki= 0;ki<numserv;ki++)
{
for(int kj = 0;kj<ctr;kj++)
{
if(tpf[ki].serverid == lofn[kj])
{
tpf[ki].isneigh = 1;
}
}
}

for(int ki = 0;ki<numserv;ki++)
{
st[ki] = time(0);
ctrr[ki] = 0;
}

//Reading Topology file ends

//--Code to take commands
printf("Server is up, listening to commands\n");
printf("Please enter a command\n");

//Master Socket Code
int udpSocket,activity;
  char buffer[1024];
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;

  udpSocket = socket(PF_INET, SOCK_DGRAM, 0);

  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(crs.port);
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
  bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
  addr_size = sizeof serverStorage;

//MasterSocket Code ends

    printf("Please enter your option :\n");       
    while(TRUE) 
    {
        FD_ZERO(&readfds);
        FD_SET(udpSocket, &readfds);
        FD_SET(STDIN, &readfds);
        
        max_sd = udpSocket;
        if(STDIN > max_sd)
{ max_sd = STDIN;
}


tv.tv_sec = interval;
tv.tv_usec = 0;


        activity = select( max_sd + 1 , &readfds , NULL , NULL , &tv);
    
        if ((activity < 0) && (errno!=EINTR)) 
        {
            printf("select error");
        }


if(activity > 0)//listening/receiving for updates from neighbors and storing them in the routing table
{
if(FD_ISSET(udpSocket, &readfds)) 
{
void *bufrv = calloc(1024, sizeof(char));
uint16_t num,nob= 0,port,nBytes,ports,acost,svid,svids;
struct sockaddr_in sds;
char ipad[32],buffer[1024],ipads[32];
nBytes = recvfrom(udpSocket,bufrv,1024,0,(struct sockaddr *)&serverStorage, &addr_size);
packets++;
memcpy(&(num), bufrv, 2);
nob += 2;
memcpy(&(sds.sin_port), bufrv + nob, 2);
nob += 2;
memcpy(&(sds.sin_addr), bufrv + nob, 4);
nob += 4;
memcpy(&(svids), bufrv + nob, 2);
nob += 2;

memcpy(&(acost), bufrv + nob, 2);
nob += 2;

ports = ntohs(sds.sin_port);
inet_ntop(AF_INET, &(sds.sin_addr), ipads, INET_ADDRSTRLEN);
time_t et = time(0);


for(int y=0;y<num-1;y++)
{
memcpy(&(sds.sin_addr), bufrv + nob, 4);
nob += 4;

memcpy(&(sds.sin_port), bufrv + nob, 2);
nob += 2;

memcpy(&(svid), bufrv + nob, 2);
nob += 2;

memcpy(&(acost), bufrv + nob, 2);
nob += 2;
port = ntohs(sds.sin_port);
inet_ntop(AF_INET, &(sds.sin_addr), ipad, INET_ADDRSTRLEN);

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//BELLMAN FORD ALGORITHM STARTS
//Explained in Comments below
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------

//checking if f[l-1](u) < f[l](v) + w(u,v) for all u,v belongs to edge.
//Here f[l](v) is shortest path from node v to a particular destination and w(u,v) is the intial weight of the edge/link between u and v
if(svid != crs.serverid)
{
if(ct[svid].cta > acost + ct[svids].cta)//Bellman Ford check done here
{
ct[svid].cta = acost + ct[svids].cta;//updating the shortest path if the condition is satisfied
ct[svid].nhn = svids;
}
}


else
{
ct[svids].cta = acost;
}

//checking for server messages timeout
//Note that a buffer time is added to the time 3 successive update time to account for delay due to packet losses
for(int ki = 0; ki<numserv;ki++)
{
if(tpf[ki].isneigh == 1)
{
if((svids != tpf[ki].serverid) && (difftime(et,st[ki]) > 4*(interval+1)))
{
ctrr[tpf[ki].serverid] = 1;
}
}

if(svids == tpf[ki].serverid)
{
ctrr[tpf[ki].serverid] = 0;
st[ki] = et;//resetting the timevalue for timeout when a message is received 
}

}


}

}
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//BELLMAN FORD ALGORITHM ENDS
//Explained in Comments above
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------

if(FD_ISSET(STDIN, &readfds)) 
{
fgets(buf,40,stdin);
buf[strlen(buf)-1]='\0';
if(strcmp(buf, "help") == 0)
{
cout<<"The neighbors are\n";
for(int ki = 0; ki<numserv;ki++)
{
if(tpf[ki].isneigh == 1)
{
cout<<tpf[ki].serverid<<"\t";
}
}
cout<<"\n";
}


else if(strcmp(buf, "display") == 0)
{

for(int d=1;d<=numserv;d++)
{
if(d == crs.serverid)
{
cout<<d<<"\t"<<d<<"\t"<<"0"<<"\n";
}
else if(ctrr[d] == 1)
{
cout<<d<<"\t"<<ct[d].nhn<<"\t"<<"Infinity"<<"\n";

ct[d].cta = 10000;

for(int ki = 0; ki<numserv;ki++)
{
if(tpf[ki].isneigh == 1)
{
int clientSocket[10],nBytesc;
char bufferc[1024];
struct sockaddr_in serverAddrc;
socklen_t addr_sizec;

clientSocket[ki] = socket(PF_INET, SOCK_DGRAM, 0);

serverAddrc.sin_family = AF_INET;
serverAddrc.sin_port = htons(tpf[ki].port);
serverAddrc.sin_addr.s_addr = inet_addr(tpf[ki].ipad);
memset(serverAddrc.sin_zero, '\0', sizeof serverAddrc.sin_zero);  

addr_sizec = sizeof serverAddrc;
struct sockaddr_in sds;
inet_pton(AF_INET, crs.ipad, &(sds.sin_addr));
sds.sin_port = htons(crs.port);
int nob= 0;
uint16_t num_updates = 3+numedge,zer= 0;
void *bufsend = calloc((12 * num_updates + 8), sizeof(char));
num_updates = numedge+1;
memcpy(bufsend, &(num_updates), 2);
nob += 2;
memcpy(bufsend + nob, &(sds.sin_port), 2);
nob += 2;
memcpy(bufsend + nob, &(sds.sin_addr), 4);
nob += 4;
memcpy(bufsend + nob, &(crs.serverid), 2);
nob += 2;
memcpy(bufsend + nob, &(zer), 2);
nob += 2;


for(int y = 0;y<numedge;y++)
{
inet_pton(AF_INET, rtdd[cost[y].neighid].ipd, &(sds.sin_addr));
sds.sin_port = htons(rtdd[cost[y].neighid].port);
memcpy(bufsend + nob, &(sds.sin_addr), 4);
nob += 4;
memcpy(bufsend + nob, &(sds.sin_port), 2);
nob += 2;
memcpy(bufsend + nob, &(cost[y].neighid), 2);
nob += 2;
memcpy(bufsend + nob, &(ct[cost[y].neighid].cta), 2);
nob += 2;
}


nBytesc = strlen(bufferc) + 1;
sendto(clientSocket[ki],bufsend,sizeof(char) * (12 * num_updates + 8),0,(struct sockaddr *)&serverAddrc,addr_sizec);

}

}


}

else if(ct[d].cta >= 10000)
{
cout<<d<<"\t"<<ct[d].nhn<<"\t"<<"Infinity"<<"\n";
}

else
{
cout<<d<<"\t"<<ct[d].nhn<<"\t"<<ct[d].cta<<"\n";
}
}
cout<<"display SUCCESS\n";
}

else if((strncmp(buf, "update", 6) == 0) && (strstr(buf,"inf") != NULL))
{
up2 = int(buf[9]) - '0';

ct[up2].cta = 10000;

for(int ki = 0; ki<numserv;ki++)
{
if(tpf[ki].isneigh == 1)
{
int clientSocket[10],nBytesc;
char bufferc[1024];
struct sockaddr_in serverAddrc;
socklen_t addr_sizec;

clientSocket[ki] = socket(PF_INET, SOCK_DGRAM, 0);

serverAddrc.sin_family = AF_INET;
serverAddrc.sin_port = htons(tpf[ki].port);

serverAddrc.sin_addr.s_addr = inet_addr(tpf[ki].ipad);
memset(serverAddrc.sin_zero, '\0', sizeof serverAddrc.sin_zero);  

addr_sizec = sizeof serverAddrc;
struct sockaddr_in sds;
inet_pton(AF_INET, crs.ipad, &(sds.sin_addr));
sds.sin_port = htons(crs.port);
int nob= 0;
uint16_t num_updates = 3+numedge,zer= 0;
void *bufsend = calloc((12 * num_updates + 8), sizeof(char));
num_updates = numedge+1;
memcpy(bufsend, &(num_updates), 2);
nob += 2;
memcpy(bufsend + nob, &(sds.sin_port), 2);
nob += 2;
memcpy(bufsend + nob, &(sds.sin_addr), 4);
nob += 4;
memcpy(bufsend + nob, &(crs.serverid), 2);
nob += 2;
memcpy(bufsend + nob, &(zer), 2);
nob += 2;


for(int y = 0;y<numedge;y++)
{
inet_pton(AF_INET, rtdd[cost[y].neighid].ipd, &(sds.sin_addr));
sds.sin_port = htons(rtdd[cost[y].neighid].port);
memcpy(bufsend + nob, &(sds.sin_addr), 4);
nob += 4;
memcpy(bufsend + nob, &(sds.sin_port), 2);
nob += 2;
memcpy(bufsend + nob, &(cost[y].neighid), 2);
nob += 2;
memcpy(bufsend + nob, &(ct[cost[y].neighid].cta), 2);
nob += 2;
}

nBytesc = strlen(bufferc) + 1;
sendto(clientSocket[ki],bufsend,sizeof(char) * (12 * num_updates + 8),0,(struct sockaddr *)&serverAddrc,addr_sizec);
}

}

cout<<buf<<" SUCCESS\n";

}

else if(strncmp(buf, "update", 6) == 0)
{
up1 = int(buf[7]) - '0';
up2 = int(buf[9]) - '0';
up3 = int(buf[11]) - '0';
ct[up2].cta = up3;

for(int ki = 0; ki<numserv;ki++)
{
if(tpf[ki].isneigh == 1)
{
int clientSocket[10],nBytesc;
char bufferc[1024];
struct sockaddr_in serverAddrc;
socklen_t addr_sizec;

clientSocket[ki] = socket(PF_INET, SOCK_DGRAM, 0);

serverAddrc.sin_family = AF_INET;
serverAddrc.sin_port = htons(tpf[ki].port);
serverAddrc.sin_addr.s_addr = inet_addr(tpf[ki].ipad);
memset(serverAddrc.sin_zero, '\0', sizeof serverAddrc.sin_zero);  

addr_sizec = sizeof serverAddrc;
struct sockaddr_in sds;
inet_pton(AF_INET, crs.ipad, &(sds.sin_addr));
sds.sin_port = htons(crs.port);
int nob= 0;
uint16_t num_updates = 3+numedge,zer= 0;
void *bufsend = calloc((12 * num_updates + 8), sizeof(char));
num_updates = numedge+1;
memcpy(bufsend, &(num_updates), 2);
nob += 2;
memcpy(bufsend + nob, &(sds.sin_port), 2);
nob += 2;
memcpy(bufsend + nob, &(sds.sin_addr), 4);
nob += 4;
memcpy(bufsend + nob, &(crs.serverid), 2);
nob += 2;
memcpy(bufsend + nob, &(zer), 2);
nob += 2;


for(int y = 0;y<numedge;y++)
{
inet_pton(AF_INET, rtdd[cost[y].neighid].ipd, &(sds.sin_addr));
sds.sin_port = htons(rtdd[cost[y].neighid].port);
memcpy(bufsend + nob, &(sds.sin_addr), 4);
nob += 4;
memcpy(bufsend + nob, &(sds.sin_port), 2);
nob += 2;
memcpy(bufsend + nob, &(cost[y].neighid), 2);
nob += 2;
memcpy(bufsend + nob, &(ct[cost[y].neighid].cta), 2);
nob += 2;
}


nBytesc = strlen(bufferc) + 1;
sendto(clientSocket[ki],bufsend,sizeof(char) * (12 * num_updates + 8),0,(struct sockaddr *)&serverAddrc,addr_sizec);
}

}

cout<<buf<<" SUCCESS\n";
}

else if(strcmp(buf, "packets") == 0)
{
cout<<"packets SUCCESS\n";
cout<<"Number of packets received are "<<packets<<"\n";
}


else if(strncmp(buf, "disable", 7) == 0)
{
int jkl = int(buf[8]) - '0';

ct[jkl].cta = 10000;

for(int ki = 0; ki<numserv;ki++)
{
if(tpf[ki].isneigh == 1)
{
int clientSocket[10],nBytesc;
char bufferc[1024];
struct sockaddr_in serverAddrc;
socklen_t addr_sizec;

clientSocket[ki] = socket(PF_INET, SOCK_DGRAM, 0);

serverAddrc.sin_family = AF_INET;
serverAddrc.sin_port = htons(tpf[ki].port);

serverAddrc.sin_addr.s_addr = inet_addr(tpf[ki].ipad);
memset(serverAddrc.sin_zero, '\0', sizeof serverAddrc.sin_zero);  

addr_sizec = sizeof serverAddrc;
struct sockaddr_in sds;
inet_pton(AF_INET, crs.ipad, &(sds.sin_addr));
sds.sin_port = htons(crs.port);
int nob= 0;
uint16_t num_updates = 3+numedge,zer= 0;
void *bufsend = calloc((12 * num_updates + 8), sizeof(char));
num_updates = numedge+1;
memcpy(bufsend, &(num_updates), 2);
nob += 2;
memcpy(bufsend + nob, &(sds.sin_port), 2);
nob += 2;
memcpy(bufsend + nob, &(sds.sin_addr), 4);
nob += 4;
memcpy(bufsend + nob, &(crs.serverid), 2);
nob += 2;
memcpy(bufsend + nob, &(zer), 2);
nob += 2;


for(int y = 0;y<numedge;y++)
{
inet_pton(AF_INET, rtdd[cost[y].neighid].ipd, &(sds.sin_addr));
sds.sin_port = htons(rtdd[cost[y].neighid].port);
memcpy(bufsend + nob, &(sds.sin_addr), 4);
nob += 4;
memcpy(bufsend + nob, &(sds.sin_port), 2);
nob += 2;
memcpy(bufsend + nob, &(cost[y].neighid), 2);
nob += 2;
memcpy(bufsend + nob, &(ct[cost[y].neighid].cta), 2);
nob += 2;
}


nBytesc = strlen(bufferc) + 1;
sendto(clientSocket[ki],bufsend,sizeof(char) * (12 * num_updates + 8),0,(struct sockaddr *)&serverAddrc,addr_sizec);
}

}


cout<<buf<<" SUCCESS\n";
}

else if(strcmp(buf, "crash") == 0)
{
break;
}

else if(strcmp(buf, "step") == 0)
{

for(int ki = 0; ki<numserv;ki++)
{
if(tpf[ki].isneigh == 1)
{
int clientSocket[10],nBytesc;
char bufferc[1024];
struct sockaddr_in serverAddrc;
socklen_t addr_sizec;

clientSocket[ki] = socket(PF_INET, SOCK_DGRAM, 0);

serverAddrc.sin_family = AF_INET;
serverAddrc.sin_port = htons(tpf[ki].port);

serverAddrc.sin_addr.s_addr = inet_addr(tpf[ki].ipad);
memset(serverAddrc.sin_zero, '\0', sizeof serverAddrc.sin_zero);  

addr_sizec = sizeof serverAddrc;
struct sockaddr_in sds;
inet_pton(AF_INET, crs.ipad, &(sds.sin_addr));
sds.sin_port = htons(crs.port);
int nob= 0;
uint16_t num_updates = 3+numedge,zer= 0;
void *bufsend = calloc((12 * num_updates + 8), sizeof(char));
num_updates = numedge+1;
memcpy(bufsend, &(num_updates), 2);
nob += 2;
memcpy(bufsend + nob, &(sds.sin_port), 2);
nob += 2;
memcpy(bufsend + nob, &(sds.sin_addr), 4);
nob += 4;
memcpy(bufsend + nob, &(crs.serverid), 2);
nob += 2;
memcpy(bufsend + nob, &(zer), 2);
nob += 2;


for(int y = 0;y<numedge;y++)
{
inet_pton(AF_INET, rtdd[cost[y].neighid].ipd, &(sds.sin_addr));
sds.sin_port = htons(rtdd[cost[y].neighid].port);
memcpy(bufsend + nob, &(sds.sin_addr), 4);
nob += 4;
memcpy(bufsend + nob, &(sds.sin_port), 2);
nob += 2;
memcpy(bufsend + nob, &(cost[y].neighid), 2);
nob += 2;
memcpy(bufsend + nob, &(ct[cost[y].neighid].cta), 2);
nob += 2;
}




nBytesc = strlen(bufferc) + 1;
sendto(clientSocket[ki],bufsend,sizeof(char) * (12 * num_updates + 8),0,(struct sockaddr *)&serverAddrc,addr_sizec);
}
}

//sending ends

cout<<"step SUCCESS\n";
}


else
{
printf("Please enter the right command to the server\n");
}

}//STDIN
}//activity



if(activity == 0)
{
for(int ki = 0; ki<numserv;ki++)
{
if(tpf[ki].isneigh == 1)
{
int clientSocket[10],nBytesc;
char bufferc[1024];
struct sockaddr_in serverAddrc;
socklen_t addr_sizec;

clientSocket[ki] = socket(PF_INET, SOCK_DGRAM, 0);

serverAddrc.sin_family = AF_INET;
serverAddrc.sin_port = htons(tpf[ki].port);

serverAddrc.sin_addr.s_addr = inet_addr(tpf[ki].ipad);
memset(serverAddrc.sin_zero, '\0', sizeof serverAddrc.sin_zero);  

addr_sizec = sizeof serverAddrc;
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//ROUTING TABLE STRUCTURE STARTS
//Explained in Comments below
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
struct sockaddr_in sds;
inet_pton(AF_INET, crs.ipad, &(sds.sin_addr));
sds.sin_port = htons(crs.port);
int nob= 0;
uint16_t num_updates = 3+numedge,zer= 0;
void *bufsend = calloc((12 * num_updates + 8), sizeof(char));
num_updates = numedge+1;
memcpy(bufsend, &(num_updates), 2);//sending the number of updates stored in num_updates variable
nob += 2;
memcpy(bufsend + nob, &(sds.sin_port), 2);//sending the server port of the server which is sending the packet, stored in crs.port
nob += 2;
memcpy(bufsend + nob, &(sds.sin_addr), 4);//sending the server ip of the server which is sending the packet, stored in crs.ipad
nob += 4;
memcpy(bufsend + nob, &(crs.serverid), 2);//sendind server id of current server with cost 0 as required
nob += 2;
memcpy(bufsend + nob, &(zer), 2);//sendind server id of current server with cost 0 as required
nob += 2;


for(int y = 0;y<numedge;y++)
{
inet_pton(AF_INET, rtdd[cost[y].neighid].ipd, &(sds.sin_addr));
sds.sin_port = htons(rtdd[cost[y].neighid].port);
memcpy(bufsend + nob, &(sds.sin_addr), 4);//sending the server ip of the neighbor, stored in rtdd[server id of the neighbor].ipd
nob += 4;
memcpy(bufsend + nob, &(sds.sin_port), 2);//sending the port number of the neighbor, stored in rtdd[server id of the neighbor].port
nob += 2;
memcpy(bufsend + nob, &(cost[y].neighid), 2);//sending the cost of link from current server to the neighbor, stored in cost[iterator].neighid
nob += 2;
memcpy(bufsend + nob, &(ct[cost[y].neighid].cta), 2);//sending the cost of link from current server to the neighbor, stored in ct[server id of the neighbor].port
nob += 2;
}

//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------
//ROUTING TABLE STRUCTURE ENDS
//Explained in Comments above
//------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------


nBytesc = strlen(bufferc) + 1;
sendto(clientSocket[ki],bufsend,sizeof(char) * (12 * num_updates + 8),0,(struct sockaddr *)&serverAddrc,addr_sizec);
}
}
}

}//while

}


//---Main Starts here
int main(int argc , char *argv[])
{
if(strcmp(argv[1], "-t") == 0 && strcmp(argv[3], "-i") == 0)
{
storeip();
strcpy(tpl,argv[2]);
interval = atoi(argv[4]);
StartupServer(); 
}

else
{
printf("Please enter the right format for server startup : server -t <topology-file-name> -i <routing-update-interval>\n");
}

return 0;
}
