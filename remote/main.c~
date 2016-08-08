#include <upnp/upnp.h>
#include <stdio.h>
#include <string.h>
#include "sample_util.h"
ithread_mutex_t DeviceListMutex;

const char GatewayDeviceType[] = "urn:schemas-upnp-org:device:InternetGatewayDevice:1";

UpnpClient_Handle ctrlpt_handle = -1;


typedef struct RouterNode {
	char serviceType[250];
	char controlUrl[250];
	 struct RouterNode *next;

} Node, *NodeList;

NodeList list;

int CallbackEventHandler(Upnp_EventType EventType, void *Event, void *Cookie)
{
	char *urlBase;
	char controlUrl[100];
	char *ipc = ":1900/ipc";
	printf("Init! EventType = %d\n", EventType);
			struct Upnp_Action_Complete *a_event = (struct Upnp_Action_Complete *)Event;

		
			printf("Error in  Action Complete Callback -- %d:%s\n",
					a_event->ErrCode,a_event);


	
	switch(EventType) {
		case UPNP_DISCOVERY_ADVERTISEMENT_ALIVE:
		case UPNP_DISCOVERY_SEARCH_RESULT: {
			 struct Upnp_Discovery *d_event = (struct Upnp_Discovery *)Event;
			 IXML_Document *DescDoc = NULL;
			 int ret;
			 ret = UpnpDownloadXmlDoc(d_event->Location, &DescDoc);
			 printf("UpnpDownloadXmlDoc ret = %d\n d_event->Location = %s\n", ret, d_event->Location);
			 char *friendlyName = SampleUtil_GetFirstDocumentItem(DescDoc, "friendlyName");
			 urlBase = SampleUtil_GetFirstDocumentItem(DescDoc, "URLBase");
			 strncpy(controlUrl, urlBase, strlen(urlBase));
			 printf("friendlyName = %s controlUrl = %s  urlBase = %s\n", friendlyName, controlUrl, urlBase);
			 strcat(controlUrl, ipc);

			 Node tmp;
			 memcpy(tmp.controlUrl, controlUrl, sizeof(controlUrl));
			 
			 list->next = &tmp;

			 printf("friendlyName = %s controlUrl = %s\n", friendlyName, controlUrl);
				ixmlDocument_free(DescDoc);
			
			break;
		}

		}
	return 0;
}

void sendAction(char *ip_address, char *controlUrl)
{
	IXML_Document *actionNode = NULL;
	char *actionname = "AddPortMapping";
	char *serviceType = "urn:schemas-upnp-org:service:WANIPConnection:1";
	//char *controlUrl = "http://192.168.1.1:1900/ipc";

	char *NewRemoteHost = "NewRemoteHost";
	char *NewRemoteHostVal = "";

	char *NewExternalPort = "NewExternalPort";
	char *NewExternalPortVal = "6547";

	char *NewProtocol = "NewProtocol";
	char *NewProtocolVal = "TCP";

	char *NewInternalPort= "NewInternalPort";
	char *NewInternalPortVal = "6547";

	char *NewInternalClient= "NewInternalClient";
	char *NewInternalClientVal = ip_address;

	char *NewEnabled= "NewEnabled";
	char *NewEnabledVal = "1";

	char *NewLeaseDuration= "NewLeaseDuration";
	char *NewLeaseDurationVal = "0";

	char *NewPortMappingDescription = "NewPortMappingDescription";
	char *NewPortMappingDescriptionVal = "wwwupnp";
	int rc;
	
	
	UpnpAddToAction(&actionNode, actionname,serviceType, NewRemoteHost, NewRemoteHostVal);
	UpnpAddToAction(&actionNode, actionname,serviceType, NewExternalPort, NewExternalPortVal);
	UpnpAddToAction(&actionNode, actionname,serviceType, NewProtocol, NewProtocolVal);
	UpnpAddToAction(&actionNode, actionname,serviceType, NewInternalClient, NewInternalClientVal);
	UpnpAddToAction(&actionNode, actionname,serviceType, NewInternalPort, NewInternalPortVal);
	UpnpAddToAction(&actionNode, actionname,serviceType, NewEnabled, NewEnabledVal);
	UpnpAddToAction(&actionNode, actionname,serviceType, NewLeaseDuration, NewLeaseDurationVal);
	UpnpAddToAction(&actionNode, actionname,serviceType, NewPortMappingDescription, NewPortMappingDescriptionVal);
	rc = UpnpSendActionAsync(ctrlpt_handle,controlUrl,serviceType, NULL,actionNode,CallbackEventHandler, NULL);


	printf("%s\n rc = %d\n", ixmlPrintDocument(actionNode), rc);
	ixmlDocument_free(actionNode);
	
	
}

int main()
{
	int rc;
	unsigned short port = 0;
	char *ip_address = NULL;
	rc = UpnpInit(ip_address, port);

	
	list = (NodeList)malloc(sizeof(Node));
	list->next = NULL;


	ithread_mutex_lock(&DeviceListMutex);
	if(!ip_address) {
		ip_address = UpnpGetServerIpAddress();
	}
	
	if(!port) {
		port = UpnpGetServerPort();
	}
	
	printf("Init! ip_address = %s, port = %u\n", ip_address, port);

	rc = UpnpRegisterClient(CallbackEventHandler,NULL, &ctrlpt_handle);

	printf("Init! rc =  %u\n", rc);

	rc = UpnpSearchAsync(ctrlpt_handle, 100, GatewayDeviceType, NULL);
	printf("Search! rc =  %u\n", rc);

	printf("Search! list->next->controlUrl =  %s\n", list->next->controlUrl);

	NodeList temp = list;
	while(temp->next != NULL) {
		sendAction(ip_address, temp->controlUrl);
		temp = temp->next;

	}

	//sendAction();
	//sleep(10);
	UpnpFinish();
	
	ithread_mutex_unlock(&DeviceListMutex);

	
	return 0;
}

