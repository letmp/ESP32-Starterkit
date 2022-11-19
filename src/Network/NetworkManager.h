#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <Arduino.h>
#include <ESPmDNS.h>
#include <ETH.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include <Persistence/PersistenceManager.h>
#include <Common/Common.h>

#define TIMEOUT_NETWORK 5000
#define HTTP_PORT 80
#define MQTT_PORT 1883

#define ETH_ADDR 0		 // I²C-address of Ethernet PHY (0 or 1 for LAN8720, 31 for TLK110)
#define ETH_POWER_PIN -1 // Pin# of the enable signal for the external crystal oscillator (-1 to disable for internal APLL source)
#define ETH_MDC_PIN 23	 // Pin# of the I²C clock signal for the Ethernet PHY
#define ETH_MDIO_PIN 18	 // Pin# of the I²C IO signal for the Ethernet PHY
#define ETH_TYPE ETH_PHY_LAN8720
#ifdef ETH_CLK_MODE
#undef ETH_CLK_MODE
#endif
#define ETH_CLK_MODE ETH_CLOCK_GPIO17_OUT // ETH_CLOCK_GPIO0_IN

class NetworkManager
{

private:
	PersistenceManager mPersistenceManager;

	String mUniqueHostname;

	// these parameters should match the template placeholders in data/netconfig.html
	String PARAM_HOSTNAME = "hostname";
	String PARAM_NETCONFIG = "netConfig";
	String PARAM_WIFI_SSID = "wifiSSID";
	String PARAM_WIFI_PWD = "wifiPwd";
	String PARAM_STATIC_WIFI_IP = "staticWifiIP";
	String PARAM_STATIC_WIFI_GATEWAY = "staticWifiGateway";
	String PARAM_STATIC_ETH_IP = "staticEthIP";
	String PARAM_STATIC_ETH_GATEWAY = "staticEthGateway";

	String mWifiSSID;
	String mWifiPassword;

	IPAddress mIpAddressSubnet;

	bool mHasStaticWifiAddress;
	IPAddress mIpAddressWifi;
	IPAddress mIpAddressWifiGateway;

	bool mHasStaticEthAddress;
	IPAddress mIpAddressEth;
	IPAddress mIpAddressEthGateway;

	void setUniqueHostname();
	bool loadWifiConfig();
	bool loadEthConfig();
	bool initWifiAP();
	bool initWifiSTA();
	bool initETH();

	void initMdns();

	AsyncWebServer mAsyncWebServer;
	void startWebServer(bool hasWifiConfig);
	void handleGetNetconfig(AsyncWebServerRequest *request);
	void handlePostNetconfig(AsyncWebServerRequest *request);
	String processTemplateNetconfig(const String &var);
	void writeParameterToSPIFFS(AsyncWebParameter *p, String parameter);

public:
	NetworkManager();
	void begin();

	void loop();
};

#endif