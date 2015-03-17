#include "GameNet.h"



// We copy this from Multiplayer.cpp to keep things all in one file for this example
unsigned char GetPacketIdentifier(RakNet::Packet *p);
// Copied from Multiplayer.cpp
// If the first byte is ID_TIMESTAMP, then we want the 5th byte
// Otherwise we want the 1st byte
unsigned char GetPacketIdentifier(RakNet::Packet *p)
{
	if (p==0)
		return 255;
    
	if ((unsigned char)p->data[0] == ID_TIMESTAMP)
	{
		RakAssert(p->length > sizeof(RakNet::MessageID) + sizeof(RakNet::Time));
		return (unsigned char) p->data[sizeof(RakNet::MessageID) + sizeof(RakNet::Time)];
	}
	else
		return (unsigned char) p->data[0];
}


void testNet();

std::mutex mtx;

void* ThreadFunction(void* arg)
{
    if(mtx.try_lock())
    {
        GameNet *pGameNet = (GameNet*)arg;
        
        log("ThreadFunction ....");
        testNet();
        
        mtx.unlock();
    
    }
    
   
    return NULL;
    
}


bool GameNet::m_netOnFlag = false;
static GameNet* s_gameNet = NULL;

GameNet::GameNet()
{
    m_thread = NULL;

}



GameNet::~GameNet()
{
    m_netOnFlag = false;
}


GameNet* GameNet::getInstance()
{
    if(s_gameNet == NULL)
    {
        s_gameNet = new GameNet();
    }
    
    return s_gameNet;

}


void GameNet::stopNet()
{
  m_netOnFlag = false;
}

void GameNet::test()
{
    if(m_netOnFlag)
        return;
    
    m_netOnFlag = true;
    
    m_thread = new std::thread(ThreadFunction,this);

}



void testNet()
{
   
	RakNet::RakPeerInterface *client=RakNet::RakPeerInterface::GetInstance();
    //	client->InitializeSecurity(0,0,0,0);
	//RakNet::PacketLogger packetLogger;
	//client->AttachPlugin(&packetLogger);
    
	
	// Holds packets
	RakNet::Packet* p;
    
	// GetPacketIdentifier returns this
    
	unsigned char packetIdentifier;
    
    // Just so we can remember where the packet came from    
	char ip[64], serverPort[30], clientPort[30];
    
    client->AllowConnectionResponseIPMigration(false);
	// Get our input
    strcpy(clientPort, "6666");
    strcpy(ip, "192.168.1.105");
    strcpy(serverPort, "1234");
    
	// Connecting the client is very simple.  0 means we don't care about
	// a connectionValidationInteger, and false for low priority threads
	RakNet::SocketDescriptor socketDescriptor(atoi(clientPort),0);
	socketDescriptor.socketFamily=AF_INET;
	client->Startup(8,&socketDescriptor, 1);
	client->SetOccasionalPing(true);
    
    
	RakNet::ConnectionAttemptResult car = client->Connect(ip, atoi(serverPort), 0, 0);
	if(car !=RakNet::CONNECTION_ATTEMPT_STARTED)
    {
        log("Net connection fail to start!");
    }

    
    
	unsigned int i;
	for (i=0; i < client->GetNumberOfAddresses(); i++)
	{
		log("%i. %s\n", i+1, client->GetLocalIP(i));
	}
    
	log("My GUID is %s\n", client->GetGuidFromSystemAddress(RakNet::UNASSIGNED_SYSTEM_ADDRESS).ToString());
	
	bool isNetSetUp = false;
    
    while (GameNet::m_netOnFlag)
	{
        RakSleep(30);        
        // Get a packet from either the server or the client
        
        if(isNetSetUp )
        {
            char message[2048];
            strcpy(message, "send a message to server!");
            client->Send(message, (int) strlen(message)+1, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
            RakSleep(1000);
        }
        
        
        
		for (p=client->Receive(); p; client->DeallocatePacket(p), p=client->Receive())
		{
			// We got a packet, get the identifier with our handy function
			packetIdentifier = GetPacketIdentifier(p);
            
			// Check if this is a network message packet
			switch (packetIdentifier)
			{
                case ID_DISCONNECTION_NOTIFICATION:
                    // Connection lost normally
                    log("ID_DISCONNECTION_NOTIFICATION\n");
                    break;
                case ID_ALREADY_CONNECTED:
                    // Connection lost normally
                    log("ID_ALREADY_CONNECTED with guid %" PRINTF_64_BIT_MODIFIER "u\n", p->guid);
                    break;
                case ID_INCOMPATIBLE_PROTOCOL_VERSION:
                    log("ID_INCOMPATIBLE_PROTOCOL_VERSION\n");
                    break;
                case ID_REMOTE_DISCONNECTION_NOTIFICATION: // Server telling the clients of another client disconnecting gracefully.  You can manually broadcast this in a peer to peer enviroment if you want.
                    log("ID_REMOTE_DISCONNECTION_NOTIFICATION\n");
                    break;
                case ID_REMOTE_CONNECTION_LOST: // Server telling the clients of another client disconnecting forcefully.  You can manually broadcast this in a peer to peer enviroment if you want.
                    log("ID_REMOTE_CONNECTION_LOST\n");
                    break;
                case ID_REMOTE_NEW_INCOMING_CONNECTION: // Server telling the clients of another client connecting.  You can manually broadcast this in a peer to peer enviroment if you want.
                    log("ID_REMOTE_NEW_INCOMING_CONNECTION\n");
                    break;
                case ID_CONNECTION_BANNED: // Banned from this server
                    log("We are banned from this server.\n");
                    break;
                case ID_CONNECTION_ATTEMPT_FAILED:
                    log("Connection attempt failed\n");
                    break;
                case ID_NO_FREE_INCOMING_CONNECTIONS:
                    // Sorry, the server is full.  I don't do anything here but
                    // A real app should tell the user
                    log("ID_NO_FREE_INCOMING_CONNECTIONS\n");
                    break;
                    
                case ID_INVALID_PASSWORD:
                    log("ID_INVALID_PASSWORD\n");
                    break;
                    
                case ID_CONNECTION_LOST:
                    // Couldn't deliver a reliable packet - i.e. the other system was abnormally
                    // terminated
                    log("ID_CONNECTION_LOST\n");
                    break;
                    
                case ID_CONNECTION_REQUEST_ACCEPTED:
                    // This tells the client they have connected
                    log("ID_CONNECTION_REQUEST_ACCEPTED to %s with GUID %s\n", p->systemAddress.ToString(true), p->guid.ToString());
                    log("My external address is %s\n", client->GetExternalID(p->systemAddress).ToString(true));
                    
                    isNetSetUp = true;
                    break;
                case ID_CONNECTED_PING:
                case ID_UNCONNECTED_PING:
                    log("Ping from %s\n", p->systemAddress.ToString(true));
                    break;
                default:
                    // It's a client, so just show the message
                    log("%s\n", p->data);
                    break;
			}
		}
	}
    
	// Be nice and let the server know we quit.
	client->Shutdown(300);
    
	// We're done with the network
	RakNet::RakPeerInterface::DestroyInstance(client);
    log("thread out");
}






