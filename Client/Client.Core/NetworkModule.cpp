#include <iostream>
#include <MessageIdentifiers.h>
#include "NetworkModule.h"

#include "NetworkRPC.h"
#include "GeneralRPC.h"
#include "PlayerRPC.h"
#include "ProjectGlobals.h"

#include "Utilities.h"

NetworkModule::NetworkModule() :
	m_rakPeer(RakNet::RakPeerInterface::GetInstance()), m_rpc(RakNet::RPC4::GetInstance()), m_connected(false), m_netState(NETSTATE_NONE)
{
	m_rakPeer->AttachPlugin(m_rpc);
	GeneralRPC::registerRPC(m_rpc);
	PlayerRPC::registerRPC(m_rpc);
}

NetworkModule::~NetworkModule()
{
	m_rakPeer->Shutdown(500);

	GeneralRPC::unregisterRPC(m_rpc);
	PlayerRPC::unregisterRPC(m_rpc);

	m_rakPeer->DetachPlugin(m_rpc);

	RakNet::RPC4::DestroyInstance(m_rpc);
	RakNet::RakPeerInterface::DestroyInstance(m_rakPeer);
}


bool	NetworkModule::init()
{
	if (m_rakPeer->Startup(1, &RakNet::SocketDescriptor(), 1, THREAD_PRIORITY_NORMAL) == RakNet::RAKNET_STARTED)
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool	NetworkModule::connect(const std::string& address, short port, const std::string& password)
{
	if (m_connected)
		return true;

	if (m_rakPeer->Connect(address.c_str(), port, password.c_str(), password.length()) == RakNet::ConnectionAttemptResult::CONNECTION_ATTEMPT_STARTED)
	{
		m_netState = NETSTATE_CONNECTING;
		m_connected = true;
		return true;
	}
	else
	{
		m_connected = false;
		return false;
	}
}

void	NetworkModule::disconnect()
{
	if (!m_connected)
		return;
	m_rakPeer->CloseConnection(RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
	m_connected = false;
	m_netState = NETSTATE_DISCONNECTED;
}

void	NetworkModule::pulse()
{
	RakNet::Packet*	packet = nullptr;

	if (m_netState == NETSTATE_DISCONNECTED)
		return;

	while (packet = m_rakPeer->Receive())
	{
		if (!packet)
			continue;

		switch (packet->data[0])
		{
		case ID_CONNECTION_REQUEST_ACCEPTED:
			connectionAccepted(packet);
			break;
		}
		m_rakPeer->DeallocatePacket(packet);
	}
}

void	NetworkModule::connectionAccepted(RakNet::Packet* packet)
{
	std::cout << "Appel connection accepted" << std::endl;
	RakNet::BitStream	bits;

	m_netState = NETSTATE_CONNECTED;

	//Todo: Dynamize this function
	std::string serial = Utilities::GetSerialHash();
	bits.Write(RakNet::RakString("Enguerrand"));
	bits.Write(RakNet::RakString(serial.c_str()));

	callRPC(RPC_CONNECT, &bits, HIGH_PRIORITY, RELIABLE_ORDERED, true);
}


void	NetworkModule::callRPC(const std::string& rpc, RakNet::BitStream* bitStream, PacketPriority packetPriority, PacketReliability packetReliability, bool broadcast)
{
	if (m_rpc != nullptr)
		m_rpc->Call(rpc.c_str(), bitStream, packetPriority, packetReliability, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, broadcast);
}


RakNet::RakPeerInterface*	NetworkModule::getRakPeer()
{
	return m_rakPeer;
}

RakNet::RPC4*	NetworkModule::getRPC()
{
	return m_rpc;
}

bool	NetworkModule::isConnected()	const
{
	return m_connected;
}

void	NetworkModule::setNetState(eNetworkState netState)
{
	m_netState = netState;
}

eNetworkState	NetworkModule::getNetState() const
{
	return m_netState;
}