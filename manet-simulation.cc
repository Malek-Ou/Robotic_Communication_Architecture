#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/olsr-helper.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"
#include "ns3/flow-monitor-helper.h"
#include "ns3/ipv4-flow-classifier.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("ManetSimulation");

int main (int argc, char *argv[]) {
	// Enable logging
	LogComponentEnable ("ManetSimulation", LOG_LEVEL_INFO);
	LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
	LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);
	LogComponentEnable ("FlowMonitor", LOG_LEVEL_INFO);

	// Create nodes
	NodeContainer nodes;
	nodes.Create (5);  // Create 5 nodes

	// Set up Wi-Fi
	WifiHelper wifi;
	wifi.SetStandard (WIFI_STANDARD_80211n);

	WifiMacHelper wifiMac;
	wifiMac.SetType ("ns3::AdhocWifiMac");

	// Set up the PHY layer
	YansWifiPhyHelper wifiPhy;
	wifiPhy.Set ("ChannelSwitchDelay", TimeValue (MicroSeconds (100)));

	// Set up channel with propagation models
	YansWifiChannelHelper wifiChannelHelper;
	wifiChannelHelper.AddPropagationLoss ("ns3::FriisPropagationLossModel");
	wifiChannelHelper.AddPropagationLoss ("ns3::LogDistancePropagationLossModel");
	wifiChannelHelper.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
	Ptr<YansWifiChannel> wifiChannel = wifiChannelHelper.Create ();
	wifiPhy.SetChannel (wifiChannel);

	// Install Wi-Fi devices
	NetDeviceContainer devices = wifi.Install (wifiPhy, wifiMac, nodes);

	// Enable pcap tracing
	wifiPhy.EnablePcap ("manet-simulation", devices);

	// Set up mobility model
	MobilityHelper mobility;
	mobility.SetPositionAllocator ("ns3::GridPositionAllocator",
                               	"MinX", DoubleValue (0.0),
                               	"MinY", DoubleValue (0.0),
                               	"DeltaX", DoubleValue (5.0),
                               	"DeltaY", DoubleValue (10.0),
                               	"GridWidth", UintegerValue (3),
                               	"LayoutType", StringValue ("RowFirst"));
	mobility.SetMobilityModel ("ns3::RandomWaypointMobilityModel",
                           	"Speed", StringValue ("ns3::UniformRandomVariable[Min=1.0|Max=5.0]"),
                           	"Pause", StringValue ("ns3::UniformRandomVariable[Min=1.0|Max=5.0]"),
                           	"PositionAllocator", StringValue ("ns3::GridPositionAllocator"));
	mobility.Install (nodes);

	// Install the internet stack with OLSR
	InternetStackHelper internet;
	OlsrHelper olsr;
	internet.SetRoutingHelper (olsr);
	internet.Install (nodes);

	// Set up IP addresses
	Ipv4AddressHelper ipv4;
	ipv4.SetBase ("10.1.1.0", "255.255.255.0");
	Ipv4InterfaceContainer interfaces = ipv4.Assign (devices);

	// Set up applications
	// UDP Echo Server
	UdpEchoServerHelper echoServer (9); // Port number 9
	ApplicationContainer serverApps = echoServer.Install (nodes.Get (1)); // Install on node 1
	serverApps.Start (Seconds (1.0)); // Start at 1 second
	serverApps.Stop (Seconds (30.0)); // Stop at 30 seconds

	// UDP Echo Client
	UdpEchoClientHelper echoClient (interfaces.GetAddress (1), 9); // Address of server node 1, port 9
	echoClient.SetAttribute ("MaxPackets", UintegerValue (10)); // Send 10 packets
	echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0))); // Interval between packets
	echoClient.SetAttribute ("PacketSize", UintegerValue (1024)); // Packet size of 1024 bytes
	ApplicationContainer clientApps = echoClient.Install (nodes.Get (0)); // Install on node 0
	clientApps.Start (Seconds (2.0)); // Start at 2 seconds
	clientApps.Stop (Seconds (30.0)); // Stop at 30 seconds

	// Set up NetAnim
	AnimationInterface anim ("manet-animation.xml");
	anim.SetMobilityPollInterval (Seconds (1)); // Record positions every 1 second
	anim.SetStartTime (Seconds (0)); // Start time for animation
	anim.SetStopTime (Seconds (30)); // Stop time for animation
	anim.EnablePacketMetadata (true); // Enable packet metadata

	// Update node descriptions and sizes
	anim.UpdateNodeDescription (0, "Source Node"); // Description for node 0
	anim.UpdateNodeSize (0, 1.5, 1.5); // Size for node 0
	anim.UpdateNodeDescription (1, "Destination Node"); // Description for node 1
	anim.UpdateNodeSize (1, 1.5, 1.5); // Size for node 1
	anim.UpdateNodeDescription (2, "Relay Node 1"); // Description for node 2
	anim.UpdateNodeSize (2, 1.5, 1.5); // Size for node 2
	anim.UpdateNodeDescription (3, "Relay Node 2"); // Description for node 3
	anim.UpdateNodeSize (3, 1.5, 1.5); // Size for node 3
	anim.UpdateNodeDescription (4, "Relay Node 3"); // Description for node 4
	anim.UpdateNodeSize (4, 1.5, 1.5); // Size for node 4

	// Set up Flow Monitor
	FlowMonitorHelper flowmon;
	Ptr<FlowMonitor> monitor = flowmon.InstallAll();
	Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowmon.GetClassifier());

	Simulator::Run ();

	// Flow Monitor results
	std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats();
	for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i = stats.begin(); i != stats.end(); ++i) {
    	Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow (i->first);
    	NS_LOG_UNCOND ("Flow " << i->first << " (" << t.sourceAddress << " -> " << t.destinationAddress << ")");
    	NS_LOG_UNCOND (" Tx Bytes: " << i->second.txBytes);
    	NS_LOG_UNCOND (" Rx Bytes: " << i->second.rxBytes);
    	NS_LOG_UNCOND (" Lost Packets: " << i->second.lostPackets);
    	NS_LOG_UNCOND (" Delay: " << i->second.delaySum.GetSeconds () << " s");
    	NS_LOG_UNCOND (" Jitter: " << i->second.jitterSum.GetSeconds () << " s");
	}

	Simulator::Destroy ();
	return 0;
}


